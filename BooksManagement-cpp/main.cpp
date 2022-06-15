#include "Book.h"

using namespace std;

int main() {
    int choice;
    DoBook dao;
    setbuf(stdout, nullptr);
    system("color F0");
    dao.init();

    while (true) {
        system("cls");
        printf("                ͼ����Ϣ����ϵͳ\n");
        printf("                  1.����ͼ��\n");
        printf("                  2.ɾ��ͼ��\n");
        printf("                  3.�޸�ͼ��\n");
        printf("                  4.��ѯͼ��\n");
        printf("                  5.���ͼ��\n");
        printf("                  0.�˳�ϵͳ\n");
        printf("��ѡ��");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                dao.insert_onebook();
                break;
            case 2:
                dao.delete_onebook();
                break;
            case 3:
                dao.modify_onebook();
                break;
            case 4:
                dao.select_onbook();
                break;
            case 5:
                dao.display_allbook();
                break;
            case 0:
                return 0;
            default:
                printf("����ָ�����\n");
                break;
        }
        system("pause");
    }
    return 0;
}
