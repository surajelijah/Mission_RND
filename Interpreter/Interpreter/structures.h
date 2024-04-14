#pragma once
#include<malloc.h>
#include<stdio.h>


typedef struct {
	char* name;
	int offset;
	int size;
	char* type;
}symbols;

int unit_space = 1;
int end = 0;
//typecast int to short to store an int in one byte.
typedef struct {

	symbols *symbolTable;
	int size_of_symbolTable;
	int index;

}symbol_table;


symbol_table* symTab=NULL;

char* memory = (char*)malloc(500);
 
int reg[8];



typedef struct{

	int opCode;
	int* parameters;
	int noOfParameters;

}instructions;

instructions* insTable[25];

int programCounter = 0;
int index_ins = 0;
int max_ins = 150;

//i.e, number of instructions


typedef struct {

	char* reg;
	char* dataType;
	void* value;// int value

}registers;