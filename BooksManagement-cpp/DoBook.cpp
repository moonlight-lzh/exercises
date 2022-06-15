#include <iomanip>
#include <fstream>
#include "Book.h"

/** ��ӡ���ı��� */
void DoBook::print_title() {
    cout << std::left << setw(15) << "ISBN";
    cout << std::left << setw(17) << "����";
    cout << std::left << setw(16) << "����";
    cout << std::left << setw(17) << "������";
    cout << std::left << setw(9) << "�۸�" << endl;
    print_cutting_line();
}

/** ��ӡͼ����Ϣ */
void DoBook::print_book(const Book &book) {
    cout << std::left << setw(12) << book.isbn;
    cout << std::left << setw(21) << book.name;
    cout << std::left << setw(14) << book.author;
    cout << std::left << setw(19) << book.publisher;
    cout << std::left << setw(8) << book.price << endl;
}

/** ��ӡ�ָ��� */
void DoBook::print_cutting_line() {
    cout << "----------------------------------------------------------------------" << endl;
}

/** ��ѯͼ���ţ��������� */
int DoBook::index_of_book(const string &isbn) {
    int i;
    for (i = 0; i < books.size(); i++) {
        if (books[i].isbn == isbn) {
            return i;
        }
    }
    return -1;
}

/** ��ȡ�ļ�����ʼ��ͼ����Ϣ */
void DoBook::init() {
    string line;
    Book book;

    // �Զ�ȡ�ķ�ʽ���ļ�
    ifstream infile(books_file, ios_base::in);
    if (!infile.is_open()) {
        return;
    }

    // ���ԭ��ͼ���¼
    books.clear();

    // ѭ����ȡ�ļ��е�ÿһ��
    while (getline(infile, line)) {
        // ����ÿ�н�β�Ŀո�
        while (!line.empty() && isspace(line.back())) {
            line.pop_back();
        }

        // �������м�¼
        if (line.empty()) {
            continue;
        }

        // ʹ���ַ�������ȡͼ����Ϣ������ӵ�������
        istringstream iss(line);
        iss >> book.isbn >> book.name >> book.author >> book.publisher >> book.price;
        books.emplace_back(book);
    }

    // �ر��ļ�
    infile.close();
}

/** ��������ͼ����Ϣ���ļ� */
void DoBook::saveall() {
    // ��д��ķ�ʽ���ļ�
    ofstream outfile(books_file, ios_base::out);
    if (!outfile.is_open()) {
        cout << "����ͼ����Ϣ�����ļ�[" << books_file << "]ʧ��." << endl;
        exit(0);
    }

    // ѭ��ÿһ��ͼ����Ϣ��д���ļ�
    for (const auto &book: books) {
        outfile << book.isbn << '\t' << book.name << '\t' << book.author << '\t' << book.publisher << '\t'
                << book.price << endl;
    }

    // �ر��ļ�
    outfile.close();
}

/** ��ӡ��ʾ���е�ͼ����Ϣ */
void DoBook::display_allbook() {
    print_cutting_line();
    print_title();
    for (const auto &book: books) {
        print_book(book);
    }
    print_cutting_line();
}

/** ����һ��ͼ���¼ */
void DoBook::insert_onebook() {
    Book book;
    cout << "�������������ͼ����Ϣ" << endl;
    cout << "ͼ���ţ�";
    cin >> book.isbn;

    // �ж������ͼ�����Ƿ��Ѿ�����
    while (index_of_book(book.isbn) > -1) {
        cout << "�������ͼ�����Ѵ��ڣ����������루����Nȡ��������" << endl;
        cout << "����ͼ���ţ�";
        cin >> book.isbn;
        if (book.isbn.size() == 1 && (book.isbn[0] == 'N' || book.isbn[0] == 'n')) {
            return;
        }
    }

    // ����ͼ���������Ϣ
    cout << "ͼ�����ƣ�";
    cin >> book.name;
    cout << "���ߣ�";
    cin >> book.author;
    cout << "�����磺";
    cin >> book.publisher;
    cout << "�۸�";
    cin >> book.price;

    // ������¼���������ļ�
    books.emplace_back(book);
    saveall();
    cout << "�����ɹ���" << endl;
}

/** ɾ��һ��ͼ���¼ */
void DoBook::delete_onebook() {
    string isbn;
    char ch;
    int index;
    cout << "������Ҫɾ����ͼ���ţ�";
    cin >> isbn;

    // �ж������ͼ�����Ƿ����
    index = index_of_book(isbn);
    if (index < 0) {
        cout << "������ָ��ͼ���ŵ�ͼ���¼��" << endl;
        return;
    }

    // ��ӡ��ʾ��ɾ����ͼ����Ϣ
    print_cutting_line();
    print_title();
    print_book(books[index]);
    print_cutting_line();

    // ȷʵ�Ƿ�ɾ��������¼
    cout << "�Ƿ�ɾ����ͼ����Ϣ����Y/N����";
    cin.ignore();
    cin.get(ch);
    if (ch != 'Y' && ch != 'y') {
        return;
    }

    // ɾ��ͼ�飬�������ļ�
    books.erase(books.begin() + index);
    saveall();
    cout << "ɾ���ɹ���" << endl;
}

/** �޸�һ��ͼ���¼ */
void DoBook::modify_onebook() {
    string isbn;
    int index, choice;
    cout << "������Ҫ�޸ĵ�ͼ���ţ�";
    cin >> isbn;

    // �ж������ͼ�����Ƿ����
    index = index_of_book(isbn);
    if (index < 0) {
        cout << "������ָ��ͼ���ŵ�ͼ���¼��" << endl;
        return;
    }

    // ��ӡ��ʾ���޸ĵ�ͼ����Ϣ
    print_cutting_line();
    print_title();
    print_book(books[index]);
    print_cutting_line();

    // ѡ���޸�����
    cout << "1.ͼ����\n" << "2.ͼ������\n" << "3.����\n" << "4.������\n" << "5.�۸�" << endl;
    cout << "��ѡ��";
    cin >> choice;

    // ����ѡ�������޸�����
    switch (choice) {
        case 1:
            cout << "�������޸ĺ��ͼ���ţ�";
            cin >> isbn;

            // ��֤�޸ĺ��ͼ�����Ƿ���ڣ�����ͼ���ŵ�Ψһ��
            while (index_of_book(isbn) > -1) {
                cout << "�������ͼ�����Ѵ��ڣ����������룺";
                cin >> isbn;
            }
            books[index].isbn = isbn;
            break;
        case 2:
            cout << "�������޸ĺ��ͼ�����ƣ�";
            cin >> books[index].name;
            break;
        case 3:
            cout << "�������޸ĺ�����ߣ�";
            cin >> books[index].author;
            break;
        case 4:
            cout << "�������޸ĺ�ĳ����磺";
            cin >> books[index].publisher;
            break;
        case 5:
            cout << "�������޸ĺ�ļ۸�";
            cin >> books[index].price;
            break;
        default:
            return;
    }

    // �޸ĳɹ������ļ�
    saveall();
    cout << "�޸ĳɹ���" << endl;
}

/** ����ͬ������ѯͼ����Ϣ */
void DoBook::select_onbook() {
    bool find = false;
    int choice;
    string value;

    // ѡ���ѯ�ķ�ʽ
    cout << "1.��ͼ���Ų�ѯ" << endl;
    cout << "2.��ͼ�����Ʋ�ѯ" << endl;
    cout << "3.�����߲�ѯ" << endl;
    cout << "4.���������ѯ" << endl;
    cout << "0.����" << endl;
    cout << "��ѡ��";
    cin >> choice;

    // �����ѯ������
    switch (choice) {
        case 1:
            cout << "����ͼ���ţ�";
            break;
        case 2:
            cout << "����ͼ�����ƣ�";
            break;
        case 3:
            cout << "�������ߣ�";
            break;
        case 4:
            cout << "��������磺";
            break;
        default:
            return;
    }
    cin >> value;
    print_cutting_line();
    print_title();
    for (const auto &book: books) {
        // ����ѡ��Ƚϲ�ͬ������ֵ���ж��Ƿ���ҵ�ͼ���¼
        if ((choice == 1 && book.isbn == value)
            || (choice == 2 && book.name == value)
            || (choice == 3 && book.author == value)
            || (choice == 4 && book.publisher == value)) {
            print_book(book);
            find = true;            // ��ǲ�ѯ����ص�ͼ����Ϣ
        }
    }

    print_cutting_line();

    if (!find) {
        cout << "����ʧ�ܣ���������ؼ�¼��ͼ����Ϣ��" << endl;
    }
}

