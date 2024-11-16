#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int surroundingMines(int rows, int columns, char minefield[rows][columns], int i, int j) { // to-do - need to fix out-of-bounds errors (indexing)
	
	int surrounding_mines = 0; 

	if (minefield[i][j] != 'X') {
				
		if (minefield[i+1][j] == 'X') { 
			surrounding_mines++; 
		}	

		if (minefield[i-1][j] == 'X') { 
			surrounding_mines++;
		}
	
		if (minefield[i][j+1] == 'X') {
                	surrounding_mines++;
            	}

		if (minefield[i][j-1] == 'X') {
                	surrounding_mines++;
		}

		if (minefield[i-1][j+1] == 'X') { 
                	surrounding_mines++;
            	}
			
		if (minefield[i+1][j+1] == 'X') {
                	surrounding_mines++;
            	}

		if (minefield[i-1][j-1] == 'X') {
			surrounding_mines++;
            	}

		if (minefield[i+1][j-1] == 'X') {
                	surrounding_mines++;
            	}
	}	

	return surrounding_mines; 
}

void boardLayout(int rows, int columns, int mines) {
	
	char minefield[rows][columns]; 
	char playerBoard[rows][columns];
	
	int mines_placed = 0; 

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
	            minefield[i][j] = '.';
		    playerBoard[i][j] = '.';
	        }
	    }

	while (mines_placed < mines) { 
		int i = rand() % rows;
		int j = rand() % columns;
		
		if (minefield[i][j] != 'X') { 
			minefield[i][j] = 'X'; 					
			mines_placed++; 
		}
	}

	for (int i = 0; i < rows; i++) { // printing for dev purposes - remove later  
    		for (int j = 0; j < columns; j++) { 
    			printf("%c ", minefield[i][j]);
		}
     	printf("\n");
    }

	for (int i = 0; i < rows; i++) { 
		for (int j = 0; j < columns; j++) { 
			if (minefield[i][j] != 'X') { 
				int touching_mines = surroundingMines(rows, columns, minefield, i, j);
				minefield[i][j] = '0' + touching_mines;
				playerBoard[i][j] = '0' + touching_mines;    			
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

int main() { 

	srand(time(NULL)); 

	boardLayout(10, 10, 56); // testing - needs to be input from Angel's code  
}
