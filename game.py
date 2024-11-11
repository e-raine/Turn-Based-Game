# library
import random

def main():
    hp = int(input("Input max HP: "))
    player_hp = max_hp(hp)
    
    if choice() == toss_coin():
        player_moves()
    else:
        bot_players()
    print(choice(),toss_coin())

            
def max_hp(hp):    
    while (hp < 50 or hp > 200):
        hp = int(input("Input max HP: "))
    return str(hp) 

def toss_coin():
    coin = random.randint(1,2)
    return coin

def choice():
    n = int(input("Input: \n [1] Heads \n [2] Tails "))
    return n 

def player_moves():
    print("Player moves")

def bot_players():
    print("Bot Moves")


main()
