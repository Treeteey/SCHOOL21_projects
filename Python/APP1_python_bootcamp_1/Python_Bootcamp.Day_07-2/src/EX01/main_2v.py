import sys
import os
# Add the parent directory of `EX01` to the module search path
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

from EX01.ask_questions_2v import ask_questions, write_indicators
from EX01.is_replicant_2v import is_replicant



def main():
    """
    Launches the program
    
    """
    filename = 'questions.json'
    ans_inds = ask_questions(filename)
    write_indicators(ans_inds)
    is_repl = is_replicant(ans_inds)
    print(is_repl)



if __name__ == '__main__':
    main()