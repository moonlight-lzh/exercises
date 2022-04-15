#pragma once

#include <unordered_map>
#include "LinkList.h"

/**
 * ͳ����
 */
class Statistic {
private:
    /// unordered hash map
    std::unordered_map<std::string, size_t> umap{};

    /// ��ʾͳ�ƽ��
    void show_result();

    /// ͳ�Ƹ����ֶ�
    void statistic(LinkList &, string(*get_value)(const Student &));
public:

    /// Ĭ�Ϲ��캯��
    Statistic() = default;

    /// ͳ���Ա�
    void gender_statistic(LinkList &);

    /// ͳ�ư༶
    void classes_statistic(LinkList &);

    /// ͳ������
    void age_statistic(LinkList &);

    /// ͳ��ϵ��
    void dept_statistic(LinkList &);
};