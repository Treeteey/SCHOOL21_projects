import threading
import time
import random

num_doctors = 5
# Index of the Doctor to the left and right
LEFT = lambda i: (i - 10 + num_doctors) % num_doctors + 9
RIGHT = lambda i: (i - 8) % num_doctors + 9

state = [0] * num_doctors  # 0 = thinking, 1 = hungry, 2 = blasting
# Класс Condition() модуля threading реализует объекты условий, которые позволяют
# одному или нескольким потокам ждать, пока они не будут уведомлены другим 
# потоком о его выполнении. Типичный пример использования условий это использование 
# блокировки для синхронизации доступа потоков к общему состоянию.
condition = [threading.Condition() for _ in range(num_doctors)]

def get_both_screwdrivers(id):
    left = LEFT(id)
    right = RIGHT(id)
    index = id - 9
    with condition[index]:
        state[index] = 1  # Hungry
        while state[index] == 1 and (state[left - 9] == 2 or state[right - 9] == 2):
            condition[index].wait()
            # print(f"Doctor {id}: Waiting...")
        # print(f"Doctor {id}: Got both screwdrivers!")
        if state[index] == 1:
            state[index] = 2  # Blasting

def blast(id):
    print(f"Doctor {id}: BLAST!")
    time.sleep(0.1) # Simulate some delay

def release_both_screwdrivers(id):
    left = LEFT(id)
    right = RIGHT(id)
    index = id - 9
    with condition[index]:
        state[index] = 0  # Thinking
        # Notify neighbors that resources are available
        with condition[left - 9]:
            condition[left - 9].notify_all()
        with condition[right - 9]:
            condition[right - 9].notify_all()
        # print(f"Doctor {id}: Released both screwdrivers!")

def doctor_thread(id):
    # print(f"Doctor {id}: Started")
    get_both_screwdrivers(id)  # Acquire resources
    blast(id)                  # Perform the action
    release_both_screwdrivers(id)  # Release resources

def main():
    # target is the callable object to be invoked by the run() method
    # args is a list or tuple of arguments for the target invocation
    # или в каждом потоке вызывается своя функция doctor_thread с переменной i
    doctors = [threading.Thread(target=doctor_thread, args=(i,)) for i in range(9, 14)]
    # Once a thread object is created, its activity must be started by calling the 
    # thread’s start() method. This invokes the run() method in a separate thread of control.
    # или нужно вручную запустить каждый поток (функцию в нем doctor_thread)
    for d in doctors:
        d.start()

    # Other threads can call a thread’s join() method. This blocks the calling thread until 
    # the thread whose join() method is called is terminated.
    for d in doctors:
        d.join()  # Wait for all threads to finish

if __name__ == '__main__':
    start_time = round(time.time() * 1000)
    main()
    duration = round(time.time() * 1000) - start_time
    # print(f"Duration 1: {duration / 1000:.2f} seconds")

    # выводы практически всегда идут в порядке возрастания номеров докторов
    # Из-за отсутствия print() планировщик потоков почти не переключается между ними. 
    # Поток успевает выполнить весь код до того, как планировщик передаст управление другому потоку.
    # Поэтому добавили временные задержки в функции blast() чтобы GIL переключался между потоками