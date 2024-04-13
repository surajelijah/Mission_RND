
/*
OVERVIEW: Given an array of integers find the maximum possible sum formed by a positive and the negative
integer in the array.
Ex: input: [1, 9, 8, 2, 3, -1,-10,-5] output: 8 (formed by 9 and -1) 

INPUTS: An Integer array and the length of the array

OUTPUT: Maximum possible sum formed by a positive and the negative integer in the array

ERROR CASES: Return 0 for the invalid inputs

NOTES:
*/

#include <stdio.h>

int maxPosNegSum(int* input,int length)
{
	if (input == NULL)
		return 0;
	if (length <= 0)
		return 0;
	int pmax = 0, nmax = 0, j = 0, k = 0;//pmax is max positve number and nmax is max negative number;
	for (int i = 0; i < length; i++)
	{
		if (j == 0){
			if (input[i] < 0)
			{
				nmax = input[i];
				j++;
			}
		}
		else
		{
			if (input[i]<0 && input[i]>nmax)
			{
				nmax = input[i];
				j++;
			}
		}
		if (input[i] > pmax)
			pmax = input[i];
		if (input[i] < 0)
			k++;
	}
	if (k == length)//All negative numbers
		return 0;
	if (k == 0)   //All positive numbers
		return 0;
	if (pmax == 0)
		pmax = 0;
	return pmax + nmax;
}