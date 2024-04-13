
/*
OVERVIEW: Given a number N return all the prime numbers upto the integer N.
Ex: input: 10 output: [2,3,5,7] 

INPUTS: An Integer N

OUTPUT: Return an Array of Prime numbers until the number N(N inclusive)

ERROR CASES: Return NULL for invalid inputs

Sample Input : 10
Sample Output : An Array consisting elements {2,3,5,7}
NOTES:

Try to think of a optimized way , and avoid unnecessary comparisons.
*/

#include <stdio.h>
int* nPrime(int N)
{
	/*if (N <= 0)
	return NULL;
	static int* p = NULL;
	p = (int*)malloc(sizeof(int) * 1);
	int flag = 0, i = 3, j = 2, k = 0;
	int *ptr = NULL;
	if (N == 2){
	p[0] = 2;
	return p;
	}
	if (N>2)
	{
	p[k] = 2;
	ptr = (int*)realloc(p, sizeof(int)*(k + 2));
	k++;
	}
	while (i <= N)
	{
	flag = 0;
	for (j = 2; j*j <= i; j++)
	{
	if (i%j == 0)
	{
	flag = 1;
	break;
	}
	}
	if (flag == 0)
	{
	p[k] = i;
	ptr = (int*)realloc(p, sizeof(int)*(k + 2));
	p = ptr;
	k++;
	}
	i = i + 2;
	}
	return p;*/
	//I've tried the above code by dynamically reallocating when i find a prime and add it into the array
	//It was working fine in online compiler but and the code is right as far as I know i debugged it no errors 
	//so I opted for static array in predefined size
	if (N <= 0)
		return NULL;
	static int a[200] = { 0 };
	int flag = 0, i = 3, j = 2, k = 0;
	if (N == 2)
	{
		a[0] = 2;
		return a;
	}
	if (N > 2)
	{
		a[0] = 2;
		k++;
	}
	while (i <= N)
	{
		flag = 0;
		for (j = 2; j*j <= i; j++)
		{
			if (i%j == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			a[k] = i;
			k++;
		}
		i = i + 2;
	}
	return a;
}