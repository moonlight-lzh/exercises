#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// 申请内存
#define mal(n, t)((t *) malloc(sizeof(t) * n))

/// 学生节点
typedef struct Node {
    char name[32];              // 姓名
    int age;                    // 年龄
    int id;                     // 学生编号
    char sex[8];                // 性别
    float score;                // 成绩
    struct Node *next;          // 指向下一个学生的指针
} Node;

struct Node *List;              // 链表头结点

/// 初始化链表
void init_list() {
    List = mal(1, struct Node);
    List->next = NULL;
}

/// 头插法插入新结点
void insert_node(Node *node) {
    node->next = List->next;
    List->next = node;
}

/// 根据姓名查找结点
Node *find_node_by_name(char *name) {
    for (Node *cur = List; cur->next != NULL; cur = cur->next) {
        if (strcmp(cur->next->name, name) == 0) {
            return cur->next;
        }
    }
    return NULL;
}

/// 根据学生编号查找结点
Node *find_node_by_id(int id) {
    for (Node *cur = List; cur->next != NULL; cur = cur->next) {
        if (cur->next->id == id) {
            return cur->next;
        }
    }
    return NULL;
}

/// 根据学生编号删除结点
void delete_node(int id) {
    Node *pre = NULL;
    for (Node *cur = List; cur->next != NULL; cur = cur->next) {
        if (cur->next->id == id) {
            pre = cur;
            break;
        }
    }
    if (pre == NULL) {
        printf("未查找到该学生信息，无法删除。\n");
        return;
    }
    char ch;
    printf("是否删除该生信息？（y/n）:");
    getchar();            // 吸收回车
    ch = getchar();
    if (ch == 'N' || ch == 'n') {
        return;
    }

    if (ch == 'Y' || ch == 'y') {
        Node *t = pre->next;
        pre->next = t->next;
        free(t);
        printf("删除成功。\n");
    }
}

/// 欢迎界面
void welcome() {
    printf("\n```````````````````````````````````````````````````````````\n");
    printf("*************************************************************\n");
    printf("****************** 欢迎登录学生信息管理系统 ******************\n");
    printf("**************************************************************\n");
    printf("``````````````````````````````````````````````````````````````\n");
}

/// 主菜单
void menu() {
    printf("\n````````````````````````````````````````````````````````````\n");
    printf("                  学 生 信 息 管 理 系 统                     \n\n");
    printf("                     1 - 增加学生信息                          \n");
    printf("                     2 - 修改学生信息                          \n");
    printf("                     3 - 删除学生信息                          \n");
    printf("                     4 - 显示学生信息                          \n");
    printf("                     5 - 显示所有学生信息                      \n");
    printf("                     0 - 退出系统                              \n");
    printf("```````````````````````````````````````````````````````````````\n");
}

/// 新增学生信息
void add_student() {
    Node *node = mal(1, Node);
    if (node == NULL) {
        printf("新增失败\n");
        return;
    }
    printf("请输入待新增学生信息：学号 姓名 性别 年龄 成绩\n");
    scanf("%d %s %s %d %f", &node->id, node->name, node->sex, &node->age, &node->score);
    node->next = List->next;
    List->next = node;
    printf("新增成功\n");
}

/// 删除学生信息
void delete_student() {
    int id;
    printf("请输入需要删除学生的学号：");
    scanf("%d", &id);
    delete_node(id);
}

/// 展示所有学生信息
void display_all_student() {
    if (List->next == NULL) {
        printf("学生信息为空！\n");
        return;
    }
    printf("````````````````````````````````````````````````````\n");
    printf("学号\t姓名\t性别\t年龄\t成绩\t\n");
    for (Node *cur = List->next; cur != NULL; cur = cur->next) {
        printf("%d\t%s\t%s\t%d\t%.2f\n", cur->id, cur->name, cur->sex, cur->age, cur->score);
    }
    printf("````````````````````````````````````````````````````\n");
}

/// 修改学生信息
void modify_student() {
    int id;
    printf("请输入需要修改的学生编号：");
    scanf("%d", &id);
    Node *node = find_node_by_id(id);
    if (node == NULL) {
        printf("未录入该学生信息，无法修改！");
        return;
    }
    printf("请输入需要修改的信息：1-姓名，2-性别，3-年龄，4-成绩：");
    int option;
    scanf("%d", &option);
    switch (option) {
        case 1:
            printf("请输入修改后的姓名:");
            scanf("%s", node->name);
            printf("修改成功。");
            break;
        case 2:
            printf("请输入修改后的性别:");
            scanf("%s", node->sex);
            printf("修改成功。");
            break;
        case 3:
            printf("请输入修改后的年龄:");
            scanf("%d", &node->age);
            printf("修改成功。");
            break;
        case 4:
            printf("请输入修改后的成绩:");
            scanf("%f", &node->score);
            printf("修改成功。");
            break;
        default:
            printf("未作出任何修改，返回主菜单。");
            return;
    }
}

/// 展示某个学生信息
void display_student() {
    printf("请选择查找方式：1-学号，2-姓名：");
    int option;
    scanf("%d", &option);
    Node *node = NULL;
    int id;
    char name[32];
    switch (option) {
        case 1:
            printf("请输入需要查询学生的学号：");
            scanf("%d", &id);
            node = find_node_by_id(id);
            break;
        case 2:
            printf("请输入需要查询学生的姓名：");
            scanf("%s", name);
            node = find_node_by_name(name);
            break;
        default:
            return;
    }

    if (node == NULL) {
        printf("未查询到该生信息！");
        return;
    }
    printf("学号：%d 姓名：%s 性别：%s 年龄：%d 成绩：%.2f\n", node->id, node->name, node->sex, node->age, node->score);
}

int main() {
    welcome();
    init_list();                            // 初始化链表
    int option;
    do {
        menu();                             // 主菜单
        fflush(stdin);                      // 清空输入缓冲区
        scanf("%d", &option);
        switch (option) {
            case 1:
                add_student();              // 新增学生信息
                break;
            case 2:
                modify_student();           // 修改学生信息
                break;
            case 3:
                delete_student();           // 删除学生信息
                break;
            case 4:
                display_student();          // 查询展示学生信息
                break;
            case 5:
                display_all_student();      // 展示所有学生信息
                break;
            case 0:                         // 退出系统
                break;
            default:
                printf("请输入正确的操作指令。\n");
                break;
        }
    } while (option);
    return 0;
}
