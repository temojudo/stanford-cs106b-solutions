/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <algorithm>
#include <string>
#include "gboggle.h"
#include "grid.h"
#include "map.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const int NUM_COLS = 4;
const int MIN_LENGTH_OF_WORD = 4;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
void drawTable(Grid<char> &letters,Vector<char> &cubeLetters);
void humansTurn(Player &player,Grid<char> &letters);
bool isPossible(string word,Grid<char> &letters,int x1,int y1,int x2,int y2,Grid<bool> &highlightChars);
void computersTurn(Player player,Grid<char> &letters,Vector<char> &cubeLetters,string word,Grid<bool> &highlightChars);

/* Main program */
Grid<bool> usedLetters(NUM_COLS,NUM_COLS);
Set<string> usedWords;
Lexicon words("EnglishWords.dat");

void drawHighlight(Grid<bool> &highlightChars) {
	for (int i=0;i<highlightChars.numCols();i++)
		for (int j=0;j<highlightChars.numCols();j++)
			highlightCube(i,j,highlightChars[i][j]);
}

void clearHighlight(Grid<bool> &highlightChars) {
	for (int i=0;i<highlightChars.numCols();i++)
		for (int j=0;j<highlightChars.numCols();j++) {
			highlightCube(i,j,false);
			highlightChars[i][j]=false;
		}
}

int main() {
	GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
    giveInstructions();

	Grid<char> letters(NUM_COLS,NUM_COLS);
	Player player;

	Vector<char> cubeLetters;
	drawTable(letters,cubeLetters);

	player=HUMAN;
	humansTurn(player,letters);

	player=COMPUTER;
	Grid<bool> highlightChars(4,4);
	computersTurn(player,letters,cubeLetters,"",highlightChars);

    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

// [TODO: Fill in the rest of the code]
void drawTable(Grid<char> &letters,Vector<char> &cubeLetters) {
	Vector<string> cubes;

	cout<<"Enter 1 to choose cube letters or 0 for auto-generated cubes: ";
	int comb=getInteger();
	if (comb==1) {
		cout<<"You've to choose 16 strings and each string with 6 letters"<<endl;
		for (int i=1;i<=NUM_COLS*NUM_COLS;i++) {
			cout<<"Enter "<<i<<"-th string: ";
			string str=getLine();
			cubes.add(str);
		}
	} else for (int i=0;i<NUM_COLS*NUM_COLS;i++)
		cubes.add(STANDARD_CUBES[i]);

	drawBoard(NUM_COLS,NUM_COLS);
	for (int i=0;i<cubes.size();i++) {
		int x=randomInteger(0,cubes.size()-1);
		swap(cubes[x],cubes[i]);
	}

	for (int i=0;i<cubes.size();i++) {
		int x=randomInteger(0,5);
		labelCube(i/NUM_COLS,i%NUM_COLS,cubes[i][x]);
		letters[i/NUM_COLS][i%NUM_COLS]=cubes[i][x];
		cubeLetters.add(cubes[i][x]);
	}
}

void humansTurn(Player &player,Grid<char> &letters) {
	Grid<bool> highlightChars(NUM_COLS,NUM_COLS);
	while(true) {
		string word=getLine("Enter new not used possible word (empty word for finish): ");
		clearHighlight(highlightChars);
		if (word.length()==0) {
			cout<<"now wait for computer..."<<endl;
			break;
		}

		word=toLowerCase(word);
		if (word.length()<MIN_LENGTH_OF_WORD || usedWords.contains(word) || !words.contains(word) 
			|| !isPossible(toUpperCase(word),letters,0,0,NUM_COLS-1,NUM_COLS-1,highlightChars)) {
			
			cout<<"try other word"<<endl;
			continue;
		}

		usedWords.add(word);
		recordWordForPlayer(word,player);
		drawHighlight(highlightChars);
	}
}

bool isPossible(string word,Grid<char> &letters,int x1,int y1,int x2,int y2,Grid<bool> &highlightChars) {
	if (word.length()==0)
		return true;

	for (int i=x1;i<=x2;i++)
		for (int j=y1;j<=y2;j++)
			if (letters[i][j]==word[0] && !usedLetters[i][j]) {
				usedLetters[i][j]=true;
				if (isPossible(word.substr(1),letters,max(0,i-1),max(0,j-1),min(NUM_COLS-1,i+1),min(NUM_COLS-1,j+1),highlightChars)) { 
						usedLetters[i][j]=false;
						highlightChars[i][j]=true;
						return true;
				}
				usedLetters[i][j]=false;
			}

	return false;
}

void computersTurn(Player player,Grid<char> &letters,Vector<char> &cubeLetters,string word,Grid<bool> &highlightChars) {
	if (!words.containsPrefix(word)) return;

	if (word.length()>=MIN_LENGTH_OF_WORD && !usedWords.contains(word) && words.contains(word) 
		&& isPossible(toUpperCase(word),letters,0,0,NUM_COLS-1,NUM_COLS-1,highlightChars)) {
	
			usedWords.add(word);
			recordWordForPlayer(word,player);
	}

	for (int i=0;i<cubeLetters.size();i++)
		computersTurn(player,letters,cubeLetters,word+char(cubeLetters[i]-'A'+'a'),highlightChars);
}
