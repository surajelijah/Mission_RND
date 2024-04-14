
#pragma once
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<string>

#include"DataStore.h"

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


void commit(){

} 
void saveinFile(){

}
Table* initialiseTable(){
// modified ya done
	Table* table;
	table = (Table*)malloc(sizeof(Table));
	table->no_of_rows = 0;
	table->row = (cell**)malloc(sizeof(cell*)*100);
	table->row[0] = NULL;
	table->curent_commit = (int*)malloc(sizeof(int)*100);
	table->curent_commit[0] = 1;
	table->ids = (struct id*)malloc(sizeof(struct id) * 100);
	table->ids[table->no_of_rows].index = -1;
	table->ids[table->no_of_rows].key = "";
	return table;
}
int findid(Table* table,char* key){
	for (int i = 0; i < table->no_of_rows; i++){
		if (str_cmp(key, table->ids[i].key)){
			return table->ids[i].index;
		}
	}
	return -1;
}
void addRow(Table* table,char* key,int no_of_cols,char** nameOfCols,char** value){
	//                                                                    ^ 
	//                                                                    |  
	// as of now all the coloumns stores only interger values..............

	cell* newcell = (cell*)malloc(sizeof(cell));

	table->no_of_rows++;
	/*realloc(table->row,sizeof(cell*)*table->no_of_rows);
	realloc(table->curent_commit, sizeof(int)*table->no_of_rows);
	realloc(table->ids, sizeof(struct id)*table->no_of_rows);*/
    // do malloc for key
	
	table->ids[table->no_of_rows - 1].key = key;
	table->ids[table->no_of_rows - 1].index = table->no_of_rows - 1;



	table->curent_commit[table->no_of_rows - 1] = 1;



	char* col=(char*)malloc(sizeof(char) * 150);	
	str_cpy(nameOfCols[0], col);
	
	table->row[table->no_of_rows - 1] = newcell;
	table->row[table->no_of_rows - 1]->col_name = col;
	table->row[table->no_of_rows - 1]->val = (char*)malloc(sizeof(char) * 32);
	table->row[table->no_of_rows - 1]->val = value[0];
	table->row[table->no_of_rows - 1]->version = 1;
	table->row[table->no_of_rows - 1]->prev_version = NULL;
	struct cell* temp = table->row[table->no_of_rows - 1];
	temp->next_col = NULL;

	cell* nextcell;
	for (int j = 1; j < no_of_cols; j++){
		nextcell = (struct cell*)malloc(sizeof(struct cell));
		temp->next_col = nextcell;
		nextcell->next_col = NULL;
		nextcell->prev_version = NULL;
		nextcell->val = (char*)malloc(sizeof(char) * 32);
		nextcell->val = value[j];
		nextcell->version = 1;
		char* col = (char*)malloc(sizeof(char) * 15);
		str_cpy(nameOfCols[j], col);
		nextcell->col_name = col;
		temp = nextcell;
	}
}
cell* currentCell(Table* table, cell* c, int i){
	while (c != NULL){
		if (table->curent_commit[i] <= c->version){
			return c;
		}
		else{
			c = c->prev_version;
		}
	}
	return NULL;
}
int copyCell(cell* c1, cell* c2,int  i){
	//c2=currentCell(c2,i);
	if (c2 == NULL){
		return false;
	}
	c1->col_name = c2->col_name;
	c1->next_col = NULL;
	c1->prev_version = NULL;
	c1->val = c2->val;
	c1->version = c2->version;
	
	return true;
}
// do error handling when no of rows gets more than max no of rows
struct cell* get(Table* table,char* key){

	int indx=0;// = findid(key);
	struct cell* cellsHead = table->row[indx];
	struct cell* temp=NULL;
	struct cell* head =NULL;
	while (cellsHead != NULL){
		struct cell* nextcell = (struct cell*)malloc(sizeof(struct cell));
		if (head == NULL){
			head = nextcell;
		}
		bool b=copyCell(nextcell, cellsHead,indx);
		if (b == false){
			return NULL;
			// returns NULL if current cell not found with apt version.
		}
		if (temp != NULL){
			temp->next_col = nextcell;
		}
		temp = nextcell;
	
		cellsHead = cellsHead->next_col;
	}
	return head;
}
void update(Table* table,char* key,struct Record R){
	int indx = findid(table,key);
	int i = 0;
	cell* current = table->row[indx];
	cell** newcells = (cell**)malloc(sizeof(cell*)*R.noOfcols);
	for (int k = 0; k < R.noOfcols; k++){
		newcells[k] = (cell*)malloc(sizeof(cell));
	}
	cell* prev = current;
	// check version types and all...here! as of now just upate the val n increment version and insert cell
	if (str_cmp(R.colNames[0], current->col_name)){
		newcells[0]->next_col = current->next_col;
		newcells[0]->prev_version = prev;
		newcells[0]->col_name = current->col_name;
		newcells[i]->val = (char*)malloc(sizeof(char) * 32);
		newcells[0]->val = R.vals[0];
		newcells[0]->version = current->version + 1;
		table->row[indx] = newcells[0];
		prev = newcells[0];
		current = current->next_col;
		i = 1;
	}
	
	// if R.colNames[0]==current->col_name ,table->row[indx]=newcells[0]......

	while (current != NULL && i<R.noOfcols){

		if (str_cmp(R.colNames[i],current->col_name)){
			//struct cell* newcell = (cell*)malloc(sizeof(cell));
			newcells[i]->col_name = current->col_name;
			newcells[i]->next_col = current->next_col;
			newcells[i]->prev_version = current;
			newcells[i]->version = current->version + 1;
			prev->next_col = newcells[i];
			newcells[i]->val = (char*)malloc(sizeof(char) * 32);
			newcells[i]->val = R.vals[i];
			prev = newcells[i];
			current = current->next_col;
			/*if (i<R.noOfcols)
			newcells[i]->next_col = newcells[i + 1];
			if (i == R.noOfcols - 1){
				newcells[i]->next_col = NULL;
			}
			i++;
	*/	
			i++;
		}
		else{
			prev = current;
			current = current->next_col;
							
		}

		if (i >= R.noOfcols){
			break;
		}
			}
	if (i < R.noOfcols){
		for (int j = i; j < R.noOfcols; j++){
			prev->next_col = newcells[j];
			newcells[j]->col_name = R.colNames[j];
			newcells[j]->version = 1;
			newcells[j]->next_col = NULL;
			
			newcells[j]->prev_version = NULL;
			newcells[j]->val = (char*)malloc(sizeof(char) * 32);
			newcells[j]->val = R.vals[j];
			prev = newcells[j];

		}
	}
	table->curent_commit[indx]++;
//	table->row[indx] = newcells[0];
}
int findTableId(char* key){
	for (int i = 0; i < no_of_tables; i++){
		if (strcmp(tabIds[i].key, key)==0){
			return tabIds[i].index;
		}
	}
	return -1;
}
void put(char* tabNamme,char* key, struct Record R,int version){
	// check for conditions where the find key returns -1,
	int k = findTableId(tabNamme);
	if (k == -1){
		printf("entered table doesnot exist");
		return;
	}
	int k2 = findid(tables[k],key);
	if (k2 == -1){

		addRow(tables[k],key, R.noOfcols, R.colNames, R.vals);
					
	}
	else if(version<=0){
		//  update the update function
		update(tables[k],key, R);
	}
	else{
		if (version == tables[k]->curent_commit[k]){
			update(tables[k],key, R);
		}
		else{
			printf("CONFLICT");
		}
	}
}
void delete_row(char* Tname,char* key){
	
	int k = findTableId(Tname);
	int indx = findid(tables[k],key);
	tables[k]->row[indx] = NULL;
	tables[k]->curent_commit[indx] = 1;
	tables[k]->ids->index = -1;
	tabIds[k].index = -1;
	tabIds[k].key = "";
	// free memory!!!
}

// creates table with table name as key
int create(char* tabName){
	int b = findTableId(tabName);
	if (b >= 0){
		printf("\nTable already exists\n");
		return -1;
	}
	
	// we have to use malloc once before using realloc.
	tabIds[no_of_tables].index = no_of_tables;
	char* Tname = (char*)malloc(sizeof(char) * 32);
	str_cpy(tabName, Tname);
	tabIds[no_of_tables].key = Tname;
	
	tables[no_of_tables] = initialiseTable();
	no_of_tables++;
	return 1;

}
void 	initialiseTableids(){
	//assuming 15 tables as of now.
	//25 tables assumption.
	tables = (Table**)malloc(sizeof(Table*)*25);
	tabIds = (tableId*)malloc(sizeof(tableId)*15);
}
void print(char* tname){
	int b = findTableId(tname);
	if (b < 0){
		printf("\nTable doesnot exists\n");
		return;
	}
	for (int i = 0; i < tables[b]->no_of_rows; i++){
		cell* temp = tables[b]->row[i];
		// NEED TO OPTIMISE TO PRINT THE CURRENT VEERSION
		// AS OF NOE THIS JUSTS PRINTS THE ENTIRE UPDATED/LATEST RECORD
		cell* temp2 = temp;
		printf("\n");
		while (temp){
			printf("%s\t", temp->col_name);
			temp = temp->next_col;
			
		}
		printf("\n");
		while (temp2){
			printf("%s\t", temp2->val);
			temp2 = temp2->next_col;
		}
	}
}
FILE* createFile(char* colName, char* Tname){
	// open file .

	// write file ame in first line and col name in second line. open in append mode.
	return NULL;

}
void initialiseBackupFiles(Table* table,char* tname){
	files = (struct Files*)malloc(sizeof(Files));
	files->no_of_files = 0;
	files->FileNames = (char**)malloc(sizeof(char*)*max_files);
	files->file_ptrs = (FILE**)malloc(sizeof(FILE*)*max_files);

	cell* temp = table->row[0];
	int i = 0;
		while (temp){
		/*	files->FileNames[i] = (char*)malloc(sizeof(char) * 20);
			strcpy(files->FileNames[i],temp->col_name)
		*/
			files->FileNames[i] = temp->col_name;
			files->file_ptrs[i] = (FILE*)malloc(sizeof(FILE));
			files->file_ptrs[i] = createFile(temp->col_name,tname);
			files->no_of_files++;
			i++;
			temp = temp->next_col;

		}

}
FILE* getFilePointer(char* colName){
	for (int i = 0; i < files->no_of_files; i++){
		if (strcmp(colName, files->FileNames[i]) == 0){
			return files->file_ptrs[i];
		}
	}
	return NULL;
}

void saveRow(char* key, cell* row,char* Tname){
	
	
	FILE* fptr = NULL;
	while (row){

		fptr = getFilePointer(row->col_name);
		//write 3 coma separated values into the file(key,val,ver).
		// refer down for saving pattern.

		
	}
}
void save(Table* table,char* Tname){
	for (int i = 0; i < table->no_of_rows; i++){
		// save each row.
		// key is enough
		saveRow(table->ids[i].key, table->row[i],Tname);
	}
	//	for (int i=0)
}
void commit(char* tName){
	int id = findTableId(tName);
	if (id < 0){
		printf("\ntable doesnot exist!\n");
	}
	initialiseBackupFiles(tables[id], tName);

}
void follow(char* tabName, char* Ukey, char* followKey){
	int id = findTableId(tabName);
	Table* T = tables[id];
	int uid = findid(T, Ukey);
	cell* temp = T->row[uid];
	while (temp->next_col){
		if (strcmp(temp->col_name, "followers") == 0){

			cell* f = (cell*)malloc(sizeof(cell));
			f->col_name = "followers";
			f->next_col = NULL;
			f->prev_version = temp;
			f->val = (char*)malloc(sizeof(char) * 300);
			f->version = temp->version++;
			f->val = followKey;//change heere
			return;
		}
		temp = temp->next_col;
	}
	cell* f = (cell*)malloc(sizeof(cell));
	f->col_name = "followers";
	f->next_col = NULL;
	f->prev_version = NULL;
	f->val = (char*)malloc(sizeof(char) * 300);
	f->version = 1;
	f->val = followKey;

	
}
// to reconstruct entire database.
// there will be two types files tables.txt( tale name and col names in pairs) and the ragardingg cols in the tabName+colname.txt files 
// in tabname+colname.txt files.....
//create <tableName>
//  put <tableName> <row Name> <col1Name=values>,<col2Name=values>,<col3Name=values>....
//get <tableName>
// first line of file is table name
// second line is the coloumn name
//From third line ... coma separated or space separated  values of
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 1)key (for row)                                                     >    
//2)value (col value for in tht row                                    >
//3)version (of that cell)                                             >
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>