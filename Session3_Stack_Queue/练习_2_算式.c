#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef int Elemtype;
#include "3.3.3_链栈.h"

/**
 * 运行配置：Calculator
 * 练习：使用栈进行表达式的求值
 * 对于形如 13+3*2-5*(6-17+1*2)-6这样的式子，从前往后入栈
 *
 * - 数字：入数字栈
 * - 字符：和字符栈顶作比较
 *      - 优先级更高：入栈
 *      - 优先级相同或低：出栈，进行运算
 *      - 括号：左括号入栈，右括号出栈运算，直到左括号出栈
 * - 运算方法：数字栈出栈，结果入栈
 *
 * wswsl23 2024.06.23
 */

void Print(LinkStack Num,LinkStack Fun){
    LinkStack tmp=Num;
    while (tmp){
        printf("%d ",tmp->data);
        tmp=tmp->next;
    }
    printf("\n");

    tmp=Fun;
    while (tmp){
        printf("%c ",tmp->data);
        tmp=tmp->next;
    }
    printf("\n\n");
}

// 字符串转换为数字
int ToNum(char *n){
    int num = 0,length=strlen(n);
    for(int i=0;i<length;i++){
        num+=(n[i]-48)*pow(10,length-i-1);
    }
    return num;
}

int Calcul(int fun,int n1,int n2){
    // num2 fun num1
    switch (fun) {
        case '+':return n1+n2;
        case '-':return n2-n1;
        case '*':return n1*n2;
        case '/':return n2/n1; // 这里应该做除零判断，我懒得写
    }
}

int Calculation(char s[]){
    int n= strlen(s);
    char num[10];
    int index = 0;
    int num1,num2,tmp;

    // 初始化两个栈
    LinkStack Num,Fun;
    InitStack(&Num);
    InitStack(&Fun);

    // 分析式子
    for(int i=0;i<n;i++){
        // 判断是数字还是字母
        if ('0'<s[i] && s[i]<'9')
            num[index++]=s[i];
        else{
            if (index!=0){
                num[index] = '\0';
                Push(&Num,ToNum(num)); // 数字入栈
                index=0;
            }

            // 左括号 栈空：直接入栈
            if (s[i]=='(' || s[i]=='[' || ListEmpty(Fun))
                Push(&Fun,s[i]);
            // * /: 比较栈顶
            else if(s[i]=='*' || s[i]=='/'){
                tmp=GetTop(Fun);
                while (!ListEmpty(Fun) && tmp!='+' && tmp!='-') // 到栈空或乘除
                {
                    Pop(&Num,&num1);
                    Pop(&Num,&num2);
                    Pop(&Fun,&tmp);
                    Push(&Num,Calcul(tmp,num1,num2)); // 运算结果入栈
                    tmp=GetTop(Fun);
                }
                Push(&Fun,s[i]); // 入栈
            }
            //+ - 右括号：出栈直到左括号或栈空
            else {
                tmp = GetTop(Fun);
                while (!ListEmpty(Fun) && (tmp!='(' && tmp!='[')){
                    Pop(&Fun,&tmp);
                    Pop(&Num,&num1);
                    Pop(&Num,&num2);
                    Push(&Num,Calcul(tmp,num1,num2)); // 运算结果入栈
                    tmp = GetTop(Fun);
                }
                if (s[i]=='+' || s[i]=='-')
                    Push(&Fun,s[i]);
                else
                    Pop(&Fun,&tmp);
            }
        }

    }

    num[index] = '\0';
    Push(&Num,ToNum(num)); // 最后一个数字入栈

    // 如果还有运算符，持续出栈到空
    while (!ListEmpty(Fun)){
        Pop(&Num,&num1);
        Pop(&Num,&num2);
        Pop(&Fun,&tmp);
        Push(&Num,Calcul(tmp,num1,num2)); // 运算结果入栈
    }

    return GetTop(Num);
}

void main(){
    char s[] = "13+3*2-5*(6-17+1*2)-6";
    assert(Calculation(s)==58);
}


