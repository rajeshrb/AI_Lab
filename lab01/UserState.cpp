#include "UserState.hpp"

using namespace std;

int UserState::heuristic_Estimate(UserState* goalState)
{
	int manHattan_dist=0;
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(goalState->posVal[i][j])
			{
				for(int a=0; a<3; a++)
				{
					for(int b=0; b<3; b++)
					{
						if(goalState->posVal[i][j]==this->posVal[a][b])
						{
							manHattan_dist+=abs(i-a)+abs(j-b);
							a=3;
							break;
						}
					}
				}
			}
		}
	}
	return manHattan_dist;
}

int UserState::Dist_Between_parentAndChild()
{
	return 1;
}

void UserState::getChildState(vector<UserState* >& childStates)
{
	int i, j;
	for(i=0; i<3; i++)
	{ 
		for(j=0; j<3; j++)
		{
			if(this->posVal[i][j]==0)
			{
				if(i+1<3)
				{
					UserState* Child=new UserState;
					
					for(int a=0; a<3; a++)
						for(int b=0; b<3; b++)
							Child->posVal[a][b]=this->posVal[a][b];
					
					Child->posVal[i][j]=this->posVal[i+1][j];
					Child->posVal[i+1][j]=0;
					childStates.push_back(Child);
				}
				
				if(i-1>-1)
				{
					UserState* Child=new UserState;
					
					for(int a=0; a<3; a++)
						for(int b=0; b<3; b++)
							Child->posVal[a][b]=this->posVal[a][b];

					Child->posVal[i][j]=this->posVal[i-1][j];
					Child->posVal[i-1][j]=0;
					childStates.push_back(Child);
				}

				if(j+1<3)
				{
					UserState* Child=new UserState;
					
					for(int a=0; a<3; a++)
						for(int b=0; b<3; b++)
							Child->posVal[a][b]=this->posVal[a][b];

					Child->posVal[i][j]=this->posVal[i][j+1];
					Child->posVal[i][j+1]=0;
					childStates.push_back(Child);
				}

				if(j-1>-1)
				{
					UserState* Child=new UserState;
					
					for(int a=0; a<3; a++)
						for(int b=0; b<3; b++)
							Child->posVal[a][b]=this->posVal[a][b];

					Child->posVal[i][j]=this->posVal[i][j-1];
					Child->posVal[i][j-1]=0;
					childStates.push_back(Child);
				}
				return ;		
			}
		}
	}
}

bool UserState::isGoalState(UserState* goalState)
{
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			if(this->posVal[i][j]!=goalState->posVal[i][j]) return false;

	return true; 
}

bool UserState::Not_in_ClosedList(vector<UserState* >& closedList)
{
	int totalClosedState=closedList.size();
	for(int i=0; i<totalClosedState; i++)
	{
		bool found=1;
		for(int a=0; a<3; a++)
		{
			for(int b=0; b<3; b++)
			{
				found=((closedList[i]->posVal[a][b]==this->posVal[a][b]) && found);
			}
			if(!found) break; 
		}
		if(found) return false;
	}

	return true;
}

list<UserState* >::iterator UserState::Not_in_OpenList(list<UserState* >& openList)
{
	list<UserState* >::iterator it=openList.begin(), itr=openList.end();
	
	while(it!=itr)
	{
		bool found=1;
		for(int a=0; a<3; a++)
		{
			for(int b=0; b<3; b++)
			{
				found=(((*it)->posVal[a][b]==this->posVal[a][b]) && found);
			}
			if(!found) break; 
		}	
		if(found) return it;
		it++;
	}

	return itr;
}

void UserState::Print_Path(UserState* goalState)
{
	if(goalState==NULL) return ;
	else
	{
		Print_Path(goalState->parentState);
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				printf("%d ", goalState->posVal[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
}

//~ int main()
//~ {
	//~ UserState* k=new UserState; 
	//~ cout<<k->Dist_Between_parentAndChild()<<endl;
	//~ cout<<"success"<<endl;
//~ }