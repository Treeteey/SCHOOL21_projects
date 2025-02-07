import random
import time
import locale 
import asyncio
import threading
from enum import Enum
import tabulate
import os

# st_file = "src/students.txt"
# ex_file = "src/examiners.txt"
# qu_file = "src/questions.txt"

st_file = "students.txt"
ex_file = "examiners.txt"
qu_file = "questions.txt"

def get_data()-> bool:
    with open(st_file, "r", encoding="utf-8") as f:
        students = [line.strip().split() for line in f]
    with open(ex_file, "r", encoding="utf-8") as f:
        examiners = [line.strip().split()[0] for line in f]
    with open(qu_file, "r", encoding="utf-8") as f:
        questions = [line.strip() for line in f if line.strip()]
    
    return students, examiners, questions


lock = threading.Lock()
count = 0 # student queue

class StudentState(Enum):
    queue = 1
    passed = 2
    failed = 3

class Student:
    state: StudentState
    name: str
    gender: bool
    asked_questions: list[str]
    start_time: float
    total_time: float
    correct_answers: {}

    def __init__(self, name: str, gender: str):
        self.state = StudentState.queue
        self.name = name
        self.gender = gender
        self.asked_questions = []
        self.correct_answers = {}
    

    def passed(self):
        self.state = StudentState.passed
    
    def failed(self):
        self.state = StudentState.failed

    def answer(self, question: str) -> str:
        '''
        Возвращает слово из вопроса, выбранное по принципу золотого сечения

        :param question: вопрос
        :return: слово из вопроса

        random.choices(population, weights=None, *, cum_weights=None, k=1)
        population - последовательность (строка, список, кортеж)
        weights - последовательность чисел, которые используются в качестве весов для выбора элементов из популяции
        cum_weights - последовательность чисел, которые используются в качестве накопленных весов для выбора элементов из популяции
        k - количество элементов, которые нужно выбрать
        '''
        words = question.split(" ")
        golden_ratio = 1.61803398875
        probabilities = [1 / (golden_ratio ** i) for i in range(len(words))]
        sum_prob = sum(probabilities)
        probabilities = [i / sum_prob for i in probabilities]
        if self.gender == "female":
            probabilities.reverse()
        answer = random.choices(words, weights=probabilities, k=1)[0]
        self.asked_questions.append(question)
        return answer
    


class ExaminerState(Enum):
    exam = 1
    wait = 2
    eat = 3

class Examiner:
    name: str
    current_student: Student
    total_students: int
    failed: int
    start_time: float
    total_time: float
    state: ExaminerState # exam, wait, eat
    students: list[Student]
    questions: list[str]
    ate: bool


    def __init__(self, name: str, students: list[Student], questions: list[str]):
        self.state = ExaminerState.wait
        self.name = name
        self.total_students = 0
        self.failed = 0
        self.students = students
        self.questions = questions
        self.ate = False
        self.current_student = None
        self.total_time = 0


    def go_eat(self):
        time.sleep(random.randint(12, 18))
        self.ate = True
    
    def exam_time(self) -> int:
        lenght = len(self.name)
        return random.uniform(lenght-1, lenght+1)

    def get_student(self, student: Student):
        # print(f"{self.name} get {student.name}")
        self.current_student = student
        self.total_students += 1
        right_answers = 0
        self.current_student.start_time = time.time()
        # ask 3 questions
        for _ in range(3):
            attempt = 0
            while attempt < 10:  # 10 попыток, если все вопросы уже заданы - выходим
                new_question = random.choice(self.questions)
                if new_question not in student.asked_questions:
                    student_answer = student.answer(new_question)
                    examiner_answer = self.exam_answer(new_question)
                    if student_answer in examiner_answer:
                        right_answers += 1
                        self.current_student.correct_answers[new_question] = True
                    else:
                        self.current_student.correct_answers[new_question] = False
                    break # Выходим из цикла, если вопрос задан
                attempt += 1  # Увеличиваем счётчик попыток
            else:
                pass
                # print(f"{self.name} не смог задать новый вопрос {student.name}")  # Если все попытки неудачны

        time_ = self.exam_time()              
        # print(f"{self.name} time sleep {time_}")
        time.sleep(time_)


        # make desicion
        desicions = (0, 1, 2) # 0 - fail, 1 - pass, 2 - depends on right answers
        weights = (1/8, 1/4, 5/8)
        desicion = random.choices(desicions, weights, k=1)[0]
        if desicion == 0:
            student.failed()
            self.failed += 1
        elif desicion == 1:
            student.passed()
        else:
            # если правильных ответов больше 2 - студент сдал
            if right_answers >= 2:
                student.passed()
            else:
                student.failed()
                self.failed += 1      
        
        
        # print(f"{self.name} finish {student.name}")
        self.current_student.total_time = time.time() - self.current_student.start_time
        self.current_student = None





    def exam_answer(self, question: str) -> list[str]:
        words = question.split(" ")
        lenght = len(words)

        if lenght <= 1:
            return words

        result_list = []
        # счетчик доступных слов, если 0 - элемент не будет выбран никогда
        word_weights = [1 for _ in range(lenght)]

        first_index = random.randint(0, lenght-1) # индекс слова из вопроса 
        result_list.append(words[first_index])

        word_weights[first_index] = 0 # слово под этим индексом больше не будет выбрано

        options = (1, 0) # 1 get another word, 0 stop
        weights = (1/3, 2/3)

        while True and word_weights.count(1) > 0:
            if random.choices(options, weights, k=1)[0] == 0:
                break
            else:
                index = random.choices(range(lenght), word_weights, k=1)[0]
                result_list.append(words[index])
                word_weights[index] = 0

        return result_list
    
    def next_student(self) -> Student | None:
        global count
        with lock:
            if count >= len(self.students): 
                return None
            student = self.students[count] 
            count += 1 
        return student


    def run(self):
        self.start_time = time.time()
        # print(f"{self.name} начинает работу")
        while True:
            next_student = self.next_student()
            if next_student is None:
                # print(f"{self.name} завершает работу (студенты кончились)")
                break
            else:
                self.get_student(next_student)

            if time.time() - self.start_time > 30 and not self.ate:
                # print(f"{self.name} go eat")
                self.go_eat()
                # print(f"{self.name} back")

            # print(f"{self.name} засыпает на 1 секунду")
            time.sleep(1)   
        # print(f"{self.name} завершил работу окончательно")
        self.total_time = time.time() - self.start_time
    
def main():
    students, examiners, questions = get_data()

    students_list = [Student(name, gender) for name, gender in students]
    examiner_list = [Examiner(name, students_list, questions) for name in examiners]
    # потоки для экзаменаторов
    threads = [threading.Thread(target=examiner.run) for examiner in examiner_list]
    # отдельный поток для отрисовки таблицы
    thread_table = threading.Thread(target=draw_table, args=(students_list, examiner_list, time.time(), threads), daemon=True)
    
    start_time = time.time()

    for thread in threads:
        thread.start()
    thread_table.start()

    for thread in threads:
        thread.join()
    thread_table.join()
    
    draw_finish_table(students_list, examiner_list, start_time)




def clear_console():
    os.system("cls" if os.name == "nt" else "clear")

def draw_table(students: list[Student], examiners: list[Examiner], start_time: float, threads: list[threading.Thread]):
    while True:
        with lock:
            clear_console()
            students_sorted = sorted(students, key=lambda s: s.state.value)
            student_data = [[s.name, s.state.name] for s in students_sorted]

            examiner_data = [[e.name, e.current_student.name if e.current_student else "-",
                              e.total_students, e.failed, f"{int(time.time() - e.start_time)} сек"]
                             for e in examiners]

            print("Таблица студентов:")
            print(tabulate.tabulate(student_data, headers=["Студент", "Статус"], tablefmt="grid"))

            print("\nТаблица экзаменаторов:")
            print(tabulate.tabulate(examiner_data, headers=["Экзаменатор", "Текущий студент", "Всего", "Завалил", "Время работы"], tablefmt="grid"))

            remaining_students = len([s for s in students if s.state == StudentState.queue])
            print(f"\nОсталось в очереди: {remaining_students} из {len(students)}")

            elapsed_time = int(time.time() - start_time)
            print(f"\nПрошло времени: {elapsed_time} сек")

            # Если в очереди больше нет студентов, прерываем цикл
            if all(not t.is_alive() for t in threads):
                break

        time.sleep(1)

def draw_finish_table(students: list[Student], examiners: list[Examiner], start_time: float):
    clear_console()
    students_sorted = sorted(students, key=lambda s: s.state.value)
    student_data = [[s.name, s.state.name] for s in students_sorted]

    examiner_data = [[e.name, e.total_students, e.failed, e.total_time] for e in examiners]

    print("Таблица студентов:")
    print(tabulate.tabulate(student_data, headers=["Студент", "Статус"], tablefmt="grid"))

    print("\nТаблица экзаменаторов:")
    print(tabulate.tabulate(examiner_data, headers=["Экзаменатор", "Всего студентов", "Завалил", "Время работы"], tablefmt="grid"))

    formatted_start_time = time.strftime("%H:%M:%S", time.localtime(start_time))
    formatted_end_time = time.strftime("%H:%M:%S", time.localtime(time.time()))
    print(f"Начало экзамена: {formatted_start_time}, конец экзамена: {formatted_end_time}")
    
    passed_students = [s for s in students if s.state.name == StudentState.passed.name]
    if len(passed_students) > 0:
        min_time = min(s.total_time for s in passed_students)
        best_students = [s.name for s in passed_students if s.total_time <= min_time]
        print("\nЛучшие студенты:", best_students)

    min_failed = min(e.failed/e.total_students for e in examiners)
    best_examiners = [[e.name for e in examiners if e.failed/e.total_students <= min_failed]]
    print("\nЛучшие экзаменаторы:", best_examiners)

    failed_students = [[s.name, s.total_time] for s in students_sorted if s.state.value == "Failed"]
    if len(failed_students) > 0:
        min_time_failed = min(s.total_time for s in failed_students)
        worst_students = [s.name for s in failed_students if s.total_time <= min_time_failed]
        print("Студенты на отчисление: ", worst_students)

    # словарь для подсчёта правильных ответов по вопросам
    best_questions = {}    
    # Iterate over all students
    for s in students_sorted:
        # items() возвращает пары ключ-значение
        for q, correct in s.correct_answers.items():
            # dict.get() возвращает значение по ключу, если ключа нет - возвращает 0
            best_questions[q] = best_questions.get(q, 0) + int(correct)
    max_correct_answers = max(best_questions.values())
    best_questions = {q: c for q, c in best_questions.items() if c == max_correct_answers}
    print("\nЛучшие вопросы:", best_questions)

    if len(passed_students)/len(students_sorted) > 0.85:
        print("\nЭкзамен удался")
    else:
        print("\nЭкзамен провален")

if __name__ == "__main__":
    main()