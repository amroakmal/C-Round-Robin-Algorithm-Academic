#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "QLL.h"
#define DT P

int main()
{
    DT array[100];
    DT temp;
    int i=0,j;
    FILE *fp;

    fp = fopen("datafile.txt", "r");
    char src[28]; // a temp array for just getting the wanted time slots from the file
    while(!feof(fp))
    {
        fgets(src,28,fp);
        break;
    }
    //getting the wanted time slots to work on from the given file
    int c1=src[22]-'0';
    int  c2=src[23]-'0';
    int tot=c1*10+c2;
    char auxarray[tot][tot];

    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp, "%s" "%d" "%d",  array[i].pname,&array[i].st,&array[i].et);
            i++;
        }
    }
    //auxn: for getting the number of processes to be worked on from the file
    int auxn=i;
    Queue Q;
    initializeQ(&Q);
    for(i=0; i<tot; i++)
    {
        for(j=0; j<tot; j++)
        {
            auxarray[i][j]='\0';
        }
    }
//Make sure processes scheduled assendingly from the File
    for(i=0; i<tot; i++)
    {
        for(j=i+1; j<auxn-2; j++)
        {
            if(array[i].st >array[j].st)
            {
                temp = array[i];
                array[i]=array[j];
                array[j]=temp;
            }
        }

    }
    //enQueueing all the processes at the beginning before scheduling
    //tot: the wanted watching time slots form the file
    //Nested Loop as may more than one process have same start time
    for(i=0; i<tot; i++)
    {
        for(j=0; j<auxn-1; j++)
        {
            if(i==array[j].st)
            {
                enQueue(&Q,array[j]);
            }

        }
    }


    DT t;
    int x;
    int cntnumber=auxn-1;
    int data1[cntnumber];
    int k=0;//For putting values in data1 array for calculating waiting time
    // char data2 [tot][tot];
    for(i=0; i<tot; i++)
    {
        x=0;
        for(j=0; j<cntnumber; j++)
        {
            t=DeQueue(&Q);
            //Checking if its the right process's start time to operate in it or not
            if(t.st <= i )
            {
                x=1;
                if(t.et == 0)
                {
                    DeQueue(&Q);
                }
                break;
            }
            //if not the right process time, return it back to the Queue and check the next process
            else
            {
                enQueue(&Q,t);
            }
        }
        //if its the right process time to work on
        if(x==1)
        {
            strcpy(auxarray[i],t.pname);
            //decrement the exec. time for the process
            t.et--;
            //checking if the program aborted or not
            if(t.et ==0 )
            {

                //strcpy(data2[i],t.pname);
                printf("%s \t (%d--->%d)  %s aborts\n",t.pname,i,i+1,t.pname);
                data1[k++]=i-t.st-t.et+1;
                cntnumber--;
            }
            else
            {
                printf("%s \t (%d--->%d) \n",t.pname,i,i+1);
                enQueue(&Q,t);
            }
        }
        //if no processes working on this time interval
        else
        {
            printf("idle \t (%d--->%d)\n",i,i+1);
        }
        //when to end after the given wanted time sots
        if(i==tot-1)
        {
            printf("stop\n");
            break;
        }
    }
    printf("\n");
    printf("Gantt Table:\n_____________\n\nProcess\tFrom:\tTo:\n");

    for(i=0; i<tot; i++)
    {
        printf("%s\t|%d\t|%d\t\n",auxarray[i],i,i+1);
    }

    float sum=0;
    for(i=0; i<k; i++)
    {
        sum+=data1[i];
    }
    printf("\nAverage Waiting Time = %.3f\n",sum/k);

}
