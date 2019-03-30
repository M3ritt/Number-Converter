#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

/*
 *converts a decimal number to a binary number
 * @param is the given number
 * creates variables for power and base
 * Checks base case of number being 0
 * Goes through a loop until number = 0
 * Takes the remainder of modulus division by 2 then divides number by 2
 * the binary number is then added to itself times num*base in order to the get power of zeros that are added
 * base is then increased by power of 10
*/
int decimalToBinary(int number) {
    int binary = 0, base = 1, num = 1;
    if(number == 0)
        return 0;
    while(number > 0){
        num = number%2;
        number /= 2;
        binary += num * base;
        base *= 10;
    }
    return binary;
} 

/*
 *converts a binary number to a decimal number
 *@param is the given number
 * creates a temporary number that is equal to @param
 * base is set to 1 because it is base case of binary, 2^0
 * while loop until temp is finished
 * the lastDigit from the temp is extracted due to modulus division
 * lastDigit is then multiplied by the proper base number and then added to create the decimal number
 * base is then adjusted for the next number
 */

int binaryToDecimal(int number) { 
    int temp = number, decimalNumber = 0, base = 1;
    while (temp > 0){ 
        int lastDigit = temp % 10; 
        temp = temp/10;
        decimalNumber += lastDigit * base;     
        base = base*2; 
    }
    return decimalNumber;
} 

/*
 *converts a decimal number to unary
 * @param is the given number
 * creates a string called unary and sets to to size of number+2 for the '0' and null terminator
 * sets all numbers equal to '1' using for loop
 * last number is set to '0' and then null terminator is placed
 * returns string of unary
 */
char* decimalToUnary(int number){
    char *unary = (char *)malloc(sizeof(char) * number+2);
    for(int i=0; i < number; i++){
        unary[i] = '1';
    }
    unary[number] = '0';
    unary[number+1] = '\0';
    return unary;
}

/*
 *converts a number from decimal to gammacode
 * @param is the int number
 * error checks if number is 1 to return 0, special base
 * then gets binary and changes to char[] n order to get length of offset
 * also sets a null terminator at end of offset since offset is set to size max
 * for loop ignores first position of offset and sets end of offset to null terminator again
 * length of offset is then set to unary 
 * final product is printed of length in unary, then offset
 */
int decimalToGamma(int number){
    if(number == 1){
        printf("0\n");
        return 0;
    }
    int binary = decimalToBinary(number);
    int max = 100;
    char offset[max];
    //itoa(binary, offset, 10);
    sprintf(offset, "%d\n", binary);
    offset[0] = '\n';
    int offsetLength = 0;
    for(int i = 0; i < sizeof(offset); i++){
        if(offset[i] == '1' || offset[i] == '0')
            offsetLength++;
        if(offset[i+1] == '\0')
            break;
    }
    for(int i = 0; i < offsetLength; i++){
        offset[i] = offset[i+1];
    }
    offset[offsetLength] = '\0';
    char* lengthInUnary = decimalToUnary(offsetLength);
    lengthInUnary[strlen(lengthInUnary)] = '\0';
    printf("%s%s\n", lengthInUnary, offset);
    return 0;
}

/*
 *returns a number based on whether the command is 'exit'
 * @param is the command that user entered
 * checks position of '('
 * checks if command contains 'exit'
 */
int isValid(char* command){
    int exit = 0;
    if(command[0] == 'e' && command[1] == 'x' && command[2] == 'i' && command[3] == 't'){
        exit = 1;
    } else if(command[7] == '(' || command[9] == '(')
        exit = 2;
    return exit;
}

/*
 * returns an int whether the number given actually is an int
 * goes through each character and checks whether it is a digit
 * returns a number, 1 being not an int, 0 being valid
 */
int isNumbers(char* number){
    int flag = 0;
    int len = strlen(number);
    for(int i = 0; i < len; i++){
        if(!isdigit(number[i])){
            flag = 1;
            break;
        }
    }
    return flag;
}
/*
 * main entrance point to program
 * reads user input and separates first portion which is before parantheses which is stored as 'choice'
 * reads number to be converted as 'number' and then converts char* to int if number is not NULL
 * error checks for not valid 'number' and wrong input method
 * based on 'choice' it chooses the correct method to call to convert
 * repeats loop
 */
int main(){ 
    char command[100];
    char *choice, *number, *convertedNum;
    int conversionNum, converted;
    int valid, checkingNumber = 1;
    printf("jmeritt$ ");
    fgets(command, sizeof(command), stdin);
    valid = isValid(command);  
    choice = strtok(command, "(");
    number = strtok(NULL, ")");
    if(number != NULL)
        checkingNumber = isNumbers(number);
    while(valid != 1){
        if(number != NULL)
          conversionNum = atoi(number); 
        if(valid == 0 || checkingNumber != 0){
            printf("[Error] Please enter the command correctly!\n");
        }else if(strcmp(choice, "dec2bin") == 0){
           converted = decimalToBinary(conversionNum);
           printf("%i \n", converted);
        } else if (strcmp(choice, "bin2dec") == 0){
           converted = binaryToDecimal(conversionNum);
           printf("%i \n", converted);
        }else if((strcmp(choice, "unarycode") == 0) && (conversionNum != 0)){
            convertedNum = decimalToUnary(conversionNum);
            printf("%s \n", convertedNum);
        }else if(strcmp(choice, "gammacode") == 0){
            decimalToGamma(conversionNum);
        }else
            printf("[Error] Please enter the command correctly!\n");
        printf("jmeritt$ ");
        fgets(command, sizeof(command), stdin);
        valid = isValid(command);
        choice = strtok(command, "(");
        number = strtok(NULL, ")");
        if(number != NULL)
            checkingNumber = isNumbers(number);
    }
    return 0;
}
