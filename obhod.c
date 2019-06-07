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

void printTree(tree* t){
	if(t->root==NULL)
		printf("-");
	else{	
		node** nodes_to_print[2];
		nodes_to_print[0] = malloc(sizeof(node)*32);
		nodes_to_print[1] = malloc(sizeof(node)*32);
		int next_free_pos[2]={0,0},values_for_printing[2]={0,0},is_1=1;
		printf("%d ", t->root->value);
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
			printf(" ");
		}
	}
	printf("\n");
}

void preorderPrintTree(tree* t){
	node** nodes = malloc(sizeof(node)*32);
	int last_pos=31;
	printf("%d ", t->root->value);
	nodes[last_pos]=t->root->right;
	last_pos--;
	nodes[last_pos]=t->root->left;
	last_pos--;
	while(last_pos!=31){
		last_pos++;
		node* tmp=nodes[last_pos];
		printf("%d ", tmp->value);
		if(tmp->right!=NULL){
			nodes[last_pos]=tmp->right;
			last_pos--;
		}
		if(tmp->left!=NULL){
			nodes[last_pos]=tmp->left;
			last_pos--;
		}
	}
	printf("\n");
}

void postorderPrintNode(node* n){
	if (n!=NULL) {
        postorderPrintNode(n->left);
        postorderPrintNode(n->right);
        printf("%d ", n->value);
    }
}

void postorderPrintTree(tree* t){
	postorderPrintNode(t->root->left);
	postorderPrintNode(t->root->right);
	printf("%d\n", t->root->value);
}


int main(){
	tree* root = malloc(sizeof(tree));
	init(root);
	int t;
	for(int i=0;i<7;i++){
		scanf("%d",&t);
		insert(root,t);
	}
	printTree(root);
	preorderPrintTree(root);
	postorderPrintTree(root);
	clear(root);	
	return 0;
}