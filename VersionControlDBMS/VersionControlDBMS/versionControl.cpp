#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include"Modules.h"

// as of now a new record is being created even if  u are updating only 2 cols and the entire record is being replaced as the latest version and previous version moves  down.
// a simple soln to implement the optimised updation of only few cols can be getting array of cells and 
// while sending it to update  function we can send it as a array of cells (instead of sending linked lists of "ALL THE "cells with updated values) we can send only cols
// now compare the col names which are updated by tracersing in the linked list and reaplce those cells with new cells.
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

void commandUI(){
	char query[50];
	char* cmd;
	
	while (true){
		fflush(stdin);
		// reads till new line
		printf("\n-> ");
		scanf("%[^\n]s", query);
		int i = 0;
		cmd = parse(query, &i);
		lower(cmd);
		if (strcmp(cmd, "create")==0){
			char* Tname = "";
			
			
			Tname = parse(query, &i);//(char*)malloc(sizeof(char) * 15);
		
			while (strcmp(Tname, "") == 0){
				// skips all spaces
				Tname = parse(query, &i);
			}
			create(Tname);
			
			continue;
		}
		else if (strcmp(cmd, "get")==0){
			char* tkey = parse(query, &i);
			print(tkey);
		}
		else if (strcmp(cmd, "put")==0){
			// put <tableName> <row Name> <col1Name=values>,<col2Name=values>,<col3Name=values>....
			char* Tname;

			// here in this case put <tablenNAME> <username>(unique) <col1=value>,<col2=value>,...
			Tname = parse(query, &i);//(char*)malloc(sizeof(char) * 15);

			while (strcmp(Tname, "")==0){
				// skips all spaces
				Tname = parse(query, &i);
			}
			// add while loops where ever possible.

			char* rowkey = parse(query, &i);
			//DYANMIC STRUCTURES CAN BE USED TO STORE THE RELATED VALUES HERE. CAUSE WE DONT YET KNOW THE NO. OF COLS USER WANTS TO PUT.
			int noOfCols = 0;
			//  here i am considering 20 cols as maxxxxx!! UNOPTIMAL
			char* colNames[20];
			// scan all the col,value pairs and store it in a structure.
			char** val = (char**)malloc(sizeof(char*) * 30);//assuming 30 coloumns!

			int c = 0;
			while (query[i] != '\0')
			{
				colNames[c] = parse(query, &i); 
			//	parse(query, &i);
				char* value = parse(query, &i);
				val[c] = value;
			//	parse(query, &i);
				c++;
				if (query[i - 1] == '\0')break;

			}
			struct Record r;
			/*r.vals = (char**)malloc(sizeof(char*)*c);
			for (int z = 0; z < c; z++){
				r.vals[z] = (char*)malloc(sizeof(char) * 32);
			}*/
			r.vals = val;
			r.colNames = colNames;
			r.noOfcols = c;
			r.vals = val;
			put(Tname, rowkey, r, -1); 

		}
		else if (strcmp(cmd, "exit")==0){
			break;
		}
		else if (strcmp("delete", cmd)==0){
			char* tkey = parse(query, &i);//table key
			char* rkey = parse(query, &i);
			delete_row(tkey, rkey);
		}
		else if (strcmp("printssss", cmd)==0){
			
		}
		else if (strcmp("commit", cmd) == 0){
			commit();
		}


	}
	return;

}


int main(){
	initialiseTableids();
	commandUI();
	system("pause");

}
