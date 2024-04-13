/*
Given an array which has two arithmetic sequences and
one geometric sequence (in any order).
Copy indexes where each sequence starts and ends into an Array and return it.

Note : Each sequence will be of atleast LENGTH 3,and The sequences can be overlapping

Ex : 1, 3, 5, 7, 2, 4, 8, 16 18 20, output is [0, 3, 7, 9, 4, 7]
Ex : 1 ,2, 4, 8, 12, 16, 21, 26     output is [2, 5, 5, 7, 0, 3]
Ex : 10 15 20 30 50 70 100 200 400 800  output is [0, 2, 3, 5, 6, 9]

The final_arr[0], final_arr[1] values in final array
will be start and end indexes of First A.P in the Original Array

The final_arr[2], final_arr[3] values in final array
will be start and end indexes of Second A.P

The final_arr[4], final_arr[5] values in final array
will be start and end indexes of First  G.P (Only)

Input: Array and Length of Array
Output : New Array which has 6 integers , which denote the (start,end) indexes .

Note : All elements in the array will be part of atleast 1 sequence .
Two A.P cannot start at same index .

Difficulty : Medium
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int check_AP_or_GP(int ,int,int,int,int*);

int * find_sequences(int *arr, int len){
	
	if (arr==NULL||len<2)//To decide whther a sequence is A.P or G.P we require minimum of three elements 
	return NULL;
	int index = 0, flag = 0;//flag differentiates between the A.P and G.P function call
	int diff = 0,ratio=1,i=0,count=0,s=0;
	static int Ansarr[6];
	while (index < len-1)
	{
		flag = 0;
		if ((arr[index + 1] - arr[index]) == (arr[index + 2] - arr[index + 1]) && s<2 && (diff != (arr[index + 1] - arr[index])))
		{
    //s is to make it limit to 2 A.P's and next conditon is to ensure that the newly formed A.P is different with different difference
			flag = 1;
			diff = arr[index + 1] - arr[index];
			Ansarr[count] = index;
			//index = index + 2;
			i = check_AP_or_GP(index+2, diff, flag,len,arr);//i is the index up until which the sequnece continues
			Ansarr[count+1] = i;
			count = count + 2;
			//index = i;
			index = index + 1;
			s++;
		}
		else
		{
			if ((arr[index + 1] * arr[index + 1]) == (arr[index + 2] * arr[index]))
			{
				flag = 2;
				ratio = (arr[index + 1] * arr[index + 1]);
				if (ratio == 0)
				{
					index = index + 1;
				}
				else
				{
					Ansarr[4] = index;
					//index = index + 2;
					i = check_AP_or_GP(index+2, ratio, flag,len,arr);
					Ansarr[5] = i;
					//index = i;
					index = index + 1;
				}
			}
		}
		if (flag == 0)
			index = index + 1;
	}
	return Ansarr;
}
int check_AP_or_GP(int pos, int seqgen, int marker,int length,int* a)//pos is the index,seqgen is the sequence generator factor like diff or ratio,marker is to A.P or G.P
{
	if (pos > length || pos == length - 1)
		return length - 1;
	int i = 0,temp=0;
	if (marker == 1)
	{
		while (1)
		{
			temp = seqgen;
			if (a[pos + 1] == a[pos] + temp)
				pos = pos + 1;
			else
				break;
		}
		return pos;
	}
	if (marker == 2)
	{
		while (1)
		{
			temp = seqgen;
			if (a[pos + 1] == a[pos] * temp)
				pos = pos + 1;
			else
				break;
		}
		return pos;
	}
}