/*
OVERVIEW: Given an array where every element occurs three times, except one element which occurs only
once. Find the element that occurs once.
E.g.: Input: arr = 12, 1, 12, 3, 12, 1, 1, 2, 3, 3
ouput: 2

INPUTS: Integer array and length of the array.

OUTPUT: Element that occurs only once.

ERROR CASES: Return -1 for invalid inputs.

NOTES:
There are better ways of solving the problem than a brute-force solution which is of O(n^2)
complexity .
*/

#include<stdio.h>
#include <stdlib.h>

int findSingleOccurenceNumber(int *A, int len) {

		if (A == NULL || len<0)//Error case
			return -1;
		if (len == 1)//Only one element
			return A[0];
		if (len % 3 == 0)//No single element
			return -1;
		int singleoccelement = 0, index = 0;
		int i = 0 ,j = 0,temp=0;
		bool flag=0;
		for (i = 1; i < len && A[i-1] <= A[i]; i++);
			if (i == len)
				flag = 1;//already sorted
		//sorting the elements
		if (flag ==0)
		{
			i = 0;
			for (i = 0; i < len; i++)
			{
				for (j = i + 1; j < len; j++)
				{
					if (A[i] <= A[j])
					{
						temp = A[i];
						A[i] = A[j];
						A[j] = temp;
					}
				}
			}
		}
		//after sorting traversing and finding where a single element occurs
		while (index < len)
		{
			if (index == len - 1)
			{
				singleoccelement = A[index];
			}
			if (A[index] != A[index + 1])//index starts from 1
			{
				singleoccelement = A[index];
				break;
			}
			else
			{
				index = index + 3;//every number which repeats has a frequency 3
			}
		}
		return singleoccelement;
	}