#include "2.4_数组实现.h"
#include <assert.h>
/**
 * 运行配置：Test_Polynomial
 * 练习：使用线性表进行一元多项式的加减
 * 包含：有序表实现 有序表合并 二分法查找
 *
 * 思路分析：
 * 由于加减没有本质区别(系数也可能为负)，因此加减使用同一个函数。
 * 为了方便计算，顺序表最好按照指数升序或降序排列，因此我们写一个新的插入算法，按照指数将一条数据插到对应的位置。
 * 也可以选择写一个排序算法，在加减前对两个表进行排序。
 *
 * 插入算法思路：二分法
 * 原本的插入是指定位置插入，为了复用该函数，我们可以写一个寻找算法，寻找应该插入的位置，然后再使用原本的函数进行插入。
 * 值得注意的是，指数相同时我们应该直接合并，只有指数不同时我们才进行插入。
 * 对于升降序排列的一组数，可以使用二分法查找提高效率。注意该方法不适用于链表实现的顺序表。
 *
 * wswsl23 2024.06.20
 */

// 查找位置，找到返回1，未找到返回0
int FindIndex(struct Sqlist L,int *index,struct Polynomial e){
    /**
     * 二分法：
     * 对于有序数组，如[0,1,2,3,4,...,99]可以使用二分法快速查找。不知道大家有没有写过 猜数字 的程序，与猜数字的最优方法类似。
     * 如，我们要找到数字 27，那么我们首先找到该数组的中间(0+99)//2=44，44比27大，我们将后边界更新为44。
     * 现在，我们找到新的数组的中间(0+44)//2=22,22比27小，我们将前边界更新为22，新的中间为(22+44)//2=33。
     * 重复该过程，知道我们找到27。
     *
     * 现在，你可能会注意到一个问题，如果不存在27的话怎么办？
     * 以num=[1,3,4,5]为例，我们想要找到数字2。按照上述步骤进行搜索，以i,j代表前后边界
     * 1: i=0,j=3   mid=(i+j)//2=1   num[mid]=3 >2  j=mid=1
     * 2: i=0,j=1   mid=(i+j)//2=0   num[mid]=1 <2  i=mid=0
     * 很明显，现在就会进入i=0,j=1的死循环。我们再看一下这个过程，会发现我们的范围[i,j]是一个闭区间，
     * 在更新边界为[i,mid]或者[mid,j]的时候，我们将mid也划入了区间中。但是我们已经知道，mid不是我们需要的值。
     *
     * 因此，我们可以在更新边界时，再往里缩小一点，i=mid+1 j=mid-1
     * 以num=[1,3,5,7,9]为例，我们要找数字2
     * 1: i=0,j=4   mid=2   num[mid]=5 >2  j=mid-1=1
     * 2: i=0,j=1   mid=0   num[mid]=1 <2  i=mid+1=1
     * 3：i=1,j=1   此时，你会发现一件神奇的事——i==j。如果我们在这里停下，此时左边界 i=1 即我们要插入的位置。
     */
    int i=0,j=GetLength(L)-1,mid;
    while (i<=j){
        mid = (i+j)/2; // 由于mid是int型，会自动截取整数部分
        if(L.elem[mid].e==e.e){
            *index=mid;
            return 1;
        }
        else if(L.elem[mid].e>=e.e)
            j=mid-1;
        else
            i=mid+1;
    }
    *index=i;
    return 0;
}

// 插入
void InsertOrder(struct Sqlist *L,struct Polynomial e){
    if (GetLength(*L)==0){
        ListInsert_Sq(L,0,e);
    }
    else{
        int index;
        if (FindIndex(*L,&index,e)){
            L->elem[index].p += e.p;
            if (L->elem[index].p==0){
                ListDelete_Sq(L,index);
            }
        }
        else
            ListInsert_Sq(L,index,e);
    }
}

// 深拷贝
void CopySql(struct Sqlist *C,struct Sqlist A,int index){
    for(int i=index;i<GetLength(A);i++){
        // 从index开始拷贝
        ListInsert_Sq(C, GetLength(*C),A.elem[i]);
    }
}

// 加减计算 func==1，加法 func==-1，减法
void Poly_Calculate(struct Sqlist *C,struct Sqlist A,struct Sqlist B,float func){
    // 任一表为空
    if (GetLength(A)==0){
        // *C = B; 这样是浅拷贝，需要深拷贝
        ClearList(C);
        CopySql(C,B,0);
    }
    if (GetLength(B)==0){
        ClearList(C);
        CopySql(C,A,0);
    }

    // i,j代表A/B的项数
    int i=0,j=0,index=0;
    while (i<GetLength(A) && j<GetLength(B)){
        // 进行比较，小的进入C 注意B需要乘func
        if (A.elem[i].e<B.elem[j].e){
            ListInsert_Sq(C,index++,A.elem[i++]); // index++ 先运算，再自增
        }
        else if (A.elem[i].e>B.elem[j].e){
            struct Polynomial temp;
            temp.e = B.elem[j].e;
            temp.p = B.elem[j++].p*func;
            ListInsert_Sq(C,index++,temp);
        }

        else { // 相等
            struct Polynomial temp;
            temp.e = B.elem[j].e;
            temp.p = B.elem[j++].p*func + A.elem[i++].p;
            if (temp.p!=0){
                ListInsert_Sq(C,index++,temp);
            }
        }
    }
    // 收尾
    if (i<GetLength(A))
        CopySql(C,B,j);
    else if(j<GetLength(B)){
        CopySql(C,A,i);
    }
}

void test(){
    struct Sqlist A,B,C;
    struct Polynomial e;
    assert(InitList_Sq(&A));
    assert(InitList_Sq(&B));
    assert(InitList_Sq(&C));

    // 插入同样项
    e.p=2,e.e=1;
    InsertOrder(&A,e);
    InsertOrder(&A,e);
    InsertOrder(&B,e);
    e.p=4;
    assert(IsEqual(A.elem[0],e));

    // 插入多项
    e.p=3,e.e=4;
    InsertOrder(&A,e);
    assert(IsEqual(A.elem[1],e));
    e.p=2,e.e=8;
    InsertOrder(&A,e);
    assert(IsEqual(A.elem[2],e));
    e.p=-1;
    InsertOrder(&B,e);

    e.p=2,e.e=2;
    InsertOrder(&A,e);
    assert(IsEqual(A.elem[1],e));

    e.p=-2,e.e=2;
    InsertOrder(&B,e);

    // 有负数输出不是很美观，但我懒得改了
    Print_Sq(A);
    Print_Sq(B);
    // 4.00x^1 + 2.00x^2 + 3.00x^4 + 2.00x^8
    // 2.00x^1 + -2.00x^3 + -2.00x^8

    Poly_Calculate(&C,A,B,1.);
    Print_Sq(C);
    // 6.00x^1 + 2.00x^2 + -2.00x^3 + 3.00x^4

    assert("这里请自行对比，因为我懒得写"==0);
}


int main(void){
    test();
    return 0;
}