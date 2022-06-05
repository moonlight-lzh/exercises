#include "Definitions.h"

///插入
void LinkedList_Insert(struct LinkedList *list, Household *data) {
    Node *new_node = (Node *) malloc(sizeof(Node));  //创建新的链表结点
    new_node->data = data;
    new_node->next = NULL;
    if (list->tail == NULL) {
        list->head = list->tail = new_node;    //链表为空，则将新增节点作为头结点
    } else {
        list->tail->next = new_node;
        list->tail = new_node;                //新结点插入链表尾端
    }
    list->size++;
}
///释放链表
void LinkedList_Destroy(struct LinkedList *list) {
    Node *node;
    while (list->head) {
        node = list->head;
        list->head = list->head->next;
        free(node->data);             //释放数据
        free(node);                   //释放结点
    }
    list->head = list->tail = NULL;
    list->size = 0;
}

///根据姓名查询链表结点
Node *LinkedList_SearchName(struct LinkedList list, const char *name) {
    Node *node;
    for (node = list.head; node; node = node->next) {
        if (strcmp(node->data->name, name) == 0) {
            return node;
        }
    }
    return NULL;
}

///根据姓名删除链表结点
int LinkedList_Remove(struct LinkedList *list, const char *name) {
    if (list->head == NULL) {
        return 0;
    }

    Node *node, *temp;
    if (strcmp(list->head->data->name, name) == 0) {            // 删除的是头结点
        node = list->head;
        list->head = list->head->next;
        list->size--;
        free(node);
        return 1;
    }

    node = list->head;
    while (node && node->next) {
        if (strcmp(node->next->data->name, name) == 0) {
            temp = node->next;
            node->next = node->next->next;
            if (temp == list->tail) {
                list->tail = node;      // 删除了尾结点
            }
            list->size--;
            free(temp);
            return 1;
        }
        node = node->next;
    }
    return 0;
}

///从文件读取数据至链表
void LinkedList_ReadFile(struct LinkedList *list) {
    int i, size;
    Household *data;
    FILE *fp;

    list->size = 0;
    list->head = list->tail = NULL;

    fp = fopen(DATA_FILE_NAME, "r");    //只读的方式打开文件
    if (fp == NULL) {
        return;
    }

    fscanf(fp, "%d\n", &size);           //读取元素个数

    for (i = 0; i < size; ++i) {
        data = (Household *) malloc(sizeof(Household));   //创建数据指针
        Household_ReadFile(fp, data);        //将文件中一行信息读入数据指针
        LinkedList_Insert(list, data);       //数据插入链表
    }
    fclose(fp);
}

///将链表中数据保存至文件
void LinkedList_WriteFile(struct LinkedList *list) {
    Node *node;
    FILE *fp;
    fp = fopen(DATA_FILE_NAME, "w");    //只写的方式打开文件
    if (fp == NULL) {
        printf("保存数据打开文件失败：%s\n", strerror(errno));
        return;
    }

    fprintf(fp, "%d\n", list->size);     //链表结点个数写入文件

    for (node = list->head; node; node = node->next) {
        Household_WriteFile(fp, *node->data);   //结点的数据写入文件
    }
    fclose(fp);
}
