#pragma once
#include <vector>
#include <map>
#include <memory>
#include "Task.h"
#include "PeriodicTask.h"
#include "Schedule.h"
using std::string;
using std::multimap;
using std::vector;
using std::shared_ptr;

//Планировщик
class Scheduler {
	// набор заданий
	// при добавлении заданий по умолчанию сортируется по возрастанию уровня важности
	multimap<int, shared_ptr<Task> > set;
public:
	Scheduler() { };
	void add_task(Task* t) // добавить задание в планировщик
	{
		set.insert(std::make_pair(t->get_importance(), shared_ptr<Task>(t)));
	}

	Task* get_task(int num) const
	{
		int k = 0;
		for (auto itr = set.rbegin(); itr != set.rend(); ++itr, k++)
		{
			if (itr != set.rend() && (k == num))
			return itr->second.get();
		}
	}

	int get_list_size() const
	{
		return set.size();
	}

	Schedule* make_schedule() const // составить расписание из набора заданий
	{
		int N = set.size();
		vector<int> d;
		vector<int> exec_time; // для хранения времен планируемых выполнений
		//multimap<int, Task*> test;
		d.resize(N);
		int k = 0;
		int d_max = 0;
		// обходим набор заданий в обратном порядке (по убыванию важности для корректной работы жадного алгоритма)
		// формируем массив сроков выполнения и ищем в нем максимальный элемент
		for (auto it = set.rbegin(); it != set.rend(); ++it, ++k)
		{
			d[k] = it->second->get_deadline();
			if (d_max < d[k])
				d_max = d[k];
		}
		exec_time.resize(d_max);
		for (int i = 0; i < N; i++)
		{
			k = d[i];
			while (k >= 1 && exec_time[k - 1])
				k--;
			if (k == 0)
				continue;
			exec_time[k - 1] = i + 1;
		}
		Schedule* S = new Schedule();
		k = 1;
		for (auto it = set.rbegin(); it != set.rend(); ++it, k++)
			for (int i = 0; i < d_max; i++)
			{
				if (exec_time[i] == k)
				{
					S->add_node((it->second).get(), i);
				}
			
			}
		return S;
	}

};
