#pragma once
#include <string>
#include "Task.h"
using std::string;

//������� ��� �������������� ����������
class PeriodicTask : public Task {
	// ���� deadline - ����� ���������� ����������
	int period; // ����� ������ ����� ���������������� ������������
public:

	PeriodicTask(const string& id, const string& text, int deadline, int importance, int period)
		:Task(id, text, deadline, importance), period(period) {}

	int get_period() const
	{
		return period;
	};

	void skip_task() // ������� ���������� ���������� �������
	{
		extend_deadline(period);
	}

	virtual void print() const // ������ ���������� � ������������� �������
	{
		this->Task::print();
		printf("Period: %i\n", period);
	}

	bool exec()
	{
		this->print();
		printf("Executed.\n\n");
		this->skip_task();
		return true;
	}
};
