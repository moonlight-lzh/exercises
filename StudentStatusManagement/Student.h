#pragma once

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/// <summary>
/// ѧ����
/// </summary>
class Student {
    // ��Ԫ��Management
    friend class Management;

private:
    string number;          // ѧ��
    string name;            // ����
    string gender;          // �Ա�
    string age;             // ����
    string classes;         // �༶
    string major;           // רҵ
    string dept;            // ϵ��
public:
    // Ĭ�Ϲ��캯��
    Student() = default;

    // �������������
    friend ostream &operator<<(ostream &, const Student &);

    // �������������
    friend istream &operator>>(istream &, Student &);

    static void show_title();

    // ��ȡ�Ա�
    static string get_gender(const Student &stu) { return stu.gender; }

    // ��ȡ�༶
    static string get_classes(const Student &stu) { return stu.classes; }

    // ��ȡ����
    static string get_age(const Student &stu) { return stu.age; }

    // ��ȡϵ��
    static string get_dept(const Student &stu) { return stu.dept; }

    // �Ƚ�ѧ��
    static bool cmp_number(const Student &stu, const string &str) { return str == stu.number; }

    // �Ƚ�����
    static bool cmp_name(const Student &stu, const string &str) { return str == stu.name; }

    // �Ƚ��Ա�
    static bool cmp_gender(const Student &stu, const string &str) { return str == stu.gender; }

    // �Ƚϰ༶
    static bool cmp_classes(const Student &stu, const string &str) { return str == stu.classes; }

    // �Ƚ�רҵ
    static bool cmp_major(const Student &stu, const string &str) { return str == stu.major; }

    // �Ƚ�ϵ��
    static bool cmp_dept(const Student &stu, const string &str) { return str == stu.dept; }
};