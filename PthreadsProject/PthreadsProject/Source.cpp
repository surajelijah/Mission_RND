//#pragma once
//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include<malloc.h>
//#include"threads.h"
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<pthread.h>
#include<Windows.h>
void addToreqQ(struct req* r);
bool b[5];
pthread_mutex_t lock;
int database[100];

struct req{
	// if u want to use my api use define functions as void* func(void*){}
	void*(func)(void*);
	char reqtype;
	// use generic structure here.
	int value;
	int id;

};
struct node{
	struct req* r;
	node* next;
};
struct node* head;
int get(int id){
	if (database[id] >= 0)
	{
		printf("the vaalue at %d id is %d", id, database[id]);
		return 1;
	}
	else{

		return 2;
	}
}


int put(int id, int val){
	database[id] = val;
	return 1;
}

void* generatePutReq(void* args){

	while (true){
		Sleep(500);
		int seed = time(NULL);
		srand(seed);
		int n = rand();
		if (n < 0)n = n*-1;
		struct req* r = (struct req*)malloc(sizeof(struct req));
		r->reqtype = 'p';
		r->id = n % 100;
		r->value = r->id;

		addToreqQ(r);
	}
}

void* generateGetReq(void* args){

	while (true){
		Sleep(1000);
		struct req *r = (struct req*)malloc(sizeof(struct req));
		r->reqtype = 'g';
		int seed = time(NULL);
		srand(seed);
		int n = rand();
		if (n < 0)n = n*-1;
		r->value = n % 10;
		r->id = n % 100;
		addToreqQ(r);
	}

}
void push(struct req* r){
	if (!head){

		struct node* n = (struct node*)malloc(sizeof(struct node));
		n->next = NULL;
		n->r = r;
		head = n;
	}
	else{
		struct node* temp = head;
		struct node* n = (struct node*)malloc(sizeof(struct node));
		n->next = NULL;
		n->r = r;
		while (temp->next){
			temp = temp->next;
		}
		temp->next = n;
	}
}
struct req*  pop(){
	if (!head){
		return NULL;
	}

	//struct node* temp = head;

	struct req *r = head->r;
	head = head->next;
	return r;
}
void addToreqQ(struct req* r){
	push(r);
}



void* workerThread(void* args){
	printf("\nreading the database\n");
	while (true){


		struct req* r;
		pthread_mutex_lock(&lock);
		r = pop();
		pthread_mutex_unlock(&lock);
		if (!r)continue;
		char reqType = r->reqtype;
		if (reqType == 'g'){
			printf("\nreading the database\n");
			int id = r->id;
			get(id);
			printf("\nread the database %d\n", id);
		}
		else if (reqType == 'p'){
			pthread_mutex_lock(&lock);
			printf("\nwriting the database\n");
			int id = r->id;
			int val = r->value;
			put(id, val);
			pthread_mutex_unlock(&lock);

		}
		else{
			continue;
		}

	}
}
void threadManager(){
	// assign  the thread a task.
	pthread_t threadids[5];
	pthread_create(&threadids[0], NULL, workerThread, NULL);
	pthread_create(&threadids[1], NULL, workerThread, NULL);
	pthread_create(&threadids[2], NULL, workerThread, NULL);
	pthread_create(&threadids[3], NULL, workerThread, NULL);
	pthread_create(&threadids[4], NULL, workerThread, NULL);
	pthread_join(threadids[0], NULL);
	pthread_join(threadids[1], NULL);
	pthread_join(threadids[2], NULL);
	pthread_join(threadids[3], NULL);
	pthread_join(threadids[4], NULL);
}

int temp(){
	for (int i = 0; i < 5; i++)b[i] = true;
	head = NULL;
	int err = 0;
	pthread_mutex_init(&lock, NULL);


	pthread_t threadids[2];

	pthread_create(&threadids[0], NULL, generateGetReq, NULL);
	pthread_create(&threadids[0], NULL, generatePutReq, NULL);
	threadManager();
	pthread_join(threadids[0], NULL);
	pthread_join(threadids[1], NULL);
	pthread_mutex_destroy(&lock);

	return 0;
}


int main(){
	temp();
}
