import random
from itertools import repeat
import time as t


#functions

def m10maker(n):
    maker = True
    qwerty = 0
    while maker == True:
        if qwerty == int((n - 1)/10) - 1:
            maker = False
        qwerty += 1
        multiples_of_10.append((qwerty * 10)-1) 

def getplayersnames(p,t,an,num):
    for counter in range(int(p)):
        n = num[an]
        the =  input('Who is your ' + n + ' player? ')
        t.insert(an, the)
        an = an + 1
        list_of_players = ', '.join(t)
    ans1 = input('These are the players playing:\n' + list_of_players + '\nAre these the only people playing(y/n)?')
    if ans1 == 'n':
        play = input('How many more players are playing?')
        getplayersnames(play,t,an,num)
    else:
        print('Now for the player\'s cards')


def makecards(clen, cnums, p, n):
   for a in range(p):
        num90 = list(range(1, n))
        for counter in range(clen):
            cardnum = random.choice(num90)
            num90.remove(cardnum)
            cnums[a].append(cardnum)

def getnumbers(num90, finnums, a, names, cards, fincards, an, nums, an2, finnames, an3):
    z = [ ]
    while len(num90) > 0:
        print('Retrieving number...')
        t.sleep(1)
        chosen_number = random.choice(num90)
        print('The chosen number is ' + str(chosen_number))
        num90.remove(chosen_number)
        finnums.append(chosen_number)
        print('Checking for occurrence in cards...')
        t.sleep(1)
        an = 0
        an2 = 0
        c = len(names) - len(finnames)
        for counter in range(len(names)):
            an3 = 0
            plural = ' numbers'
            if chosen_number in cards[counter]:
                an += 1
                fincards[counter].append(chosen_number)
                cards[counter].remove(chosen_number)
                if len(cards[counter]) == 0:
                    an2 += 1
                    an3 += 1
                    print(names[counter] + ' has finished their numbers and is ' + nums[0])
                    finnames.append(names[counter])
                if an3 != 1:
                    if len(cards[counter]) == 1:
                        plural = ' number'
                    print(names[counter] + ', you have ' + str(chosen_number) + ' in your card, and have ' + str(len(cards[counter])) + plural + ' left to finish')
                t.sleep(0.5)
        if an < 1:
            print('No one has ' + str(chosen_number))
        if an2 >= 1:
            z.append(an2)
            nums.remove(nums[0])
        if a in multiples_of_10:
            print('The numbers that have been called out so far are: ' + ', '.join(map(str, finnums)))
        a = a + 1
        xyz = input('Are you ready to continue? ')
    return [z, finnames]

#variables/lists

winner = 'winners are'

finnumbers = [ ]

z = [ ]

the_players = [ ]

finplayers = [ ]

donenums = [ ]

any_use = 0

anyuse = 0

anyuses = 0

any_uses = 0

numbers = ['first', 'second', 'third', 'fourth', 'fifth', 'sixth', 'seventh', 'eigth', 'ninth', 'tenth', 'eleventh', 'twelfth']

global multiples_of_10
multiples_of_10 = [ ]

#intro
print('Welcome to DigiBingo(3 - 12 players)!')
print('DigiBingo:\n    1. Asks for details\n    2. Makes each player a card of numbers\n    3. Chooses a random number not chosen already and shows which people have that number\n    4. Displays the winner and the order of players(who came 1st/2nd/last)')
print('So...')
t.sleep(0.5)
print('Let\'s get started.')

#get player's names and setup
player = input('How many players are playing DigiBingo? ')
getplayersnames(player,the_players,any_use,numbers)
n = int(input('How many numbers would you like to use(e.g. 90, 100)'))
n += 1
numbers_to_n = list(range(1, n))
if n > 10:
    m10maker(n)

#make the cards
cardnums = [[] for counter in repeat(None, len(the_players))]
cardlen= input('How many numbers would you like per each player\'s cards(numbers  to strike out when called)? ')
makecards(int(cardlen), cardnums, len(the_players), n)
for a in range(len(the_players)):
    l = ', '.join(map(str, cardnums[a]))
    print(the_players[a] + ', your numbers are: ' + l)
xyzy = input('Are you ready to continue? ')

#calling the numbers
fincardnums = [[] for counter in repeat(None, len(the_players))]
y = getnumbers(numbers_to_n, finnumbers, any_use, the_players, cardnums, fincardnums, anyuse, numbers, anyuses, finplayers, any_uses)
z = y[0]
finplayers = y[1]

#Who wins?
if z[0] == 1:
    winner = 'winner is'
print('The ' + winner + '...', end = ' ')
t.sleep(0.5)
print(', '.join(finplayers[:z[0]]))
numbers = ['First', 'Second', 'Third', 'Fourth', 'Fifth', 'Sixth', 'Seventh', 'Eigth', 'Ninth', 'Tenth', 'Eleventh', 'Twelfth']
for counter in range(len(z)):
    print(f"{numbers[counter]}: {', '.join(finplayers[:z[0]])}")
    for counter in range(z[0]):
        finplayers.remove(finplayers[0])
    z.remove(z[0])








