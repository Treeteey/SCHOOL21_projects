import random
import time
import asyncio
import os
import threading
import tabulate
from enum import Enum

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
        if self.gender == "Ж":
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
    start_exam_time: float
    start_time: float
    total_time: float
    state: ExaminerState # exam, wait, eat
    students: list[Student]
    questions: list[str]
    ate: bool
    gender: str
    examiners: list['Examiner']

    def __init__(self, name: str, gender:str, students: list[Student], questions: list[str], examiners: list['Examiner'], start_exam_time: float):
        self.state = ExaminerState.wait
        self.name = name
        self.total_students = 0
        self.failed = 0
        self.students = students
        self.questions = questions
        self.ate = False
        self.current_student = None
        self.total_time = 0
        self.gender = gender
        self.start_time = time.time()
        self.examiners = examiners
        self.start_exam_time = start_exam_time


    async def go_eat(self):
        draw_table_2(self.students, self.examiners, self.start_exam_time)
        await asyncio.sleep(random.randint(12, 18))
        self.ate = True
    
    def exam_time(self) -> int:
        lenght = len(self.name)
        return random.uniform(lenght-1, lenght+1)

    async def get_student(self, student: Student):
        # print(f"{self.name} get {student.name}")
        self.current_student = student
        self.total_students += 1
        right_answers = 0
        self.current_student.start_time = time.time()

        draw_table_2(self.students, self.examiners, self.start_exam_time)

        right_answers = self.ask_questions()

        time_ = self.exam_time()              
        # print(f"{self.name} time sleep {time_}")
        await asyncio.sleep(time_)

        self.make_desicion(right_answers)
        
        # print(f"{self.name} finish {student.name}")
        self.current_student.total_time = time.time() - self.current_student.start_time
        self.current_student = None

        draw_table_2(self.students, self.examiners, self.start_exam_time)





    def ask_questions(self) -> int:    
         # ask 3 questions
        right_answers = 0
        for _ in range(3):
            attempt = 0
            while attempt < 10:  # 10 попыток, если все вопросы уже заданы - выходим
                new_question = random.choice(self.questions)
                if new_question not in self.current_student.asked_questions:
                    student_answer = self.current_student.answer(new_question)
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
        return right_answers

    def make_desicion(self, right_answers: int):
        # make desicion
        desicions = (0, 1, 2) # 0 - fail, 1 - pass, 2 - depends on right answers
        weights = (1/8, 1/4, 5/8)
        desicion = random.choices(desicions, weights, k=1)[0]
        if desicion == 0:
            self.current_student.failed()
            self.failed += 1
        elif desicion == 1:
            self.current_student.passed()
        else:
            # если правильных ответов больше 2 - студент сдал
            if right_answers >= 2:
                self.current_student.passed()
            else:
                self.current_student.failed()
                self.failed += 1    


    def exam_answer(self, question: str) -> list[str]:
        words = question.split(" ")
        lenght = len(words)

        if lenght <= 1:
            return words

        golden_ratio = 1.61803398875
        probabilities = [1 / (golden_ratio ** i) for i in range(1, len(words)+1)]
        sum_prob = sum(probabilities)
        # счетчик доступных слов, если 0 - элемент не будет выбран никогда
        probabilities = [i / sum_prob for i in probabilities]
        if self.gender == "Ж":
            probabilities.reverse()
        answer = random.choices(words, weights=probabilities, k=1)[0]

        result_list = []

        first_index = random.choices(range(lenght), probabilities, k=1)[0] # индекс слова из вопроса 
        result_list.append(words[first_index])

        probabilities[first_index] = 0 # слово под этим индексом больше не будет выбрано

        options = (1, 0) # 1 get another word, 0 stop
        weights = (1/3, 2/3)

        while True and sum(probabilities) > 0:
            if random.choices(options, weights, k=1)[0] == 0:
                break
            else:
                index = random.choices(range(lenght), probabilities, k=1)[0]
                result_list.append(words[index])
                probabilities[index] = 0

        return result_list



    def next_student(self) -> Student | None:
        global count
        with lock:
            if count >= len(self.students): 
                return None
            student = self.students[count] 
            count += 1 
        return student


    async def run(self):
        self.start_time = time.time()
        while True:
            next_student = self.next_student()
            if next_student is None:
                break
            await self.get_student(next_student)
            if time.time() - self.start_time > 30 and not self.ate:
                await self.go_eat()
            await asyncio.sleep(1)
        self.total_time = time.time() - self.start_time

def clear_console():
    os.system("cls" if os.name == "nt" else "clear")


STATE_TRANSLATION = {
    StudentState.queue: "Очередь",
    StudentState.passed: "Сдал",
    StudentState.failed: "Завалил"
}


def draw_table_2(students: list[Student], examiners: list[Examiner], start_time: float):
    clear_console()
    students_sorted = sorted(students, key=lambda s: s.state.value)
    student_data = [[s.name, STATE_TRANSLATION[s.state]] for s in students_sorted]

    examiner_data = [[e.name, e.current_student.name if e.current_student else "-",
                        e.total_students, e.failed, f"{(time.time() - e.start_time):.2f} сек"]
                        for e in examiners]

    print(tabulate.tabulate(student_data, headers=["Студент", "Статус"], tablefmt="grid"))

    print(tabulate.tabulate(examiner_data, headers=["Экзаменатор", "Текущий студент", "Всего", "Завалил", "Время работы"], tablefmt="grid"))

    remaining_students = len([s for s in students if s.state == StudentState.queue])
    print(f"\nОсталось в очереди: {remaining_students} из {len(students)}")

    print(f"Время с момента начала экзамена: {(time.time() - start_time):.2f} сек")