#include "Definitions.h"

/// 显示系统主菜单
void ShowMenu();

/// 按任意键继续
void WaitContinue();

/// 主函数
int main() {
    int choice;
    setbuf(stdout, 0);      // 清空输出缓冲区

    Manage_Login();     // 用户登录

    do {
        ShowMenu();         // 主菜单
        printf("->");
        scanf("%d", &choice);
        CUTTING_LINE();
        switch (choice) {
            case 1:
                Manage_Input();         // 新增住户
                WaitContinue();
                break;
            case 2:
                Manage_Delete();        // 删除住户
                WaitContinue();
                break;
            case 3:
                Manage_Modify();        // 修改住户
                WaitContinue();
                break;
            case 4:
                Manage_Search();        // 查询住户
                WaitContinue();
                break;
            case 5:
                Manage_Sort();         //按楼号排序
                WaitContinue();
                break;
            case 6:
                Manage_Browsing();      // 浏览所有住户
                WaitContinue();
                break;
            case 7:
                Manage_AutoGenPayment();        // 自动生成物业费
                WaitContinue();
                break;
            case 8:
                Manage_Payment();       // 户主缴费
                WaitContinue();
                break;
            case 9:
                Manage_Statistic();     // 统计未缴费户主
                WaitContinue();
                break;
            case 0:
                printf("系统即将退出，感谢您的使用！\n");
                break;
            default:
                printf("指令异常！\n");
                break;
        }
    } while (choice);
    return 0;
}

/// 按任意键继续
void WaitContinue() {
    printf("按任意键继续...");
    _getch();
}

/// 主菜单
void ShowMenu() {
    system("cls");
    putchar('\n');
    CUTTING_LINE();
    printf("                                    社 区 物 业 费 管 理 系 统\n\n");
    printf("                                        1.添加新住户信息\n");
    printf("                                        2.删除住户信息\n");
    printf("                                        3.修改住户信息\n");
    printf("                                        4.查询住户信息\n");
    printf("                                        5.排序后浏览\n");
    printf("                                        6.浏览全部住户信息\n");
    printf("                                        7.自动生成物业费\n");
    printf("                                        8.户主缴费\n");
    printf("                                        9.按楼号统计\n");
    printf("                                        0.退出系统\n");
    CUTTING_LINE();
}
