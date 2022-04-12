#include <iostream>
#include <memory.h>
#include <cmath>

using namespace std;

#define MAX_COEF 30

class Polynomial {
protected:
    double coef[MAX_COEF];      // 系数
    bool eval = false;          // 默认是正常的多项式，true的时候表示这个多项式是计算结果
public:
    Polynomial();

    Polynomial(bool eval);

    void clear();

    void assign(int, double);

    void add(int, double);

    Polynomial derivation();

    double evaluate(double);

    Polynomial operator+(const Polynomial &);

    Polynomial operator-(const Polynomial &);

    Polynomial operator*(const Polynomial &);

    friend ostream &operator<<(ostream &, Polynomial);
};

/// 无参构造函数
Polynomial::Polynomial() {
    clear();
}

/// 有参数的构造函数，表示当前多项式是计算结果
Polynomial::Polynomial(bool eval) : Polynomial() {
    this->eval = eval;
}

/// 清空所有系数
void Polynomial::clear() {
    memset(coef, 0, sizeof(coef));
}

/// 设置系数
void Polynomial::assign(int exp, double coe) {
    coef[exp] = coe;
}

/// 增加系数
void Polynomial::add(int exp, double coe) {
    coef[exp] += coe;
}

/// 求导
Polynomial Polynomial::derivation() {
    Polynomial x;
    for (int i = MAX_COEF - 1; i > 0; i--) {
        if (coef[i] != 0) {
            x.add(i - 1, coef[i] * i);      // 求导降幂
        }
    }
    return x;
}

/// 计算表达式
double Polynomial::evaluate(double x) {
    double res = 0;
    for (int i = MAX_COEF - 1; i >= 0; i--) {
        if (coef[i] == 0) {         // 系数为0
            continue;
        }
        if (x == 1) {
            res += coef[i];         // 底数为1
        } else {
            res += coef[i] * pow(x, i);         // 求幂
        }
    }
    return res;
}

/// 重载 + 操作符
Polynomial Polynomial::operator+(const Polynomial &other) {
    Polynomial x(true);
    for (int i = MAX_COEF - 1; i >= 0; i--) {
        x.coef[i] = this->coef[i] + other.coef[i];          // 对应指数相加
    }
    return x;
}

/// 重载 - 操作符
Polynomial Polynomial::operator-(const Polynomial &other) {
    Polynomial x(true);
    for (int i = MAX_COEF - 1; i >= 0; i--) {
        x.coef[i] = this->coef[i] - other.coef[i];          // 对应指数相减
    }
    return x;
}

/// 重载 * 操作符
Polynomial Polynomial::operator*(const Polynomial &other) {
    Polynomial x(true);
    for (int i = 0; i < MAX_COEF; ++i) {
        for (int j = 0; j < MAX_COEF; ++j) {
            if (this->coef[i] != 0 && other.coef[j] != 0) {
                x.coef[i + j] = this->coef[i] * other.coef[j];      // 双重for循环实现乘法分配，系数相乘，指数相加
            }
        }
    }
    return x;
}

/// 重载 << 操作符
ostream &operator<<(ostream &os, Polynomial c) {
    int count = 0;
    for (int i = MAX_COEF - 1; i >= 0; i--) {           // 高次项往低次项顺序输出
        if (c.coef[i] == 0) {
            continue;
        }
        if (++count > 1 && c.coef[i] > 0) {
            cout << '+';        // 不是第一个系数，并且系数大于0的，前面需要加上'+'
        }
        if (c.coef[i] == -1) {
            cout << '-';                // 系数是-1的时候只输出'-'
        } else if (c.coef[i] != 1) {
            cout << c.coef[i];          // 系数不是1和-1的时候正常输出
        }
        if (i > 1) {
            cout << "x^" << i;          // 指数大于1按照x^n的格式输出
        } else if (i == 1) {
            cout << 'x';                // 指数是1的时候，输出'x'
        }
    }
    if (count == 0 && c.eval) {
        cout << 0;
    }
    return os;
}

/// 主菜单
void main_menu() {
    cout << "---------------The Commands---------------" << endl;
    cout << "s - 设置当前多项式" << endl;
    cout << "l - 调用assign_coef函数" << endl;
    cout << "t - 调用add_to_coef函数" << endl;
    cout << "c - 调用clear函数" << endl;
    cout << "v - 显示当前多项式" << endl;
    cout << "a - 显示所有多项式" << endl;
    cout << "d - 对当前多项式求导并显示" << endl;
    cout << "e - 计算当前多项式的值" << endl;
    cout << "+ - 显示A+B的和" << endl;
    cout << "- - 显示A-B的差" << endl;
    cout << "* - 显示A*B的积" << endl;
    cout << "q - quit" << endl;
    cout << "------------------------------------------" << endl;
}

/// 显示所有多项式
void show_all(Polynomial arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << (char) ('a' + i) << ':' << arr[i] << endl;
    }
}

/// 主函数
int main() {
    Polynomial p[3];        // a,b,c多项式数组
    int current = 0;        // 当前选择的多项式0,1,2
    char command;           // 指令
    string expression;
    do {
        main_menu();
        cout << '<';
        cin >> command;
        switch (command) {
            case 's':           // 设置当前多项式
                char ch;
                do {
                    cout << "Enter the polynomial you want to work on:(a,b,c)>";
                    cin >> ch;
                } while (ch < 'a' || ch > 'c');
                current = ch - 'a';
                break;
            case 'l':       // 多项式assign赋值
            case 't':       // 多项式add增加
                int exp;
                double coe;
                cout << "Enter exponent:";
                cin >> exp;
                cout << "Enter coefficient:";
                cin >> coe;
                if (command == 'l') {
                    p[current].assign(exp, coe);
                } else {
                    p[current].add(exp, coe);
                }
                cout << "After assigning:" << p[current] << endl;
                break;
            case 'c':       // clear清空多项式
                p[current].clear();
                cout << "After clearing:" << endl;
                break;
            case 'v':       // 显示当前多项式
                cout << (char) ('a' + current) << ':' << p[current] << endl;
                break;
            case 'a':       // 显示所有多项式
                show_all(p, 3);
                break;
            case 'd':       // 多项式求导并显示
                cout << p[current].derivation() << endl;
                break;
            case 'e':       // 计算当前多项式的值
                double x;
                cout << "输入x的值：";
                cin >> x;
                cout << "多项式：" << p[current] << endl;
                cout << "的值是：" << p[current].evaluate(x) << endl;
                break;
            case '+':       // 显示A+B的和
                cout << p[0] + p[1] << endl;
                break;
            case '-':       // 显示A-B的差
                cout << p[0] - p[1] << endl;
                break;
            case '*':       // 显示A*B的和
                cout << p[0] * p[1] << endl;
                break;
            case 'q':       // quit退出
                break;
            default:
                cout << "指令错误，请重新输入" << endl;
                break;
        }
    } while (command != 'q');
    return 0;
}
