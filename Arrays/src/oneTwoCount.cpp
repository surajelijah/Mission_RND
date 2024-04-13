/*
OVERVIEW: Given an Integer Array return the count of one's and two's in a new array of length two.
Ex: input: [1,2,2,1,2,1,2] 
	output: [3,4]
	where 3 is the count of 1's and 4 is the count of 2's

INPUTS: An Integer Array and length of the array 

OUTPUT: An Array with 1's count and 2's count

ERROR CASES: Return NULL for invalid inputs

Difficulty : Very Easy
*/

#include <stdio.h>
int* oneTwoCount(int* input, int length)
{
	if (input == NULL)
		return NULL;
	if (length <= 0)
		return NULL;
	static int count[2] = { 0 }, i = 0;//static decalration is important as without static sending local address to main is illegal. 
	int a = 0, b = 0;//a,b are count values of 1's and 2's respectively.
	for (i = 0; i < length; i++)
	{
		if (*(input + i) == 1)
			a++;
		if (*(input + i) == 2)
			b++;
	}
	count[0] = a;
	count[1] = b;
	return count;
}