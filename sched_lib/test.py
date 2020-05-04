import ctypes

lib = ctypes.CDLL('./sched_lib.dll')

# Создание заданий
t = lib.createPeriodicTask('1', '2', 3, 4, 10)
t_2 = lib.createTask('3', '4', 2, 5)
t_3 = lib.createPeriodicTask('abc', 'edf', 5, 8, 3)

# Тест функций
d = lib.get_deadline(t)
d_1 = lib.get_importance(t)
d_2 = lib.get_period(t)
print(d, d_1, d_2)
lib.skip_task(t)
print(lib.get_deadline(t))

# Создание планировщика, добавление в него заданий
planner = lib.createScheduler()
lib.add_task(t, planner)
lib.add_task(t_2, planner)
lib.add_task(t_3, planner)

# Создание плана
plan = lib.make_Schedule(planner)

# Выполнение задания
lib.execute_task(plan)
lib.execute_task(plan)


# Удаление объектов
lib.deleteScheduler(planner)
lib.deleteSchedule(plan)

