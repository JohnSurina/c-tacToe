#ifndef TIC_TAC_DEFINITIONS
#define TIC_TAC_DEFINITIONS 1

#define checkEqual(a, b, c) if((*a == *b) && (*b == *c)) return *a // Check that three values are equal, return their value if they are.
#define LEN(x) sizeof(x) / sizeof(x[0]) // Calculate the length of an array with uniformly allocatead memory.

typedef struct ticTacToeBoard TicTacToeBoard;

/**
 * A Structure containing a 9-value array, corresponding
 * to the 9 slots on a tic tac toe board. To see better
 * what each entry in the array is intended to represent,
 * please see the definition given in initializeTicTacToeBoard.
 * The intention of this array is to have either 1 or 2
 * be populated in each entry for either player 1 or 2, and
 * have a 0 populated if the space is unpopulated.
 */
struct ticTacToeBoard {
    int ticTacToeArray[9];

    int* TL;
    int* TM;
    int* TR;
    int* ML;
    int* MM;
    int* MR;
    int* BL;
    int* BM;
    int* BR;
};

/**
 * Due to the "pass by value" nature of parameters,
 * and the fact that this structure contains convenience
 * self-referencing pointers, we must design this function
 * to modify an already instantiated value, rather than
 * create and return a new one. If we did not do this,
 * then the memory locations that we would reference in
 * this function would eventually be overwritten (because
 * we would be pointing to the freed version of the local
 * value), and they would be effectively useless.
 */ 
void initializeTicTacToeBoard(TicTacToeBoard * board){

    for (int i = 0; i < LEN(board->ticTacToeArray); i++){
        board->ticTacToeArray[i] = 0;
    }

    board->TL = &(board->ticTacToeArray[0]);
    board->TM = &(board->ticTacToeArray[1]);
    board->TR = &(board->ticTacToeArray[2]);
    board->ML = &(board->ticTacToeArray[3]);
    board->MM = &(board->ticTacToeArray[4]);
    board->MR = &(board->ticTacToeArray[5]);
    board->BL = &(board->ticTacToeArray[6]);
    board->BM = &(board->ticTacToeArray[7]);
    board->BR = &(board->ticTacToeArray[8]);

    return;
}

/**
 * Check to see if there is any winning situation on the board.
 * Return the winning user integer if there is such a case.
 * Return the integer 3 if all board places are occupied and
 * there is no winner (tie).
 * Otherwise, return 0, indicating the game is still in session.
 */
int checkForWinningCondition(TicTacToeBoard boardState){
    checkEqual(boardState.TL, boardState.TM, boardState.TR);
    checkEqual(boardState.ML, boardState.MM, boardState.MR);
    checkEqual(boardState.BL, boardState.BM, boardState.BR);
    checkEqual(boardState.TL, boardState.ML, boardState.BL);
    checkEqual(boardState.TM, boardState.MM, boardState.BM);
    checkEqual(boardState.TR, boardState.MR, boardState.BR);
    checkEqual(boardState.TL, boardState.MM, boardState.BR);
    checkEqual(boardState.BL, boardState.MM, boardState.TR);

    for(int i = 0; i < LEN(boardState.ticTacToeArray); i++){
        if(boardState.ticTacToeArray[i] == 0) return 0;
    }

    return 3;
}

/**
 * Force a player move to a location. Does not check
 * if the space is occupied.
 */
void makeMove(int* boardPointer, int player){
    if (player == 1 || player == 2){
        *boardPointer = player;
    }
}

/**
 * Checks to see if a place on the board is unoccupied
 * before assigning a player token.
 */
int makeMoveSafely(int* boardPointer, int player){
    if (*boardPointer){ // If the memory at the given address is occupied, return false.
        return(0);
    } else {
        makeMove(boardPointer, player);
        return(1);
    }
}

#endif