#include <stdio.h>
#include <string.h>

#include "task.h"
#include "cpu.h"

#define SLICE 10
#define SIZE 100

static int wt[SIZE],i=0,j,n,total=0,pos;
static float avg_wt;
static Task task_list[SIZE], temp;


void add(char *name,int priority, int burst) {
    n++;
    Task task;
    task.name = name;
    task.tid = n;
    task.priority = priority;
    task.burst = burst; 
    task_list[i] = task;
    i++;
}

void schedule(){
    //sorting of burst times
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(task_list[j].burst<task_list[pos].burst)
                pos=j;
        }
        temp=task_list[i];
        task_list[i] = task_list[pos];
        task_list[pos]=temp;
    }

    //Calculating wait time and averate wait time
    wt[0]=0;            
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=task_list[j].burst;
        total+=wt[i];
    }
    avg_wt=(float)total/n;  

    //Printing the schedule
    printf("Task schedule");    
    printf("\nProcess\t    Burst Time    \tWaiting Time");
    for(i=0;i<n;i++)
    {   
        int burst=task_list[i].burst;
        printf("\n%s\t\t  %d\t\t    %d\t\t",task_list[i].name,burst,wt[i]);
    }  
    printf("\n\nAverage Waiting Time=%f \n",avg_wt);

    //Execute the tasks
    for(i=0;i<n;i++)
    {   
        run(task_list[i], SLICE);
    } 
}


