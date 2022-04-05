#include "Stack.h"

/// 栈的初始化
void stack_init(Stack *stack) {
    stack->top = -1;
}

/// 判断栈是否为空
bool stack_empty(Stack stack) {
    return stack.top == -1;
}

/// 判断栈是否已满
bool stack_full(Stack stack) {
    return stack.top == STACK_MAXSIZE - 1;
}

/// 获取栈顶元素
bool stack_top(Stack stack, void **elem) {
    if (stack_empty(stack)) {
        perror("get top exception, stack empty!");
        return false;
    }
    *elem = stack.data[stack.top];
    return true;
}

/// 弹出栈顶元素
bool stack_pop(Stack *stack, void **elem) {
    if (stack_empty(*stack)) {
        perror("pop exception, stack empty!");
        return false;
    }
    *elem = stack->data[stack->top];
    stack->data[stack->top--] = NULL;
    return true;
}

/// 元素压入栈中
void stack_push(Stack *stack, void *data) {
    if (stack_full(*stack)) {
        perror("push exception, stack full!");
        return;
    }
    stack->data[++stack->top] = data;
}