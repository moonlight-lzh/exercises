#include "LinkList.h"

/**
 * 析构函数
 */
LinkList::~LinkList() {
    for (size_t i = 0; i < size; ++i) {
        Node *node = this->head;
        this->head = this->head->next;
        delete node->data;
        delete node;
    }
}

/**
 * 获取链表头结点
 * @return 链表的头结点
 */
const Node *LinkList::get_head() {
    return this->head;
}

/**
 * 链表是否为空
 * @return true：链表为空，false：链表不为空
 */
bool LinkList::empty() {
    return size == 0;
}

/**
 * 插入数据到链表尾端
 * @param data 学生指针
 */
void LinkList::append(Student *data) {
    if (empty()) {
        this->head = this->tail = new Node(data, nullptr);
    } else {
        tail->next = new Node(data, tail->next);
        tail = tail->next;
    }
    size++;
}

/**
 * 删除第一个匹配的结点
 * @param str 字符串
 * @param cmp 比较函数指针
 * @return
 */
bool LinkList::delete_first(const string &str, bool  (*cmp)(const Student &, const string &)) {
    if (empty()) {
        return false;
    }

    Node *node = nullptr;               // 待删除结点
    if (cmp(*head->data, str)) {
        node = head;                    // 删除头结点
        head = head->next;
    } else {
        Node *pre = nullptr;                // 待删除结点的前置结点
        for (Node *p = head; p && p->next; p = p->next) {
            if (cmp(*p->next->data, str)) {
                pre = p;
                break;
            }
        }

        if (pre == nullptr) {
            return false;
        }

        if (pre->next == tail) {            // 待删除结点为当前链表的尾结点
            node = tail;
            tail = pre;
        } else {
            node = pre->next;
            pre->next = node->next;
        }
    }

    delete node->data;
    delete node;
    size--;
    return true;
}

/**
 * 查询第一个匹配的结点
 * @param str 字符串
 * @param cmp 比较函数指针
 * @return 学生指针
 */
Student *LinkList::find_first(const string &str, bool  (*cmp)(const Student &, const string &)) {
    for (const Node *p = head; p; p = p->next) {
        if (cmp(*p->data, str)) {
            return p->data;
        }
    }
    return nullptr;
}

/**
 * 查找所有匹配的结点
 * @param str 字符串
 * @param find 查找的结果向量
 * @param cmp 比较函数指针
 */
void LinkList::find_all(const string &str, vector<Student *> &find, bool (*cmp)(const Student &, const string &)) {
    for (const Node *p = head; p; p = p->next) {
        if (cmp(*p->data, str)) {
            find.push_back(p->data);
        }
    }
}

/**
 * 判断指定内容的结点是否存在
 * @param str 字符串
 * @param cmp 比较函数指针
 * @return
 */
bool LinkList::exist(const string &str, bool  (*cmp)(const Student &, const string &)) {
    return find_first(str, cmp) != nullptr;
}

/**
 * 打印显示所有的结点信息
 */
void LinkList::show_all() {
    if (empty()) {
        return;
    }
    Node *p = head;
    while (p) {
        std::cout << *(p->data);
        p = p->next;
    }
}