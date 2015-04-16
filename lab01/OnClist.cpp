#include "OnClist.hpp"

using namespace std;

int OpenSet::Find(UserState* ustate)
{
	string str=ustate->Int_To_String();
	ITR(UMap) itr=this->usmap.find(str), itrend=this->usmap.en();
	if(itr==itrend) return 0;
	return itr->ss->g;
}

UserState* OpenSet::Min()
{
	UserState* utemp=*(this->bheap.bg());
	this->bheap.dl(this->bheap.bg());
	return utemp;
}

void OpenSet::Insert(UserState* ustate)
{
	string str=ustate->Int_To_String();
	this->usmap.in(mk(str,ustate));
	this->bheap.in(ustate);
	return ;
}

bool OpenSet::Empty()
{
	return this->usmap.empty();
}

void OpenSet::Erase(UserState* ustate)
{
	string str=ustate->Int_To_String();
	this->usmap.dl(str);
	return ;
}

int ClosedSet::Find(UserState* ustate)
{
	string str=ustate->Int_To_String();
	ITR(UMap) itr=this->usmap.find(str), itrend=this->usmap.en();
	if(itr==itrend) return 0;
	return itr->ss->g;
}

void ClosedSet::Insert(UserState* ustate)
{
	string str=ustate->Int_To_String();
	this->usmap.in(mk(str,ustate));
	return ;
}

void ClosedSet::Erase(UserState* ustate)
{
	string str=ustate->Int_To_String();
	this->usmap.dl(str);
	return ;
}

int ClosedSet::Size()
{
	return this->usmap.sz();
}