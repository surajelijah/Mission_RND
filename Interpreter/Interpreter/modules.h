#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structures.h"

int str_cmp(char *s1, char *s2)
{
	int i;
	for (i = 0; s1[i] && s2[i]; i++)
	{
		if (s1[i] != s2[i])
			return 0;
	}
	return 1;
}
int str_cpy(char *source, char *dest)
{
	int i;
	for (i = 0; source[i]; i++)
		dest[i] = source[i];
	dest[i] = '\0';
	return i;
}

void lower(char *str)
{
	int i = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= 'A'&&str[i] <= 'Z')
		{
			str[i] = str[i] - 'A' + 'a';
		}
	}
	return;
}
void upper(char *str){
	int i = 0;
	for (i = 0; str[i] != '\0'; i++){
		if (str[i] >= 'a' && str[i] <= 'z'){
			str[i] = str[i] - 'a' + 'A';
		}
	}
	return;
}
int getreg(char* r){
	lower(r);
	if (strcmp(r, "ax")==0){
		return 0;
	}
	else  if (strcmp(r, "bx")==0){
		return 1;

	}
	else  if (strcmp(r, "cx")==0){
		return 2;

	}
	else  if (strcmp(r, "dx")==0){
		return 3;

	}
	else  if (strcmp(r, "ex")==0){
		return 4;

	}
	else  if (strcmp(r, "fx")==0){
		return 5;

	}
	else  if (strcmp(r, "gx")==0){
		return 6;

	}
	else  if (strcmp(r, "hx")==0){
		return 7;

	}
	else{
		return -1;
	}

}
char* parse(char*query, int* i){
	// parses the query from ith character to the delimitters mentioned in the if statement
	//	char* cmd;
	int j = 0;
	char* tmp = (char*)malloc(sizeof(char) * 15);
	while (query[*i] != ',' && query[*i] != ' ' && query[*i] != '\n' && query[*i] != '['&& query[*i] != ']' && query[*i] != '=' && query[*i] != '\0')
	{
		tmp[j++] = query[(*i)++];
	}
	(*i)++;
	tmp[j] = '\0';
	return tmp;


}
int getOpCode(char* cmd,int i,char* c){
	lower(cmd);
	if (str_cmp(cmd, "mov")){
		// check if register to mem and ret 1 or mem to reg	and ret 2	
		char* para = parse(c, &i);
		int r = getreg(para);
		if (r>=0 && r<=7)
			return 2;
		else
			return 1;
	}
	else if (str_cmp(cmd, "add")){
		return 3;
	}
	else if (str_cmp(cmd, "sub")){
		return 4;
	}
	else if (str_cmp(cmd, "mul")){
		return 5;
	}
	else if (str_cmp(cmd, "jmp")){
		return 6;
	}
	else if (str_cmp(cmd, "if")){
		return 7;
	}
	else if (str_cmp(cmd, "eq")){
		return 8;
	}
	else if (str_cmp(cmd, "lt")){
		return 9;
	}
	else if (str_cmp(cmd, "gt")){
		return 10;
	}
	else if (str_cmp(cmd, "lteq")){
		return 11;
	}
	else if (str_cmp(cmd, "gteq")){
		return 12;
	}
	else if (str_cmp(cmd, "print")){
		return 13;
	}
	else if (str_cmp(cmd, "read")){
		return 14;
	}
	else if (str_cmp(cmd, "endif")){
		return 15;
	}
	else{
		return -1;
	}
}


int toint(char* temp){


	//	printf("%d    ", atoi(temp));
	return atoi(temp);

}


void initialiseymbolTable(int s){
	symTab = (symbol_table*)malloc(sizeof(symbol_table));
	symTab->size_of_symbolTable = s;
	symTab->index = 0;
	symTab->symbolTable = (symbols*)malloc(sizeof(symbols)*s);


}


int str_len(char* s){
	int i = 0;
	for (i = 0; s[i] != '\0'; i++){
		
	}
	return i;
}
int getOffset(char* varName){

	for (int i = 0; i < symTab->size_of_symbolTable; i++){
		if (str_cmp(symTab->symbolTable[i].name, varName)){
			return symTab->symbolTable[i].offset; //  address anamaata
		}
	}
	// if not found.
	return -1;
}

int addToInstTable(char* c){
// as of now max number of instructions are 25 !!!
	int i = 0;
	insTable[index_ins] = (instructions*)malloc(sizeof(instructions));
	char* cmd = parse(c, &i);
	int opCode = getOpCode(cmd,i,c);
	insTable[index_ins]->opCode = opCode;
	char* para;
	int p = 0;
	int ofset=-1;
	switch (opCode){
	case 1:
		// DIND NOT HANDLE MOVING ARRAYS
		//			MOV b[4], EX /* values of EX moves to B[4] */
		//move register to memory
		insTable[index_ins]->noOfParameters = 2;
		insTable[index_ins]->parameters = (int*)malloc(sizeof(int) * 2);
		
		// prameters are off set of the memory i.e, the variable and the reg number.
		para = parse(c, &i);
		ofset = getOffset(para);
		if (ofset == -1){
			printf("\nVariable Not Declared\n");
			getchar();
			exit(1);
		}
		para = parse(c, &i);
		p = getreg(para);// second parameter i.e the reg number.
		// MOV A,AX
		insTable[index_ins]->parameters[0] = ofset;
		insTable[index_ins]->parameters[1] = p;
		index_ins++;
		break;
	case 2:
		// move memory to register //		MOV DX,E
		insTable[index_ins]->noOfParameters = 2;
		insTable[index_ins]->parameters = (int*)malloc(sizeof(int) * 2);
		para = parse(c, &i);
		p = getreg(para);
		para = parse(c, &i);
		ofset = getOffset(para);
		if (ofset == -1){
			printf("\nVariable Not Declared\n");
			getchar();
			exit(1);
		}
		insTable[index_ins]->parameters[1] = ofset;
		insTable[index_ins]->parameters[0] = p;
		index_ins++;

		break;
	case 3:
		//for adding two numbers
		insTable[index_ins]->noOfParameters = 3;
		insTable[index_ins]->parameters = (int*)malloc(sizeof(int) * 3);
		para = parse(c, &i);
		p = getreg(para);
		insTable[index_ins]->parameters[0] = p;
		para = parse(c, &i);
		p = getreg(para);
		insTable[index_ins]->parameters[1] = p;
		para = parse(c, &i);
		p = getreg(para);
		insTable[index_ins]->parameters[2] = p;
		index_ins++;
		break;
	case 4:
		// for subtracting two numbers
		insTable[index_ins]->noOfParameters = 3;
		insTable[index_ins]->parameters = (int*)malloc(sizeof(int) * 3);
		para = parse(c, &i);
		p = getreg(para);
		insTable[index_ins]->parameters[0] = p;
		para = parse(c, &i);	
		p = getreg(para);
		insTable[index_ins]->parameters[1] = p;
		para = parse(c, &i);
		p = getreg(para);
		insTable[index_ins]->parameters[2] = p;
		index_ins++;
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		break;
	case 12:
		break;
	case 13:
		//for printing two numbers
		para = parse(c, &i);
		p = getreg(para);
		insTable[index_ins]->parameters = (int*)malloc(sizeof(int) * 1);
		insTable[index_ins]->parameters[0] = p;
		insTable[index_ins]->noOfParameters = 1;
		index_ins++;//to store next instruction

		break;
	case 14:
		// for READ COMMAND !
		para = parse(c, &i);
		p=getreg(para);
		insTable[index_ins]->parameters = (int*)malloc(sizeof(int) * 1);
		insTable[index_ins]->parameters[0] = p;
		insTable[index_ins]->noOfParameters = 1;
		index_ins++;//to store next instruction
		break;
	default:
		break;
	}
	return 1;
}
int addToSymbolTable(char* c){
	//returns -1 if cannot be added to symbol
	int i = 0;
	
	char* cmd= parse(c,&i);
	
	//int opcode = getOpCode(cmd);
	//returns -1 if operation is not recognised
	
	
	//lower(cmd)
	if (cmd[0]!='\0'&& str_cmp(cmd,"DATA"))
	{
		char* varname = parse(c, &i);
		// check if symoltab->index is less than symTab->sizeofthe symbol table 
		symTab->symbolTable[symTab->index].name = varname;
		
		symTab->symbolTable[symTab->index].size = unit_space;
		symTab->symbolTable[symTab->index].offset = end;
		
	//	symTab->symbolTable[symTab->index].type=??
		if (c[i-1] == '['){
			char* n = parse(c, &i);
			int s = toint(n);
			symTab->symbolTable[symTab->index].size = unit_space*s;
			symTab->symbolTable[symTab->index].offset = end;
			//end = end + unit_space*symTab->symbolTable[symTab->index].size;
			//	symTab->symbolTable[symTab->index].type=??
		}
		end = end + unit_space*symTab->symbolTable[symTab->index].size*sizeof(int);
		symTab->index++;
	}
	else if (str_cmp(cmd, "CONST")){
		char* varname = parse(c,&i);
		symTab->symbolTable[symTab->index].name = varname;
		char* val="";
		while ((strcmp(val,"")==0)){
			(val = parse(c, &i));
		}
		
	
		symTab->symbolTable[symTab->index].size = 0;
		symTab->symbolTable[symTab->index].offset = end;
		int* b = (int*)&memory[end];
		*b = toint(val);
		end = end + unit_space*sizeof(int);
		symTab->index++;
		//int* b = (int*)&memory[];
	}
	else{
		return -1;
	}
	return 1;
}
void read(int regno){
	printf("\nEnter the value for register %d: \n", regno);
	int d = 0;
	scanf("%d",&d);
	reg[regno] = d;
}
void print(int regno){
	printf("\nThe value for register %d: \n", regno);
	printf("%d", reg[regno]);
}
void add(int reg1, int reg2, int reg3){
	// adds reg2 and reg3 and stores it in reg1
	reg[reg1] = reg[reg2] + reg[reg3];
}
void sub(int reg1, int reg2, int reg3){
	// sub reg2 and reg3 and stores it in reg1
	reg[reg1] = reg[reg2] - reg[reg3];
}
void movRtoM(int offset, int regno){
	int* b = (int*)&memory[offset];
	*b = reg[regno];
}
void movMtoR(int regno, int offset){
	reg[regno] = *(int*)&memory[offset];
}
// to execute the intermediate code!!!
void execute(){
	
	int ins=0;

	while (programCounter != index_ins){
		//need to increment program counter !
		ins = insTable[programCounter]->opCode;
		switch (ins){
		case 1:
		//second parameter i.e the reg number.
		// MOV A,AX

	//			MOV AX, C /* now AX has value 5 */
	//			MOV BX, A /* whatever value A variable has will move to BX */
	//			MOV CX, B[0] /* whatever value B[0] has will move to CX */
	//			MOV FX, E /* moves value of E to FX */
	//			MOV C, DX /* value of DX moves to C */
	//			MOV b[4], EX /* values of EX moves to B[4] */
				//offset,regno.
			movRtoM(insTable[programCounter]->parameters[0], insTable[programCounter]->parameters[1]);
			programCounter++;
			break;


		case 2:
			movMtoR(insTable[programCounter]->parameters[0], insTable[programCounter]->parameters[1]);
			programCounter++;
			break;
		case 3:
			//for adding two numbers
			add(insTable[programCounter]->parameters[0], insTable[programCounter]->parameters[1], insTable[programCounter]->parameters[2]);
			programCounter++;
			break;
		case 4:
			
			// for subtracting two numbers
			sub(insTable[programCounter]->parameters[0], insTable[programCounter]->parameters[1], insTable[programCounter]->parameters[2]);
			programCounter++;

			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
			break;
		case 11:
			break;
		case 12:
			break;
		case 13:
			//for printing two numbers
			print(insTable[programCounter]->parameters[0]);
			programCounter++;
			break;
		case 14:
			// for READ COMMAND !
			read(insTable[programCounter]->parameters[0]);
			programCounter++;
			break;
		default:
			break;
		}
	}
	return ;
}
void readFile(FILE* fp){
	char c[252];
	fgets(c, 252, fp);
	int s = 0;
	while (fgets(c, 252, fp) != NULL){
		 s++;
		 if (str_cmp(c, "START:")){
			 fseek(fp, 0, SEEK_SET);
			 initialiseymbolTable(s);
			 break;
		 }
	}
	bool begin = false;
	while (fgets(c, 252, fp) != NULL){
		
		if (!(str_cmp(c, "START:"))&& !begin){
			int b=addToSymbolTable(c);
			if (b == -1){
				printf("\ncannot be added to symbol table\n");
			}
			
		}
		else if ((str_cmp(c, "START:"))){
			begin = true;
			continue;
		}
		else {

			int b=addToInstTable(c);
			if (b == -1){
				printf("\ncannot be added to Instruction table\n");
			}
		}

	}
}