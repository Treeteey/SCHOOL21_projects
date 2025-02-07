# install redis server  on windows through "Chocolatey"
# 1) install chokolatey with powershell
# https://docs.chocolatey.org/en-us/choco/setup/
# 2) install redis with chocolatey in PowerShell:
# 'pip install redis'  in VS Code

# first - RUN 'redis-server' in PowerShell
# second - RUN 'py consumer.py -e 2222222222,4444444444'
# third - RUN 'py producer.py'  several times, you can change 
#                               that script while redis is ON


import redis
import sys  # для работы с аргументами командной строки

import json # чтобы преобразовать строку message в словарь
            # и считывать нужные поля

'''
По умолчанию, когда вы получаете данные из Redis, 
они возвращаются в виде байтов (bytes). Это означает, 
что вы получаете данные в виде сырых байтов, которые
необходимо декодировать в строку или другой тип данных,
чтобы их можно было использовать в вашем приложении.
  decode_responses=True  - декодирует байты в строку
'''

# connect to server
r = redis.Redis(
  host='127.0.0.1',
  port=6379, 
  db=0,
  # this will ensure that binary data is decoded
  decode_responses=True 
)

# subscribe to channel
p = r.pubsub()
p.subscribe('my_channel')

# check for bad account numbers
bad_account_numbers = [] # str type
if len(sys.argv) > 2 and sys.argv[1] == "-e":
    bad_account_numbers = sys.argv[2].split(",")
    # print(bad_account_numbers)


# read messages
# message это словарь в который записываются данные полученные
# из Redis функцией listen(). В таком словаре есть стандартные ключи
# по которым можно получить данные
for message in p.listen():
    if isinstance(message['data'], str):        
        # create string
        string = message['data']

        # convert string to json dict
        data = json.loads(string)
        numbers = [data['metadata']['from'], data['metadata']['to'], data['amount']]
        # print(numbers)
        
        if numbers[2] > 0 and str(numbers[1]) in bad_account_numbers:
            data['metadata']['from'], data['metadata']['to'] = data['metadata']['to'], data['metadata']['from']
            # print('swap')
        string = json.dumps(data)
        print(string)