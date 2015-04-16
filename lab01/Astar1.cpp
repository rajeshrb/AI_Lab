#include "UserState.hpp"

using namespace std;

class Compare
{
	public:
		bool operator()(UserState* X, UserState* Y) {return X->f>=Y->f;}	
};

#define em empty
#define VS vector<UserState* >
#define pb push_back
#define sz size
#define LS list<UserState* >
#define ITR(x) x::iterator
#define bg begin
#define en end
#define dlt erase
#define bk back

ITR(LS) State_with_Maxf(LS & OpenList)
{
	ITR(LS) bgn=OpenList.bg(), edn=OpenList.en(), itrMax;
	itrMax=bgn;
	bgn++;
	for(; bgn!=edn; bgn++) if((*bgn)->f<(*itrMax)->f) itrMax=bgn;
	return itrMax;	
}
int count=0;
int AStarSearch(UserState* initState, UserState* goalState)
{
	VS ClosedList;
	LS OpenList;
	initState->g=0;
	initState->h=initState->heuristic_Estimate(goalState);
	initState->f=initState->g+initState->h;
	initState->parentState=NULL;
	OpenList.pb(initState);
	
	while(!OpenList.em())
	{
		ITR(LS) itrMax=State_with_Maxf(OpenList);
		UserState* currentState=(*itrMax);
		ClosedList.pb(currentState);
		OpenList.dlt(itrMax);
		count++;
		//~ cout<<count<<endl;
		//~ for(int i=0; i<3; i++)
		//~ {
			//~ for(int j=0; j<3; j++) printf("%d ", currentState->posVal[i][j]);
			//~ printf("\n");	
		//~ }
		//~ cout<<(currentState->f)<< endl;
		
		if(!(currentState->isGoalState(goalState)))
		{
			//cout<<"A ";
			VS childStates;
			currentState->getChildState(childStates);
			int totalChild=childStates.sz();
			//cout<<totalChild<<endl;
			for(int i=0; i<totalChild; i++)
			{
				//cout<<"F "<<childStates[i]->Not_in_ClosedList(ClosedList)<<" ";
				if(childStates[i]->Not_in_ClosedList(ClosedList))
				{
					//cout<<"B ";
					int gtmp=currentState->g+childStates[i]->Dist_Between_parentAndChild();
					ITR(LS) itrchild=childStates[i]->Not_in_OpenList(OpenList), itren=OpenList.en();
					if(itrchild==itren)
					{
						//cout<<"C ";
						childStates[i]->g=gtmp;
						childStates[i]->h=childStates[i]->heuristic_Estimate(goalState);
						childStates[i]->f=childStates[i]->g+childStates[i]->h;
						childStates[i]->parentState=currentState;
						OpenList.pb(childStates[i]);
						//cout<<OpenList.sz()<<endl;
						//~ for(int a=0; a<3; a++)
						//~ {
							//~ for(int b=0; b<3; b++) printf("%d ", childStates[i]->posVal[a][b]);
							//~ printf("\n");	
						//~ }
						//~ 
						//~ cout<<(childStates[i]->f)<<endl;
					}
					else if(gtmp<((*itrchild)->g))
					{
						//cout<<"D ";
						(*itrchild)->g=gtmp;
						(*itrchild)->f=gtmp+(*itrchild)->h;
						(*itrchild)->parentState=currentState;
						
						//~ for(int a=0; a<3; a++)
						//~ {
							//~ for(int b=0; b<3; b++) printf("%d ", (*itrchild)->posVal[a][b]);
							//~ printf("\n");	
						//~ }
						//~ cout<<((*itrchild)->g)<<" U"<<endl;
					}
				}
			}
		}
		else
		{
			//cout<<"E\n";
			cout<<ClosedList.size()<<endl;
			currentState->Print_Path(currentState);
			return 1;
		}
		//cout<<"..............................................................\n";
	}
	return -1;
}

int main()
{
	UserState* initState=new UserState;
	UserState* goalState=new UserState;
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++) scanf("%d",&(initState->posVal[i][j]));
	}

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++) scanf("%d",&(goalState->posVal[i][j]));
	}
	
	if(AStarSearch(initState,goalState))	cout<<"the above path is the optimal path:\n"<<endl;
	else cout<<"path cannot be found:\n"<<endl;
}

