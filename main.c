#include <stdio.h>
#include "stack.h"

#define CHAR_SIZE sizeof(char)

// Function definitions
char* readFile(char* fileName);
int runCode(char* codeIn);

// Global variables
struct hashNode* scopeStack = NULL;

int main(int numArgs, char* args[]) {
    // Make sure only a fileName was given from command line
    if(numArgs < 2 || numArgs > 2){
        printf("Invalid or no filename given.");
        return 1;
    }

    char* codeIn = readFile(args[1]);
    if(codeIn == NULL){
        printf("Unable to read file: %s",args[1]);
        return 1;
    }

    int codeRan = runCode(codeIn);
    if(codeRan != 0)  return codeRan;
}// END FUNCTION main

char* readFile(char* fileName){
    FILE *fileData;
    long byteSize;

    // read in entire file
    fileData = fopen(fileName,"r");
    if(fileData == NULL){
        printf("Unable to read file: %s.",fileName);
        return NULL;
    }
    fseek(fileData,0L,SEEK_END);  // Find the end of the file
    byteSize = ftell(fileData);   // Store the file size for later
    fseek(fileData,0L,SEEK_SET);  // Move iterator back to the start

    char* codeIn = (char*)calloc(byteSize,CHAR_SIZE);
    if(codeIn == NULL){
        printf("Unable to read file: %s",fileName);
        return NULL;
    }

    fread(codeIn, CHAR_SIZE, byteSize, fileData);
    fclose(fileData);

    // Remove all spaces from the file
    // LATER, PROBABLY EXTRACT FUNCTION POSITIONS HERE TOO
    int spaces = 0;
    for(int i=0;i<byteSize;i++){
        if(codeIn[i] != ' '){
            codeIn[spaces++] = codeIn[i];
        }
    }
    codeIn[spaces] = '\0';

    return codeIn;
}// END FUNCTION readFile

int runCode(char* codeIn){
    // Create hashmap to store all the variables in this scope
    const unsigned initialSize = 16;
    struct hashmap variables;
    hashmap_create(initialSize, &variables);
    // Push it to the top of the scope stack
    push(&scopeStack, variables);

    // Copy over the inputted code into new array to not mutate the old one
    char runningCode[strlen(codeIn)];
    strcpy(runningCode,codeIn);

    // Loop through each line of the new changeable array
    int lineNum = 0;
    int charactersRead = 0;
    // Use strtok as an iterator for each line
    char *line = strtok(runningCode, "\n");
    while(line != NULL){
        printf("Line %d: %s\n",++lineNum,line);
        charactersRead += strlen(line);
        char *command = (char*)calloc(3, CHAR_SIZE);
        char *params = (char*)calloc(strlen(line)-3, CHAR_SIZE);
        strcpy(params,line+3);
        strncpy(command, line, 3);
        printf("%s\n",command);
        printf("%s\n",params);

        // Move iterator to next line
        line=strtok(NULL,"\n");
    }// END WHILE
    return 0;
}// END FUNCTION runCode

void mapExample(){

    char* text = "Hello !";
    struct Data test = {"str",text};

    hashmap_put(&(*scopeStack).data, "greeting", strlen("greeting"), test);

    printf("%s, %s\n",hashmap_get(&(*scopeStack).data, "greeting", strlen("greeting")).type,(char*)hashmap_get(&(*scopeStack).data, "greeting", strlen("greeting")).data);

}