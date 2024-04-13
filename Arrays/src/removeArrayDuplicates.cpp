/*
OVERVIEW:  given an array that has duplicate values remove all duplicate values.
E.g.: input: [1, 1, 2, 2, 3, 3], output [1, 2, 3]

Ex 2: [4,4,2,2,1,5] output : [4,2,1,5]

INPUTS: Integer array and length of the array .

OUTPUT: Update input array by removing duplicate values and return the final array length

ERROR CASES: Return -1 for invalid inputs.

NOTES: Don't create new array, try to change the input array.
*/

#include <stdio.h>

int removeArrayDuplicates(int *Arr, int len)
{
	
	if (Arr == NULL)
		return -1;
	if (len <= 0)
		return -1;
	int i = 0, j = 0, temp = 0;
	for (i = 0; i < len; i++)//considering the input is small enough to use bubble sort or else merge sort is preferred
	{
		for (j = i + 1; j < len; j++)
		{
			if (Arr[i]>Arr[j])
			{
				temp = Arr[i];
				Arr[i] = Arr[j];
				Arr[j] = temp;
			}
		}
	}
	i = 0;
	j = 0;
	while (i < len)
	{
		if (Arr[j] != Arr[i])
		{
			Arr[++j] = Arr[i];
			i++;
		}
		else
		{
			i++;
		}
	}
	return j + 1;
}