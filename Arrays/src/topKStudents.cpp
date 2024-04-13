/*
OVERVIEW:  You are given scores for students of a class in alphabetical order. Write a function that returns the names and scores of top K students.
Input is array of structures of type student (each student has name and score).
E.g.: If input is [ { "stud1", 20 }, { "stud2", 30 }, { "stud3", 40 } ] (three students with marks 20, 30 , 40) and K value is 2.
return top 2 students [ { "stud2", 30 }, { "stud3", 40 } ]

INPUTS: array of structures of type student, length of the array, integer K.

OUTPUT: Return top K students from array. Output need not be in decreasing order of scores.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
Problem Code :TK
*/

#include <iostream>
#include <malloc.h>

struct student {
	char *name;
	int score;
};

struct student ** topKStudents(struct student *students, int len, int K) {
	if (students == NULL || len <= 0 || K <= 0)
		return NULL;
	struct student** top_ptr = NULL;
	//struct student* temp = NULL;
	top_ptr = (struct student**)malloc(sizeof(struct student*));
	int count = 0, i = 0, j = 0, p = 0;//count is for knowing the number of students greater than the number are present in the array.
	if (K >= len)
	{
		for (i = 0; i < len; i++)
			top_ptr[i] = &students[i];
		return top_ptr;
	}
	i = 0;
	//temp= (struct student*)malloc(sizeof(struct student)*len);
	for (i = 0; i < len; i++)
	{
		count = 0;
		for (j = 0; j < len; j++)
		{

			if (students[i].score < students[j].score)
			{
				count++;
			}
			if (count > K)
				break;
		}
		if (count < K)
		{
			top_ptr[p++] = &students[i];
		}
	}
	return top_ptr;
}