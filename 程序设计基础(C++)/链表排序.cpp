#include <iostream>
using namespace std;
struct Node
{
	int content;
	Node *next;
};
Node *input()//输入数据，建立链表
{
	Node *head=NULL;
	int x;
	cin>>x;
	while (x!=-1)
	{
		Node *p=new Node;
		p->content=x;
		p->next=head;//新结点插在表头
		head=p;
		cin>>x; 
	 } 
	 return head;
 } 
void sort(Node *h)
 {
 	if (h==NULL||h->next==NULL)
 		return;//只有一个或没有结点时不用排序
 	else for (Node *p1=h;p1->next!=NULL;p1=p1->next)//遍历一次
		{
			Node *p_min=p1;//将指向最小的结点,初始化为P1 
			for(Node *p2=p1->next;p2!=NULL;p2=p2->next) //再遍历一次,从p1之后开始比较 
			if(p2->content<p_min->content)
			p_min=p2;//保持指向最小的结点
			if(p_min!=p1)
			{
				int temp=p1->content;
				p1->content=p_min->content;
				p_min->content=temp;//排序思路：把小的往前放 
			 } 	
		 } 	 
 }
void output (Node *h)
{
	for (Node *p=h;p!=NULL;p=p->next)
		cout<<p->content<<',';
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
	sort(head);
	output(head);
	remove(head);
	return 0;
}
