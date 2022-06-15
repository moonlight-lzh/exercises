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
        printf("                图书信息管理系统\n");
        printf("                  1.新增图书\n");
        printf("                  2.删除图书\n");
        printf("                  3.修改图书\n");
        printf("                  4.查询图书\n");
        printf("                  5.浏览图书\n");
        printf("                  0.退出系统\n");
        printf("请选择：");
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
                printf("输入指令错误！\n");
                break;
        }
        system("pause");
    }
    return 0;
}
