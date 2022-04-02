#include <stdio.h>
#include <string.h>
#include "LinkQueue.h"

struct LinkQueue Q;         // 队列

int window_number;          // 当前窗口号

int business_count[4] = {0};        // 每种业务的叫号人数

#define USER "admin"        // 登录用户名
#define PSWD "1"            // 登录密码

/// 欢迎
void welcome() {
    printf("****************************************************************\n");
    printf("*                     欢迎进入银行排队叫号系统                   *\n");
    printf("****************************************************************\n");
}

/// 登录
void login() {
    printf("------------------------------登 录------------------------------\n");

    int login = 0;
    int times = 0;      // 登录次数
    char username[10], password[10];
    do {
        printf("请输入用户名：");
        scanf("%s", username);
        printf("请输入密码：");
        scanf("%s", password);
        times++;
        if (strcmp(username, USER) == 0 && strcmp(password, PSWD) == 0) {
            login = 1;
        } else if (3 - times > 0) {
            printf("输入用户名或密码错误，请重新输入，您还有%d次机会。\n", 3 - times);
        }
    } while (times < 3 && login == 0);      // 3次登录机会

    if (login) {
        printf("登录成功，请输入当前窗口号：\n");
        scanf("%d", &window_number);
        printf("即将进入系统，请稍候...\n");
    } else {
        printf("登录失败，系统即将退出...\n");
        exit(1);
    }
    printf("-----------------------------------------------------------------\n");
}

/// 主菜单
void main_menu() {
    printf("****************************************************************\n");
    printf("*                         银行排队叫号系统                       *\n");
    printf("*                                                              *\n");
    printf("*                           1 - 取 号                          *\n");
    printf("*                           2 - 叫 号                          *\n");
    printf("*                           3 - 信息展示                        *\n");
    printf("*                           0 - 退出系统                        *\n");
    printf("****************************************************************\n");
}

/// 取号
void take_number() {
    printf("------------------------------取 号------------------------------\n");
    struct Data *data = NEW_DATA();
    if (data == NULL) {
        printf("取号失败：内存分配异常！\n");
        printf("-----------------------------------------------------------------\n");
        return;
    }
    printf("请输入姓名：\n");
    scanf("%s", data->name);
    printf("请选择业务类型（0-个人业务 1-公司业务 2-综合业务 3-优先业务）：\n");
    scanf("%d", &data->businessType);
    data->number = ++business_count[data->businessType];
    printf("您取到的号码为：%d\n", data->number);
    LinkQueue_EnQueue(&Q, data);
    printf("取号成功！\n");
    printf("-----------------------------------------------------------------\n");
}

/// 优先业务出队
void dequeue_priority(struct LinkQueue *queue, struct Data **x) {
    struct LinkNode *find = NULL;
    for (struct LinkNode *prev = Q.front; prev != NULL && prev->next != NULL; prev = prev->next) {
        if (prev->next->data->businessType == Priority) {
            find = prev->next;
            prev->next = prev->next->next;
            *x = find->data;
            break;
        }
    }
    LinkQueue_RemoveNode(queue, find);      // 从队列中删除出队结点
}

/// 根据业务类型返回业务名称
void get_business_name(enum BusinessType type, char *s) {
    switch (type) {
        case Personal:
            strcpy(s, "个人业务");
            break;
        case Corporate:
            strcpy(s, "公司业务");
            break;
        case Integrated:
            strcpy(s, "综合业务");
            break;
        case Priority:
            strcpy(s, "优先业务");
            break;
        default:
            break;
    }
}

/// 叫号
void call_number() {
    printf("------------------------------叫 号------------------------------\n");
    if (LinkQueue_IsEmpty(Q)) {
        printf("当前队列为空，无法叫号。\n");
        printf("-----------------------------------------------------------------\n");
        return;
    }
    struct Data *data = NULL;
    if (business_count[Priority] > 0) {
        // 先叫号优先业务
        dequeue_priority(&Q, &data);
    } else {
        // 其他类型业务出队
        LinkQueue_DeQueue(&Q, &data);
    }
    if (data == NULL) {
        printf("叫号失败！\n");
        return;
    }
    business_count[data->businessType]--;       // 对应业务类型人数减1
    printf("叫号成功！\n");
    char name[20];
    get_business_name(data->businessType, name);     // 获取业务类型名称
    printf("请 %03d号 %s 到 %d 号窗口办理%s!\n", data->number, data->name, window_number, name);
    printf("-------------------------------------------------------------------\n");
    free(data);
}

/// 信息展示
void show_numbers() {
    printf("------------------------------信息展示------------------------------\n");
    printf("个人业务等待人数：%d\n", business_count[Personal]);
    printf("公司业务等待人数：%d\n", business_count[Corporate]);
    printf("综合业务等待人数：%d\n", business_count[Integrated]);
    printf("优先业务等待人数：%d\n", business_count[Priority]);
    printf("-------------------------------------------------------------------\n");
}

/// 主函数
int main() {
    setbuf(stdout, NULL);       // 清空输入缓存

    LinkQueue_Init(&Q);         // 队列初始化

    welcome();                  // 欢迎

    login();                 // 登录

    int option = 0;
    do {
        main_menu();                         // 主菜单
        scanf("%d", &option);       // 输入操作选项
        fflush(stdout);
        switch (option) {
            case 1:
                take_number();          // 取号
                break;
            case 2:
                call_number();          // 叫号
                break;
            case 3:
                show_numbers();         // 信息展示
                break;
            case 0:
                goto loop_end;          // 退出系统
            default:
                printf("输入指令异常！\n");
                break;
        }
    } while (option);
    loop_end:
    return 0;
}
