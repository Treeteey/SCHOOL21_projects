import json
from typing import List, Tuple





def ask_questions() -> tuple[List[int], List[List[int]]]:
    """
    Функция, которая спрашивает у пользователя вопросы и 
    возвращает ответы и показатели
    
    Args:
        None

    Returns:
        tuple[List[int], List[List[int]]]: кортеж с ответами и показателями
    
    Raises:
        None
    """
    with open('questions.json', 'r', encoding='utf-8') as file:
        data = json.load(file)
    counter = 0
    answers = []
    indicators = []
    for question in data['voight_kampff_test']:
        print('Вопрос ',counter, ' : ',question['question'])
        for answer in question['answers']:
            print(answer)
        args = ['f']
        while not args[0].isdigit() or args[0] not in ['1', '2', '3']:
            args = input("Выбери вариант ответа: ").split()
            if len(args) != 1:
                print("Wrong input")
        answers.append(int(args[0]))
        ind = write_indicators()
        indicators.append(ind)
        counter += 1
        print('-----------------')
    return answers, indicators


def write_indicators() -> List[int]:
    while True:
        try:
            data = input("Введи 4 показателя через пробел: ").split()
            if len(data) != 4:
                print("Wrong input")
                continue
            for i in range(4):
                data[i] = int(data[i])
            if data[0] < 0 or data[1] < 0 or data[2] < 1 or data[3] < 2 or\
                data[0] > 100 or data[1] > 300 or data[2] > 6 or data[3] > 8:
                print("Wrong input")
                continue
            break
        except:
            print("Wrong input")
    return data
