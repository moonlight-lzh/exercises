#ifndef PROPERTYMANAGEMENT_DEFINITIONS_H
#define PROPERTYMANAGEMENT_DEFINITIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <conio.h>

/******************************************** �궨�� *********************************************/

#define LOGIN_USER "abc"
#define LOGIN_PWD "abc"
#define DATA_FILE_NAME "../household.dat"
#define CUTTING_LINE() \
    printf("---------------------------------------------------------------------------------------------------------\n")
/*************************************************************************************************/

/******************************************** �ṹ�� *********************************************/

/** ס����Ϣ�ṹ�� */
typedef struct {
    char name[32];          // ��������
    char gender[4];         // �Ա�
    char idcard[20];        // �������֤��
    char phone[12];         // ��ϵ�绰
    char building[10];      // ¥��
    char unit[10];          // ��Ԫ��
    char room[10];          // ����
    float area;             // ���
    float price;            // ÿƽ����ҵ�ļ۸�
    float payment;          // Ӧ������ҵ��
    char remark[64];        // ��ע
} Household;

/** ������ṹ�� */
typedef struct Node {
    Household *data;        // ������
    struct Node *next;      // nextָ����
} Node;

/** ������ṹ�� */
struct LinkedList {
    Node *head;             // ͷ���ָ��
    Node *tail;             // β���ָ��
    int size;               // ��������
};

/** ����ṹ�� */
struct Array {
    Household data[100];       // ����
    int size;               // ������Ԫ�ظ���
};

/*************************************************************************************************/


/******************************************** ������غ��� *****************************************/

/**
 * ��ӡ��ͷ
 */
void Household_Header();

/**
 * ��ӡס����Ϣ
 * @param data ס������
 */
void Household_Print(Household data);

/**
 * ���ַ�����ȡ�ַ���
 * @param dest Ŀ���ַ���
 * @param src Դ�ַ���
 * @param end ��ȡ������ָ��
 */
void Household_ReadString(char *dest, char *src, char **end);

/**
 * ���ļ���ȡ������Ϣ
 * @param fp �ļ�ָ��
 * @param data �����ṹ��
 */
void Household_ReadFile(FILE *fp, Household *data);

/**
 * ��������Ϣд���ļ�
 * @param fp �ļ�ָ��
 * @param data ������Ϣ
 */
void Household_WriteFile(FILE *fp, Household data);

/*************************************************************************************************/


/******************************************** ������غ��� *****************************************/

/**
 * ����ס����Ϣ
 * @param list ����
 * @param data ס������ָ��
 */
void LinkedList_Insert(struct LinkedList *list, Household *data);

/**
 * ��������
 * @param list ����
 */
void LinkedList_Destroy(struct LinkedList *list);

/**
 * ɾ��������
 * @param list ����
 * @param name ��ɾ�����Ļ�������
 * @return ɾ���ɹ�����1��ʧ�ܷ���0
 */
int LinkedList_Remove(struct LinkedList *list, const char *name);

/**
 * ���ݻ���������ѯ������
 * @param list ����
 * @param name ��������
 * @return ��ѯ���������㣬��ѯʧ�ܷ���NULL
 */
Node *LinkedList_SearchName(struct LinkedList list, const char *name);

/**
 * ��ȡ�ļ�����������
 * @param list ����
 */
void LinkedList_ReadFile(struct LinkedList *list);

/**
 * ���������е��������ļ�
 * @param list ����
 */
void LinkedList_WriteFile(struct LinkedList *list);

/*************************************************************************************************/

/******************************************** ������غ��� *****************************************/

/**
 * ��ȡ�ļ�����������
 * @param array ����
 */
void Array_ReadFile(struct Array *array);

/**
 * �������е�����д���ļ�
 * @param array ����
 */
void Array_WriteFile(struct Array *array);


/**
 * ����[¥��]������������
 * @param array ����
 */
void Array_SortBuilding(struct Array *array);


/**
 * ����[��������]��ѯ����Ԫ�أ�������������
 * @param array ����
 * @param name ��������
 * @return ��ѯ������������ѯʧ�ܷ���-1
 */
int Array_SearchName(struct Array array, const char *name);


/*************************************************************************************************/


/****************************************** ����������غ��� ****************************************/

/**
 * �û���¼
 */
void Manage_Login();

/**
 * ����ס����Ϣ
 */
void Manage_Input();

/**
 * �޸�ס����Ϣ
 */
void Manage_Modify();

/**
 * ɾ��ס����Ϣ
 */
void Manage_Delete();

/**
 * �������ס����Ϣ
 */
void Manage_Browsing();

/**
 * ����
 */
void Manage_Sort();
/**
 * ��ѯס����Ϣ
 */
void Manage_Search();

/**
 * �Զ�������ҵ��
 */
void Manage_AutoGenPayment();

/**
 * �����ɷ�
 */
void Manage_Payment();

/**
 * ��¥��ͳ��δ���ѻ�����Ϣ
 */
void Manage_Statistic();

/**
 * �޸�ס����Ϣ��������
 * @param list ����
 * @param node ���޸ĵĽ��
 * @return �޸Ľ����1��ʾ�޸ĳɹ���0��ʾ�޸�ʧ��
 */
int Manage_Modify_Aux(struct LinkedList list, Node **node);

/*************************************************************************************************/

#endif //PROPERTYMANAGEMENT_DEFINITIONS_H