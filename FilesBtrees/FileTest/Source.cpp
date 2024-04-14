// try to make it dynamic.
#include"PageModules.h"

void createIndexPageStudents(){
	FILE* bfr = fopen("binarystudentsFile.txt", "rb");
	FILE* bfw = fopen("binarystudentsFile.txt", "ab");
	if (!bfr){
		printf("erroe opening file\n");
	}
	int i = 0;
	DataPageStudents *page = (DataPageStudents*)malloc(sizeof(DataPageStudents));
	fread(page, sizeof(DataPageStudents), 1, bfr);
	L1IndexPage index_page;
	index_page.pageid[0] = 0;// or ftell(bfp)
	i++;
	index_page.tableid = '0';
	index_page.unused[0] = '\0';
	index_page.pageType = '2';

	while (!feof(bfr) && i != 16){
		index_page.pageid[i] = ftell(bfr);

		fread(page, sizeof(DataPageStudents), 1, bfr);
		
		index_page.student_key[i-1] = page->data[0].id;
		i++;
	}
	tablePage.pageType = '3';
	int offset;

	tablePage.tableid = '0';
	strcpy(tablePage.table[0] , "stud");
	tablePage.unused[0] = '\0';
	fwrite(&index_page, sizeof(index_page), 1, bfw);
	offset = ftell(bfw);
	offset = tablePage.rootPageId[0] = ftell(bfw)-128;
	fclose(bfw);
	fclose(bfr);
}

void createIndexPageMarks(){
	FILE* bfr = fopen("binarystudentsFile.txt", "rb");
	FILE* bfw = fopen("binarystudentsFile.txt", "ab");
	if (!bfr){
		printf("erroe opening file\n");
	}
	int i = 0;
	DataPageMarks *page = (DataPageMarks*)malloc(sizeof(DataPageStudents));
	fseek(bfr, 16 * sizeof(DataPageStudents) + 1 * sizeof(L1IndexPage), SEEK_SET);
	L1IndexPage index_page;

	index_page.pageid[0] = ftell(bfr);// or ftell(bfp)
	fread(page, sizeof(DataPageMarks), 1, bfr);
	i++;
	index_page.unused[0] = '\0';
	index_page.pageType = '2';
	index_page.tableid = '1';

	// 8 pageids . 7 keys
	while (!feof(bfr) && i != 8){
		index_page.pageid[i] = ftell(bfr);
		fread(page, sizeof(DataPageStudents), 1, bfr);
		index_page.student_key[i - 1] = page->data[0].sid;
		i++;
	}
	tablePage.pageType = '3';
	
	tablePage.tableid = '0';
	strcpy(tablePage.table[1], "marks");
	tablePage.unused[0] = '\0';
	fwrite(&index_page, sizeof(index_page), 1, bfw);
	tablePage.rootPageId[1] = ftell(bfw)-128;

	fclose(bfw);
	fclose(bfr);	
}
void createTablePage(){
	 FILE* bfw = fopen("binarystudentsFile.txt", "ab");
	 fwrite(&tablePage, sizeof(TablePage), 1, bfw);
	 fclose(bfw);
	/* bfw = fopen("binarystudentsFile.txt", "rb");
	 fseek(bfw, 16*sizeof(DataPageStudents)+2*sizeof(L1IndexPage)+8*sizeof(DataPageMarks), SEEK_SET);
	 TablePage tp;
	 fread(&tp, sizeof(TablePage), 1, bfw);
	 L1IndexPage ip;


	 fseek(bfw, tp.rootPageId[0],SEEK_SET);
	 fread(&ip, sizeof(DataPageStudents), 1, bfw);
	 DataPageStudents ds;
	 fseek(bfw, ip.pageid[0], SEEK_SET);
	 fread(&ds, sizeof(DataPageStudents), 1, bfw);
	 fseek(bfw, tp.rootPageId[1],SEEK_SET );

	 fread(&ip, sizeof(L1IndexPage),1,bfw);
	 DataPageMarks dp;
	 fseek(bfw, ip.pageid[0], SEEK_SET);
	 fread(&dp, sizeof(DataPageMarks), 1, bfw);
	 fclose(bfw);
	 */

}
/// nullify the struct 
int main(){
	int s = sizeof(DataPageMarks);
 	s = sizeof(L1IndexPage);
	s = sizeof(DataPageMarks);
	s = sizeof(TablePage);
	createBinaryfileStudents();
	createIndexPageStudents();
	createBinaryfileMarks();
	createIndexPageMarks();
	createTablePage();
	//bfr = fopen("binaryMarksFile.txt", "rb");
	//student* w = get(4);
	////createIndexesMarks();
	//	student s=getStudent(5);

	student** stds = getStudents(5, 18);
	int l = 18 - 5 - 1;
	student** stdswithnames = contains(stds, l, "h");
	join();
	//PagePolling.
}



/*


printf("%d", sizeof(user));
FILE* fp = fopen("randomuserdata.csv" , "r");
FILE* fpb = fopen("StudentBinary.txt", "wb");

char buff[1024];
user u[3];
DataPage pages[4];
int i = 0;
int count = 1;
//	while (!feof(fp)){
while (count <= 10 && !feof(fp)){
char *id, *name;
//	fscanf(fp, "%s,%s", id, name);
fgets(buff, 1024, fp);
id = strtok(buff, ",");
pages[i].data[count].id = atoi(id);
strcpy(pages[i].data[count].name,strtok(NULL,","));
count++;
//	fscanf(fp, "%s,%s", id, name);

pages[i].data[count].id = atoi(id);
strcpy(pages[i].data[count].name, name);
count++;
fscanf(fp, "%s,%s", id, name);
pages[i].data[count].id = atoi(id);
strcpy(pages[i].data[count].name, name);
pages[i].unsused[0] = '\0';
i++;
count++;
}


//	}





*/