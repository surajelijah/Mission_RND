/*
OVERVIEW: In a given ascending sorted array, two numbers are changed their position, please fix those two numbers.
E.g.: In [10, 40, 30, 20, 50] 20 and 40 are swapped, so final output will be [10, 20, 30, 40, 50]

INPUTS: Ascending sorted array with two positions swapped, length of the array.

OUTPUT: Update sorted array by fixing swapped numbers.

ERROR CASES: Return NULL for invalid Inputs.

Problem Code :SAP
*/

#include <stdio.h>

void * sortedArrayPositionsChange(int *Arr, int len)
{
	if (Arr == NULL || len<0)//invalid case
		return NULL;
	int temp = -1, temp1 = -1;
	int i = 0, a = 0;
	if (Arr[0]>Arr[len - 1])//base case
	{
		temp = 0;
		temp1 = len - 1;
	}
	else{
		while (i < len)//search for fisrt number
		{
			if (Arr[i]>Arr[i + 1])
			{
				temp = i;
				i++;
				break;
			}
			i++;
		}
		while (i < len)//search for second number
		{
			if (Arr[i] > Arr[i + 1])
			{
				temp1 = i + 1;
				break;
			}
			i++;
		}
	}
	if (temp != -1 && temp1 != -1)//swap the numbers
	{
		a = Arr[temp];
		Arr[temp] = Arr[temp1];
		Arr[temp1] = a;
		return NULL;
	}
}