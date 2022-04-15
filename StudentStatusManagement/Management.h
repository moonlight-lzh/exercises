#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include "LinkList.h"
#include "Statistic.h"
#include "Student.h"

using namespace std;

/**
 * ������
 */
class Management {
private:
    /// ����ָ��
    LinkList *list;

    /// ͳ����ָ��
    Statistic *statistic;

    /// �����ļ�����
    const string filename = "./students.txt";
public:
    /// ���캯��
    Management();

    /// ��������
    ~Management();

    /// ��ȡ�����ļ�
    void read_files();

    /// ���������ļ�
    void write_files();

    /// ��Ϣ¼��
    void info_entry();

    /// ��Ϣ�޸�
    void info_modify();

    ///��Ϣɾ��
    void info_delete();

    /// ��Ϣ��ѯ
    void info_query();

    /// ��Ϣͳ��
    void info_statistics();

    /// ��Ϣ���
    void info_view();

    /// ��ӡ�ָ���
    static void parting_line();

    /// ����Ա��ַ����Ƿ�Ϸ�
    static bool check_gender(const string &);

    /// ��������ַ����Ƿ�Ϸ�
    static bool check_age(const string &);
};