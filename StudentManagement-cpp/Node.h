#pragma once

#include "Student.h"

/**
 * �����
 */
class Node {
    /// ��Ԫ��LinkList
    friend class LinkList;

    /// ��Ԫ��Statistic
    friend class Statistic;

    /// ��Ԫ��Management
    friend class Management;
private:
    /// �޲ι��캯��
    Node() = default;

    /// ���в����Ĺ��캯��
    Node(Student *data, Node *next) {
        this->next = next;
        this->data = data;
    }

    /// nextָ����
    Node *next = nullptr;

    /// ������
    Student *data = nullptr;
};