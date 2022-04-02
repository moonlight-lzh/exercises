#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BOOKS_SIZE 4    // ͼ�������С
#define USERS_SIZE 6    // �û������С

#define USER_FILE_PATH "../A.txt"       // �û���Ϣ�ļ���·��
#define BOOK_FILE_PATH "../B.txt"       // ͼ����Ϣ�ļ���·��


/**
 * ͼ��ṹ��
 */
typedef struct Book {
    char number[10];            // ͼ����
    char name[32];              // ͼ������
    float price;                // ͼ��۸�
    int total;                  // ͼ������
    int current;                // �ִ�����
} Book;


/**
 * �û��ṹ��
 */
typedef struct User {
    char number[10];            // ͼ��֤��
    char name[32];              // ����
    char sex[10];               // �Ա�
    int quantity;               // ��������
    int max_quantity;           // ����������
    char books[128];            // ����ͼ��ı�ţ��磺A01,C03,B02
} User;

User Users[USERS_SIZE];                // �û�����
Book Books[BOOKS_SIZE];                // ͼ������

/**********************************************��������*********************************************/

void query_user();                              // ��ѯ�û�
void query_book();                              // ��ѯͼ��
void borrow_books();                            // ���鹦��
void return_books();                            // ���鹦��
void sort_books();                              // ������
void read_files();                              // ��ȡ�����ļ�
void write_files();                             // ���������ļ�
void main_menu();                               // ���˵�
void query_menu();                              // ��ѯ���ܲ˵�
void print_book(const char *);                  // ��ӡָ��ͼ���ŵ�ͼ����Ϣ
void print_books(const char *);                 // ��ӡ����ͼ���ŵ�ͼ����Ϣ��A01,C03,B02��
int find_user_by_number(const char *);          // ����ͼ��֤�Ų����û��������û�����
int find_book_by_name_number(const char *);     // ����ͼ�����ƻ�ͼ���Ų���ͼ�飬����ͼ������
void add_user_books(int, const char *);         // ����û�����ͼ����
void delete_user_books(int, const char *);      // ɾ���û�����ͼ����
void sort_books_price();                        // ����ͼ��۸�����
int read_file_int(FILE *fp);                    // ���ļ��ж�ȡһ������
float read_file_float(FILE *fp);                // ���ļ��ж�ȡһ��������
void read_user_file();                          // ��ȡ�û��ļ�A.txt
void read_book_file();                          // ��ȡͼ���ļ�B.txt

/***************************************************************************************************/

/***********************************************������**********************************************/
int main() {
    read_files();        // ����ϵͳǰ��ȡ�ļ�����ͼ����Ϣ���û���Ϣ
    int option = 0;
    do {
        main_menu();                    // ���˵�
        scanf("%d", &option);
        switch (option) {
            case 1:
                query_menu();           // ��ѯ
                break;
            case 2:
                borrow_books();         // ����
                break;
            case 3:
                return_books();         // ����
                break;
            case 4:
                sort_books();           // ����
                break;
            default:
                printf("����ָ���쳣��\n");
                break;
        }
    } while (option);
    system("pause");
    return 0;
}
/***************************************************************************************************/


/**********************************************����ʵ��*********************************************/
/**
 * ����ͼ���ţ���ѯͼ����Ϣ
 */
void query_book() {
    printf("��������Ҫ��ѯ��ͼ���ţ�");
    char number[10];
    scanf("%s", number);
    for (int i = 0; i < BOOKS_SIZE; i++) {
        if (strcmp(Books[i].number, number) == 0) {    // ����ͼ���Ų�ѯ
            printf("ͼ���ţ�%s\n", Books[i].number);
            printf("ͼ�����ƣ�%s\n", Books[i].name);
            printf("ͼ��۸�%.2f\n", Books[i].price);
            printf("ͼ��������%d\n", Books[i].total);
            printf("�ִ�������%d\n", Books[i].current);
            break;
        }
    }
}

/**
 * ��ӡָ��ͼ���ŵ�ͼ����Ϣ
 * @param number
 */
void print_book(const char *number) {
    for (int i = 0; i < BOOKS_SIZE; i++) {
        if (strcmp(Books[i].number, number) == 0) {     // ����ͼ���Ų�ѯ
            printf("ͼ���ţ�%s\t", Books[i].number);
            printf("ͼ�����ƣ�%s\t", Books[i].name);
            printf("ͼ��۸�%.2f\n", Books[i].price);
            break;
        }
    }
}

/**
 * ��ӡ����ͼ���ŵ�ͼ����Ϣ
 * @param str
 */
void print_books(const char *str) {
    char buf[10] = {0};        // str�е�ÿ��ͼ����
    char *q = buf;
    while (*str != '\0') {
        *q++ = *str++;
        if (*str == ',' || *str == '\0') {
            *q = '\0';
            print_book(buf);        // ��ӡbuf�д洢��ͼ���ŵ�ͼ����Ϣ
            q = buf;                // qָ������
            str++;
        }
    }
}

/**
 * ����ͼ��֤�ţ���ѯ�û���Ϣ
 */
void query_user() {
    printf("��������Ҫ��ѯ�û���ͼ��֤�ţ�");
    char number[10];
    scanf("%s", number);
    for (int i = 0; i < USERS_SIZE; i++) {
        if (strcmp(Users[i].number, number) == 0) {     // �����û�ͼ��֤�Ų�ѯ
            printf("ͼ��֤�ţ�%s\t", Users[i].number);
            printf("������%s\t", Users[i].name);
            printf("�Ա�%s\n", Users[i].sex);
            printf("������%d�ᣬ���ɽ���%d��", Users[i].quantity, Users[i].max_quantity - Users[i].quantity);

            if (Users[i].quantity > 0) {         // �û�����������Ϊ0���ʹ�ӡ����ͼ�����Ϣ
                printf("������������£�\n");
                print_books(Users[i].books);
            } else {
                printf("\n");
            }
            break;
        }
    }
}

/**
 * ����ͼ��֤�Ų�ѯ����ȡ�û��������е�����
 * @param card_number
 * @return
 */
int find_user_by_number(const char *card_number) {
    for (int i = 0; i < USERS_SIZE; i++) {
        if (strcmp(Users[i].number, card_number) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * ����ͼ���Ż�ͼ�����Ʋ�ѯ����ȡͼ���������е�����
 * @param str
 * @return
 */
int find_book_by_name_number(const char *str) {
    for (int i = 0; i < BOOKS_SIZE; i++) {
        if (strcmp(Books[i].number, str) == 0 || strcmp(Books[i].name, str) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * �����û�����ͼ����
 * @param user_index
 * @param book_number
 */
void add_user_books(int user_index, const char *book_number) {
    char *p = Users[user_index].books;
    if (*p != '\0') {      // books��Ϊ�գ���pָ���ƶ���books��ĩβ
        while (*p != '\0') {
            p++;
        }
        *p++ = ',';
    }
    while (*book_number != '\0') {      // ������ͼ���ſ�����books
        *p++ = *book_number++;
    }
}

/**
 * ɾ���û�����ͼ����
 * @param user_index
 * @param book_number
 */
void delete_user_books(int user_index, const char *book_number) {
    size_t len = strlen(book_number);            // ͼ�����ַ�������
    char *p = Users[user_index].books;
    while (*p != '\0') {
        // �ж�pָ����ָ����ַ�����book_number�Ƿ���ͬ
        int flag = 1;
        for (int i = 0; i < len; i++) {
            if (*(p + i) != *(book_number + i)) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            break;            // flagΪ1����ʾָ���ƶ��˵���ɾ��ͼ����
        }
        p++;
    }
    if (*(p - 1) == ',') {       // ɾ��ǰ���','��������֣�,B02,C03)�������
        p--;
    }
    while (*(p + len) != '\0') {      // �ַ�ǰ�Ƹ���ɾ����ͼ����
        *p = *(p + len + 1);
        p++;
    }
}

/**
 * ����
 */
void borrow_books() {
    char card_number[32];
    printf("�������û�ͼ��֤�ţ�");
    scanf("%s", card_number);
    int user_index = find_user_by_number(card_number);
    if (user_index < 0) {
        printf("���û���Ϣ�����ڣ��޷����ģ�\n");
        return;
    }
    printf("��������Ҫ���ĵ�ͼ�����ƻ�ͼ���ţ�");
    char str[32];
    scanf("%s", str);
    int book_index = find_book_by_name_number(str);
    if (book_index < 0 || Books[book_index].current == 0) {
        printf("�޷����ģ�ͼ�鲻���ڻ�ͼ����ȫ�������\n");
        return;
    }
    Users[user_index].quantity++;        // �����һ
    Books[book_index].current--;         // ����һ

    // ������ͼ���Ŵ浽books
    add_user_books(user_index, Books[book_index].number);
    // ����
    write_files();
    printf("����ɹ���\n");
}

/**
 * ����
 */
void return_books() {
    char card_number[32];
    printf("�������û�ͼ��֤�ţ�");
    scanf("%s", card_number);
    int user_index = find_user_by_number(card_number);
    if (user_index < 0) {
        printf("���û���Ϣ�����ڣ��޷����飡\n");
        return;
    }
    printf("��������Ҫ�黹��ͼ�����ƻ�ͼ���ţ�");
    char str[32];
    scanf("%s", str);
    int book_index = find_book_by_name_number(str);
    if (book_index < 0 || Books[book_index].current + 1 > Books[book_index].total) {
        printf("�޷����飬ͼ�鲻���ڻ��ִ���������ͼ��������\n");
        return;
    }
    Users[user_index].quantity--;        // �����һ
    Books[book_index].current++;        // ����һ
    // ������ͼ���Ŵ�booksɾ��
    delete_user_books(user_index, Books[book_index].number);
    // ����
    write_files();
    printf("����ɹ���\n");
}

/**
 * ����ͼ��۸�����ð������
 */
void sort_books_price() {
    // ð������
    Book tmp;
    for (int i = 0; i < BOOKS_SIZE; i++) {
        int flag = 0;
        for (int j = 0; j < BOOKS_SIZE - i - 1; j++) {
            if (Books[j].price < Books[j + 1].price) {
                tmp = Books[j];
                Books[j] = Books[j + 1];
                Books[j + 1] = tmp;
                flag = 1;
            }
        }
        if (flag == 0) {          // ��������û���κ�Ԫ�ؽ�����˵������������ɣ�����ѭ��
            break;
        }
    }
}

/**
 * �����ӡ���
 */
void sort_books() {
    sort_books_price();
    printf("******************************************************************\n");
    printf("ͼ����    ͼ������      ͼ��۸�     �ִ�����    ͼ������\n");
    for (int i = 0; i < BOOKS_SIZE; i++) {
        printf("%-8s %-16s %-13.2f %-10d %-10d\n",
               Books[i].number, Books[i].name, Books[i].price, Books[i].current, Books[i].total);
    }
    printf("******************************************************************\n");
}

/**
 * ��ȡ�ļ�ָ����ָ�������
 * @param fp
 * @return
 */
int read_file_int(FILE *fp) {
    char buffer[24] = {0};
    char *end;
    fscanf(fp, "%s", buffer);
    return strtol(buffer, &end, 10);
}

/**
 * ��ȡ�ļ�ָ����ָ��ĸ�����
 * @param fp
 * @return
 */
float read_file_float(FILE *fp) {
    char buffer[24] = {0};
    char *end;
    fscanf(fp, "%s", buffer);
    return strtof(buffer, &end);
}

/**
 * ��ȡ�û���Ϣ�ļ�A.txt
 */
void read_user_file() {
    FILE *fp;
    errno_t error = fopen_s(&fp, USER_FILE_PATH, "r");
    if (error != 0) {
        printf("open file A.txt failed : %s\n", strerror(error));
        exit(1);
    }
    unsigned char ch;
    int i = 0;
    while (!feof(fp)) {
        ch = fgetc(fp);
        if (ch == '\n') {
            i++;            // �������з�����ȡ��һ���û���Ϣ
        } else {
            fseek(fp, -1, SEEK_CUR);        // fpָ����ǰ�ƶ�һλ
        }
        if (i >= USERS_SIZE) {           // ��������û����˳�ѭ�������ټ�����ȡ�ļ�
            break;
        }
        fscanf(fp, "%s", Users[i].number);
        fscanf(fp, "%s", Users[i].name);
        fscanf(fp, "%s", Users[i].sex);
        Users[i].quantity = read_file_int(fp);
        Users[i].max_quantity = read_file_int(fp);
        if (Users[i].quantity > 0) {
            fscanf(fp, "%s", Users[i].books);
        }
    }
    fclose(fp);
}

/**
 * ��ȡͼ����Ϣ�ļ�B.txt
 */
void read_book_file() {
    FILE *fp;
    errno_t error = fopen_s(&fp, BOOK_FILE_PATH, "r");
    if (error != 0) {
        printf("open file B.txt failed : %s\n", strerror(error));
        exit(1);
    }
    unsigned char ch;
    int i = 0;
    while (!feof(fp)) {
        ch = fgetc(fp);
        if (ch == '\n') {
            i++;            // �������з�����ȡ��һ��ͼ����Ϣ
        } else {
            fseek(fp, -1, SEEK_CUR);        // fpָ�����һλ
        }
        if (i >= BOOKS_SIZE) {  // �������ͼ�����˳�ѭ�������ټ�����ȡ�ļ�
            break;
        }
        fscanf(fp, "%s", Books[i].number);
        fscanf(fp, "%s", Books[i].name);
        Books[i].price = read_file_float(fp);
        Books[i].current = read_file_int(fp);
        Books[i].total = read_file_int(fp);
    }
    fclose(fp);
}

/**
 * ��ȡ����ͼ����û����ļ���Ϣ
 */
void read_files() {
    read_user_file();
    read_book_file();
}

/**
 * ��ͼ����û���Ϣ�������ļ�
 */
void write_files() {
    FILE *fpA = fopen(USER_FILE_PATH, "w");
    for (int i = 0; i < USERS_SIZE; i++) {
        fprintf(fpA, "%s\t%s\t%s\t%d\t%d\t%s\n",
                Users[i].number, Users[i].name, Users[i].sex, Users[i].quantity, Users[i].max_quantity, Users[i].books);
    }
    fclose(fpA);

    FILE *fpB = fopen(BOOK_FILE_PATH, "w");
    for (int i = 0; i < BOOKS_SIZE; i++) {
        fprintf(fpB, "%s\t%s\t%.2f\t%d\t%d\n",
                Books[i].number, Books[i].name, Books[i].price, Books[i].current, Books[i].total);
    }
    fclose(fpB);
}

/**
 * ���˵�
 */
void main_menu() {
    printf("******************************************************************\n");
    printf("************************** �鼮����ϵͳ **************************\n");
    printf("*                          1 - ��ѯ����                          *\n");
    printf("*                          2 - ���鹦��                          *\n");
    printf("*                          3 - ���鹦��                          *\n");
    printf("*                          4 - ������                          *\n");
    printf("*                          0 - �˳�ϵͳ                          *\n");
    printf("******************************************************************\n");
}

/**
 * ��ѯ�˵�
 */
void query_menu() {
    printf("**************************** ���鹦�� ****************************\n");
    printf("*                          1 - ͼ���ѯ                          *\n");
    printf("*                          2 - �û���Ϣ��ѯ                      *\n");
    printf("*                          0 - ������һ��                        *\n");
    printf("******************************************************************\n");

    int option;
    scanf("%d", &option);
    if (option == 1) {
        query_book();
    } else if (option == 2) {
        query_user();
    }
}
/***************************************************************************************************/
