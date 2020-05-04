#pragma once
#include <string>
#include <memory>
#include "PeriodicTask.h"
#include "Task.h"
using std::string;

// План (бинарное дерево, прошитое по возрастанию ключа)
class Schedule {
	// узел бинарного дерева
	typedef struct Node {
		Task* task;
		int time; // планируемое время исполнения
		Node* left, * right;
		bool right_is_thread; // обычный указатель или указатель прошивки
	}Node;
	Node* root;
public:
	Schedule() :
		root(nullptr) { };
	void add_node(Task* t, int time);
	void print_node(Node* p) const;
	void print_Schedule() const; // вывести план (для пользователя)
	void show(Node* p) const; // вывести план
	void execute_task(); //выполнить задание 
	bool is_empty() const; //проверка на то, есть ли в плане задания
	void deleteSchedule(Node* p);
	~Schedule();

};


