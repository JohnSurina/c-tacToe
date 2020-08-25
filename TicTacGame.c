#include <stdio.h>
#include <string.h>
#include "ticTacDefinitions.c"

#define MAP_PLAYER_TOKEN(a,b,c) (!(a) ? ' ' : ((a == 1) ? b : c)) // Map a to b if a is 1, c if a is 2, and a space otherwise
#define SWAP_PLAYER_TURN(a) (a == 1) ? 2 : 1 // Switch 1 to 2, and vise versa

/**
 * Prompt a user to provide a character to act as their token.
 */
void promptForToken(char playerNumber, char* playerTokenPointer){
    printf("Player %c, please enter a single character for your player token: ", playerNumber);
    scanf("\n%c", playerTokenPointer);
    //printf("Player %c's token is set to: %d\n\n", playerNumber, *playerTokenPointer); This line checks the token signature.
}

/**
 * AFTER prompting the user for a move, collect the
 * value that the player wishes. return the slot on
 * the game board. This function will loop while
 * the input is invalid.
 */
int* collectMove(TicTacToeBoard board){
    while(1){
        char move[3];
        scanf("\n%2c", move);
        move[2] = 0;
        
        if (strcmp(move, "TL") == 0) return board.TL;
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

/**
 * Make a prompt for whether the players would like to 
 * continue playing or not. Return 1 if they want to continue,
 * return 0 otherwise.
 */
int checkIfPlayersWantToKeepPlaying(){
    char playAgainMarker;
    printf("Play again? (y/n):");
    scanf("\n%c", &playAgainMarker);

    if ( !( (playAgainMarker == 'y') || (playAgainMarker == 'Y') ) ){
        return 0;
    }
    return 1;
}

/**
 * Map the characters provided for players 1 and 2 to
 * the values in their tic tac toe board.
 */
void collectCharacters(char charArray[9], TicTacToeBoard board, char p1, char p2){
    for (int i = 0; i < (int)LEN(board.ticTacToeArray); i++){
        int value = board.ticTacToeArray[i];
        charArray[i] = MAP_PLAYER_TOKEN(value, p1, p2);
    }    
}

/**
 * Print out the tic tac toe board in ascii characters.
 * This function is necessary to map the provided player tokens
 * (characters) to their integer values on the tic tac toe board.
 */
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

/**
 * This Function is the primary game loop. 
 */
int playGame(){
    int stillPlaying = 1;
    TicTacToeBoard playBoard;
    char player1Token = 0;
    char player2Token = 0;

    printf("Welcome to C-TicTacToe!\nby JSurina\n\n");
    promptForToken('1', &player1Token);
    promptForToken('2', &player2Token);
    
    while(stillPlaying){ // This loop accounts for multiple plays

        initializeTicTacToeBoard(&playBoard);

        int winner = 0;
        int playerTurn = 1;
        
        while(!winner){ // This is an inter-game loop.
            int* boardMovePosition;

            printBoard(playBoard, player1Token, player2Token);
            printf("Player %d, please enter your move.\nValid moves are (TL, TM, TR, ML, MM, MR, BL, BM, BR)\n", playerTurn);

            while(1){
                boardMovePosition = collectMove(playBoard);

                if( makeMoveSafely(boardMovePosition, playerTurn) ) break;
                printf("The position you've selected is already occupied!\n\
                        Please enter a valid, unnocupied position.");
                printBoard(playBoard, player1Token, player2Token);
            }

            playerTurn = SWAP_PLAYER_TURN(playerTurn);

            winner = checkForWinningCondition(playBoard);
        }

        printBoard(playBoard, player1Token, player2Token);

        if(winner != 3){
            printf("Player %d wins!\n", winner);
        } else {
            printf("Its a draw!\n");
        }

        stillPlaying = checkIfPlayersWantToKeepPlaying();
        
    }

    printf("Thank you for playing!\n\n");
    return(0);
}