#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#define MAX_ATTTEMPTS 6													

void realTimeDisp (int numAtt) {


	switch(numAtt) {
		case 0: printf("  +---+\n  |   |\n  |\n  |\n  |\n  |\n=========\n"); break;
		case 1: printf("  +---+\n  |   |\n  |   O --come on you've got this\n  |\n  |\n  |\n=========\n"); break;			/*live model code which will update each time the player guesses incorrectly*/
		case 2: printf("  +---+\n  |   |\n  |   O\n  |   |\n  |\n  |\n=========\n"); break;		
		case 3: printf("  +---+\n  |   |\n  |   O --choose your letters carefully!\n  |  /|\n  |\n  |\n=========\n"); break;		
		case 4: printf("  +---+\n  |   |\n  |   O\n  |  /|\\\n  |\n  |\n=========\n"); break;
		case 5: printf("  +---+\n  |   |\n  |   O\n  |  /|\\\n  |  /\n  |\n=========\n"); break;
		case 6: printf("  +---+\n  |   |\n  |   O --NOOOOOOOOOO!\n  |  /|\\\n  |  / \\\n  |\n=========\n"); break;
}
}

int main()  {
int wordLength = 0;
char catHint[30];
printf("                    ***WELCOME TO HANGMAN***\n");

start:																		/*program will loop back here if word entered is longer than max word length*/
	printf(" before we begin, please enter the max word length: ");
	scanf("%d", &wordLength);

char word[wordLength];

Notvalid:
	printf("Would player one please enter a word that is %d letters or less: ", wordLength);
	scanf("%s", word);

if(strlen(word) > wordLength) {
    printf("this is longer than the max word length you set. Please try again.\n");     /*Error message if you entered too long of a word*/
    goto Notvalid;
}

for(int i = 0; i <strlen(word);i++) {                                                   /*lines 42-57 are for checking for non-letters, and erroring if you do. Sends you back to line 34 if you do.*/
    word[i] = tolower(word[i]);
}
int isValidWord = 1;
for (int i = 0; i < strlen(word); i++) {                    
    if (!isalpha(word[i])) {
        isValidWord = 0;
        break;
    }
}
// If the word contains non-alphabetic characters, ask the player to re-enter
if (!isValidWord) {
    printf("The word contains invalid characters! Please enter a word using only letters.\n");      
    goto Notvalid;
}

printf("Now, will player 1 please enter a one word hint: ");			/*category hint*/
scanf("%s", catHint);

system("cls");

char goodLuck[5][50] = {							/*There will be a random good luck saying chosen out of this predetermined five.*/
"Best of luck to you!",
"hmmm, interesting word....Good luck!",
"Ooh, i wouldnt've thought of that!",
"player 2, I wish you the best",
"Let the game begin!!!!!"
};

srand(time(NULL));
int glNum = rand() % 5;

printf("%s\n",goodLuck[glNum]);


printf("Category hint is: %s\n",catHint);

char ready[5];

readyAsk:
printf("please enter yes if ready to begin: ");
scanf("%s", ready);

if(strcmp(ready, "yes") == 0) {
    system("cls");
}
else { 
    printf("huh? why did you type something else? please try again and put yes when you're ready to play\n");
    goto readyAsk;
}

if(strlen(word) != wordLength) {										/*makes the length of wordLength equal to the length of the string if it wasnt already*/
	wordLength = strlen(word);
}

char letterGuess;														/*This point downward is mainly just stuff I was testing, feel free to ignore it and write your own code*/
char result;
int incorrect = 0;
int correct = 0;


char guessed[wordLength]; 
memset(guessed, 0, sizeof(guessed)); 

while (incorrect < MAX_ATTTEMPTS && correct < wordLength) {
    realTimeDisp(incorrect); 		/*Live model */


    printf("Current word: ");				/*this is keeping progress for the game, showing blank spots and guessed letters*/
    for (int i = 0; i < wordLength; i++) {
        if (guessed[i]) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");

    
    printf("Please enter a letter to guess: ");
    scanf(" %c", &letterGuess);

    
    if (!isalpha(letterGuess)) {					/*make sure the input is a valid letter*/		
        printf("Not a valid letter! Try again.\n");
        continue;
    }

    letterGuess = tolower(letterGuess); // keep the letter lowercase//

    
    int alreadyGuessed = 0;
    for (int i = 0; i < wordLength; i++) {			/*to check if you already guessed the letter*/
        if (guessed[i] && word[i] == letterGuess) {
            alreadyGuessed = 1;
            break;
        }
    }

    if (alreadyGuessed) {
        printf("You already guessed that letter! Try again.\n");
        continue;
    }

    // Check if the guessed letter is in the word//
    int found = 0;
    for (int i = 0; i < wordLength; i++) {
        if (word[i] == letterGuess && !guessed[i]) {
            guessed[i] = 1; // Mark the letter as guessed//
            correct++;
            found = 1;
        }
    }

    if (found) {
        printf("Correct! '%c' is in the word.\n", letterGuess);
    } else {
        printf("Wrong guess! '%c' is not in the word.\n", letterGuess);
        incorrect++;
    }
}


realTimeDisp(incorrect);        /*this is the final hangman state*/


if (correct == wordLength) {
    printf("Congratulations! You guessed the word: %s\n", word);    /*win or lose*/
} else {
    printf("Game over! The word was: %s\n", word);
}

return 0;
}













	
		   
