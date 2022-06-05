#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// 学生信息结构体
struct Student
{
    // 学生学号
    int num = 0;

    // 学生姓名
    string name;

    // 成绩向量
    vector<float> scores;

    // 打印学生信息
    void print()
    {
        cout << num << "\t\t" << name;
        for (auto const& x : scores)
        {
            cout << "\t\t" << x;
        }
        cout << endl;
    }
};

// 链表结点结构体
struct LNode
{
    // 数据域
    Student student;

    // 指针域
    LNode* next = nullptr;
};

// 课程结构体
struct Course
{
private:
    // 课程文件名称
    const string COURSE_FILE = "课程.txt";

public:
    // 课程向量
    vector<string> names;

    // 读取课程文件中的数据，生成向量
    void read_file()
    {
        ifstream is(COURSE_FILE, ios::in); // 只读方式打开文件
        if (!is)
        {
            return;
        }
        names.clear(); // 清除所有课程

        string line;
        while (getline(is, line))
        {
            names.push_back(line);          // 从文件读取每一行课程名称，并添加到向量中
        }
        is.close(); // 关闭文件
    }

    // 将课程向量中的每个课程名称写入文件
    bool write_file()
    {
        ofstream os(COURSE_FILE, ios::out);         // 只写的方式打开文件
        if (!os)
        {
            cerr << "无法打开文件 '" << COURSE_FILE << '\'' << endl;
            return false;
        }

        for (const auto& line : names)       // 循环每个课程名，写入文件每一行
        {
            os << line << endl;
        }
        os.close(); // 关闭文件
        return true;
    }

    // 判断课程名称是否存在
    bool check_course_exist(const string& name)
    {
        for (const auto& x : names)
        {
            if (x == name)
            {
                return true;
            }
        }
        return false;
    }

    // 获取课程名的索引
    int get_index(const string& name)
    {
        for (size_t i = 0; i < names.size(); i++)
        {
            if (names[i] == name)
            {
                return i;
            }
        }
        return -1;
    }
};

// 按任意键继续
void wait_to_continue();

// 显示系统主菜单
int show_menu();

// 显示课程管理菜单
int show_courses_menu();

// 显示成绩管理菜单
int show_scores_menu();

// 显示统计菜单
int show_statistic_menu();

// 链表类
struct LinkedList
{
private:
    // 学生成绩文件名称
    const string SCORES_FILE = "学生成绩.txt";

    // 链表头结点
    LNode* _head;

    // 链表尾结点
    LNode* _tail;

public:
    // 构造函数
    LinkedList()
    {
        _head = _tail = nullptr;
    }

    // 析构函数
    ~LinkedList()
    {
        LNode* tmp;
        while (_head)
        {
            tmp = _head;
            _head = _head->next;
            delete tmp;          // 释放链表结点
        }
        _head = _tail = nullptr;
    }

    // 获取链表头结点
    LNode* get_head()
    {
        return this->_head;
    }

    // 添加链表结点
    void append_node(Student& stu)
    {
        auto* node = new LNode();       // 创建结点
        node->student = stu;
        node->next = nullptr;

        if (!_tail)
        {
            _head = _tail = node;
        }
        else
        {
            _tail->next = node;      // 尾插法
            _tail = node;
        }
    }

    // 根据学生编号删除结点
    bool remove_node(int num)
    {
        if (_head == nullptr)
        {
            return false;
        }

        LNode* node, * temp;
        if (_head->student.num == num)      // 头结点为待删除学生结点
        {
            node = _head;
            _head = _head->next;
            delete node;
            return true;
        }

        node = _head;
        while (node->next && node->next->student.num != num)     // 查找删除结点的前一个结点
        {
            node = node->next;
        }

        if (node->next == nullptr)
        {
            return false;
        }

        temp = node->next;
        node->next = temp->next; // 修改指针移除链表结点

        if (temp == _tail)
        {
            _tail = node; // 删除尾结点后，更新尾结点指针
        }

        delete temp; // 释放结点
        return true;
    }

    // 根据学号查询链表结点，查询结果存放到向量中
    vector<LNode*> search_node_by_num(int num)
    {
        vector<LNode*> ans;
        auto node = _head;

        while (node)
        {
            if (node->student.num == num)           // 判断学号是否相等
            { 
                ans.push_back(node);
                break;
            }
            node = node->next;
        }
        return ans;
    }

    // 根据姓名查询链表结点，查询结果存放到向量中
    vector<LNode*> search_node_by_name(const string& name)
    {
        vector<LNode*> ans;
        auto node = _head;

        while (node)
        {
            if (node->student.name == name)          // 判断姓名是否相等
            {
                ans.push_back(node);
            }
            node = node->next;
        }
        return ans;
    }

    // 根据学号查询链表结点
    LNode* search_node(int num)
    {
        auto ans = search_node_by_num(num);
        if (ans.empty())
        {
            return nullptr;
        }
        return ans.front();
    }

    // 读取成绩文件中的数据，生成链表
    void read_file()
    {
        ifstream is(SCORES_FILE, ios::in); // 只读方式打开文件
        if (!is)
        {
            return;
        }
        string line;
        while (getline(is, line))    // 读取文件每一行
        {
            // 处理，去掉字符串末尾的空白
            while (!line.empty() && isspace(line.back()))
            {
                line.pop_back();
            }
            if (line.empty())           // 跳过空行
            { 
                continue;       
            }

            istringstream iss(line);
            Student stu;

            // 读取学生的学号、姓名、各科成绩
            iss >> stu.num >> stu.name;
            float score;
            while (iss >> score)
            {
                stu.scores.push_back(score);
            }
            // 添加到链表中
            append_node(stu);
        }
        is.close(); // 关闭文件
    }

    // 将链表中的成绩数据写入文件
    bool write_file()
    {
        ofstream os(SCORES_FILE, ios::out); // 只写方式打开文件
        if (!os)
        {
            cerr << "无法打开文件 '" << SCORES_FILE << '\'' << endl;
            return false;
        }

        // 循环链表中的每个结点，将学号、姓名、各科成绩写入文件
        auto node = _head;
        while (node)
        {
            os << node->student.num << '\t';
            os << node->student.name << '\t';

            for (size_t i = 0; i < node->student.scores.size(); ++i)
            {
                os << node->student.scores[i];
                if (i == node->student.scores.size() - 1)
                {
                    os << endl;
                }
                else
                {
                    os << '\t';
                }
            }
            node = node->next;
        }
        os.close(); // 关闭文件
        return true;
    }
};

// 管理类
class Manage
{
    // 链表
    LinkedList list;

    // 课程
    Course course;

public:
    // 打印标题
    void print_titles()
    {
        cout << "学号\t\t姓名";
        for (size_t i = 0; i < course.names.size(); i++)
        {
            cout << "\t\t" << course.names[i];
        }
        cout << endl;
    }

    // 读取所有文件的信息
    void read_files()
    {
        course.read_file();

        list.read_file();
    }

    // 添加课程
    void add_course()
    {
        string name;
        cout << "请输入新增课程名称：" << endl;
        cin >> name;

        // 检查输入课程是否存在
        if (course.check_course_exist(name))
        {
            cout << "您输入的课程名称已存在，无需重复添加！" << endl;
            return;
        }

        // 新课程添加到向量中，并保存文件
        course.names.push_back(name);
        course.write_file();

        if (list.get_head())
        {
            // 修改链表结点的成绩
            cout << "请依次补充所有学生的新增课程成绩：" << endl;
            auto* node = list.get_head();
            float score;
            while (node)
            {
                cout << "输入" << node->student.name << "[" << node->student.num
                    << "]的" << name << "成绩：" << endl;
                cin >> score;
                node->student.scores.push_back(score);
                node = node->next;
            }
            // 保存成绩文件
            list.write_file();
        }

        cout << "新增课程成功！" << endl;
    }

    // 删除课程
    void delete_course()
    {
        string name;
        cout << "请输入删除课程名称：" << endl;
        cin >> name;
        int pos;

        // 判断输入的课程是否存在
        pos = course.get_index(name);
        if (pos < 0)
        {
            cout << "您输入的课程不存在！" << endl;
            return;
        }

        course.names.erase(course.names.begin() + pos);     // 删除课程
        course.write_file();                                // 保存课程文件

        // 删除链表结点的成绩
        auto* node = list.get_head();
        while (node)
        {
            node->student.scores.erase(node->student.scores.begin() +  pos); // 删除每个学生pos处的成绩
            node = node->next;
        }

        // 保存文件
        list.write_file();
        cout << "删除课程成功！" << endl;
    }

    // 修改课程
    void modify_course()
    {
        string name, new_name;
        cout << "请输入修改课程名称：" << endl;
        cin >> name;
        int pos;

        // 判断输入的课程是否存在
        pos = course.get_index(name);
        if (pos < 0)
        {
            cout << "您输入的课程不存在！" << endl;
            return;
        }

        // 验证修改后的课程名是否存在
        cout << "请输入修改后的课程名：" << endl;
        cin >> new_name;
        if (course.check_course_exist(new_name))
        {
            cout << "您输入的目标课程名已存在！";
            return;
        }

        // 修改课程名，并保存文件
        course.names[pos] = new_name;
        course.write_file();
        cout << "修改课程成功！" << endl;
    }

    // 查询课程
    void query_course()
    {
        cout << "当前课程列表：" << endl;
        for (const auto& x : course.names)
        {
            cout << x << endl;
        }
    }

    // 添加学生
    void add_student()
    {
        Student stu;
        cout << "请输入新增学生信息：" << endl;
        cout << "学号：";
        cin >> stu.num;

        // 检查新增学生的学号是否存在
        if (list.search_node(stu.num))
        {
            cout << "该学号已存在，无法新增！" << endl;
            return;
        }

        // 输入各项内容
        cout << "姓名：";
        cin >> stu.name;
        float score;
        for (size_t i = 0; i < course.names.size(); i++)
        {
            cout << course.names[i] << "成绩：";
            cin >> score;
            stu.scores.push_back(score);
        }

        // 添加链表节点
        list.append_node(stu);

        // 保存学生成绩文件
        list.write_file();
        cout << "新增成功！" << endl;
    }

    // 删除学生
    void delete_student()
    {
        int num;
        cout << "请输入需要删除学生的学号：";
        cin >> num;

        // 判断输入的学号是否存在
        auto node = list.search_node(num);
        if (node == nullptr)
        {
            cout << "不存在该学生信息！" << endl;
            return;
        }

        node->student.print();

        cout << "请再次确认，是否删除该条记录？（Y/N）\n->";

        char confirm;
        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y')
        {
            // 删除链表结点
            list.remove_node(num);

            // 保存学生成绩文件
            list.write_file();
            cout << "删除成功！" << endl;
        }
    }

    // 修改学生信息
    void modify_student()
    {
        int num;
        cout << "请输入待修改学生的学号：" << endl;
        cin >> num;

        // 判断输入的学生是否存在
        auto node = list.search_node(num);
        if (node == nullptr)
        {
            cout << "不存在该学生信息！" << endl;
            return;
        }

        // 选择修改条件
        size_t choice;
        cout << "请选择修改内容" << endl;
        cout << "1.学号\t\t2.姓名" << endl;
        for (size_t i = 0; i < course.names.size(); ++i)
        {
            cout << i + 3 << '.' << course.names[i] << "成绩" << '\t';
            if ((i + 1) % 3 == 0)
            {
                cout << endl;
            }
        }
        cout << "0.取消修改" << endl;
        cout << "->";
        cin >> choice;

        // 按选择的条件修改值
        if (choice == 1)
        {
            int val;
            cout << "请输入修改后的学号：";
            cin >> val;

            // 修改学号的时候，判断修改后的学号是否存在，保证学号唯一性
            if (list.search_node(val))
            {
                cout << "该学号已存在，无法修改！" << endl;
                return;
            }
            node->student.num = val;
        }
        else if (choice == 2)
        {
            cout << "请输入修改后的姓名：";
            cin >> node->student.name;
        }
        else if (choice >= 3 && choice <= course.names.size() + 2)
        {
            cout << "请输入修改后的" << course.names[choice - 3] << "成绩：";
            cin >> node->student.scores[choice - 3];
        }
        else
        {
            return;
        }

        // 修改成功，保存文件
        list.write_file();
        cout << "修改成功！" << endl;
    }

    // 查询学生信息
    void query_student()
    {
        cout << "    1.按学号查询" << endl;
        cout << "    2.按姓名查询" << endl;
        cout << "    0.返回" << endl;
        cout << "请选择：";
        int choice;
        int num;
        string name;
        cin >> choice;
        vector<LNode*> ans;

        // 按条件查询并返回结果
        if (choice == 1)
        {
            cout << "请输入查询的学号：";
            cin >> num;
            ans = list.search_node_by_num(num);
        }
        else if (choice == 2)
        {
            cout << "请输入查询的姓名：";
            cin >> name;
            ans = list.search_node_by_name(name);
        }
        else
        {
            return;
        }
        if (ans.empty())
        {
            cout << "查询结果为空！" << endl;
            return;
        }

        // 打印显示所有学生信息
        print_titles();
        for (auto const node : ans)
        {
            node->student.print();
        }
    }

    // 统计某个学生成绩
    void statistic_single()
    {
        int num;
        cout << "请输入待统计学生的学号：" << endl;
        cin >> num;

        // 判断输入的学生是否存在
        auto node = list.search_node(num);
        if (node == nullptr || node->student.scores.empty())
        {
            cout << "不存在该学生信息，无法统计！" << endl;
            return;
        }

        float average = node->student.scores[0];
        int imax = 0, imin = 0;

        // 统计该学生各科成绩的平均分、最高分、最低分
        for (size_t i = 1; i < node->student.scores.size(); i++)
        {
            if (node->student.scores[i] > node->student.scores[imax])
            {
                imax = i;
            }
            if (node->student.scores[i] < node->student.scores[imin])
            {
                imin = i;
            }
            average += node->student.scores[i];
        }
        average /= node->student.scores.size();

        cout << "学号：" << node->student.num << endl;
        cout << "姓名：" << node->student.name << endl;
        cout << "平均分：" << average << endl;
        cout << "最高分：" << node->student.scores[imax] << endl;
        cout << "最低分：" << node->student.scores[imin] << endl;
    }

    // 统计所有成绩
    void statistic_all()
    {
        auto node = list.get_head();
        int student_size = 0;
        auto n = course.names.size();
        vector<float> total(n, 0); // 每个科目的总分向量
        vector<float> max(n, -1);  // 每个科目的最高分向量
        vector<float> min(n, -1);  // 每个科目的最低分向量
        while (node)
        {
            for (size_t i = 0; i < n; i++)
            {
                total[i] += node->student.scores[i];
                if (max[i] < 0 || node->student.scores[i] > max[i])
                {
                    max[i] = node->student.scores[i];
                }
                if (min[i] < 0 || node->student.scores[i] < min[i])
                {
                    min[i] = node->student.scores[i];
                }
            }
            student_size++;
            node = node->next;
        }

        // 打印显示统计结果
        for (size_t i = 0; i < n; i++)
        {
            cout << course.names[i] << endl;
            cout << "\t平均分：" << total[i] / student_size << endl;
            cout << "\t最高分：" << max[i] << endl;
            cout << "\t最低分：" << min[i] << endl;
        }
    }
};

// 管理类的指针
Manage* manage;

int main()
{
    // 设置背景色和前景色
    system("color 70");

    // 创建管理对象
    manage = new Manage();

    // 读取文件数据
    manage->read_files();

    // 循环显示菜单
    while (show_menu());

    // 删除释放对象
    delete manage;
    return 0;
}

// 显示系统主菜单
int show_menu()
{
    int choice;
    system("cls");
    cout << "------------------------------------------------------------"
        << endl;
    cout << "                    学 生 成 绩 管 理 系 统\n" << endl;
    cout << "                         1.课程管理" << endl;
    cout << "                         2.学生成绩管理" << endl;
    cout << "                         3.学生成绩统计" << endl;
    cout << "                         0.退出系统" << endl;
    cout << "------------------------------------------------------------"
        << endl;
    cout << "->";
    cin >> choice;
    switch (choice)
    {
        case 1:
            while (show_courses_menu())
                ; // 课程管理
            break;
        case 2:
            while (show_scores_menu())
                ; // 学生成绩管理
            break;
        case 3:
            while (show_statistic_menu())
                ; // 学生成绩统计
            break;
        case 0:
            cout << "系统即将退出..." << endl;
            break;
        default:
            cout << "输入指令异常" << endl;
            break;
    }
    return choice;
}

// 显示课程管理菜单
int show_courses_menu()
{
    int choice;
    system("cls");
    cout << "------------------------------------------------------------"
        << endl;
    cout << "                      课  程  管  理\n" << endl;
    cout << "                        1.添加课程" << endl;
    cout << "                        2.修改课程" << endl;
    cout << "                        3.删除课程" << endl;
    cout << "                        4.查询课程" << endl;
    cout << "                          0.返回" << endl;
    cout << "------------------------------------------------------------"
        << endl;

    cout << "->";
    cin >> choice;
    switch (choice)
    {
        case 1:
            manage->add_course(); // 添加课程
            wait_to_continue();
            break;
        case 2:
            manage->modify_course(); // 修改课程
            wait_to_continue();
            break;
        case 3:
            manage->delete_course(); // 删除课程
            wait_to_continue();
            break;
        case 4:
            manage->query_course(); // 查询课程
            wait_to_continue();
            break;
        case 0:
            break;
        default:
            cout << "输入指令错误！" << endl;
            break;
    }
    return choice;
}

// 显示成绩管理菜单
int show_scores_menu()
{
    int choice = 0;
    system("cls");
    cout << "-------------------------------------------------------------"
        << endl;
    cout << "                        学 生 成 绩 管 理\n" << endl;
    cout << "                         1.添加学生成绩" << endl;
    cout << "                         2.修改学生成绩" << endl;
    cout << "                         3.删除学生成绩" << endl;
    cout << "                         4.查询学生成绩" << endl;
    cout << "                            0.返回" << endl;
    cout << "-------------------------------------------------------------"
        << endl;

    cout << "->";
    cin >> choice;
    switch (choice)
    {
        case 1:
            manage->add_student(); // 添加学生成绩
            wait_to_continue();
            break;
        case 2:
            manage->modify_student(); // 修改学生成绩
            wait_to_continue();
            break;
        case 3:
            manage->delete_student(); // 删除学生成绩
            wait_to_continue();
            break;
        case 4:
            manage->query_student(); // 查询学生成绩
            wait_to_continue();
            break;
        case 0:
            break;
        default:
            cout << "输入指令错误！" << endl;
            break;
    }
    return choice;
}

// 显示统计菜单
int show_statistic_menu()
{
    int choice = 0;
    system("cls");
    cout << "---------------------------------------------------------------"
        << endl;
    cout << "                          学 生 成 绩 统 计\n" << endl;
    cout << "                         1.统计所有学生成绩" << endl;
    cout << "                         2.统计单个学生成绩" << endl;
    cout << "                              0.返 回" << endl;
    cout << "---------------------------------------------------------------"
        << endl;

    cout << "->";
    cin >> choice;
    switch (choice)
    {
        case 1:
            manage->statistic_all(); // 统计所有学生成绩
            wait_to_continue();
            break;
        case 2:
            manage->statistic_single(); // 统计单个学生成绩
            wait_to_continue();
            break;
        case 0:
            break;
        default:
            cout << "输入指令错误！" << endl;
            break;
    }
    return choice;
}

// 按任意键继续
void wait_to_continue()
{
    system("pause");
}