#pragma once
#include <cstring>
#include <string>
#include <stdio.h>
#include <iostream>

using std::string;
using std::cout;



// задание с кратким сроком
class Task {
	string id; // строковый идентификатор задания
	string text; // текст задания
	int importance; // уровень важности
	int deadline; // крайний срок исполнения
public:
	// создание задания
	Task(const string& id, const string& text, int deadline, int importance) :
		deadline(deadline), importance(importance), id(id), text(text) {};
	bool extend_deadline(int dt) // продление срока исполнения
	{
		if (dt > 0)
		{
			deadline += dt;
			return true;
		}
		else return false;

	}
	bool change_level(int lvl) //изменение уровня важности задания
	{
		if (lvl > 0)
		{
			importance = lvl;
			return true;
		}
		else
			return false;
	}
	virtual void print() const // печать информации о задании
	{
		cout<<"------\n";
		cout<<id<<text<<deadline<<importance;
		cout<<"------\n";
	}

	int get_deadline() const
	{
		return deadline;
	}
	int get_importance() const
	{
		return importance;
	}

	virtual int get_period() const
	{
		return 0;
	}

	const string& get_text() const
	{
		return text;
	}

	const string& get_id() const
	{
		return id;
	}

	virtual bool exec() // выполнить задание
	{
		this->print();
		printf("Executed.\n\n");
		return false;
	}


	virtual ~Task() {};
};
