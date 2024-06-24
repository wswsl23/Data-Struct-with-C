#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * 运行配置：KMP
 * KMP的实现
 * 数组从0开始的，不是非常确定结果的正确性，可能有bug存在
 * wswsl23 2024.06.24
 */
void Print(int *nextval,int n){
    for (int i=0;i<n;i++){
        printf("%d ",nextval[i]);
    }
    printf("\n");
}

// 计算nextval
void Get_nextval(char *s,int *nextval){
    int j=0;
    // 长度小于2，直接出结果
    if (strlen(s)<2)
        nextval[0]=0;
    else{
        // 0 1 位固定
        nextval[0]=0,nextval[1]=1;
        // nextval进行替换
        if (s[0]==s[1])
            nextval[1]=0;

        // 计算nextval
        for(int i=2;i<strlen(s);i++){
            // 比较前面字符和第j位是否相同
            if(s[i-1]==s[j]){
                nextval[i]=j+2;
                j++;
            }
            // 如果不同，j回溯
            else{
                if (s[j-1]==s[i-1])
                    j=nextval[j];
                else
                    j=0;
                nextval[i]=j+1;
            }

            // 进行next到nextval的替换
            if (s[nextval[i]-1]==s[i])
                nextval[i]=nextval[nextval[i]-1];
        }
    }
}

// 匹配
int Index_KMP(char *s1,char *s2){
    int i=0,j=0,n1=(int)strlen(s1),n2=(int)strlen(s2);
    int next[n2];
    Get_nextval(s2,next);

    while(i<n1 && j<n2){
        if (j==-1 || s1[i]==s2[j]){
            i++;
            j++;
        }
        else{
            j = next[j]-1;
        }
    }

    if (j>=n2)
        return i-n2;
    return -1;
}

int main(){
    char *s1="aabaabec",*s2="aabe";
    assert(Index_KMP(s1,s2)==3);
    s2="aab";
    assert(Index_KMP(s1,s2)==0);
    return 0;
}
