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

def can_be_replicant_by_indicators(indicators) -> bool:
    """
    Determines if a person can be classified as a replicant based on given indicators.

    Args:
        indicators (List[int]): A list of four indicators.

    Returns:
        bool: True if the indicators suggest the person could be a replicant, False otherwise.

    Raises:
        ValueError: If the `indicators` list does not contain exactly 4 elements.
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

      



def is_replicant(ans_inds) -> bool:
    """
    Determines if the user is a replicant based on answers and indicators.

    Args:
        ans_inds (Tuple[List[int], List[List[int]]]): 
            A tuple containing:
                - A list of answers provided by the user.
                - A list of indicators associated with each question.

    Returns:
        bool: True if the user is classified as a replicant, False otherwise.

    Raises:
        ValueError: If the answers or indicators are invalid.
    """
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

    replicant_by_empathy = False if count_empathy > len(answers) else True
    if replicant_by_empathy or count_deviations > len(answers)/2:
        return True
    else:
        return False