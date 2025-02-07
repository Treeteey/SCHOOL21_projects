import asyncio

from enum import Enum, auto
from random import choice


class Action(Enum):
    HIGHKICK = auto()
    LOWKICK = auto()
    HIGHBLOCK = auto()
    LOWBLOCK = auto()

# объект итерируемого типа, так как есть метод __aiter__
class Agent:
    # асинхронный итерируемый объект
    def __aiter__(self, health=5):
        self.health = health
        self.actions = list(Action)
        return self
    # возвращать следующее значение итератора
    async def __anext__(self):
        # returns a single random element
        return choice(self.actions)
    

async def fight():
    agent = Agent() # create iterable
    async for action in agent: # get next random action from iterable
        if agent.health == 0:
            break
        if action == Action.HIGHKICK:
            print('Agent: Action.HIGHKICK, Neo: Action.HIGHBLOCK, Agent Health:', agent.health)
        elif action == Action.LOWKICK:
            print('Agent: Action.LOWKICK, Neo: Action.LOWBLOCK, Agent Health:', agent.health)
        elif action == Action.HIGHBLOCK:
            print('Agent: Action.HIGHBLOCK, Neo: Action.LOWKICK, Agent Health:', agent.health)
            agent.health -= 1
        elif action == Action.LOWBLOCK:
            print('Agent: Action.LOWBLOCK, Neo: Action.HIGHKICK, Agent Health:', agent.health)
            agent.health -= 1

    print('Neo wins!')


# asyncio.run(fight())


async def fight_id(agent: Agent, id):
    async for action in agent: # get next action from iterable
        if agent.health < 0:
            break
        if action == Action.HIGHKICK:
            print(f'Agent {id}: Action.HIGHKICK, Neo: Action.HIGHBLOCK, Agent Health:', agent.health)
        elif action == Action.LOWKICK:
            print(f'Agent {id}: Action.LOWKICK, Neo: Action.LOWBLOCK, Agent Health:', agent.health)
        elif action == Action.HIGHBLOCK:
            print(f'Agent {id}: Action.HIGHBLOCK, Neo: Action.LOWKICK, Agent Health:', agent.health)
            agent.health -= 1
        elif action == Action.LOWBLOCK:
            print(f'Agent {id}: Action.LOWBLOCK, Neo: Action.HIGHKICK, Agent Health:', agent.health)
            agent.health -= 1
        await asyncio.sleep(0.01)
        # корутина приостанавливается и цикл событий переключается на другую задачу (fight_id 
        # для другого агента) 
    

# asyncio не управляет потоками как threading, переключение происходит только в местах
# с await или по завершении корутины. Код между await выполняется последовательно
# и не прерывается  

# asyncio.run запускает корутину и цикл событий в "одном пакете".
# asyncio.create_task добавляет задачу в уже работающий цикл событий.



async def fightmany(n):
    agents = [Agent() for _ in range(n)] # create n iterable object of type Agent
    # create n tasks with each agent and its id
    tasks = [asyncio.create_task(fight_id(agent, id)) for agent, id in zip(agents, range(n))]
    # Запускает несколько корутин одновременно и ждет их завершения.
    await asyncio.gather(*tasks)
    print('Neo wins!')

asyncio.run(fightmany(3))