#include <iostream>
#include <vector>
#include <priority_queue>
#include <list>
#include <cmath>


using namespace std;

class State
{
	state* parent;
	int numberOfdisplaced, manhattanDist, f, g, positionOfdigit[3][3];
	
	int HeuristicOne();
	{
		int sumOfTiles =0;
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				if((3*i+j)!=positionOfdigit[i][j]) sumOfTiles++;
			}
		}
		return sumOfTiles-1;
	}

	int HeuristicTwo();
	{
		int sumOfDisplaced=0, xposition, yposition;
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				int digitVal=positionOfdigit[i][j];
				xpos = digitVal/3;
				ypos = digitVal%3;
				sumOfDisplaced+=abs(xposition-i) + abs(yposition - j);
			}
		}
		return sumOfDisplaced-1;	
	}
};

class compare
{
	public:
		bool operator()(state* X, state* Y)
		{
			return X->f>=Y->f;
		}
};

vector<state> getChild(state* current_state)
{
	int i, j;
	vector<state> Child;
	for(i=0; i<3; i++)
	{
		bool found=false; 
		for(j=0; j<3; j++)
		{
			if(current_state->position[i][j]==8)
			{
				if(i+1<3)
				{
					state Child1;
					for(int a=0; a<3; a++)
					{
						for(int b=0; b<3; b++)
						{
							Child1.position[a][b]=current_state->position[a][b];
						}
					}
					Child1.position[i][j]=current_state->position[i+1][j];
					Child1.position[i+1][j]=8;
					Child.push_back(Child1);
				}
				
				if(i-1>-1)
				{
					state Child1;
					for(int a=0; a<3; a++)
					{
						for(int b=0; b<3; b++)
						{
							Child1.position[a][b]=current_state->position[a][b];
						}
					}
					Child1.position[i][j]=current_state->position[i-1][j];
					Child1.position[i-1][j]=8;
					Child.push_back(Child1);
				}
				if(j+1<3)
				{
					state Child1;
					for(int a=0; a<3; a++)
					{
						for(int b=0; b<3; b++)
						{
							Child1.position[a][b]=current_state->position[a][b];
						}
					}
					Child1.position[i][j]=current_state->position[i][j+1];
					Child1.position[i][j+1]=8;
					Child.push_back(Child1);
				}
				if(j-1>-1)
				{
					state Child1;
					for(int a=0; a<3; a++)
					{
						for(int b=0; b<3; b++)
						{
							Child1.position[a][b]=current_state->position[a][b];
						}
					}
					Child1.position[i][j]=current_state->position[i][j-1];
					Child1.position[i][j-1]=8;
					Child.push_back(Child1);
				}
				found=true;
				break;			
			}
			
			if(found) break;
		}
	}
}

bool checkClosed(vector<state*> closedList, state* Child)
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			Child
		}
	}
}

int AstarSearch(state* initial, state* goal)
{
	vector<state*> closedList;
	priority_queue<state,vector<state>,compare> openList;

	initial.g=0;
	initial.manhattan=initial.mh();
	initial.f=initial.g+initial.manhattan;
	openList.push(*initial);

	while(!openList.empty())
	{
		state current_state=openList.top();
		vector<state> Child=getChild(current_state);
		for(int i=0; i<Child.size(); i++)
		{
			if()
		}
	}
}

int main()
{
	cout<<"enter the initial state:\n";
	state initial_state;
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			cin>>initial_state.position[i][j];
		}
	}
	
	initial_state.parent=null;

	cout<<"enter the final state:\n";
	state final_state;
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			cin>>final_state.position[i][j];
		}
	}
}