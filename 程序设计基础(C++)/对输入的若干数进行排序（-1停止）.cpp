#include <iostream>
struct Node
{
	int content;//代表结点的数据
	Node *next;//代表后一个结点的地址 
};
//下面进行操作声明
extern Node *input();//输入数据并建立链表
extern void sort(Node *h);//排序
extern void output(Node *h);//输出数据
extern void remove(Node *h);//删除链表 
using namespace std;
Node *input()//从表头插入数据，这样简单 
{
	Node *head=NULL;
	int x;
	cin>>x;
	while (x!=-1)
	{
		Node *p=new Node;//生成新结点
		p->content=x;
		p->next=head;//新结点插入表头
		head=p;//把新结点设置为表头结点
		cin>>x; 
	}
	return head;
 }
void sort(Node *h)//采用选择排序，小的往前放 
{
	if (h==NULL||h->next==NULL)//链表只有一个或没有结点
	return;
	//从链表的头开始逐步缩小链表的范围
	for (Node *p1=h;p1->next!=NULL;p1=p1->next) 
	{
		Node *p_min=p1;//p_min指向最小的结点，初始化为p1
		//从p1的下一个开始与p_min比较
		for (Node *p2=p1->next;p2!=NULL;p2=p2->next)
		if (p2->content>p_min->content)
		p_min=p2;//保持P_min是最小的
		if (p_min!=p1)//交换P_min与p1指向的结点的值，使p1指向的结点的值是最小的，以便输出
		 {
		 	int temp=p1->content;
		 	p1->content=p_min->content;
		 	p_min->content=temp;
		 }
	}
}
void output(Node *h)
{
	for (Node *p=h;p!=NULL;p=p->next)
	cout<<p->content<<" ";
	cout<<endl;
}
void remove(Node *h)
{
	while (h!=NULL)
	{
		Node *p=h;
		h=h->next;
		delete p;
	}
}
int main()
{
	Node *head;
	head=input();
	sort (head);
	output (head);
	remove (head);
	return 0;	
}

