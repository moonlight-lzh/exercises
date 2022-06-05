#include "Definitions.h"

///����
void LinkedList_Insert(struct LinkedList *list, Household *data) {
    Node *new_node = (Node *) malloc(sizeof(Node));  //�����µ�������
    new_node->data = data;
    new_node->next = NULL;
    if (list->tail == NULL) {
        list->head = list->tail = new_node;    //����Ϊ�գ��������ڵ���Ϊͷ���
    } else {
        list->tail->next = new_node;
        list->tail = new_node;                //�½���������β��
    }
    list->size++;
}
///�ͷ�����
void LinkedList_Destroy(struct LinkedList *list) {
    Node *node;
    while (list->head) {
        node = list->head;
        list->head = list->head->next;
        free(node->data);             //�ͷ�����
        free(node);                   //�ͷŽ��
    }
    list->head = list->tail = NULL;
    list->size = 0;
}

///����������ѯ������
Node *LinkedList_SearchName(struct LinkedList list, const char *name) {
    Node *node;
    for (node = list.head; node; node = node->next) {
        if (strcmp(node->data->name, name) == 0) {
            return node;
        }
    }
    return NULL;
}

///��������ɾ��������
int LinkedList_Remove(struct LinkedList *list, const char *name) {
    if (list->head == NULL) {
        return 0;
    }

    Node *node, *temp;
    if (strcmp(list->head->data->name, name) == 0) {            // ɾ������ͷ���
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
                list->tail = node;      // ɾ����β���
            }
            list->size--;
            free(temp);
            return 1;
        }
        node = node->next;
    }
    return 0;
}

///���ļ���ȡ����������
void LinkedList_ReadFile(struct LinkedList *list) {
    int i, size;
    Household *data;
    FILE *fp;

    list->size = 0;
    list->head = list->tail = NULL;

    fp = fopen(DATA_FILE_NAME, "r");    //ֻ���ķ�ʽ���ļ�
    if (fp == NULL) {
        return;
    }

    fscanf(fp, "%d\n", &size);           //��ȡԪ�ظ���

    for (i = 0; i < size; ++i) {
        data = (Household *) malloc(sizeof(Household));   //��������ָ��
        Household_ReadFile(fp, data);        //���ļ���һ����Ϣ��������ָ��
        LinkedList_Insert(list, data);       //���ݲ�������
    }
    fclose(fp);
}

///�����������ݱ������ļ�
void LinkedList_WriteFile(struct LinkedList *list) {
    Node *node;
    FILE *fp;
    fp = fopen(DATA_FILE_NAME, "w");    //ֻд�ķ�ʽ���ļ�
    if (fp == NULL) {
        printf("�������ݴ��ļ�ʧ�ܣ�%s\n", strerror(errno));
        return;
    }

    fprintf(fp, "%d\n", list->size);     //���������д���ļ�

    for (node = list->head; node; node = node->next) {
        Household_WriteFile(fp, *node->data);   //��������д���ļ�
    }
    fclose(fp);
}
