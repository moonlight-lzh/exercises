#include "Definitions.h"

/// ��ʾϵͳ���˵�
void ShowMenu();

/// �����������
void WaitContinue();

/// ������
int main() {
    int choice;
    setbuf(stdout, 0);      // ������������

    Manage_Login();     // �û���¼

    do {
        ShowMenu();         // ���˵�
        printf("->");
        scanf("%d", &choice);
        CUTTING_LINE();
        switch (choice) {
            case 1:
                Manage_Input();         // ����ס��
                WaitContinue();
                break;
            case 2:
                Manage_Delete();        // ɾ��ס��
                WaitContinue();
                break;
            case 3:
                Manage_Modify();        // �޸�ס��
                WaitContinue();
                break;
            case 4:
                Manage_Search();        // ��ѯס��
                WaitContinue();
                break;
            case 5:
                Manage_Sort();         //��¥������
                WaitContinue();
                break;
            case 6:
                Manage_Browsing();      // �������ס��
                WaitContinue();
                break;
            case 7:
                Manage_AutoGenPayment();        // �Զ�������ҵ��
                WaitContinue();
                break;
            case 8:
                Manage_Payment();       // �����ɷ�
                WaitContinue();
                break;
            case 9:
                Manage_Statistic();     // ͳ��δ�ɷѻ���
                WaitContinue();
                break;
            case 0:
                printf("ϵͳ�����˳�����л����ʹ�ã�\n");
                break;
            default:
                printf("ָ���쳣��\n");
                break;
        }
    } while (choice);
    return 0;
}

/// �����������
void WaitContinue() {
    printf("�����������...");
    _getch();
}

/// ���˵�
void ShowMenu() {
    system("cls");
    putchar('\n');
    CUTTING_LINE();
    printf("                                    �� �� �� ҵ �� �� �� ϵ ͳ\n\n");
    printf("                                        1.�����ס����Ϣ\n");
    printf("                                        2.ɾ��ס����Ϣ\n");
    printf("                                        3.�޸�ס����Ϣ\n");
    printf("                                        4.��ѯס����Ϣ\n");
    printf("                                        5.��������\n");
    printf("                                        6.���ȫ��ס����Ϣ\n");
    printf("                                        7.�Զ�������ҵ��\n");
    printf("                                        8.�����ɷ�\n");
    printf("                                        9.��¥��ͳ��\n");
    printf("                                        0.�˳�ϵͳ\n");
    CUTTING_LINE();
}
