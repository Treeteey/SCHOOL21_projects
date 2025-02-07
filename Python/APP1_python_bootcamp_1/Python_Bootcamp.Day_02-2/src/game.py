from collections import Counter
from typing import List
import itertools
import random


class Game(object):

    def __init__(self, matches=10):
        self.matches = matches
        self.registry = Counter() #count candies of each player

    def play(self):
        players = [Cheater(), Cooperator(), Copycat(), Detective(), Grudger(), Killer()]
        player_combinations = list(itertools.combinations(players, 2))
        random.shuffle(player_combinations)  # Shuffle the combinations to play random games
        for player1, player2 in player_combinations[:self.matches]:
            # print(player1.name, ' vs ', player2.name)
            self._play_game(player1, player2)
        # print(self.registry)
        self.top3()

    def _play_game(self, player1, player2):
        steps = 0
        candies1 = 0
        candies2 = 0
        while steps < 10:
            player1.next_step(player2.history)
            player2.next_step(player1.history)

            if player1.history[steps] == 'Cheat' and player2.history[steps] == 'Cooperate':
                candies1 += 3
                candies2 -= 1
            elif player1.history[steps] == 'Cooperate' and player2.history[steps] == 'Cheat':
                candies1 -= 1
                candies2 += 3
            elif player1.history[steps] == 'Cooperate' and player2.history[steps] == 'Cooperate':
                candies1 += 2
                candies2 += 2
            # print('round', steps, ' : ', player1.history[steps], player2.history[steps])
            # print('round', steps, ' : ', candies1, candies2)
            steps += 1
        if self.registry[player1.name] < candies1:
            self.registry[player1.name] = candies1 
        if self.registry[player2.name] < candies2:
            self.registry[player2.name] = candies2
        # print(self.registry)


    def top3(self):
        for i in range(3):
            print(self.registry.most_common()[i])
    
    def top5(self):
        registry_len = len(self.registry)
        if registry_len >= 5:
            for i in range(5):
                print(self.registry.most_common()[i])


class Player:
    def __init__(self):
        self.history = []
        self.name = ''
        

    def action(self, action: str) -> None:
        self.history.append(action)
        
    def next_step(self, other_history: List[str]) -> None:
        new_step = self.calc_history(other_history)
        self.action(new_step)

    def calc_history(other_history: List[str]) -> str:
        pass

# Always cheats
class Cheater(Player):
    def __init__(self):
        super().__init__()
        self.name = 'Cheater'
    def next_step(self, other_history):
        self.action('Cheat')

# Always cooperates
class Cooperator(Player):
    def __init__(self):
        super().__init__()
        self.name = 'Cooperator'


    def next_step(self, other_history):
        self.action('Cooperate')

# Starts with cooperating, but then just repeats whatever the other guy is doing
class Copycat(Player):
    def __init__(self):
        super().__init__()
        self.name = 'Copycat'

    def next_step(self, other_history):
        if len(self.history) == 0:
            self.action('Cooperate')
        else:
            if other_history and len(other_history) >= len(self.history)-1 > 0:  # Check if other_history is not empty
                self.action(other_history[len(self.history)-1])
            else:
                self.action('Cooperate')

# Starts by always cooperating, but switches to Cheater
# forever if another guy cheats even once
class Grudger(Player):
    def __init__(self):
        super().__init__()
        self.name = 'Grudger'

    def next_step(self, other_history):
        if 'Cheat' not in other_history:
            self.action('Cooperate')
        else:
            self.action('Cheat')



'''
First four times goes with [Cooperate, Cheat, Cooperate, Cooperate],
and if during these four turns another guy cheats even once — switches
into a Copycat. Otherwise, switches into Cheater himself
'''
class Detective(Player):
    def __init__(self):
        self.history = []
        self.name = 'Detective'
        self.new_type = ''

    def next_step(self, other_history):
        rounds = len(self.history)
        if rounds < 4:
            match len(self.history):
                case 0:
                    return self.action('Cooperate')
                case 1:
                    return self.action('Cheat')
                case 2:
                    return self.action('Cooperate')
                case 3:
                    return self.action('Cooperate')
        else:
            if len(self.history) == 4:
                if 'Cheat' in other_history:
                    self.new_type = 'Copycat'
                else:
                    self.new_type = 'Cheater'
            if self.new_type == 'Copycat':
                if len(self.history)-1 > 0:
                    self.action('Cooperate')
                else:
                    self.action(other_history[len(self.history)-1])
            elif self.new_type == 'Cheater':
                self.action('Cheat')

class Killer(Player):
    def __init__(self):
        super().__init__()
        self.name = 'Killer'
    
    def next_step(self, other_history):
        if len(self.history) == 0:
            self.action('Cooperate')
        else:
            self.action('Cheat')
            # if other_history and len(other_history) >= len(self.history)-1 > 0:  # Check if other_history is not empty
            #     self.action(other_history[len(self.history)-1])
            # else:
            #     self.action('Cheat')


if __name__ == "__main__":
    game = Game()
    game.play()

    # print('Top5:')
    # game.top5()