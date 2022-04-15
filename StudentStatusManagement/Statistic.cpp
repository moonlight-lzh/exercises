#include "Statistic.h"

/**
 * 打印统计结果
 */
inline void Statistic::show_result() {
    cout << "------------------------------------- 统计结果 -------------------------------------" << endl;

    for (const auto &pair : umap) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }

    cout << "------------------------------------------------------------------------------------" << endl;
}

/**
 * 统计不同的字段
 * @param list 单链表
 * @param get_value 获取统计字段的函数指针
 */
void Statistic::statistic(LinkList &list, string(*get_value)(const Student &)) {
    umap.clear();                   // 清空原始数据
    if (list.empty()) {             // 链表是否为空
        return;
    }
    // 循环单链表
    for (const Node *node = list.get_head(); node; node = node->next) {
        // 利用哈希表统计
        if (umap.count(get_value(*node->data))) {
            umap[get_value(*node->data)]++;
        } else {
            umap[get_value(*node->data)] = 1;
        }
    }

    // 打印统计结果
    show_result();
}

/**
 * 统计性别
 * @param list 单链表
 */
void Statistic::gender_statistic(LinkList &list) {
    statistic(list, Student::get_gender);
}

/**
 * 统计班级
 * @param list 单链表
 */
void Statistic::classes_statistic(LinkList &list) {
    statistic(list, Student::get_classes);
}

/**
 * 统计年龄
 * @param list 单链表
 */
void Statistic::age_statistic(LinkList &list) {
    statistic(list, Student::get_age);
}

/**
 * 统计系别
 * @param list 单链表
 */
void Statistic::dept_statistic(LinkList &list) {
    statistic(list, Student::get_dept);
}