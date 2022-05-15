import os


class Book:
    """
    图书类
    """
    titles = ['登录号', '书名', '作者名', '分类号', '出版单位', '出版时间', '价格']  # 标题

    def __init__(self):
        """
        默认的构造函数
        """
        self.login = None  # 登录名
        self.name = None  # 书名
        self.author = None  # 作者名
        self.classify = None  # 分类号
        self.publisher = None  # 出版单位
        self.pubdate = None  # 出版时间
        self.price = None  # 价格

    def set_login(self, val):
        self.login = val

    def set_name(self, val):
        self.name = val

    def set_author(self, val):
        self.author = val

    def set_classify(self, val):
        self.classify = val

    def set_publisher(self, val):
        self.publisher = val

    def set_pubdate(self, val):
        self.pubdate = val

    def set_price(self, val):
        self.price = val

    def tostring(self):
        """
        图书对象转字符串
        :return:
        """
        ls = [self.login, self.name, self.author, self.classify, self.publisher, self.pubdate, self.price]
        return ' '.join(map(str, ls))


class BooksManagement:
    """
    图书管理类
    """

    def __init__(self):
        """
        构造函数
        """
        self.list = list()  # 图书列表
        self.filepath = 'books.txt'  # 数据文件路径

    def input(self):
        """
        图书信息录入
        """
        book = Book()
        print('请输入：')
        book.login = input('登录号: ')
        book.name = input('书名: ')
        book.author = input('作者名: ')
        book.classify = input('分类号: ')
        book.publisher = input('出版单位: ')
        book.pubdate = input('出版时间: ')
        book.price = input('价格: ')
        # 新录入的图书对象添加到列表
        self.list.append(book)
        # 保存数据文件
        self.save_file()
        print('录入成功！')

    def browsing(self, data=None):
        """
        浏览数据
        :param data: 默认None浏览全部图书信息
        """
        format_print_title()
        if not data:
            data = self.list
        for book in data:
            format_print_row(book)
        cutting_line('+')

    def search(self):
        """
        图书信息查询
        """
        print(' 1.按书名查询')
        print(' 2.按作者名查询')
        choice = int(input('->'))
        if choice == 1:
            # 根据输入的书名查询
            ls = self.search_by_name(input())
            if ls is not None:
                ls = [ls]
        elif choice == 2:
            # 根据输入的作者名查询
            ls = self.search_by_author(input())
        else:
            return
        if ls is not None and len(ls) > 0:
            # 浏览查询结果
            self.browsing(ls)
        else:
            print('查询失败，不存在相关记录')

    def sort(self):
        """
        图书排序
        """
        print('  1.按登录号排序')
        print('  2.按分类号排序')
        print('  3.按价格排序')
        choice = int(input('->'))
        if choice == 1:
            # 根据登录号排序
            self.list.sort(key=lambda book: book.login)
        elif choice == 2:
            # 按分类号排序
            self.list.sort(key=lambda book: book.classify)
        elif choice == 3:
            # 按价格排序
            self.list.sort(key=lambda book: book.price)
        else:
            return

        # 查看数据
        self.browsing()

    def delete(self):
        """
        删除图书信息
        """
        name = input('请输入需要删除的书名：')

        # 根据书名删除图书对象
        if self.del_by_name(name):
            # 保存文件
            self.save_file()
            print('删除成功！')

    def modify(self):
        """
        修改图书信息
        """
        name = input('输入书名：')
        # 根据书名查询图书对象
        book = self.search_by_name(name)
        if book is None:
            print('不存在该图书信息！')
            return

        print('请选择：')
        print('  1.登录号')
        print('  2.书名')
        print('  3.作者名')
        print('  4.分类号')
        print('  5.出版单位')
        print('  6.出版时间')
        print('  7.价格')
        print('  0.返回')
        choice = int(input('->'))
        if choice not in range(1, 8):
            return
        # 构建属性修改函数列表
        switcher = [None, book.set_login, book.set_name, book.set_author, book.set_classify, book.set_publisher,
                    book.set_pubdate, book.set_price]
        switcher[choice](input('输入目标值：'))
        print('修改成功！')

    def read_file(self):
        """
        读取数据文件
        """
        # 是否存在数据文件
        if not os.path.exists(self.filepath):
            return
        with open(self.filepath, 'r', encoding='utf-8') as f:
            for line in f.readlines():
                if len(line.strip()) == 0:  # 跳过空行
                    continue
                book = Book()
                book.login, book.name, book.author, book.classify, book.publisher, book.pubdate, book.price \
                    = line.split()
                self.list.append(book)

    def save_file(self):
        """
        保存数据文件
        """
        lines = [s.tostring() + '\n' for s in self.list]
        with open(self.filepath, 'w+', encoding='utf-8') as f:
            f.writelines(lines)

    def del_by_name(self, name):
        """
        根据书名删除图书对象
        :param name: 书名
        :return: 删除是否成功，成功返回true，失败返回false
        """
        book = self.search_by_name(name)
        if book is None:
            print('删除失败，未查询到相关记录！')
            return False
        confirm = input('是否删除？（y/n）: ')
        if confirm == 'y' or confirm == 'Y':
            self.list.remove(book)
            return True
        else:
            print('取消删除记录！')
            return False

    def search_by_name(self, name):
        """
        根据书名查询图书
        :param name: 书名
        :return: 查询到的图书对象，查询失败返回None
        """
        for item in self.list:
            if item.name == name:
                return item
        return None

    def search_by_author(self, author):
        """
        根据作者名查询图书
        :param author: 作者名
        :return: 查询到的图书列表，查询失败列表为空
        """
        ls = []
        for item in self.list:
            if item.author == author:
                ls.append(item)
        return ls


def wait_continue():
    """
    按任意键返回
    :return:
    """
    input('按任意键返回...')


def cutting_line(fill='-'):
    """
    打印一条分割线
    :param fill: 两端填充符号，默认'-'
    """
    print('{0}-------------------------------------------------------------------------------------------'
          '-------------------------{0}'.format(fill))


def format_print_title():
    """
    格式化打印标题
    """
    cutting_line('+')
    pattern = "|{0:{7}^8}|{1:{7}^12}|{2:{7}^8}|{3:{7}^8}|{4:{7}^12}|{5:{7}^7}|{6:{7}^7}|"
    print(pattern.format(Book.titles[0], Book.titles[1], Book.titles[2], Book.titles[3], Book.titles[4], Book.titles[5],
                         Book.titles[6], chr(12288)))
    cutting_line('+')


def format_print_row(book):
    """
    格式化打印一条图书记录
    :param book: 图书对象
    """
    pattern = "|{0:{7}^10}|{1:{7}^12}|{2:{7}^8}|{3:{7}^10}|{4:{7}^12}|{5:{7}^11}|{6:{7}^8}|"
    print(pattern.format(book.login, book.name, book.author, book.classify, book.publisher, book.pubdate,
                         book.price, chr(12288)))


def show_menu():
    """
    显示系统菜单
    """
    cutting_line()
    print('图 书 信 息 管 理 系 统'.center(118))
    cutting_line()
    print('1.图书信息录入'.center(118))
    print('2.图书信息浏览'.center(118))
    print('3.图书信息查询'.center(118))
    print('4.图书信息排序'.center(118))
    print('5.图书信息删除'.center(118))
    print('6.图书信息修改'.center(118))
    print('0.退 出 系 统'.center(120))
    cutting_line()


if __name__ == '__main__':
    print('欢迎进入图书信息管理系统！\n')

    # 创建图书管理对象
    manage = BooksManagement()

    # 读取数据文件
    manage.read_file()

    # 构建功能函数列表
    funcs = [None, manage.input, manage.browsing, manage.search, manage.sort, manage.delete, manage.modify]
    while True:
        # 显示主菜单
        show_menu()
        try:
            op = int(input('->'))
        except Exception as e:
            print('输入指令异常: ', e)
            continue
        if op == 0:
            print('系统即将退出，感谢您的使用！')
            break
        if 0 < op < len(funcs):
            # 执行功能函数
            funcs[op]()
            wait_continue()
        else:
            print('指令异常！')
