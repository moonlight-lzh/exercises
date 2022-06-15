#include <iomanip>
#include <fstream>
#include "Book.h"

/** 打印表格的标题 */
void DoBook::print_title() {
    cout << std::left << setw(15) << "ISBN";
    cout << std::left << setw(17) << "名称";
    cout << std::left << setw(16) << "作者";
    cout << std::left << setw(17) << "出版社";
    cout << std::left << setw(9) << "价格" << endl;
    print_cutting_line();
}

/** 打印图书信息 */
void DoBook::print_book(const Book &book) {
    cout << std::left << setw(12) << book.isbn;
    cout << std::left << setw(21) << book.name;
    cout << std::left << setw(14) << book.author;
    cout << std::left << setw(19) << book.publisher;
    cout << std::left << setw(8) << book.price << endl;
}

/** 打印分割线 */
void DoBook::print_cutting_line() {
    cout << "----------------------------------------------------------------------" << endl;
}

/** 查询图书编号，返回索引 */
int DoBook::index_of_book(const string &isbn) {
    int i;
    for (i = 0; i < books.size(); i++) {
        if (books[i].isbn == isbn) {
            return i;
        }
    }
    return -1;
}

/** 读取文件，初始化图书信息 */
void DoBook::init() {
    string line;
    Book book;

    // 以读取的方式打开文件
    ifstream infile(books_file, ios_base::in);
    if (!infile.is_open()) {
        return;
    }

    // 清空原有图书记录
    books.clear();

    // 循环读取文件中的每一行
    while (getline(infile, line)) {
        // 处理每行结尾的空格
        while (!line.empty() && isspace(line.back())) {
            line.pop_back();
        }

        // 跳过空行记录
        if (line.empty()) {
            continue;
        }

        // 使用字符串流读取图书信息，并添加到向量中
        istringstream iss(line);
        iss >> book.isbn >> book.name >> book.author >> book.publisher >> book.price;
        books.emplace_back(book);
    }

    // 关闭文件
    infile.close();
}

/** 保存所有图书信息至文件 */
void DoBook::saveall() {
    // 以写入的方式打开文件
    ofstream outfile(books_file, ios_base::out);
    if (!outfile.is_open()) {
        cout << "保存图书信息，打开文件[" << books_file << "]失败." << endl;
        exit(0);
    }

    // 循环每一条图书信息，写入文件
    for (const auto &book: books) {
        outfile << book.isbn << '\t' << book.name << '\t' << book.author << '\t' << book.publisher << '\t'
                << book.price << endl;
    }

    // 关闭文件
    outfile.close();
}

/** 打印显示所有的图书信息 */
void DoBook::display_allbook() {
    print_cutting_line();
    print_title();
    for (const auto &book: books) {
        print_book(book);
    }
    print_cutting_line();
}

/** 新增一条图书记录 */
void DoBook::insert_onebook() {
    Book book;
    cout << "请输入待新增的图书信息" << endl;
    cout << "图书编号：";
    cin >> book.isbn;

    // 判断输入的图书编号是否已经存在
    while (index_of_book(book.isbn) > -1) {
        cout << "您输入的图书编号已存在，请重新输入（输入N取消新增）" << endl;
        cout << "输入图书编号：";
        cin >> book.isbn;
        if (book.isbn.size() == 1 && (book.isbn[0] == 'N' || book.isbn[0] == 'n')) {
            return;
        }
    }

    // 输入图书的其他信息
    cout << "图书名称：";
    cin >> book.name;
    cout << "作者：";
    cin >> book.author;
    cout << "出版社：";
    cin >> book.publisher;
    cout << "价格：";
    cin >> book.price;

    // 新增记录，并保存文件
    books.emplace_back(book);
    saveall();
    cout << "新增成功！" << endl;
}

/** 删除一条图书记录 */
void DoBook::delete_onebook() {
    string isbn;
    char ch;
    int index;
    cout << "输入需要删除的图书编号：";
    cin >> isbn;

    // 判断输入的图书编号是否存在
    index = index_of_book(isbn);
    if (index < 0) {
        cout << "不存在指定图书编号的图书记录！" << endl;
        return;
    }

    // 打印显示待删除的图书信息
    print_cutting_line();
    print_title();
    print_book(books[index]);
    print_cutting_line();

    // 确实是否删除该条记录
    cout << "是否删除该图书信息？（Y/N）：";
    cin.ignore();
    cin.get(ch);
    if (ch != 'Y' && ch != 'y') {
        return;
    }

    // 删除图书，并保存文件
    books.erase(books.begin() + index);
    saveall();
    cout << "删除成功！" << endl;
}

/** 修改一条图书记录 */
void DoBook::modify_onebook() {
    string isbn;
    int index, choice;
    cout << "输入需要修改的图书编号：";
    cin >> isbn;

    // 判断输入的图书编号是否存在
    index = index_of_book(isbn);
    if (index < 0) {
        cout << "不存在指定图书编号的图书记录！" << endl;
        return;
    }

    // 打印显示待修改的图书信息
    print_cutting_line();
    print_title();
    print_book(books[index]);
    print_cutting_line();

    // 选择修改条件
    cout << "1.图书编号\n" << "2.图书名称\n" << "3.作者\n" << "4.出版社\n" << "5.价格" << endl;
    cout << "请选择：";
    cin >> choice;

    // 根据选项输入修改内容
    switch (choice) {
        case 1:
            cout << "请输入修改后的图书编号：";
            cin >> isbn;

            // 验证修改后的图书编号是否存在，保持图书编号的唯一性
            while (index_of_book(isbn) > -1) {
                cout << "您输入的图书编号已存在，请重新输入：";
                cin >> isbn;
            }
            books[index].isbn = isbn;
            break;
        case 2:
            cout << "请输入修改后的图书名称：";
            cin >> books[index].name;
            break;
        case 3:
            cout << "请输入修改后的作者：";
            cin >> books[index].author;
            break;
        case 4:
            cout << "请输入修改后的出版社：";
            cin >> books[index].publisher;
            break;
        case 5:
            cout << "请输入修改后的价格：";
            cin >> books[index].price;
            break;
        default:
            return;
    }

    // 修改成功保存文件
    saveall();
    cout << "修改成功！" << endl;
}

/** 按不同条件查询图书信息 */
void DoBook::select_onbook() {
    bool find = false;
    int choice;
    string value;

    // 选择查询的方式
    cout << "1.按图书编号查询" << endl;
    cout << "2.按图书名称查询" << endl;
    cout << "3.按作者查询" << endl;
    cout << "4.按出版社查询" << endl;
    cout << "0.返回" << endl;
    cout << "请选择：";
    cin >> choice;

    // 输入查询的内容
    switch (choice) {
        case 1:
            cout << "输入图书编号：";
            break;
        case 2:
            cout << "输入图书名称：";
            break;
        case 3:
            cout << "输入作者：";
            break;
        case 4:
            cout << "输入出版社：";
            break;
        default:
            return;
    }
    cin >> value;
    print_cutting_line();
    print_title();
    for (const auto &book: books) {
        // 根据选项比较不同的属性值，判断是否查找到图书记录
        if ((choice == 1 && book.isbn == value)
            || (choice == 2 && book.name == value)
            || (choice == 3 && book.author == value)
            || (choice == 4 && book.publisher == value)) {
            print_book(book);
            find = true;            // 标记查询到相关的图书信息
        }
    }

    print_cutting_line();

    if (!find) {
        cout << "查找失败，不存在相关记录的图书信息！" << endl;
    }
}

