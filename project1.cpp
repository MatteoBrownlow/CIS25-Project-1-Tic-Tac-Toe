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
