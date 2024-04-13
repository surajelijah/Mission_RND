/*
OVERVIEW: You are given 2 bank statements that are ordered by date - 
Write a function that produces a single merged statement ordered by dates.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[2] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" } };
Output: { { 10, "09-10-2003", "First" }, { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" },  30, "03-03-2005", "Third" }, { 220, "18-01-2010", "Sixth" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Combined statement ordered by transaction date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <stdio.h>
#include <stdlib.h>

int isOlder(char *dob1, char *dob2);
int len(char* a);
int monthValidate(int mon, int y);
void chartonum(char* str, int* year, int* month, int* date);

struct transaction {
	int amount;
	char date[11];
	char description[20];
};



struct transaction * mergeSortedArrays(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	if (A == NULL || B == NULL || ALen<0 || BLen<0)
		return NULL;
	if (A != NULL && B == NULL)
		return A;
	if (B != NULL && A == NULL)
		return B;
	//Here I use two pointers/indexes just like in the merge procedure of merge sort and also I;ll make use
	//of the isOlder function from cBasics Lesson  
	int Aindex = 0, Bindex = 0, temp = 0, i = 0;
    static transaction Merged_Array[6];
	//static transaction* Merged_Array = (transaction*)malloc(sizeof(transaction) * 6);even this declaration also works.
	while (Aindex < ALen&&Bindex < BLen)
	{
		temp = isOlder(A[Aindex].date, B[Bindex].date);
		if (temp == 2)//date1 is greater than date 2
		{
			Merged_Array[i++] = B[Bindex];
			Bindex++;
		}
		if (temp == 1)//date 1 is smaller than date 2
		{
			Merged_Array[i++] = A[Aindex];
			Aindex++;
		}
		if (temp == 0)//date1 is equal to date2
		{
			Merged_Array[i++] = A[Aindex];
			Merged_Array[i++] = B[Bindex];
			Aindex++;
			Bindex++;
		}
	}
	while (Aindex < ALen)//copying the rest from A if present
	{
		Merged_Array[i++] = A[Aindex++];
	}
	while (Bindex<BLen)//copying the rest from B if present
	{
		Merged_Array[i++] = B[Bindex++];
	}

	return Merged_Array;
}
int isOlder(char *dob1, char *dob2) {

	int len1 = len(dob1);
	int len2 = len(dob2);
	int temp = 0, year1 = 0, year2 = 0, a = 0, b = 0, i = 1;
	int month1 = 0, month2 = 0;
	int date1 = 0, date2 = 0, j = 0;

	if (len1 == 10 && len2 == 10 && (dob1[2] == '-'&&dob2[2] == '-') && (dob1[5] == '-'&&dob2[5] == '-'))
	{
		chartonum(dob1, &year1, &month1, &date1);
		chartonum(dob2, &year2, &month2, &date2);
		if (year1 == 0 || year2 == 0 || month1 > 12 || month1 == 0 || month2 > 12 || month2 == 0 || date1 > 31 || date2 > 31 || date1 == 0 || date1 == 0)
			return -1;
		j = monthValidate(month1, year1);
		if (date1 > j)
			return -1;
		j = monthValidate(month2, year2);
		if (date2 > j)
			return -1;
		if (year1 > year2)
			return 2;
		else
		{
			if (year1 < year2)
				return 1;
		}
		if (year1 == year2)
		{
			if (month1 > month2)
				return 2;
			else
			{
				if (month1 < month2)
					return 1;
			}
			if (month1 == month2)
			{
				if (date1 > date2)
					return 2;
				else
				{
					if (date1 < date2)
						return 1;
				}
				if (date1 == date2)
					return 0;
			}
		}
	}
	else
		return -1;
}
int len(char* a)
{
	int i = 0;
	while (a[i] != '\0')
	{
		if (a[i] == 45)
			i++;
		else
		{
			if (a[i] >= 48 && a[i] <= 57)
				i++;
			else
				break;
		}
	}
	return i;
}
int monthValidate(int mon, int y)//y is year
{
	bool b = 0;
	if (y % 4 == 0)
		b = 1;
	else
		b = 0;
	switch (mon)
	{
	case 1:return 31;
	case 2:if (b == 1)
		return 29;
		   else
			   return 28;
	case 3:return 31;
	case 4:return 30;
	case 5:return 31;
	case 6:return 30;
	case 7:return 31;
	case 8:return 31;
	case 9:return 30;
	case 10:return 31;
	case 11:return 30;
	case 12:return 31;
	}
}
void chartonum(char* str, int* year, int* month, int* date)
{
	int temp = 0, a = 0, b = 0, i = 1;
	while (temp<4)//year to number
	{
		a = str[9 - temp] - '0';
		*year = *year + a*i;
		i = i * 10;
		temp++;
	}
	a = str[3] - '0';//month to number
	b = str[4] - '0';
	*month = a * 10 + b;
	a = str[0] - '0';//date to number
	b = str[1] - '0';
	*date = a * 10 + b;
	return;
}
