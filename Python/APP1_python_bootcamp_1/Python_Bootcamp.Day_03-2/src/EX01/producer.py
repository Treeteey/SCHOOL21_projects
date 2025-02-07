# install redis server  on windows through "Chocolatey"
# 1) install chokolatey with powershell
# https://docs.chocolatey.org/en-us/choco/setup/
# 2) install redis with chocolatey in PowerShell:
# 'pip install redis'  in VS Code

# first - RUN 'redis-server' in PowerShell
# second - RUN 'py consumer.py -e 2222222222,4444444444'
# third - RUN 'py producer.py'  several times, you can change 
#                               that script while redis is ON


# import redis
# import sys

# r = redis.Redis(
#   host='127.0.0.1',
#   port=6379, 
#   db=0,
#   # this will ensure that binary data is decoded
#   decode_responses=True 
# )

# # channel that is listened by consumer
# # and text that should be send to that channel


# def generate_string(number_1: int, number_2: int, amount: int) -> str:
#   string = f'{{"metadata": {{"from": {number_1}, "to": {number_2}}}, "amount": {amount}}}'
#   return string

# sender = 0
# recipient = 0
# amount = 0

# # ИЗМЕНИ ЭТИ данные вручную
# string_custom = generate_string(2222222222, 1023461745, 10000)
# string = string_custom

# if len(sys.argv) == 4:
#   sender = int(sys.argv[1])
#   recipient = int(sys.argv[2])
#   amount = int(sys.argv[3])
#   if len(str(sender)) == 10 and len(str(recipient)) == 10:
#     string = generate_string(sender, recipient, amount)
  

# r.publish('my_channel', string)



import redis
import sys

# connect to server
r = redis.Redis(
  host='127.0.0.1',
  port=6379, 
  db=0,
  # this will ensure that binary data is decoded
  decode_responses=True 
)

# channel that is listened by consumer
# and text that should be send to that channel


def generate_string(number_1: int, number_2: int, amount: int) -> str:
  if number_1 and number_2 and amount and len(str(number_1)) == 10 and len(str(number_2)) == 10:
    string = f'{{"metadata": {{"from": {number_1}, "to": {number_2}}}, "amount": {amount}}}'
    return string
  else:
    return '-1'  

def main(number_1: int, number_2: int, amount: int) -> None:
  string = generate_string(number_1, number_2, amount)
  if string != '-1':
    print(string)
    r.publish('my_channel', string) 


def test():
  cases = [
    (1111111111, 2222222222, 10000),
    (3333333333, 4444444444, -3000),
    (2222222222, 5555555555, 5000),
    (1111111111, 2222222222, -10000),
    (222222, 5555555555, 5000),
    (2222222222, 555555, 5000),
    (2222222222, 4444444444, 5000),
  ]

  for case in cases:
    main(*case)



if __name__ == "__main__":
  # main(1111111111, 2222222222, -10000) # одиночный тест
  test()