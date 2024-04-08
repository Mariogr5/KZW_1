#include <iostream>
using namespace std;

class Task
{
	public:
		int prepare;
		int work;
		int end;
		int number_of_task;

		Task(int prepare, int work, int end, int number_of_task)
		{
			this->prepare = prepare;
			this->work = work;
			this->end = end;
			this->number_of_task = number_of_task;
		}
};