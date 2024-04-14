// this is my filesystem where the page size is 128 bytes .
typedef struct{
	int id;
	//int d;
	char name[32];


}student;
//size = 36



typedef struct{
	int sid;
	int m1, m2, m3, m4;
	
}marks;
//pagesize=128 , marks size = 20

// while file is being read ffirst two bytes gets stored in the pageType and tale id. 
typedef struct {
	

	student data[3];
	char pageType;
	char tableId;
	// 20 bytes remaining.
	char unsused[18];
}DataPageStudents;
// when the alignment changes in the structure the size it occupies also changes.
typedef struct{

	// 8 bytes remaining.
	
	marks data[6];
	char pageType;
	char tableId;
	char unused[6];
}DataPageMarks;

typedef struct{
	
	int pageid[16];// page id is the page no. where we can find the student with the key ie student id 
	int student_key[15];//  key is the student id
	// this is level one B+ tree.
	
	char pageType;
	char tableid;
	char unused[2];
}L1IndexPage;

typedef struct{
	int indexPageId[16];// index id the id of the index page where we can find the pageid to search for the student id which is the key
	int student_key[15];
	//  this is for level 2
}L2IndexPage;
typedef struct{
	int rootPageId[11];
	char pageType;
	char tableid;
	
	char table[10][8];
	char unused[2];
}TablePage;

TablePage tablePage;
/******************
 T1= 16DP+1IP=17   *
 T2=  8DP+1IP=9    *   
 TablePage   =1    *
 _________________
              27  | 
 _________________|
                   *
				   *
*******************/