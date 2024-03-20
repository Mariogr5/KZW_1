#include <iostream>
using namespace std;

class Task
{
	public:
		int prepare;
		int work;
		int end;

		Task(int prepare, int work, int end)
		{
			this->prepare = prepare;
			this->work = work;
			this->end = end;
		}
};