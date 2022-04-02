#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BOOKS_SIZE 4    // 图书数组大小
#define USERS_SIZE 6    // 用户数组大小

#define USER_FILE_PATH "../A.txt"       // 用户信息文件的路径
#define BOOK_FILE_PATH "../B.txt"       // 图书信息文件的路径


/**
 * 图书结构体
 */
typedef struct Book {
    char number[10];            // 图书编号
    char name[32];              // 图书名称
    float price;                // 图书价格
    int total;                  // 图书总数
    int current;                // 现存数量
} Book;


/**
 * 用户结构体
 */
typedef struct User {
    char number[10];            // 图书证号
    char name[32];              // 姓名
    char sex[10];               // 性别
    int quantity;               // 借书数量
    int max_quantity;           // 最大借书数量
    char books[128];            // 所借图书的编号，如：A01,C03,B02
} User;

User Users[USERS_SIZE];                // 用户数组
Book Books[BOOKS_SIZE];                // 图书数组

/**********************************************函数声明*********************************************/

void query_user();                              // 查询用户
void query_book();                              // 查询图书
void borrow_books();                            // 借书功能
void return_books();                            // 还书功能
void sort_books();                              // 排序功能
void read_files();                              // 读取所有文件
void write_files();                             // 保存所有文件
void main_menu();                               // 主菜单
void query_menu();                              // 查询功能菜单
void print_book(const char *);                  // 打印指定图书编号的图书信息
void print_books(const char *);                 // 打印所有图书编号的图书信息（A01,C03,B02）
int find_user_by_number(const char *);          // 根据图书证号查找用户，返回用户索引
int find_book_by_name_number(const char *);     // 根据图书名称或图书编号查找图书，返回图书索引
void add_user_books(int, const char *);         // 添加用户所借图书编号
void delete_user_books(int, const char *);      // 删除用户所借图书编号
void sort_books_price();                        // 根据图书价格排序
int read_file_int(FILE *fp);                    // 从文件中读取一个整型
float read_file_float(FILE *fp);                // 从文件中读取一个浮点型
void read_user_file();                          // 读取用户文件A.txt
void read_book_file();                          // 读取图书文件B.txt

/***************************************************************************************************/

/***********************************************主函数**********************************************/
int main() {
    read_files();        // 启动系统前读取文件加载图书信息和用户信息
    int option = 0;
    do {
        main_menu();                    // 主菜单
        scanf("%d", &option);
        switch (option) {
            case 1:
                query_menu();           // 查询
                break;
            case 2:
                borrow_books();         // 借书
                break;
            case 3:
                return_books();         // 还书
                break;
            case 4:
                sort_books();           // 排序
                break;
            default:
                printf("输入指令异常！\n");
                break;
        }
    } while (option);
    system("pause");
    return 0;
}
/***************************************************************************************************/


/**********************************************函数实现*********************************************/
/**
 * 输入图书编号，查询图书信息
 */
void query_book() {
    printf("请输入需要查询的图书编号：");
    char number[10];
    scanf("%s", number);
    for (int i = 0; i < BOOKS_SIZE; i++) {
        if (strcmp(Books[i].number, number) == 0) {    // 根据图书编号查询
            printf("图书编号：%s\n", Books[i].number);
            printf("图书名称：%s\n", Books[i].name);
            printf("图书价格：%.2f\n", Books[i].price);
            printf("图书总数：%d\n", Books[i].total);
            printf("现存数量：%d\n", Books[i].current);
            break;
        }
    }
}

/**
 * 打印指定图书编号的图书信息
 * @param number
 */
void print_book(const char *number) {
    for (int i = 0; i < BOOKS_SIZE; i++) {
        if (strcmp(Books[i].number, number) == 0) {     // 根据图书编号查询
            printf("图书编号：%s\t", Books[i].number);
            printf("图书名称：%s\t", Books[i].name);
            printf("图书价格：%.2f\n", Books[i].price);
            break;
        }
    }
}

/**
 * 打印所有图书编号的图书信息
 * @param str
 */
void print_books(const char *str) {
    char buf[10] = {0};        // str中的每个图书编号
    char *q = buf;
    while (*str != '\0') {
        *q++ = *str++;
        if (*str == ',' || *str == '\0') {
            *q = '\0';
            print_book(buf);        // 打印buf中存储的图书编号的图书信息
            q = buf;                // q指针重置
            str++;
        }
    }
}

/**
 * 输入图书证号，查询用户信息
 */
void query_user() {
    printf("请输入需要查询用户的图书证号：");
    char number[10];
    scanf("%s", number);
    for (int i = 0; i < USERS_SIZE; i++) {
        if (strcmp(Users[i].number, number) == 0) {     // 根据用户图书证号查询
            printf("图书证号：%s\t", Users[i].number);
            printf("姓名：%s\t", Users[i].name);
            printf("性别：%s\n", Users[i].sex);
            printf("共借书%d册，还可借书%d册", Users[i].quantity, Users[i].max_quantity - Users[i].quantity);

            if (Users[i].quantity > 0) {         // 用户借书数量不为0，就打印所借图书的信息
                printf("，借书情况如下：\n");
                print_books(Users[i].books);
            } else {
                printf("\n");
            }
            break;
        }
    }
}

/**
 * 根据图书证号查询，获取用户在数组中的索引
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
 * 根据图书编号或图书名称查询，获取图书在数组中的索引
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
 * 增加用户所借图书编号
 * @param user_index
 * @param book_number
 */
void add_user_books(int user_index, const char *book_number) {
    char *p = Users[user_index].books;
    if (*p != '\0') {      // books不为空，则将p指针移动到books的末尾
        while (*p != '\0') {
            p++;
        }
        *p++ = ',';
    }
    while (*book_number != '\0') {      // 将所借图书编号拷贝到books
        *p++ = *book_number++;
    }
}

/**
 * 删除用户所借图书编号
 * @param user_index
 * @param book_number
 */
void delete_user_books(int user_index, const char *book_number) {
    size_t len = strlen(book_number);            // 图书编号字符串长度
    char *p = Users[user_index].books;
    while (*p != '\0') {
        // 判断p指针所指向的字符串和book_number是否相同
        int flag = 1;
        for (int i = 0; i < len; i++) {
            if (*(p + i) != *(book_number + i)) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            break;            // flag为1，表示指针移动了到待删除图书编号
        }
        p++;
    }
    if (*(p - 1) == ',') {       // 删掉前面的','，避免出现（,B02,C03)这种情况
        p--;
    }
    while (*(p + len) != '\0') {      // 字符前移覆盖删掉的图书编号
        *p = *(p + len + 1);
        p++;
    }
}

/**
 * 借书
 */
void borrow_books() {
    char card_number[32];
    printf("请输入用户图书证号：");
    scanf("%s", card_number);
    int user_index = find_user_by_number(card_number);
    if (user_index < 0) {
        printf("该用户信息不存在，无法借阅！\n");
        return;
    }
    printf("请输入需要借阅的图书名称或图书编号：");
    char str[32];
    scanf("%s", str);
    int book_index = find_book_by_name_number(str);
    if (book_index < 0 || Books[book_index].current == 0) {
        printf("无法借阅，图书不存在或图书已全部借出！\n");
        return;
    }
    Users[user_index].quantity++;        // 借书加一
    Books[book_index].current--;         // 库存减一

    // 把所借图书编号存到books
    add_user_books(user_index, Books[book_index].number);
    // 保存
    write_files();
    printf("借书成功！\n");
}

/**
 * 还书
 */
void return_books() {
    char card_number[32];
    printf("请输入用户图书证号：");
    scanf("%s", card_number);
    int user_index = find_user_by_number(card_number);
    if (user_index < 0) {
        printf("该用户信息不存在，无法还书！\n");
        return;
    }
    printf("请输入需要归还的图书名称或图书编号：");
    char str[32];
    scanf("%s", str);
    int book_index = find_book_by_name_number(str);
    if (book_index < 0 || Books[book_index].current + 1 > Books[book_index].total) {
        printf("无法还书，图书不存在或现存数量超过图书总数！\n");
        return;
    }
    Users[user_index].quantity--;        // 借书减一
    Books[book_index].current++;        // 库存加一
    // 把所借图书编号从books删除
    delete_user_books(user_index, Books[book_index].number);
    // 保存
    write_files();
    printf("还书成功！\n");
}

/**
 * 根据图书价格排序（冒泡排序）
 */
void sort_books_price() {
    // 冒泡排序
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
        if (flag == 0) {          // 本轮排序没有任何元素交换，说明数组排序完成，结束循环
            break;
        }
    }
}

/**
 * 排序打印输出
 */
void sort_books() {
    sort_books_price();
    printf("******************************************************************\n");
    printf("图书编号    图书名称      图书价格     现存数量    图书总数\n");
    for (int i = 0; i < BOOKS_SIZE; i++) {
        printf("%-8s %-16s %-13.2f %-10d %-10d\n",
               Books[i].number, Books[i].name, Books[i].price, Books[i].current, Books[i].total);
    }
    printf("******************************************************************\n");
}

/**
 * 读取文件指针所指向的整型
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
 * 读取文件指针所指向的浮点型
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
 * 读取用户信息文件A.txt
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
            i++;            // 遇到换行符，读取下一个用户信息
        } else {
            fseek(fp, -1, SEEK_CUR);        // fp指针向前移动一位
        }
        if (i >= USERS_SIZE) {           // 超过最大用户数退出循环，不再继续读取文件
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
 * 读取图书信息文件B.txt
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
            i++;            // 遇到换行符，读取下一个图书信息
        } else {
            fseek(fp, -1, SEEK_CUR);        // fp指针回退一位
        }
        if (i >= BOOKS_SIZE) {  // 超过最大图书数退出循环，不再继续读取文件
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
 * 读取加载图书和用户的文件信息
 */
void read_files() {
    read_user_file();
    read_book_file();
}

/**
 * 将图书和用户信息保存至文件
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
 * 主菜单
 */
void main_menu() {
    printf("******************************************************************\n");
    printf("************************** 书籍借阅系统 **************************\n");
    printf("*                          1 - 查询功能                          *\n");
    printf("*                          2 - 借书功能                          *\n");
    printf("*                          3 - 还书功能                          *\n");
    printf("*                          4 - 排序功能                          *\n");
    printf("*                          0 - 退出系统                          *\n");
    printf("******************************************************************\n");
}

/**
 * 查询菜单
 */
void query_menu() {
    printf("**************************** 借书功能 ****************************\n");
    printf("*                          1 - 图书查询                          *\n");
    printf("*                          2 - 用户信息查询                      *\n");
    printf("*                          0 - 返回上一层                        *\n");
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
