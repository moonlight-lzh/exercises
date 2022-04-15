#pragma once

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/// <summary>
/// 学生类
/// </summary>
class Student {
    // 友元类Management
    friend class Management;

private:
    string number;          // 学号
    string name;            // 姓名
    string gender;          // 性别
    string age;             // 年龄
    string classes;         // 班级
    string major;           // 专业
    string dept;            // 系别
public:
    // 默认构造函数
    Student() = default;

    // 重载输出操作符
    friend ostream &operator<<(ostream &, const Student &);

    // 重载输入操作符
    friend istream &operator>>(istream &, Student &);

    static void show_title();

    // 获取性别
    static string get_gender(const Student &stu) { return stu.gender; }

    // 获取班级
    static string get_classes(const Student &stu) { return stu.classes; }

    // 获取年龄
    static string get_age(const Student &stu) { return stu.age; }

    // 获取系别
    static string get_dept(const Student &stu) { return stu.dept; }

    // 比较学号
    static bool cmp_number(const Student &stu, const string &str) { return str == stu.number; }

    // 比较姓名
    static bool cmp_name(const Student &stu, const string &str) { return str == stu.name; }

    // 比较性别
    static bool cmp_gender(const Student &stu, const string &str) { return str == stu.gender; }

    // 比较班级
    static bool cmp_classes(const Student &stu, const string &str) { return str == stu.classes; }

    // 比较专业
    static bool cmp_major(const Student &stu, const string &str) { return str == stu.major; }

    // 比较系别
    static bool cmp_dept(const Student &stu, const string &str) { return str == stu.dept; }
};