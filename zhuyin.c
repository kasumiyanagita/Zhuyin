#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <time.h>
#include "zhuyin.h"

void clearInputBuffer(void) {
	// Discard all remaining char's from the standard input buffer: 
	while (getchar() != '\n')
	{
		; // do nothing! 
	}
}

// Wait for user to input the "enter" key to continue 
void suspend(void) {
	printf("<ENTER> to continue...");
	clearInputBuffer();
	putchar('\n');
}

void displayWelcomeMessage(void) {
	printf("Welcome to Zhuyin!\n\n");
	suspend();
}

int inputInt(void)
{
	char newLine = 'X';
	int wholeNum;

	while (newLine != '\n')
	{
		scanf("%d%c", &wholeNum, &newLine);
		if (newLine != '\n')
		{
			clearInputBuffer(); //When incorrect type is inputted, such as char instead of int, input is left in the buffer and will infinitely loop into the next scanf, hence need to clear the buffer when input is invalid
			printf("Error! Input a whole number: ");
		}
	}
	return wholeNum;
}

int inputIntRange(int min, int max) {
	int num2;
	int flag = 0;
	while (flag == 0) {
		num2 = inputInt();
		if (num2 > max || num2 < min) {
			printf("ERROR! Value must be between %d and %d inclusive: ", min, max);
		}
		else flag = 1;
	}
	return num2;
}

int selectQuizType() {
	int choice;

	printf(" ------------------ \n"
		   "| SELECT QUIZ TYPE |\n"
		   " ------------------ \n\n"
		"1. Zhuyin to Alphabets\n"
		"2. Alphabets to Zhuyin\n"
		"----------------------\n"
		"0. Exit the game\n\n"

		"Select the quiz type: ");
	choice = inputIntRange(0, 2);

	return choice;
}

int selectQuizDifficulty(){
	int choice;

	printf("\n ------------------- \n"
		   "| SELECT DIFFICULTY |\n"
		   " ------------------- \n\n"
		"1. Easy (You can choose the answer from 4 options)\n"
		"2. Normal (You need to type everything by yourself)\n"
		"----------------------\n"
		"0. Return to select game type\n\n"

		"Select the difficulty: ");
	choice = inputIntRange(0, 2);

	return choice;
}

void exitMessage(){
	printf("Thank you for playing!\n\n");
}

int selectGameMode(){
	int gameModeSelect = 1;
	int quizType;
	int quizDifficulty;
	int gameMode;

	while (gameModeSelect){
		quizType = selectQuizType();

		//exit the game if a user selected 0 (exit the game)
		if (quizType == 0){
			gameModeSelect = 0;
			exitMessage();
		}

		//select the difficulty if quizType is not 0
		else {
			quizDifficulty = selectQuizDifficulty();
			if (quizDifficulty != 0){
				gameModeSelect = 0;

				//assign a value 1-4 to each game mode (gameMode)
				//(value to assign). (Type) (Difficulty) ((quizType), (quizDifficulty))
				//1. Zhuyin to Alpha Easy (1, 1)
				//2. Zhuyin to Alpha Norm (1, 2)
				//3. Alpha to Zhuyin Easy (2, 1)
				//4. Alpha to Zhuyin Norm (2, 2)

				if (quizType == 1 && quizDifficulty == 1){
					gameMode = 1;
				}
				else if (quizType == 1 && quizDifficulty == 2){
					gameMode = 2;
				}
				else if (quizType == 2 && quizDifficulty == 1){
					gameMode = 3;
				}
				else {
					gameMode = 4;
				}
			}
		}
	}

	return gameMode;
}

void gameStartHeader(int gameMode){
	switch (gameMode){
		case 1:
		printf("\n ----------------------\n"
			   "|ZHUYIN TO ALPHA [EASY]|\n"
			   " ----------------------\n"
			   "*** GAME START! ***\n");
		break;

		case 2:
		printf("\n ------------------------\n"
			   "|ZHUYIN TO ALPHA [NORMAL]|\n"
			   " ------------------------\n"
			   "*** GAME START! ***\n");
		break;

		case 3:
		printf("\n ----------------------\n"
			   "|ALPHA TO ZHUYIN [EASY]|\n"
			   " ----------------------\n"
			   "*** GAME START! ***\n");
		break;

		case 4:
		printf("\n ----------------------\n"
			   "|ALPHA TO ZHUYIN [NORMAL]|\n"
			   " ----------------------\n"
			   "*** GAME START! ***\n");
		break;
	}
}
int zhuyinToAlphaEasy(){
	int i, j, index = 1, score = 0, randNum, anotherRandomNum, correctAns, choice, alSelectedAns[4] = { 0 };

	randNum = getRandomNumber();
	printf("  ");
	displayZhuyin(randNum);
	alSelectedAns[0] = randNum;

	correctAns = getRandomChoice();
	printf("Which of the following represents the sound this alphabet makes?\n\n");
	for (i = 1; i < 5; i++)
	{
		if (i == correctAns)
		{
			printf("%d: ", i);
			displayAlpha(randNum);
		}
		else
		{
			anotherRandomNum = getRandomNumber();
			for (j = 0; j < 4; j++)
			{
				if (anotherRandomNum == alSelectedAns[j])
				{
					anotherRandomNum = getRandomNumber();
					j = 0;
				}
			}
			alSelectedAns[index] = anotherRandomNum;
			index++;
			printf("%d: ", i);
			displayAlpha(anotherRandomNum);
		}
	}
	printf("\nAnswer: ");
	scanf("%d", &choice);

	if (choice == correctAns)
	{
		printf("Correct! Well done.\n\n");
		score++;
	}
	else
	{
		printf("Wrong! Study harder...^_^\n\n");
	}

	return score;
}

int zhuyinToAlphaNorm(){
	int score = 0;
	return score;
}

void questionHeader(int questionNum){
	printf("\n[Question %d]\n", questionNum);
}

int getInputAnswer(){
	int answer;
	printf("Answer: ");
	answer = inputIntRange(1, 4);
	return answer;
}

//display English alphabets that represents a single Zhuyin character
//with 4 choices of a Zhuyin character
int alphaToZhuyinEasy(){
	int score = 0, randNum, correctChoice, wrongChoice, i, j;
	int answer, sameChoice;

	//save characters that already displayed as one of choices
	//to avoid displaying the same choice of characters
	int choices[4] = {0};

	//get a random number to define which English alphabets to display
	randNum = getRandomNumber();

	//display English alphabets that represents a single Zhuyin character
	displayAlpha(randNum);

	//define which is the correct choice (1-4)
	correctChoice = getRandomChoice();

	//display 4 choices
	for (i = 1; i < 5; i++){

		//display the correct choice
		if (i == correctChoice){
			printf("%d: ", i);
			displayZhuyin(randNum); //use the same number "randNum" as displayAlpha
			printf("\n");
			//save the correct choice in choices array.
			choices[i-1] = randNum;
		}
		//display 3 wrong choices
		else {
			//get a random number to generate a wrong choice
			wrongChoice = getRandomNumber(); 
			sameChoice = 0;

			//validate the number for the choice to prevent the same choice is not be displayed
			while (sameChoice == 0){
				//validate the choice
				for (j=0; j<4; j++){
					if (wrongChoice == choices[j]){
						sameChoice = 1;
					}
				}
				//reinitialize the choice when it's the same
				if (sameChoice == 1){
					wrongChoice = getRandomNumber();
					//initialize sameChoice as 0 until it is validated again
					sameChoice = 0;
				}
				//Add the choice to choices array if it's not the same as any other choice
				else {
					choices[i-1] = wrongChoice;
					//initialize sameChoice as 1 so it exits the loop
					sameChoice = 1;
				}

			}
			

			//display the wrong choice
			printf("%d: ", i);
			displayZhuyin(choices[i-1]);
			printf("\n");
		}
	}
	//get input for an answer
	answer = getInputAnswer();
	
	//get score+1 if the answer is correct
	if (answer == correctChoice){
		printf("Correct!\n");
		score = 1;
	}
	else printf("Incorrect!\n");

	return score;
}



int alphaToZhuyinNorm(){
	int score = 0;
	return score;
}

void displayResult(int score){
	printf("\n*** FINISH ***\n\n"
		   " --------------\n"
		   "| SCORE RESULT |\n"
		   " --------------\n\n");
	printf("Your total score is: %d\n\n", score);
	suspend();
}



//get random number in range of 1-37
int getRandomNumber(){
	int num = 38;
	while (num < 1 || num > 37){
		num = rand();
	}
	return num;
}

//get random number in range of 1-4
int getRandomChoice(){
	int num = 5;
	while (num < 1 || num > 4){
		num = rand();
	}
	return num;
}

//Display a single Zhuyin character
void displayZhuyin(int randomNum){
	switch (randomNum)
	{
	case 1:
		printf("£t\n");
		break;
	
	case 2:
		printf("£u\n");
		break;
		
	case 3:
		printf("£v\n");
		break;
		
	case 4:
		printf("£w\n");
		break;

	case 5:
		printf("£x\n");
		break;
	
	case 6:
		printf("£y\n");
		break;
		
	case 7:
		printf("£z\n");
		break;
		
	case 8:
		printf("£{\n");
		break;

	case 9:
		printf("£|\n");
		break;
	
	case 10:
		printf("£}\n");
		break;
		
	case 11:
		printf("£~\n");
		break;
		
	case 12:
		printf("£¡\n");
		break;

	case 13:
		printf("£¢\n");
		break;
	
	case 14:
		printf("££\n");
		break;
		
	case 15:
		printf("£¤\n");
		break;
		
	case 16:
		printf("£¥\n");
		break;

	case 17:
		printf("£¦\n");
		break;
	
	case 18:
		printf("£§\n");
		break;
		
	case 19:
		printf("£¨\n");
		break;
		
	case 20:
		printf("£©\n");
		break;
		
	case 21:
		printf("£ª\n");
		break;
	
	case 22:
		printf("£«\n");
		break;
		
	case 23:
		printf("£¬\n");
		break;
		
	case 24:
		printf("£­\n");
		break;
		
	case 25:
		printf("£®\n");
		break;
	
	case 26:
		printf("£¯\n");
		break;
		
	case 27:
		printf("£°\n");
		break;
		
	case 28:
		printf("£±\n");
		break;
		
	case 29:
		printf("£²\n");
		break;
	
	case 30:
		printf("£³\n");
		break;
		
	case 31:
		printf("£´\n");
		break;
		
	case 32:
		printf("£µ\n");
		break;

	case 33:
		printf("£¶\n");
		break;
	
	case 34:
		printf("£·\n");
		break;
		
	case 35:
		printf("¤@\n");
		break;
		
	case 36:
		printf("£¹\n");
		break;

	case 37:
		printf("£º\n");
		break;		
	}
}

//Display English characters to represent a single Zhuyin character
void displayAlpha(int randomNum){
	switch (randomNum){
	case 1:
		printf("be\n");
		break;
	
	case 2:
		printf("pe\n");
		break;
		
	case 3:
		printf("me\n");
		break;
		
	case 4:
		printf("fe\n");
		break;

	case 5:
		printf("de\n");
		break;
	
	case 6:
		printf("te\n");
		break;
		
	case 7:
		printf("ne\n");
		break;
		
	case 8:
		printf("le\n");
		break;

	case 9:
		printf("ge\n");
		break;
	
	case 10:
		printf("ke\n");
		break;
		
	case 11:
		printf("he\n");
		break;
		
	case 12:
		printf("ji\n");
		break;

	case 13:
		printf("qi\n");
		break;
	
	case 14:
		printf("xi\n");
		break;
		
	case 15:
		printf("zhi\n");
		break;
		
	case 16:
		printf("chi\n");
		break;

	case 17:
		printf("shi\n");
		break;
	
	case 18:
		printf("ri\n");
		break;
		
	case 19:
		printf("zi\n");
		break;
		
	case 20:
		printf("ci\n");
		break;
		
	case 21:
		printf("si\n");
		break;
	
	case 22:
		printf("a\n");
		break;
		
	case 23:
		printf("o\n");
		break;
		
	case 24:
		printf("e\n");
		break;
		
	case 25:
		printf("e^\n");
		break;
	
	case 26:
		printf("ai\n");
		break;
		
	case 27:
		printf("ei\n");
		break;
		
	case 28:
		printf("ao\n");
		break;
		
	case 29:
		printf("ou\n");
		break;
	
	case 30:
		printf("an\n");
		break;
		
	case 31:
		printf("en\n");
		break;
		
	case 32:
		printf("ang\n");
		break;
		
	case 33:
		printf("eng\n");
		break;
	
	case 34:
		printf("er\n");
		break;
		
	case 35:
		printf("yi\n");
		break;
		
	case 36:
		printf("wu\n");
		break;

	case 37:
		printf("yu\n");
		break;		
	}
}

//start the quiz based on gameMode user chose
//10 questions each
int startQuiz(int gameMode){
	int score = 0, i;

	switch (gameMode){
		case 1:
		for (i=0; i<10; i++){
		questionHeader(i+1);
		score += zhuyinToAlphaEasy();
		}
		break;

		case 2:
		for (i=0; i<10; i++){
		questionHeader(i+1);
		score += zhuyinToAlphaNorm();
		}
		break;

		case 3:
		for (i=0; i<10; i++){
		questionHeader(i+1);
		score += alphaToZhuyinEasy();
		}
		break;

		case 4:
		for (i=0; i<10; i++){
		questionHeader(i+1);
		score += alphaToZhuyinNorm();
		}
		break;
	}
	return score;
}



