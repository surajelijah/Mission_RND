/*
OVERVIEW:  You are given scores for students of a class in alphabetical order. Write a function that sorts these scores in descending order.
Input is array of structures of type student (each student has name and score).
E.g.: If input is [ { "stud1", 20 }, { "stud2", 30 }, { "stud3", 40 } ] (three students with marks 20, 30 , 40).
Output for this will be [ { "stud3", 40 }, { "stud2", 30 }, { "stud1", 20 } ]

INPUTS: Array of structures of type student, length of array.

OUTPUT: Sort the array in descending order of scores.

ERROR CASES: Return NULL for invalid Inputs.

Problem Code :SD
*/

#include <stdio.h>

struct student {
	char name[10];
	int score;
};

void * scoresDescendingSort(struct student *students, int len) {
	if (students == NULL || len<0)
		return NULL;
	int i = 0, j = 0;
	if (len == 1)
		return NULL;
	else{
		struct student temp;
		for (i = 0; i < len; i++)//considering the input is small enough to use bubble sort or else merge sort is preferred
		{
			for (j = i + 1; j < len; j++)
			{
				if ((students[i].score) < (students[j].score))
				{
					temp = students[i];
					students[i] = students[j];
					students[j] = temp;
				}
			}
		}
	}
	return NULL;
}