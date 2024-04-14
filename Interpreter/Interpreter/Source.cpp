/*


26th May : Compilers
-> In memory intermediate language generation + execution
-> Persisting the intermediate language into a file and its related symboltables, metadata etc and executing it. (Similar to .o files in c)
-> Creating a C like program from the intermediate language.

Sample Program :
DATA B
DATA A
DATA C[4]
DATA D
CONST E = 0
START:
READ AX
READ BX
MOV A, AX
MOV B, BX
ADD CX, AX, BX
X:
READ AX
SUB DX, AX, BX
PRINT DX
PRINT CX
IF CX EQ DX THEN
MOV C[0], CX
PRINT C[0]
ELSE
MOV C[1], DX
PRINT C[1]
JUMP X
ENDIF
PRINT E
Sample Input /Output
Input :
2 2 6
Output: 4 4
4 4 4

Input 2 :
5 3 6 0
(Goes into x label again)
11 (takes input into AX)
Ouput 2:
8 3 3 0
8 8 8 0




*/


#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include"modules.h"

void intermediateFile(){

}

int main(){

	
	
	
	/*	char* memory = (char*)malloc(200);
	
	int end = 0;
	char* a = &memory[end];
	end = end + sizeof(char);
	int offset = end;
	*a = 'b';
	int* b = (int*)&memory[end];
	end = end + sizeof(int);
	*b = 10;
	printf("%c,%d",((char*)memory)[0],(int*)memory[offset]);
	getchar();

*/

	FILE * fp = fopen("code.txt", "r");

	readFile(fp);
	execute();
	getchar();
}