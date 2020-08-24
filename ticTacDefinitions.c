
#define checkEqual(a, b, c) if((*a == *b) && (*b == *c)) return *a
#ifndef TIC_TAC_DEFINITIONS
#define TIC_TAC_DEFINITIONS 1

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

TicTacToeBoard constructTicTacToeBoard(){
    printf("debug marker -1");
    TicTacToeBoard boardReturn;

    for (int i = 0; i < sizeof(boardReturn.ticTacToeArray); i++){
        printf("debug marker 0 : %d", i);
        boardReturn.ticTacToeArray[i] = 0;
    }

    boardReturn.TL = &(boardReturn.ticTacToeArray[0]);
    boardReturn.TM = &(boardReturn.ticTacToeArray[1]);
    boardReturn.TR = &(boardReturn.ticTacToeArray[2]);
    boardReturn.ML = &(boardReturn.ticTacToeArray[3]);
    boardReturn.MM = &(boardReturn.ticTacToeArray[4]);
    boardReturn.MR = &(boardReturn.ticTacToeArray[5]);
    boardReturn.BL = &(boardReturn.ticTacToeArray[6]);
    boardReturn.BM = &(boardReturn.ticTacToeArray[7]);
    boardReturn.BR = &(boardReturn.ticTacToeArray[8]);
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
        return(0);
    } else {
        makeMove(boardPointer, player);
        return(1);
    }
}

#endif