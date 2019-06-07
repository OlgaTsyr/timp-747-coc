#include <stdio.h>
#include<stdlib.h>

struct Node {
	int value;
	struct Node *next;
	struct Node *prev;
} Node;

struct two_chained_list{		
	struct Node* begin;
	struct Node* end;	
} two_chained_list;

int isEmpty(struct two_chained_list* spisok)
{
	return spisok->begin==NULL && spisok->end==NULL;
}

struct Node* find(struct two_chained_list* spisok,int k)
{
	struct Node *tmp=spisok->begin;
	while(tmp->value!=k){
		if(tmp->next!=NULL){
			tmp=tmp->next;
		}else{
			return 0;
		}
	}
	return tmp;
}

struct Node* find_invers(struct two_chained_list* spisok,int k)
{
	struct Node *tmp=spisok->end;
	while(tmp->value!=k){
		if(tmp->prev!=NULL){
			tmp=tmp->prev;
		}else{
			return 0;
		}
	}
	return tmp;
}

void init(struct two_chained_list* spisok,int value)
{
	struct Node* tmp;
	tmp = (struct Node*)malloc(sizeof(struct Node));
	tmp->value=value;
	tmp->next=NULL;
	tmp->prev=NULL;
	spisok->begin = tmp;
	spisok->end = tmp;
}

int push_back(struct two_chained_list* spisok, int x)
{
	if(isEmpty(spisok)==1)
		init (spisok,x);
	else
	{
		struct Node *tmp = (struct Node*)malloc(sizeof(struct Node));
		tmp->value=x;
		tmp->prev=spisok->end;
		tmp->next=NULL;
		spisok->end=tmp;
		tmp->prev->next=tmp;
	}
	return 0;
}

int push_front(struct two_chained_list* spisok,int x) 
{
	if(isEmpty(spisok)==1)
		init (spisok,x);
	else
	{
		struct Node *tmp = (struct Node*)malloc(sizeof(struct Node));
		tmp->value=x;
		tmp->prev=NULL;
		tmp->next=spisok->begin;
		spisok->begin=tmp;
		tmp->next->prev=tmp;
	}
	return 0;
}

int clear(struct two_chained_list* spisok)
{
	if(isEmpty(spisok)==1)
	{
		struct Node *tmp=spisok->begin;
		struct Node *temp=NULL;
		while(tmp!=NULL)
		{
			temp=tmp->next;
			free(tmp);
			tmp=temp;
		}
		spisok->begin=NULL;
		spisok->end=NULL;
	}
}

void _remove(struct two_chained_list* spisok, struct Node *tmp){
	if(tmp!=NULL){
		if (tmp==spisok->begin && tmp==spisok->end) {
			clear(spisok);
			return;
		}
		if (tmp==spisok->begin)
		{
			spisok->begin=tmp->next;
			tmp->next->prev=NULL;
		}
		else if(tmp==spisok->end)
		{
			spisok->end=tmp->prev;
			tmp->prev->next=NULL;
		}
		else if (tmp!=spisok->begin && tmp!=spisok->end)
		{
			tmp->next->prev=tmp->prev;
			tmp->prev->next=tmp->next;
		}
		free(tmp);
	}
}

int removeLast(struct two_chained_list* spisok,int x)
{
	struct Node* element = find_invers(spisok,x);
	if (element!=NULL){
		_remove(spisok,element);
		return 0;
	}
	return -1;
}

int removeFirst(struct two_chained_list* spisok, int x)
{
	struct Node* element = find(spisok,x);
	if (element!=NULL){
		_remove(spisok,element);
		return 0;
	}
	return -1;
}

int insertAfter	(struct two_chained_list* spisok,int num, int data)
{
	struct Node* tmp = spisok->begin;
	for (int i = 1;i<num;i++)
	{
		tmp=tmp->next;
		if(tmp==NULL) 
			return -1;
	}
	struct Node *temp = malloc(sizeof(Node));
	temp->value=data;
	temp->next=tmp->next;
	temp->prev=tmp;
	tmp->next->prev=temp;
	tmp->next=temp;  
	return 0;   
}

int insertBefore(struct two_chained_list* spisok,int num, int data)
{
	struct Node* tmp = spisok->begin;
	for (int i = 1;i<num;i++)
	{
		tmp=tmp->next;
		if(tmp==NULL) 
			return -1;
	}
	struct Node *temp = malloc(sizeof(Node));
	temp->value=data;
	temp->prev=tmp->prev;
	temp->next=tmp;
	tmp->prev=temp;
	temp->prev->next=temp;      
	return 0; 
}

void print(struct two_chained_list* spisok)
{
	struct Node* tmp=spisok->begin;
	while(tmp->next!=NULL)
	{
		printf("%d ", tmp->value);
		tmp=tmp->next;
	}
	printf("%d\n", tmp->value);
}

void print_invers(struct two_chained_list* spisok)
{
	struct Node* tmp=spisok->end;
	while(tmp->prev!=NULL)
	{
		printf("%d ", tmp->value);
		tmp=tmp->prev;
	}
	printf("%d\n", tmp->value);	
}



int main()
{
	int n,a;
	struct two_chained_list* spisok=(struct two_chained_list*)malloc(sizeof(struct two_chained_list));	
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&a);
		push_back(spisok,a);
	}
	print(spisok);
	
	int k[3];
	for(int i=0;i<3;i++){
		scanf("%d",&k[i]);
		if(find(spisok,k[i])!=NULL)
			printf("1");
		else
			printf("0");
	}
	printf("\n");

	int m;
	scanf("%d",&m);
	push_back(spisok,m);
	print_invers(spisok);

	int t;
	scanf("%d",&t);
	push_front(spisok,t);
	print(spisok);

	int j,x;
	scanf("%d%d",&j,&x);
	insertAfter(spisok,j,x);
	print_invers(spisok);

	int u,y;
	scanf("%d%d",&u,&y);
	insertBefore(spisok,u,y);
	print(spisok);

	int z;
	scanf("%d",&z);
	removeFirst(spisok,z);
	print_invers(spisok);

	int r;
	scanf("%d",&r);
	removeLast(spisok,r);
	print(spisok);

	clear(spisok);
	return 0;
}
