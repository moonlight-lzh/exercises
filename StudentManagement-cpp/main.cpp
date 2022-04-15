#include <iostream>
#include "Management.h"

using namespace std;

/**
 * 欢迎
 */
void welcome() {
    Management::parting_line();
    cout << "                              欢迎进入学生学籍管理系统                            " << endl;
    Management::parting_line();
    cout << endl;
}

/**
 * 主菜单
 */
void main_menu() {
    Management::parting_line();
    cout << "                             学 生 学 籍 管 理 系 统                             " << endl;
    cout << "                                                                               " << endl;
    cout << "                                1 - 录入学生信息                                " << endl;
    cout << "                                2 - 删除学生信息                                " << endl;
    cout << "                                3 - 修改学生信息                                " << endl;
    cout << "                                4 - 查询学生信息                                " << endl;
    cout << "                                5 - 统计学生信息                                " << endl;
    cout << "                                6 - 浏览学生信息                                " << endl;
    cout << "                                0 - 退出系统                                    " << endl;
    Management::parting_line();
}

/**--------------------------------------- Main Function -------------------------------------*/

/**
 * 主函数
 * @return
 */
int main() {
    /// 初始化管理类
    auto *management = new Management();

    /// 读取数据文件
    management->read_files();

    /// 欢迎界面
    welcome();

    int option = 0;

    do {
        /// 主菜单
        cin.clear();
        main_menu();

        /// 选择功能
        cin >> option;
        switch (option) {
            case 1:             // 录入
                management->info_entry();
                break;
            case 2:             // 删除
                management->info_delete();
                break;
            case 3:             // 修改
                management->info_modify();
                break;
            case 4:             // 查询
                management->info_query();
                break;
            case 5:             // 统计
                management->info_statistics();
                break;
            case 6:             // 浏览
                management->info_view();
                break;
            case 0:             // 退出系统
                cout << "系统化即将推出..." << endl;
                break;
            default:
                cout << "输入指令异常。" << endl;
                break;
        }
    } while (option);
    /// 删除management释放空间
    delete management;
    system("pause");
    return 0;
}
/**--------------------------------------- Main Function -------------------------------------*/