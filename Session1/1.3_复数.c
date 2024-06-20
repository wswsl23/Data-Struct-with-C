#include <stdio.h>
#include <assert.h>

/**
 * 运行配置：complex_num
 * 复数的加减乘除
 * wswsl23 2024.06.20
 */

typedef struct Complex{
    float real_part;
    float imag_part;
};

// 以下函数都应该做溢出检测，但是我没做

// 复数赋值
void Complex_assign(struct Complex *A,float real,float imag){
    A->real_part=real;
    A->imag_part=imag;
}

// 复数求和 C = A+B
void Complex_add(struct Complex *C,struct Complex A,struct Complex B){
    C->real_part = A.real_part+B.real_part;
    C->imag_part = A.imag_part+B.imag_part;
}

// 复数求差 C = A-B
void Complex_sub(struct Complex *C,struct Complex A,struct Complex B){
    C->real_part = A.real_part-B.real_part;
    C->imag_part = A.imag_part-B.imag_part;
}

// 复数求积 C = A*B
void Complex_mul(struct Complex *C,struct Complex A,struct Complex B){
    C->real_part = A.real_part*B.real_part - A.imag_part*B.imag_part;
    C->imag_part = A.imag_part*B.real_part + A.real_part*B.imag_part;
}

// 复数求商 C = A/B
void Complex_div(struct Complex *C,struct Complex A,struct Complex B){
    float tmp=0;
    tmp = B.real_part*B.real_part + B.imag_part*B.imag_part;
    if(tmp==0){
        printf("Complex_div 错误：除零错误");
    }
    C->real_part = (A.real_part*B.real_part + A.imag_part*B.imag_part)/tmp;
    C->imag_part = (A.imag_part*B.real_part - A.real_part*B.imag_part)/tmp;
}

void test(){
    // z=((8+6i)(4+3i)) / ((8+6i)+(4+3i))
    struct Complex A,B,mul,add,result;
    Complex_assign(&A,8.,6.);
    Complex_assign(&B,4.,3.);
    Complex_mul(&mul,A,B);
    Complex_add(&add,A,B);
    Complex_div(&result,mul,add);
    assert(result.real_part-2.666667<0.01 && result.imag_part-2.<0.01);

    // (8+6i)-(4+3i)
    Complex_sub(&result,A,B);
    assert(result.real_part-4.<0.01 && result.imag_part-3.<0.01);
}

int main(void) {
    test();
    return 0;
}


