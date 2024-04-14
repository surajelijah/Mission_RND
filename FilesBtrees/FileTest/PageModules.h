// pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"Pages.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<malloc.h>



char*  csv(char* q, int *i){
	char* temp;
	int j = 0;
	temp = (char*)malloc(sizeof(char) * 32);
	while (q[*i] != '\0'){
		if (q[*i] != '\n'&& q[*i] != ','){
			temp[j++] = q[*i++];
		}
	}
	temp[j] = '\0';
	*i++;
	return temp;
}

void createBinaryfileStudents(){
	// 16 DPs
	FILE* bfr = fopen("binarystudentsFile.txt", "wb");
	FILE* fp = fopen("randomuserdata.csv", "r");
	if (!fp){
		printf("\nFile Not Found\n");
	}
	
	int count = 0;
	char* str = (char*)malloc(sizeof(char) * 1024);
	// as of now only 256 records. cause 16 indexx pages(cause one level2 indexxpage) each 16 pages. 16*16=256
	
	//while (count<256){
		
		int i = 0;
		fgets(str, 1024, fp);
		while (i < 16){
			DataPageStudents dp; //= (DataPageStudents*)malloc(sizeof(DataPageStudents));
			dp.pageType = '1';
			dp.tableId = '1';
			fgets(str, 1024, fp);
			char* id = strtok(str, ",");
			char* name = strtok(NULL, ",");
			strcpy(dp.data[0].name, name);
			dp.data[0].id = atoi(id);
		
			//	dp->unsused[0] = NULL;
			
			fgets(str, 1024, fp);
			id = strtok(str, ",");
			name = strtok(NULL, ",");
			strcpy(dp.data[1].name, name);
			dp.data[1].id = atoi(id);
	
			//	dp->unsused[0] = NULL;
			
			fgets(str, 1024, fp);
			id = strtok(str, ",");
			name = strtok(NULL, ",");
			strcpy(dp.data[2].name, name);
			dp.data[2].id = atoi(id);
		
			//	dp->unsused[0] = NULL;
			
			i++;
			
			fwrite(&dp, sizeof(DataPageStudents), 1, bfr);
		
		}
		
		//count++;
	//}
	fclose(fp);
	fclose(bfr);
}
void createBinaryfileMarks(){
	FILE* fp = fopen("SudentMarksDataSet_Version_2.xls", "r");
	if (!fp){
		printf("\nFile Not Found\n");
		return;
	}
	FILE* bfr = fopen("binarystudentsFile.txt", "ab");
	if (!bfr){
		printf("\nFile Not Found\n");
		return;
	}
	int count = 0;
	char* str = (char*)malloc(sizeof(char) * 1024);
	// as of now only 256 records. cause 16 indexx pages(cause one level2 indexxpage) each 16 pages. 16*16=256
	DataPageMarks *dp = (DataPageMarks*)malloc(sizeof(DataPageMarks));
	//while (count<256){

	int i = 0;
	fgets(str, 1024, fp);
	while (i < 8){
		int count = 0;
		while (count < 6){
			fgets(str, 1024, fp);
			dp->data[count].sid = atoi(strtok(str, ","));
			dp->data[count].m1 = atoi(strtok(NULL, ","));
			dp->data[count].m2 = atoi(strtok(NULL, ","));
			dp->data[count].m3 = atoi(strtok(NULL, ","));
			dp->data[count].m4 = atoi(strtok(NULL, ","));
			dp->pageType = '1';
			dp->tableId = '2';
			dp->unused[0] = '\0';
			count++;

		}
		fwrite(dp, sizeof(DataPageStudents), 1, bfr);
		i++;
		//count++;
		//}}
	}
	fclose(fp);
	fclose(bfr);

}

void WriteIndxPage(){

}
int getSeekPos(int id,FILE* bfr){

	fseek(bfr, 16 * sizeof(DataPageStudents), SEEK_SET);
	L1IndexPage ip;
	fread(&ip, sizeof(L1IndexPage), 1, bfr);
	for (int i = 0; i < 15; i++){
		if (id>ip.student_key[i]){
			continue;
		}
		if (id <= ip.student_key[i]){
			return ip.pageid[i];
		}

	}

	if (id >= 46 && id <= 48){
		return  ip.pageid[15];
	}
}
student getStudent(int id){
	FILE* bfr=fopen("binarystudentsFile.txt","rb");
	//student s = (student*)malloc(sizeof(student));
	DataPageStudents dp;// = (DataPageStudents*)malloc(sizeof(DataPageStudents));
	int offset = getSeekPos(id,bfr);
	fseek(bfr, offset, SEEK_SET);
	fread(&dp, sizeof(DataPageStudents), 1, bfr);
	for (int j = 0; j < 3; j++){
		if (dp.data[j].id == id){
			return dp.data[j];
		}
	}

}
// we can check the pagetype dtata to know the type fo data
student** getStudents(int id1, int id2){
	student** s=(student**)malloc(sizeof(student*)*(id2-id1-1));
	FILE* bfr = fopen("binarystudentsFile.txt", "rb");
	int seek_id1 = getSeekPos(id1,bfr);
	int seek_id2 = getSeekPos(id2,bfr);
	DataPageStudents dp;
	int n = 0;
	fseek(bfr, 0, SEEK_SET);
	fseek(bfr, seek_id1, SEEK_SET);
	for (; seek_id1 <=seek_id2; seek_id1+=128){
		

		fread(&dp, sizeof(DataPageStudents), 1, bfr);
		for (int j = 0; j < 3; j++){
			if (id1 < dp.data[j].id && id2>dp.data[j].id){
				s[n] = (student*)malloc(sizeof(student));
				s[n]->id = dp.data[j].id;
				strcpy(s[n]->name, dp.data[j].name);
				n++;

			}
					}
	}
	fclose(bfr);
	return s;

}
student** contains(student** s,int noOfstuds,char key[]){
	// algorithm to find substring: // there are more thope algorithms!
	int l = strlen(key);
	student** s2 = (student**)malloc(sizeof(student*)*noOfstuds);
	for (int i = 0; i < noOfstuds; i++)s2[i] = NULL;
	int k = 0;
	for (int i = 0; i < noOfstuds; i++){
		if (strstr(s[i]->name, key)){
			s2[k] = (student*)malloc(sizeof(student));
			k++ ;
		}
	}
	return s2;
}
void join(){

	FILE* bfw = fopen("binarystudentsFile.txt", "rb");
	fseek(bfw, 16 * sizeof(DataPageStudents) + 2 * sizeof(L1IndexPage) + 8 * sizeof(DataPageMarks), SEEK_SET);
	TablePage tp;
	fread(&tp, sizeof(TablePage), 1, bfw);
	DataPageMarks dpm;
	DataPageStudents dps;
	L1IndexPage ips,ipm;
	//students index page
	fseek(bfw, tp.rootPageId[0], SEEK_SET);
	fread(&ips, sizeof(DataPageStudents), 1, bfw);
	// marks index page
	fseek(bfw, tp.rootPageId[1], SEEK_SET);
	fread(&ipm, sizeof(L1IndexPage), 1, bfw);
	int count = 0;
	int i = 0;
	int j = 0;
	printf("\nsid\t%10s\t\tM1\tM2\tM3\tM4\n","NAME");
	while (count < 48){
		// reading student DATAPAGE
		fseek(bfw, ips.pageid[i], SEEK_SET);
		i++;
		fread(&dps, sizeof(DataPageStudents), 1, bfw);
		
		// reading DATA oage of student marks
		fseek(bfw, ipm.pageid[j], SEEK_SET);
		j++;
		fread(&dpm, sizeof(DataPageMarks), 1, bfw);
		int f = 0;
		for (int g = 0; g < 3; g++,f++){
			printf("%d\t%10s\t\t%d\t%d\t%d\t%d\n", dps.data[g].id, dps.data[g].name, dpm.data[f].m1, dpm.data[f].m2, dpm.data[f].m3, dpm.data[f].m4);
			count++;
		
		}
		// reading student DATAPAGE
		fseek(bfw, ips.pageid[i], SEEK_SET);
		i++;
		fread(&dps, sizeof(DataPageStudents), 1, bfw);
		for (int g = 0,f=3; g < 3; g++, f++){
			printf("%d\t%10s\t\t%d\t%d\t%d\t%d\n", dps.data[g].id, dps.data[g].name, dpm.data[f].m1, dpm.data[f].m2, dpm.data[f].m3, dpm.data[f].m4);
			count++;
		}
	}

	}
// in range query by comparing pageids we re reducing the comparosions from sid to pageid and reducing the comaprisions three folds