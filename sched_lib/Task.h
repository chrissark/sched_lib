#pragma once
#include <cstring>
#include <string>
#include <stdio.h>

using std::string;



// ������� � ������� ������
class Task {
	string id; // ��������� ������������� �������
	string text; // ����� �������
	int importance; // ������� ��������
	int deadline; // ������� ���� ����������
public:
	// �������� �������
	Task(const string& id, const string& text, int deadline, int importance) :
		deadline(deadline), importance(importance), id(id), text(text) {};
	bool extend_deadline(int dt) // ��������� ����� ����������
	{
		if (dt > 0)
		{
			deadline += dt;
			return true;
		}
		else return false;

	}
	bool change_level(int lvl) //��������� ������ �������� �������
	{
		if (lvl > 0)
		{
			importance = lvl;
			return true;
		}
		else
			return false;
	}
	virtual void print() const // ������ ���������� � �������
	{
		printf("------\n");
		printf("ID: %s\nText: %s\ndeadline - %ds, importance level - %d \n", id.c_str(), text.c_str(), deadline, importance);
		printf("------\n");
	}

	int get_deadline() const
	{
		return deadline;
	}
	int get_importance() const
	{
		return importance;
	}
	virtual bool exec() // ��������� �������
	{
		this->print();
		printf("Executed.\n\n");
		return false;
	}


	virtual ~Task() {};
};
