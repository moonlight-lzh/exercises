#include "Student.h"

/**
 * 打印标题
 */
void Student::show_title() {
    cout << std::left << setw(14) << "学号";
    cout << std::left << setw(8) << "姓名";
    cout << std::left << setw(6) << "性别";
    cout << std::left << setw(7) << "年龄";
    cout << std::left << setw(14) << "班级";
    cout << std::left << setw(19) << "专业";
    cout << std::left << setw(16) << "系别" << endl;
}

/**
 * 重载输出操作符
 * @param out 输出流
 * @param s 学生变量的引用
 * @return 输出流
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
/// 重载输入操作符
/// </summary>
/// <param name="in">输入流</param>
/// <param name="s">学生变量的引用</param>
/// <returns>输入流</returns>
istream &operator>>(istream &in, Student &s) {
    in >> s.number >> s.name >> s.gender >> s.age >> s.classes >> s.major >> s.dept;
    return in;
}
