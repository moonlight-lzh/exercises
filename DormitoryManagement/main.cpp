#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/**--------------------------------------- Macros ---------------------------------------*/

#define NEW_NODE() ((Node*)calloc(sizeof(Node), 1))
#define NEW_STUDENT()((Student*)malloc(sizeof(Student)))
#define STU_FILE_NAME "../students.data"
#define NONE_BUILDING '#'

/**--------------------------------------- Macros ---------------------------------------*/

/**--------------------------------------- Structures ---------------------------------------*/

/// 性别枚举
typedef enum SEX {
    BOY, GIRL
} SEX;

/// 学生信息结构体
typedef struct _Student {
    char college[20];       // 学院
    char sclass[20];        // 班级
    int number;             // 学号
    char name[20];          // 姓名
    SEX sex;                // 性别
    char building;          // 宿舍楼号
    int room;               // 宿舍号
    int bed;                // 床位号
    char remarks[128];      // 备注
} Student;

typedef struct _Node {
    Student *student;
    struct _Node *next;
} Node;

Node *list;
int list_size = 0;

/**--------------------------------------- Structures ---------------------------------------*/

/**--------------------------------------- Definitions ---------------------------------------*/

void read_files();

void write_files();

void welcome();

void return_menu();

void main_menu();

void information_entry();

void information_modify();

void information_delete();

void information_view();

void information_query();

void information_sort();

SEX get_sex(const char *sex);

const char *get_sex_name(SEX sex);

void init_list();

void insert_node(Node *new_node);

void delete_node(Node *front_node);

void delete_dormitory(char building, int room);

Node *search_front_node(int stu_number);

Node *search_node_number(int stu_number);

Node *search_node_name(const char *stu_name);

void print_student(Student stu);

bool is_number(const char *str);

int compare_class(const char *cls1, const char *cls2);

/**--------------------------------------- Definitions ---------------------------------------*/

/**--------------------------------------- Main Function ---------------------------------------*/
int main() {
    setbuf(stdout, 0);

    system("color 70");

    init_list();

    read_files();

    welcome();
    int option = 0;
    do {
        main_menu();
        rewind(stdin);
        scanf("%d", &option);

        switch (option) {
            case 1:             // 录入
                information_entry();
                break;
            case 2:             // 修改
                information_modify();
                break;
            case 3:             // 删除
                information_delete();
                break;
            case 4:             // 浏览
                information_view();
                break;
            case 5:             // 查询
                information_query();
                break;
            case 6:             // 排序
                information_sort();
                break;
            case 0:             // 退出系统
                printf("系统化即将推出...\n");
                break;
            default:
                printf("输入指令异常。\n");
                break;
        }

    } while (option);
    return 0;
}
/**--------------------------------------- Main Function -------------------------------------*/

/**--------------------------------------- Implements ---------------------------------------*/

/// 欢迎
void welcome() {
    printf("-----------------------------------------------------------------------------\n");
    printf("                            欢迎进入学生宿舍管理系统                           \n");
    printf("-----------------------------------------------------------------------------\n");
    printf("正在进入系统...\n\n");
}

/// 返回主菜单
void return_menu() {
    printf("按任意键返回主菜单...\n");
    rewind(stdin);
    getchar();
}

/// 主菜单
void main_menu() {
    printf("-----------------------------------------------------------------------------\n");
    printf("                             学 生 宿 舍 管 理 系 统                           \n");
    printf("                                                                             \n");
    printf("                                1 - 录入学生信息                               \n");
    printf("                                2 - 修改学生信息                               \n");
    printf("                                3 - 删除学生信息                               \n");
    printf("                                4 - 浏览学生信息                               \n");
    printf("                                5 - 查询学生信息                               \n");
    printf("                                6 - 排序学生信息                               \n");
    printf("                                0 - 退出系统                                   \n");
    printf("------------------------------------------------------------------------------\n");
}

/// 录入
void information_entry() {
    char sex[4], ch;
    Student *stu;
    printf("------------------------------------录 入-------------------------------------\n\n");
    entry_retype:
    stu = NEW_STUDENT();
    printf("请录入学生信息（学院 班级 学号 姓名 性别）：\n");
    rewind(stdin);
    scanf("%s %s %d %s %s", stu->college, stu->sclass, &stu->number, stu->name, sex);

    // 判断输入的学号/姓名是否已经存在
    if (search_node_number(stu->number) || search_node_name(stu->name)) {
        printf("您所输入的信息[姓名：%s 学号：%d]已存在，请重新输入！\n", stu->name, stu->number);
        free(stu);
        rewind(stdin);
        goto entry_retype;
    }

    stu->sex = get_sex(sex);
    stu->building = NONE_BUILDING;
    printf("是否录入宿舍信息？(y / n)：");
    rewind(stdin);
    ch = (char) getchar();
    if (ch == 'y' || ch == 'Y') {
        // 录入宿舍信息
        printf("请输入宿舍信息（楼号 宿舍号 床位号）：\n");
        rewind(stdin);
        scanf("%c %d %d", &stu->building, &stu->room, &stu->bed);
    }
    // 新增结点插入链表
    Node *node = NEW_NODE();
    node->student = stu;
    insert_node(node);
    printf("学生信息录入成功！\n");
    // 保存文件
    write_files();
    return_menu();
    printf("-----------------------------------------------------------------------------\n");
}

// 修改
void information_modify() {
    char str[30], ch, *end;
    int num = 0, option = 0;
    printf("------------------------------------修 改-------------------------------------\n\n");
    modify_retype:
    printf("请输入需要修改的学生姓名或学号：\n");
    rewind(stdin);
    scanf("%s", str);
    Node *node = NULL;
    if (is_number(str)) {
        // 输入的是整数，则按照学号查询
        num = strtol(str, &end, 10);
        node = search_node_number(num);
    } else {
        // 按照姓名查询
        node = search_node_name(str);
    }

    // 查询失败
    if (node == NULL) {
        printf("您所输入的信息不存在！\n");
        printf("是否重新输入？(y / n)：\n");
        rewind(stdin);
        ch = (char) getchar();
        if (ch == 'y' || ch == 'Y') {
            rewind(stdin);
            goto modify_retype;
        } else {
            goto modify_end;
        }
    }

    // 选择查询条件
    printf("请选择：\n");
    printf("1.学院\n");
    printf("2.班级\n");
    printf("3.学号\n");
    printf("4.姓名\n");
    printf("5.性别\n");
    printf("6.楼号\n");
    printf("7.宿舍号\n");
    printf("8.床位号\n");
    printf("9.备注\n");
    printf("0.返回\n");
    rewind(stdin);
    scanf("%d", &option);
    printf("输入修改后的内容：\n");
    rewind(stdin);
    // 将修改后的内容更新到链表结点中
    switch (option) {
        case 1:          // 学院
            scanf("%s", node->student->college);
            break;
        case 2:         // 班级
            scanf("%s", node->student->sclass);
            break;
        case 3:         // 学号
        case3:
            scanf("%d", &num);
            if (search_node_number(num)) {
                printf("您所输入的学号[%d]已存在，请重新输入！\n", num);
                rewind(stdin);
                goto case3;
            }
            node->student->number = num;
            break;
        case 4:         // 姓名
        case4:
            scanf("%s", str);
            if (search_node_name(str)) {
                printf("您所输入的学生姓名[%s]已存在，请重新输入！\n", str);
                rewind(stdin);
                goto case4;
            }
            strcpy(node->student->name, str);
            break;
        case 5:         // 性别
            scanf("%s", str);
            node->student->sex = get_sex(str);
            break;
        case 6:         // 楼号
            scanf("%c", &node->student->building);
            break;
        case 7:         // 宿舍号
            scanf("%d", &node->student->room);
            break;
        case 8:         // 床位号
            scanf("%d", &node->student->bed);
            break;
        case 9:         // 备注
            scanf("%s", node->student->remarks);
            break;
        case 0:         // 返回
            goto modify_end;
    }
    printf("信息修改成功！");
    // 保存文件
    write_files();
    modify_end:
    return_menu();
    printf("-----------------------------------------------------------------------------\n");
}

/// 删除
void information_delete() {
    int option, num, room;
    char building;
    Node *front_node;
    printf("------------------------------------删 除------------------------------------\n\n");
    printf("请选择：\n");
    printf("1.删除学生信息\n");
    printf("2.删除宿舍信息\n");
    printf("0.返回\n");
    delete_retype:
    rewind(stdin);
    scanf("%d", &option);
    rewind(stdin);
    switch (option) {
        case 1:
            printf("请输入需要删除学生的学号：");
            scanf("%d", &num);
            // 根据输入的学号查询前置结点
            front_node = search_front_node(num);
            if (front_node == NULL) {
                printf("该生不存在，无法删除！\n");
            } else {
                delete_node(front_node);
                printf("学生信息删除成功！\n");
                write_files();
            }
            break;
        case 2:
            // 根据输入的宿舍信息，清空该宿舍下学生的宿舍信息
            printf("请输入需要删除的宿舍：（楼号 宿舍号）\n");
            scanf("%c %d", &building, &room);
            delete_dormitory(building, room);
            printf("宿舍信息删除成功！\n");
            write_files();
            break;
        case 0:
            goto delete_end;
        default:
            printf("无效指令，请重新输入");
            rewind(stdin);
            goto delete_retype;
    }
    delete_end:
    return_menu();
    printf("-----------------------------------------------------------------------------\n");
}

/// 打印学生信息
void print_student(Student stu) {
    // 打印输出一行学生信息
    printf("%-14s %-16s %-12d %-8s %-4s %-4c ", stu.college, stu.sclass, stu.number, stu.name, get_sex_name(stu.sex),
           stu.building);
    if (stu.building != NONE_BUILDING) {
        printf("%-4d %-4d ", stu.room, stu.bed);
    } else {
        printf("%-8c", ' ');
    }
    printf("%s\n", stu.remarks);
}

/// 浏览
void information_view() {
    printf("------------------------------------浏 览------------------------------------\n\n");
    for (Node *cur = list; cur && cur->next; cur = cur->next) {
        print_student(*cur->next->student);
    }
    printf("-----------------------------------------------------------------------------\n");
}

/// 查询
void information_query() {
    bool found;
    char condition[50], *end;
    int option = 0, num = 0, count = 0;
    printf("------------------------------------查 询-------------------------------------\n\n");

    // 选择查询条件
    printf("请选择查询条件：\n");
    printf("1.学院\n");
    printf("2.班级\n");
    printf("3.学号\n");
    printf("4.姓名\n");
    printf("5.性别\n");
    printf("6.楼号\n");
    printf("7.宿舍号\n");
    printf("0.返回\n");

    scanf("%d", &option);
    if (option <= 0 || option > 7) {
        goto query_end;
    }
    rewind(stdin);
    scanf("%s", condition);
    if (is_number(condition)) {
        // 输入的数字则提前转为整型
        num = strtol(condition, &end, 10);
    }

    for (Node *current = list->next; current; current = current->next) {        // 循环链表中的所有结点
        found = false;
        switch (option) {           // 根据输入的条件判断
            case 1:
                found = strcmp(current->student->college, condition) == 0;
                break;
            case 2:
                found = strcmp(current->student->sclass, condition) == 0;
                break;
            case 3:
                found = current->student->number == num;
                break;
            case 4:
                found = strcmp(current->student->name, condition) == 0;
                break;
            case 5:
                found = current->student->sex == get_sex(condition);
                break;
            case 6:
                found = current->student->building == num;
                break;
            case 7:
                found = current->student->room == num;
                break;
        }
        if (!found) {       // 当前结果不匹配
            continue;
        }
        count++;        // 统计查询到的结果数
        print_student(*current->student);
    }

    if (count == 0) {
        printf("未查询到任何信息！\n");      // 查询失败
    }
    query_end:
    return_menu();
    printf("-----------------------------------------------------------------------------\n");
}

/// 排序
void information_sort() {
    int option, i, j, k = 0;
    Student *array[20], *temp;
    Node *current;
    printf("------------------------------------排 序-------------------------------------\n\n");

    // 选择排序条件
    printf("请选择排序条件：\n");
    printf("1.学生姓名\n");
    printf("2.学号\n");
    printf("3.宿舍号\n");
    printf("4.班级\n");
    printf("5.性别\n");
    printf("0.返回\n");

    rewind(stdin);
    scanf("%d", &option);
    if (option == 0) {
        goto sort_end;
    }

    /// 链表中的结点放到指针数组中
    for (current = list->next; current; current = current->next) {
        array[k++] = current->student;
    }

    // 冒泡排序
    for (i = 0; i < list_size - 1; ++i) {
        bool sorted = true;
        for (j = 0; j < list_size - i - 1; ++j) {
            bool isswap;
            switch (option) {
                case 1:
                    isswap = strcmp(array[j]->name, array[j + 1]->name) > 0;
                    break;
                case 2:
                    isswap = array[j]->number > array[j + 1]->number;
                    break;
                case 3:
                    isswap = array[j]->room > array[j + 1]->room;
                    break;
                case 4:
                    isswap = compare_class(array[j]->sclass, array[j + 1]->sclass) > 0;
                    break;
                case 5:
                    isswap = array[j]->sex > array[j + 1]->sex;
                    break;
                default:
                    goto sort_end;
            }

            if (isswap) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                sorted = false;
            }
        }
        if (sorted) {
            break;
        }
    }

    // 顺序输出
    for (j = 0; j < list_size; ++j) {
        print_student(*array[j]);
    }
    sort_end:
    return_menu();
    printf("-----------------------------------------------------------------------------\n");
}

/// 获取字符串第一个整数
int get_first_int(char **src) {
    return strtol(*src, src, 10);
}

/// 获取字符串第一个不为空的字符串
void get_first_str(char *dest, char **src) {
    for (; *(*src) != '\0' && isspace(*(*src)); (*src)++);
    for (; *(*src) != '\0' && !isspace(*(*src)); (*src)++) {
        *dest++ = *(*src);
    }
    *dest = '\0';
}

/// 获取字符串中第一个不为空的字符
char get_first_char(char **src) {
    for (; isspace(**src); (*src)++);
    return *(*src)++;
}

/// 读取文件，生成链表
void read_files() {
    char buff[256];
    char *ptr;
    char sex[4];
    FILE *fp;
    fp = fopen(STU_FILE_NAME, "r");
    if (fp == NULL) {
        return;
    }
    Node *node;
    while (!feof(fp)) {
        fgets(buff, 256, fp);
        ptr = buff;

        // 创建新结点
        node = NEW_NODE();
        node->student = NEW_STUDENT();
        *node->student->remarks = '\0';

        // 获取一行数据
        get_first_str(node->student->college, &ptr);
        get_first_str(node->student->sclass, &ptr);
        node->student->number = get_first_int(&ptr);
        get_first_str(node->student->name, &ptr);
        get_first_str(sex, &ptr);
        node->student->sex = get_sex(sex);
        node->student->building = get_first_char(&ptr);
        node->student->room = strtol(ptr, &ptr, 10);
        node->student->bed = strtol(ptr, &ptr, 10);
        get_first_str(node->student->remarks, &ptr);

        // 插入链表
        insert_node(node);
    }
    fclose(fp);
}

/// 保存信息，写入文件
void write_files() {
    FILE *fp = fopen(STU_FILE_NAME, "w");
    if (fp == NULL) {
        printf("保存数据至文件失败！\n");
        return;
    }
    Student *stu;
    for (Node *cur = list; cur && cur->next; cur = cur->next) {
        stu = cur->next->student;
        fprintf(fp, "%s %s %d %s %s %c ", stu->college, stu->sclass, stu->number,
                stu->name, get_sex_name(stu->sex), stu->building);
        if (stu->building != NONE_BUILDING) {
            fprintf(fp, "%d %d ", stu->room, stu->bed);
        }
        printf("%s", stu->remarks);
        if (cur->next->next) {
            fputc('\n', fp);
        }
    }
    fclose(fp);
}

/// 根据性别的字符串返回枚举
SEX get_sex(const char *sex) {
    return strcmp(sex, "男") == 0 ? BOY : GIRL;
}

/// 根据性别枚举返回字符串
const char *get_sex_name(SEX sex) {
    return sex == BOY ? "男" : "女";
}

/// 初始化链表（含头结点）
void init_list() {
    list = NEW_NODE();
}

/// 链表插入结点（头插法）
void insert_node(Node *new_node) {
    new_node->next = list->next;
    list->next = new_node;
    list_size++;
}

/// 根据前置结点，删除链表结点
void delete_node(Node *front_node) {
    Node *node = front_node->next;
    front_node->next = node->next;
    free(node->student);
    free(node);
    list_size--;
}

/// 删除宿舍信息
void delete_dormitory(char building, int room) {
    for (Node *cur = list; cur && cur->next; cur = cur->next) {
        if (cur->next->student->building == building && cur->next->student->room == room) {
            cur->next->student->building = NONE_BUILDING;
            cur->next->student->room = 0;
            cur->next->student->bed = 0;
        }
    }
}

/// 根据学号查询前置结点
Node *search_front_node(int stu_number) {
    for (Node *cur = list; cur && cur->next; cur = cur->next) {
        if (cur->next->student->number == stu_number) {
            return cur;
        }
    }
    return NULL;
}

/// 根据学号查询结点
Node *search_node_number(int stu_number) {
    for (Node *cur = list; cur && cur->next; cur = cur->next) {
        if (cur->next->student->number == stu_number) {
            return cur->next;
        }
    }
    return NULL;
}

/// 根据学生姓名查询结点
Node *search_node_name(const char *stu_name) {
    for (Node *cur = list; cur && cur->next; cur = cur->next) {
        if (strcmp(cur->next->student->name, stu_name) == 0) {
            return cur->next;
        }
    }
    return NULL;
}

/// 判断一个字符串是否是整数
bool is_number(const char *str) {
    if (*str == '\0') {
        return false;
    }
    while (*str != '\0') {
        if (*str < '0' || *str > '9') {
            return false;
        }
        str++;
    }
    return true;
}

int compare_class(const char *cls1, const char *cls2) {
    int grade1;
    int grade2;
    int class1;
    int class2;
    while (*cls1 != '\0') {
        if (*cls1 >= '0' && *cls1 <= '9') {
            break;
        }
        cls1++;
    }
    char *end;
    grade1 = strtol(cls1, &end, 10);
    cls1 = end;
    while (*cls1 != '\0') {
        if (*cls1 >= '0' && *cls1 <= '9') {
            break;
        }
        cls1++;
    }
    class1 = strtol(cls1, &end, 10);

    while (*cls2 != '\0') {
        if (*cls2 >= '0' && *cls2 <= '9') {
            break;
        }
        cls2++;
    }
    grade2 = strtol(cls2, &end, 10);
    cls2 = end;
    while (*cls2 != '\0') {
        if (*cls2 >= '0' && *cls2 <= '9') {
            break;
        }
        cls2++;
    }
    class2 = strtol(cls2, &end, 10);

    if (grade1 != grade2) {
        return grade1 - grade2;
    }
    if (class1 == class2) {
        return 0;
    }
    return class1 - class2;
}

/**--------------------------------------- Implements ---------------------------------------*/
