#include "Student.h"

/**
 * ��ӡ����
 */
void Student::show_title() {
    cout << std::left << setw(14) << "ѧ��";
    cout << std::left << setw(8) << "����";
    cout << std::left << setw(6) << "�Ա�";
    cout << std::left << setw(7) << "����";
    cout << std::left << setw(14) << "�༶";
    cout << std::left << setw(19) << "רҵ";
    cout << std::left << setw(16) << "ϵ��" << endl;
}

/**
 * �������������
 * @param out �����
 * @param s ѧ������������
 * @return �����
 */
ostream &operator<<(ostream &out, const Student &s) {
    out << std::left << setw(14) << s.number;
    out << std::left << setw(8) << s.name;
    out << std::left << setw(6) << s.gender;
    out << std::left << setw(7) << s.age;
    out << std::left << setw(14) << s.classes;
    out << std::left << setw(19) << s.major;
    out << std::left << setw(16) << s.dept << endl;
    return out;
}

/// <summary>
/// �������������
/// </summary>
/// <param name="in">������</param>
/// <param name="s">ѧ������������</param>
/// <returns>������</returns>
istream &operator>>(istream &in, Student &s) {
    in >> s.number >> s.name >> s.gender >> s.age >> s.classes >> s.major >> s.dept;
    return in;
}
