

#include <string>
#include <cstring>
#include <cstdio>
#include "pch.h"
#include "TaskLib.h"

extern "C"
{
	Scheduler* createScheduler()
	{
		return new Scheduler();
	}
	void add_task(Task* t, Scheduler* S)
	{
		return S->add_task(t);
	}
	Schedule* make_Schedule(Scheduler* S)
	{
		return S->make_schedule();
	}

	void deleteScheduler(Scheduler* S)
	{
		delete S;
	}

	Task* get_task(Scheduler* S, int num)
	{
		return S->get_task(num);
	}

	int get_list_size(Scheduler* S)
	{
		return S->get_list_size();
	}

}