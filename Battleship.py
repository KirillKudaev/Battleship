'''
Authors: Kirill Kudaev and Amanda Breneman
Instructor: John Broere
Program: Battleship
Course: CSCI 220
Date: 10/2/15

Description: This is a functioning battleship game that allows the user to place their ships manually or automatically and 
places computer's ships automatically. Four ships have to be placed: Aircraft Carrier (5 spaces), Battleship (4 spaces), 
Patrol Boat (3 spaces), Submarine (2 spaces). The game then alternates turns between the user and computer until someone wins,   
i.e. sinks all their opponents ships.

'''

import random   #provides access to random module
import time     #provides access to time module
import os       #provides a portable way of using operating system dependent functionality
import sys      #provides access to some variables used or maintained by the interpreter and to functions
                #that interact strongly with the interpreter


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Function: cls()
#
#   Pre: none
#
#   Post: the screen has been cleared
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def cls():
        os.system('cls' if os.name == 'nt' else 'clear')


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Function: printBoardTesting(myBoard)
#
#   Pre: myBoard has been declared
#
#   Post: the testing board has been printed to the screen
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def printBoardTesting(myBoard):
    for k in myBoard:
        print ' '.join(k)                           #for Testing. Clean output without any extra symbols


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Function: printBoard(myBoard)
#
#   Pre: myBoard has been declared
#
#   Post: the board has been printed to the screen in a neat style
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def printBoard(myBoard):

    rowDictionary = {1 : 'A', 2 : 'B', 3 : 'C', 4 :'D', 5 : 'E', 6 : 'F', 7 :'G', 8 : 'H', 9 : 'I', 10 : 'J'}

    print '    1   2   3   4   5   6   7   8   9   10'
    print

    iCount = 1

    for k in myBoard:
        print rowDictionary[iCount], ' ', ' | '.join(k), '|'
        print '   ========================================'
        iCount += 1


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Function: getCoordinates()
#
#   Pre: none
#
#   Post: the user's input for row,col have been returned
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def getCoordinates():
    
    userInput = raw_input('Please enter coordinates row,col (ex. A,1): ')
    userInput = userInput.split(',')

    #dictionary to hold the value for each corresponding letter
    rowDictionary = {'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5, 'G': 6, 'H': 7, 'I': 8, 'J': 9}

    row = rowDictionary[userInput[0].upper()]       #user enters a letter, either upper or lower case
    col = int(userInput[1]) - 1                     #user enters the column number - numbering starts at 1

    return (row, col)


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Function: getOrientation()
#
#   Pre: none
#
#   Post: the user's input for orientation has been returned
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def getOrientation():
    
    userInput = raw_input('Horizontal or vertical (v or h): ')

    return (userInput.lower())


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Function: testPlacement(board, shipLength, orientation, row, col)
#
#   Pre: board, shipLength, orientation, row, and col have been declared
#
#   Post: returns false if the ship placement is invalid (out of boundaries or overlaps another ship), otherwise true
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def testPlacement(board, shipLength, orientation, row, col):

    ########################################## Check boundaries of board #################################################

    if (col > 9 or col < 0):                        #check col of first element of the ship's place
        return False

    if (row > 9 or row < 0):                        #check row of first element of the ship's place
        return False

    #Add the shipLength to the column to see if the end of the ship fits on the board
    #If both the beginning and end of the ship fit on the board, then the whole ship fits on the board
    #Create temp variables to hold the value of the end of the ship
    col2 = col
    row2 = row

    if orientation == 'h':          
        col2 = col + shipLength - 1
    elif orientation == 'v':
        row2 = row + shipLength - 1

    if (col2 > 9 or col2 < 0):                      #check col of last element of the ship's place
        return False
    if (row2 > 9 or row2 < 0):                      #check row of last element of the ship's place
        return False

    ############################################# Check overlapping ships ################################################

    if orientation == 'h':                          #check if horizontal ships overlap
        for x in xrange(0,shipLength):              #loop through and check each section of the ship
            if board[row][col + x] != ' ':          #check if it is equal to '0'
                return False

    elif orientation == 'v':                        #check if vertical ships overlap
        for x in xrange(0,shipLength):              #loop through and check each section of the ship
            if board[row + x][col] != ' ':          #check if it is equal to '0'
                return False
    else:
        return False

    return True                                     #return true if it is a valid placement of the ship


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Function: testShootingCoordinates(row, col)
#
#   Pre: row and col have been declared
#
#   Post: if the space guessed is inside the boundaries of the board it returns true, else it returns false
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def testShootingCoordinates(row, col):

    if (col > 9 or col < 0):                        #check col of first element of the ship's place
        return False

    if (row > 9 or row < 0):                        #check row of first element of the ship's place
        return False

    return True


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Function: placeShip(board, name, shipLength, orientation, row, col)
#
#   Pre: board, name, shipLength, orientation, row, and col have been declared
#
#   Post: the ship has been placed on the player's board, otherwise it prints an error message (which should never happen)
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def placeShip(board, name, shipLength, orientation, row, col):

    if orientation == 'h':
        for c in xrange(0,shipLength):              #place ship horizontally
            board[row][col + c] = name
    elif orientation == 'v':
        for r in xrange(0,shipLength):              #place ship vertically
            board[row + r][col] = name
    else:   
        print 'Ship has not been placed'            #this should never print - just a precaution

    
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Function: Menu()
#
#   Pre: none
#
#   Post: the menu has been printed and returns the user's input of whether they want to auto-deploy their ship
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def Menu():

    print 'Welcome to Battleship!'                  #Print out the menu
    print
    print 'Ships available:'
    print '1 - Aircraft Carrier (5 spaces)'
    print '1 - Battleship       (4 spaces)'
    print '1 - Patrol Boat      (3 spaces)'
    print '1 - Submarine        (2 spaces)'
    print

    userInput = raw_input('Would you like to have your ships auto-deployed? y or n: ')      #read in user input

    while (userInput.lower() != 'y') and (userInput.lower() != 'n'):
        userInput = raw_input('Would you like to have your ships auto-deployed? y or n: ')  #read in user input again

    return userInput.lower()                        #returns the userInput


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Function: deployShips(autoDeployShips, userBoard)
#
#   Pre: autoDeployShips and userBoard have been declared
#
#   Post: a function has been called to deploy the user's ships either manually or automatically
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def deployShips(autoDeployShips, userBoard):

    if autoDeployShips == 'y':                      #auto deploy the ships
        autoDeploy(userBoard, 'p')
    elif autoDeployShips == 'n':                    #manually deploy ships
        manualDeploy(userBoard)


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Function: manualDeploy(emptyBoard)
#
#   Pre: emptyBoard has been declared
#
#   Post: the user's ships have been manually deployed based on the user's input
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def manualDeploy(emptyBoard):

    userBoard = emptyBoard                          #create and set userboard = emptyboard

    cls()                                           #clear screen

    ####Read in data and place first ship####
    printBoard(userBoard)                           #print userboard
    print
    print 'Deploy your: Aircraft Carrier'
    row, col = getCoordinates()                     #read in coordinates from user
    orientation = getOrientation()                  #get orientation

    while testPlacement(userBoard, 5, orientation, row, col) == False:
        cls()                                       #clear screen
        printBoard(userBoard)                       #print userboard
        print
        print "Invalid input - try again"
        row, col = getCoordinates()                 #read in coordinates from user
        orientation = getOrientation()              #get orientation

    placeShip(userBoard, 'A', 5, orientation, row, col)     #place ship

    printBoard(userBoard)                           #print userboard
    print                                           #print blank line for spacing
        
    ####Read in data and place second ship####
    cls()                                           #clear screen
    printBoard(userBoard)                           #print userboard
    print
    print 'Deploy your: Battleship'
    row, col = getCoordinates()                     #read in coordinates from user
    orientation = getOrientation()                  #get orientation
    cls()                                           #clear screen

    while testPlacement(userBoard, 4, orientation, row, col) == False:
        cls()                                       #clear screen
        printBoard(userBoard)                       #print userboard
        print
        print "Invalid input - try again"
        row, col = getCoordinates()                 #read in coordinates from user
        orientation = getOrientation()              #get orientation

    placeShip(userBoard, 'B', 4, orientation, row, col)     #place ship
    print 

    printBoard(userBoard)                           #print userboard
    print                                           #print blank line for spacing

    ####Read in data and place third ship####
    cls()                                           #clear screen
    printBoard(userBoard)                           #print userboard
    print
    print 'Deploy your: Patrol Boat'
    row, col = getCoordinates()                     #read in coordinates from user
    orientation = getOrientation()                  #get orientation

    while testPlacement(userBoard, 3, orientation, row, col) == False:
        cls()                                       #clear screen
        printBoard(userBoard)                       #print userboard
        print
        print "Invalid input - try again"
        row, col = getCoordinates()                 #read in coordinates from user
        orientation = getOrientation()              #get orientation

    placeShip(userBoard, 'P', 3, orientation, row, col)     #place ship

    printBoard(userBoard)                           #print userboard
    print                                           #print blank line for spacing

    ####Read in data and place fourth ship####
    cls()                                           #clear screen
    printBoard(userBoard)                           #print userboard
    print
    print 'Deploy your: Submarine'
    row, col = getCoordinates()                     #read in coordinates from user
    orientation = getOrientation()                  #get orientation

    while testPlacement(userBoard, 2, orientation, row, col) == False:
        cls()                                       #clear screen
        printBoard(userBoard)                       #print userboard
        print
        print "Invalid input - try again"
        row, col = getCoordinates()                 #read in coordinates from user
        orientation = getOrientation()              #get orientation

    placeShip(userBoard, 'S', 2, orientation, row, col)     #place ship

    printBoard(userBoard)                           #print userboard
    print

    print "All the user's ships have been deployed!"
    print 

    raw_input("Press ENTER to deploy the computer's ships!")    #have user hit enter to start playing game
    cls()


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Function: randomPosition()
#
#   Pre: none
#
#   Post: a random row, col, and orientation have been returned
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def randomPosition():

    row = random.randint(0,9)                       #initializes row with a random integer from 0 to 9
    col = random.randint(0,9)                       #initializes col with a random integer from 0 to 9

    horOrVert = random.randint(0,1)                 #initializes orientation with 'h' (if 0) or 'v' (if 1)
    if horOrVert == 0:
        orientation = 'h'
    elif horOrVert == 1:
        orientation = 'v'

    return (row, col, orientation)                  #returns all 3 variables


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Function: autoDeploy(emptyBoard, player)
#
#   Pre: emptyBoard and player have been declared
#
#   Post: the ships of the player sent in have been auto-deployed
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def autoDeploy(emptyBoard, player):

    board = emptyBoard                              #create and set board = emptyboard

    row, col, orientation = randomPosition()        #sets row, column and orientation of the ship to random values

    while testPlacement(board, 5, orientation, row, col) == False: #if ship can't be placed
        row, col, orientation = randomPosition()    #sets row, column and orientation of the ship to random values

    placeShip(board, 'A', 5, orientation, row, col) #place the ships
        
    #######Read in data and place second ship
    row, col, orientation = randomPosition()        #sets row, column and orientation of the ship to random values

    while testPlacement(board, 5, orientation, row, col) == False: #if ship can't be placed
        row, col, orientation = randomPosition()    #sets row, column and orientation of the ship to random values

    placeShip(board, 'B', 4, orientation, row, col) #place the ships

    ########Read in data and place third ship
    row, col, orientation = randomPosition()        #sets row, column and orientation of the ship to random values

    while testPlacement(board, 5, orientation, row, col) == False: #if ship can't be placed
        row, col, orientation = randomPosition()    #sets row, column and orientation of the ship to random values


    placeShip(board, 'P', 3, orientation, row, col) #place the ships

    ########Read in data and place fourth ship
    row, col, orientation = randomPosition()        #sets row, column and orientation of the ship to random values

    while testPlacement(board, 5, orientation, row, col) == False: #if ship can't be placed
        row, col, orientation = randomPosition()    #sets row, column and orientation of the ship to random values


    placeShip(board, 'S', 2, orientation, row, col) #place the ships

    if player == 'p':                               #print message saying user fleet has been deployed
        print
        print "User's fleet being deployed:"
        print
        print 'Deploying Aircraft Carrier...'
        print 'Deploying Battleship...'
        print 'Deploying Patrol Boat...'
        print 'Deploying Submarine...'
        print
        print "User's fleet has been deployed."
        print
        raw_input("Press ENTER to continue.")
        cls() 

    elif player == 'c':                             #print message saying computer fleet has been deployed
        print
        print "Computer's fleet being deployed:"
        print
        print 'Deploying Aircraft Carrier...'
        print 'Deploying Battleship...'
        print 'Deploying Patrol Boat...'
        print 'Deploying Submarine...'
        print
        print "Computer's fleet has been deployed!"
        print
        raw_input("Press ENTER to continue.") 
        cls() 


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Function: playGame(userBoard, compBoard, compMaskedBoard)
#
#   Pre: userBoard, compBoard, compMaskedBoard have been declared
#
#   Post: the user and computer have taken turns until someone has won
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def playGame(userBoard, compBoard, compMaskedBoard):

    rowDictionary = {1 : 'A', 2 : 'B', 3 : 'C', 4 :'D', 5 : 'E', 6 : 'F', 7 :'G', 8 : 'H', 9 : 'I', 10 : 'J'}

    #variable pool for the size of the ships
    A = 5           #Aircraft Carrier
    Acomp = 5
    B = 4           #Battleship
    Bcomp = 4
    P = 3           #Patrol Boat
    Pcomp = 3
    S = 2           #Submarine
    Scomp = 2

    while (A + B + P + S != 0) and (Acomp + Bcomp + Pcomp + Scomp != 0):    #run loop while no one has won yet

        #####Player's turn: shoots at the computer's ships#####

        bFlagUser = False

        while bFlagUser == False:                       #repeat loop while input is invalid
            #printBoard(compBoard)                      #TESTING
            #print
            print 'Computer Board:'                     #print the computer's board for the player to shoot at
            printBoard(compMaskedBoard)
            print

            row, col = getCoordinates()                 #read in coordinates from user

            while testShootingCoordinates(row, col) == False:   #while coordinates are invalid, go through loop
                cls()                                   #clear screen
                print 'Computer Board:'  
                printBoard(compMaskedBoard)             #print computer board   
                print
                print "Invalid input - try again"
                row, col = getCoordinates()             #read in coordinates from user

            #Check spaces on computer board
            if compBoard[row][col] == ' ':              #space is empty - print *
                compBoard[row][col] = '*'
                compMaskedBoard[row][col] = '*'
                print                                   #print computer board with appropriate spacing
                print 'Computer Board:'
                printBoard(compMaskedBoard)
                print      
                print 'Sorry, ' + rowDictionary[row + 1] + ',' + str(col + 1) + ' is a miss'
                bFlagUser = True                        #since user entered valid input, set bFlagUser to true

            elif compBoard[row][col] == 'A':            #space has part of the aircraft carrier - print $
                compBoard[row][col] = '$'
                compMaskedBoard[row][col] = '$'
                Acomp = Acomp - 1
                print                                   #print computer board with appropriate spacing
                print 'Computer Board:'
                printBoard(compMaskedBoard)
                print 
                print rowDictionary[row + 1] + ',' + str(col + 1) + ' is a hit'
                if Acomp == 0:
                    print 'The Aircraft Carrier was sunk.'
                bFlagUser = True                        #since user entered valid input, set bFlagUser to true

            elif compBoard[row][col] == 'B':            #space has part of the battleship - print $
                compBoard[row][col] = '$'
                compMaskedBoard[row][col] = '$'
                Bcomp = Bcomp - 1
                print                                   #print computer board with appropriate spacing
                print 'Computer Board:'
                printBoard(compMaskedBoard)
                print 
                print rowDictionary[row + 1] + ',' + str(col + 1) + ' is a hit'
                if Bcomp == 0:
                    print 'The Battleship was sunk.'
                bFlagUser = True                        #since user entered valid input, set bFlagUser to true

            elif compBoard[row][col] == 'P':            #space has part of the patrol boat - print $
                compBoard[row][col] = '$'
                compMaskedBoard[row][col] = '$'
                Pcomp = Pcomp - 1
                print                                   #print computer board with appropriate spacing
                print 'Computer Board:'
                printBoard(compMaskedBoard)
                print 
                print rowDictionary[row + 1] + ',' + str(col + 1) + ' is a hit'
                if Pcomp == 0:
                    print 'The Patrol Boat was sunk.'
                bFlagUser = True                        #since user entered valid input, set bFlagUser to true

            elif compBoard[row][col] == 'S':            #space has part of the submarine - print $
                compBoard[row][col] = '$'
                compMaskedBoard[row][col] = '$'
                Scomp = Scomp - 1
                print                                   #print computer board with appropriate spacing
                print 'Computer Board:'
                printBoard(compMaskedBoard)
                print 
                print rowDictionary[row + 1] + ',' + str(col + 1) + ' is a hit'
                if Scomp == 0:
                    print 'The Submarine was sunk.'
                bFlagUser = True                        #since user entered valid input, set bFlagUser to true

            elif compBoard[row][col] == '*':            #space has already been guessed
                print 'You have already guessed that'
                raw_input("Press ENTER and try again")

            elif compBoard[row][col] == '$':            #space has already been guessed
                print 'You have already guessed that'
                raw_input("Press ENTER and try again.")

        raw_input("Press ENTER to end the user's turn") #clear screen and go on to computer's turn
        cls() 


        ####Computer's turn: shoots at player's ships####

        bFlagComputer = False

        if (A + B + P + S != 0) and (Acomp + Bcomp + Pcomp + Scomp != 0):   #only do comp turn if no one has won yet

            while bFlagComputer == False:
                compRow, compCol, dummyVar = randomPosition()   #obtain random numbers for the computer's shot

                if userBoard[compRow][compCol] == ' ':      #space is empty - print *
                    userBoard[compRow][compCol] = '*'
                    print                                   #print userboard with spacing
                    print 'User Board:'
                    printBoard(userBoard)
                    print rowDictionary[compRow + 1] + ',' + str(compCol + 1) + ' is a miss'
                    bFlagComputer = True                    #since comp entered valid input, set bFlagComputer to true

                elif userBoard[compRow][compCol] == 'A':    #space has part of the aircraft carrier - print $
                    userBoard[compRow][compCol] = '$'
                    A = A - 1
                    print                                   #print userboard with spacing
                    print 'User Board:'
                    printBoard(userBoard)
                    print rowDictionary[compRow + 1] + ',' + str(compCol + 1) + ' is a hit'
                    if A == 0:
                        print 'The computer has sunk your Aircraft Carrier.'
                    bFlagComputer = True                    #since comp entered valid input, set bFlagComputer to true

                elif userBoard[compRow][compCol] == 'B':    #space has part of the battleship - print $
                    userBoard[compRow][compCol] = '$'
                    B = B - 1
                    print                                   #print userboard with spacing
                    print 'User Board:'
                    printBoard(userBoard)
                    print rowDictionary[compRow + 1] + ',' + str(compCol + 1) + ' is a hit'
                    if B == 0:
                        print 'The computer has sunk your Battleship.'
                    bFlagComputer = True                    #since comp entered valid input, set bFlagComputer to true

                elif userBoard[compRow][compCol] == 'P':    #space has part of the patrol boat - print $
                    userBoard[compRow][compCol] = '$'
                    P = P - 1
                    print                                   #print userboard with spacing
                    print 'User Board:'
                    printBoard(userBoard)
                    print rowDictionary[compRow + 1] + ',' + str(compCol + 1) + ' is a hit'
                    if P == 0:
                        print 'The computer has sunk your Patrol Boat.'
                    bFlagComputer = True                    #since comp entered valid input, set bFlagComputer to true

                elif userBoard[compRow][compCol] == 'S':    #space has part of the submarine - print $
                    userBoard[compRow][compCol] = '$'
                    S = S - 1
                    print                                   #print userboard with spacing
                    print 'User Board:'
                    printBoard(userBoard)
                    print rowDictionary[compRow + 1] + ',' + str(compCol + 1) + ' is a hit'
                    if S == 0:
                        print 'The computer has sunk your Submarine.'
                    bFlagComputer = True                    #since comp entered valid input, set bFlagComputer to true

                raw_input("Press ENTER to end the computer's turn.") #clear screen and go on to computer's turn
                cls() 



        win(A, Acomp, B, Bcomp, P, Pcomp, S, Scomp)          #call win() to see who has won


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Function: win(A, Acomp, B, Bcomp, P, Pcomp, S, Scomp)
#
#   Pre: A, Acomp, B, Bcomp, P, Pcomp, S, and Scomp have been declared
#
#   Post: the winner has been printed to the screen
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def win(A, Acomp, B, Bcomp, P, Pcomp, S, Scomp):

    if (A + B + P + S == 0):                        #if all of the user ships have been sunk, comp wins
        print 'Computer won!'
    elif (Acomp + Bcomp + Pcomp + Scomp == 0):      #if all of the comp ships have been sunk, user wins
        print 'User won!'


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Function: main()
#
#   Pre: Menu, deployShips and autoDeploy functions have been initialized
#
#   Post: initializes user and computer boards with "O"s, prints out the menu, lets the user
#   set ships either automatically or manually. After that, it automatically sets the ships for computer board. 
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def main():

    sys.stdout.write("\x1b[8;{rows};{cols}t".format(rows=26, cols=86))  #change the size of the window


    #bPlayAgain = True

    #while bPlayAgain == True:

    userBoard = []                                  #create the user's board
    for i in range(10):                             #initializing array 10x10 with ' '
        userBoard.append([' '] * 10)

    compBoard = []                                  #create the computer's board that holds the placement of the ships
    for i in range(10):                             #initializing array 10x10 with ' '
        compBoard.append([' '] * 10)

    compMaskedBoard = []                            #create the computer's masked board that will be used for printing
    for i in range(10):                             #initializing array 10x10 with ' '
        compMaskedBoard.append([' '] * 10)

    userInput = Menu()                              #take in the user input - automatically or manually deploy ships

    cls()                                           #clear screen

    #Call deployShips to have ships deployed
    if userInput == 'y':                            #user wants to automatically deploy ships
        deployShips('y', userBoard)
    elif userInput == 'n':                          #user want to manually deploy ships
        deployShips('n', userBoard)

    autoDeploy(compBoard, 'c')                      #call autodeploy to deploy the computer's ships
    
    raw_input('Press ENTER to start the game!')     #have user hit enter to start playing game
    cls()    

    playGame(userBoard, compBoard, compMaskedBoard) #call playGame to start playing the actual game


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Call to run the main program
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
if __name__=='__main__':
    random.seed(time.time())
    cls()
    main()
    raw_input('Press ENTER to quit the program.')
    cls()