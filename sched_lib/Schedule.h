#pragma once
#include <string>
#include <memory>
#include "PeriodicTask.h"
#include "Task.h"
using std::string;

typedef struct Node {
	Task* task;
	int time; // планируемое время исполнения
	Node* left, * right;
	bool right_is_thread; // обычный указатель или указатель прошивки
}Node;

// План (бинарное дерево, прошитое по возрастанию ключа)
class Schedule {
	// узел бинарного дерева
	Node* root;
public:
	Schedule() :
		root(nullptr) { };
	void add_node(Task* t, int time);
	void print_Schedule() const; // вывести план (для пользователя)
	void show(Node* p) const; // вывести план
	Task* execute_task(); //выполнить задание 

	Node* get_root() const;

	void delete_executed_task(Node *p, Node* parent);
	bool is_empty() const; //проверка на то, есть ли в плане задания
	void deleteSchedule(Node* p);
	~Schedule();

};


