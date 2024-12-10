#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

												

void realTimeDisp (int numAttempts, int maxAttempts) {

 int progress = numAttempts * (6.0 / maxAttempts); 
	switch(progress) {
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
int numAttempts, maxAttempts;
printf("                    ***WELCOME TO HANGMAN***\n");

start:																		/*program will loop back here if word entered is longer than max word length, or if anyting that isnt a positive number is entered.*/
    printf("Before we begin, please enter the max word length: ");

    if (scanf("%d", &wordLength) != 1 || wordLength <= 0) {
        printf("Invalid input. Please enter a positive number.\n");
        while (getchar() != '\n'); 
        goto start;
    }

    printf("Please enter if you would like six, twelve, or eighteen attempts: ");
    scanf("%d", &maxAttempts);

    if (maxAttempts != 6 && maxAttempts != 12 && maxAttempts != 18) {
        printf("You selected an invalid number. Please start over.\n");
        goto start;
    }

char *word = malloc((wordLength + 1) * sizeof(char));
if (!word) {
        printf("Memory allocation failed. Exiting program.\n");
        return 1;
}
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
for (int i = 0; i < strlen(word); i++) {                                                /*Code to make sure input is a valid word with valid characters*/
    if (!isalpha(word[i])) {
        isValidWord = 0;
        break;
    }
}
                                                                                             
if (!isValidWord) {
    printf("The word contains invalid characters! Please enter a word using only letters.\n");      
    goto Notvalid;
}

	printf("Now, will player 1 please enter a one word hint: ");			            /*category hint*/
	scanf("%s", catHint);

	printf("\e[1;1H\e[2J");

char goodLuck[5][50] = {							                                    /*There will be a random good luck saying chosen out of this predetermined five.*/
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
    printf("\e[1;1H\e[2J");
}
else { 
    printf("huh? why did you type something else? please try again and put yes when you're ready to play\n");
    goto readyAsk;
}

if(strlen(word) != wordLength) {										/*makes the length of wordLength equal to the length of the string if it wasnt already*/
	wordLength = strlen(word);
}

char letterGuess;														/*This is when the game begins*/
char result;
int incorrect = 0;
int correct = 0;


char guessed[wordLength]; 
memset(guessed, 0, sizeof(guessed)); 

while (incorrect < maxAttempts && correct < wordLength) {
    realTimeDisp(incorrect, maxAttempts); 		/*Live model*/


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
            guessed[i] = 1;                             // Mark the letter as guessed//
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


realTimeDisp(incorrect, maxAttempts);        /*this is the final hangman state*/


if (correct == wordLength) {
    printf("Congratulations!\nYou guessed the word: %s\n", word);    /*win or lose*/
} else {
    printf("Game over! The word was: %s\n", word);
}

free(word);
return 0;
}













	
		   
