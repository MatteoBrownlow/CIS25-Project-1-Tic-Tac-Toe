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
