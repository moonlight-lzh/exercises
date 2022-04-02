#ifndef QUEUESYSTEM_LINKQUEUE_H
#define QUEUESYSTEM_LINKQUEUE_H

#include <stdlib.h>     // 引入stdlib.h头文件中的malloc和free函数

/**
 * 业务类型枚举
 */
enum BusinessType {
    Personal,       // 个人业务
    Corporate,      // 公司业务
    Integrated,     // 综合业务
    Priority        // 优先业务
};

/**
 * 数据结构体
 */
struct Data {
    int number;                          // 叫号
    enum BusinessType businessType;      // 业务类型
    char name[16];                       // 姓名
};

/**
 * 链队列中的节点结构体
 */
struct LinkNode {
    struct Data *data;           // 数据域
    struct LinkNode *next;      // 指针域
};

/**
 * 链队列结构体
 */
struct LinkQueue {
    struct LinkNode *front;     // 队首指针，出队删除节点
    struct LinkNode *rear;      // 队尾指针，入队添加节点
    int size;                   // 队列中结点数
};

/**
 * malloc申请堆空间创建LinkNode指针
 */
#define NEW_NODE()((struct LinkNode *) malloc(sizeof(struct LinkNode)))

/**
 * malloc申请堆空间创建Data指针
 */
#define NEW_DATA()((struct Data *) malloc(sizeof(struct Data)))

/**
 * 队列初始化
 * @param queue 队列指针
 */
void LinkQueue_Init(struct LinkQueue *queue);

/**
 * 判断队列是否为空
 * @param queue 队列
 * @return 1为空，0不为空
 */
int LinkQueue_IsEmpty(struct LinkQueue queue);

/**
 * 数据入队
 * @param queue
 * @param x
 */
void LinkQueue_EnQueue(struct LinkQueue *queue, struct Data *x);

/**
 * 数据出队
 * @param queue 队列
 * @param x 出队返回的数据指针
 * @return
 */
int LinkQueue_DeQueue(struct LinkQueue *queue, struct Data **x);

/**
 * 删除队列中的结点
 * @param queue 队列
 * @param node 待删除结点
 */
void LinkQueue_RemoveNode(struct LinkQueue *queue, struct LinkNode *node);

#endif
