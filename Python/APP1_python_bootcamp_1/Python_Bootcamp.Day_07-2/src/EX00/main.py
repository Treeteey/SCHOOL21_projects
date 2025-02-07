from ask_questions import ask_questions
from is_replicant import is_replicant

if __name__ == '__main__':
    ans_inds = ask_questions()
    is_repl = is_replicant(ans_inds)
    print(is_repl)