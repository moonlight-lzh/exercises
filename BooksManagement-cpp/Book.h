
#ifndef MYCPPPROJECT_BOOK_H
#define MYCPPPROJECT_BOOK_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

/** 图书信息结构体 */
struct Book {
    string isbn;            // 图书编号
    string name;            // 图书名称
    string author;          // 作者
    string publisher;       // 出版社
    float price = 0;        // 价格
};

/** 图书数据操作类 */
class DoBook {
    vector<Book> books;         // 图书向量

    const string books_file = "books.txt";      // 图书数据的文件名

    void print_title();                         // 打印标题

    void print_book(const Book &book);          // 打印图书信息

    int index_of_book(const string& isbn);      // 查找图书编号索引

    void print_cutting_line();                  // 打印分割线
public:
    void init();                // 初始化，读取文件

    void saveall();             // 保存数据至文件

    void display_allbook();     // 显示所有图书信息

    void insert_onebook();      // 新增图书信息

    void delete_onebook();      // 删除图书信息

    void modify_onebook();      // 修改图书信息

    void select_onbook();       // 查询图书信息
};

#endif //MYCPPPROJECT_BOOK_H
