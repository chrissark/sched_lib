#pragma once

#include <string>
#include <cstring>
#include <cstdio>
#include "pch.h"
#include "TaskLib.h"



extern "C"
{
	Task* createTask(char* id, char* text, int deadline, int importance)
	{
		return new Task(id, text, deadline, importance);
	}

	int get_deadline(Task* t)
	{
		return t->get_deadline();
	}

	int get_importance(Task* t)
	{
		return t->get_importance();
	}

	int get_period(Task* t)
	{
		return t->get_period();
	}

	void get_id(Task* t, char* name, int max_name_len)
	{
		strncpy_s(name, max_name_len, t->get_id().c_str(),  t->get_id().length());
	}

	void get_text(Task* t, char* name, int max_name_len)
	{
		strncpy_s(name, max_name_len, t->get_text().c_str(), t->get_id().length());
	}

	bool extend_deadline(Task* t, int dt)
	{
		return t->extend_deadline(dt);
	}

	bool change_level(Task* t, int lvl)
	{
		return t->change_level(lvl);
	}

	bool execReg(Task* t)
	{
		return t->exec();
	}

	void deleteTask(Task* t)
	{
		delete t;
	}

	void printTask(Task* t)
	{
		t->print();
	}


}
