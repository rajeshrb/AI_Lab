
using namespace std;

class BHeap
{
	vector<UserState*> bheap;
	public:
		UserState* Min();
		void Insert(UserState* elem);
		void Erase();		
};
