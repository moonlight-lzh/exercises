#pragma once

#include <unordered_map>
#include "LinkList.h"

/**
 * 统计类
 */
class Statistic {
private:
    /// unordered hash map
    std::unordered_map<std::string, size_t> umap{};

    /// 显示统计结果
    void show_result();

    /// 统计各个字段
    void statistic(LinkList &, string(*get_value)(const Student &));
public:

    /// 默认构造函数
    Statistic() = default;

    /// 统计性别
    void gender_statistic(LinkList &);

    /// 统计班级
    void classes_statistic(LinkList &);

    /// 统计年龄
    void age_statistic(LinkList &);

    /// 统计系别
    void dept_statistic(LinkList &);
};