#include <stdio.h>
#include <string.h>

#define MAX_SIZE 10 

typedef struct TreeNode{
	//文件名或者目录名
	//如果是叶子结点，说明是最后的目录、文件
	char *val;
	//int q;
	//初始化size为10
	
	struct TreeNode *next[MAX_SIZE];
} tnode;

void init(tnode *root){
	root->val = "/";
	for(int i=0;i<MAX_SIZE;i++) {
		root->next[i] = NULL;
	}
}

void addnode(tnode *root,char *val) {
	//ifjudge 是true 就跳到新建的目录， 是false 就不跳转到新建立的目录
	tnode temp;
	temp.val = val;
	for(int i=0;i<MAX_SIZE;i++) {
		root->next[i] = NULL;
	}
	for(int i=0;i<MAX_SIZE;i++) {
		if(root->next[i] == NULL) {
			root->next[i]=&temp;

			//if(ifjudge) { return *(root->next[i]);}
		}
	}
	//return *root;
	
}

void display(tnode *root) {
	if(root == NULL ) {
		return;
	}
	printf("%s\n",root->val);

	for(int i=0;i<MAX_SIZE;i++) {
		if(root->next[i]!=NULL) {
			printf("%s\n", root->next[i]->val);
		}
		// display(root->next[i]);
	}
}



int main(){

	//首先输入目录，然后构建这个树
	printf("初始化目录，根目录设置为/\n");
	tnode tree;
	init(&tree);
	display(&tree);
	tnode cur = tree;
	int c_time=0;
	
	while(c_time < 10) {

		char *s;
		scanf(" %s",s);
		// getchar();
		addnode(&cur,s);
		display(&tree);
		c_time+=1;
		printf(" c_time is %d\n",c_time);
	}


	return 0;
}
