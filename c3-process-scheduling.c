//
//  main.c
//  jincheng
//
//  Created by Yiyi Deng on 10/24/16.
//  Copyright © 2016 邓依伊. All rights reserved.
//
//  编写并调试一个模拟的进程调度程序，采用“最高优先数优先”调度算法对多个并发进程进行调度。
//  要求：采用动态优先数。即进程的优先数在创建进程时可以给定一个初始值，并且可以按一定原则修改优先数：在进程获得一次CPU后就将其优先数减少1。

#include <stdio.h>
#include <stdlib.h>

#define getpch(type) (type*)malloc(sizeof(type))


struct pcb { /* 定义进程控制块PCB */
    char state;
    int id;
    int  prio;
    int  needtime;
    int  runtime;
    struct pcb * next;
}*ready=NULL, *p; // 就绪队列的头进程，当前运行进程

typedef struct pcb PCB;

void insert();

void input() /* 建立进程控制块函数 */
{
    int i,num;
    
    printf("\n number of processes:");
    scanf("%d",&num);
    for(i=0;i<num;i++)
    {
        printf("\n No.%d:",i);
        p=getpch(PCB);
        p->id = i;
        printf("\n priority:");
        scanf("%d",&p->prio);
        printf(" required time:");
        scanf("%d",&p->needtime);
        p->runtime=0;
        p->state='W';
        p->next=NULL;
        insert();
    }
}

// 优先数算法的插入
void insert() // 创建一个进程后&一个进程运行1个单位时间后，要将这个进程插入就绪队列
{
    PCB *in;
    in=ready;
    
    if (ready==NULL) // 此时就绪队列为空
        ready=p;
    else
    {
        if (in->prio<=p->prio) // 就绪队列第一个进程的优先级<=当前进程
        {
            p->next=in; // 直接把当前进程插到队头
            ready=p;
        }
        else
        {
            while (in->next!=NULL)
            {
                if (in->next->prio>=p->prio)
                    in=in->next; // 继续往后找
                else break;
            }
            // 插到in后面（此时这个in，要么是最后一个，此时所有就绪进程优先级都比p大；要么是第一个出现的优先级比p小的进程的前面一个）
            p->next=in->next;
            in->next=p;
        }
    }
}

void disp(PCB * pr) /* 建立进程显示函数 */
{
    printf("\n id\tstate\tpriority\tneedtime\truntime \n");
    printf(" %d \t\t",pr->id);
    printf(" %c \t\t",pr->state);
    printf(" %d \t\t",pr->prio);
    printf(" %d \t\t",pr->needtime);
    printf(" %d \t\t",pr->runtime);
    printf("\n");
}

void check() /* 建立进程查看函数 */
{
    PCB* pr;
    printf("\n **** Current Process:%d",p->id); /*显示当前运行进程*/
    disp(p);
    pr=ready;
    printf("\n **** Current ready Queue:\n"); /*显示就绪队列状态*/
    while(pr!=NULL)
    {
        disp(pr);
        pr=pr->next;
    }
}

void destroy() /*建立进程撤消函数(进程运行结束,撤消进程)*/
{
    printf("\n Process [%d] has finished.\n",p->id);
    free(p);
}

void running() /* 建立进程就绪函数 */
{
    (p->runtime)++;
    (p->prio)--;
    if(p->runtime==p->needtime)
        destroy();
    else
    {
        p->state='W';
        insert();
    }
}

int main()
{
    int h=0;
    char ch;
    input();
    ch=getchar();
    while(ready!=NULL)
    {
        h++;
        printf("\n The execute number:%d \n",h); 
        p=ready; 
        ready=p->next; 
        //p->next=NULL;
        p->state='R'; 
        check(); 
        running(); 
        printf("\n Press any key to continue");
        ch=getchar();
    }
    printf("\n\n Finished.\n");
    ch=getchar();
    return 0;
} 
