from typing import List

# сочуствие/эмоциональность в ответах в порядке возрастания
# на вопросы из questions.json 
empathy = [
    [1, 2, 3],
    [3, 2, 1],
    [3, 2, 1],
    [2, 3, 1],
    [2, 1, 3],
    [1, 3, 2],
    [1, 3, 2],
    [1, 2, 3],
    [3, 2, 1],
    [3, 2, 1],
]

def can_be_replicant_by_indicators(indicators:  List[int]) -> bool:
    """
    Проверка на возможность быть репликантом
    """
    
    if len(indicators) != 4:
        raise ValueError("indicators must have 4 elements")
    deviations = []
    if indicators[0] > 11 and indicators[0] < 17:
        deviations.append(True)
    if indicators[1] > 59 and indicators[1] < 101:
        deviations.append(True)
    if indicators[2] < 3:
        deviations.append(True)
    if indicators[3] < 5:
        deviations.append(True)
    if True in deviations:
        return True
    else:
        return False

      



def is_replicant(ans_inds: tuple[List[int], List[List[int]]]) -> bool:
    answers, indicators = ans_inds
    count_empathy = 0
    count_deviations = 0
    for answer_num in range(len(answers)):
        # higher j = more empathy -> max == 20 NOT REPLICANT!
        for j in range(len(empathy[answer_num])):
            if answers[answer_num] == empathy[answer_num][j]:
                count_empathy += j
        
        can_be_repl = can_be_replicant_by_indicators(indicators[answer_num])
        if can_be_repl:
            count_deviations += 1

    replicant_by_empathy = False if count_empathy > 10 else True
    if replicant_by_empathy or count_deviations > 5:
        return True
    else:
        return False