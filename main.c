#include <stdio.h>
#include "utils.h"
//#include <time.h> //Uncomment this and line 139 if you want a random seed

char Menu();
void PlayGame(char mode);
void ConvertToLower(char *c);
int guessWord(char *pointer, int trysLeft);
int GuessHardWord(char *pointer, int trysLeft, char correctPosition[], int* uniqueGuessed, char uniqueChar[], char characterGuessed[]);
void GetRandomWord(char savedWord[]);
int CheckList(char inputs[]);
void GetStatistics();

//Global variables for tracking statistics
int totalGamesPlayed = 0;
int totalGamesWon = 0;
int normalGamesPlayed = 0;
int normalGamesWon = 0;
int hardGamesPlayed = 0;
int hardGamesWon = 0;
int firstRoundWins = 0;
int secondRoundWins = 0;
int thirdRoundWins = 0;
int fourthRoundWins = 0;
int fifthRoundWins = 0;
int sixthRoundWins = 0;

int main() {
    char  input = Menu();
    if (input == '1' || input == '2')
        PlayGame(input);
    if (input == '3')
        GetStatistics();
    return 0;
}
// This will provide a menu of options and returns a character value between 1 and 4 or it will run this function till it gets a 1 or 4
char Menu(){
    printf("Please enter a number for the option that you want\n1.Play Normal mode\n2.Play Hard Mode\n3.Show statistics\n4.Exit\n=>");
    char input = getchar();
    char newline = getchar();
    if(newline != '\n'){
        newline = getchar();
    }
    if (input > '4' || input < '1')
        return Menu();
    else
        return input;
}

void PlayGame(char mode){
    totalGamesPlayed++;
    char savedWord[6];
    GetRandomWord(savedWord);

    //printf("%s\n", savedWord); //Uncomment this line if you want to see the word. This is for debugging

    int correctWord = 0;
    int trysLeft = 6;
    char correctPosition[5];
    int uniqueGuess = 0;
    char uniqueChar[] = {0};
    char wrongLetters[26] = {0};
    for (int i = 0; i < 26; ++i) {
        wrongLetters[i] = '0';
    }
    if (mode == '1') { // if the users inputs 1 from the menu it will play normal mode
        normalGamesPlayed++;
        while (correctWord < 5 && trysLeft > 0) {
            correctWord = guessWord(savedWord, trysLeft);//loads the guessWord function and keep loading till the user runs out of tries or guesses the word
            if (correctWord != 5) {
                printf("\nSorry that is an incorrect guess\n");
                trysLeft--;
                if (trysLeft == 0) {
                    printf("The word was %s\n", savedWord);
                }
            } else {
                printf("\nCorrect guess. The word was: %s\n", savedWord);
                totalGamesWon++;
                normalGamesWon++;
                // These if statements will track what rounds the user wins each game on
                if (trysLeft == 6)
                    firstRoundWins++;
                else if (trysLeft == 5)
                    secondRoundWins++;
                else if (trysLeft == 4)
                    thirdRoundWins++;
                else if (trysLeft == 3)
                    fourthRoundWins++;
                else if (trysLeft == 2)
                    fifthRoundWins++;
                else
                    sixthRoundWins++;
            }
        }
    }
    else{// the only way the user can reach this part if the input 2 for the menu function
        hardGamesPlayed++;
        while (correctWord < 5 && trysLeft > 0) {
            correctWord = GuessHardWord(savedWord, trysLeft, correctPosition, &uniqueGuess, uniqueChar,wrongLetters);
            if (correctWord != 5) {
                printf("\nSorry that is an incorrect guess\n");
                trysLeft--;
                if (trysLeft == 0 && correctWord != 5) {
                    printf("The word was %s\n", savedWord);
                }
            } else {
                printf("\nCorrect guess. The word was: %s\n", savedWord);
                totalGamesWon++;
                hardGamesWon++;
                // These if statements will track what rounds the user wins each game on
                if (trysLeft == 6)
                    firstRoundWins++;
                else if (trysLeft == 5)
                    secondRoundWins++;
                else if (trysLeft == 4)
                    thirdRoundWins++;
                else if (trysLeft == 3)
                    fourthRoundWins++;
                else if (trysLeft == 2)
                    fifthRoundWins++;
                else
                    sixthRoundWins++;
            }
        }
    }
    //After the player loses or wins they will be asked to play again. If they input y it will load a new game otherwise they will return to menu
    printf("\nDo you want to play again(y/n):");
    char yes_no = getchar();
    getchar();
    ConvertToLower(&yes_no);
    if(yes_no == 'y'){
        PlayGame(mode);
    } else
        main();
}
//This function gets a new word from the word list using the load word list function from utils.c file and then returns a word
void GetRandomWord(char savedWord[6]){
    char wordlist[DICT_SIZE][WORD_SIZE + 1];
    //srand(time(NULL)); //Uncomment this line and line 3 if you want a random seed
    load_word_list(wordlist);
    int guessNum = rand() % DICT_SIZE;
    for (int i = 0; i < 6; ++i) {
        savedWord[i] = wordlist[guessNum][i];
    }
}
// This function converts uppercase letter to lowercase
void ConvertToLower(char *c){
    if (*c >= 'A' && *c <= 'Z')
        *c = *c - 'A' + 'a';
}
// This function plays the normal game mode
int guessWord(char *pointer, int trysLeft){
    int correctLength = 0;
    int correctlyGuessed = 0;
    //We get the user input here
    printf("\n\nPlease enter your guess:\n");
    char input1 = '0';
    char input2 = '0';
    char input3 = '0';
    char input4 = '0';
    char input5 = '0';
    char newline = '0';
    //I used an if statement after each getchar() to quickly tell the user that they did not enter enough letters
    input1 = getchar();
    if (input1 == '\n'){
        printf("You have not entered 5 letters\n");
        return guessWord(pointer, trysLeft);
    }
    input2 = getchar();
    if (input2 == '\n'){
        printf("You have not entered 5 letters\n");
        return guessWord(pointer, trysLeft);
    }
    input3 = getchar();
    if (input3 == '\n'){
        printf("You have not entered 5 letters\n");
        return guessWord(pointer, trysLeft);
    }
    input4 = getchar();
    if (input4 == '\n'){
        printf("You have not entered 5 letters\n");
        return guessWord(pointer, trysLeft);
    }
    input5 = getchar();
    if (input5 == '\n'){
        printf("You have not entered 5 letters\n");
        return guessWord(pointer, trysLeft);
    }
    newline = getchar();
    //We put the user input into an array
    char inputs[] = {input1, input2, input3, input4, input5};
    char correctCharacter[5] = {0};//This array will be used to save the position of corrct letters
    char uniqueChar[5] = {0};// This array is used to save letter that were guessed but not in the correct position
    int uniqueGuessed = 0;
    //This for loop is used to check if the user inputted something other than letters
    for (int i  = 0; i  < 5; ++i ) {
        ConvertToLower(&inputs[i]);
        if (inputs[i] == '\n' || inputs[i] < 'a' || inputs[i] > 'z'){
            correctLength = 1;
            break;
        }
    }
    //This if statement will check if the word is correct and from the list and will then play the game and update arrays
    if (correctLength != 1 && newline == '\n' && CheckList(inputs) == 1) {
        for (int i = 0; i < 5; i++) {
            if (inputs[i] == pointer[i]) { //Correct letter in correct position
                for (int j = 0; j < uniqueGuessed + 1; ++j) {
                    if(inputs[i] == uniqueChar[j])
                        break;
                    if(j == uniqueGuessed && inputs[i] != uniqueChar[j]){//If it is a new letter it will add it to the list of correctly guessed letters
                        uniqueChar[uniqueGuessed] = inputs[i];
                        uniqueGuessed++;
                        break;
                        }
                    }
                correctlyGuessed++;
            } else {
                for (int j = 0; j < 5; ++j) {
                    if (inputs[i] == pointer[j]) {//Correct Letter in wrong position
                        for (int x = 0; x < uniqueGuessed + 1; x++) {
                            if (inputs[i] == uniqueChar[x]) {
                                break;
                            }
                            if(x == uniqueGuessed) {
                                uniqueChar[uniqueGuessed] = inputs[i];
                                uniqueGuessed++;
                                break;
                            }
                        }
                    }
                }
            }
        }
        for(int i = 0; i < 5;i++){
            if(inputs[i] == pointer[i])
                correctCharacter[i] = inputs[i];
            else
                correctCharacter[i] = '-';
            printf("%c",correctCharacter[i]);//Will print correct letter if in right position or a '-' otherwise
        }


        //This if statement will inform the user that they were incorrect and show them the letter that were correct and how many guesses they have remaining
        if (correctlyGuessed < 5){
            printf("\nYou have %d guesses remaining\n", trysLeft - 1);
            printf("Correctly guessed letters: ");
            for (int i = 0; i < uniqueGuessed; ++i) {
                printf("%c ", uniqueChar[i]);
            }
        }
        return correctlyGuessed;
    }else{//This will run the function again if the users has inputted an invalid word
        if(newline != '\n'){
            newline = getchar();
        }
        printf("Sorry the word needs to be 5 characters long and a real word\n");
        return guessWord(pointer, trysLeft);
    }
}
//This function is used to play the hard mode. The problem outline made me think that if they broke the rules of this mode even if it is a valid word, they don't lose a try
int GuessHardWord(char *hardPointer, int trysLeft, char correctPosition[], int *uniqueGuessed, char uniqueChar[], char charactersGuessed[]){
    int correctLength = 0;
    int correctlyGuessed = 0;
    int newUniqueGuessed = *uniqueGuessed;
    printf("\n\nPlease enter your guess:\n");
    char input1 = '0';
    char input2 = '0';
    char input3 = '0';
    char input4 = '0';
    char input5 = '0';
    char newline = '0';
    //I used an if statement after each getchar() to quickly tell the user that they did not enter enough letters
    input1 = getchar();
    if (input1 == '\n'){
        printf("You have not entered 5 letters\n");
        return GuessHardWord(hardPointer, trysLeft, correctPosition, &newUniqueGuessed, uniqueChar, charactersGuessed);
    }
    input2 = getchar();
    if (input2 == '\n'){
        printf("You have not entered 5 letters\n");
        return GuessHardWord(hardPointer, trysLeft, correctPosition, &newUniqueGuessed, uniqueChar, charactersGuessed);
    }
    input3 = getchar();
    if (input3 == '\n'){
        printf("You have not entered 5 letters\n");
        return GuessHardWord(hardPointer, trysLeft, correctPosition, &newUniqueGuessed, uniqueChar, charactersGuessed);
    }
    input4 = getchar();
    if (input4 == '\n'){
        printf("You have not entered 5 letters\n");
        return GuessHardWord(hardPointer, trysLeft, correctPosition, &newUniqueGuessed, uniqueChar, charactersGuessed);
    }
    input5 = getchar();
    if (input5 == '\n'){
        printf("You have not entered 5 letters\n");
        return GuessHardWord(hardPointer, trysLeft, correctPosition, &newUniqueGuessed, uniqueChar, charactersGuessed);
    }
    newline = getchar();
    char inputs[] = {input1, input2, input3, input4, input5};
    if (trysLeft >=6) {//If it is a new word it will try to reset values
        for (int i = 0; i < 5; ++i) {
            correctPosition[i] = '-';
            uniqueChar[i] = '0';
        }
    }
    for (int i  = 0; i  < 5; ++i ) {
        ConvertToLower(&inputs[i]);
        if (inputs[i] == '\n' || inputs[i] < 'a' || inputs[i] > 'z'){//Checks that user has entered letters
            correctLength = 1;
            break;
        }
    }

    for (int i = 0; i < 5; ++i) {
        if (correctPosition[i] != '0' && correctPosition[i] != '-' && correctPosition[i] != 0){//Checks that user is entering the letter that they guessed in the correct position in a previous round in this round
            if(correctPosition[i] != inputs[i]){//If they haven't they will be brought back to the start without losing a try
                printf("A previously found letter was not used in the correct position\n");
                return GuessHardWord(hardPointer, trysLeft, correctPosition, &newUniqueGuessed, uniqueChar, charactersGuessed);
            }
        }
    }
    for (int i = 0; i < newUniqueGuessed; ++i) {//Checking that the user is using a letter that they have previously guessed even if it was in the wrong position
        for (int j = 0; j < 5; ++j) {
            if(inputs[j] == uniqueChar[i]) {
                break;
            }
            if (j == 4 && inputs[j] == uniqueChar[i]) {//If they have missed a letter they will be returned to the start of the game without losing a try
                printf("A previously found letter in the wrong position was not used\n");
                return GuessHardWord(hardPointer, trysLeft,correctPosition, &newUniqueGuessed, uniqueChar, charactersGuessed);
            }
        }
    }
    //This is to check that they are not trying to use a letter that they have previously used and was wrong
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 26; j++){
            if (inputs[i] == charactersGuessed[j]){
                printf("You have guessed a letter that was previously guessed wrong\n");
                return GuessHardWord(hardPointer, trysLeft, correctPosition, &newUniqueGuessed, uniqueChar, charactersGuessed);
            }
        }
    }
    if (correctLength != 1 && newline == '\n' && CheckList(inputs) == 1) {
        for (int i = 0; i < 5; i++) {
            if (inputs[i] == hardPointer[i]) { //correct guess in correct position
                for (int j = 0; j < newUniqueGuessed + 1; ++j) {
                    if(inputs[i] == uniqueChar[j])//Checks letter is not already in the uniqueChar array
                        break;
                    if(j == newUniqueGuessed && inputs[i] != uniqueChar[j]){//Checks that letter is not already in the uniqueChar array and adds the letter to it
                        uniqueChar[newUniqueGuessed] = inputs[i];
                        newUniqueGuessed++;
                        break;
                    }
                }
                correctlyGuessed++;
            } else {
                for (int j = 0; j < 5; ++j) {
                    if (inputs[i] == hardPointer[j]) {//letter guessed but in the wrong position
                        for (int x = 0; x < newUniqueGuessed + 1; x++) {
                            if (inputs[i] == uniqueChar[x]) {
                                break;
                            }
                            if(x == newUniqueGuessed) {
                                uniqueChar[newUniqueGuessed] = inputs[i];
                                newUniqueGuessed++;
                                break;
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 26; ++j) {
                if (inputs[i] == hardPointer[j])//checks that the letter is not in the word to be guess so it is not added to the characters guessed list
                    break;
                if (inputs[i] == charactersGuessed[j]) {//Checks that the letter is not already in the list
                    break;
                }
                if (j == 25 && inputs[i] != charactersGuessed[j]){
                    for (int k = 0; k < newUniqueGuessed; ++k) {
                        if(charactersGuessed[j] == uniqueChar[k])
                            break;
                        if(k == newUniqueGuessed -1 && charactersGuessed[j] != uniqueChar[k])
                            for (int l = 0; l < 26; ++l) {
                                if (charactersGuessed[l] == '0'){
                                    charactersGuessed[l] = inputs[i];
                                    break;
                                }

                            }
                    }
                }
            }
        }

        for(int i = 0; i < 5;i++){
            if(inputs[i] == hardPointer[i])
                correctPosition[i] = inputs[i];
            else
                correctPosition[i] = '-';
            printf("%c",correctPosition[i]);
        }


        if (correctlyGuessed < 5){
            printf("\nYou have %d guesses remaining\n", trysLeft - 1);
            printf("Correctly guessed letters: ");
            for (int i = 0; i < newUniqueGuessed; ++i) {
                if (uniqueChar[i] != '0' && uniqueChar[i] != 0)
                    printf("%c ", uniqueChar[i]);
            }
        }
        if (correctlyGuessed >= 5 || trysLeft <= 0)
            return correctlyGuessed;
        else {
            printf("\nSorry that is an incorrect guess\n");
            trysLeft--;
            return GuessHardWord(hardPointer, trysLeft, correctPosition, &newUniqueGuessed, uniqueChar, charactersGuessed);
        }
    }else{
        if(newline != '\n'){
            newline = getchar();
        }
        printf("Sorry the word needs to be 5 characters long and a real word\n");
        return GuessHardWord(hardPointer, trysLeft, correctPosition, &newUniqueGuessed, uniqueChar, charactersGuessed);
    }
}
//A function to check if the user has entered a word that is in the list of words
int CheckList(char inputs[5]) {
    char wordlist[DICT_SIZE][WORD_SIZE + 1];
    load_word_list(wordlist);
    for (int i = 0; i < DICT_SIZE; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (inputs[j] != wordlist[i][j])
                break;
            if (j == 4 && inputs[j] == wordlist[i][j]) {
                return 1;
            }
        }
    }
    return 0;
}
//A function to show all the statistic when the user inputs 3 in the menu
void GetStatistics(){
    if (totalGamesPlayed >0) {//Shows statistics for all games of both modes if a game was played
        float totalPercentageWon = ((float)(totalGamesWon)/(float)totalGamesPlayed) * 100;
        printf("\n\nTotal Games Played: %d\n", totalGamesPlayed);
        printf("Total Games Won: %d\n", totalGamesWon);
        printf("Total Games Lost: %d\n", totalGamesPlayed - totalGamesWon);
        printf("Percentage of Total Games Won: %.2f%c\n\n", totalPercentageWon, '%');
        if (normalGamesPlayed > 0){ //Shows statistics for the normal mode
            float normalPercentageWon = ((float)(normalGamesWon)/(float)normalGamesPlayed) * 100;
            printf("Normal Games Played: %d\n", normalGamesPlayed);
            printf("Normal Games Won: %d\n", normalGamesWon);
            printf("Normal Games Lost: %d\n", normalGamesPlayed - normalGamesWon);
            printf("Percentage of Normal Games Won: %.2f%c\n\n", normalPercentageWon, '%');
        } else //Shows this message if the player hasn't played a normal mode game
            printf("You have not played a normal game yet\n\n");
        if (hardGamesPlayed > 0){//Shows statistics for the hard mode
            float hardPercentageWon = ((float)(hardGamesWon)/(float)hardGamesPlayed) * 100;
            printf("Hard Games Played: %d\n", hardGamesPlayed);
            printf("Hard Games Won: %d\n", hardGamesWon);
            printf("Hard Games Lost: %d\n", hardGamesPlayed - hardGamesWon);
            printf("Percentage of Hard Games Won: %.2f%c\n\n", hardPercentageWon, '%');
        }
        else//Shows this message if the player hasn't played a hard mode game
            printf("You have not played a Hard Game yet\n\n");

    }
    else //Shows this message if the player hasn't played any game
        printf("No game has been played yet\n\n");
    //This is to show a histogram of which rounds that the user has won on using '*'
    printf("Histogram of guesses taken:\n");
    printf("First Round: |");
    for (int i = 0; i < firstRoundWins; ++i)
        printf("*");
    printf("\n");
    printf("Second Round:|");
    for (int i = 0; i < secondRoundWins; ++i)
        printf("*");
    printf("\n");
    printf("Third Round: |");
    for (int i = 0; i < thirdRoundWins; ++i)
        printf("*");
    printf("\n");
    printf("Fourth Round:|");
    for (int i = 0; i < fourthRoundWins; ++i)
        printf("*");
    printf("\n");
    printf("Fifth Round: |");
    for (int i = 0; i < fifthRoundWins; ++i)
        printf("*");
    printf("\n");
    printf("Sixth Round: |");
    for (int i = 0; i < sixthRoundWins; ++i)
        printf("*");
    printf("\n\n");
    main();
}