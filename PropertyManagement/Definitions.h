#ifndef PROPERTYMANAGEMENT_DEFINITIONS_H
#define PROPERTYMANAGEMENT_DEFINITIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <conio.h>

/******************************************** 宏定义 *********************************************/

#define LOGIN_USER "abc"
#define LOGIN_PWD "abc"
#define DATA_FILE_NAME "../household.dat"
#define CUTTING_LINE() \
    printf("---------------------------------------------------------------------------------------------------------\n")
/*************************************************************************************************/

/******************************************** 结构体 *********************************************/

/** 住户信息结构体 */
typedef struct {
    char name[32];          // 户主姓名
    char gender[4];         // 性别
    char idcard[20];        // 户主身份证号
    char phone[12];         // 联系电话
    char building[10];      // 楼号
    char unit[10];          // 单元号
    char room[10];          // 房号
    float area;             // 面积
    float price;            // 每平方物业的价格
    float payment;          // 应缴纳物业费
    char remark[64];        // 备注
} Household;

/** 链表结点结构体 */
typedef struct Node {
    Household *data;        // 数据域
    struct Node *next;      // next指针域
} Node;

/** 单链表结构体 */
struct LinkedList {
    Node *head;             // 头结点指针
    Node *tail;             // 尾结点指针
    int size;               // 链表结点数
};

/** 数组结构体 */
struct Array {
    Household data[100];       // 数组
    int size;               // 数组中元素个数
};

/*************************************************************************************************/


/******************************************** 户主相关函数 *****************************************/

/**
 * 打印表头
 */
void Household_Header();

/**
 * 打印住户信息
 * @param data 住户数据
 */
void Household_Print(Household data);

/**
 * 从字符串读取字符串
 * @param dest 目标字符串
 * @param src 源字符串
 * @param end 读取结束的指针
 */
void Household_ReadString(char *dest, char *src, char **end);

/**
 * 从文件读取户主信息
 * @param fp 文件指针
 * @param data 户主结构体
 */
void Household_ReadFile(FILE *fp, Household *data);

/**
 * 将户主信息写入文件
 * @param fp 文件指针
 * @param data 户主信息
 */
void Household_WriteFile(FILE *fp, Household data);

/*************************************************************************************************/


/******************************************** 链表相关函数 *****************************************/

/**
 * 插入住户信息
 * @param list 链表
 * @param data 住户数据指针
 */
void LinkedList_Insert(struct LinkedList *list, Household *data);

/**
 * 销毁链表
 * @param list 链表
 */
void LinkedList_Destroy(struct LinkedList *list);

/**
 * 删除链表结点
 * @param list 链表
 * @param name 待删除结点的户主姓名
 * @return 删除成功返回1，失败返回0
 */
int LinkedList_Remove(struct LinkedList *list, const char *name);

/**
 * 根据户主姓名查询链表结点
 * @param list 链表
 * @param name 户主姓名
 * @return 查询到的链表结点，查询失败返回NULL
 */
Node *LinkedList_SearchName(struct LinkedList list, const char *name);

/**
 * 读取文件数据至链表
 * @param list 链表
 */
void LinkedList_ReadFile(struct LinkedList *list);

/**
 * 保存链表中的数据至文件
 * @param list 链表
 */
void LinkedList_WriteFile(struct LinkedList *list);

/*************************************************************************************************/

/******************************************** 数组相关函数 *****************************************/

/**
 * 读取文件数据至数组
 * @param array 数组
 */
void Array_ReadFile(struct Array *array);

/**
 * 将数组中的数据写入文件
 * @param array 数组
 */
void Array_WriteFile(struct Array *array);


/**
 * 根据[楼号]进行数组排序
 * @param array 数组
 */
void Array_SortBuilding(struct Array *array);


/**
 * 根据[户主姓名]查询数组元素，返回数组索引
 * @param array 数组
 * @param name 户主姓名
 * @return 查询到的索引，查询失败返回-1
 */
int Array_SearchName(struct Array array, const char *name);


/*************************************************************************************************/


/****************************************** 户主管理相关函数 ****************************************/

/**
 * 用户登录
 */
void Manage_Login();

/**
 * 新增住户信息
 */
void Manage_Input();

/**
 * 修改住户信息
 */
void Manage_Modify();

/**
 * 删除住户信息
 */
void Manage_Delete();

/**
 * 浏览所有住户信息
 */
void Manage_Browsing();

/**
 * 排序
 */
void Manage_Sort();
/**
 * 查询住户信息
 */
void Manage_Search();

/**
 * 自动生成物业费
 */
void Manage_AutoGenPayment();

/**
 * 户主缴费
 */
void Manage_Payment();

/**
 * 按楼号统计未交费户主信息
 */
void Manage_Statistic();

/**
 * 修改住户信息辅助函数
 * @param list 链表
 * @param node 待修改的结点
 * @return 修改结果：1表示修改成功，0表示修改失败
 */
int Manage_Modify_Aux(struct LinkedList list, Node **node);

/*************************************************************************************************/

#endif //PROPERTYMANAGEMENT_DEFINITIONS_H