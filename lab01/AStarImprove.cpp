#include "OnClist.hpp"

using namespace std;

int total_expanded_node;

int AStarSearch(UserState* init_state, UserState* goal_state, int hn)
{
	ClosedSet closed_set;
	OpenSet open_set;
	
	open_set.Insert(init_state);	
	while(!open_set.Empty())
	{
		UserState* current_state=open_set.Min();
		closed_set.Insert(current_state);
		open_set.Erase(current_state);
		total_expanded_node++;
		//~ cout<<current_state.Int_To_String()<<" "<<current_state.Is_Goal_State(goal_state)<<endl;
		if(!(current_state->Is_Goal_State(goal_state)))
		{
			VS child_states;
			current_state->Get_Child_State(child_states);
			int total_child=child_states.sz();
			for(int i=0; i<total_child; i++)
			{
				int gtmp=current_state->g+child_states[i]->Dist_Between_Parent_Child();
				int gchildc=closed_set.Find(child_states[i]), gchildo=open_set.Find(child_states[i]);
				if(!gchildc)
				{
					if(!gchildo || gtmp<gchildo)
					{
						child_states[i]->g=gtmp;
						child_states[i]->h=child_states[i]->Heuristic_Estimate(goal_state,hn);
						child_states[i]->f=child_states[i]->g+child_states[i]->h;
						child_states[i]->parent_state=current_state;
						if(gtmp<gchildo)
						{
							open_set.Erase(child_states[i]);
						}
						open_set.Insert(child_states[i]);
					}
				}
				else if(gtmp<gchildc)
				{
					closed_set.Erase(child_states[i]);
					child_states[i]->g=gtmp;
					child_states[i]->h=child_states[i]->Heuristic_Estimate(goal_state,hn);
					child_states[i]->f=child_states[i]->g+child_states[i]->h;
					child_states[i]->parent_state=current_state;
					if(gchildo)
					{
						open_set.Erase(child_states[i]);
					}
					open_set.Insert(child_states[i]);
				}
			}
		}
		else
		{
			current_state->Print_Path(current_state,0);
			return 1;
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
		
		total_expanded_node=0;
		AStarSearch(init_state,goal_state,hn);
		cout<<endl;
		//~ cout<<AStarSearch(init_state,goal_state,hn)<<" ";
		//~ cout<<total_expanded_node<<endl<<endl;
	}
}
