#pragma once

#include <iostream>
#include <vector>

#include "Student.h"
#include "Node.h"

/**
 * 单链表类
 */
class LinkList {
private:
    /// 头结点
    Node *head = nullptr;

    /// 尾结点
    Node *tail = nullptr;

    /// 链表大小
    size_t size = 0;
public:
    /// 默认构造函数
    LinkList() = default;

    /// 析构函数
    ~LinkList();

    /// 获取链表头结点
    const Node *get_head();

    /// 判断链表是否为空
    bool empty();

    /// 链表尾部添加结点
    void append(Student *);

    /// 删除第一个匹配的结点
    bool delete_first(const string &, bool (*cmp)(const Student &, const string &));

    /// 查找第一个匹配的结点
    Student *find_first(const string &, bool (*cmp)(const Student &, const string &));

    /// 查找所有匹配的结果
    void find_all(const string &, vector<Student *> &, bool (*cmp)(const Student &, const string &));

    /// 判断是否存在匹配的结点
    bool exist(const string &, bool (*cmp)(const Student &, const string &));

    /// 打印展示所有结点的信息
    void show_all();
};