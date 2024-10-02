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
