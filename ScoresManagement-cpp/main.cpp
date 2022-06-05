#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// ѧ����Ϣ�ṹ��
struct Student
{
    // ѧ��ѧ��
    int num = 0;

    // ѧ������
    string name;

    // �ɼ�����
    vector<float> scores;

    // ��ӡѧ����Ϣ
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

// ������ṹ��
struct LNode
{
    // ������
    Student student;

    // ָ����
    LNode* next = nullptr;
};

// �γ̽ṹ��
struct Course
{
private:
    // �γ��ļ�����
    const string COURSE_FILE = "�γ�.txt";

public:
    // �γ�����
    vector<string> names;

    // ��ȡ�γ��ļ��е����ݣ���������
    void read_file()
    {
        ifstream is(COURSE_FILE, ios::in); // ֻ����ʽ���ļ�
        if (!is)
        {
            return;
        }
        names.clear(); // ������пγ�

        string line;
        while (getline(is, line))
        {
            names.push_back(line);          // ���ļ���ȡÿһ�пγ����ƣ�����ӵ�������
        }
        is.close(); // �ر��ļ�
    }

    // ���γ������е�ÿ���γ�����д���ļ�
    bool write_file()
    {
        ofstream os(COURSE_FILE, ios::out);         // ֻд�ķ�ʽ���ļ�
        if (!os)
        {
            cerr << "�޷����ļ� '" << COURSE_FILE << '\'' << endl;
            return false;
        }

        for (const auto& line : names)       // ѭ��ÿ���γ�����д���ļ�ÿһ��
        {
            os << line << endl;
        }
        os.close(); // �ر��ļ�
        return true;
    }

    // �жϿγ������Ƿ����
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

    // ��ȡ�γ���������
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

// �����������
void wait_to_continue();

// ��ʾϵͳ���˵�
int show_menu();

// ��ʾ�γ̹���˵�
int show_courses_menu();

// ��ʾ�ɼ�����˵�
int show_scores_menu();

// ��ʾͳ�Ʋ˵�
int show_statistic_menu();

// ������
struct LinkedList
{
private:
    // ѧ���ɼ��ļ�����
    const string SCORES_FILE = "ѧ���ɼ�.txt";

    // ����ͷ���
    LNode* _head;

    // ����β���
    LNode* _tail;

public:
    // ���캯��
    LinkedList()
    {
        _head = _tail = nullptr;
    }

    // ��������
    ~LinkedList()
    {
        LNode* tmp;
        while (_head)
        {
            tmp = _head;
            _head = _head->next;
            delete tmp;          // �ͷ�������
        }
        _head = _tail = nullptr;
    }

    // ��ȡ����ͷ���
    LNode* get_head()
    {
        return this->_head;
    }

    // ���������
    void append_node(Student& stu)
    {
        auto* node = new LNode();       // �������
        node->student = stu;
        node->next = nullptr;

        if (!_tail)
        {
            _head = _tail = node;
        }
        else
        {
            _tail->next = node;      // β�巨
            _tail = node;
        }
    }

    // ����ѧ�����ɾ�����
    bool remove_node(int num)
    {
        if (_head == nullptr)
        {
            return false;
        }

        LNode* node, * temp;
        if (_head->student.num == num)      // ͷ���Ϊ��ɾ��ѧ�����
        {
            node = _head;
            _head = _head->next;
            delete node;
            return true;
        }

        node = _head;
        while (node->next && node->next->student.num != num)     // ����ɾ������ǰһ�����
        {
            node = node->next;
        }

        if (node->next == nullptr)
        {
            return false;
        }

        temp = node->next;
        node->next = temp->next; // �޸�ָ���Ƴ�������

        if (temp == _tail)
        {
            _tail = node; // ɾ��β���󣬸���β���ָ��
        }

        delete temp; // �ͷŽ��
        return true;
    }

    // ����ѧ�Ų�ѯ�����㣬��ѯ�����ŵ�������
    vector<LNode*> search_node_by_num(int num)
    {
        vector<LNode*> ans;
        auto node = _head;

        while (node)
        {
            if (node->student.num == num)           // �ж�ѧ���Ƿ����
            { 
                ans.push_back(node);
                break;
            }
            node = node->next;
        }
        return ans;
    }

    // ����������ѯ�����㣬��ѯ�����ŵ�������
    vector<LNode*> search_node_by_name(const string& name)
    {
        vector<LNode*> ans;
        auto node = _head;

        while (node)
        {
            if (node->student.name == name)          // �ж������Ƿ����
            {
                ans.push_back(node);
            }
            node = node->next;
        }
        return ans;
    }

    // ����ѧ�Ų�ѯ������
    LNode* search_node(int num)
    {
        auto ans = search_node_by_num(num);
        if (ans.empty())
        {
            return nullptr;
        }
        return ans.front();
    }

    // ��ȡ�ɼ��ļ��е����ݣ���������
    void read_file()
    {
        ifstream is(SCORES_FILE, ios::in); // ֻ����ʽ���ļ�
        if (!is)
        {
            return;
        }
        string line;
        while (getline(is, line))    // ��ȡ�ļ�ÿһ��
        {
            // ����ȥ���ַ���ĩβ�Ŀհ�
            while (!line.empty() && isspace(line.back()))
            {
                line.pop_back();
            }
            if (line.empty())           // ��������
            { 
                continue;       
            }

            istringstream iss(line);
            Student stu;

            // ��ȡѧ����ѧ�š����������Ƴɼ�
            iss >> stu.num >> stu.name;
            float score;
            while (iss >> score)
            {
                stu.scores.push_back(score);
            }
            // ��ӵ�������
            append_node(stu);
        }
        is.close(); // �ر��ļ�
    }

    // �������еĳɼ�����д���ļ�
    bool write_file()
    {
        ofstream os(SCORES_FILE, ios::out); // ֻд��ʽ���ļ�
        if (!os)
        {
            cerr << "�޷����ļ� '" << SCORES_FILE << '\'' << endl;
            return false;
        }

        // ѭ�������е�ÿ����㣬��ѧ�š����������Ƴɼ�д���ļ�
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
        os.close(); // �ر��ļ�
        return true;
    }
};

// ������
class Manage
{
    // ����
    LinkedList list;

    // �γ�
    Course course;

public:
    // ��ӡ����
    void print_titles()
    {
        cout << "ѧ��\t\t����";
        for (size_t i = 0; i < course.names.size(); i++)
        {
            cout << "\t\t" << course.names[i];
        }
        cout << endl;
    }

    // ��ȡ�����ļ�����Ϣ
    void read_files()
    {
        course.read_file();

        list.read_file();
    }

    // ��ӿγ�
    void add_course()
    {
        string name;
        cout << "�����������γ����ƣ�" << endl;
        cin >> name;

        // �������γ��Ƿ����
        if (course.check_course_exist(name))
        {
            cout << "������Ŀγ������Ѵ��ڣ������ظ���ӣ�" << endl;
            return;
        }

        // �¿γ���ӵ������У��������ļ�
        course.names.push_back(name);
        course.write_file();

        if (list.get_head())
        {
            // �޸�������ĳɼ�
            cout << "�����β�������ѧ���������γ̳ɼ���" << endl;
            auto* node = list.get_head();
            float score;
            while (node)
            {
                cout << "����" << node->student.name << "[" << node->student.num
                    << "]��" << name << "�ɼ���" << endl;
                cin >> score;
                node->student.scores.push_back(score);
                node = node->next;
            }
            // ����ɼ��ļ�
            list.write_file();
        }

        cout << "�����γ̳ɹ���" << endl;
    }

    // ɾ���γ�
    void delete_course()
    {
        string name;
        cout << "������ɾ���γ����ƣ�" << endl;
        cin >> name;
        int pos;

        // �ж�����Ŀγ��Ƿ����
        pos = course.get_index(name);
        if (pos < 0)
        {
            cout << "������Ŀγ̲����ڣ�" << endl;
            return;
        }

        course.names.erase(course.names.begin() + pos);     // ɾ���γ�
        course.write_file();                                // ����γ��ļ�

        // ɾ��������ĳɼ�
        auto* node = list.get_head();
        while (node)
        {
            node->student.scores.erase(node->student.scores.begin() +  pos); // ɾ��ÿ��ѧ��pos���ĳɼ�
            node = node->next;
        }

        // �����ļ�
        list.write_file();
        cout << "ɾ���γ̳ɹ���" << endl;
    }

    // �޸Ŀγ�
    void modify_course()
    {
        string name, new_name;
        cout << "�������޸Ŀγ����ƣ�" << endl;
        cin >> name;
        int pos;

        // �ж�����Ŀγ��Ƿ����
        pos = course.get_index(name);
        if (pos < 0)
        {
            cout << "������Ŀγ̲����ڣ�" << endl;
            return;
        }

        // ��֤�޸ĺ�Ŀγ����Ƿ����
        cout << "�������޸ĺ�Ŀγ�����" << endl;
        cin >> new_name;
        if (course.check_course_exist(new_name))
        {
            cout << "�������Ŀ��γ����Ѵ��ڣ�";
            return;
        }

        // �޸Ŀγ������������ļ�
        course.names[pos] = new_name;
        course.write_file();
        cout << "�޸Ŀγ̳ɹ���" << endl;
    }

    // ��ѯ�γ�
    void query_course()
    {
        cout << "��ǰ�γ��б�" << endl;
        for (const auto& x : course.names)
        {
            cout << x << endl;
        }
    }

    // ���ѧ��
    void add_student()
    {
        Student stu;
        cout << "����������ѧ����Ϣ��" << endl;
        cout << "ѧ�ţ�";
        cin >> stu.num;

        // �������ѧ����ѧ���Ƿ����
        if (list.search_node(stu.num))
        {
            cout << "��ѧ���Ѵ��ڣ��޷�������" << endl;
            return;
        }

        // �����������
        cout << "������";
        cin >> stu.name;
        float score;
        for (size_t i = 0; i < course.names.size(); i++)
        {
            cout << course.names[i] << "�ɼ���";
            cin >> score;
            stu.scores.push_back(score);
        }

        // �������ڵ�
        list.append_node(stu);

        // ����ѧ���ɼ��ļ�
        list.write_file();
        cout << "�����ɹ���" << endl;
    }

    // ɾ��ѧ��
    void delete_student()
    {
        int num;
        cout << "��������Ҫɾ��ѧ����ѧ�ţ�";
        cin >> num;

        // �ж������ѧ���Ƿ����
        auto node = list.search_node(num);
        if (node == nullptr)
        {
            cout << "�����ڸ�ѧ����Ϣ��" << endl;
            return;
        }

        node->student.print();

        cout << "���ٴ�ȷ�ϣ��Ƿ�ɾ��������¼����Y/N��\n->";

        char confirm;
        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y')
        {
            // ɾ��������
            list.remove_node(num);

            // ����ѧ���ɼ��ļ�
            list.write_file();
            cout << "ɾ���ɹ���" << endl;
        }
    }

    // �޸�ѧ����Ϣ
    void modify_student()
    {
        int num;
        cout << "��������޸�ѧ����ѧ�ţ�" << endl;
        cin >> num;

        // �ж������ѧ���Ƿ����
        auto node = list.search_node(num);
        if (node == nullptr)
        {
            cout << "�����ڸ�ѧ����Ϣ��" << endl;
            return;
        }

        // ѡ���޸�����
        size_t choice;
        cout << "��ѡ���޸�����" << endl;
        cout << "1.ѧ��\t\t2.����" << endl;
        for (size_t i = 0; i < course.names.size(); ++i)
        {
            cout << i + 3 << '.' << course.names[i] << "�ɼ�" << '\t';
            if ((i + 1) % 3 == 0)
            {
                cout << endl;
            }
        }
        cout << "0.ȡ���޸�" << endl;
        cout << "->";
        cin >> choice;

        // ��ѡ��������޸�ֵ
        if (choice == 1)
        {
            int val;
            cout << "�������޸ĺ��ѧ�ţ�";
            cin >> val;

            // �޸�ѧ�ŵ�ʱ���ж��޸ĺ��ѧ���Ƿ���ڣ���֤ѧ��Ψһ��
            if (list.search_node(val))
            {
                cout << "��ѧ���Ѵ��ڣ��޷��޸ģ�" << endl;
                return;
            }
            node->student.num = val;
        }
        else if (choice == 2)
        {
            cout << "�������޸ĺ��������";
            cin >> node->student.name;
        }
        else if (choice >= 3 && choice <= course.names.size() + 2)
        {
            cout << "�������޸ĺ��" << course.names[choice - 3] << "�ɼ���";
            cin >> node->student.scores[choice - 3];
        }
        else
        {
            return;
        }

        // �޸ĳɹ��������ļ�
        list.write_file();
        cout << "�޸ĳɹ���" << endl;
    }

    // ��ѯѧ����Ϣ
    void query_student()
    {
        cout << "    1.��ѧ�Ų�ѯ" << endl;
        cout << "    2.��������ѯ" << endl;
        cout << "    0.����" << endl;
        cout << "��ѡ��";
        int choice;
        int num;
        string name;
        cin >> choice;
        vector<LNode*> ans;

        // ��������ѯ�����ؽ��
        if (choice == 1)
        {
            cout << "�������ѯ��ѧ�ţ�";
            cin >> num;
            ans = list.search_node_by_num(num);
        }
        else if (choice == 2)
        {
            cout << "�������ѯ��������";
            cin >> name;
            ans = list.search_node_by_name(name);
        }
        else
        {
            return;
        }
        if (ans.empty())
        {
            cout << "��ѯ���Ϊ�գ�" << endl;
            return;
        }

        // ��ӡ��ʾ����ѧ����Ϣ
        print_titles();
        for (auto const node : ans)
        {
            node->student.print();
        }
    }

    // ͳ��ĳ��ѧ���ɼ�
    void statistic_single()
    {
        int num;
        cout << "�������ͳ��ѧ����ѧ�ţ�" << endl;
        cin >> num;

        // �ж������ѧ���Ƿ����
        auto node = list.search_node(num);
        if (node == nullptr || node->student.scores.empty())
        {
            cout << "�����ڸ�ѧ����Ϣ���޷�ͳ�ƣ�" << endl;
            return;
        }

        float average = node->student.scores[0];
        int imax = 0, imin = 0;

        // ͳ�Ƹ�ѧ�����Ƴɼ���ƽ���֡���߷֡���ͷ�
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

        cout << "ѧ�ţ�" << node->student.num << endl;
        cout << "������" << node->student.name << endl;
        cout << "ƽ���֣�" << average << endl;
        cout << "��߷֣�" << node->student.scores[imax] << endl;
        cout << "��ͷ֣�" << node->student.scores[imin] << endl;
    }

    // ͳ�����гɼ�
    void statistic_all()
    {
        auto node = list.get_head();
        int student_size = 0;
        auto n = course.names.size();
        vector<float> total(n, 0); // ÿ����Ŀ���ܷ�����
        vector<float> max(n, -1);  // ÿ����Ŀ����߷�����
        vector<float> min(n, -1);  // ÿ����Ŀ����ͷ�����
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

        // ��ӡ��ʾͳ�ƽ��
        for (size_t i = 0; i < n; i++)
        {
            cout << course.names[i] << endl;
            cout << "\tƽ���֣�" << total[i] / student_size << endl;
            cout << "\t��߷֣�" << max[i] << endl;
            cout << "\t��ͷ֣�" << min[i] << endl;
        }
    }
};

// �������ָ��
Manage* manage;

int main()
{
    // ���ñ���ɫ��ǰ��ɫ
    system("color 70");

    // �����������
    manage = new Manage();

    // ��ȡ�ļ�����
    manage->read_files();

    // ѭ����ʾ�˵�
    while (show_menu());

    // ɾ���ͷŶ���
    delete manage;
    return 0;
}

// ��ʾϵͳ���˵�
int show_menu()
{
    int choice;
    system("cls");
    cout << "------------------------------------------------------------"
        << endl;
    cout << "                    ѧ �� �� �� �� �� ϵ ͳ\n" << endl;
    cout << "                         1.�γ̹���" << endl;
    cout << "                         2.ѧ���ɼ�����" << endl;
    cout << "                         3.ѧ���ɼ�ͳ��" << endl;
    cout << "                         0.�˳�ϵͳ" << endl;
    cout << "------------------------------------------------------------"
        << endl;
    cout << "->";
    cin >> choice;
    switch (choice)
    {
        case 1:
            while (show_courses_menu())
                ; // �γ̹���
            break;
        case 2:
            while (show_scores_menu())
                ; // ѧ���ɼ�����
            break;
        case 3:
            while (show_statistic_menu())
                ; // ѧ���ɼ�ͳ��
            break;
        case 0:
            cout << "ϵͳ�����˳�..." << endl;
            break;
        default:
            cout << "����ָ���쳣" << endl;
            break;
    }
    return choice;
}

// ��ʾ�γ̹���˵�
int show_courses_menu()
{
    int choice;
    system("cls");
    cout << "------------------------------------------------------------"
        << endl;
    cout << "                      ��  ��  ��  ��\n" << endl;
    cout << "                        1.��ӿγ�" << endl;
    cout << "                        2.�޸Ŀγ�" << endl;
    cout << "                        3.ɾ���γ�" << endl;
    cout << "                        4.��ѯ�γ�" << endl;
    cout << "                          0.����" << endl;
    cout << "------------------------------------------------------------"
        << endl;

    cout << "->";
    cin >> choice;
    switch (choice)
    {
        case 1:
            manage->add_course(); // ��ӿγ�
            wait_to_continue();
            break;
        case 2:
            manage->modify_course(); // �޸Ŀγ�
            wait_to_continue();
            break;
        case 3:
            manage->delete_course(); // ɾ���γ�
            wait_to_continue();
            break;
        case 4:
            manage->query_course(); // ��ѯ�γ�
            wait_to_continue();
            break;
        case 0:
            break;
        default:
            cout << "����ָ�����" << endl;
            break;
    }
    return choice;
}

// ��ʾ�ɼ�����˵�
int show_scores_menu()
{
    int choice = 0;
    system("cls");
    cout << "-------------------------------------------------------------"
        << endl;
    cout << "                        ѧ �� �� �� �� ��\n" << endl;
    cout << "                         1.���ѧ���ɼ�" << endl;
    cout << "                         2.�޸�ѧ���ɼ�" << endl;
    cout << "                         3.ɾ��ѧ���ɼ�" << endl;
    cout << "                         4.��ѯѧ���ɼ�" << endl;
    cout << "                            0.����" << endl;
    cout << "-------------------------------------------------------------"
        << endl;

    cout << "->";
    cin >> choice;
    switch (choice)
    {
        case 1:
            manage->add_student(); // ���ѧ���ɼ�
            wait_to_continue();
            break;
        case 2:
            manage->modify_student(); // �޸�ѧ���ɼ�
            wait_to_continue();
            break;
        case 3:
            manage->delete_student(); // ɾ��ѧ���ɼ�
            wait_to_continue();
            break;
        case 4:
            manage->query_student(); // ��ѯѧ���ɼ�
            wait_to_continue();
            break;
        case 0:
            break;
        default:
            cout << "����ָ�����" << endl;
            break;
    }
    return choice;
}

// ��ʾͳ�Ʋ˵�
int show_statistic_menu()
{
    int choice = 0;
    system("cls");
    cout << "---------------------------------------------------------------"
        << endl;
    cout << "                          ѧ �� �� �� ͳ ��\n" << endl;
    cout << "                         1.ͳ������ѧ���ɼ�" << endl;
    cout << "                         2.ͳ�Ƶ���ѧ���ɼ�" << endl;
    cout << "                              0.�� ��" << endl;
    cout << "---------------------------------------------------------------"
        << endl;

    cout << "->";
    cin >> choice;
    switch (choice)
    {
        case 1:
            manage->statistic_all(); // ͳ������ѧ���ɼ�
            wait_to_continue();
            break;
        case 2:
            manage->statistic_single(); // ͳ�Ƶ���ѧ���ɼ�
            wait_to_continue();
            break;
        case 0:
            break;
        default:
            cout << "����ָ�����" << endl;
            break;
    }
    return choice;
}

// �����������
void wait_to_continue()
{
    system("pause");
}