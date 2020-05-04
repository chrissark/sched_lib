#pragma once
#include <string>
#include <memory>
#include "PeriodicTask.h"
#include "Task.h"
using std::string;

// ���� (�������� ������, �������� �� ����������� �����)
class Schedule {
	// ���� ��������� ������
	typedef struct Node {
		Task* task;
		int time; // ����������� ����� ����������
		Node* left, * right;
		bool right_is_thread; // ������� ��������� ��� ��������� ��������
	}Node;
	Node* root;
public:
	Schedule() :
		root(nullptr) { };
	void add_node(Task* t, int time);
	void print_node(Node* p) const;
	void print_Schedule() const; // ������� ���� (��� ������������)
	void show(Node* p) const; // ������� ����
	void execute_task(); //��������� ������� 
	bool is_empty() const; //�������� �� ��, ���� �� � ����� �������
	void deleteSchedule(Node* p);
	~Schedule();

};


