#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string>

using namespace std;

#define VS vector<UserState>

#define ITR(x) x::iterator
#define DIMENTION 9
#define SQDIMENTION 3
#define pb push_back
#define bg begin
#define en end
#define sz size
#define bk back
#define dl erase

class Point
{
	public:
		int x,y;
};

class UserState
{
	/* different Heuristics */	
	int Manhattan(UserState goal_state);
	int Displaced_Tiles(UserState goal_state);
	int Own(UserState goal_state);
	int Overestimated(UserState goal_state);
	int Zeroh();
	public:
		int f, g, h;													/* heuristic veriables f(n)=g(n)+h(n) */ 
		UserState* parent_state;											/* for tracking the path */
		Point state_val[DIMENTION];   										/* state value */
		
		UserState Create_Child(int indx);
		int Heuristic_Estimate(UserState goal_state, int hn);				/* calculate heuristic */	
		int Dist_Between_Parent_Child();											/* give the distance btwn parent and child */				
		void Get_Child_State(vector<UserState>& child_states);		/* calculate all neighbours of this class */
		bool Is_Goal_State(UserState goal_state);							/*chaeck whether the this class is goal_state */
		void Print_Path(UserState* goal_state);							/* print the path from start_state to goal_state */
		string Int_To_String();
};