#include <assert.h>
#include "2.4_数组实现.h"

/**
 * 运行配置：List_order
 * 使用结构体数组实现线性表的顺序存储，以多项式为例
 * wswsl23 2024.06.20
 */

void test(){
    struct Sqlist L;
    assert(InitList_Sq(&L));
    /**
     * 补充：关于对齐
     * 有些编译器有自动对齐的功能，详细可以搜索 C语言字节对齐 自行了解。
     * 尝试下列代码：
     * printf("%llu\t",sizeof(L));
       printf("%llu\t",sizeof(L.elem));
       printf("%llu\n",sizeof(L.length));
     * 结果为： 16      8       4
     * 可见，结构体的大小要大于元素大小的和。实际上，如果修改结构体的结构，再增加一个 int 类型的元素，L的大小仍是16。
     * 对齐会使CPU的效率提高。如果编译器没有自动对齐功能，可以为结构体添加对齐用的元素来提高效率。
     */
    struct Polynomial e,f;
    e.e=1,e.p=2;
    assert(ListInsert_Sq(&L,0,e)); // 线性表空时插入元素
    assert(GetElem(L,0,&f));
    assert(IsEqual(e, f));

    // 插入多个元素
    e.e=2,e.p=3;
    assert(ListInsert_Sq(&L,1,e)); // 最后插入
    e.e=3,e.p=4;
    assert(ListInsert_Sq(&L,1,e)); // 中间插入
    e.e=6,e.p=3;
    assert(ListInsert_Sq(&L,0,e)); // 开头插入

    // 一共插入4个元素
    assert(GetLength(L)==4);

    // 目前表内容：
    // 3x^6 2x^1 4x^3 3x^2
    // Print_Sq(L);

    // 查找并删除元素
    int index;
    index = LocateElem(L,e);
    assert(index==0);
    assert(ListDelete_Sq(&L,index));

    // 清空和释放
    ClearList(&L);
    assert(L.elem);
    DestroyList(&L);
}


int main(void){
    test();
    return 0;
}


