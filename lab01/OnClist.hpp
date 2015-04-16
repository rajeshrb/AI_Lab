#include "UserStateImprove.hpp"
#include <unordered_map>
#include <set>

using namespace std;

class Compare
{
	public:
		bool operator()(UserState* X, UserState* Y)
		{
			if(X->f==Y->f) return X->h<=Y->h;
			else return X->f<=Y->f;
		}
};

#define UMap unordered_map<string,UserState*>
#define SS set<UserState*,Compare>
#define mk make_pair
#define ff first
#define ss second
#define in insert

class OpenSet
{
	SS bheap;
	UMap	usmap;
	
	public:
		int Find(UserState* ustate);
		UserState* Min();
		void Insert(UserState* ustate);
		bool Empty();
		void Erase(UserState* ustate);
};

class ClosedSet
{
	UMap	usmap;
	public:
		int Find(UserState* ustate);
		void Insert(UserState* ustate);
		void Erase(UserState* ustate);
		int Size();
};
