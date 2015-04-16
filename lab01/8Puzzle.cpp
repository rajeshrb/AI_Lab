#include "UserStateImprove.hpp"

using namespace std;

int UserState::Manhattan(UserState goal_state)
{
	int md=0;
	for(int i=0; i<DIMENTION; i++) 
		md+=abs(goal_state.state_val[i].x-this->state_val[i].x)+abs(goal_state.state_val[i].y-this->state_val[i].y);
	return md;
}

int UserState::Displaced_Tiles(UserState goal_state)
{
	int dt=0;
	for(int i=0; i<DIMENTION; i++)
		if(goal_state.state_val[i].x!=this->state_val[i].x) dt++;
		else if(goal_state.state_val[i].y!=this->state_val[i].y) dt++;
	return dt;
}

int UserState::Own(UserState goal_state)
{
	int own=0;
	for(int i=0; i<DIMENTION; i++)
	{ 
		int X, Y;
		X=goal_state.state_val[i].x-this->state_val[i].x;
		Y=goal_state.state_val[i].y-this->state_val[i].y;
		own+=sqrt(X*X+Y*Y);
	}
	return own;
}

int UserState::Overestimated(UserState goal_state)
{
	return Manhattan(goal_state)+Own(goal_state);
}

int UserState::Zeroh()
{
	return 0;
}

int UserState::Heuristic_Estimate(UserState goal_state, int hn)
{
	switch(hn)
	{
		case 0:
			return Manhattan(goal_state);
		case 1:
			return Displaced_Tiles(goal_state);
		case 2:
			return Own(goal_state);
		case 3:
			return Overestimated(goal_state);
		case 4:
			return Zeroh();
	}			
}	

string UserState::Int_To_String()
{
	char pos[SQDIMENTION][SQDIMENTION];
	for(int i=0; i<DIMENTION; i++)
		pos[this->state_val[i].x][this->state_val[i].y]=i+'0';
	
	string str="";
	for(int i=0; i<SQDIMENTION; i++)
		for(int j=0; j<SQDIMENTION; j++) str=str+pos[i][j];
	return str;
}

UserState UserState::Create_Child(int indx)
{
	UserState ustemp;
	for(int i=0; i<DIMENTION; i++)
	{
		ustemp.state_val[i].x=this->state_val[i].x;
		ustemp.state_val[i].y=this->state_val[i].y;
	}			
	
	int xtemp=ustemp.state_val[0].x, ytemp=ustemp.state_val[0].y;
	
	ustemp.state_val[0].x=ustemp.state_val[indx].x;
	ustemp.state_val[0].y=ustemp.state_val[indx].y;
	ustemp.state_val[indx].x=xtemp;
	ustemp.state_val[indx].y=ytemp;

	return ustemp;
}

int UserState::Dist_Between_Parent_Child()
{
	return 1;
}

void UserState::Get_Child_State(vector<UserState>& child_states)
{
	int A[4];
	for(int i=0; i<DIMENTION; i++)
	{
		if(this->state_val[i].y==this->state_val[0].y)
		{
			if(this->state_val[i].x==this->state_val[0].x-1) A[0]=i;
			else if(this->state_val[i].x==this->state_val[0].x+1) A[1]=i;
		}
		else if(this->state_val[i].x==this->state_val[0].x)
		{
			if(this->state_val[i].y==this->state_val[0].y+1) A[3]=i;
			else if(this->state_val[i].y==this->state_val[0].y-1) A[2]=i;
		}
	}
	
	if(this->state_val[0].x-1>-1) child_states.pb(Create_Child(A[0]));
	if(this->state_val[0].x+1<SQDIMENTION) child_states.pb(Create_Child(A[1]));	
	if(this->state_val[0].y-1>-1) child_states.pb(Create_Child(A[2]));
	if(this->state_val[0].y+1<SQDIMENTION) child_states.pb(Create_Child(A[3]));	
}

bool UserState::Is_Goal_State(UserState goal_state)
{
	for(int i=0; i<DIMENTION; i++)
	{	
		if(goal_state.state_val[i].x!=this->state_val[i].x) return false;
		else if(goal_state.state_val[i].y!=this->state_val[i].y) return false;
	}
	return true;
}

void UserState::Print_Path(UserState* goal_state)
{
	int pos[SQDIMENTION][SQDIMENTION];
	for(int i=0; i<DIMENTION; i++) pos[goal_state->state_val[i].x][goal_state->state_val[i].y]=i;
	
	if(goal_state->parent_state==NULL)
	{
		for(int i=0; i<SQDIMENTION; i++)
		{
			for(int j=0; j<SQDIMENTION; i++)
				printf("%d ",pos[i][j]);
			printf("\n");
		}
		return ;
	}
	else
	{
		Print_Path(goal_state->parent_state);
		for(int i=0; i<SQDIMENTION; i++)
		{
			for(int j=0; j<SQDIMENTION; i++)
				printf("%d ",pos[i][j]);
			printf("\n");
		}
		return ;
	}
}