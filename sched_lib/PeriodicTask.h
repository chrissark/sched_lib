#pragma once
#include <string>
#include "Task.h"
using std::string;

//задания для периодического выполнения
class PeriodicTask : public Task {
	// поле deadline - метка ближайшего выполнения
	int period; // число секунд между запланированными исполнениями
public:

	PeriodicTask(const string& id, const string& text, int deadline, int importance, int period)
		:Task(id, text, deadline, importance), period(period) {}

	int get_period() const
	{
		return period;
	};

	void skip_task() // пропуск очередного выполнения задания
	{
		extend_deadline(period);
	}

	virtual void print() const // печать информации о периодическом задании
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
