#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Declare printSudoku function
void printSudoku(int***);


// Declare solveSudoku function
int solveSudoku(int***);

//Helper functions. You can define any functions that can help your solve the problem

bool CheckBlock(int*** arr, int val, int block, int row, int col){ 
		
		for(row = 0; row < 3; row++) {
			for(col = 0; col < 3; col++) {
				if(*(*(*(arr + block) + col) + row) == val) {
					return false;
				}
			}
		}
    return true;
}

bool CheckRow(int*** arr, int val, int block, int row, int col){
    
	int n = block;
	
	if(n < 3)
		n = 0;
	else if (n < 6)
		n = 3;
	else if (n < 9)
		n = 6;
	
	switch (n){
        case 0:
			block = 0;
            for(row = 0; row < 3; row++){
                if(*(*(*(arr + block) + col) + row) == val)
                    return false;                
            }
			
            block = 1;
            for(row = 0; row < 3; row++){
                if(*(*(*(arr + block) + col) + row) == val)
                    return false;
            }
			
            block = 2;
            for(row = 0; row < 3; row++){
                if(*(*(*(arr + block) + col) + row) == val)
                    return false;
                
            }
            return true;

        case 3:
			block = 3;
            for(row = 0; row < 3; row++){
                if(*(*(*(arr + block) + col) + row) == val)
                    return false;
            }
			
            block = 4;
            for(row = 0; row < 3; row++){
                if(*(*(*(arr + block) + col) + row) == val)
                    return false;
            }
			
            block = 5;
            for(row = 0; row < 3; row++){
                if(*(*(*(arr + block) + col) + row) == val)
                    return false;
            }
            return true;

        case 6:
			block = 6;
            for(row = 0; row < 3; row++){
                if(*(*(*(arr + block) + col) + row) == val)
                    return false;
            }
			
            block = 7;
            for(row = 0; row < 3; row++){
                if(*(*(*(arr + block) + col) + row) == val)
                    return false;
            }
			
            block = 8;
            for(row = 0; row < 3; row++){
                if(*(*(*(arr + block) + col) + row) == val)
                    return false;
            }
            return true;
		
	}
}


bool CheckCol(int*** arr, int val, int block, int row, int col){ 
	
	int n = block;
	if(n == 0 || n == 3 || n == 6)
		n = 0;
	else if (n == 1 || n == 4 || n == 7)
		n = 1;
	else if (n == 2 || n == 5 || n == 8)
		n = 2;

    switch (n) {
        case 0:
			block = 0;
            for(col = 0; col < 3; col++){
                if(*(*(*(arr + block) + col) + row) == val)
                    return false;
            }
			
            block = 3;
            for(col = 0; col < 3; col++){
                if(*(*(*(arr + block) + col) + row) == val)
                    return false;
            }
			
            block = 6;
            for(col = 0; col < 3; col++){
                if(*(*(*(arr + block) + col) + row) == val)
                    return false;
            }
            return true;
        case 1:
			block = 1;
           for(col = 0; col < 3; col++){
                if(*(*(*(arr + block) + col) + row) == val)
                    return false;
            }
			
            block = 4;
            for(col = 0; col < 3; col++){
                if(*(*(*(arr + block) + col) + row) == val)
                    return false;
            }
			
            block = 7;
            for(col = 0; col < 3; col++){
                if(*(*(*(arr + block) + col) + row) == val)
                    return false;
            }
            return true;

        case 2:
			block = 2;
            for(col = 0; col < 3; col++){
                if(*(*(*(arr + block) + col) + row) == val){
                    return false;
                }
            }
			
            block = 5;
            for(col = 0; col < 3; col++){
                if(*(*(*(arr + block) + col) + row) == val)
                    return false;
            }
			
            block = 8;
            for(col = 0; col < 3; col++){
                if(*(*(*(arr + block) + col) + row) == val)
                    return false;
            }
            return true;
	} 
}


/*
The main program reads a text file containing the block values of the Sudoku grid.
It then saves each 3x3 block into a 2D array. The Sudoku grid is composed of 9 3x3 blocks.
DO NOT MODIFY THE MAIN FUNTION!!!
*/

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    int ***blocks = (int***)malloc(9 * sizeof(int**));

    // Open file for reading
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open File!\n");
        return 0;
    }

	// Read 9x9 blocks into 2D arrays
    for(i=0; i<9; i++)
    {
        *(blocks+i) = (int**)malloc(3 * sizeof(int*));
        printf("Reading numbers in block %d... \n", i+1);
        for(j=0; j<3; j++)
        {
            *(*(blocks+i)+j) = (int*)malloc(3 * sizeof(int));

                fscanf(fptr, "%d %d %d", *(*(blocks+i)+j), *(*(blocks+i)+j)+1, *(*(blocks+i)+j)+2);
                printf("%d %d %d\n", *(*(*(blocks+i)+j)), *(*(*(blocks+i)+j)+1), *(*(*(blocks+i)+j)+2));
        }
    }
	
	// Print out original Sudoku grid
    printf("Printing Sudoku before being solved:\n");
    printSudoku(blocks);

	// Call solveSudoku and print out result
    printf("\nSolving Sudoku...\n\n");
    if(solveSudoku(blocks)){
        printf("Sudoku solved!\n");
        printSudoku(blocks);
    }
    else
        printf("This Sudoku cannot be solved!\n");
//        printSudoku(blocks);
    return 0;
}


void printSudoku(int*** arr){
	// This function will print out the complete Sudoku grid (arr). It must produce the output in the SAME format as the samples in the instructions. 	
	
	// Your implementation here
    int i, j, k;
    
	printf("\n");
    for(j = 0; j < 3; j++){
        for(i = 0; i < 3; i++){
            for(k = 0; k < 3; k++){
                printf("%3d ", *(*(*(arr + i) + j) + k));
            }
			 printf(" | ");
        }
		printf("\n");
	}
   
    printf("-------------------------------------------- \n");
    
    for(j = 0; j < 3; j++){
        for(i = 3; i < 6; i++){
            for(k = 0; k < 3; k++){
                printf("%3d ", *(*(*(arr + i) + j) + k));
            }
			 printf(" | ");
        }
		printf("\n");
    }
    printf("-------------------------------------------- \n");
    
    for(j = 0; j < 3; j++){
        for(i = 6; i < 9; i++){
            for(k = 0; k < 3; k++){
                printf("%3d ", *(*(*(arr + i) + j) + k));
            }
			printf(" | ");
        }
		printf("\n");
    }
	printf("\n");
}

int solveSudoku(int*** blocks){
	// This is the function to solve the Sudoku (blocks). Feel free to use any helper functions.
	// YOU MUST NOT USE ANY ARRAY NOTATION ([])!
	//Your implementation here
    int nani,block, row, col; //nani is the value we change 1 - 9 because nani means what
   
    for(block = 0; block < 9; block++){
        for(row = 0; row < 3; row++){
            for(col = 0; col < 3; col++){
				if(*(*(*(blocks + block) + col) + row)== 0){
					for(nani = 1; nani < 10; nani++){
                        if(CheckBlock(blocks, nani, block, row, col) && 
						CheckRow(blocks, nani, block, row, col)&&
						CheckCol(blocks, nani, block, row, col)){
                            *(*(*(blocks + block) + col) + row) = nani;
                            if(solveSudoku(blocks)){
                                return 1;
                            }
                        }
                    }
                    *(*(*(blocks + block) + col) + row) = 0;
                    return 0;
                }
            }
        }
    }
	return 0;
}