#include <stdio.h>
#include "ticTacDefinitions.c"

void promptForToken(char playerNumber, char* playerTokenPointer){
    printf("Player %c, please enter a single character for your player token: ", playerNumber);
    scanf("\n%c", playerTokenPointer);
    printf("Player %c's token is set to: %d\n\n", playerNumber, *playerTokenPointer);
    printf("debug marker -4");
}

int* collectMove(TicTacToeBoard board){
    while(1){
        char move[3];
        scanf("%2c", &move);
        move[2] = 0;

        if (move == "TL") return board.TL;
        if (move == "TM") return board.TM;
        if (move == "TR") return board.TR;
        if (move == "ML") return board.ML;
        if (move == "MM") return board.MM;
        if (move == "MR") return board.MR;
        if (move == "BL") return board.BL;
        if (move == "BM") return board.BM;
        if (move == "BR") return board.BR;

        printf("The selected move was invalid, please enter a value from the following list\n\
                (TL, TM, TR, ML, MM, MR, BL, BM, BR)\n");
    }

}

int checkIfPlayersWantToKeepPlaying(){
    char playAgainMarker;
    printf("Play again? (y/n):");
    scanf("%c", &playAgainMarker);

    if ( !( (playAgainMarker == 'y') || (playAgainMarker == 'Y') ) ){
        return 0;
    }
    return 1;
}

void printBoard(TicTacToeBoard board){
    printf("-------------");
    printf("| %c | %c | %c |", *board.TL, *board.TM, *board.TR);
    printf("-------------");
    printf("| %c | %c | %c |", *board.ML, *board.MM, *board.MR);
    printf("-------------");
    printf("| %c | %c | %c |", *board.BL, *board.BM, *board.BR);
    printf("-------------");

}

int playGame(){
    int stillPlaying = 1;
    TicTacToeBoard playBoard;
    char player1Token = 0;
    char player2Token = 0;

    printf("Welcome to C-TicTacToe!\nby JSurina\n\n");
    promptForToken('1', &player1Token);
    promptForToken('2', &player2Token);
    printf("debug marker -3");
    
    while(stillPlaying){
        printf("debug marker -2");
        playBoard = constructTicTacToeBoard();

        printf("debug marker 1");

        int winner = 0;
        int playerTurn = 1;

        while(!winner){
            int* boardMovePosition;

            printf("debug marker 1");

            printBoard(playBoard);
            printf("Player %d, please enter your move.\nValid moves are (TL, TM, TR, ML, MM, MR, BL, BM, BR)\n", playerTurn);

            while(1){
                boardMovePosition = collectMove(playBoard);

                if( makeMoveSafely(boardMovePosition, playerTurn) ) break;
                printf("The position you've selected is already occupied!\n\
                        Please enter a valid, unnocupied position.");
                printBoard(playBoard);
            }

            winner = checkForWinningCondition(playBoard);
        }

        printf("Player %d wins!\n", winner);

        stillPlaying = checkIfPlayersWantToKeepPlaying();
        
    }

    printf("Thank you for playing!");
    return(0);
}