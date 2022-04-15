#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// malloc
#define mal(n, t)((t *) malloc(sizeof(t) * n))

/// 链表结点-学生信息
typedef struct Node {
    char name[32];
    int age;
    int id;
    char sex;
    float score;
    struct Node *next;
} Node;

/// 链表头结点指针
struct Node *list;

/// 初始化链表
void init_list() {
    // 表头节点
    list = mal(1, struct Node);
    list->next = NULL;
}

/// 根绝学生姓名查询结点
Node *find_node_by_name(char *name) {
    for (Node *cur = list; cur->next != NULL; cur = cur->next) {
        if (strcmp(cur->next->name, name) == 0) {
            return cur->next;
        }
    }
    return NULL;
}

/// 根据学生编号查询学生结点
Node *find_node_by_id(int id) {
    for (Node *cur = list; cur->next != NULL; cur = cur->next) {
        if (cur->next->id == id) {
            return cur->next;
        }
    }
    return NULL;
}

/// 根据学生编号删除结点
void delete_node(int id) {
    // 查询待删除学生的前置结点
    Node *pre = NULL;
    for (Node *cur = list; cur->next != NULL; cur = cur->next) {
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
    scanf("%c", &ch);
    if (ch == 'N' || ch == 'n') {
        return;
    }
    // 确认删除
    if (ch == 'Y' || ch == 'y') {
        Node *t = pre->next;
        pre->next = t->next;
        free(t);
        printf("删除成功。\n");
    }
}

/// 销毁链表
void destroy_list() {
    Node *nd;
    for (Node *cur = list; cur != NULL;) {
        nd = cur;
        cur = cur->next;
        free(nd);
    }
}

/// 欢迎
void welcome() {
    printf("```````````````````````````````````````````````````````````\n");
    printf("***********************************************************\n");
    printf("*******************欢迎登录学生信息管理系统*******************\n");
    printf("***********************************************************\n");
    printf("```````````````````````````````````````````````````````````\n\n\n");
}

/// 主菜单
void menu() {
    printf("```````````````````````````````````````````````````````````\n");
    printf("                   学生信息管理系统                          \n");
    printf("                     0-退出系统                             \n");
    printf("                    1-增加学生信息                           \n");
    printf("                    2-修改学生信息                           \n");
    printf("                    3-删除学生信息                           \n");
    printf("                    4-显示学生信息                           \n");
    printf("```````````````````````````````````````````````````````````\n");
}

/// 新增学生信息
void add_student() {
    Node *node = mal(1, Node);
    if (node == NULL) {
        printf("新增失败\n");
        return;
    }
    printf("请输入待新增学生信息：学号 姓名 性别（m/f） 年龄 成绩\n");
    scanf("%d %s %c %d %f", &node->id, node->name, &node->sex, &node->age, &node->score);
    fflush(stdin);
    node->next = list->next;
    list->next = node;
    printf("新增成功\n");
}

/// 修改学生信息
void modify_student() {
    int id;
    printf("请输入需要修改的学生编号：");
    scanf("%d", &id);
    Node *node = find_node_by_id(id);       // 根据输入的学生编号查询学生结点
    if (node == NULL) {
        printf("未录入该学生信息，无法修改！");
        return;
    }
    printf("请输入需要修改的信息：1-姓名，2-性别，3-年龄，4-成绩");
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
            scanf("%c", &node->sex);
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
            printf("未作出任何修改，返回主菜单");
            return;
    }
}

/// 删除学生信息
void delete_student() {
    int id;
    printf("请输入需要删除学生的学号：");
    scanf("%d", &id);
    delete_node(id);        // 删除链表节点
}

/// 显示学生信息
void display_student() {
    printf("请选择查找方式：1-学号，2-姓名");
    int option;
    scanf("%d", &option);
    Node *node = NULL;
    int id;
    char name[32];
    switch (option) {
        case 1:
            printf("请输入需要查询学生的学号：");
            scanf("%d", &id);
            node = find_node_by_id(id);     // 根据学生编号查询学生
            break;
        case 2:
            printf("请输入需要查询学生的姓名：");
            scanf("%s", name);
            node = find_node_by_name(name);     // 根据学生姓名查询学生
            break;
        default:
            return;
    }

    if (node == NULL) {
        printf("未查询到该生信息！");
        return;
    }
    printf("学号：%d 姓名：%s 性别：%c 年龄：%d 成绩：%f\n", node->id, node->name, node->sex, node->age, node->score);
}

/// 主函数
int main() {
    welcome();      // 欢迎
    init_list();    // 初始化链表
    int option;
    do {
        menu();     // 菜单
        scanf("%d", &option);
        switch (option) {
            case 1:
                add_student();      // 新增学生信息
                break;
            case 2:
                modify_student();   // 修改学生信息
                break;
            case 3:
                delete_student();   // 删除学生信息
                break;
            case 4:
                display_student();  // 显示学生信息
                break;
            case 0:
                goto loop_end;      // 退出系统
            default:
                printf("请输入正确的操作指令。\n");
                break;
        }
    } while (1);
    loop_end:
    destroy_list();     // 销毁链表
    return 0;
}
