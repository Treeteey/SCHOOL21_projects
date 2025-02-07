# Этот файл должен создать из файла todo.yml 
# новый файл deploy.yml для ansible playbook
'''
----------- Пример на виртуальных машинах
1) Создать 2 виртуальных машины - основная и управляемая
2) Задать в настройках виртуалки "Сеть - Виртуальный адаптер хоста" 
    задаст уникальные ip в одной сети
    не позволит подключаться к внешней сети интернет
    но можно взаимводействовать между виртуальными машинами 
    192.168.56.101  - first
    192.168.56.102  - second
3) Установить Ansible на основную машину
4) Установи ssh на обе машины: sudo apt install openssh-server 
    (придется изменить адаптер на nat в настройках виртуалки)
5) Измени IP если нужно
    sudo nano /etc/netplan/...
    sudo netplan apply
6) на основной сгенерируй ключ: ssh-keygen
7) Скопировать ключи на вторую машину: ssh-copy-id user@192.168.56.102
    user - имя пользователя на второй машине а не имя второй машины
8) Проверить подключение можно: ssh user@192.168.56.102
9) Чтобы скопировать файлы с основной машины на виртуальную:
    scp consumer.py user@192.168.56.101:~
    скачается в корневую папку 
10) Создать файл inventory с адресами машин
    [hosts]
    192.168.56.102 ansible_user=user
11) Написать playbook и запустить
    ansible-playbook -i inventory deploy.yml --ask-become-pass
    -i  - подключить inventory
    --ask-become-pass - запрашивать пароль sudo
'''

'''
        Скачать Ansible
На главную машину
sudo apt update && sudo apt -y install software-properties-common
офф репо Ansible
sudo add-apt-repository --yes --update ppa:ansible/ansible

sudo apt -y install ansible

ansible --version
'''

# pip install PyYAML   - установить библиотеку PyYAML windows

import yaml

# Load the data from todo.yaml
with open('../../materials/todo.yml', 'r') as file:
    todo_data = yaml.safe_load(file)

packages = todo_data['server']['install_packages']
files = todo_data['server']['exploit_files']
bad_guys = todo_data['bad_guys']


# Initialize the playbook structure
deploy_playbook = {
    'name': 'Task 02 - Deploy with ansible',
    'hosts': 'hosts', # create inventory file with hosts
    'become': True,   # sudo priveleges
    'tasks': []
}

# Add tasks to install packages from todo.yaml in the correct order
for package in packages:
    deploy_playbook['tasks'].append({
        'name': f'install {package}',
        'apt': {
            'name': package,
            'state': 'present',
            'update_cache': 'yes'
        },
    })

# Add task to create the directory for exploit files
deploy_playbook['tasks'].append({
    'name': 'Create directory',
    'file': {
        'path': '/home/user/fsociety',
        'state': 'directory',
        'owner': 'user',
        'group': 'user',
        'mode': '0755'
    }
})

# Add tasks to copy files from todo.yaml
for exploit_file in files:
    deploy_playbook['tasks'].append({
        'name': f'Copy {exploit_file}',
        'copy': {
            'src': exploit_file,
            'dest': f'/home/user/fsociety/{exploit_file}'
        }
    })

# Add tasks to run exploit.py and consumer.py
deploy_playbook['tasks'].append({
    'name': 'Run exploit.py',
    'raw': 'python3 /home/user/fsociety/exploit.py',
    'ignore_errors': True
})

deploy_playbook['tasks'].append({
    'name': 'Run consumer.py',
    'raw': 'python3 /home/user/fsociety/consumer.py',
    'ignore_errors': True
})

# Write the generated playbook to deploy.yaml
with open('deploy.yml', 'w') as file:
    yaml.dump([deploy_playbook], file, default_flow_style=False, allow_unicode=True)

print("deploy.yml has been generated successfully!")



