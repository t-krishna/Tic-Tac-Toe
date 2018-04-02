import os

#TicTacToe: minimax

#Began: 10/14/2016
#Completed: 10/24/2016
#AI that uses the minimax algorithm to calculate all possible moves and choose the best one
#this AI will never lose. It will either draw with the player or win

#defining global variables
labelsForBoard = [1, 2, 3, 4, 5, 6, 7, 8, 9] #the game board
choice = 0

#draw board function
def draw_board(label:list)-> None:
	'prints out the board'
	print()
	z = 0
	for i in range(3):
		for j in range(3):
			print(label[z], end=" ")
			z = z + 1
		print()



#checking win conditions function (score system) and if game is over
def win(label:list)-> tuple:
	'Checks win conditions and returns a tuple of if the game is over and the score'
	

	if ((label[0] == label[1] == label[2] == player) or
		(label[3] == label[4] == label[5] == player) or
		(label[6] == label[7] == label[8] == player) or
		(label[0] == label[3] == label[6] == player) or
		(label[1] == label[4] == label[7] == player) or
		(label[2] == label[5] == label[8] == player) or
		(label[0] == label[4] == label[8] == player) or
		(label[2] == label[4] == label[6] == player)):
		x = (True, -10) #True = Game is over, -10 = score
		return(x)

	elif ((label[0] == label[1] == label[2] == cpu) or
		(label[3] == label[4] == label[5] == cpu) or
		(label[6] == label[7] == label[8] == cpu) or
		(label[0] == label[3] == label[6] == cpu) or
		(label[1] == label[4] == label[7] == cpu) or
		(label[2] == label[5] == label[8] == cpu) or
		(label[0] == label[4] == label[8] == cpu) or
		(label[2] == label[4] == label[6] == cpu)):
		x = (True, 10) #True = Game is over, 10 = score
		return(x)

	else:
		counter = 0
		for i in range(9):
			if((label[i] == player) or (label[i] == cpu)):
				counter = counter + 1
				if (counter == 9):
					x = (True, 0) #True = Game is over, 0 = score
					return(x)
		x = (False, 0) #False = Game is not over, 0 = score
		return(x)



#check if the player inputed an int for their move
def is_int(s:int)-> bool:
	'Checks if the player input is an int and returns a bool for the player_turn function'
	try:
		int(s)
		return True
	except ValueError:
		return False

#player turn function
def player_turn(label:list)-> list:
	'Places a player marker on their selected tile if it is available'
	while(True):
		selectedTile = input("Your move: ")
		if (is_int(selectedTile) == True):
			selectedTile = int(selectedTile)
			if ((selectedTile > 0) and (selectedTile < 10) and 
				(label[selectedTile - 1] != player) and (label[selectedTile - 1] != cpu)):
				label[selectedTile - 1] = player
				return label
			else:
				print("invalid input")
		else:
			print("invalid input")



#switches between player and cpu
def switch(currentPlayer: str)-> str:
	'switches between player and cpu markers for the minimax function'
	if currentPlayer == cpu:
		return player
	else:
		return cpu

#obtains the index for the best move
def minimax(label:list, currentPlayer:str)-> int:
	'Calculates the scores for every calculated move. Stores the move in choice variable'
	global choice
	if win(label)[0] == True:
		return win(label)[1]
	scores = []
	moves = []

	for i in range(len(label)):
		if ((label[i] != cpu) and (label[i] != player)):
			possibleGame = list(label)
			possibleGame[i] = currentPlayer
			x = minimax(possibleGame, switch(currentPlayer))
			if (x == None):
				x = 0
			scores.append(x)
			moves.append(i)

	if (currentPlayer == cpu):
		maxScoreIndex = scores.index(max(scores))
		choice = moves[maxScoreIndex]
		return scores[maxScoreIndex]
	else:
		minScoreIndex = scores.index(min(scores))
		choice = moves[minScoreIndex]
		return scores[minScoreIndex]

#impliments the choice move obtained during the minimax funtion onto the board
def cpu_turn(label:list, currentPlayer:str)-> list:
	'Returns the list with the choice move obtained during the minimax function'
	minimax(label, currentPlayer)
	label[choice] = currentPlayer
	return label



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

#if the player chose X then they go first
if (player == 'X'):
	draw_board(labelsForBoard)
	player_turn(labelsForBoard)
	cpu_turn(labelsForBoard, cpu)
	draw_board(labelsForBoard)
else:
	cpu_turn(labelsForBoard, cpu)
	draw_board(labelsForBoard)

#the game loop after specifying the first move
while(win(labelsForBoard)[0] == False):
	player_turn(labelsForBoard)

	if (win(labelsForBoard)[0] == False):
		cpu_turn(labelsForBoard, cpu)

	#checking the win conditions. If game not over just draw board
	if (win(labelsForBoard)[0] == True): #checking if the game is over
		if (win(labelsForBoard)[1] == 0): 
			print("\nDRAW")
			draw_board(labelsForBoard)
		elif (win(labelsForBoard)[1] == 10):
			print("\nYOU LOSE")
			draw_board(labelsForBoard)
		else:
			print("\nYOU WON? IMPOSSIBLE!!!")
			draw_board(labelsForBoard)
	else:
		draw_board(labelsForBoard)
