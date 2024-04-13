/*
OVERVIEW: Given a sorted array, insert a given number into the array at appropriate position.
			E.g.: Arr = [2, 4, 6], num = 5 final Arr = [2, 4, 5, 6]. 5 is inserted at 2nd index.

INPUTS: Integer	Array pointer, length of the array, number to be inserted.

OUTPUT: Array pointer after inserting number.

ERROR CASES: Return NULL for invalid inputs.

NOTES: Use memory allocation techniques to allocate memory.

ProblemCode :SAIN
*/

#include <stdio.h>
#include <malloc.h>

int * sortedArrayInsertNumber(int *Arr, int len, int num)
{
	if (Arr == NULL || len < 0)
		return NULL;
	int i = 0, key, j;
	static int *new_ar = NULL;
	new_ar = (int*)malloc(sizeof(int)*(len + 1));
	for (i = 0; i<len; i++)//adding previous elements to the new_ar array
	{
		new_ar[i] = Arr[i];
	}
	new_ar[len] = num;
	for (i = 1; i < len + 1; i++)//insertion sort
	{
		key = new_ar[i];
		j = i - 1;
		while (j >= 0 && new_ar[j] > key)
		{
			new_ar[j + 1] = new_ar[j];
			j = j - 1;
		}
		new_ar[j + 1] = key;
	}
	return new_ar;
}