#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int surroundingMines(int rows, int columns, char minefield[rows][columns], int i, int j) { 
	
	int surrounding_mines = 0; 

	if (minefield[i][j] != 'X') {
				
<<<<<<< HEAD
		if (minefield[i+1][j] == 'X' && ((i+1) < rows)) { 
=======
		if (i < (rows - 1) && minefield[i+1][j] == 'X') {
>>>>>>> origin/main
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

void generateMinefield(int rows, int columns, int mines, char minefield[rows][columns]) { 
	
	int mines_placed = 0; 

	while (mines_placed < mines) { 
		int i = rand() % rows;
		int j = rand() % columns;
		
		if (minefield[i][j] != 'X') { 
			minefield[i][j] = 'X'; 					
			mines_placed++; 
		}
	}

}

void generateNumberMap(int rows, int columns, char minefield[rows][columns], char playerBoard[rows][columns]) { 
	for (int i = 0; i < rows; i++) { 
		for (int j = 0; j < columns; j++) { 
			if (minefield[i][j] != 'X') { 
				int touching_mines = surroundingMines(rows, columns, minefield, i, j);
				if (touching_mines == 0) { 
    					playerBoard[i][j] = ' ';
				} else {
					playerBoard[i][j] = '0' + touching_mines;    			
				}
			}
			else { 
				playerBoard[i][j] = 'X';
			}
		}
	}

	for (int i = 0; i < rows; i++) { // only for dev testing - need to print only the square player selects 
        	for (int j = 0; j < columns; j++) {
            		printf("%c ", playerBoard[i][j]);
        }
        printf("\n");
    }
}

void board(int rows, int columns, char minefield[rows][columns]) { 
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
	            minefield[i][j] = '.';
	        }
	    }
}

int main() { 

	srand(time(NULL)); 

	int rows = 4; // for dev testing - Angel's code
    	int columns = 4;
    	int mines = 4;
	
	char minefield[rows][columns];
	char playerBoard[rows][columns];

	board(rows, columns, minefield);
	generateMinefield(rows, columns, mines, minefield);
	generateNumberMap(rows, columns, minefield, playerBoard);
}
