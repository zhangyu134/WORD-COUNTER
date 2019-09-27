/*2019.9.21 开始编程
本计数器用于统计若干段落的英文单词数和总量。
开发环境：Dev C++ 5.9.2
编译器配置:TDM-GCC 4.8.1 64-bit Release*/
#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<windows.h>
typedef struct paraunit
{
	int paranum;                                 //定义段落序号 
	int wordnum;                                 //定义每段含有的单词数量 
	struct paraunit *next;                        //指向下一段 
}paraunit;                                        //段落链表单元
typedef struct word0
{
	char c;                                      //定义字符 
	word0 *next;                                 //指向下个字符 
}word0;
struct paraunit *countword(char *paragraph);     //定义计数函数，输入段落，返回一个链表
struct word0 *inputparagraph();                  //定义输入段落函数
word0* linkparagraph(word0 *paragraph1,word0* paragraph2);
void printout(paraunit *list);
word0* linkparagraph(word0 *paragraph1,word0* paragraph2)
{
	word0 *t;
	if(paragraph1==NULL)paragraph1=paragraph2;
	else if(paragraph2==NULL)return paragraph1;
	else
	{
		t=paragraph1;
		while(t->next!=NULL)t=t->next;
		t->next=paragraph2;
	}
	return paragraph1;
}
struct word0 *inputparagraph()
{
	char t;                                     
	word0 *p,*p1; 
	scanf("%c",&t);
	if(t=='#')return NULL;                               
	p1=(word0 *)malloc(sizeof(word0));
	p1->c=t;
	p1->next=NULL;
	p=p1;
	scanf("%c",&t);
	while(t!='\n')
	{
		p1->next=(word0 *)malloc(sizeof(word0));
		p1=p1->next;
		p1->c=t;
		p1->next=NULL;
		scanf("%c",&t);
	}
	p1->next=(word0 *)malloc(sizeof(word0));
	p1=p1->next;
	p1->c='\0';
	p1->next=NULL;
	return p;
}	               
struct paraunit *countword(word0* paragraph)
{
	word0 *t;
	t=paragraph;
	struct paraunit *ch;
	int flag=1,ra=0;
	struct paraunit *ch1=(struct paraunit*)malloc(sizeof(paraunit));
	ch1->paranum=0;
	ch1->wordnum=0;
	ch=ch1;
	bool sletter,bletter,others,numbers;
	while(t!=NULL)
	{
		ra++;
		ch1->paranum=ra;
		ch1->wordnum=0;
		while(t->c!='\0')
		{
			sletter=((t->c)>='a'&&(t->c)<='z');
			bletter=((t->c)>='A'&&(t->c)<='Z');
			others=((t->c)=='-'||(t->c)=='\'');
			numbers=((t->c)>='0'&&(t->c)<='9');
			if(sletter||bletter||others||numbers)
				if(flag==1)
				{
					flag=0;
					ch1->wordnum++;
				}
			if(t->c==' ')flag=1;
			t=t->next;
		}
		if(ch1->paranum>1)ch1->wordnum++;
		t=t->next;
		if(t!=NULL)
		{
			ch1->next=(paraunit *)malloc(sizeof(paraunit));
			ch1=ch1->next;	
			ch1->next=NULL;
		}
	}
	ch1->next=NULL; 
	return ch;
}
void printout(paraunit *list)
{
	int sum1=0,sum2=0,sum3=0; 
	paraunit *p;
	p=list;
	while(p!=NULL)
	{
		printf("第%d段共有%d个单词。\n",p->paranum,p->wordnum);
		sum1=p->paranum;
		sum2+=p->wordnum;
		if(p->wordnum!=0)sum3++;
		p=p->next;
	}
	printf("全文共%d段，%d个非空段，合计%d个单词。\n",sum1,sum3,sum2);
}
int main()
{ 
	word0 *para=NULL,*para1;
	printf("请输入段落(一个回车为一段)，以#为段首结束：\n");
	do
	{
		para1=inputparagraph();
		para=linkparagraph(para,para1);
	}while(para1!=NULL);
	printout(countword(para));
	return 0;	
}

 


