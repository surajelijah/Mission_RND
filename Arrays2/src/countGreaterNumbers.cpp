/*
OVERVIEW: You are given a bank statement where transactions are ordered by date. Write a function that finds the number of transactions in that statement after a given date.
-- find the count of numbers greater than a given number in a sorted array.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
date = "19-10-2004"
Output: 1 (as there is only one transaction { 30, "03-03-2005", "Third" })

INPUTS: One bank statement (array of transactions) and date.

OUTPUT: Return the number of transactions in that statement after a given date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include<stdio.h>
int isOlders(char *dob1, char *dob2);
int lens(char* a);
int monthValidates(int mon, int y);
void chartonums(char* str, int* year, int* month, int* date);

struct transaction {
	int amount;
	char date[11];
	char description[20];
};

int countGreaterNumbers(struct transaction *Arr, int len, char *date) {
	if (Arr==NULL||len<0)
	return -1;
	int Arrindex = 0, count = 0,temp=0;
	while (Arrindex < len)
	{
		temp = isOlders(date, Arr[Arrindex].date);
		if (temp == 1)//Here you need to note that we are checking for dates greater than given date which opposite to the retrun value of isOlder
			count++;
		Arrindex++;
	}
	return count;
}
int isOlders(char *dob1, char *dob2) {

	int len1 = lens(dob1);
	int len2 = lens(dob2);
	int temp = 0, year1 = 0, year2 = 0, a = 0, b = 0, i = 1;
	int month1 = 0, month2 = 0;
	int date1 = 0, date2 = 0, j = 0;

	if (len1 == 10 && len2 == 10 && (dob1[2] == '-'&&dob2[2] == '-') && (dob1[5] == '-'&&dob2[5] == '-'))
	{
		chartonums(dob1, &year1, &month1, &date1);
		chartonums(dob2, &year2, &month2, &date2);
		if (year1 == 0 || year2 == 0 || month1 > 12 || month1 == 0 || month2 > 12 || month2 == 0 || date1 > 31 || date2 > 31 || date1 == 0 || date1 == 0)
			return -1;
		j = monthValidates(month1, year1);
		if (date1 > j)
			return -1;
		j = monthValidates(month2, year2);
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
int lens(char* a)
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
int monthValidates(int mon, int y)//y is year
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
void chartonums(char* str, int* year, int* month, int* date)
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
