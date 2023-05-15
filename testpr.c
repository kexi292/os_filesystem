#include <stdio.h>
void create() {
    printf("%s\n","输入一个值");
    // char ch = getchar();
    char ch[10];
    scanf(" %s",ch);
    
         printf("输出这个值%6s\n",ch);
         create();
    
    return ;
}

int main() {
    create();
    return 0;
}