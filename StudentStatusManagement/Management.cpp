#include "Management.h"
#include "Statistic.h"

/**
 * 构造函数
 */
Management::Management() {
    list = new LinkList();                      // 创建单链表
    statistic = new Statistic();                // 创建统计类
}

/**
 * 析构函数
 */
Management::~Management() {
    delete list;
    delete statistic;
}

/**
 * 读取数据文件
 */
void Management::read_files() {
    ifstream ifs;
    ifs.open(filename, ios::in);
    if (!ifs.is_open()) {
        cout << "读取学生信息，打开文件[" << filename << "]失败！" << endl;
        return;
    }
    while (!ifs.eof()) {
        auto *s = new Student();      // 创建学生指针
        ifs >> *s;                      // 读取文件内容
        list->append(s);                // 插入链表
    }

    ifs.close();                        // 关闭文件流
}

/**
 * 保存数据文件
 */
void Management::write_files() {
    ofstream ofs;
    ofs.open(filename, ios::out | ios::trunc);              // 打开文件
    for (const Node *node = list->get_head(); node; node = node->next) {
        ofs << *node->data;            // 学生信息写入文件流
    }
    ofs.close();                    // 关闭文件流
}

/**
 * 信息录入
 */
void Management::info_entry() {
    cout << "请输入：学号 姓名 性别 年龄 班号 专业 系别" << endl;

    auto *s = new Student();
    cin >> *s;                      // 输入学生信息

    if (list->exist(s->number, Student::cmp_number)) {
        cout << "您所输入的学号已存在，无法录入该生信息！" << endl;
        delete s;
        return;
    }
    if (list->exist(s->name, Student::cmp_name)) {
        cout << "您所输入的学号已存在，无法录入该生信息！" << endl;
        delete s;
        return;
    }
    if (!check_gender(s->gender)) {
        cout << "您所输入的性别格式错误，无法录入该生信息！" << endl;
        delete s;
        return;
    }
    if (!check_age(s->age)) {
        cout << "您所输入的年龄格式错误，无法录入该生信息！" << endl;
        delete s;
        return;
    }

    list->append(s);                    // 插入链表
    write_files();                      // 录入成功，保存文件
    cout << "学生信息录入成功！" << endl;
}

/**
 * 信息修改
 */
void Management::info_modify() {
    string str;
    Student *stu;
    int which;

    cout << "请输入学号：" << endl;
    cin >> str;

    stu = list->find_first(str, Student::cmp_number);
    if (stu == nullptr) {
        cout << "未查询到任何学生信息。" << endl;
        return;
    }

    cout << "请选择修改内容：" << endl;
    cout << "1.学号" << endl;
    cout << "2.姓名" << endl;
    cout << "3.性别" << endl;
    cout << "4.年龄" << endl;
    cout << "5.班号" << endl;
    cout << "6.专业" << endl;
    cout << "7.系别" << endl;
    cout << "0.返回" << endl;
    cin >> which;

    cout << "请输入修改的目标值：" << endl;
    cin >> str;

    switch (which) {
        case 1:
            if (list->exist(str, Student::cmp_number)) {
                cout << "您所输入的学号已存在，无法修改！" << endl;
                return;
            }
            stu->number = str;              // 修改学号
            break;

        case 2:
            if (list->exist(str, Student::cmp_name)) {
                cout << "您所输入的姓名已存在，无法修改！" << endl;
                return;
            }
            stu->name = str;                // 修改姓名
            break;
        case 3:
            if (!check_gender(str)) {
                cout << "您所输入的性别格式错误，无法修改！" << endl;
                return;
            }
            stu->gender = str;              // 修改性别
            break;
        case 4:
            if (!check_age(str)) {
                cout << "您所输入的年龄格式错误，无法修改！" << endl;
                return;
            }
            stu->age = str;                    // 修改年龄
            break;
        case 5:
            stu->classes = str;             // 修改班级
            break;
        case 6:
            stu->major = str;               // 修改专业
            break;
        case 7:
            stu->dept = str;                // 修改系别
            break;
        case 0:
            return;
        default :
            cout << "输入指令异常，修改失败！" << endl;
            break;
    }
    write_files();                      // 修改成功，保存文件
    cout << "学生信息修改成功。" << endl;
}

/**
 * 信息删除
 */
void Management::info_delete() {
    string str;
    cout << "请输入学号：" << endl;
    cin >> str;
    bool success = list->delete_first(str, Student::cmp_number);            // 根据学号删除结点
    if (!success) {
        cout << "不存在该生信息，删除失败！" << endl;
    } else {
        write_files();                          // 删除成功，保存文件
        cout << "学生信息删除成功！" << endl;
    }
}

/**
 * 信息查询
 */
void Management::info_query() {
    int which;
    string str;
    vector<Student *> result;
    Student *stu;

    cout << "请选择查询条件：" << endl;
    cout << "1.学号" << endl;
    cout << "2.姓名" << endl;
    cout << "3.性别" << endl;
    cout << "4.班号" << endl;
    cout << "5.专业" << endl;
    cout << "6.系别" << endl;
    cout << "0.返回" << endl;
    cin >> which;

    cout << "请输入查询内容：" << endl;
    cin >> str;

    switch (which) {
        case 1:
        case 2:
            stu = list->find_first(str, which == 1 ? Student::cmp_number : Student::cmp_name);          // 查询学号或姓名
            if (stu) {
                result.push_back(stu);
            }
            break;
        case 3:
            list->find_all(str, result, Student::cmp_gender);               // 查找性别
            break;
        case 4:
            list->find_all(str, result, Student::cmp_classes);              // 查找班级
            break;
        case 5:
            list->find_all(str, result, Student::cmp_major);                // 查找专业
            break;
        case 6:
            list->find_all(str, result, Student::cmp_dept);                 // 查找系别
            break;
        case 0:
            return;
        default:
            cout << "输入指令异常！" << endl;
            return;
    }

    if (result.empty()) {
        cout << "未查询到任何学生信息。" << endl;
        return;
    }

    // 打印查询结果
    Student::show_title();
    for (auto &item : result) {
        cout << *item;
    }
}

/**
 * 信息统计
 */
void Management::info_statistics() {
    int option;

    cout << "请选择统计类型：" << endl;
    cout << "1.性别" << endl;
    cout << "2.班号" << endl;
    cout << "3.年龄" << endl;
    cout << "4.系别" << endl;
    cout << "0.返回" << endl;

    cin >> option;

    switch (option) {
        case 1:
            statistic->gender_statistic(*list);            // 统计性别
            break;
        case 2:
            statistic->classes_statistic(*list);           // 统计班级
            break;
        case 3:
            statistic->age_statistic(*list);               // 统计年龄
            break;
        case 4:
            statistic->dept_statistic(*list);              // 统计系别
            break;
        case 0:
            break;
        default:
            cout << "输入指令异常！" << endl;
            break;
    }
}

/**
 * 信息浏览
 */
void Management::info_view() {
    parting_line();
    Student::show_title();
    list->show_all();               // 显示所有的学生信息
}

/**
 * 检查性别字符串是否合法
 * @param str 字符串
 * @return true：合法，false：不合法
 */
bool Management::check_gender(const string &str) {
    return str == "男" || str == "女";
}

/**
 * 检查年龄字符串是否合法
 * @param str 字符串
 * @return true：合法，false：不合法
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
 * 打印分隔符
 */
void Management::parting_line() {
    cout << "-------------------------------------------------------------------------------" << endl;
}