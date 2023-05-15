#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define  MAX_SIZE 10 

typedef char datatype;

typedef struct node 
{
    datatype data[MAX_SIZE];//结点的值
    struct node *lchild;//指向最左子树的根结点指针。
    struct node *Sibling;// 指向右边第一个兄弟结点的指针。
}Cnode;

//创建树
Cnode* CreateTree()
{
    datatype ch[MAX_SIZE];
    Cnode *T;
    printf("%s\n","请输入结点值,#代表空");
    scanf("%s",ch);
    if(strcmp(ch,"#") == 0) {
        T = NULL;
    }else {
        if( !(T=(Cnode *)malloc(sizeof(Cnode)))) return NULL;
        strcpy(T->data,ch);
        printf("创建%s的孩子树\n",ch);
        T->lchild = CreateTree();    //生成最左子树的根结点;
        printf("创建%s的兄弟子树\n",ch);
        T->Sibling = CreateTree();   //生成右边第一个兄弟结点的指针
    }
    return T;
}
//遍历打印树 -调式时使用
void preorderTest(Cnode *root)
{
    if(root) 
    {
        printf("结点值%s\n",root->data);
        preorder(root->lchild); //遍历子树的结点。
        preorder(root->Sibling); //遍历兄弟结点的指针
    }
}
//层序遍历整课树
void printAllTree(Cnode *root)
{
    
}

//只是打印出当前结点的孩子结点
void printchild(Cnode *root) 
{
    Cnode *child = root->lchild;
    while(child) {
        printf("结点值%s\n",child->data);
        child = child->Sibling;//指向child兄弟结点
    }
}
//只是打印出当前结点的兄弟结点
void printSilbling(Cnode *root)
{
    while(root) {
        printf("结点值%s\n",root->data);
        root = root->Sibling;//指向root的兄弟结点
    }
}
//把这课树摧毁
void deleteTree(Cnode *root)
{
    if(root) {
        deleteTree(root->lchild);
        deleteTree(root->Sibling);
        free(root);
    }
}


int main() {
    printf("%s\n","---------创建目录----------");
    //搭建目录
    Cnode* root = CreateTree();

    printf("%s\n","---------遍历整课树--------");
    //遍历整个树
    preorderTest(root);

    printf("%s\n","----------释放空间---------");
    //释放空间
    deleteTree(root);
    return 0;
}