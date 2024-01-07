#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "zhuyin.c"


int main() {
	//variable declaration
	int score = 0;
	int gameMode;

	//srand() for rand() to generate different options
	//each time program calls rand()
	srand(time(NULL));

	//display welcome message
	displayWelcomeMessage();

	//select game mode
	gameMode = selectGameMode();

	//start the quiz based on gameMode user chose
	//10 questions in each game
	gameStartHeader(gameMode);
	score = startQuiz(gameMode);
	
	//display the total score that a user got
	displayResult(score);

	//display exit message
	exitMessage();

	return 0;
}
