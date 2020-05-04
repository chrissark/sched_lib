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

//�����������
class Scheduler {
	// ����� �������
	// ��� ���������� ������� �� ��������� ����������� �� ����������� ������ ��������
	multimap<int, shared_ptr<Task> > set;
public:
	Scheduler() { };
	void add_task(Task* t) // �������� ������� � �����������
	{
		set.insert(std::make_pair(t->get_importance(), shared_ptr<Task>(t)));
	}

	Schedule* make_schedule() const // ��������� ���������� �� ������ �������
	{
		int N = set.size();
		vector<int> d;
		vector<int> exec_time; // ��� �������� ������ ����������� ����������
		//multimap<int, Task*> test;
		d.resize(N);
		int k = 0;
		int d_max = 0;
		// ������� ����� ������� � �������� ������� (�� �������� �������� ��� ���������� ������ ������� ���������)
		// ��������� ������ ������ ���������� � ���� � ��� ������������ �������
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
