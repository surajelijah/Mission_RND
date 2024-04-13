
/*
OVERVIEW:  Write a function that takes ascending sorted student's score array and tells how many number of students got more marks and how many students got less marks than the given student.
E.g.: Input array: [10, 20, 30, 40, 50], score: 30, lessCount value is 2 (10, 20 are less than 30), moreCount value is 2 (40, 50 are greater than 30).

INPUTS: Ascending sorted student marks array, length of the array, one student score, lessCount and moreCount are to be
used to store final results.

OUTPUT: Update lessCount and moreCount with number of students less than and more than given score.

ERROR CASES: Return NULL for invalid inputs.

NOTES:

Problem Code :SC
*/

#include <stdio.h>

void * studentsCount(int *Arr, int len, int score, int *lessCount, int *moreCount) {
	if (Arr == NULL || len <= 0 || score<0)
		return NULL;
	*lessCount = 0;
	*moreCount = 0;
	if (len == 1)
	{
		if (score == Arr[0])
		{
			*lessCount = 0;
			*moreCount = 0;
		}
		else
		{
			if (score > Arr[0])
			{
				*lessCount = 1;
				*moreCount = 0;
			}
			else
			{
				*lessCount = 0;
				*moreCount = 1;
			}
		}
		return NULL;
	}
	if (Arr[0] == Arr[len - 1])
	{
		if (score == Arr[0])
		{

			*lessCount = 0;
			*moreCount = 0;
		}
		else
		{
			if (score > Arr[0])
			{
				*lessCount = len;
				*moreCount = 0;
			}
			else
			{
				*lessCount = 0;
				*moreCount = len;
			}
		}
		return NULL;
	}
	int i = 0;
	for (i = 0; i < len; i++)
	{
		if (Arr[i]>score)
			(*moreCount) = (*moreCount) + 1;
		else
		{
			if (Arr[i]<score)
				(*lessCount) = (*lessCount) + 1;
		}
	}
	return NULL;
}
