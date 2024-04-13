/*
OVERVIEW: You are given 2 bank statements that are ordered by date. 
Write a function that returns dates common to both statements
(ie both statements have transactions in these dates).
E.g.: Input: 
A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[3] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" }, { 320, "27-08-2015", "Seventh" } };
Output: { { 10, "09-10-2003", "First" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Transactions having same dates.


ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <stdio.h>
int isOldert(char *dob1, char *dob2);
int lent(char* a);
int monthValidatet(int mon, int y);
void chartonumt(char* str, int* year, int* month, int* date);

struct transaction {
	int amount;
	char date[11];
	char description[20];
};

struct transaction * sortedArraysCommonElements(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	if (A == NULL || B == NULL || ALen<0 || BLen<0)
		return NULL;
	if (A != NULL && B == NULL)
		return NULL;
	if (B != NULL && A == NULL)
		return NULL;
	int Aindex = 0, Bindex = 0, temp = 0, i = 0;
	static transaction Merged_Array[6];
	while (Aindex < ALen && Bindex < BLen)
	{
		temp = isOldert(A[Aindex].date, B[Bindex].date);
		if (temp == 0)//date1 is equal to date2
		{
			Merged_Array[i++] = A[Aindex];
			Aindex++;
			Bindex++;
		}
		if (temp == 1)
			Bindex++;
		if (temp == 2)
			Aindex++;
	}
	if (i == 0)
		return NULL;
	return Merged_Array;
}
int isOldert(char *dob1, char *dob2) {

	int len1 = lent(dob1);
	int len2 = lent(dob2);
	int temp = 0, year1 = 0, year2 = 0, a = 0, b = 0, i = 1;
	int month1 = 0, month2 = 0;
	int date1 = 0, date2 = 0, j = 0;

	if (len1 == 10 && len2 == 10 && (dob1[2] == '-'&&dob2[2] == '-') && (dob1[5] == '-'&&dob2[5] == '-'))
	{
		chartonumt(dob1, &year1, &month1, &date1);
		chartonumt(dob2, &year2, &month2, &date2);
		if (year1 == 0 || year2 == 0 || month1 > 12 || month1 == 0 || month2 > 12 || month2 == 0 || date1 > 31 || date2 > 31 || date1 == 0 || date1 == 0)
			return -1;
		j = monthValidatet(month1, year1);
		if (date1 > j)
			return -1;
		j = monthValidatet(month2, year2);
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
int lent(char* a)
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
int monthValidatet(int mon, int y)//y is year
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
void chartonumt(char* str, int* year, int* month, int* date)
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
