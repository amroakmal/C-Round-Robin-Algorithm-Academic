#ifndef QLL_H_INCLUDED
#define QLL_H_INCLUDED
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
int isEmpty(Queue* q);
QNode* new_node(DT value);
void initializeQ(Queue* q);
void enQueue(Queue* q, DT value);
int size(Queue* q);
DT DeQueue(Queue* q);


#endif // QLL_H_INCLUDED
