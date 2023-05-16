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

//树
Cnode * Tree;

//创建树
Cnode* CreateTree()
{
    datatype ch[MAX_SIZE];
    int type = 0;
    char y;
    Cnode *T;
    printf("%s\n","请输入结点值,#代表空");
    scanf("%s %c",ch,&y);getchar();
    if(y == 'y' || y == 'Y') {
        printf("创建文件\n");
        type = 1;
    }
    if(strcmp(ch,"#") == 0) {
        T = NULL;
    }else {
        if( !(T=(Cnode *)malloc(sizeof(Cnode)))) return NULL;  
        strcpy(T->data,ch);
        T->type = type;
        if(type == 1) {
            //是文件，那么直接就把孩子树赋值为NULL
            printf("是文件，无孩子树\n");
            T->lchild = NULL;
        }else {
            printf("创建%s的孩子树\n",ch);
            T->lchild = CreateTree();    //生成最左子树的根结点;
        }
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
        printf(" %s\n",root->data);
        Cnode * temp = root->lchild;
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
//适用于取到最后一个子结点，e.g g h f 取到f
Cnode * searchfinalchild(Cnode *root)
{
    if(root == NULL) return NULL;
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
    if(root == NULL) return NULL;
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
        temp->Sibling = T;
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
int searchlocalItem(Cnode* node, char value[],int type) 
{
    //先清空
    if(node == NULL ) return -1;
    if(strcmp(node->data,value)==0 && node->type == type) {
        return 1;
    }
    int lc = searchlocalItem(node->lchild,value,type);
    int si = searchlocalItem(node->Sibling,value,type);
    if(lc == 1 || si == 1) {
        return 1;
    }else {
        return -1;
    }
}
//检查兄弟结点中是否存在结点
int searchissib(Cnode* node,char value[],int type) 
{
    if(node ==NULL) return -1;
    if(strcmp(node->data,value)==0 && node->type == type) {
        return 1;
    }
    return searchissib(node->Sibling,value,type);
    
}
//从根目录查找是否有对应的目录或文件
//没有找到就返回NULL，找到了就返回PATH
//value[] 要查找的字符串，path[] 找到后的路径存放在这里， ispath 是否要合并路径 y -> 1  N -> 0
Cnode* searchtillItem(Cnode * root,char value[],int type,char path[],int ispath) 
{
    if(root==NULL) return NULL;
    if(strcmp(root->data,value) == 0 && root->type == type) {
        strcat(path,"/"); 
        strcat(path,root->data); 
        return root;
    }else {
        if( searchissib(root,value,type)!=1 && searchlocalItem(root,value,type)) {
            //查找到了是在孩子树中
            strcat(path,"/");
            //添加当前目录
            strcat(path,root->data);
        }
    }
    
    //先查兄弟结点
    Cnode* si = searchtillItem(root->Sibling,value,type,path,ispath);
    if(si!=NULL) return si;
    // if(si!=NULL) {
    //     if(ispath) { 
    //         strcat(path,"/"); 
    //         strcat(path,si->data); 
    //     }
    //     return si;
    // }
    Cnode* lc = searchtillItem(root->lchild,value,type,path,ispath);
    if(lc !=NULL) return lc;
    // if(lc != NULL) {
    //     if(ispath) { 
            
    //         strcat(path,"/");
    //         strcat(path,lc->data);
    //     }
    //     return lc;
    // } 
    return NULL;
    
}

//从根目录处开始查找，但是返回的不是目标结点，而是前序遍历来说的目标结点的前一个结点
Cnode* searchPreTill(Cnode*root,char value[],int type) {
    if(root == NULL) return NULL;
    if(root->lchild!=NULL && root->lchild->type == type && strcmp(root->lchild->data,value) == 0 ) 
    {
        printf("找到了%s的前驱%s\n",value,root->data);
        return root;
    }else if (root->Sibling !=NULL && root->Sibling->type == type && strcmp(root->Sibling->data,value) == 0) 
    {
        printf("找到了%s的前驱%s\n",value,root->data);
        return root;
    }
    Cnode * temp = searchPreTill(root->lchild,value,type);
    Cnode* temp2 = searchPreTill(root->Sibling,value,type);
    if(temp!=NULL) {
        return temp;
    }else if(temp2!=NULL) {
        return temp2;
    }
    return NULL;
}


//查找并删除特定结点
//type 1 是文件，type 0 是目录 
void deteleItem(Cnode *root,char value[],int type)
{
    //从根目录开始找目录或者文件
    //考虑删除目录为空和文件，则直接删除，并维护兄弟链不断开
    //考虑目录非空，则维护兄弟链不断开
    //对于孩子树中的结点，询问是否将以下内容全部删除 Y/N 
    //Y 使用delete 
    //N 则是递归处理（先处理兄弟，再处理孩子，最后处理自己）

    if(root==NULL) return;
    //search Node where Node->lchild->data is value or Node->Sibling->data is value 
    Cnode* temp = searchPreTill(root,value,type);
    // Cnode * temp = NULL;
    if( temp != NULL ) {
        Cnode * cur = NULL;
        if(temp->lchild!=NULL && temp->lchild->type ==type && strcmp(temp->lchild->data,value) == 0) {
            cur = temp->lchild;
            //cur就是目前要删除的结点，temp结点就是前序遍历的前一个结点，此处temp=>lchild = cur
            temp->lchild= cur->Sibling; //把兄弟结点链接到lchild上
            Cnode * finalSibling = searchfinalSibling(cur->Sibling);
            if(finalSibling == NULL) {
                //cur 就是temp唯一的子节点
                temp->lchild = cur->lchild;
            }else {
                //把当前结点的子树全部改为temp的子节点
                finalSibling->Sibling = cur->lchild;
            }
            printf("释放%s的内存空间\n",cur->data);
            free(cur);
        }
        if(temp->Sibling!=NULL && temp->Sibling->type == type && strcmp(temp->Sibling->data,value) == 0) {
            cur = temp->Sibling;
            //cur   temp是cur的兄弟结点
            temp->Sibling = cur->Sibling;
            Cnode * finalSibling = searchfinalSibling(cur->Sibling);
            if(finalSibling==NULL) {
                //cur 就是temp 之后唯一的兄弟结点
                //把cur的孩子树连到原先的链尾
                temp->Sibling = cur->lchild;
            }else{
                //把cur的孩子树全部连成原先的兄弟结点
                finalSibling->Sibling = cur->lchild;
            }
            printf("释放%s的内存空间\n",cur->data);
            free(cur);
        }
    }else {
        printf("没有对应的文件或目录,请检查type是否错误\n");
        return;
    }

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
        printf("释放%s的内存空间\n",root->data);
        free(root);
    }
}



int main() {
    printf("%s\n","---------创建目录----------");
    //搭建目录
    Tree = CreateTree();

    printf("-----------打印所有目录-----------------\n");
    preorderTest(Tree);
    while(1) {
        printf("进入测试:\n 输入 mkdir 创建文件或目录\n 输入 cd 跳转到对应目录中去\n 输入 rm 删除对应目录或文件\n 输入 quit 结束测试\n");
        char com[MAX_NODE];
        char path[MAX_NODE];
        memset(path,'\0',sizeof(path));
        scanf("%s",com);
        if(strcmp(com,"mkdir") == 0) {
            char argscd[MAX_NODE];
            char argsmkdir[MAX_NODE];
            memset(path,'\0',sizeof(path));
            int type;
            char ch;
            printf("---------创建文件或目录----------\n");
            printf("现在在根目录位置,请跳转到所以需目录处\n");
            Cnode * cur;
            do {
                printf("%s\n","请输入指定参数, name  ");
                scanf("%s",argscd);
                cur = searchtillItem(Tree,argscd,0,path,1);
            }while(cur == NULL);
            printf("当前路径为: %s\n",path);
            printf("请输入指定参数 name type\n");
            printf("help -- type 1 是文件  0 是目录\n");
            scanf("%s %d",argsmkdir,&type);
            printf("创建为兄弟目录或文件 Y/N ? \n");
            scanf(" %c",&ch);
            if(ch == 'Y' || ch == 'y') {
                addSiblingItem(cur,argsmkdir,type);
            }else {
                addChildItem(cur,argsmkdir,type);
            }
            printf("-----------打印所有目录-----------------\n");
            preorderTest(Tree);

        }else if( strcmp(com,"cd") == 0) {
            printf("%s\n","---------跳转到对应的目录中去-------");
            printf("%s\n","请输入指定参数, name type");
            printf("%s\n","type --help  1 为文件 0 为目录");
            char argscd[MAX_NODE]; 
            int type = 0;
            memset(path,'\0',sizeof(path));
            Cnode * cur;
            do {
                printf("%s\n","请输入指定参数, name type");
                scanf("%s %d",argscd,&type);
                cur = searchtillItem(Tree,argscd,type,path,1);
            }while(cur == NULL);
            printf("路径为: %s\n",path);
            printf("-----------当前目录--------------------\n");
            preorderTest(cur);
            printf("-----------打印所有目录 -----------------\n");
            preorderTest(Tree);

        }else if( strcmp(com,"rm") == 0) {
            printf("-----------删除对应文件或目录-----------\n");
            printf("请输入指定参数, name type\n");
            printf("%s\n","type --help  1 为文件 0 为目录");
            char argsrm[MAX_NODE];
            int type;
            scanf("%s %d",argsrm,&type);
            deteleItem(Tree,argsrm,type);
            printf("------------打印所有目录-----------------\n");
            preorderTest(Tree);
        }else if( strcmp(com,"quit") == 0) {
            break;
        }else {
            printf("输入错误指令 请检查大小写\n");
        }
        
    }

    printf("%s\n","----------释放空间---------");
    //释放空间
    deleteTree(Tree);
    return 0;
}