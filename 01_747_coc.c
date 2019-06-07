#include <stdio.h>
#include<stdlib.h>

struct Node {
	int value;
	struct Node *next;
} Node;

struct one_chained_list{		
	struct Node* begin;	
} one_chained_list;

int isEmpty(struct one_chained_list* spisok)
{
	return spisok->begin==NULL;
}

struct Node* find(struct one_chained_list* spisok,int value)
{
	struct Node *tmp=spisok->begin;
	while(tmp->value!=value){
		if(tmp->next!=NULL)
			tmp=tmp->next;
		else
			return 0;
	}
	return tmp;
}

void init(struct one_chained_list* spisok,int value)
{
	struct Node* tmp;
	tmp = (struct Node*)malloc(sizeof(struct Node));
	tmp->value=value;
	tmp->next=NULL;
	spisok->begin = tmp;
}

int push_back(struct one_chained_list* spisok, int x)
{
	if(isEmpty(spisok)==1)
		init (spisok,x);
	else
	{
		struct Node* tmp = (struct Node*)malloc(sizeof(struct Node));
		tmp->value=x;
		tmp->next=NULL;
		struct Node* temp = spisok->begin;
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=tmp;
	}
	return 0;
}

int push_front(struct one_chained_list* spisok,int x) 
{
	if(isEmpty(spisok)==1)
		init (spisok,x);
	else
	{
		struct Node *tmp = (struct Node*)malloc(sizeof(struct Node));
		tmp->value=x;
		tmp->next=spisok->begin;
		spisok->begin=tmp;
	}
	return 0;
}

int clear(struct one_chained_list* spisok)
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
	}
}

void _remove(struct one_chained_list* spisok, struct Node *tmp){
	if(tmp!=NULL){
		if (tmp==spisok->begin)
			spisok->begin=tmp->next;
		else
		{
			struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
			temp=spisok->begin;
			while(temp->next!=tmp)
				temp=temp->next;
			temp->next = tmp->next;
		}
		free(tmp);
	}
}

int removeFirst(struct one_chained_list* spisok, int x)
{
	struct Node* element = find(spisok,x);
	if (element!=NULL){
		_remove(spisok,element);
		return 0;
	}
	return -1;
}

int insertAfter	(struct one_chained_list* spisok,int num, int value)
{
	struct Node *temp = malloc(sizeof(Node));
	temp->value=value;

	struct Node* tmp = spisok->begin;
	struct Node* prev_tmp = spisok->begin;
	
	for (int i = 1;i<num+1;i++)
	{
		prev_tmp=tmp;
		tmp=tmp->next;
		if(tmp==NULL) 
			return -1;
	}
	prev_tmp->next=temp;
	temp->next=tmp;
	return 0;   
}

void print(struct one_chained_list* spisok)
{
	struct Node* tmp=spisok->begin;
	while(tmp->next!=NULL)
	{
		printf("%d ", tmp->value);
		tmp=tmp->next;
	}
	printf("%d\n", tmp->value);
}

int main()
{
	int n,a;
	struct one_chained_list* spisok=(struct one_chained_list*)malloc(sizeof(struct one_chained_list));	
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
	print(spisok);

	int t;
	scanf("%d",&t);
	push_front(spisok,t);
	print(spisok);

	int j,x;
	scanf("%d%d",&j,&x);
	insertAfter(spisok,j,x);
	print(spisok);

	int z;
	scanf("%d",&z);
	removeFirst(spisok,z);
	print(spisok);

	clear(spisok);
	return 0;
}
