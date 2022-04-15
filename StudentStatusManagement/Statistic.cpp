#include "Statistic.h"

/**
 * ��ӡͳ�ƽ��
 */
inline void Statistic::show_result() {
    cout << "------------------------------------- ͳ�ƽ�� -------------------------------------" << endl;

    for (const auto &pair : umap) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }

    cout << "------------------------------------------------------------------------------------" << endl;
}

/**
 * ͳ�Ʋ�ͬ���ֶ�
 * @param list ������
 * @param get_value ��ȡͳ���ֶεĺ���ָ��
 */
void Statistic::statistic(LinkList &list, string(*get_value)(const Student &)) {
    umap.clear();                   // ���ԭʼ����
    if (list.empty()) {             // �����Ƿ�Ϊ��
        return;
    }
    // ѭ��������
    for (const Node *node = list.get_head(); node; node = node->next) {
        // ���ù�ϣ��ͳ��
        if (umap.count(get_value(*node->data))) {
            umap[get_value(*node->data)]++;
        } else {
            umap[get_value(*node->data)] = 1;
        }
    }

    // ��ӡͳ�ƽ��
    show_result();
}

/**
 * ͳ���Ա�
 * @param list ������
 */
void Statistic::gender_statistic(LinkList &list) {
    statistic(list, Student::get_gender);
}

/**
 * ͳ�ư༶
 * @param list ������
 */
void Statistic::classes_statistic(LinkList &list) {
    statistic(list, Student::get_classes);
}

/**
 * ͳ������
 * @param list ������
 */
void Statistic::age_statistic(LinkList &list) {
    statistic(list, Student::get_age);
}

/**
 * ͳ��ϵ��
 * @param list ������
 */
void Statistic::dept_statistic(LinkList &list) {
    statistic(list, Student::get_dept);
}