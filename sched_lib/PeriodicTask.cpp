#pragma once

#include <string>
#include <cstring>
#include <cstdio>
#include "pch.h"
#include "TaskLib.h"

extern "C"
{
	PeriodicTask* createPeriodicTask(char* id, char* text, int deadline, int importance, int period)
	{
		return new PeriodicTask(id, text, deadline, importance, period);
	}

	int get_period(PeriodicTask* t)
	{
		return t->get_period();
	}

	void skip_task(PeriodicTask* t)
	{
		return t->skip_task();
	}

	void printPeriodicTask(PeriodicTask* t)
	{
		return t->print();
	}

	bool execPeriodic(PeriodicTask* t)
	{
		return t->exec();
	}

	void deletePeriodicTask(PeriodicTask* t)
	{
		delete t;
	}
}