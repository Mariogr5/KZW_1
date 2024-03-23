﻿

#include <iostream>
#include <string>
#include <sstream>
#include "txtReader.cpp"
#include <algorithm>

using namespace std;

void show_vector(vector<Task>& tasks)
{
	for (int i = 0; i < tasks.size(); i++)
	{
		cout << tasks[i].prepare << " " << tasks[i].work << " " << tasks[i].end << endl;
	}
}

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

void sort_vector_by_end(vector<Task>& myVector, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j < n; j++)
		{
			if (myVector[j - 1].end < myVector[j].end)
				swap(myVector[j - 1], myVector[j]);
		}
	}
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

void sort_by_preparation(TxtReader &datas)
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

void get_time(TxtReader &datas)
{
	int counter = 0;

	vector<Task> tasks = datas._tasks;
	vector<int> end_times;
	show_vector(tasks);
	for (int i = 0; i < datas._counter; i++)
	{
		if (counter < tasks[i].prepare)
		{
			counter = tasks[i].prepare;
		}
		counter += tasks[i].work;
		//cout << "Counter : " << counter << "  ";
		end_times.push_back(counter + tasks[i].end);
		//cout << end_times[i] << endl;
	}
	int max_time = max_of_list(end_times, datas._counter);

	cout << "\nMAX TIME: " << max_time << endl;
}


vector<Task> sollution_1(TxtReader& datas) 
{
	// tasks must be sorted by R 
	vector<Task> avaliabeTask;
	vector <Task> order;

	sort_by_preparation(datas);
	vector<Task> tasks = datas._tasks;
	int time = tasks[0].prepare;

	//time = tasks[0].prepare + tasks[0].work;

	while (order.size() != datas._counter)
	{
		for (int i = 0; i < tasks.size(); i++)
		{
			if (tasks[i].prepare <= time)
			{
				avaliabeTask.push_back(tasks[i]);
				tasks.erase(tasks.begin() + i);
			}
		}
		if (avaliabeTask.size() != 0)
		{
			sort_vector_by_end(avaliabeTask, avaliabeTask.size());
			time += avaliabeTask[0].work;
			order.push_back(avaliabeTask[0]);
			avaliabeTask.erase(avaliabeTask.begin());
		}
		else
		{
			time = tasks[0].prepare;
		}
	}
	cout << endl << "Size: " << datas._tasks.size() << endl;
	cout << endl << "Size: " << order.size() << endl;
	return order;
}

int main()
{
	TxtReader reader2 = read_data("zadanie1.txt");
	sort_by_preparation(reader2);
	reader2._tasks = sollution_1(reader2);
	show_vector(reader2._tasks);
	get_time(reader2);
}

//Możliwe rozwiązania:
//Broadforce
//Tabu Search
//pamiętamy 10 ostatnich rozwiązań i szukamy najlepszy, otoczenie, pomijając rozwiązania już sprawdzone
//Znajdujemy rozwiązania po r i szukamy optymalnego 