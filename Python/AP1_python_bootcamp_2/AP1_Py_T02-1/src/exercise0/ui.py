import tabulate
import os
import time
from models import Examiner, Student, StudentState

def clear_console():
    os.system("cls" if os.name == "nt" else "clear")

STATE_TRANSLATION = {
    StudentState.queue: "Очередь",
    StudentState.passed: "Сдал",
    StudentState.failed: "Завалил"
}


def draw_finish_table(students: list[Student], examiners: list[Examiner], start_time: float):
    clear_console()
    students_sorted = sorted(students, key=lambda s: s.state.value)
    student_data = [[s.name, STATE_TRANSLATION[s.state]] for s in students_sorted]

    examiner_data = [[e.name, e.total_students, e.failed, e.total_time] for e in examiners]

    print(tabulate.tabulate(student_data, headers=["Студент", "Статус"], tablefmt="grid"))

    print(tabulate.tabulate(examiner_data, headers=["Экзаменатор", "Всего студентов", "Завалил", "Время работы"], tablefmt="grid"))


    print(f"\nВремя с момента начала экзамена и до момента его завершения: {(time.time() - start_time):.2f}")
    
    passed_students = [s for s in students if s.state.name == StudentState.passed.name]
    if len(passed_students) > 0:
        min_time = min(s.total_time for s in passed_students)
        best_students = [s.name for s in passed_students if s.total_time <= min_time]
        print("Имена лучших студентов:", ", ".join(best_students))

    min_failed = min(e.failed/e.total_students for e in examiners)
    best_examiners = [e.name for e in examiners if e.failed/e.total_students <= min_failed]
    print("Имена лучших экзаменаторов:", ", ".join(best_examiners))

    failed_students = [s for s in students_sorted if s.state.name == "failed"]
    if len(failed_students) > 0:
        min_time_failed = min(s.total_time for s in failed_students)
        worst_students = [s.name for s in failed_students if s.total_time <= min_time_failed]
        print("Имена студентов, которых после экзамена отчислят: ", ', '.join(worst_students))

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
    print("Лучшие вопросы:", ', '.join(best_questions))

    print("Вывод: экзамен ", end="")
    if len(passed_students)/len(students_sorted) > 0.85:
        print("удался")
    else:
        print("не удался")