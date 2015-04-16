#include <stdlib.h>
#include <vector>
#include <iostream>
#include <list>
#include <cmath>
#include <stdio.h>

using namespace std;

class UserState
{
	public:
		int posVal[3][3];
		UserState* parentState;
		int f, g, h;
		int heuristic_Estimate(UserState* goalState);
		int Dist_Between_parentAndChild();
		void getChildState(vector<UserState* >& childStates);
		bool isGoalState(UserState* goalState);
		list<UserState* >::iterator Not_in_OpenList(list<UserState* >& openList);
		bool Not_in_ClosedList(vector<UserState* >& closedList);
		void Print_Path(UserState* goalState);
};

