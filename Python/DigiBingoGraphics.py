import random
from itertools import repeat
from tkinter import *
from tkinter import simpledialog
from tkinter import messagebox
import sys

#Functions

def numMaker(chosen_num):
    calc_num = chosen_num - 1
    number = Label(display, anchor=CENTER, font=('Arial', 25), text=("%02d" % (chosen_num,)))
    num_str = ("%02d" % (calc_num,))
    x_pos = int(num_str[1]) * 78 + 625
    if int(num_str[1]) > 4:
        x_pos += 63
    y_pos = int(num_str[0]) * 64 + 62
    number.place(x=x_pos, y=y_pos)

def getPlayersNames(num_players, names, sp, ords):
    for _ in range(int(num_players)):
        ordinal = ords[sp]
        name =  simpledialog.askstring('Name', 'Who is your ' + ordinal + ' player? ')
        names.insert(sp, name)
        sp += 1
    names_str = ', '.join(names)
    complete = messagebox.askyesno('Players', f'These are the players playing:\n {names_str} \nAre these the only people playing(y/n)?')
    if complete == False:
        num_players = simpledialog.askstring('Players' ,'How many more players are playing?')
        getPlayersNames(num_players, names, sp, ords)
    else:
        messagebox.askquestion('Part 2: Players Cards' ,'Now for the player\'s cards. Are you ready to continue?')

def makeCards(card_len, card_nums, num_players, max_num):
    num_options = list(range(1, max_num))
    for player_num in range(num_players):
        for counter in range(card_len):
            card_num = random.choice(num_options)
            num_options.remove(card_num)
            card_nums[player_num].append(card_num)
        num_options.extend(card_nums[player_num])

def callNumbers(call_nums, names, cards, ords, disp_info):
    tie_manager = []
    player_order = []
    while len(call_nums) > 0:
        chosen_number = random.choice(call_nums)
        call_nums.remove(chosen_number)
        chosen_num_disp.config(text="%02d" % (chosen_number,))
        numMaker(chosen_number)
        main.after(1000)
        sp1 = 0
        sp2 = 0
        message_text = ''
        for counter in range(len(names)):
            plural = ' numbers'
            if chosen_number in cards[counter]:
                sp1 += 1
                cards[counter].remove(chosen_number)
                if len(cards[counter]) == 0:
                    sp2 += 1
                    message_text += (names[counter] + ' has finished their numbers and is ' + ords[0] + '\n')
                    player_order.append(names[counter])
                else:
                    if len(cards[counter]) == 1:
                        plural = ' number'
                    message_text += (names[counter] + ', you have ' + str(chosen_number) + ' in your card, and have ' + str(len(cards[counter])) + plural + ' left to finish' + '\n')
        if sp2 >= 1:
            tie_manager.append(sp2)
            ords.remove(ords[0])
        if disp_info == 'no':
            message_text = 'Are you ready to continue(Press "No" to exit the game)?'
        else:
            message_text += ('Are you ready to continue(Press "No" to exit the game)?')
        if messagebox.askquestion('Continue?', message_text) == 'no':
            sys.exit()
    return tie_manager, player_order

#Variable Declaration
position_disp_text = []
winner = 'winners are'
player_names = []
spare = 0
ordinals = ['first', 'second', 'third', 'fourth', 'fifth', 'sixth', 'seventh', 'eigth', 'ninth', 'tenth', 'eleventh', 'twelfth', 'thirteenth', 'fourteenth', 'fifteenth', 'sixteenth', 'seventeenth', 'eighteenth', 'nineteenth', 'twentieth', 'twenty-first', 'twenty-second', 'twenty-third', 'twenty-fourth', 'twenty-fifth', 'twenty-sixth', 'twenty-seventh', 'twenty-eigth', 'twenty-ninth', 'thirtieth']
max_number = 91
card_length = 15

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
getPlayersNames(player, player_names, spare, ordinals)
numbers_to_n = list(range(1, max_number))

#Make the cards
card_numbers = [[] for counter in repeat(None, len(player_names))]
makeCards(card_length, card_numbers, len(player_names), max_number)
message_text = ''
for p in range(len(player_names)):
    l = ', '.join(map(str, card_numbers[p]))
    message_text += (player_names[p] + ', your numbers are: ' + l + '\n')
display_info = messagebox.askquestion('Final Question', 'Do you want it to be dispalyed when someone has a number in their card?')
messagebox.askquestion('Ready', message_text + 'Are you ready to continue?')

#Calling the numbers
display.create_text(245, 289, text='The chosen number is:', font=('Arial', 20))
chosen_num_disp = Label(display, text='', font=('Arial', 245))
chosen_num_disp.place(x=245, y=484, anchor='center')
tie_manager, player_ranking = callNumbers(numbers_to_n, player_names, card_numbers, ordinals, display_info)

#Who wins?
display.delete("all")
introLabel.config(text=f"{' '*100}\n" * 9)
if tie_manager[0] == 1:
    winner = 'winner is'
for second in range(5, -1, -1):
    chosen_num_disp.config(text=f' {second} ')
    main.update_idletasks()
    main.after(1000)
introLabel.config(text=f'The {winner}...', font=("Arial", 20))
introLabel.place(y=30, x=30)
chosen_num_disp.destroy()
winner_disp2 = Label(display, text=(', '.join(player_ranking[:tie_manager[0]])), font=('Arial', 20))
winner_disp2.place(x=220, y=30)
ordinals = ['1st', '2nd', '3rd', '4th', '5th', '6th', '7th', '8th', '9th', '10th', '11th', '12th', '13th', '14th', '15th', '16th', '17th', '18th', '19th', '20th', '21st', '22nd', '23rd', '24th', '25th', '26th', '27th', '28th', '29th', '30th']
for counter in range(len(tie_manager)):
    position_disp_text.append(f"{ordinals[counter]}: {', '.join(player_ranking[:tie_manager[0]])}")
    for counter in range(tie_manager[0]):
        player_ranking.remove(player_ranking[0])
    tie_manager.remove(tie_manager[0])
pos_disp = Label(display, text='\n'.join(position_disp_text), font=('Arial', 20), justify=LEFT)
pos_disp.place(y=60, x=30)
main.mainloop()
