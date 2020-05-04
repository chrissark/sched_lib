#include "Schedule.h"
#include "TaskLib.h"
#include "pch.h"


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
			parent = p; // ��� ������ p ��������� ��������

			if (new_node->time < p->time)
			{
				left_child = p; // ���� ��������� ����, � �������� ������� ����� �������
				p = p->left;
			}
			else // ���� ����� �������, ��������� � ������ ���������
			{
				if (p->right_is_thread)
					break;
				else p = p->right;
			}

		}
		if (new_node->time < parent->time)
		{
			parent->left = new_node;
			//�������� ������ ��������, ������������ � ����� ���������
			new_node->right = parent;
			new_node->right_is_thread = true;
		}
		else
		{
			parent->right = new_node;
			parent->right_is_thread = false;
			if (left_child)
			{
				// �������� ��������, ������������ � ������ ���������
				// ��� �������, ��� ������ ������ � ����� ��������
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


// ����� �����
void Schedule::show(Node* p) const
{
	if (is_empty())
		return;
	//���������� �� ����� ���������� �� ���. ��������
	while (p->left)
	{
		p = p->left;
	}
	//������ �� ��������, ���� ��� �� ��������
	while (p)
	{
		print_node(p);
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


//���������� �������
void Schedule::execute_task()
{
	Node* p = root;
	Node* parent = p;

	if (is_empty())
		return;

	//���� ������� � ���������� ������
	while (p->left)
	{
		parent = p;
		p = p->left;
	}
	// ��������� �������
	// ���� ��������� true, ������ ������� ������������� --> ������ ���� ��������� � ������ ��������
	if (p->task->exec())
	{
		add_node(p->task, p->task->get_deadline());
	}
	//�������� ������� �� ������
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

void Schedule::print_node(Node* p) const
{
	p->task->print();
	printf("Execution time: %i\n", p->time);
	if (p->right_is_thread)
		printf("Right is thread\n");
	printf("\n\n");
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

Schedule::~Schedule()
{
	deleteSchedule(root);
}


extern "C"
{
	Schedule* createSchedule()
	{
		return new Schedule();
	}
	void printSchedule(Schedule* S)
	{
		return S->print_Schedule();
	}
	bool is_empty(Schedule* S)
	{
		return S->is_empty();
	}
	void execute_task(Schedule* S)
	{
		return S->execute_task();
	}
	void deleteSchedule(Schedule* S)
	{
		delete S;
	}
	void add_node(Task* t, int time, Schedule* S)
	{
		return S->add_node(t, time);
	}
}
