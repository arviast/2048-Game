//  prog5_1024.cpp
//     Text version of the game 1024, a variant of 2048 available online at:
//        http://gabrielecirulli.github.io/2048/
//     Object of game is to combine number tiles with the same value, accumulating
//     points as the game progresses, to try and create the tile with the value 1024.
//     Each move consists of sliding pieces to the left, up, right or down.
/*  Running program looks like:
 
 Arvinbayar Jamsranjav
 UIC CS 141, Spring 2019
 Welcome to 1024.
 This program is based off of Gabriele Cirulli's game online at
 bit.ly/great2048
 
 For each move enter a direction as a letter key, as follows:
 W
 A S D
 where A=left,W=up, D=right and S=down.
 
 After a move, when two identical valued tiles come together they
 join to become a new single tile with the value of the sum of the
 two originals. This value gets added to the score.  On each move
 one new randomly chosen value of 2 or 4 is placed in a random open
 square.  User input of x exits the game.
 
 Game ends when you reach 1024.
 
 Score: 0
 .     4     .     .
 
 .     .     .     .
 
 .     .     4     .
 
 .     .     .     .
 
 1. Your move: a
 
 Score: 0
 4     .     .     .
 
 .     .     .     .
 
 4     .     .     .
 
 .     .     2     .
 
 2. Your move: a
 .
 .
 .
 */

#include <iostream>     // For cin, cout, endl
#include <iomanip>      // used for setting output field size using setw
#include <cstdlib>      // For rand()
using namespace std;    // So we don't need std:: in front of every cin, cout, and endl

const int MaxBoardSize = 12;          // Max number of squares per side
const int MaxTileStartValue = 1024;   // Max tile value to start out on a 4x4 board


//--------------------------------------------------------------------
// Display Instructions
void displayInstructions()
{
    cout << "Welcome to 1024. \n"
    << "  \n"
    << "For each move enter a direction as a letter key, as follows: \n"
    << "    W    \n"
    << "  A S D  \n"
    << "where A=left,W=up, D=right and S=down. \n"
    << "  \n"
    << "After a move, when two identical valued tiles come together they    \n"
    << "join to become a new single tile with the value of the sum of the   \n"
    << "two originals. This value gets added to the score.  On each move    \n"
    << "one new randomly chosen value of 2 or 4 is placed in a random open  \n"
    << "square.  User input of x exits the game.                            \n"
    << "  \n";
}//end displayInstructions()


//--------------------------------------------------------------------
// Place a randomly selected 2 or 4 into a random open square on
// the board.
void placeRandomPiece( int board[], int squaresPerSide)
{
    // Randomly choose a piece to be placed (2 or 4)
    int pieceToPlace = 2;
    if( rand()%2 == 1) {
        pieceToPlace = 4;
    }
    
    // Find an unoccupied square that currently has a 0
    int index;
    do {
        index = rand() % (squaresPerSide*squaresPerSide);
    }while( board[ index] != 0);
    
    // board at position index is blank, so place piece there
    board[ index] = pieceToPlace;
}//end placeRandomPiece()


//--------------------------------------------------------------------
// Display squaresPerSideXsquaresPerSide board
void displayAsciiBoard(int board[], int squaresPerSide, int score) {
    cout << endl << "Score: " << score << endl;
    cout << "     ";
    for (int i = 0; i < (squaresPerSide*squaresPerSide); i++) {
        if ( i > 0 && i % squaresPerSide == 0 ) {
            cout << setw(6)<< endl << endl;
        }
        if (board[i] == 0) {
            cout << "." << setw(6);
        }
        else if (board[i] != 0) {
            cout << board[i] << setw(6);
        }
        if (i == ((squaresPerSide*squaresPerSide)-1)) {
            cout << endl << endl << setw(0);
        }
    }
}


//--------------------------------------------------------------------
// LEFT MOVE FUNCTION that including 3 steps
// 1. Slide
// 2. Merge or combine
// 3. Again slide (for special cases. For ex: same numbers in a row)
void moveLeft (int board[], int squaresPerSide, int& score) {
    // Step 1
    
    for (int i = 0; i < squaresPerSide*squaresPerSide; i++) {
        if (board[i] != 0) {
            while (((i) % squaresPerSide != 0) && (board[i-1] == 0) && i <=squaresPerSide*squaresPerSide && i > 0) {
                board[i-1] = board[i];
                board[i] = 0;
                i -= (i + 1);
            }
        }
    }
    // Step 2
    for (int i = 0; i < squaresPerSide*squaresPerSide; i++) {
        if(board[i] == board[i-1] && (i % squaresPerSide != 0)) {
            board[i-1] += board[i];
            board[i] = 0;
            score += board[i-1];
        }
    }
    // Step 3
    for (int i = 0; i < squaresPerSide*squaresPerSide; i++) {
        if (board[i] != 0) {
            while (((i) % squaresPerSide != 0) && (board[i-1] == 0) && i <=squaresPerSide*squaresPerSide) {
                board[i-1] = board[i];
                board[i] = 0;
                i -= (i + 1);
            }
        }
    }
}


//--------------------------------------------------------------------
// Right MOVE FUNCTION that including 3 steps
// 1. Slide
// 2. Merge or combine
// 3. Again slide (for special cases. For ex: same numbers in a row)
void moveRight (int board[], int squaresPerSide,int& score) {
    // Step 1
    for (int i = (squaresPerSide*squaresPerSide-1); i >= 0; --i) {
        if (board[i] != 0) {
            while (((i+1) % squaresPerSide != 0) && (board[i+1] == 0) && i <= squaresPerSide*squaresPerSide) {
                board[i+1] = board[i];
                board[i] = 0;
                i += (i + 1);
            }
        }
    }
    // Step 2
    for (int i = (squaresPerSide*squaresPerSide-1); i >= 0; --i) {
        if(board[i] == board[i+1] && ((i+1) % squaresPerSide != 0)) {
            board[i+1] += board[i];
            board[i] = 0;
            score += board[i+1];
        }
    }
    // Step 3
    for (int i = (squaresPerSide*squaresPerSide-1); i >= 0; --i) {
        if (board[i] != 0) {
            while (((i+1) % squaresPerSide != 0) && (board[i+1] == 0) && i <= squaresPerSide*squaresPerSide) {
                board[i+1] = board[i];
                board[i] = 0;
                i += (i + 1);
            }
        }
    }
}


//--------------------------------------------------------------------
// Up MOVE FUNCTION that including 3 steps
// 1. Slide
// 2. Merge or combine
// 3. Again slide (for special cases. For ex: same numbers in a row)
void moveUp(int board[], int squaresPerSide,int& score) {
    // Step 1
    for (int i = 0; i < squaresPerSide*squaresPerSide; i++) {
        if (board[i] != 0) {
            while (i >= squaresPerSide && (board[i-squaresPerSide] == 0) && i <= squaresPerSide*squaresPerSide) {
                board[i-squaresPerSide] = board[i];
                board[i] = 0;
                i -= (squaresPerSide + 1);
            }
        }
    }
    // Step 2
    for (int i = 0; i < (squaresPerSide*squaresPerSide); i++) {
        if(board[i] == board[i-squaresPerSide] && (i >= squaresPerSide)) {
            board[i-squaresPerSide] += board[i];
            board[i] = 0;
            score += board[i-squaresPerSide];
        }
    }
    // Step 3
    for (int i = 0; i < squaresPerSide*squaresPerSide; i++) {
        if (board[i] != 0) {
            while (i >= squaresPerSide && (board[i-squaresPerSide] == 0) && i <= squaresPerSide*squaresPerSide) {
                board[i-squaresPerSide] = board[i];
                board[i] = 0;
                i -= (squaresPerSide + 1);
            }
        }
    }
}


//--------------------------------------------------------------------
// Down MOVE FUNCTION that including 3 steps
// 1. Slide
// 2. Merge or combine
// 3. Again slide (for special cases. For ex: same numbers in a row)
void moveDown(int board[], int squaresPerSide, int& score) {
    // Step 1
    for (int i = (squaresPerSide*squaresPerSide-1); i >= 0; --i) {
        if (board[i] != 0) {
            while (i < (squaresPerSide*squaresPerSide-squaresPerSide) && (board[i+squaresPerSide] == 0) &&
                   i <= squaresPerSide*squaresPerSide) {
                board[i+squaresPerSide] = board[i];
                board[i] = 0;
                i += (squaresPerSide + 1);
            }
        }
    }
    // Step 2
    for (int i = (squaresPerSide*squaresPerSide-1); i >= 0; --i) {
        if(board[i] == board[i+squaresPerSide] && (i < (squaresPerSide*squaresPerSide-squaresPerSide))) {
            board[i+squaresPerSide] += board[i];
            board[i] = 0;
            score += board[i+squaresPerSide];
        }
    }
    // Step 3
    for (int i = (squaresPerSide*squaresPerSide-1); i >= 0; --i) {
        if (board[i] != 0) {
            while (i < (squaresPerSide*squaresPerSide-squaresPerSide) && (board[i+squaresPerSide] == 0) &&
                   i <= squaresPerSide*squaresPerSide) {
                board[i+squaresPerSide] = board[i];
                board[i] = 0;
                i += (squaresPerSide + 1);
            }
        }
    }
}


//--------------------------------------------------------------------
// Used for finding maxTileValue
// Hardcoded version to find a n-th power of the number
int raiseToPower(int x, int power)
{
    int answer;
    int i;
    answer =1;
    for (i=1; i<=power;i++)
    {
        answer = answer*x;
    }
    return(answer);
}

//---------------------------------------------------------------------------------------
int main()
{
    int score = 0;
    int squaresPerSide = 4;        // User will enter this value.  Set default to 4
    int board[ MaxBoardSize * MaxBoardSize];          // space for largest possible board
    int previousBoard[ MaxBoardSize * MaxBoardSize];  // space for copy of board, used to see
    //    if a move changed the board.
    int maxTileValue = MaxTileStartValue;  // 1024 for 4x4 board, 2048 for 5x5, 4096 for 6x6, etc.
    char userInput = ' ';                  // handles user input
    int move = 1;                          // user move counter
    
    int userIndex =0;                      // for userInput 'p' initializing index
    int userChoosenNumber = 0;             // for userInput 'p' initializing choosen number
    int difference = 0;                    // used to find a maxTileValue for resizing the board
    int power = 2;                         // used to find a maxTileValue
    
    displayInstructions();
    
    // Get the board size, create and initialize the board
    int boardSize = (squaresPerSide * squaresPerSide);
    for(int i = 0; i < boardSize; i++) {
        board[i] = 0;
    }
    
    // 2 Random pieces are given in the start
    placeRandomPiece( board, squaresPerSide);
    placeRandomPiece( board, squaresPerSide);
    
    // Starting text declaring when you win
    cout << "Game ends when you reach " << maxTileValue << "." << endl;
    
    // Infinite loop to run program until user selects exit, board is full, or max tile value is reached
    while( true)
    {
        // Display the text-based board
        displayAsciiBoard( board, squaresPerSide, score);
        
        // Make a copy of the board.  After we then attempt a move, the copy will be used to
        // verify that the board changed, which only then allows randomly placing an additional
        // piece on the board and updating the move number.
        // ...
        boardSize = squaresPerSide * squaresPerSide;
        for(int i = 0; i < boardSize; i++) {
            previousBoard[i] = board[i];
        }
        
        // Prompt for and handle user input
        cout << move << ". Your move: ";
        cin >> userInput;
        cout << endl;
        switch (userInput) {
            case 'x':
                cout << "Thanks for playing. Exiting program... \n\n";
                exit( 0);
                break;
            case 'a':
                moveLeft(board,squaresPerSide,score);
                break;
            case 'd':
                moveRight(board,squaresPerSide,score);
                break;
            case 'w':
                moveUp(board, squaresPerSide,score);
                break;
            case 's':
                moveDown(board,squaresPerSide,score);
                break;
            case 'p':
                cin >> userIndex >> userChoosenNumber;
                board[userIndex] = userChoosenNumber;
                continue;
                break;
            case 'r':
                // Text board resets and asks for user desired size
                cout << "Resetting board" << endl << endl;
                cout << "Enter the size board you want, between 4 and 12:";
                cin >> squaresPerSide;
                
                // My Hardcoded version of finding maxTileValue (could use math library, but ...)
                difference = squaresPerSide - 4;
                cout << endl << "Game ends when you reach " << (raiseToPower(2,difference) * MaxTileStartValue) << "." << endl;
                
                // Resetting the board and places random piece
                // Score and move starts to count
                for (int i = 0; i < squaresPerSide*squaresPerSide; i++) {
                    board[i] = 0;
                }
                placeRandomPiece(board,squaresPerSide);
                score = 0;
                move = 0;
                break;
                
            default:
                cout << "Invalid input, please retry.";
                continue;
                break;
        }//end switch( userInput)
        
        // If the move resulted in pieces changing position, then it was a valid move
        // so place a new random piece (2 or 4) in a random open square and update the move number.
        // ...
        for(int i = 0; i < boardSize; i++) {
            if (board[i] != previousBoard[i]) {
                placeRandomPiece(board,squaresPerSide);
                move++;
                break;
            }
        }
        
        // See if we're done.  If so, display the final board and break.
        // ...
        for (int i = 0; i < boardSize; i++) {
            if(board[i] == maxTileValue) {
                cout << "Congratulations!  You made it to " << maxTileValue << "!!!" << endl;
                displayAsciiBoard( board, squaresPerSide, score);
                exit (0);
                break;
            }
        }
        
        // Board is full
        // Counting all non zeros, if non zeros == boardsize , then we done !
        int countingNotZeros = 0;
        for (int i = 0; i < boardSize; i++) {
            if(board[i] != 0) {
                ++countingNotZeros;
            }
        }
        if(countingNotZeros == (boardSize)) {
            cout << "No more available moves.  Game is over." << endl;
            displayAsciiBoard( board, squaresPerSide, score);
            exit( 0);
            break;
        }
        

    }//end while( true)
    
    return 0;
}//end main()
