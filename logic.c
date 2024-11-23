#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#include "minesweeper.h"

#define DEBUG 0



// COPIED ESHA'S CODE INTO HERE JUST TO GENERATE TESTING INPUT
int surroundingMines(int rows, int columns, char **minefield, int i, int j) { 
	
	int surrounding_mines = 0; 

	if (minefield[i][j] != 'X') {
				
		if (i < (rows - 1) && minefield[i+1][j] == 'X') {
			surrounding_mines++; 
		}	

		if (i > 0 && minefield[i-1][j] == 'X') { 
			surrounding_mines++;
		}
	
		if (j < (columns - 1) && minefield[i][j+1] == 'X') {
                	surrounding_mines++;
            	}

		if (j > 0 && minefield[i][j-1] == 'X') {
                	surrounding_mines++;
		}

		if (i > 0 && j < (columns - 1) && minefield[i-1][j+1] == 'X') { 
                	surrounding_mines++;
            	}
			
		if (i < (rows - 1) && j < (columns - 1) && minefield[i+1][j+1] == 'X') {
                	surrounding_mines++;
            	}

		if (i > 0 && j > 0 && minefield[i-1][j-1] == 'X') {
			surrounding_mines++;
            	}

		if (j > 0 && i < (rows - 1) && minefield[i+1][j-1] == 'X') {
                	surrounding_mines++;
		}
	}	

	return surrounding_mines; 
}

char** generateMinefield(int rows, int columns, int mines) { 	
	
	char** minefield = (char**)malloc(rows * sizeof(char*));
		for (int i = 0; i < rows; i++) {
			minefield[i] = (char*)malloc(columns * sizeof(char));
    	}
	
	for (int i = 0; i < rows; i++) {
        	for (int j = 0; j < columns; j++) {
            		minefield[i][j] = '.';
        }
    }

	int mines_placed = 0; 

	while (mines_placed < mines) { 
		int i = rand() % rows;
		int j = rand() % columns;
		
		if (minefield[i][j] != 'X') { 
			minefield[i][j] = 'X'; 					
			mines_placed++; 
		}
	}

	return minefield;
}

char** generateNumberMap(int rows, int columns, char **minefield) { 
	
	char** numberMap = (char**)malloc(rows * sizeof(char*));
    		for (int i = 0; i < rows; i++) {
        		numberMap[i] = (char*)malloc(columns * sizeof(char));
    		}

	for (int i = 0; i < rows; i++) { 
		for (int j = 0; j < columns; j++) { 
			if (minefield[i][j] != 'X') { 
				int touching_mines = surroundingMines(rows, columns, minefield, i, j);
				if (touching_mines == 0) { 
    					numberMap[i][j] = '0'; // change to '0' from ' '
				} else {
					numberMap[i][j] = '0' + touching_mines;    			
				}
			} else { 
				numberMap[i][j] = 'X';
		}
	}
}
	return numberMap;
}

char** generateGameboard(int rows, int columns) { 

    char** gameboard = malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        gameboard[i] = malloc(columns * sizeof(char));
        for (int j = 0; j < columns; j++) {
            gameboard[i][j] = '.';
        }
    }
    return gameboard;
}

// END OF COPIED CODE FROM ESHA





/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| digSquare - Recursively ripple reveals unrevealed spaces on the game board.
|               If the [r][c] indicated square on board is unrevealed (indicated by '.' character) replace it with the number of adjacent mines, numbermap[r][j].
|               Then, if there are 0 adjacent mines (to that square), repeat the reveal process at all 8 adjacent squares on board (making sure staying within bounds of board).
|
| Arguments: r = row index of targetted square for reveal
|            c = column index of targetted square for reveal
|            rows = total number of rows in the board (and numbermap)
|            columns = total number of columns in the board (and numbermap)
|            ** board = pointer to 2D array holding the player-shown game board
|            ** numbermap = pointer to 2D array that holds the number of mines adjacent to each square
|            *squares_revealed = scoring metric, increments score counter each time a new square is revealed
|
| Pointers / Side Effects: *squares_revealed - incremented every time an unrevealed square is revealed
|                          ** board - board updated with revealed number(s) from digSquare or updated with added/removed flags (from flagging process)
| Outputs: None
| Returns: None
| Functions Called: digSquare - recursively calls itself to ripple reveal multiple squares
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
void digSquare(int r, int c, int rows, int columns, char ** board, char ** numbermap, int * squares_revealed) {

    if (board[r][c] == '.') {  // if unrevealed reveal square
        board[r][c] = numbermap[r][c];
        (*squares_revealed)++; // scoring metric increment
    }
    else { // skip if not '.' (already revealed)
        if (DEBUG) {
        printf("[%d][%d] not '.\'\tSkipping\n", r, c); // for diagnosing
        }
        return; // skips revealing steps
    }
    

    if (DEBUG) { // For diagnosing
        printf("\nDEV - Printing Board:\n");
        for (int i = 0; i < rows; i++) { // print board
                for (int j = 0; j < columns; j++) {
                        printf("%c ", board[i][j]); 
            }
            printf("\n");
        }
    }

    if (numbermap[r][c] == '0') { // if revealed square was a 0 (no adjacent mines), reveal all 8 adjacent squares
        if (DEBUG) {
            printf("Ripple Revealing around [%d][%d]\n", r, c);
        }

        // 8 if statements, 1 for each adjacent square
        // checks if within bounds of array
        // if yes, then recursively call this function on that square
        if (r > 0 && c > 0) { // NW diagonal
            if (DEBUG) {
                printf("Looking NW from [%d][%d] at [%d][%d]\n", r, c, r-1, c-1);
            }
            digSquare(r-1, c-1, rows, columns, board, numbermap, squares_revealed);
        }	

        if (r > 0) { // N face
            if (DEBUG) {
                printf("Looking N from [%d][%d] at [%d][%d]\n", r, c, r-1, c);
            }
            digSquare(r-1, c, rows, columns, board, numbermap, squares_revealed);
        }

        if (r > 0 && c < (columns-1)) { // NE diagonal
            if (DEBUG) {
                printf("Looking NE from [%d][%d] at [%d][%d]\n", r, c, r-1, c+1);
            }
            digSquare(r-1, c+1, rows, columns, board, numbermap, squares_revealed);
        }

        if (c < (columns-1)) { // E face
            if (DEBUG) {
                printf("Looking E from [%d][%d] at [%d][%d]\n", r, c, r, c+1);
            }
            digSquare(r, c+1, rows, columns, board, numbermap, squares_revealed);
        }

        if (r < (rows-1) && c < (columns-1)) { // SE diagonal
            if (DEBUG) {
                printf("Looking SE from [%d][%d] at [%d][%d]\n", r, c, r+1, c+1);
            }
            digSquare(r+1, c+1, rows, columns, board, numbermap, squares_revealed);
        }
        
        if (r < (rows-1)) { // S face
            if (DEBUG) {
                printf("Looking S from [%d][%d] at [%d][%d]\n", r, c, r+1, c);
            }
            digSquare(r+1, c, rows, columns, board, numbermap, squares_revealed);
        }
        
        if (r < (rows-1) && c > 0) { // SW diagonal
            if (DEBUG) {
                printf("Looking SW from [%d][%d] at [%d][%d]\n", r, c, r+1, c-1);
            }
            digSquare(r+1, c-1, rows, columns, board, numbermap, squares_revealed);
        }
        
        if (c > 0) { // W face
            if (DEBUG) {
                printf("Looking W from [%d][%d] at [%d][%d]\n", r, c, r, c-1);
            }
            digSquare(r, c-1, rows, columns, board, numbermap, squares_revealed);
        }
    }

}



/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| gameEndCheck - determines if player has won game (if every mine has been flagged and there are no additional incorrect flags)
|
| Arguments: rows = total number of rows in the board (and minefield)
|            columns = total number of columns in the board (and minefield)
|            ** board = pointer to 2D array holding the player-shown game board
|            ** minefield = pointer to 2D array that holds the positions of the mines
|            mines = number of mines in play
|            * flags = the number of flags the user has placed
|
| Pointers / Side Effects: None
| Outputs: None
| Returns: None
| Functions Called: /////////////////////////////////// DHRUV FUCTION --> win
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
void gameEndCheck(int rows, int columns, char ** board, char ** minefield, int mines, int * flags) {
    if (DEBUG) {
        printf("IN GAME END CHECK: end of game check:\tmines:%d\tflags%d\n", mines, *flags);
    }

    if (mines == *flags) { // same number of flags as mines, assume flag char is 'F'
        if (DEBUG) {
            printf("same number of mines as flags\n");
        }

        int correct_flags = 0;
        for (int i = 0; i < rows; i++) {  // parses through the whole array
                for (int j = 0; j < columns; j++) { 
                    if (minefield[i][j] == 'X' && board[i][j] == 'F') { // if mine maps to flag
                        correct_flags++; // increase counter
                    }
            }
        } 
        if (correct_flags == mines) { // if every flag maps exactly to a mine
            printf("END OF GAME - WIN\n"); /////////////////////////////////// DHRUV FUCTION --> win
            //scoreboard
        }
    }

}

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| processMove - processes the users move based on parameters user inputted in ////////////////// READ INPUT FUNCTION
|               depending on user input, handles the flagging process or calls digSquare to reveal the particular square
|
| Arguments: specified_row = the row index of the square the user wants to modify
|            specified_column = the column index of the square the user wants to modify
|            change = indicates the action the user wishes to perform on the targetted square (0 for dig, 1 for flag)
|            row = total number of rows in the board (and minefield and numbermap)
|            columns = total number of columns in the board (and minefield and numbermap)
|            ** board = pointer to 2D array holding the player-shown game board
|            ** minefield = pointer to 2D array that holds the positions of the mines
|            ** numbermap = pointer to 2D array that holds the number of mines adjacent to each square
|            mines = number of mines in play
|            * flags = the number of flags the user has placed
|            * squares_revealed = the number of flags the user has placed
|
| Pointers / Side Effects: * flags - counter for number of flags user has placed, incremented or decremented by flagging process
| Returns: None
| Functions Called: digSquare - if user specifies dig (change==0) digSquare is called on [specified_row][specified_column]
|                   gameEndCheck - calls at end of the flag processing to check if user has now won the game
| /////////////////////////////////// DHRUV FUCTION --> lose
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
void processMove(int specified_row, int specified_column, int change, int rows, int columns, char ** board, char ** minefield, char ** numbermap, int mines, int * flags, int * squares_revealed) {
    
    if (change == 0) { // 0 for dig
        if (numbermap[specified_row][specified_column] == 'X') { // if dug up a mine
            printf("TRIGGER END OF GAME - LOSE\n"); /////////////////////////////////// DHRUV FUCTION --> lose
            // trigger scoreboard
        }

        else { // if didn't dig a mine
            printf("Calling Dig Square\n"); 
            digSquare(specified_row, specified_column, rows, columns, board, numbermap, squares_revealed);
        }
    }


    if (change == 1) { // 1 is flag
        if (board[specified_row][specified_column] == '.') { // if space was unmarked
            board[specified_row][specified_column] = 'F'; // flag it
            *flags+=1;
        }
        else if (board[specified_row][specified_column] == 'F') { // if space was flagged
            board[specified_row][specified_column] = '.'; // remove it
            *flags-=1;
        }

        if (DEBUG) { // for diagnosing
            printf("BEFORE GAME END CHECK:\tmines:%d\tflags%d\n", mines, *flags);
        }

        gameEndCheck(rows, columns, board, minefield, mines, flags); // check if game ended due to flagging change
    }

}




// MY MAIN WILL NOT BE IN FINAL RELEASE, IT IS PURELY FOR TESTING PURPOSES OF ALL logic.c FUCTIONS

/*
int main() { 
    
    int rows = 4;
    int columns = 5;
	
    // this all just to hard code array for testing
    char minefield_array[4][5] = { {'X', '.', '.', '.', '.'}, {'X', '.', '.', '.', '.'}, {'.', '.', '.', '.', '.'}, {'.', '.', '.', '.', 'X'} };

    char **minefield = malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        minefield[i] = minefield_array[i];
    }
    // end of hard coding array
    
    
    // generate boards
    char ** numbermap = generateNumberMap(4, 5, minefield);
    char ** board = generateGameboard(4, 5);



    if (DEBUG) { // make sure that minefield and numbermap generated properly
        printf("DEV - Printing Minefield:\n");
        for (int i = 0; i < rows; i++) { // printing for dev purposes - remove later  
                for (int j = 0; j < columns; j++) { 
                    printf("%c ", minefield[i][j]);
            }
            printf("\n");
        }

        printf("\nDEV - Printing NumberMap:\n");
        for (int i = 0; i < rows; i++) { // only for dev testing - need to print only the square player selects 
                for (int j = 0; j < columns; j++) {
                        printf("%c ", numbermap[i][j]);
            }
            printf("\n");
        }
    }

    printf("TESTING MOVE PROCESSING\n");
    int flags = 0;
    int squares_revealed = 0;
    printf("\n\n\ntest step 1:\n");
    processMove(2, 2, 0, 4, 5, board, minefield, numbermap, 3, &flags, &squares_revealed);
    printf("\n\n\ntest step 2:\n");
    processMove(3, 4, 1, 4, 5, board, minefield, numbermap, 3, &flags, &squares_revealed);
    printf("\n\n\ntest step 4:\n");
    processMove(0, 0, 1, 4, 5, board, minefield, numbermap, 3, &flags, &squares_revealed);
    printf("\n\n\ntest step 5:\n");
    processMove(1, 0, 1, 4, 5, board, minefield, numbermap, 3, &flags, &squares_revealed);


    printf("Modify Board Tests completed\n\nPrinting Board:\n");

    for (int i = 0; i < rows; i++) { // only for dev testing
            for (int j = 0; j < columns; j++) {
                    printf("%c ", board[i][j]);
        }
        printf("\n");
    }


    printf("Squares Revealed: %d of %d total.\n", squares_revealed, rows*columns);




    printf("End of testing: Freeing all arrays.\n");
    free(minefield);
    free(numbermap);
    free(board);
    printf("End of testing: All arrays freed.\n");
}
*/