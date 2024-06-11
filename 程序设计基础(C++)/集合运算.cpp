#include <iostream>;
using namespace std;
struct Node
{
	int content;
	Node *next;
};
//输入一个集合 
Node* input_set()
{
	Node* head=NULL,* tail=NULL;
	int x;
	cin>>x;
	while (x!=999)
	{
		Node*p=new Node;
		p->content=x;
		p->next=NULL;
		if (head==NULL)
		head=tail=p;
		else {
			tail->next=p;
			tail=p;	
		}
		
		cin>>x;
	}
	return head;
}
//为实现运算所需要的一些操作
//查找元素
bool find(Node *head,int x)
{
	int d=0; 
	for (Node *p=head;p!=NULL;p=p->next)
	if (p->content==x){
		d=1;
		break;
	}
	return d;
}
//添加元素
void insert(Node *head,int x)
{
	Node *p=new Node;
	p->content=x;
	p->next=head;
	head=p;
}
//求交集 
Node *intersection(Node *head1,Node *head2)
{
	Node *head=NULL;
	for (Node *p=head1;p!=NULL;p=p->next)
	{
		if (find (head2,p->content))
		insert(head,p->content);
	}
	return head;
}
//求并集
Node *unions(Node *head1,Node *head2) 
{
	Node *head=NULL,*p;
	for (p=head1;p!=NULL;p=p->next)
	insert (head,p->content);
	for (p=head2;p!=NULL;p=p->next)
	{
		if (!find(head1,p->content))
		insert (head,p->content);
	}
	return head;
}
//求差集
Node *differences(Node *head1,Node *head2)
{
	Node *head=NULL,*p;
	for(p=head1;p!=NULL;p=p->next)
	{
		if (!find(head2,p->content))
		insert (head,p->content);	
	}
	return head;
 } 
 //输出集合
 void output_set(Node *head)
 {
 	Node *p;
 	for (p=head;p!=NULL;p=p->next)
 	cout<<p->content<<" ";
 	cout<<endl;
  } 
int main()
{
	cout<<"请依次输入两个集合的元素(以999为结束)";
	Node *set1,*set2,*set_intersection,*set_union,*set_difference;
	set1=input_set();
	set2=input_set();
	set_intersection=intersection(set1,set2);
	set_union=unions(set1,set2);
	set_difference=differences(set1,set2);
	cout<<"交集是："; 
	output_set(set_intersection);
	cout<<"并集是：";
	output_set(set_union); 
	cout<<"差集是："; 
	output_set(set_difference);
	return 0;
 } 
