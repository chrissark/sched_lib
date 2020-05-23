import ctypes

lib = ctypes.CDLL('./sched_lib.dll')



# вывод плана
def show_schedule(schedule):
    if (lib.is_empty(schedule) == True):
        print("No tasks in schedule.")
        return 
    print("---------SCHEDULE---------")
    show(lib.get_root(schedule))
    print("--------------------------")
    


def show(node):
        #спускаемся по левым указателям до мин. элемента
        while (lib.get_left(node)):
            node = lib.get_left(node)

        #проход по прошивке и печать элементов
        while (node):
            task = lib.get_task_from_node(node)
            time = lib.get_exec_time(node)
            print_info(task)
            print("Execution time:", time)
            print("\n")
            
            if (lib.right_is_thread(node)):
                node = lib.get_right(node)
            else:
                break
            
        if (not node):
            return
        if (lib.get_right(node)):
            show(lib.get_right(node))
            

# сделать шаг (выполнить задание из плана)
def run_exec(schedule):
    t = lib.execute_task(schedule)
    if (t):
        print_info(t)
        print("Executed.")
    else:
        print("Error: schedule is empty.")
    

    
# вывод списка заданий из планировщика
def show_list(scheduler):
    length = lib.get_list_size(scheduler)
    for i in range(length):
        print(i + 1)
        print_info(lib.get_task(scheduler, i))
    
# печать информации о задании
def print_info(task):
    task_id = ctypes.create_string_buffer(100)
    task_text = ctypes.create_string_buffer(500)   
    lib.get_id.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_size_t]
    lib.get_id(task, task_id, ctypes.sizeof(task_id))
    lib.get_text.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_size_t]
    lib.get_text(task, task_text, ctypes.sizeof(task_text))
    period = lib.get_period(task)
    
    print("ID:", task_id.value.decode('utf-8'))
    print("Text:", task_text.value.decode('utf-8'))
    print("Deadline:",lib.get_deadline(task))
    print("Importance level:", lib.get_importance(task))
    if (period == 0):
        pass
    else:
        print("Period:", period)
    print("\n")
    

# добавить в планировщик задание
def add_to_sched(scheduler):
    data = [0] * 2
    print("Enter task ID: ")
    data_id = input()
    print("Enter text of task: ")
    data_text = input()
    try:
        print("Enter deadline (number of seconds): ")
        data[0] = int(input())
        print("Enter importance level (integer - the greater the value, the more important the task): ")
        data[1] = int(input())
    except:
        print("Error: invalid number entered.")
        return
    try:
        name = ctypes.c_char_p(data_id.encode('utf-8'))
        text = ctypes.c_char_p(data_text.encode('utf-8'))
        t = lib.createTask(name, text, data[0], data[1])
        lib.add_task(t, scheduler)
    except:
        print("Error.")

# добавить в планировщик периодическое задание
def add_periodic_to_sched(scheduler):
    data = [0] * 3
    print("Enter task ID: ")
    data_id = input()
    print("Enter text of task: ")
    data_text = input()
    try:
        print("Enter deadline (number of seconds): ")
        data[0] = int(input())
        print("Enter importance level (integer - the greater the value, the more important the task): ")
        data[1] = int(input())
        print("Enter period (number of seconds): ")
        data[2] = int(input())
    except:
        print("Error: invalid number entered.")
        return
    try:
        name = ctypes.c_char_p(data_id.encode('utf-8'))
        text = ctypes.c_char_p(data_text.encode('utf-8'))
        t = lib.createPeriodicTask(name, text, data[0], data[1], data[2])
        lib.add_task(t, scheduler)
    except:
        print("Error.")
        
    
def menu(scheduler):

    sched_flag = False
    
    while True:
    
         print("Choose an action:")
         print("1.Add task")
         print("2.Add periodic task")
         print("3.Show list of tasks")
         print("4.Clear list")
         print("5.Make schedule")
         print("6.Show schedule")
         print("7.Run execution")
         print("8.Delete schedule")
         print("0.Exit")
    
         try:
           choice = int(input())
         except:
            print("Error: invalid number entered.")
            continue
    
         if (choice == 1):
            add_to_sched(scheduler)
        
         elif (choice == 2):
            add_periodic_to_sched(scheduler)

         elif (choice == 3):
            show_list(scheduler)

         elif (choice == 4):
             lib.deleteScheduler(scheduler)
             scheduler = lib.createScheduler()
             print("List is cleared.")
        
         elif (choice == 5):
            if (sched_flag == False):
                schedule = lib.make_Schedule(scheduler)
                sched_flag = True
                print("Schedule is ready.")
            else:
                print("Error: schedule already exists.")

         elif (choice == 6):
            if (sched_flag == True):
                show_schedule(schedule)
            else:
                print("Error: no schedule exists.")
                
                
         elif (choice == 7):
            if (sched_flag == True):
                run_exec(schedule)
            else:
                print("Error: no schedule exists.")

            
         elif (choice == 8):
            if (sched_flag == True):                
               lib.deleteSchedule(schedule)
               print("Deleted.")
               sched_flag = False
            else:
               print("Error: no schedule exists.")

        
         elif (choice == 0):
            lib.deleteScheduler(scheduler)
            if (sched_flag == True):
                lib.deleteSchedule(schedule)
            break
         else:
            print("Error: no such action.")



scheduler = lib.createScheduler()    
menu(scheduler)    
    
    
