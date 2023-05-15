#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define  MAX_SIZE 10 //目录名的长度限制
#define  MAX_NODE 100 //队列中最多的结点数目

typedef char datatype;

typedef struct node 
{
    datatype data[MAX_SIZE];//结点的值
    int type; //0是目录 1是文件
    struct node *lchild;//指向最左子树的根结点指针。
    struct node *Sibling;// 指向右边第一个兄弟结点的指针。
}Cnode;

//创建树
Cnode* CreateTree()
{
    datatype ch[MAX_SIZE];
    int type = 0;
    char y;
    Cnode *T;
    printf("%s\n","请输入结点值,#代表空");
    scanf("%s",ch);
    printf("%s\n","是否是文件 Y/N");
    scanf("%c",&y);
    if(y == 'y' || y == 'Y') {
        type = 1;
    }
    if(strcmp(ch,"#") == 0) {
        T = NULL;
    }else {
        if( !(T=(Cnode *)malloc(sizeof(Cnode)))) return NULL;
        strcpy(T->data,ch);
        T->type = type;
        printf("创建%s的孩子树\n",ch);
        T->lchild = CreateTree();    //生成最左子树的根结点;
        printf("创建%s的兄弟子树\n",ch);
        T->Sibling = CreateTree();   //生成右边第一个兄弟结点的指针
    }
    return T;
}
//遍历打印树
void preorderTest(Cnode *root)
{
    if(root) 
    {
        printf("结点值%s\n",root->data);
        Cnode * temp = root->lchild;
        printf("-------------\n");
        while(temp!=NULL) {
            if(temp->type == 0) {
                printf("        目录---%s\n",temp->data);
            }else{
                printf("        文件---%s\n",temp->data);
            }
            temp = temp->Sibling;
        }
        preorderTest(root->lchild); //遍历子树的结点。
        preorderTest(root->Sibling); //遍历兄弟结点的指针
    }
}
//层序遍历整课树，思路在于把当前结点输出，把孩子结点入队
void printAllTree(Cnode *root)
{
    Cnode*queue[MAX_NODE]; //结点数组
    int front,rear; // 队列的首元素和队尾元素

    if(root == NULL) return;//递归的最小条件
    front = -1; rear = 0;
    queue[rear] = root;
    while(front!=rear) 
    {
        front++; //指向第一个元素
        printf("%s  ",queue[front]->data);
        if(queue[front]->lchild!=NULL) 
        {
            Cnode * temp = queue[front]->lchild; //指向的是queue[front] 结点的最左孩子结点
            while(temp!=NULL)
            {
                rear++;
                queue[rear] = temp;//把每个孩子结点入队
                temp = temp->Sibling;
            }
        }
        printf("\n");
    }
}
//给root结点，添加子目录
void addChildItem(Cnode *root,char value[],int type) {
    if(root == NULL) return;
    Cnode *T;
    Cnode *temp;
    if(!(T = (Cnode *)malloc(sizeof(Cnode)))) return;
    strcpy(T->data,value);
    T->type = type;
    T->lchild =NULL;
    T->Sibling =NULL;
    temp = searchfinalchild(root);
    if(temp == NULL) {
        root->lchild = T;
    }else{
        temp->Sibling = T
    }
    return;
}

//给root结点，添加兄弟目录
void addSiblingItem(Cnode *root,char value[],int type) 
{
    if(root==NULL) return;
    Cnode* T;
    Cnode* temp;
    if(!(T= (Cnode *)malloc(sizeof(Cnode)))) return;
    strcpy(T->data,value);
    T->type = type;
    T->lchild =NULL;
    T->Sibling =NULL;
    temp =searchfinalSibling(root);
    if(temp == NULL) {
        root->Sibling = T;
    }else {
        temp->Sibling = T;
    }
}

//查找当前目录下是否有对应的目录或者文件,就是查找当前结点的兄弟结点中是否有对应的文件或目录
//返回NULL 说明没有，找到了，返回path 
Cnode* searchlocalItem(Cnode* node, char value[],char path[]) 
{
    if(node->Sibling==NULL) return -1;
    Cnode *temp =node->Sibling;
    while(temp != NULL) {
        if(strcmp(temp->data,value)==0){
            return 1;
        }
        temp = temp->Sibling;
    }   
    return -1;
}
//从根目录查找是否有对应的目录或文件
//没有找到就返回NULL，找到了就返回PATH
Cnode* searchtillItem(Cnode * root,char value[],char path[]) 
{
    if(root==NULL) return -1;
    int root_data = -1;
    if(strcmp(root->data,value)==0) {
        return 1;
    }
    int lchild = searchtillItem(root->lchild);
    int sibling = searchtillItem(root->Sibling);
    if(lchild == 1 || sibling == 1){
        return 1;
    }else{
        return -1;
    }
}


//查找并删除特定结点 
//参数设置Cnode* node
// value ? 
void deteleItem(Cnode *node)
{
    //如果有孩子树的话,那么就需要
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
//适用于取到最后一个子结点，e.g g h f 取到f
Cnode * searchfinalchild(Cnode *root)
{
    if(root->lchild == NULL) return NULL;
    root = root->lchild;
    while(root!=NULL) {
        if(root->Sibling == NULL) {
            break;
        }
        root = root->Sibling;
    }
    return root;
}

//用于取到当前结点最右的兄弟结点
Cnode * searchfinalSibling(Cnode * root) 
{
    if(root->Sibling == NULL) return NULL;
    root = root->Sibling;
    while(root != NULL) {
        if(root->Sibling == NULL) {
            break;
        } 
        root = root->Sibling;
    }
    return root;
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