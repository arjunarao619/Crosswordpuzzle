/**
 * ENGG1110 Problem Solving by Programming
 *
 * Course Project
 *
 * I declare that the project here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   https://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name  : <your name>
 * Student ID    : <your student ID>
 * Class/Section : <your class/section>
 * Date          : <date>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Macros */
#define MAX_GRID 10
#define MAX_WORDLIST 8
#define MAX_WORD 11
#define MAX_FILENAME 260


/* NO global variables are allowed */


/* Read the letter grid from console into the 2D array parameter letterGird
 Return the size of the letter grid */
int readLetterGridFromConsole(char letterGrid[MAX_GRID][MAX_GRID]) {
    int row, col;
    int gridSize;
    
    printf("Enter the size of the letter grid:\n");
    scanf("%d", &gridSize);
    printf("Enter the letter grid:\n");
    
    for(row = 0; row < gridSize; row++) {
        for(col = 0; col < gridSize; col++) {
            /* In scanf(), use " %c" instead of "%c" to read the first non-whitespace character,
             so that the newline character at the end of the previous line can be ignored */
            scanf(" %c", &letterGrid[row][col]);
        }
    }
    
    return gridSize;
}


/* Read the word list from console into the 2D array parameter wordList
 Return the number of words */
int readWordListFromConsole(char wordList[MAX_WORDLIST][MAX_WORD]) {
    int i;
    int listSize;
    
    printf("Enter the size of the word list :\n");
    scanf("%d", &listSize);
    printf("Enter the word list:\n");
    for(i = 0; i < listSize; i++) {
        /* no & before wordList[i] since wordList[i] already represents the memory address */
        scanf("%s",  wordList[i]);
    }
    
    return listSize;
}


/* Read the letter grid from file into the 2D array parameter letterGird
 Return
 the size of the letter grid if successful
 -1 if there is any file reading error */
int readLetterGridFromFile(char letterGrid[MAX_GRID][MAX_GRID]) {//TODO
    
    
    FILE *infile1;
   // char fileLetterGrid[MAX_FILENAME];
    
//    printf("Enter filename of the letter grid: ");
//    scanf("%s",fileLetterGrid);

    infile1 = fopen("LetterGrid.txt","r");
    
    if(infile1 == NULL){
       printf("Error in reading the letter grid file. Program terminates.");
        exit(1);
   }
    
    int gridSize;
    fscanf(infile1,"%d",&gridSize);
    printf("\n%d",gridSize);
    
//    for(int i=0;i<gridSize;i++){
//        for(int j=0;j<gridSize;j++){
//            letterGrid[i][j] = getc(infile);
//        }
//    }
    
    fclose(infile1);
    return gridSize;
    return 0;
}


/* Read the word list from file into the 2D array parameter wordList
 Return
 the number of words if successful
 -1 if there is any file reading error */
int readWordListFromFile(char wordList[MAX_WORDLIST][MAX_WORD]) {//DONE
    
    
    //DOING - 3RD NOVEMBER
    FILE * infile;
    int listSize;
    infile = fopen("WordList.txt","r");
    listSize = fscanf(infile,"%d",&listSize); //scanning first line of text file to input the number of words in the list
    int i = 0;
    while(i<listSize){
        
        fscanf(infile, "%s", &wordList[i][0]);
        i++;
    }
    fclose(infile);
    return listSize;
}


/* Display the letter grid, assume gridSize <= 10 */
void printLetterGrid(char letterGrid[MAX_GRID][MAX_GRID], int gridSize) {
    
    
    /* For debugging */
    if(gridSize < 2 || gridSize > MAX_GRID) {
        printf("DEBUG: gridSize is %d but not between 2 and %d\n", gridSize, MAX_GRID);
        printf("Program terminates.\n");
        exit(1);
    }
    
    printf("### %d x %d Letter Grid ###\n", gridSize, gridSize);
    printf(" +");
    for(int x=0;x<gridSize;x++)printf(" %d",x);
    printf("\n");
    for(int y=0;y<gridSize+2;y++)printf(" +");
    
    for(int i=0;i<gridSize;i++){
        printf("\n%d + ",i);
        for(int j=0;j<gridSize;j++){
            printf("%c",letterGrid[i][j]);
        }
    }
    
    
    
}


/* Display the word list stored in wordList of size listSize with the matching status for each word */
void printWordList(char wordList[MAX_WORDLIST][MAX_WORD], int listSize, int matchingStatus[MAX_WORDLIST]) {
   
    
    /* For debugging */
    if(listSize < 1 || listSize > MAX_WORDLIST) {
        printf("DEBUG: listSize is %d but not between 1 and %d\n", listSize, MAX_WORDLIST);
        printf("Program terminates.\n");
        exit(1);
    }
    
    printf("\n### Word List of Size %d ###\n", listSize);
    
    char matchingStatus1[MAX_WORDLIST];
    
    for(int i=0;i<listSize;i++){
        if(matchingStatus[i] == 1){
            matchingStatus1[i] = 'X';
        }
    }
    
    for(int i=0;i<listSize;i++){
        printf("[%c] %s\n",matchingStatus1[i],wordList[i]);
    }
    
   
    
    
}


/* Check whether the input word is in the word list and whether it is matched before
 Return
 the index of the input word in the word list (i.e., a value between 0 and listSize - 1) if the input word is in the word list and has not been matched before
 listSize if the input word is in the word list but has been matched already
 -1 if the input word is not in the word list */
int checkWordList(char wordList[MAX_WORDLIST][MAX_WORD], int listSize, int matchingStatus[MAX_WORDLIST], char inputWord[MAX_WORD]) {
    
    
    for(int i=0;i<listSize;i++){
        if(strcmp(inputWord,wordList[i]) == 0){
            if(matchingStatus[i] == 1){
                return 0;//if match is found as a duplicate, return listSize (0 for now)
            }
            else return 1;//if match is found for the first time, return index (1 for now)
        }
        
    }
    return -1;//if no match is found, -1 is returned
    
 
}


/* Check whether the input word is in the letter grid in the specified row, column, and direction
 Return
 1 if the input word is in the letter grid in the specified row, column, and direction
 0 if the input word cannot be found in the letter grid in the specified row, column, and direction
 -1 if the search of the input word exceeds the boundary of the letter grid
 This function should not print anything, except debugging messages (if any) */
int checkLetterGrid(char letterGrid[MAX_GRID][MAX_GRID], int gridSize, char inputWord[MAX_WORD], int matchRow, int matchCol, int matchDirection) {
    
    int matchSize = 0;
    
    if(letterGrid[matchRow][matchCol] == inputWord[0]){
        matchSize++;
        
        if(matchDirection == 1){
            int count = 0;
            
            int match = 0;
            if(strlen(inputWord) > gridSize)return -1;
            if(strlen(inputWord) <=2){ //SPECIAL CASE ONLY FOR TWO-LETTERED WORDS
                if(letterGrid[matchRow+1][matchCol - 1] == inputWord[ count + 1 ]){
                    return 1;
                }
            }
            else{
                while(count < strlen(inputWord)){
                    if(letterGrid[matchRow+1][matchCol - 1] == inputWord[ count + 1 ]){
                        
                        count++;
                        match++;
                        matchRow++;
                        matchCol--;
                        
                    }
                    
                    
                }
            }
            if(match == strlen(inputWord)){
                return 1;
            }else return 0;
           
            
        }
        
        if(matchDirection == 2){
            int count = 0;
            
            int match = 0;
            if(strlen(inputWord) > gridSize)return -1;
            if(strlen(inputWord) <=2){ //SPECIAL CASE ONLY FOR TWO-LETTERED WORDS
                if(letterGrid[matchRow++][matchCol] == inputWord[ count + 1 ]){
                    return 1;
                }
            }
            else{
                while(count < strlen(inputWord)){
                    if(letterGrid[matchRow++][matchCol] == inputWord[ count + 1 ]){
                        
                        count++;
                        match++;
                        matchRow++;
                        
                    }
                    
                    
                }
            }
            if(match == strlen(inputWord)){
                return 1;
            }else return 0;
            
            
        }
        
        if(matchDirection == 3){
            int count = 0;
            
            int match = 0;
            if(strlen(inputWord) > gridSize)return -1;
            if(strlen(inputWord) <=2){ //SPECIAL CASE ONLY FOR TWO-LETTERED WORDS
                if(letterGrid[matchRow+1][matchCol + 1] == inputWord[ count + 1 ]){
                    return 1;
                }
            }
            else{
                while(count < strlen(inputWord)){
                    if(letterGrid[matchRow+1][matchCol + 1] == inputWord[ count + 1 ]){
                        
                        count++;
                        match++;
                        matchCol++;
                        matchRow++;
                        
                    }
                    
                    
                }
            }
            if(match == strlen(inputWord)){
                return 1;
            }else return 0;
            
            
        }
        
        if(matchDirection == 4){
            int count = 0;
            
            int match = 0;
            if(strlen(inputWord) > gridSize)return -1;
            if(strlen(inputWord) <=2){ //SPECIAL CASE ONLY FOR TWO-LETTERED WORDS
                if(letterGrid[matchRow][matchCol - 1] == inputWord[ count + 1 ]){
                    return 1;
                }
            }
            else{
                while(count < strlen(inputWord)){
                    if(letterGrid[matchRow][matchCol - 1] == inputWord[ count + 1 ]){
                        printf("%c",letterGrid[matchRow][matchCol-1]);
                        count++;
                        match++;
                        matchCol--;
                        
                    }
                    
                    
                }
            }
            if(match == strlen(inputWord)){
                return 1;
            }else return 0;
            
            
        }
        
        if(matchDirection == 6){
            int count = 0;
            
            int match = 0;
            if(strlen(inputWord) > gridSize)return -1;
            if(strlen(inputWord) <=2){ //SPECIAL CASE ONLY FOR TWO-LETTERED WORDS
                if(letterGrid[matchRow][matchCol + 1] == inputWord[ count + 1 ]){
                    return 1;
                }
            }
            else{
                while(count < strlen(inputWord)){
                    if(letterGrid[matchRow][matchCol + 1] == inputWord[ count + 1 ]){
                        
                        count++;
                        match++;
                        matchCol++;
                        
                    }
                    
                    
                }
            }
            if(match == strlen(inputWord)){
                return 1;
            }else return 0;
            
            
        }
        
        if(matchDirection == 9){
            int count = 0;
            
            int match = 0;
            if(strlen(inputWord) > gridSize)return -1;
            if(strlen(inputWord) <=2){ //SPECIAL CASE ONLY FOR TWO-LETTERED WORDS
                if(letterGrid[matchRow-1][matchCol + 1] == inputWord[ count + 1 ]){
                    return 1;
                }
            }
            else{
                while(count < strlen(inputWord)){
                    if(letterGrid[matchRow-1][matchCol +1] == inputWord[ count + 1 ]){
                        
                        count++;
                        match++;
                        matchCol++;
                        matchRow--;
                        
                    }
                    
                    
                }
            }

            if(match == strlen(inputWord)){
                
                return 1;
            }else return 0;
            
            
        }
        
        if(matchDirection == 8){
            int count = 0;
            
            int match = 0;
            if(strlen(inputWord) > gridSize)return -1;
            if(strlen(inputWord) <=2){ //SPECIAL CASE ONLY FOR TWO-LETTERED WORDS
                if(letterGrid[matchRow-1][matchCol] == inputWord[ count + 1 ]){
                    return 1;
                }
            }
            else{
                while(count < strlen(inputWord)){
                    if(letterGrid[matchRow-1][matchCol] == inputWord[ count + 1 ]){
                        
                        count++;
                        match++;
                        matchRow--;
                        
                    }
                    
                    
                }
            }
            if(match == strlen(inputWord)){
                return 1;
            }else return 0;
            
        }
        
        if(matchDirection == 7){
            int count = 0;
            
            int match = 0;
            if(strlen(inputWord) > gridSize)return -1;
            if(strlen(inputWord) <=2){ //SPECIAL CASE ONLY FOR TWO-LETTERED WORDS
                if(letterGrid[matchRow-1][matchCol - 1] == inputWord[ count + 1 ]){
                    return 1;
                }
            }
            else{
                while(count < strlen(inputWord)){
                    if(letterGrid[matchRow-1][matchCol - 1] == inputWord[ count + 1 ]){
                        
                        count++;
                        match++;
                        matchRow--;
                        matchCol--;
                        
                    }
                    
                    
                }
            }
            if(match == strlen(inputWord)){
                return 1;
            }else return 0;
            
        }
        
        
    }
    return 0;
}


/* Display the secret table */
void printSecretTable(/* put your parameter list here */) {
    
    
    /* TODO: Complete the function */
    
    
}

/* The main() function */
int main()
{
    int gridSize;
    char letterGrid[MAX_GRID][MAX_GRID];
    int listSize;
    char wordList[MAX_WORDLIST][MAX_WORD];
    int matchingStatus[MAX_WORDLIST];     /* Each element should be either 0 (not matched) or 1 (matched) */
    
    
    /* TODO: Complete the main() function by invoking the functions declared above */
    
    
    /* Ask the user whether to read the data from file */
    char choice;
    printf("Read data from file [Y/N]? \n");
    scanf("%c",&choice);
    
    
    
    /* Read the letter grid and the word list from file or console */
    if(choice == 'Y'){
        gridSize = readLetterGridFromFile(letterGrid);
        listSize = readWordListFromFile(wordList);
    }
    else if (choice == 'N'){
        gridSize = readLetterGridFromConsole(letterGrid);
        listSize = readWordListFromConsole(wordList);
    }
    
    /* Initialize all elements in the matchingStatus array to 0 */
    
    for(int i =0;i<MAX_WORDLIST;i++){
        matchingStatus[i] = 0;
    }
    
    /* FOR TESTING: Uncomment the following two statements to print the letter grid and the word list
     You can move them elsewhere after testing
     Please make sure the five arguments are initialized properly */
    printLetterGrid(letterGrid, gridSize);
    printWordList(wordList, listSize, matchingStatus);
    
    
    
    /* Read the user input repeatedly until the puzzle finishes */
    char inputWord[MAX_WORD];
    int status = -1;
    while(1){
        printf("Enter the word: ");
        scanf("%s",inputWord);
        
       status =  checkWordList(wordList,listSize,matchingStatus,inputWord);
        if(status == -1){
            printf("\nThe input word is not in the word list.\n");
        }
        else if (status == 0){
            printf("\nThe input word has aldready been matched before.\n");
        }
        else{
            int matchRow,matchCol,matchDir;
            printf("\nEnter the row number, the column number, and the direction (1-4 or 6-9):");
            scanf("%d %d %d",&matchRow,&matchCol,&matchDir);
            int result = checkLetterGrid(letterGrid,gridSize,inputWord,matchRow,matchCol,matchDir);
            if(result == -1){
                printf("The search exceeds the boundary of the letter grid.\n");
            }
            else if(result == 0){
                printf("\nThe input word cannot be found in the given location.\n");
            }
            else if(result == 1){
                printf("\nThe word is found!\n");
                //checking winning condition
                
                
            }
        }
    }
    
    
    return 0;
}

