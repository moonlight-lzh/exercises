#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include "LinkList.h"
#include "Statistic.h"
#include "Student.h"

using namespace std;

/**
 * 管理类
 */
class Management {
private:
    /// 链表指针
    LinkList *list;

    /// 统计类指针
    Statistic *statistic;

    /// 数据文件名称
    const string filename = "./students.txt";
public:
    /// 构造函数
    Management();

    /// 析构函数
    ~Management();

    /// 读取数据文件
    void read_files();

    /// 保存数据文件
    void write_files();

    /// 信息录入
    void info_entry();

    /// 信息修改
    void info_modify();

    ///信息删除
    void info_delete();

    /// 信息查询
    void info_query();

    /// 信息统计
    void info_statistics();

    /// 信息浏览
    void info_view();

    /// 打印分割线
    static void parting_line();

    /// 检查性别字符串是否合法
    static bool check_gender(const string &);

    /// 检查年龄字符串是否合法
    static bool check_age(const string &);
};