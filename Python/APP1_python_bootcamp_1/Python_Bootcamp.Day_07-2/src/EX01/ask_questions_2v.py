import json
from typing import List





def ask_questions(filename) -> List[str]:
    """
    Prompts the user with questions from a JSON file and collects answers and indicators.

    Args:
        filename (str): The path to the JSON file containing the questions.

    Returns:
        Tuple[List[int], List[List[int]]]: 
            A tuple containing:
                - A list of integers representing the user's answers.
                - A list of lists, where each inner list contains indicators associated with each question.

    Raises:
        FileNotFoundError: If the specified file does not exist.
        ValueError: If the file is not a valid JSON.
        RuntimeError: If an unexpected error occurs while opening or reading the file.
        KeyError: If the JSON file does not contain the expected structure ('voight_kampff_test').
    """
    try:
        with open(filename, 'r', encoding='utf-8') as file:
            data = json.load(file)
            print("File opened")
    except FileNotFoundError:
        raise FileNotFoundError(f"File '{filename}' does not exist.")
    except json.JSONDecodeError:
        raise ValueError(f"File '{filename}' is not a valid JSON file.")
    except Exception as e:
        raise RuntimeError(f"An unexpected error occurred: {e}")
    
    counter = 0
    answers = []
    indicators = []
    try:
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
            # break
        return answers, indicators
    except:
        raise KeyError


def write_indicators() -> tuple[int,...]:
    """
    Collects four indicators from the user input.

    The indicators must meet the following conditions:
        - The first value is between 0 and 100 (inclusive).
        - The second value is between 0 and 300 (inclusive).
        - The third value is between 1 and 6 (inclusive).
        - The fourth value is between 2 and 8 (inclusive).

    Returns:
        Tuple[int, int, int, int]: A tuple containing four integer indicators.

    Raises:
        ValueError: If the input values are invalid or out of the specified range.
    """
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
