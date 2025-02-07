import pytest
import json
from EX01.ask_questions_2v import ask_questions, write_indicators

# Mock data for testing
QUESTIONS_JSON = {
    "voight_kampff_test": [
        {
            "id": 0,
            "question": "Sample question?",
            "answers": ["1. Answer A", "2. Answer B", "3. Answer C"]
        }
    ]
}

def test_ask_questions_empty_file():
    # Create an empty file
    with open('empty_questions.json', 'w', encoding='utf-8') as f:
        json.dump({}, f)

    with pytest.raises(KeyError):
        ask_questions('empty_questions.json')

def test_ask_questions_invalid_file():
    with pytest.raises(KeyError):
        ask_questions('empty_questions.json')


# monkeypatch.setattr temporarily replaces the input function in 
# the builtins module with a lambda function that always returns the string "15 60 3 5".

# Instead of waiting for actual user input, it immediately receives
# the string "15 60 3 5" from the mocked input
def test_write_indicators_valid_input(monkeypatch):
    monkeypatch.setattr("builtins.input", lambda _: "15 60 3 5")
    result = write_indicators()
    assert result == [15, 60, 3, 5]


def test_write_indicators_out_of_bounds(monkeypatch):
    # Simulate user entering invalid input twice, then valid input
    inputs = iter([
        "200 60 3 5",  # Invalid input (data[0] > 100)
        "15 -10 3 5",  # Invalid input (data[1] < 0)
        "10 60 3 5"    # Valid input
    ])
    # lambda func replaces the input function
    monkeypatch.setattr("builtins.input", lambda _: next(inputs))
    
    result = write_indicators()
    assert result == [10, 60, 3, 5]  # The valid input

# monkeypatch is a feature provided by pytest that allows you to 
# temporarily modify or replace parts of your application during testing. 
# This can include:
#   Mocking or replacing functions and methods.
#   Modifying or overriding attributes and global variables.
#   Simulating user input or external dependencies.

# builtins is a module in Python that contains all the built-in functions 
# (e.g., input, print, len) that are globally available.