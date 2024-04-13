/*
Problem Code :PHEIGHTS

You are given an Array of Integers and length .The numbers in the array denotes the heights of the people .
Imagine people are standing one behind another and A[0] will be the last guy .

Ex: In the array of A:[1,8,3,4,2] . 2 is the first guy , 4 is behind him , 3 is behind 4 etc and so on . ie A[0] is behind a[1],a[2],a[3],a[4].
A[0] can see all people from A[1:Len-1]
A[1] can see all people from A[2:Len-1] etc

(You can view the set of people , as standing from Left to Right also if that makes it convinient)

There are now a set of Rules :
->Each person can also see the person who is ahead of him . (In the array you can treat it like he can see only the people who are on the right side ) .
->If a person height is X , he can only see the persons whose height are greater or equal than him (>=X). [Unless any person whose height is greater but is blocked by some other person
whose height is even more ]

Ex: Let Array be [2,5,7,6,8,4,5]
2 can see only 5,7,8 . [He cant see 6 because 7 blocks it]
5 can see 7,8 [Again he cant see 6, as 7 blocks it]
7 can see only 8
6 can see only 8
8 can see no one
4 can see 5 and 5 can see no one .

**You need to return an Array which is made up of the **index** of the person who can be viewed by max number of people and also how many people can see him.**
Like in the above example , you need to return the index of 8 ie 4 . As 8 can be watched by 3 people .where as every other element can be watched by fewer than 3 people .

If there are multiple people who can be viewed by same number of people , Return the Array whose index of the person is less .

Ex2 : Input :4,3,8,6,5,1,7,2  Output : Returns [6,3] [6 is the Index of 7 and 3 people can see him]
Ex3 : Input :1,2,7,20,3,5,4,9,8 Output : Returns [3,3] [3 is the Index of 20 and 3 people can see him]
Explanation for Ex3 : Even though both 20 and 9 can be watched by 3 people , as 20's index is less return that array .

Constraints :
0<=A[i]<=100000
0<=Len<=100000

In the case of 4,6,5,6,6,5,0 . 4 can see all three 6's .6 can also each other . The final ans is {4,4}

Note : Return NULL for Invalid Inputs .0 is also a valid viewbale people count .
*/

#include <stddef.h>
#include <stdlib.h>

int* getLeaderIndex(int *arr, int len){
	
	if (arr==NULL || len<0)
	return NULL;
	int i = 0;
	static int ans[2];
	int flag = 0;
	int j=0, max = 0, pos = 0, index = 0, count = 0, num = 0;
	//checking if the arr is sorted in ascending and descending order
	for (i = 0; i < len-1; i++)
	{
		if (arr[i]>arr[i + 1])//for ascending
		{
			break;
		}
	}
	if (i == len-1)
	{
		ans[0] = len - 1;
		ans[1] = len - 1;
		return ans;
	}
	i = 0;
	for (i = 0; i < len - 1; i++)
	{
		if (arr[i]<arr[i + 1])//for descending
		{
			break;
		}
	}
	if (i == len-1)
	{
		ans[0] = 0;
		ans[1] = 0;
		return ans;
	}
	//Now if the array is not sorted
	i = len - 1;
	while (i >= 1)
	{
		count = 0;
		j = i;
		while (j!=0)//logic here is traversing backwards and breaking at positon 
		//where there is an element greater than i'th elemnet and cal the count ....	
		{
			if (arr[i] < arr[j - 1])
				break;
			count++;
			j--;
		}
		num = arr[i];
		pos = i;
		i = j;
		if (max <= count)
		{
			if (max == count)
			{
				index = pos;
			}
			else
			{
				max = count;
				index = pos;
			}
		}
		i--;
	}
	ans[0] = index;
	ans[1] = max;
	return ans;
}