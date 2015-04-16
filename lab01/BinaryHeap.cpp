#include "BinaryHeap.hpp"

using namespace std;

UserState* BHeap::Min()
{
	return this->bheap[0];
}

void BHeap::Insert(UserState* ustate)
{
	int k=this->bheap.sz();
	this->bheap.pb(ustate);
	while(1)
	{
		if(k==0) return ;
		if(k&1)
		{			
			UserState* utemp=this->bheap[k];
			if(utemp->f<this->bheap[k>>1]->f)
			{
				this->bheap[k]=this->bheap[k>>1];
				this->bheap[k>>1]=utemp;
				k>>=1;
			}
			else return ;
		}
		else
		{
			UserState* utemp=this->bheap[k];
			if(utemp->f<this->bheap[(k-1)>>1]->f)
			{
				this->bheap[k]=this->bheap[(k-1)>>1];
				this->bheap[(k-1)>>1]=utemp;
				k--;
				k>>=1;
			}
			else return ;
		}
	}
}

void BHeap::Erase()
{
	this->bheap[0]=this->bheap.bk();
	this->bheap.dl(this->bheap.bg());
	int k=0, s=this->bheap.sz();
	while(1)
	{
		int stemp=s*2;
		if(stemp>=k || stemp+1>=k) return ;
		if(this->bheap[stemp]->f<=this->bheap[stemp+1]->f)
		{
			if(this->bheap[s]->f<=this->bheap[stemp]->f) return ;
			UserState* utemp=this->bheap[s];
			this->bheap[s]=this->bheap[stemp];
			this->bheap[stemp]=utemp;
			s=stemp;
		}
		else
		{
			if(this->bheap[s]->f<=this->bheap[stemp+1]->f) return ;
			UserState* utemp=this->bheap[s];
			this->bheap[s]=this->bheap[stemp+1];
			this->bheap[stemp+1]=utemp;
			s=stemp+1;
		}
	}
	return ;			 
}