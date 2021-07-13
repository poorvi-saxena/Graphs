#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct node{
    struct node *left;
    int data;
    struct node *right;
};

struct queue
{
    int size;
    int front;
    int rear;
    node **Q;
};

void create(struct queue *q, int size)
{
  q->size=size;
    q->front=NULL;
    q->rear=NULL;
    q->Q=(node **)malloc(q->size*sizeof(node *));
}

void enqueue(struct queue *q, node *x)
{
    q->rear=(q->rear+1)%q->size;
    q->Q[q->rear]=x;
}

node * dequeue(struct queue *q)
{
    node* x=NULL;
    if(q->front==q->rear){
        cout<<"Ëmpty Queue"<<"\n";
    }
    else{
        q->front=(q->front+1)%q->size;
        x=q->Q[q->front];
    }
    return x;
}

int isEmpty(struct queue q)
{
    return q.front==q.rear;
}

#endif // QUEUE_H_INCLUDED
