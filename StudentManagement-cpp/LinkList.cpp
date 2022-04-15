#include "LinkList.h"

/**
 * ��������
 */
LinkList::~LinkList() {
    for (size_t i = 0; i < size; ++i) {
        Node *node = this->head;
        this->head = this->head->next;
        delete node->data;
        delete node;
    }
}

/**
 * ��ȡ����ͷ���
 * @return �����ͷ���
 */
const Node *LinkList::get_head() {
    return this->head;
}

/**
 * �����Ƿ�Ϊ��
 * @return true������Ϊ�գ�false������Ϊ��
 */
bool LinkList::empty() {
    return size == 0;
}

/**
 * �������ݵ�����β��
 * @param data ѧ��ָ��
 */
void LinkList::append(Student *data) {
    if (empty()) {
        this->head = this->tail = new Node(data, nullptr);
    } else {
        tail->next = new Node(data, tail->next);
        tail = tail->next;
    }
    size++;
}

/**
 * ɾ����һ��ƥ��Ľ��
 * @param str �ַ���
 * @param cmp �ȽϺ���ָ��
 * @return
 */
bool LinkList::delete_first(const string &str, bool  (*cmp)(const Student &, const string &)) {
    if (empty()) {
        return false;
    }

    Node *node = nullptr;               // ��ɾ�����
    if (cmp(*head->data, str)) {
        node = head;                    // ɾ��ͷ���
        head = head->next;
    } else {
        Node *pre = nullptr;                // ��ɾ������ǰ�ý��
        for (Node *p = head; p && p->next; p = p->next) {
            if (cmp(*p->next->data, str)) {
                pre = p;
                break;
            }
        }

        if (pre == nullptr) {
            return false;
        }

        if (pre->next == tail) {            // ��ɾ�����Ϊ��ǰ�����β���
            node = tail;
            tail = pre;
        } else {
            node = pre->next;
            pre->next = node->next;
        }
    }

    delete node->data;
    delete node;
    size--;
    return true;
}

/**
 * ��ѯ��һ��ƥ��Ľ��
 * @param str �ַ���
 * @param cmp �ȽϺ���ָ��
 * @return ѧ��ָ��
 */
Student *LinkList::find_first(const string &str, bool  (*cmp)(const Student &, const string &)) {
    for (const Node *p = head; p; p = p->next) {
        if (cmp(*p->data, str)) {
            return p->data;
        }
    }
    return nullptr;
}

/**
 * ��������ƥ��Ľ��
 * @param str �ַ���
 * @param find ���ҵĽ������
 * @param cmp �ȽϺ���ָ��
 */
void LinkList::find_all(const string &str, vector<Student *> &find, bool (*cmp)(const Student &, const string &)) {
    for (const Node *p = head; p; p = p->next) {
        if (cmp(*p->data, str)) {
            find.push_back(p->data);
        }
    }
}

/**
 * �ж�ָ�����ݵĽ���Ƿ����
 * @param str �ַ���
 * @param cmp �ȽϺ���ָ��
 * @return
 */
bool LinkList::exist(const string &str, bool  (*cmp)(const Student &, const string &)) {
    return find_first(str, cmp) != nullptr;
}

/**
 * ��ӡ��ʾ���еĽ����Ϣ
 */
void LinkList::show_all() {
    if (empty()) {
        return;
    }
    Node *p = head;
    while (p) {
        std::cout << *(p->data);
        p = p->next;
    }
}