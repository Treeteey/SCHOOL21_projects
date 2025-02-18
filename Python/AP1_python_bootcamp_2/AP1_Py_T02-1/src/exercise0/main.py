from models import Examiner, Student, StudentState
from ui import draw_finish_table
import sys
import asyncio
import time

# st_file = "src/exercise0/students.txt"
# ex_file = "src/exercise0/examiners.txt"
# qu_file = "src/exercise0/questions.txt"

st_file = "students.txt"
ex_file = "examiners.txt"
qu_file = "questions.txt"

def get_data() -> tuple:
    try:
        with open(st_file, "r", encoding="utf-8") as f:
            students = [line.strip().split() for line in f if len(line.strip().split()) == 2] 
        with open(ex_file, "r", encoding="utf-8") as f:
            examiners = [line.strip().split() for line in f if len(line.strip().split()) == 2]
        with open(qu_file, "r", encoding="utf-8") as f:
            questions = [line.strip() for line in f if line.strip()]
    except:
        print("Wrong file")
        sys.exit()
    if check_data(students, examiners, questions):
        return students, examiners, questions
    else:
        sys.exit()


def check_data(students: list[str], examiners: list[str], questions: list[str]) -> bool:
    if len(students) == 0 or len(examiners) == 0 or len(questions) == 0:
        print("Wrong data")
        return False
    count = 0
    for student_info in students:
        if len(student_info) != 2 or student_info[1] not in ["М", "Ж"]:
            print(f"Wrong {count} student data")
            return False
        count += 1
    count = 0
    for examiner_info in examiners:
        if len(examiner_info) != 2 or examiner_info[1] not in ["М", "Ж"]:
            print(f"Wrong {count} examiner data")
            return False
        count += 1
    count = 0
    for question in questions:
        if len(question) == 0:
            print(f"Wrong {count} question data")
            return False
        count += 1
    return True

count = 0 # student queue


async def main():
    students, examiners, questions = get_data()
    students_list = [Student(name, gender) for name, gender in students]
    start_exam_time = time.time()

    examiner_list = []  # Создаём список заранее
    for e in examiners:
        examiner = Examiner(e[0], e[1], students_list, questions, examiner_list, start_exam_time)
        examiner_list.append(examiner)

    tasks = [asyncio.create_task(examiner.run()) for examiner in examiner_list]
    
    await asyncio.gather(*tasks)  # Запуск всех задач
    draw_finish_table(students_list, examiner_list, start_exam_time)


if __name__ == "__main__":
    asyncio.run(main())