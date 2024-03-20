

#include <iostream>
#include <string>
#include <sstream>
#include "txtReader.cpp"
#include <algorithm>

using namespace std;


TxtReader read_data(string file_path)
{
	ifstream infile(file_path);

	vector<Task> file_tasks;

	if (!infile.is_open()) {
		cout << "Nie można otworzyć pliku." << endl;
		return TxtReader(0, 0, file_tasks);
	}
	else
		cout << "Poprawnie wczytano plik" <<endl;


	int iterator = 0;
	string line;
	while (getline(infile, line)) {
		istringstream iss(line);
		int a, b, c;
		if (!(iss >> a >> b >> c)) {
			break;
		}

		file_tasks.push_back(Task(a, b, c));

		//cout << a <<" "<< b << " " << c << endl;
		iterator++;

	}
	
	return TxtReader(1, iterator, file_tasks);
}


void sort_vector(vector<Task> &myVector, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j < n; j++)
		{
			if (myVector[j - 1].prepare > myVector[j].prepare)
				swap(myVector[j - 1], myVector[j]);
		}
	}

}

void sort_by_preparation(TxtReader datas)
{
	sort_vector(datas._tasks, datas._counter);
	
	cout << endl;
	for (int i = 0; i < datas._counter; i++)
	{
		cout << datas._tasks[i].prepare << " " << datas._tasks[i].work << " " << datas._tasks[i].end << endl;
	}
}


int max_of_list(vector<int> task, int lenght)
{
	int temp = 0;
	for (int i = 0; i < lenght; i++)
	{
		if (task[i] > temp)
			temp = task[i];
	}
	return temp;
}

void get_time(TxtReader datas)
{
	int counter = 0;

	vector<Task> tasks = datas._tasks;
	vector<int> end_times;

	for (int i = 0; i < datas._counter; i++)
	{
		if (counter < tasks[i].prepare)
		{
			counter = tasks[i].prepare;
			//tasks[i].prepare = tasks[i].prepare - counter;
		}
		counter += tasks[i].work;

		end_times.push_back(counter + tasks[i].end);
	}
	int max_time = max_of_list(end_times, datas._counter);

	cout << "\nMAX TIME: " << max_time << endl;
}




int main()
{
	TxtReader reader2 = read_data("zadanie1.txt");
	sort_by_preparation(reader2);
	get_time(reader2);
}

//Możliwe rozwiązania:
//Broadforce
//Tabu Search
//pamiętamy 10 ostatnich rozwiązań i szukamy najlepszy, otoczenie, pomijając rozwiązania już sprawdzone
//Znajdujemy rozwiązania po r i szukamy optymalnego 