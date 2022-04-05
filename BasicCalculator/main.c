#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

/// 操作符栈
Stack op_stack;

/// 操作数栈
Stack num_stack;

/// 表达式的长度
#define EXP_MAXSIZE 128

/// 返回操作符的优先级
int get_priority(char op) {
    switch (op) {
        case '(':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case ')':
            return 3;
        default:
            return -1;
    }
}

/// 计算两个操作数
float calculate(float a, float b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            return 0;
    }
}

/// 中缀表达式转后缀表达式
char *infix_cvt_postfix(char *exp) {
    char *cvt = calloc(EXP_MAXSIZE, sizeof(char));
    char *ptr = cvt;
    stack_init(&op_stack);
    char *ch;
    while (*exp != '\0') {
        // 操作数
        if ((*exp >= '0' && *exp <= '9') || *exp == '.') {
            if (*exp == '.') {      // 以小数点开头的，.3前加个0，变成0.3
                *ptr++ = '0';
            }
            do {
                *ptr++ = *exp++;
            } while ((*exp >= '0' && *exp <= '9') || *exp == '.');

            if (*exp == '.') {      // 以小数点结尾的，5.后加个0，变成5.0
                *ptr++ = '0';
            }
            *ptr++ = ' ';       // 数字后面加个空格分隔
            continue;
        }
        // 操作符
        if ((get_priority(*exp) >= 0)) {
            if (*exp == '(') {
                // 左括号直接入栈
                stack_push(&op_stack, (void *) exp);
            } else if (*exp == ')') {
                // 遇到右括号，操作符一直出栈，直到遇到左括号为止
                while (stack_pop(&op_stack, (void **) &ch) && *ch != '(') {
                    *ptr++ = *ch;
                    *ptr++ = ' ';
                }
            } else {
                // 栈中优先级大于当前操作符的出栈
                while (!stack_empty(op_stack)
                       && stack_top(op_stack, (void **) &ch)
                       && get_priority(*ch) >= get_priority(*exp)) {
                    stack_pop(&op_stack, (void **) &ch);
                    *ptr++ = *ch;
                    *ptr++ = ' ';
                }
                // 当前操作符入栈
                stack_push(&op_stack, (void *) exp);
            }
        }
        exp++;
    }
    // 栈中操作符依次出栈至后缀表达式
    while (!stack_empty(op_stack)) {
        stack_pop(&op_stack, (void **) &ch);
        *ptr++ = *ch;
        *ptr++ = ' ';
    }
    return cvt;
}

/// 计算后缀表达式
float calculate_postfix(const char *exp) {
    stack_init(&num_stack);
    float *num = NULL;
    float *a, *b;
    while (*exp != '\0') {
        // 操作数入栈
        if (*exp >= '0' && *exp <= '9') {
            num = malloc(sizeof(float));
            *num = strtod(exp, (char **) &exp);
            stack_push(&num_stack, num);
            continue;
        }
        // 操作符：弹出栈顶两个操作数并计算，然后将计算结果入栈
        if (get_priority(*exp) > 0) {
            stack_pop(&num_stack, (void **) &b);
            stack_pop(&num_stack, (void **) &a);
            num = malloc(sizeof(float));
            *num = calculate(*a, *b, *exp);
            stack_push(&num_stack, num);
            free(a);
            free(b);
        }
        exp++;
    }
    /// 弹出栈中最后一个操作数，作为计算结果返回
    stack_pop(&num_stack, (void **) &num);
    float ans = *num;
    free(num);
    return ans;
}

int main() {
    setbuf(stdout, 0);
    printf("请输入中缀表达式：\n");
    char *infix = malloc(sizeof(char) * EXP_MAXSIZE);
    gets(infix);
    char *cvt = infix_cvt_postfix(infix);
    printf("后缀表达式：\n%s\n", cvt);
    float result = calculate_postfix(cvt);
    printf("计算结果：%.2f\n", result);
    free(infix);
    free(cvt);
    return 0;
}