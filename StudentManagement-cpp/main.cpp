#include <iostream>
#include "Management.h"

using namespace std;

/**
 * ��ӭ
 */
void welcome() {
    Management::parting_line();
    cout << "                              ��ӭ����ѧ��ѧ������ϵͳ                            " << endl;
    Management::parting_line();
    cout << endl;
}

/**
 * ���˵�
 */
void main_menu() {
    Management::parting_line();
    cout << "                             ѧ �� ѧ �� �� �� ϵ ͳ                             " << endl;
    cout << "                                                                               " << endl;
    cout << "                                1 - ¼��ѧ����Ϣ                                " << endl;
    cout << "                                2 - ɾ��ѧ����Ϣ                                " << endl;
    cout << "                                3 - �޸�ѧ����Ϣ                                " << endl;
    cout << "                                4 - ��ѯѧ����Ϣ                                " << endl;
    cout << "                                5 - ͳ��ѧ����Ϣ                                " << endl;
    cout << "                                6 - ���ѧ����Ϣ                                " << endl;
    cout << "                                0 - �˳�ϵͳ                                    " << endl;
    Management::parting_line();
}

/**--------------------------------------- Main Function -------------------------------------*/

/**
 * ������
 * @return
 */
int main() {
    /// ��ʼ��������
    auto *management = new Management();

    /// ��ȡ�����ļ�
    management->read_files();

    /// ��ӭ����
    welcome();

    int option = 0;

    do {
        /// ���˵�
        cin.clear();
        main_menu();

        /// ѡ����
        cin >> option;
        switch (option) {
            case 1:             // ¼��
                management->info_entry();
                break;
            case 2:             // ɾ��
                management->info_delete();
                break;
            case 3:             // �޸�
                management->info_modify();
                break;
            case 4:             // ��ѯ
                management->info_query();
                break;
            case 5:             // ͳ��
                management->info_statistics();
                break;
            case 6:             // ���
                management->info_view();
                break;
            case 0:             // �˳�ϵͳ
                cout << "ϵͳ�������Ƴ�..." << endl;
                break;
            default:
                cout << "����ָ���쳣��" << endl;
                break;
        }
    } while (option);
    /// ɾ��management�ͷſռ�
    delete management;
    system("pause");
    return 0;
}
/**--------------------------------------- Main Function -------------------------------------*/