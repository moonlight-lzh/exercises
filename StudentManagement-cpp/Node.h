#pragma once

#include "Student.h"

/**
 * 结点类
 */
class Node {
    /// 友元类LinkList
    friend class LinkList;

    /// 友元类Statistic
    friend class Statistic;

    /// 友元类Management
    friend class Management;
private:
    /// 无参构造函数
    Node() = default;

    /// 含有参数的构造函数
    Node(Student *data, Node *next) {
        this->next = next;
        this->data = data;
    }

    /// next指针域
    Node *next = nullptr;

    /// 数据域
    Student *data = nullptr;
};