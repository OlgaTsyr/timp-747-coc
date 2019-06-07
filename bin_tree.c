#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	struct node *left,*right,*prev;
	int value;
} node;

typedef struct tree
{
	int size;
	struct node* root;
} tree;

void init(tree* t){
	t->root=NULL;
	t->size=0;
}

void clear_node(node* n){
	if(n!=NULL){
		if(n->left!=NULL)
			clear_node(n->left);	
		if(n->right!=NULL)
			clear_node(n->right);
	}
	free(n);
	n=NULL;
}

void clear(tree* t){
	clear_node(t->root->left);
	clear_node(t->root->right);
	t->root=NULL;
	t->size=0;
}

int removeMin(node* n){
	if(n!=NULL){
		if(n->left!=NULL)
			return removeMin(n->left);
		else{
			if(n->right!=NULL){
				n->prev->right=n->right;
				n->right=n->prev;
			}else
				n->prev->left=NULL;
			int res=n->value;
			free(n);
			n=NULL;
			return res;
		}
	}	
}

void insert(tree* t,int value){
	node* new = malloc(sizeof(node));
	new->value=value;
	new->left=new->right=new->prev=NULL;
	if(t->root==NULL){
		t->root=new;
		t->size=1;
		return;
	}
	node* tmp=t->root;
	while(1){
		if(tmp->value==value)
			return;
		if(value > tmp->value){
			if(tmp->right==NULL){
				new->prev=tmp;
				tmp->right=new;
				t->size++;
				return;
			}
			else
				tmp=tmp->right;
		}
		else if(value < tmp->value){
			if(tmp->left==NULL){
				new->prev=tmp;
				tmp->left=new;
				t->size++;
				return;
			}else
				tmp=tmp->left;
		}
	}
}

int find(tree* t,int value,node* n){
	if(t->root==NULL)
		return 1;
	node* tmp=t->root;
	while(1){
		if(tmp==NULL)
			return 1;
		if(tmp->value==value){
			n->value=tmp->value;
			n->left=tmp->left;
			n->right=tmp->right;
			n->prev=tmp->prev;
			return 0;
		}
		if(value > tmp->value)
			tmp=tmp->right;
		else if(value < tmp->value)
			tmp=tmp->left;
	}
}

int removeElement(tree* t,int value){
	if(t->root==NULL)
		return 1;
	node* tmp=t->root;
	while(1){
		if(tmp==NULL)
			return 1;
		if(value > tmp->value)
			tmp=tmp->right;
		else if(value < tmp->value)
			tmp=tmp->left;
		else{
			if(tmp->left==NULL && tmp->right==NULL){
				if(tmp->prev->left==tmp)
					tmp->prev->left=NULL;
				else if(tmp->prev->right==tmp)
					tmp->prev->right=NULL;
				free(tmp);
			}
			else if(tmp->left!=NULL && tmp->right==NULL){
				if(tmp->prev->left==tmp)
					tmp->prev->left=tmp->left;
				else if(tmp->prev->right==tmp)
					tmp->prev->right=tmp->left;
				free(tmp);
			}
			else if(tmp->left==NULL && tmp->right!=NULL){
				if(tmp->prev->left==tmp)
					tmp->prev->left=tmp->right;
				else if(tmp->prev->right==tmp)
					tmp->prev->right=tmp->right;
				free(tmp);
			}
			else{
				tmp->value=removeMin(tmp->right);
			}
			t->size--;
			return 0;
		}
	}
}

void printTree(tree* t){
	if(t->root==NULL)
		printf("-\n");
	else{	
		node** nodes_to_print[2];
		nodes_to_print[0] = malloc(sizeof(node)*32);
		nodes_to_print[1] = malloc(sizeof(node)*32);
		int next_free_pos[2]={0,0},values_for_printing[2]={0,0},is_1=1;
		printf("%d\n", t->root->value);
		nodes_to_print[0][next_free_pos[0]]=t->root->left;
		next_free_pos[0]++;
		nodes_to_print[0][next_free_pos[0]]=t->root->right;
		next_free_pos[0]++;
		values_for_printing[0]=1;

		while(values_for_printing[0] || values_for_printing[1]){
			values_for_printing[is_1]=0;
			for(int i=0;i<next_free_pos[1-is_1];i++){
				if(nodes_to_print[1-is_1][i]!=NULL){
					printf("%d",nodes_to_print[1-is_1][i]->value);
					nodes_to_print[is_1][next_free_pos[is_1]]=nodes_to_print[1-is_1][i]->left;
					next_free_pos[is_1]++;
					nodes_to_print[is_1][next_free_pos[is_1]]=nodes_to_print[1-is_1][i]->right;	
					next_free_pos[is_1]++;
					if(nodes_to_print[1-is_1][i]->left!=NULL || nodes_to_print[1-is_1][i]->right!=NULL)
						values_for_printing[is_1]=1;
				}else{
					printf("_");
					nodes_to_print[is_1][next_free_pos[is_1]]=NULL;
					next_free_pos[is_1]++;
					nodes_to_print[is_1][next_free_pos[is_1]]=NULL;
					next_free_pos[is_1]++;
				}
				if(i+1!=next_free_pos[1-is_1]){
					printf(" ");
				}
			}
			next_free_pos[1-is_1]=0;
			values_for_printing[1-is_1]=0;
			free(nodes_to_print[1-is_1]);
			nodes_to_print[1-is_1] = malloc(sizeof(node)*32);
			is_1^=1;
			printf("\n");
		}
	}
}

int rotateRight(node* n){
	if(n->left!=NULL){
		node* tmp = n->left;
		n->left=NULL;
		n->prev=tmp;
		tmp->prev=NULL;
		tmp->right=n;		
		return 0;
	}
	else
		return 1;
}

int rotateLeft(node* n){
	if(n->right!=NULL){
		node* tmp = n->right;
		n->right=NULL;
		n->prev=tmp;
		tmp->prev=NULL;
		tmp->left=n;
		return 0;
	}
	else
		return 1;
}

void print(node* n){
	printf("%d ", n->value);
	if(n->left!=NULL)
		print(n->left);
	else
		printf("_\n");
	if(n->right!=NULL)
		print(n->right);
	else
		printf("_\n");
	printf("\n");
}

void print_found(node* n){
	if(n->prev!=NULL)
		printf("%d ", n->prev->value);
	else
		printf("_ ");
	if(n->left!=NULL)
		printf("%d ", n->left->value);
	else
		printf("_ ");
	if(n->right!=NULL)
		printf("%d\n", n->right->value);
	else
		printf("_\n");
}

int main(){
	tree* root = malloc(sizeof(tree));
	init(root);
	int t;
	for(int i=0;i<4;i++){
		scanf("%d",&t);
		insert(root,t);
	}
	printTree(root);
	for(int i=0;i<3;i++){
		scanf("%d",&t);
		insert(root,t);
	}
	printTree(root);

	int m;
	node* n = malloc(sizeof(node));
	for(int i=0;i<2;i++){
		scanf("%d",&m);
		if(find(root,m,n)==0)
			print_found(n);
		else
			printf("-\n");	
	}

	scanf("%d",&m);
	removeElement(root,m);
	printTree(root);
	while(1){
		node* n = root->root;
		if(rotateLeft(n)==0)
			root->root=n->prev;
		else
			break;
	}
	printTree(root);
	while(1){
		node* n = root->root;
		if(rotateRight(n)==0)
			root->root=n->prev;
		else
			break;
	}
	printTree(root);
	printf("%d\n", root->size);
	clear(root);
	printTree(root);
	return 0;
}