
#ifndef MYCPPPROJECT_BOOK_H
#define MYCPPPROJECT_BOOK_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

/** ͼ����Ϣ�ṹ�� */
struct Book {
    string isbn;            // ͼ����
    string name;            // ͼ������
    string author;          // ����
    string publisher;       // ������
    float price = 0;        // �۸�
};

/** ͼ�����ݲ����� */
class DoBook {
    vector<Book> books;         // ͼ������

    const string books_file = "books.txt";      // ͼ�����ݵ��ļ���

    void print_title();                         // ��ӡ����

    void print_book(const Book &book);          // ��ӡͼ����Ϣ

    int index_of_book(const string& isbn);      // ����ͼ��������

    void print_cutting_line();                  // ��ӡ�ָ���
public:
    void init();                // ��ʼ������ȡ�ļ�

    void saveall();             // �����������ļ�

    void display_allbook();     // ��ʾ����ͼ����Ϣ

    void insert_onebook();      // ����ͼ����Ϣ

    void delete_onebook();      // ɾ��ͼ����Ϣ

    void modify_onebook();      // �޸�ͼ����Ϣ

    void select_onbook();       // ��ѯͼ����Ϣ
};

#endif //MYCPPPROJECT_BOOK_H
