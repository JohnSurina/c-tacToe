#include <stdio.h>
#include <string.h>
#include "ticTacDefinitions.c"

#define MAP_PLAYER_TOKEN(a,b,c) (!(a) ? ' ' : ((a == 1) ? b : c)) // Map a to b if a is 1, c if a is 2, and a space otherwise

void promptForToken(char playerNumber, char* playerTokenPointer){
    printf("Player %c, please enter a single character for your player token: ", playerNumber);
    scanf("\n%c", playerTokenPointer);
    printf("Player %c's token is set to: %d\n\n", playerNumber, *playerTokenPointer);
}

int* collectMove(TicTacToeBoard board){
    while(1){
        char move[3];
        scanf("\n%2c", move);
        move[2] = 0;
        
        if (strcmp(move, "TL") == 0){
            printf("THIS IS THE VALUE COLLECTED AT COLLECTMOVE: %d", *board.TL);
            return board.TL;
        }
        if (strcmp(move, "TM") == 0) return board.TM;
        if (strcmp(move, "TR") == 0) return board.TR;
        if (strcmp(move, "ML") == 0) return board.ML;
        if (strcmp(move, "MM") == 0) return board.MM;
        if (strcmp(move, "MR") == 0) return board.MR;
        if (strcmp(move, "BL") == 0) return board.BL;
        if (strcmp(move, "BM") == 0) return board.BM;
        if (strcmp(move, "BR") == 0) return board.BR;

        printf("The selected move was invalid, please enter a value from the following list\n\
                (TL, TM, TR, ML, MM, MR, BL, BM, BR)\n");
    }

}

int checkIfPlayersWantToKeepPlaying(){
    char playAgainMarker;
    printf("Play again? (y/n):");
    scanf("\n%c", &playAgainMarker);

    if ( !( (playAgainMarker == 'y') || (playAgainMarker == 'Y') ) ){
        return 0;
    }
    return 1;
}

void collectCharacters(char charArray[9], TicTacToeBoard board, char p1, char p2){
    printf("\nDEBUG DDDD: %d\n", *board.TL);
    printf("\nDEBUG LEN(board.ticTacToeArray = %ld\n", LEN(board.ticTacToeArray));
    for (int i = 0; i < (int)LEN(board.ticTacToeArray); i++){
        int value = board.ticTacToeArray[i];
        printf("value i = %d : %d\n", i, value);
        charArray[i] = MAP_PLAYER_TOKEN(value, p1, p2);
    }
   printf("\nDEBUG EEEE: %d\n", *board.TL);
    
}

void printBoard(TicTacToeBoard board, char p1, char p2){
    char bchar[LEN(board.ticTacToeArray)];
    collectCharacters(bchar, board, p1, p2);

    printf("-------------\n");
    printf("| %c | %c | %c |\n", bchar[0], bchar[1], bchar[2]);
    printf("-------------\n");
    printf("| %c | %c | %c |\n", bchar[3], bchar[4], bchar[5]);
    printf("-------------\n");
    printf("| %c | %c | %c |\n", bchar[6], bchar[7], bchar[8]);
    printf("-------------\n\n");

}

int playGame(){
    int stillPlaying = 1;
    TicTacToeBoard playBoard;
    char player1Token = 0;
    char player2Token = 0;

    printf("Welcome to C-TicTacToe!\nby JSurina\n\n");
    promptForToken('1', &player1Token);
    promptForToken('2', &player2Token);
    
    while(stillPlaying){

        initializeTicTacToeBoard(&playBoard);
        printf("\nDEBUG BBBB: %d\n", *playBoard.TL);

        int winner = 0;
        int playerTurn = 1;
        
        while(!winner){
            int* boardMovePosition;

            printf("\nDEBUG CCCC: %d\n", *playBoard.TL);

            printBoard(playBoard, player1Token, player2Token);
            printf("Player %d, please enter your move.\nValid moves are (TL, TM, TR, ML, MM, MR, BL, BM, BR)\n", playerTurn);

            while(1){
                printf("\nDEBUG AAAA: %d\n", *playBoard.TL);
                boardMovePosition = collectMove(playBoard);

                if( makeMoveSafely(boardMovePosition, playerTurn) ) break;
                printf("The position you've selected is already occupied!\n\
                        Please enter a valid, unnocupied position.");
                printBoard(playBoard, player1Token, player2Token);
            }

            playerTurn = (playerTurn == 1) ? 2 : 1;

            winner = checkForWinningCondition(playBoard);
        }

        printf("Player %d wins!\n", winner);

        stillPlaying = checkIfPlayersWantToKeepPlaying();
        
    }

    printf("Thank you for playing!");
    return(0);
}