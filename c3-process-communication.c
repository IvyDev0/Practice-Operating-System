#include  <stdio.h>
#include  <sys/types.h>
#include  <sys/msg.h>
#include  <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>

#define  MSGKEY 75         /*定义关键词MEGKEY*/

struct  msgform         
{
  long mtype;
  char mtext[256]; /*文本长度*/
}msg;

int msgqid,i;

void CLIENT()
{      
  int i,pid,*pint;;
  msgqid=msgget(MSGKEY,0777);

  for(i=10;i>=1;i--)
  {
    msg.mtype=i;  
    msgsnd(msgqid,&msg,sizeof(int),0); /*发送消息msg入msgid消息队列*/
   	printf("(Client)sent: %d\n",i);

    msgrcv(msgqid,&msg,256,i+10,0);  /*从msgqid队列接收消息msg */
    printf("Client:received reply\n");
  }
  exit(0);  
}

void SERVER()
{
  int i;
  msgqid=msgget(MSGKEY,0777|IPC_CREAT); /*由关键字获得消息队列*/
  for(i=10;i>=1;i--)
  {
    msgrcv(msgqid,&msg,256,i,0);  /*从msgqid队列接收消息msg */
    printf("(Server)received\n");

    msg.mtype=i+10; 
    msgsnd(msgqid,&msg,sizeof(int),0);       /*发送应答消息msg*/
    printf("Sever:sent reply\n");
  } /*消息类型为1时,释放队列*/
	exit(0);
}

int main()
{
  while ((i=fork())==-1);
  if(!i) SERVER();
  while ((i=fork())==-1);
  if(!i) CLIENT();
  wait(0);
  wait(0);
  exit(0);
  return 0;
}   
