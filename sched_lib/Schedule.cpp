#include "Schedule.h"
#include "TaskLib.h"
#include "pch.h"
#include <vector>

using std::vector;


void Schedule::add_node(Task* t, int time)
{
	if (!root)
	{
		root = new Node;
		root->task = t;
		root->time = time;
		root->left = root->right = nullptr;
		root->right_is_thread = false;
		return;
	}
	else
	{
		Node* new_node = new Node;
		new_node->task = t;
		new_node->time = time;
		new_node->left = new_node->right = nullptr;
		new_node->right_is_thread = false;
		Node* p = root;
		Node* parent = p;
		Node* left_child = nullptr;

		while (p)
		{
			parent = p; // при сдвиге p сохраняем родителя

			if (new_node->time < p->time)
			{
				left_child = p; // ищем последний узел, у которого имеется левый потомок
				p = p->left;
			}
			else // если ключи совпали, добавлеем в правое поддерево
			{
				if (p->right_is_thread)
					break;
				else p = p->right;
			}

		}
		if (new_node->time < parent->time)
		{
			parent->left = new_node;
			//прошивка вправо элемента, вставленного в левое поддерево
			new_node->right = parent;
			new_node->right_is_thread = true;
		}
		else
		{
			parent->right = new_node;
			parent->right_is_thread = false;
			if (left_child)
			{
				// прошивка элемента, вставленного в правое поддерево
				// при условии, что найден предок с левым потомком
				new_node->right = left_child;
				new_node->right_is_thread = true;
			}
		}

	}


}

void Schedule::print_Schedule() const
{
	printf("--------------- SCHEDULE ----------------\n\n");
	show(root);
	printf("-----------------------------------------\n\n");
}


// вывод плана
void Schedule::show(Node* p) const
{
	if (is_empty())
		return;
	//спускаемся по левым указателям до мин. элемента
	while (p->left)
	{
		p = p->left;
	}
	//проход по прошивке, пока она не кончится
	while (p)
	{
		//get_data(p);
		if (p->right_is_thread)
		{
			p = p->right;
		}
		else break;

	}
	if (!p)
	{
		return;
	}
	if (p->right)
	{
		show(p->right);
	}
}


//выполнение задания
Task* Schedule::execute_task()
{
	Node* p = root;
	Node* parent = p;

	if (is_empty())
		return nullptr;

	//ищем элемент с наименьшим ключом
	while (p->left)
	{
		parent = p;
		p = p->left;
	}
	// выполняем задание
	// если вернулось true, значит задание периодическое --> должно быть добавлено в дерево повторно
	if (p->task->exec())
	{
		add_node(p->task, p->task->get_deadline());
	}
	Task* ret = p->task;
	delete_executed_task(p, parent);
	return ret;

}

void Schedule::delete_executed_task(Node* p, Node* parent)
{
	//удаление задания из списка
	if (p->right_is_thread)
	{
		parent->left = nullptr;
		delete p;
	}
	else if (p == root)
	{
		root = p->right;
		delete p;
	}
	else
	{
		parent->left = p->right;
		delete p;
	}
}

bool Schedule::is_empty() const
{
	if (!root)
	{
		printf("No tasks in schedule.\n");
		return true;
	}
	else return false;
}


void Schedule::deleteSchedule(Node* p)
{
	if (p)
	{
		if (!p->right_is_thread)
			deleteSchedule(p->right);
		deleteSchedule(p->left);

		delete p;
	}
}

Node* Schedule::get_root() const
{
	return root;
}


Schedule::~Schedule()
{
	deleteSchedule(root);
}


extern "C"
{


	bool is_empty(Schedule* S)
	{
		return S->is_empty();
	}
	Task* execute_task(Schedule* S)
	{
		return S->execute_task();
	}

	Node* get_root(Schedule *S)
	{
		return S->get_root();
	}

	Node* get_left(Node* p)
	{
		return p->left;
	}

	Node* get_right(Node* p)
	{
		return p->right;
	}

	Task* get_task_from_node(Node* p)
	{
		return p->task;
	}

	int get_exec_time(Node* p)
	{
		return p->time;
	}

	bool right_is_thread(Node* p)
	{
		return p->right_is_thread;
	}

	void deleteSchedule(Schedule* S)
	{
		delete S;
	}
}
