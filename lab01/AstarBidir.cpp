#include "OnClist.hpp"

using namespace std;
int total_expanded_nodeS, total_expanded_nodeG;

int AStarSearch(UserState* init_state, UserState* goal_state, int hn)
{
	ClosedSet closed_setS, closed_setG;
	OpenSet open_setS, open_setG;
	
	open_setS.Insert(init_state);
	open_setG.Insert(goal_state);	
	
	while(!open_setS.Empty() && !open_setG.Empty())
	{
		UserState* current_stateS=open_setS.Min();
		UserState* current_stateG=open_setG.Min();
		
		closed_setS.Insert(current_stateS);
		closed_setG.Insert(current_stateG);
		open_setS.Erase(current_stateS);
		open_setG.Erase(current_stateG);
		
		total_expanded_nodeG++;
		total_expanded_nodeS++;
		//cout<<current_stateS.Int_To_String()<<" "<<current_stateG.Int_To_String()<<endl;
		if(current_stateS->Is_Goal_State(current_stateG))
		{
			current_stateS->Print_Path(current_stateS,0);
			current_stateG->Print_Path(current_stateG,0);
			return 1;
		}
		if(!(current_stateS->Is_Goal_State(goal_state)))
		{
			VS child_states;
			current_stateS->Get_Child_State(child_states);
			int total_child=child_states.sz();			
			for(int i=0; i<total_child; i++)
			{
				int gtmp=current_stateS->g+child_states[i]->Dist_Between_Parent_Child();
				int gchildc=closed_setS.Find(child_states[i]), gchildo=open_setS.Find(child_states[i]);
				if(!gchildc)
				{
					if(!gchildo || gtmp<gchildo)
					{
						child_states[i]->g=gtmp;
						child_states[i]->h=child_states[i]->Heuristic_Estimate(goal_state,hn);
						child_states[i]->f=child_states[i]->g+child_states[i]->h;
						child_states[i]->parent_state=current_stateS;
						if(gtmp<gchildo) open_setS.Erase(child_states[i]);
						open_setS.Insert(child_states[i]);
					}
				}
				else if(gtmp<gchildc)
				{
					closed_setS.Erase(child_states[i]);
					child_states[i]->g=gtmp;
					child_states[i]->h=child_states[i]->Heuristic_Estimate(goal_state,hn);
					child_states[i]->f=child_states[i]->g+child_states[i]->h;
					child_states[i]->parent_state=current_stateS;
					if(gchildo)	open_setS.Erase(child_states[i]);
					open_setS.Insert(child_states[i]);
				}
			}
		}
		else 
		{
			current_stateS->Print_Path(current_stateS,0);
			return 2;
		}
		
		if(!(current_stateG->Is_Goal_State(init_state)))
		{
			VS child_statesG;
			current_stateG->Get_Child_State(child_statesG);
			int total_childG=child_statesG.sz();			
			for(int i=0; i<total_childG; i++)
			{
				int gtmpG=current_stateG->g+child_statesG[i]->Dist_Between_Parent_Child();
				int gchildcG=closed_setG.Find(child_statesG[i]), gchildoG=open_setG.Find(child_statesG[i]);
				if(!gchildcG)
				{
					if(!gchildoG || gtmpG<gchildoG)
					{
						child_statesG[i]->g=gtmpG;
						child_statesG[i]->h=child_statesG[i]->Heuristic_Estimate(init_state,hn);
						child_statesG[i]->f=child_statesG[i]->g+child_statesG[i]->h;
						child_statesG[i]->parent_state=current_stateG;
						if(gtmpG<gchildoG) open_setS.Erase(child_statesG[i]);
						open_setG.Insert(child_statesG[i]);
					}
				}
				else if(gtmpG<gchildcG)
				{
					closed_setS.Erase(child_statesG[i]);
					child_statesG[i]->g=gtmpG;
					child_statesG[i]->h=child_statesG[i]->Heuristic_Estimate(init_state,hn);
					child_statesG[i]->f=child_statesG[i]->g+child_statesG[i]->h;
					child_statesG[i]->parent_state=current_stateG;
					if(gchildoG) open_setG.Erase(child_statesG[i]);
					open_setG.Insert(child_statesG[i]);
				}
			}
		}
		else
		{
			current_stateG->Print_Path(current_stateG,0);
			return 3;
		}
	}
	return -1;
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		UserState* init_state=new UserState;
		UserState* goal_state=new UserState;
		for(int i=0; i<SQDIMENTION; i++)
		{
			for(int j=0; j<SQDIMENTION; j++)
			{
				int val;
				scanf("%d",&val);
				init_state->state_val[val].x=i;
				init_state->state_val[val].y=j;
			}
		}
		
		for(int i=0; i<SQDIMENTION; i++)
		{
			for(int j=0; j<SQDIMENTION; j++)
			{
				int val;
				scanf("%d",&val);
				goal_state->state_val[val].x=i;
				goal_state->state_val[val].y=j;
			}
		}
		
		int hn;
		cin>>hn;
		
		init_state->parent_state=NULL;
		init_state->g=0;
		init_state->h=init_state->Heuristic_Estimate(goal_state,hn);
		init_state->f=init_state->h;
		
		goal_state->parent_state=NULL;
		goal_state->g=0;
		goal_state->h=init_state->Heuristic_Estimate(goal_state,hn);
		goal_state->f=init_state->h;
		
		total_expanded_nodeG=0;
		total_expanded_nodeS=0;
		AStarSearch(init_state,goal_state,hn);
		cout<<endl;
		//~ cout<<AStarSearch(init_state,goal_state,hn)<<" ";
		//~ cout<<total_expanded_nodeG<<" "<<total_expanded_nodeS<<endl<<endl;
	}
}
