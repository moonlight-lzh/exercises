#include "LinkQueue.h"

/**
 * 初始化带头结点的队列
 * @param queue 队列
 */
void LinkQueue_Init(struct LinkQueue *queue) {
    struct LinkNode *node = NEW_NODE();     // 初始化一个头结点
    node->next = NULL;
    queue->front = queue->rear = node;
    queue->size = 0;
}

/**
 * 判断队列是否为空
 * @param queue 队列
 * @return 返回1：队列为空，返回0：队列非空
 */
int LinkQueue_IsEmpty(struct LinkQueue queue) {
    return queue.size == 0;
}

/**
 * 队列入队
 * @param queue 队列
 * @param x 待入队元素
 */
void LinkQueue_EnQueue(struct LinkQueue *queue, struct Data *x) {
    struct LinkNode *node = NEW_NODE();
    node->data = x;
    node->next = NULL;
    queue->rear->next = node;       // 尾插法增加结点
    queue->rear = node;         // 更新尾指针
    queue->size++;      // 更新队列元素大小
}

/**
 * 队列出队，并返回出队元素
 * @param queue 队列
 * @param x 返回的出队元素
 * @return 返回1：出队成功，返回0：出队失败，队列为空
 */
int LinkQueue_DeQueue(struct LinkQueue *queue, struct Data **x) {
    if (LinkQueue_IsEmpty(*queue)) {
        return 0;
    }
    struct LinkNode *node = queue->front->next;
    *x = node->data;            // 返回被删除结点的数据指针
    queue->front->next = node->next;        // 更新前一个结点的next指针
    LinkQueue_RemoveNode(queue, node);      // 删除结点
    return 1;
}

/**
 * 保留数据，删除队列中的结点
 * @param queue 队列
 * @param node 待删除结点
 */
void LinkQueue_RemoveNode(struct LinkQueue *queue, struct LinkNode *node) {
    if (node == NULL) {
        return;
    }
    node->data = NULL;
    free(node);     // 释放结点
    queue->size--;      // 更新队列元素大小
    if (queue->size == 0) {
        queue->rear = queue->front;         // 队列中只有一个节点，出队后更新尾结点指针，队列变为空
    }
}
