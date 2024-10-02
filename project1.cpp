#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(){
    int players = 0; 
    char playAgain = 'y';
    char array[3][3] = {{' ', ' ', ' '},{' ', ' ', ' '},{' ', ' ', ' '}};
    cout << " 1 | 2 | 3 " << endl;
	cout << "___________" << endl;
	cout << " 4 | 5 | 6 " << endl;          //initializes the array, prints the instructions, and determines who goes first
	cout << "___________" << endl;
	cout << " 7 | 8 | 9 " << endl << endl;
	cout << "Each box is numbered; enter the corresponding number to mark an 'O'" << endl;
    while(players != 1 && players!= 2){
        cout << "How many players? Enter 1 or 2: " << endl;
        cin >> players;
    }
    if(players == 2){
        while(playAgain == 'y'){    //if there are two players, this loops the twoPlayerGame function until they don't want to play anymore
        twoPlayerGame(array);
        cout << "The score is " << playerOneWins << " to " << playerOneLosses << ", with " << playerOneDraws << " draw";
        if(playerOneDraws !=1){
            cout << "s";
        }
        cout << "." << endl;
        eraseArray(array);
        do{
            cout << "Play again? (y/n)" << endl;
            cin >> playAgain;
        } while(playAgain != 'y' && playAgain != 'n');
        }
    }
    else{       //this does the same thing, but for one player vs the computer, and it "flips a coin" each game for turn order
        while(playAgain == 'y'){    
        long randomNumber = time(0);
        srand(randomNumber);
        int turnOrder = rand() % 2;
        cout << "Flipping coin..." << endl;
        sleep(2);       
        if(turnOrder == 1){
        
            humanGoesFirst(array);
            return 0;
        }
        else{
            computerGoesFirst(array);
        }
        cout << "The score is 0 to " << computerWins << ", with " << computerDraws << " draw";
        if(computerDraws != 1){
            cout << "s";
        }
        cout << "." << endl;
        eraseArray(array);
        do{
            cout << "Play again? (y/n)" << endl;
            cin >> playAgain;
        } while(playAgain != 'y' && playAgain != 'n');
        }
    }

    
}

int computerGoesFirst(char array[3][3]){
    cout << "The computer will go first" << endl;
    sleep(1);
    array[0][0] = 'X';  //the computer always has the same first move
    printArray(array);
    
    yourMove(array); 
    cout << "Your move:" << endl;
    printArray(array);  //gets then displays the player's first move

    sleep(1);
        
        if(array[1][0] == 'O' || array[2][0] == 'O' || array[1][2] == 'O'){
            array[0][2] = 'X';
        }  
        else{
            array[2][0] = 'X';
        }
    cout << "Computer move:" << endl;   //the computer's second move
    printArray(array);
                
    yourMove(array); 
    cout << "Your move:" << endl;
    printArray(array);  //the player's second move
    
    sleep(1);
    if(array[2][0] == 'X' && array[1][0] == ' '){
        array[1][0] = 'X';
        printArray(array);
        cout << "The machine wins! Humanity's downfall is imminent." << endl;
        computerWins++;

        return 0;           //if the computer wins, then the output should be different and the game should end on the spot
    }
    else if(array[0][2] == 'X' && array[0][1] == ' '){
        array[0][1] = 'X';
        printArray(array);
        cout << "The machine wins! Humanity's downfall is imminent." << endl;
        computerWins++;
        return 0;
    }
    else if(array[1][0] == 'O' && array[1][1] == 'O'){
        array[1][2] = 'X';
    }
    else if(array [0][1] == 'O' && (array[1][0] == 'O' || array[1][2]) && array[1][1] == ' '){
        array[1][1] = 'X';
    }
    else if((array[2][0] == 'X') && (array[0][1] == ' ' && array[1][1] == ' ') && array[0][2] == ' '){
        array[0][2] = 'X';
    }
    else{                       //these if/else statements print the best move by checking which squares are occupied with which letters
        array[2][2]= 'X';
    }
    cout << "Computer move:" << endl;
    printArray(array);
          
    yourMove(array); //the player's third move
    cout << "Your move:" << endl;
    printArray(array);
    
    sleep(1);
    if(checkWins(array)){
        cout << "Computer move:" << endl;
        printArray(array);
        cout << "The machine won! Humanity's downfall is imminent." << endl;
        computerWins++;
        return 0;
    }
    else if(array[0][1] == 'O' || array[0][2] == 'O'){
        array[2][1] = 'X';
    }
    else{
        array[0][1] = 'X';
    }
    cout << "Computer move:" << endl;   //the computer's fourth move
    printArray(array);
        
    yourMove(array); //the player's fourth move
    cout << "Your move:" << endl;
    printArray(array);

    sleep(1);
    //the computer's fifth move is the last of the game, so there will only be one square left
    //this means we can use nested for loops to find the first (and only) open square
    if(checkWins(array)){
        cout << "Computer move:" << endl;
        printArray(array);
        cout << "The machine wins! Humanity's downfall is imminent." << endl;
        computerWins++;
        return 0;
    }
    else{
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(array[i][j] == ' '){
                    array[i][j] = 'X';
                }
            }
        }
    }
    cout << "Computer move:" << endl;
    printArray(array);
    cout << "It's a draw." << endl;
    computerDraws++;
    return 0;
}

void printArray(char array[3][3]){
    cout << " " << array[0][0] << " | " << array[0][1] << " | " << array[0][2] << endl;
	cout << "___________" << endl;
	cout << " " << array[1][0] << " | " << array[1][1] << " | " << array[1][2] << endl;
	cout << "___________" << endl;
	cout << " " << array[2][0] << " | " << array[2][1] << " | " << array[2][2] << endl << endl;
    //this frequently called function prints the board
}

void yourMove(char array[3][3]){
    int inputMove;
    bool wrongInput = true;
    while(wrongInput){
        wrongInput = false;
        cout << "Enter your move: " << endl;
        cin >> inputMove;
    	switch (inputMove)
    	{               //A switch statement in a while loop is used for input, with the default
            case 1:     //catching all invalid input 
                if(array[0][0] == ' '){
                    array[0][0] = 'O';
                }
                else{
                cout << "Illegal move: That spot is taken" << endl;
        	    wrongInput = true;
                }
        	    break;
        	case 2:
        	    if(array[0][1] == ' '){
        	        array[0][1] = 'O';
        	    }
                else{
                    cout << "Illegal move: that spot is taken" << endl;
                    wrongInput = true;
                }
                break;
        	case 3:
        	    if(array[0][2] == ' '){
        	        array[0][2] = 'O';
        	    }
                else{
                    cout << "Illegal move: that spot is taken" << endl;
                    wrongInput = true;
                }
                break;
        	case 4:
        	    if(array[1][0] == ' '){
        	        array[1][0] = 'O';
        	    }
                else{
                    cout << "Illegal move: that spot is taken" << endl;
                    wrongInput = true;
                }
                break;
        	case 5:
        	    if(array[1][1] == ' '){
        	        array[1][1] = 'O';
        	    }
                else{
                    cout << "Illegal move: that spot is taken" << endl;
                    wrongInput = true;
                }
                break;
        	case 6:
        	    if(array[1][2] == ' '){
        	        array[1][2] = 'O';
        	    }
                else{
                    cout << "Illegal move: that spot is taken" << endl;
                    wrongInput = true;
                }
                break;
        	case 7:
        	    if(array[2][0] == ' '){
        	        array[2][0] = 'O';
        	    }
                else{
                    cout << "Illegal move: that spot is taken" << endl;
                    wrongInput = true;
                }
                break;
        	case 8:
        	    if(array[2][1] == ' '){
        	        array[2][1] = 'O';
        	    }
                else{
                    cout << "Illegal move: that spot is taken" << endl;
                    wrongInput = true;
                }
                break;
        	case 9:
        	    if(array[2][2] == ' '){
        	        array[2][2] = 'O';
        	    }
                else{
                    cout << "Illegal move: that spot is taken" << endl;
                    wrongInput = true;
                }
                break;
            default:
                cout << "Invalid move: enter a number from 1-9" << endl;
                wrongInput = true;
    	}
   	}
}

int humanGoesFirst(char array[3][3]){
    bool won, stoppedLoss, move4 = 0;
    cout << "You go first." << endl;    //this function is for when the player goes first, since the computer has to make different moves
	
    yourMove(array);
    cout << "Your move:" << endl;
	printArray(array);  //the player's first move

	int rotations = 0;
	if(array[1][1] == 'O'){
    	array[0][0] = 'X';
	}                   //to limit the number of variations and thus the number of if/else statements required, you
	else{               //can rotate the board. On move 2, this rotation shrinks the number of variations from 35 to 20
    	array[1][1] = 'X';
    	while(array[0][0] != 'O' && array[0][1] != 'O'){
        	rotateClockwise(array);
            rotations++;
    	}
    	counterClockwise(array, rotations);
	}
	sleep(1);
    cout << "Computer move:" << endl;
    printArray(array);

    yourMove(array);    //the player's second move
    cout << "Your move:" << endl;
    printArray(array);

    rotateClockwise(array, rotations);
    stoppedLoss = stopLosses(array);    //the computer's second move
    if(stoppedLoss == 0){
        if(array[0][0] == 'O' && array[1][2] == ' '){
            array[1][0] = 'X';
        }
        else{
            array[0][2] = 'X';
        }
    }
    counterClockwise(array, rotations);
    sleep(1);
    cout << "Computer move:" << endl;
    printArray(array);

    yourMove(array);    //the player's third move
    cout << "Your move:" << endl;
    printArray(array);

    rotateClockwise(array, rotations);
    won = checkWins(array);     //the computer's third move
    if(won == 0){
        stoppedLoss = stopLosses(array);
        if(stoppedLoss == 0){       //if the computer doesn't win or stop any direct wins, only three other moves are needed for the other variations
            if(array[1][0] == ' '){
                array[1][0] = 'X';
            }
            else if(array[2][1] == 'O'){
                array[0][2] = 'X';
            }
            else{
                array[0][1] = 'X';
            }
        }
    }
    else{
        counterClockwise(array, rotations);
        sleep(1);
        cout << "Computer move:" << endl;
        printArray(array);
        cout << "The machine wins! Humanity's downfall is imminent." << endl;
        computerWins++;
        return 0;
    }
    counterClockwise(array, rotations);
    sleep(1);
    cout << "Computer move:" << endl;
    printArray(array);

    yourMove(array);    //the player's fourth move
    cout << "Your move:" << endl;
    printArray(array);

    rotateClockwise(array, rotations);
    won = checkWins(array);
    if(won == 0){
        stoppedLoss = stopLosses(array);
        if(stoppedLoss == 0){  
            for(int i = 0; i < 3; i ++){    //if the computer's fourth move isn't winning or stopping a direct win
                for(int j = 0; j < 3; j++){ //it will not matter at all, so it can just move in the first open square
                    if(array[i][j] == ' '){
                        move4 = 1;
                        array[i][j] = 'X';
                        break;
                    }
                }
                if(move4){
                    break;
                }
            }
        }
    }
    else{
        counterClockwise(array, rotations);
        sleep(1);
        cout << "Computer move:" << endl;
        printArray(array);
        cout << "The machine wins! Humanity's downfall is imminent." << endl;
        computerWins++;
        return 0;
    }
    counterClockwise(array, rotations);
    sleep(1); 
    cout << "Computer move:" << endl;
    printArray(array);

    yourMove(array);
    cout << "Your move:" << endl;
    printArray(array);
    cout << "It's a draw." << endl;  //the ninth move will always be a draw, because of the moves the computer makes
    computerDraws++;
    return 0;
}

bool checkWins(char array[3][3]){   
    //this function checks to see if the computer can win on the spot. If it can, it does, since that is the best move
    if(array[0][0] == ' ' && ((array[0][1] == 'X' && array[0][2] == 'X')||(array[1][1] == 'X' && array[2][2] == 'X')||(array[1][0] == 'X' && array[2][0] == 'X'))){
        array[0][0] = 'X';
        return 1;
    }
    else if(array[0][2] == ' ' && ((array[0][1] == 'X' && array[0][0] == 'X')||(array[1][1] == 'X' && array[2][0] == 'X')||(array[1][2] == 'X' && array[2][2] == 'X'))){
        array[0][2] = 'X';
        return 1;
    }
    else if(array[2][2] == ' ' && ((array[0][2] == 'X' && array[1][2] == 'X')||(array[2][1] == 'X' && array[2][0] == 'X')||(array[1][1] == 'X' && array[0][0] == 'X'))){
        array[2][2] = 'X';
        return 1;
    }
    else if(array[2][0] == ' ' && ((array[0][0] == 'X' && array[1][0] == 'X')||(array[2][1] == 'X' && array[2][2] == 'X')||(array[1][1] == 'X' && array[0][2] == 'X'))){
        array[2][0] = 'X';
        return 1;
    }
    else if(array[0][1] == ' ' && ((array[0][0] == 'X' && array[0][2] == 'X')||(array[1][1] == 'X' && array[2][1] == 'X'))){
        array[0][1] = 'X';
        return 1;
    }
    else if(array[1][2] == ' ' && ((array[0][2] == 'X' && array[2][2] == 'X')||(array[1][0] == 'X' && array[1][1] == 'X'))){
        array[1][2] = 'X';
        return 1;
    }
    else if(array[2][1] == ' ' && ((array[2][0] == 'X' && array[2][2] == 'X')||(array[0][1] == 'X' && array[1][1] == 'X'))){
        array[2][1] = 'X';
        return 1;
    }
    else if(array[1][0] == ' ' && ((array[1][1] == 'X' && array[1][2] == 'X')||(array[1][0] == 'X' && array[1][1] == 'X'))){
        array[1][0] = 'X';
        return 1;
    }
    return 0;    

}

bool stopLosses(char array[3][3]){
    //this function, called after checkWins, checks to see if the player can win next turn.
    //if they can, the computer stops it, since that is most important besides winning itself
    if(array[0][0] == ' ' && ((array[0][1] == 'O' && array[0][2] == 'O')||(array[1][1] == 'O' && array[2][2] == 'O')||(array[1][0] == 'O' && array[2][0] == 'O'))){
        array[0][0] = 'X';
        return 1;
    }
    else if(array[0][2] == ' ' && ((array[0][1] == 'O' && array[0][0] == 'O')||(array[1][1] == 'O' && array[2][0] == 'O')||(array[1][2] == 'O' && array[2][2] == 'O'))){
        array[0][2] = 'X';
        return 1;
    }
    else if(array[2][2] == ' ' && ((array[0][2] == 'O' && array[1][2] == 'O')||(array[2][1] == 'O' && array[2][0] == 'O')||(array[1][1] == 'O' && array[0][0] == 'O'))){
        array[2][2] = 'X';
        return 1;
    }
    else if(array[2][0] == ' ' && ((array[0][0] == 'O' && array[1][0] == 'O')||(array[2][1] == 'O' && array[2][2] == 'O')||(array[1][1] == 'O' && array[0][2] == 'O'))){
        array[2][0] = 'X';
        return 1;
    }
    else if(array[0][1] == ' ' && ((array[0][0] == 'O' && array[0][2] == 'O')||(array[1][1] == 'O' && array[2][1] == 'O'))){
        array[0][1] = 'X';
        return 1;
    }
    else if(array[1][2] == ' ' && ((array[0][2] == 'O' && array[2][2] == 'O')||(array[1][0] == 'O' && array[1][1] == 'O'))){
        array[1][2] = 'X';
        return 1;
    }
    else if(array[2][1] == ' ' && ((array[2][0] == 'O' && array[2][2] == 'O')||(array[0][1] == 'O' && array[1][1] == 'O'))){
        array[2][1] = 'X';
        return 1;
    }
    else if(array[1][0] == ' ' && ((array[1][1] == 'O' && array[1][2] == 'O')||(array[1][0] == 'O' && array[1][1] == 'O'))){
        array[1][0] = 'X';
        return 1;
    }
    return 0;
}

void rotateClockwise(char array[3][3]){
	char temp = array[0][0];
	array[0][0] = array[2][0];
	array[2][0] = array[2][2];
	array[2][2] = array[0][2];
	array[0][2] = temp;
	temp = array[0][1];
	array[0][1] = array[1][0];
	array[1][0] = array[2][1];
	array[2][1] = array[1][2];
	array[1][2] = temp;
}   
//these 3 functions rotate the board, for when the player goes first
//this limits the number of variations, which means less if/else statements are needed

int rotateClockwise(char array[3][3], int rotations){
	for(int i = 0; i < rotations; i++){
    	rotateClockwise(array);
	}
	return 0;
}   

int counterClockwise(char array[3][3], int rotations){
	for(int i = 0; i < rotations; i++){
        for(int j = 0; j < 3; j++){
            rotateClockwise(array);
        }
	}
	return 0;
}

int twoPlayerGame(char array[3][3]){        
    cout << "Player 1 is O's, player 2 is X's" << endl;
    for(int i = 0; i < 4; i++){
    cout << "Player 1 - ";
    yourMove(array);
    printArray(array);
    if(playerOneWinCheck(array)){
        cout << "Player one wins!" << endl;
        playerOneWins++;
        return 0;
    }       //the two player game simply asks the players for their moves a total of 9 times
            //it checks to see if a player won, and ends the game early if one did
    cout << "Player 2 - ";
    yourMoveP2(array);
    printArray(array);
    if(playerTwoWinCheck(array)){
        cout << "Player two wins!" << endl;
        playerOneLosses++;
        return 0;
    }
    }

    cout << "Player 1 - ";
    yourMove(array);
    printArray(array);
    if(playerOneWinCheck(array)){
        cout << "Player one wins!" << endl;
        playerOneWins++;
        return 0;
    }
    else{
        cout << "It's a draw." << endl;
        playerOneDraws++;
        return 0;   //if no one has won and nine moves have been made, it's a draw
    }
}

bool playerOneWinCheck(char array[3][3]){   //this function checks every possible win, for player 1
    if((array[0][1] == 'O') && ((array[0][0] == 'O' && array[0][2] == 'O') || (array[1][1] == 'O' && array[2][1] == 'O'))){
        return true;
    }
    if((array[1][0] == 'O') && ((array[0][0] == 'O' && array[2][0] == 'O') || (array[1][1] == 'O' && array[1][2] == 'O'))){
        return true;
    }
    if((array[2][1] == 'O') && (array[2][0] == 'O' && array[2][2] == 'O')){
        return true;
    }
    if((array[1][2] == 'O') && (array[0][2] == 'O' && array[2][2] == 'O')){
        return true;
    }
    if((array[1][1] == 'O') && ((array[0][0] == 'O' && array[2][2] == 'O') || (array[2][0] == 'O' && array[0][2] == 'O'))){
        return 1;
    }
    return false;
}

bool playerTwoWinCheck(char array[3][3]){   //this function does the same, but for player 2
    if((array[0][1] == 'X') && ((array[0][0] == 'X' && array[0][2] == 'X') || (array[1][1] == 'X' && array[2][1] == 'X'))){
        return true;
    }
    if((array[1][0] == 'X') && ((array[0][0] == 'X' && array[2][0] == 'X') || (array[1][1] == 'X' && array[1][2] == 'X'))){
        return true;
    }
    if((array[2][1] == 'X') && (array[2][0] == 'X' && array[2][2] == 'X')){
        return true;
    }
    if((array[1][2] == 'X') && (array[0][2] == 'X' && array[2][2] == 'X')){
        return true;
    }
    if((array[1][1] == 'X') && ((array[0][0] == 'X' && array[2][2] == 'X') || (array[2][0] == 'X' && array[0][2] == 'X'))){
        return true;
    }
    return false;
}

void yourMoveP2(char array[3][3]){  //this is the same as the yourMove function for a 1 player game, but it puts X's
    int inputMove;                  //so it is used for player 2
    bool wrongInput = true;
    while(wrongInput){
        wrongInput = false;
        cout << "Enter your move: " << endl;
        cin >> inputMove;
    	switch (inputMove)
    	{               //A switch statement in a while loop is used for input, with the default
            case 1:     //catching all invalid input 
                if(array[0][0] == ' '){
                    array[0][0] = 'X';
                }
                else{
                cout << "Illegal move: That spot is taken" << endl;
        	    wrongInput = true;
                }
        	    break;
        	case 2:
        	    if(array[0][1] == ' '){
        	        array[0][1] = 'X';
        	    }
                else{
                    cout << "Illegal move: that spot is taken" << endl;
                    wrongInput = true;
                }
                break;
        	case 3:
        	    if(array[0][2] == ' '){
        	        array[0][2] = 'X';
        	    }
                else{
                    cout << "Illegal move: that spot is taken" << endl;
                    wrongInput = true;
                }
                break;
        	case 4:
        	    if(array[1][0] == ' '){
        	        array[1][0] = 'X';
        	    }
                else{
                    cout << "Illegal move: that spot is taken" << endl;
                    wrongInput = true;
                }
                break;
        	case 5:
        	    if(array[1][1] == ' '){
        	        array[1][1] = 'X';
        	    }
                else{
                    cout << "Illegal move: that spot is taken" << endl;
                    wrongInput = true;
                }
                break;
        	case 6:
        	    if(array[1][2] == ' '){
        	        array[1][2] = 'X';
        	    }
                else{
                    cout << "Illegal move: that spot is taken" << endl;
                    wrongInput = true;
                }
                break;
        	case 7:
        	    if(array[2][0] == ' '){
        	        array[2][0] = 'X';
        	    }
                else{
                    cout << "Illegal move: that spot is taken" << endl;
                    wrongInput = true;
                }
                break;
        	case 8:
        	    if(array[2][1] == ' '){
        	        array[2][1] = 'X';
        	    }
                else{
                    cout << "Illegal move: that spot is taken" << endl;
                    wrongInput = true;
                }
                break;
        	case 9:
        	    if(array[2][2] == ' '){
        	        array[2][2] = 'X';
        	    }
                else{
                    cout << "Illegal move: that spot is taken" << endl;
                    wrongInput = true;
                }
                break;
            default:
                cout << "Invalid move: enter a number from 1-9" << endl;
                wrongInput = true;
    	}
   	}
}

void eraseArray(char array[3][3]){  //this erases the board at the end of each game
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            array[i][j] = ' ';
        }
    }
}


