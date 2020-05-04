#pragma once
#include "Task.h"
#include "PeriodicTask.h"
#include "Scheduler.h"
#include "Schedule.h"


#ifdef PROJECT_EXPORTS
#define PROJECT_API __declspec(dllexport)
#else
#define PROJECT_API __declspec(dllimport)
#endif


extern "C"
{
	PROJECT_API Task* createTask(char* id, char* text, int deadline, int importance);
	PROJECT_API int get_deadline(Task* t);
	PROJECT_API int get_importance(Task* t);
	PROJECT_API void printTask(Task* t);
	PROJECT_API bool extend_deadline(Task* t, int dt);
	PROJECT_API bool change_level(Task* t, int lvl);
	PROJECT_API bool execReg(Task* t);
	PROJECT_API PeriodicTask* createPeriodicTask(char* id, char* text, int deadline, int importance, int period);
	PROJECT_API int get_period(PeriodicTask* t);
	PROJECT_API void skip_task(PeriodicTask* t);
	PROJECT_API void printPeriodicTask(PeriodicTask* t);
	PROJECT_API bool execPeriodic(PeriodicTask* t);
	PROJECT_API Scheduler* createScheduler();
	PROJECT_API void add_task(Task* t, Scheduler* S);
	PROJECT_API Schedule* make_Schedule(Scheduler* S);
	PROJECT_API Schedule* createSchedule();
	PROJECT_API void add_node(Task* t, int time, Schedule* S);
	PROJECT_API void printSchedule(Schedule* S);
	PROJECT_API bool is_empty(Schedule* S);
	PROJECT_API void execute_task(Schedule* S);
	PROJECT_API void deleteSchedule(Schedule* S);
	PROJECT_API void deleteTask(Task* t);
	PROJECT_API void deletePeriodicTask(PeriodicTask* t);
	PROJECT_API void deleteScheduler(Scheduler* S);











}