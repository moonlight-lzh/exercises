#include "Management.h"
#include "Statistic.h"

/**
 * ���캯��
 */
Management::Management() {
    list = new LinkList();                      // ����������
    statistic = new Statistic();                // ����ͳ����
}

/**
 * ��������
 */
Management::~Management() {
    delete list;
    delete statistic;
}

/**
 * ��ȡ�����ļ�
 */
void Management::read_files() {
    ifstream ifs;
    ifs.open(filename, ios::in);
    if (!ifs.is_open()) {
        cout << "��ȡѧ����Ϣ�����ļ�[" << filename << "]ʧ�ܣ�" << endl;
        return;
    }
    while (!ifs.eof()) {
        auto *s = new Student();      // ����ѧ��ָ��
        ifs >> *s;                      // ��ȡ�ļ�����
        list->append(s);                // ��������
    }

    ifs.close();                        // �ر��ļ���
}

/**
 * ���������ļ�
 */
void Management::write_files() {
    ofstream ofs;
    ofs.open(filename, ios::out | ios::trunc);              // ���ļ�
    for (const Node *node = list->get_head(); node; node = node->next) {
        ofs << *node->data;            // ѧ����Ϣд���ļ���
    }
    ofs.close();                    // �ر��ļ���
}

/**
 * ��Ϣ¼��
 */
void Management::info_entry() {
    cout << "�����룺ѧ�� ���� �Ա� ���� ��� רҵ ϵ��" << endl;

    auto *s = new Student();
    cin >> *s;                      // ����ѧ����Ϣ

    if (list->exist(s->number, Student::cmp_number)) {
        cout << "���������ѧ���Ѵ��ڣ��޷�¼�������Ϣ��" << endl;
        delete s;
        return;
    }
    if (list->exist(s->name, Student::cmp_name)) {
        cout << "���������ѧ���Ѵ��ڣ��޷�¼�������Ϣ��" << endl;
        delete s;
        return;
    }
    if (!check_gender(s->gender)) {
        cout << "����������Ա��ʽ�����޷�¼�������Ϣ��" << endl;
        delete s;
        return;
    }
    if (!check_age(s->age)) {
        cout << "��������������ʽ�����޷�¼�������Ϣ��" << endl;
        delete s;
        return;
    }

    list->append(s);                    // ��������
    write_files();                      // ¼��ɹ��������ļ�
    cout << "ѧ����Ϣ¼��ɹ���" << endl;
}

/**
 * ��Ϣ�޸�
 */
void Management::info_modify() {
    string str;
    Student *stu;
    int which;

    cout << "������ѧ�ţ�" << endl;
    cin >> str;

    stu = list->find_first(str, Student::cmp_number);
    if (stu == nullptr) {
        cout << "δ��ѯ���κ�ѧ����Ϣ��" << endl;
        return;
    }

    cout << "��ѡ���޸����ݣ�" << endl;
    cout << "1.ѧ��" << endl;
    cout << "2.����" << endl;
    cout << "3.�Ա�" << endl;
    cout << "4.����" << endl;
    cout << "5.���" << endl;
    cout << "6.רҵ" << endl;
    cout << "7.ϵ��" << endl;
    cout << "0.����" << endl;
    cin >> which;

    cout << "�������޸ĵ�Ŀ��ֵ��" << endl;
    cin >> str;

    switch (which) {
        case 1:
            if (list->exist(str, Student::cmp_number)) {
                cout << "���������ѧ���Ѵ��ڣ��޷��޸ģ�" << endl;
                return;
            }
            stu->number = str;              // �޸�ѧ��
            break;

        case 2:
            if (list->exist(str, Student::cmp_name)) {
                cout << "��������������Ѵ��ڣ��޷��޸ģ�" << endl;
                return;
            }
            stu->name = str;                // �޸�����
            break;
        case 3:
            if (!check_gender(str)) {
                cout << "����������Ա��ʽ�����޷��޸ģ�" << endl;
                return;
            }
            stu->gender = str;              // �޸��Ա�
            break;
        case 4:
            if (!check_age(str)) {
                cout << "��������������ʽ�����޷��޸ģ�" << endl;
                return;
            }
            stu->age = str;                    // �޸�����
            break;
        case 5:
            stu->classes = str;             // �޸İ༶
            break;
        case 6:
            stu->major = str;               // �޸�רҵ
            break;
        case 7:
            stu->dept = str;                // �޸�ϵ��
            break;
        case 0:
            return;
        default :
            cout << "����ָ���쳣���޸�ʧ�ܣ�" << endl;
            break;
    }
    write_files();                      // �޸ĳɹ��������ļ�
    cout << "ѧ����Ϣ�޸ĳɹ���" << endl;
}

/**
 * ��Ϣɾ��
 */
void Management::info_delete() {
    string str;
    cout << "������ѧ�ţ�" << endl;
    cin >> str;
    bool success = list->delete_first(str, Student::cmp_number);            // ����ѧ��ɾ�����
    if (!success) {
        cout << "�����ڸ�����Ϣ��ɾ��ʧ�ܣ�" << endl;
    } else {
        write_files();                          // ɾ���ɹ��������ļ�
        cout << "ѧ����Ϣɾ���ɹ���" << endl;
    }
}

/**
 * ��Ϣ��ѯ
 */
void Management::info_query() {
    int which;
    string str;
    vector<Student *> result;
    Student *stu;

    cout << "��ѡ���ѯ������" << endl;
    cout << "1.ѧ��" << endl;
    cout << "2.����" << endl;
    cout << "3.�Ա�" << endl;
    cout << "4.���" << endl;
    cout << "5.רҵ" << endl;
    cout << "6.ϵ��" << endl;
    cout << "0.����" << endl;
    cin >> which;

    cout << "�������ѯ���ݣ�" << endl;
    cin >> str;

    switch (which) {
        case 1:
        case 2:
            stu = list->find_first(str, which == 1 ? Student::cmp_number : Student::cmp_name);          // ��ѯѧ�Ż�����
            if (stu) {
                result.push_back(stu);
            }
            break;
        case 3:
            list->find_all(str, result, Student::cmp_gender);               // �����Ա�
            break;
        case 4:
            list->find_all(str, result, Student::cmp_classes);              // ���Ұ༶
            break;
        case 5:
            list->find_all(str, result, Student::cmp_major);                // ����רҵ
            break;
        case 6:
            list->find_all(str, result, Student::cmp_dept);                 // ����ϵ��
            break;
        case 0:
            return;
        default:
            cout << "����ָ���쳣��" << endl;
            return;
    }

    if (result.empty()) {
        cout << "δ��ѯ���κ�ѧ����Ϣ��" << endl;
        return;
    }

    // ��ӡ��ѯ���
    Student::show_title();
    for (auto &item : result) {
        cout << *item;
    }
}

/**
 * ��Ϣͳ��
 */
void Management::info_statistics() {
    int option;

    cout << "��ѡ��ͳ�����ͣ�" << endl;
    cout << "1.�Ա�" << endl;
    cout << "2.���" << endl;
    cout << "3.����" << endl;
    cout << "4.ϵ��" << endl;
    cout << "0.����" << endl;

    cin >> option;

    switch (option) {
        case 1:
            statistic->gender_statistic(*list);            // ͳ���Ա�
            break;
        case 2:
            statistic->classes_statistic(*list);           // ͳ�ư༶
            break;
        case 3:
            statistic->age_statistic(*list);               // ͳ������
            break;
        case 4:
            statistic->dept_statistic(*list);              // ͳ��ϵ��
            break;
        case 0:
            break;
        default:
            cout << "����ָ���쳣��" << endl;
            break;
    }
}

/**
 * ��Ϣ���
 */
void Management::info_view() {
    parting_line();
    Student::show_title();
    list->show_all();               // ��ʾ���е�ѧ����Ϣ
}

/**
 * ����Ա��ַ����Ƿ�Ϸ�
 * @param str �ַ���
 * @return true���Ϸ���false�����Ϸ�
 */
bool Management::check_gender(const string &str) {
    return str == "��" || str == "Ů";
}

/**
 * ��������ַ����Ƿ�Ϸ�
 * @param str �ַ���
 * @return true���Ϸ���false�����Ϸ�
 */
bool Management::check_age(const string &str) {
    if (str.empty()) {
        return false;
    }
    int res = 0;
    for (char ch : str) {
        if ('0' <= ch && ch <= '9') {
            res = res * 10 + ch - '0';
            if (res > 150) {
                return false;
            }
        } else {
            return false;
        }
    }
    return res > 0 && res < 150;
}

/**
 * ��ӡ�ָ���
 */
void Management::parting_line() {
    cout << "-------------------------------------------------------------------------------" << endl;
}