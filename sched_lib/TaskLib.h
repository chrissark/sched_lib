#pragma once
#include "Task.h"
#include "PeriodicTask.h"
#include "Scheduler.h"
#include "Schedule.h"

/*
#ifdef PROJECT_EXPORTS
#define PROJECT_API __declspec(dllexport)
#else
#define PROJECT_API __declspec(dllimport)
#endif
*/

extern "C"
{
	__declspec(dllexport) Task* createTask(char* id, char* text, int deadline, int importance);
	__declspec(dllexport) int get_deadline(Task* t);
	__declspec(dllexport) int get_importance(Task* t);
	__declspec(dllexport) bool extend_deadline(Task* t, int dt);
	__declspec(dllexport) bool change_level(Task* t, int lvl);
	__declspec(dllexport) bool execReg(Task* t);
	__declspec(dllexport) PeriodicTask* createPeriodicTask(char* id, char* text, int deadline, int importance, int period);
	__declspec(dllexport) int get_period(Task* t);
	__declspec(dllexport) void skip_task(PeriodicTask* t);
	__declspec(dllexport) bool execPeriodic(PeriodicTask* t);
	__declspec(dllexport) Scheduler* createScheduler();
	__declspec(dllexport) void add_task(Task* t, Scheduler* S);
	__declspec(dllexport) Schedule* make_Schedule(Scheduler* S);
	__declspec(dllexport) bool is_empty(Schedule* S);
	__declspec(dllexport) Task* execute_task(Schedule* S);

	__declspec(dllexport) void deleteSchedule(Schedule* S);
	__declspec(dllexport) void deleteTask(Task* t);
	__declspec(dllexport) void deletePeriodicTask(PeriodicTask* t);
	__declspec(dllexport) void deleteScheduler(Scheduler* S);

	__declspec(dllexport) Node* get_root(Schedule* S);
	__declspec(dllexport) Node* get_right(Node* p);
	__declspec(dllexport) Node* get_left(Node* p);
	__declspec(dllexport) Task* get_task_from_node(Node* p);
	__declspec(dllexport) int get_exec_time(Node* p);
	__declspec(dllexport) bool right_is_thread(Node* p);

	__declspec(dllexport) void get_text(Task* t, char* name, int max_name_len);
	__declspec(dllexport) void get_id(Task* t, char* name, int max_name_len);
	__declspec(dllexport) Task* get_task(Scheduler* S, int num);
	__declspec(dllexport) int get_list_size(Scheduler* S);











}