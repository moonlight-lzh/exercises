#include "Definitions.h"


/// 用户登录
void Manage_Login() {
    int flag = 0, i = 0;
    char user[10], pwd[10];
    do {
        system("cls");
        i++;        // 登录次数
        printf("\n----------------------------------------用 户 登 录----------------------------------------\n");
        printf("                                    输入用户名：");
        scanf("%s", user);
        printf("                                    输入密码：");
        scanf("%s", pwd);
        if (strcmp(user, LOGIN_USER) == 0 && strcmp(pwd, LOGIN_PWD) == 0) {
            flag = 1;
            break;
        }
        printf("用户名或密码错误，请重新输入。\n");
        _getch();
    } while (i < 3);

    if (!flag) {
        printf("三次密码输入均错误，系统即将退出\n");
        exit(0);
    }
    CUTTING_LINE();
}

/// 新增住户
void Manage_Input() {
    Household *data;
    struct LinkedList list;
    char name[32];
    char other_name[32];

    LinkedList_ReadFile(&list);         // 读取文件至链表

    printf("请输入\n");
    printf("户主姓名：");
    scanf("%s", name);

    if (LinkedList_SearchName(list, name)) {        // 查询链表中是否存在该户主姓名
        LinkedList_Destroy(&list);                  //释放链表
        printf("新增失败，该户主信息已存在！\n");
        return;
    }

    data = (Household *) malloc(sizeof(Household));
    strcpy(data->name, name);

    printf("户主身份证：");
    scanf("%s", data->idcard);
    printf("性别：");
    scanf("%s", data->gender);
    printf("联系电话：");
    scanf("%s", data->phone);
    printf("楼号：");
    scanf("%s", data->building);
    printf("单元号：");
    scanf("%s", data->unit);
    printf("房号：");
    scanf("%s", data->room);
    printf("面积（平方米）：");
    scanf("%f", &data->area);
    printf("每平方物业的价格：");
    scanf("%f", &data->price);
    printf("应缴物业费：");
    scanf("%f", &data->payment);
    printf("备注：");
    scanf("%s", data->remark);

    printf("请输入户主名，新增住户插入该住户之后：");
    scanf("%s", other_name);
    Node *other_node = LinkedList_SearchName(list, other_name);
    if (other_node != NULL) {
        Node *new_node = (Node *) malloc(sizeof(Node));     // 创建新的链表结点
        new_node->data = data;
        new_node->next = other_node->next;
        other_node->next = new_node;
        list.size++;
    } else {
        LinkedList_Insert(&list, data);     // 新增数据插入链表
    }

    LinkedList_WriteFile(&list);        // 保存链表数据至文件
    LinkedList_Destroy(&list);          // 释放链表
    printf("新增成功！\n");
}

/// 住户信息修改辅助函数
int Manage_Modify_Aux(struct LinkedList list, Node **node) {
    char name[32];
    int choice;
    printf("请选择修改条件：\n");
    printf(" 1.户主姓名\n");
    printf(" 2.户主身份证\n");
    printf(" 3.性别\n");
    printf(" 4.联系电话\n");
    printf(" 5.楼号\n");
    printf(" 6.单元号\n");
    printf(" 7.房号\n");
    printf(" 8.面积\n");
    printf(" 9.每平方物业的价格\n");
    printf(" 10.应缴物业费\n");
    printf(" 11.备注\n");
    printf(" 0.返回\n");

    scanf("%d", &choice);
    printf("请输入修改值：");
    switch (choice) {
        case 1:
            scanf("%s", name);

            if (LinkedList_SearchName(list, name)) {        // 验证修改后的户主是否存在，保证户主姓名唯一
                printf("修改失败，该户主姓名已存在！\n");
                return 0;
            }
            strcpy((*node)->data->name, name);
            break;
        case 2:
            scanf("%s", (*node)->data->idcard);
            break;
        case 3:
            scanf("%s", (*node)->data->gender);
            break;
        case 4:
            scanf("%s", (*node)->data->phone);
            break;
        case 5:
            scanf("%s", (*node)->data->building);
            break;
        case 6:
            scanf("%s", (*node)->data->unit);
            break;
        case 7:
            scanf("%s", (*node)->data->room);
            break;
        case 8:
            scanf("%f", (*node)->data->area);
            break;
        case 9:
            scanf("%f", (*node)->data->price);
            break;
        case 10:
            scanf("%f", (*node)->data->payment);
            break;
        case 11:
            scanf("%s", (*node)->data->remark);
            break;
        default:
            return 0;
    }
    return 1;
}

/// 修改住户信息
void Manage_Modify() {

    char name[32];
    Node *node;
    struct LinkedList list;

    LinkedList_ReadFile(&list);         // 读取文件中的数据至链表

    printf("请输入需要修改的户主姓名：");
    scanf("%s", name);

    node = LinkedList_SearchName(list, name);       // 根据户主姓名查询链表结点
    if (node == NULL) {
        printf("无法修改，不存在该户主信息！\n");
    } else {
        if (Manage_Modify_Aux(list, &node))      // 修改结点信息
        {
            LinkedList_WriteFile(&list);        // 保存链表数据至文件
            printf("修改成功！\n");
        }
    }

    LinkedList_Destroy(&list);      // 释放链表
}

/// 删除住户信息
void Manage_Delete() {
    char name[32];
    printf("请输入待删除户主的姓名：");
    scanf("%s", name);

    struct LinkedList list;
    LinkedList_ReadFile(&list);         // 读取文件中的数据至链表

    if (LinkedList_Remove(&list, name)) {       // 根据户主姓名删除链表结点
        LinkedList_WriteFile(&list);        // 删除成功保存文件
        printf("删除成功！\n");
    } else {
        printf("删除失败，不存在该户主信息！\n");
    }

    LinkedList_Destroy(&list);      // 销毁链表
}

/// 浏览全部住户信息
void Manage_Browsing() {
    Household data;
    FILE *fp;
    int size, i;
    fp = fopen(DATA_FILE_NAME, "r");        // 只读方式打开文件
    if (fp == NULL) {
        printf("浏览失败，数据文件不存在！\n");
        return;
    }

    fscanf(fp, "%d\n", &size);        // 读取第一行的元素个数
    Household_Header();
    for (i = 0; i < size; i++) {
        Household_ReadFile(fp, &data);       // 将文件中的一行信息读取到数据结构体
        Household_Print(data);                     // 显示每一个住户信息
    }
    fclose(fp);         // 关闭文件指针
}

/// 查询住户信息
void Manage_Search() {
    int i, size;
    FILE *fp;
    Household data;
    char name[32], building[10], unit[10], room[10];

    printf("请选择查询方式：\n");
    printf(" 1.户主姓名\n");
    printf(" 2.楼号+单元号+房号\n");
    scanf("%d", &i);
    if (i != 1 && i != 2) {
        return;
    }

    fp = fopen(DATA_FILE_NAME, "r");        // 只读方式打开文件
    if (fp == NULL) {
        printf("浏览失败，数据文件不存在！\n");
        return;
    }

    fscanf(fp, "%d\n", &size);        // 读取第一行的元素个数

    if (i == 1) {
        printf("户主姓名：");
        scanf("%s", name);
    } else if (i == 2) {
        printf("楼号：");
        scanf("%s", building);
        printf("单元号：");
        scanf("%s", unit);
        printf("房号：");
        scanf("%s", room);   // 根据[楼号+单元号+房号]查询数组
    }
    Household_Header();
    for (int j = 0; j < size; j++) {
        Household_ReadFile(fp, &data);                  // 将文件中的一行信息读取到数据结构体
        if (i == 1 && strcmp(data.name, name) == 0) {
            Household_Print(data);                          // 打印显示每一个住户信息
        }
        if (i == 2 && strcmp(data.building, building) == 0 &&
            strcmp(data.unit, unit) == 0 &&
            strcmp(data.room, room) == 0) {
            Household_Print(data);                     // 打印显示每一个住户信息
        }
    }
    fclose(fp);         // 关闭文件指针
}

/// 自动生成物业费
void Manage_AutoGenPayment() {
    Node *node;
    struct LinkedList list;
    LinkedList_ReadFile(&list);     // 读取数据至链表

    for (node = list.head; node; node = node->next) {
        node->data->payment += node->data->area * node->data->price;        // 自动生成物业费
    }

    LinkedList_WriteFile(&list);        // 保存链表数据至文件
    LinkedList_Destroy(&list);          // 释放链表
    printf("物业费生成成功！\n");
}

/// 排序
void Manage_Sort() {
    int i;
    struct Array array;
    Array_ReadFile(&array);            //文件写入数组
    Array_SortBuilding(&array);        //排序
    Household_Header();                //表头
    for (i = 0; i < array.size; i++) {
        Household_Print(array.data[i]);   //数据显示
    }

}

/// 住户缴费
void Manage_Payment() {
    float fee;
    char name[32];
    int pos;
    struct Array array;

    printf("请输入户主姓名：");
    scanf("%s", name);
    Array_ReadFile(&array);     // 读取文件数据至数组

    pos = Array_SearchName(array, name);        // 根据户主姓名查询数组

    if (pos < 0) {
        printf("缴费失败，不存在该住户信息！\n");
    } else if (array.data[pos].payment <= 0) {
        printf("该住户已缴清物业费，无法重新缴费！\n");
    } else {
        printf("该住户未缴纳物业费：%.2f\n", array.data[pos].payment);
        printf("请输入缴费额：");
        scanf("%f", &fee);

        if (fee > 0 && fee <= array.data[pos].payment) {
            array.data[pos].payment -= fee;              // 缴费
            Array_WriteFile(&array);                // 保存数组数据至文件
            printf("缴费成功！\n");
        } else {
            printf("缴费失败，您输入的缴费额异常！\n");
        }
    }

}

/// 统计未缴费住户信息
void Manage_Statistic() {
    struct Array array;
    int i, j, k, count;

    Array_ReadFile(&array);     // 读取文件数据至数组

    Array_SortBuilding(&array);     // 根据楼号排序

    for (i = 0; i < array.size; i++) {
        if (array.data[i].payment <= 0) {
            continue;
        }

        count = 0;      // 查找一遍，该楼号是否存在未缴费住户
        for (j = 0; j < array.size; j++) {
            if (array.data[j].payment > 0 &&
                strcmp(array.data[j].building, array.data[i].building) == 0) {
                count++;
            }
        }

        if (count == 0) {       // 该楼号下住户全部缴费
            continue;
        }

        printf("楼号：%s     未缴清物业费人数：%d\n", array.data[i].building, count);

        k = i;
        for (j = i; j < array.size; j++) {
            if (array.data[j].payment > 0 && strcmp(array.data[j].building, array.data[i].building) == 0) {

                printf("    户主：%-8s  单元号：%-5s  房号：%-5s  未缴物业费：%-8.2f  备注信息：%s\n",
                       array.data[j].name, array.data[j].unit, array.data[j].room, array.data[j].payment,
                       array.data[j].remark);
                k = j;
            }
        }
        putchar('\n');
        i = k;
    }
}
