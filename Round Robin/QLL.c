#include <stdio.h>
#include <stdlib.h>
#define DT P

typedef struct
{
    char pname[5];
    int st,et;
} P;

typedef struct
{
    DT data;
    struct QNode* next;

} QNode;

typedef struct
{
    QNode* front,*rear;
} Queue;

int isEmpty(Queue* q)
{
    if(q->front == NULL )
        return 1;
    return 0;
}

QNode* new_node(DT value)
{
    QNode* temp = (QNode*)malloc(sizeof(QNode));
    temp->data = value;
    temp->next = NULL;
    return temp;
}

void initializeQ(Queue* q)
{
    q->front = q->rear = NULL;
}

void enQueue(Queue* q, DT value)
{
    QNode* n = new_node(value);
    if(isEmpty(q))
    {
        q->front = q->rear = n;
    }
    else
    {
        q->rear->next = n;
        q->rear = n;
    }
}
int size(Queue* q)
{
    int c=0;
    QNode* n = q->front;
    while(n)
    {
        c++;
        n=n->next;
    }
    return c;
}

DT DeQueue(Queue* q)
{
    if(!isEmpty(&q))
    {
        DT x = q->front->data;
        QNode* tempo = q->front;
        q->front = q->front->next;
        free(tempo);
        return x;
    }
    else
    {
        printf("Queue is empty");
        exit(-1);

    }
}
