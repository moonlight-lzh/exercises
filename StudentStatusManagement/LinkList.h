#pragma once

#include <iostream>
#include <vector>

#include "Student.h"
#include "Node.h"

/**
 * ��������
 */
class LinkList {
private:
    /// ͷ���
    Node *head = nullptr;

    /// β���
    Node *tail = nullptr;

    /// �����С
    size_t size = 0;
public:
    /// Ĭ�Ϲ��캯��
    LinkList() = default;

    /// ��������
    ~LinkList();

    /// ��ȡ����ͷ���
    const Node *get_head();

    /// �ж������Ƿ�Ϊ��
    bool empty();

    /// ����β����ӽ��
    void append(Student *);

    /// ɾ����һ��ƥ��Ľ��
    bool delete_first(const string &, bool (*cmp)(const Student &, const string &));

    /// ���ҵ�һ��ƥ��Ľ��
    Student *find_first(const string &, bool (*cmp)(const Student &, const string &));

    /// ��������ƥ��Ľ��
    void find_all(const string &, vector<Student *> &, bool (*cmp)(const Student &, const string &));

    /// �ж��Ƿ����ƥ��Ľ��
    bool exist(const string &, bool (*cmp)(const Student &, const string &));

    /// ��ӡչʾ���н�����Ϣ
    void show_all();
};