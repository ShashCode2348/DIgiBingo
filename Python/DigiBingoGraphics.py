import random
from itertools import repeat
import time as t
from tkinter import *
from tkinter import simpledialog
from tkinter import messagebox

#Functions

def num_maker(counter):
    xy = counter
    num = Label(display, anchor=CENTER, font=('Arial', 25), text=("%02d" % (xy,)))
    counter = xy - 1
    i = ("%02d" % (counter,))
    z = int(i[1]) * 78
    if int(i[1]) > 4:
        z += 63
    x_pos = z + 625
    y_pos = int(i[0]) * 64 + 62
    num.place(x=x_pos, y=y_pos)

def getplayersnames(p,t,an,num):
    for counter in range(int(p)):
        n = num[an]
        the =  simpledialog.askstring('Name', 'Who is your ' + n + ' player? ')
        t.insert(an, the)
        an = an + 1
        list_of_players = ', '.join(t)
    ans1 = messagebox.askyesno('Players', 'These are the players playing:\n' + list_of_players + '\nAre these the only people playing(y/n)?')
    if ans1 == False:
        play = simpledialog.askstring('Players' ,'How many more players are playing?')
        getplayersnames(play,t,an,num)
    else:
        messagebox.askquestion('Part 2: Players Cards' ,'Now for the player\'s cards. Are you ready to continue?')

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
        chosen_number = random.choice(num90)
        num90.remove(chosen_number)
        finnums.append(chosen_number)
        cd.config(text="%02d" % (chosen_number,))
        num_maker(chosen_number)
        t.sleep(1)
        an = 0
        an2 = 0
        message_text = ''
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
                    message_text += (names[counter] + ' has finished their numbers and is ' + nums[0] + '\n')
                    finnames.append(names[counter])
                if an3 != 1:
                    if len(cards[counter]) == 1:
                        plural = ' number'
                    message_text += (names[counter] + ', you have ' + str(chosen_number) + ' in your card, and have ' + str(len(cards[counter])) + plural + ' left to finish' + '\n')
                t.sleep(1.5/len(names))
        if an2 >= 1:
            z.append(an2)
            nums.remove(nums[0])
        a += 1
        message_text += ('Are you ready to continue(Press "No" to exit the game)?')
        if messagebox.askquestion('Continue?', message_text) == 'no':
            quit()
    return [z, finnames]

#Variables/Lists
posTextList = [ ]
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
numbers = ['first', 'second', 'third', 'fourth', 'fifth', 'sixth', 'seventh', 'eigth', 'ninth', 'tenth', 'eleventh', 'twelfth', 'thirteenth', 'fourteenth', 'fifteenth', 'sixteenth', 'seventeenth', 'eighteenth', 'nineteenth', 'twentieth', 'twenty-first', 'twenty-second', 'twenty-third', 'twenty-fourth', 'twenty-fifth', 'twenty-sixth', 'twenty-seventh', 'twenty-eigth', 'twenty-ninth', 'thirtieth']

#Screens and Setup
main = Tk()
main.geometry('+40+10')
main.title("DigiBingo")
display = Canvas(main, width=1470, height=710)
display.pack()
main.attributes("-topmost", True)

#Intro
introText = '''Welcome to DigiBingo(2 - 30 players)!
DigiBingo:
    1. Asks for details
    2. Makes each player a card of numbers
    3. Chooses a random number not chosen already 
    and shows which people have that number
    4. Displays the winner and the position of players
Click the top to get started.'''
introLabel = Label(display, font=('Arial', 18), text=introText, justify=LEFT)
introLabel.place(x=40, y=15)
main.attributes("-topmost", False)

#Get player's names and setup
try:
    player = int(simpledialog.askstring('Part 1: Players', 'How many players are playing DigiBingo?'))
except ValueError:
    print("An integer was not entered")
getplayersnames(player,the_players,any_use,numbers)
n = 91
numbers_to_n = list(range(1, n))

#Make the cards
cardnums = [[] for counter in repeat(None, len(the_players))]
cardlen = 15
makecards(cardlen, cardnums, len(the_players), n)
message_text = ''
for a in range(len(the_players)):
    l = ', '.join(map(str, cardnums[a]))
    message_text += (the_players[a] + ', your numbers are: ' + l + '\n')
messagebox.askquestion('Ready', message_text + 'Are you ready to continue?')

#Setup
display.create_text(245, 289, text='The chosen number is:', font=('Arial', 20))
cd = Label(display, text='', font=('Arial', 245))
cd.place(x=245, y=484, anchor='center')

#Calling the numbers
fincardnums = [[] for counter in repeat(None, len(the_players))]
y = getnumbers(numbers_to_n, finnumbers, any_use, the_players, cardnums, fincardnums, anyuse, numbers, anyuses, finplayers, any_uses)
z = y[0]
finplayers = y[1]

#Who wins?
display.delete("all")
introLabel.destroy()
cd.destroy()
if z[0] == 1:
    winner = 'winner is'
smt = Label(display, text=('The ' + winner + '...'), font=('Arial', 20))
smt.place(y=30, x=30)
t.sleep(5)
sm = Label(display, text=(', '.join(finplayers[:z[0]])), font=('Arial', 20))
sm.place(x=240, y=30)
numbers = ['1st', '2nd', '3rd', '4th', '5th', '6th', '7th', '8th', '9th', '10th', '11th', '12th', '13th', '14th', '15th', '16th', '17th', '18th', '19th', '20th', '21st', '22nd', '23rd', '24th', '25th', '26th', '27th', '28th', '29th', '30th']
for counter in range(len(z)):
    posTextList.append(f"{numbers[counter]}: {', '.join(finplayers[:z[0]])}")
    for counter in range(z[0]):
        finplayers.remove(finplayers[0])
    z.remove(z[0])
h = Label(display, text='\n'.join(posTextList), font=('Arial', 20), justify=LEFT)
h.place(y=60, x=30)
main.mainloop()
