import os


class Census:
    """
    人口普查类
    """
    titles = ['姓名', '性别', '身份证号', '民族', '受教育程度', '籍贯', '住址', '出生日期']  # 标题

    def __init__(self, name=None, gender=None, idcard=None, nation=None, education=None, origin=None, address=None,
                 birthday=None):
        self.name = name  # 姓名
        self.gender = gender  # 性别
        self.idcard = idcard  # 身份证号
        self.nation = nation  # 民族
        self.education = education  # 受教育程度
        self.origin = origin  # 籍贯
        self.address = address  # 住址
        self.birthday = birthday  # 出生日期

    def __str__(self):
        ls = [self.name, self.gender, self.idcard, self.nation, self.education, self.origin, self.address,
              self.birthday]
        return ' '.join(map(str, ls))

    def set_name(self, name):
        self.name = name

    def set_gender(self, gender):
        self.gender = gender

    def set_idcard(self, idcard):
        self.idcard = idcard

    def set_nation(self, nation):
        self.nation = nation

    def set_education(self, education):
        self.education = education

    def set_origin(self, origin):
        self.origin = origin

    def set_address(self, address):
        self.address = address

    def set_birthday(self, birthday):
        self.birthday = birthday


class Management:
    """
    人口普查管理类
    """

    def __init__(self):
        """
        构造函数
        """
        self.list = list()  # 数据列表
        self.filepath = 'census.dat'  # 数据文件路径

    def input(self):
        """
        人口普查数据录入
        """
        census = Census()
        print('请输入：')
        census.name = input('姓名: ')
        census.gender = input('性别: ')
        census.idcard = input('身份证号: ')

        if self.search_by_idcard(census.idcard) is None:
            census.nation = input('民族: ')
            census.education = input('受教育程度: ')
            census.origin = input('籍贯: ')
            census.address = input('住址: ')
            census.birthday = input('出生日期: ')
            # 新录入的人口普查数据对象添加到列表
            self.list.append(census)
            # 保存数据文件
            self.save_file()
            print('录入成功！')
        else:
            print('无法录入，您所输入的身份证号已存在！')

    def browsing(self, data=None):
        """
        浏览数据
        :param data: 默认None浏览全部人口普查信息
        """
        format_print_title()
        if not data:
            data = self.list
        for item in data:
            format_print_row(item)
        cutting_line('+')

    def search(self):
        """
        人口普查信息查询
        """
        print("请选择查询条件：")
        print("    1.按姓名查询")
        print("    2.按身份证号查询")
        choice = int(input('->'))

        if choice == 1:
            name = input("请输入需要查询的姓名：")
            find = list(filter(lambda x: x.name == name, self.list))
        elif choice == 2:
            idcard = input("请输入需要查询的身份证：")
            find = list(filter(lambda x: x.idcard == idcard, self.list))
        else:
            find = None

        if find is None or len(find) == 0:
            print('查询失败，不存在相关记录')
        else:
            self.browsing(find)

    def search_by_idcard(self, idcard):
        """
        根据身份证号查询
        :param idcard: 身份证号
        :return: 人口普查对象
        """
        find = list(filter(lambda x: x.idcard == idcard, self.list))
        if find is not None and len(find) == 1:
            return find[0]
        else:
            return None

    def sort(self):
        """
        人口普查数据排序
        """
        print('  1.按姓名排序')
        print('  2.按住址排序')
        choice = int(input('->'))
        if choice == 1:
            # 按姓名排序
            self.list.sort(key=lambda item: item.name)
        elif choice == 2:
            # 按住址排序
            self.list.sort(key=lambda item: item.address)
        else:
            return

        # 查看数据
        self.browsing()

    def delete(self):
        """
        删除人口普查信息
        """
        idcard = input('请输入需要删除的身份证号：')

        # 根据姓名删除对象
        if self.del_by_idcard(idcard):
            # 保存文件
            self.save_file()
            print('删除成功！')

    def modify(self):
        """
        修改人口普查信息
        """
        idcard = input('输入身份证号：')
        # 根据书名查询人口普查对象
        find = self.search_by_idcard(idcard)
        if find is None:
            print('不存在该人口普查信息！')
            return
        print('请选择：')
        print('  1.姓名')
        print('  2.性别')
        print('  3.身份证号')
        print('  4.民族')
        print('  5.受教育程度')
        print('  6.籍贯')
        print('  7.住址')
        print('  8.出生日期')
        print('  0.返回')
        choice = int(input('->'))
        if choice not in range(1, 9):
            print('输入指令错误')
            return
        s = input("请输入修改后的内容：")
        switcher = [find.set_name, find.set_gender, find.set_idcard, find.set_nation, find.set_education,
                    find.set_origin, find.set_address, find.set_birthday]
        if choice == 3 and self.search_by_idcard(s) is not None:
            print("修改失败，您所输入的身份证号已存在！")
        else:
            switcher[choice - 1](s)
            self.save_file()
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
                values = line.split()
                census = Census(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7])
                self.list.append(census)

    def save_file(self):
        """
        保存数据文件
        """
        lines = [str(s) + '\n' for s in self.list]
        with open(self.filepath, 'w+', encoding='utf-8') as f:
            f.writelines(lines)

    def del_by_idcard(self, idcard):
        """
        根据书名删除人口普查对象
        :param idcard: 身份证
        :return: 删除是否成功，成功返回true，失败返回false
        """
        find = self.search_by_idcard(idcard)
        if find is None:
            print('删除失败，未查询到相关记录！')
            return False
        confirm = input('是否删除？（y/n）: ')
        if confirm == 'y' or confirm == 'Y':
            self.list.remove(find)
            return True
        else:
            print('取消删除记录！')
            return False


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
          '---------------------------{0}'.format(fill))


def format_print_title():
    """
    格式化打印标题
    """
    cutting_line('+')
    pattern = "|{0:{8}^6}|{1:{8}^6}|{2:{8}^14}|{3:{8}^6}|{4:{8}^8}|{5:{8}^8}|{6:{8}^14}|{7:^9}|"
    print(pattern.format(Census.titles[0], Census.titles[1], Census.titles[2], Census.titles[3], Census.titles[4],
                         Census.titles[5], Census.titles[6], Census.titles[7], chr(12288)))
    cutting_line('+')


def format_print_row(census):
    """
    格式化打印一条人口普查记录
    :param census: 人口普查对象
    """
    pattern = "|{0:{8}^6}|{1:{8}^6}|{2:^22}|{3:{8}^6}|{4:{8}^8}|{5:{8}^8}|{6:{8}^14}|{7:^12}|"
    print(pattern.format(census.name, census.gender, census.idcard, census.nation, census.education, census.origin,
                         census.address, census.birthday, chr(12288)))


def show_menu():
    """
    显示系统菜单
    """
    cutting_line()
    print('人 口 普 查 数 据 管 理 系 统'.center(120))
    cutting_line()
    print('1.人口普查数据录入'.center(120))
    print('2.人口普查数据浏览'.center(120))
    print('3.人口普查数据查询'.center(120))
    print('4.人口普查数据排序'.center(120))
    print('5.人口普查数据删除'.center(120))
    print('6.人口普查数据修改'.center(120))
    print('0.退 出 系 统'.center(120))
    cutting_line()


if __name__ == '__main__':
    print('欢迎进入人口普查数据管理系统！\n')

    # 创建人口普查数据管理对象
    manage = Management()

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
