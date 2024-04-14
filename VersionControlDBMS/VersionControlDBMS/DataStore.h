struct cell{
	char* col_name;
	char* val;
	int version;
	cell* prev_version;
	cell* next_col;
};

struct Record{
	int noOfcols;
	char** colNames;
	char** vals;
};
// what is cell** row?

typedef struct{
	int no_of_rows;
	cell** row;
//	char** rowid;
	int * curent_commit;
	//	int no_of_cols;
//	char** name_of_cols;
	struct id* ids;
}Table;

struct id{
	//to store rowname to row index
	char* key;
	// need to use no_of_cols to optimise the update of records function.
	//int no_of_cols;
	int index;

}; 
struct tableId{
	// to store table name to index
	char* key;
	int index;

};




int current_version;
Table** tables;
int no_of_tables = 0;

struct tableId* tabIds;
struct Files{
	FILE** file_ptrs;
	char** FileNames;
	int no_of_files;
};
int max_files = 20;
struct Files* files;
// conisdering max of 20 files