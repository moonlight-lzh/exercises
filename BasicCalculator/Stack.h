#ifndef BASICCALCULATOR_STACK_H
#define BASICCALCULATOR_STACK_H

#include <stdbool.h>
#include <stdlib.h>

/// 栈所能容纳的最大元素数
#define STACK_MAXSIZE 64

/// 栈的结构体
typedef struct Stack_ {
    void *data[STACK_MAXSIZE];        // 无类型指针数组
    int top;                          // 栈顶指针
} Stack;

/// 初始化栈
void stack_init(Stack *stack);

/// 栈空
bool stack_empty(Stack stack);

/// 栈满
bool stack_full(Stack stack);

/// 返回栈顶元素
bool stack_top(Stack stack, void **elem);

/// 元素出栈
bool stack_pop(Stack *stack, void **elem);

/// 元素入栈
void stack_push(Stack *stack, void *data);

#endif //BASICCALCULATOR_STACK_H
