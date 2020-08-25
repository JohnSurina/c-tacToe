
#ifndef TIC_TAC_DEFINITIONS
#define TIC_TAC_DEFINITIONS 1

#define checkEqual(a, b, c) if((*a == *b) && (*b == *c)) return *a
#define LEN(x) sizeof(x) / sizeof(x[0])

typedef struct ticTacToeBoard TicTacToeBoard;

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

int checkForWinningCondition(TicTacToeBoard boardState){
    checkEqual(boardState.TL, boardState.TM, boardState.TR);
    checkEqual(boardState.ML, boardState.MM, boardState.MR);
    checkEqual(boardState.BL, boardState.BM, boardState.BR);
    checkEqual(boardState.TL, boardState.ML, boardState.BL);
    checkEqual(boardState.TM, boardState.MM, boardState.BM);
    checkEqual(boardState.TR, boardState.MR, boardState.BR);
    checkEqual(boardState.TL, boardState.MM, boardState.BR);
    checkEqual(boardState.BL, boardState.MM, boardState.TR);
    return 0;
}

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
    if (*boardPointer){
        printf("\n I MADE IT HERE: %d\n", *boardPointer);
        return(0);
    } else {
        makeMove(boardPointer, player);
        return(1);
    }
}

#endif