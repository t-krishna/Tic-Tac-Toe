import os

#TicTacToe: minimax

#Began: 10/14/2016
#Completed: Work in progress
#Goal: AI that uses the minimax algorithm to become the perfect player

#defining global variables
labelsForBoard = [1, 2, 3, 4, 5, 6, 7, 8, 9]
gameOver = False
winState = ""

#draw board function
def draw_board():
	print()
	z = 0
	for i in range(3):
		for j in range(3):
			print(labelsForBoard[z], end=" ")
			z = z + 1
		print()



#checking win conditions function (score system)
def win(label):
	counter = 0
	for i in range(9):
		if((label[i] == player) or (label[i] == cpu)):
			counter = counter + 1
			if (counter == 9):
				x = (True, 0)
				return(x)

	if ((label[0] == label[1] == label[2] == player) or
		(label[3] == label[4] == label[5] == player) or
		(label[6] == label[7] == label[8] == player) or
		(label[0] == label[3] == label[6] == player) or
		(label[1] == label[4] == label[7] == player) or
		(label[2] == label[5] == label[8] == player) or
		(label[0] == label[4] == label[8] == player) or
		(label[2] == label[4] == label[6] == player)):
		x = (True, -10)
		return(x)

	elif ((label[0] == label[1] == label[2] == cpu) or
		(label[3] == label[4] == label[5] == cpu) or
		(label[6] == label[7] == label[8] == cpu) or
		(label[0] == label[3] == label[6] == cpu) or
		(label[1] == label[4] == label[7] == cpu) or
		(label[2] == label[5] == label[8] == cpu) or
		(label[0] == label[4] == label[8] == cpu) or
		(label[2] == label[4] == label[6] == cpu)):
		x = (True, 10)
		return(10)

	else:
		return(False, 0)

#checking draw conditions function





#check if the player inputed an int for their move
def is_int(s):
	try:
		int(s)
		return True
	except ValueError:
		return False

#player turn function
def player_turn(label):
	while(True):
		selectedTile = input("Your move: ")
		if (is_int(selectedTile) == True):
			selectedTile = int(selectedTile)
			if ((selectedTile > 0) and (selectedTile < 10) and 
				(label[selectedTile - 1] != player) and (label[selectedTile - 1] != cpu)):
				label[selectedTile - 1] = player
				break
			else:
				print("invalid input")
		else:
			print("invalid input")



def cpu_turn(label):
	print("[insert AI here]")


#the main program
print("Welcome to Tic-Tac-Toe")

#Player chooses if they want to be X(goes first) or O(goes second)
while(True):
	iconChoice = input("Would you like to be X or O? ")
	if ((iconChoice == 'X') or (iconChoice == 'x')):
		player = 'X'
		cpu = 'O'
		break
	elif ((iconChoice == 'O') or (iconChoice == 'o')):
		player = 'O'
		cpu = 'X'
		break
	else:
		print("Invalid input, please try again.")

#the game loop
while(win(labelsForBoard)[0] == False):
	draw_board()
	player_turn(labelsForBoard)
	if (win(labelsForBoard)[0] == False):
		cpu_turn(labelsForBoard)
	if (win(labelsForBoard)[0] == True):
		if (win(labelsForBoard)[1] == 0):
			print("\nDRAW")
			draw_board()
		elif (win(labelsForBoard)[1] == 10):
			print("\nYOU LOSE")
			draw_board()
		else:
			print("\nYOU WIN")
			draw_board()
