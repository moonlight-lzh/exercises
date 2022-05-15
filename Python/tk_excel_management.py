from tkinter import *
from tkinter import ttk
import tkinter.messagebox
import pandas as pd

bg_color = '#579CD5'  # background color
excel_file_name = 'achieves/学生信息.xlsx'  # excel file name


class QueryToplevel:
    """
    查询窗体
    """

    def __init__(self, parent):
        self.parent = parent
        self.window = Toplevel(parent.window)
        self.window.withdraw()
        self.window.title('查询')
        self.window.geometry("320x140+%d+%d" % (parent.x + parent.width // 2 - 160, parent.y + 70))
        self.window.resizable(0, 0)

        self.var_query_condition = StringVar()
        self.var_query_text = StringVar()
        self.result = None

        Label(self.window, text='查询条件：').grid(row=0, column=0, padx=(10, 0), pady=10)
        Label(self.window, text='查询内容：').grid(row=1, column=0, padx=(10, 0), pady=10)

        self.combobox = ttk.Combobox(self.window, width=25, textvariable=self.var_query_condition)
        self.combobox['value'] = ('姓名', '学号')
        self.combobox.grid(row=0, column=1, columnspan=2, padx=(0, 15), pady=10)

        Entry(self.window, width=25, textvariable=self.var_query_text) \
            .grid(row=1, column=1, columnspan=2, padx=(0, 15), pady=10)

        Button(self.window, text="查询", width=10, command=self.ok) \
            .grid(row=2, column=0, padx=(20, 10), pady=10)
        Button(self.window, text="退出", width=10, command=self.cancel) \
            .grid(row=2, column=1, padx=(10, 20), pady=10)

        self.reset_value()
        self.window.protocol("WM_DELETE_WINDOW", self.cancel)

    def reset_value(self):
        self.combobox.current(0)
        self.var_query_text.set('')

    def ok(self):
        condition = self.var_query_condition.get()
        text = self.var_query_text.get().strip()
        if len(condition) == 0:
            tkinter.messagebox.showinfo('提示', '请选择查询条件')
            self.result = None
        elif len(text) == 0:
            tkinter.messagebox.showinfo('提示', '请输入查询内容')
            self.result = None
        else:
            self.result = (condition, int(text) if condition == '学号' else text)
            self.window.withdraw()
            self.parent.query_record()

    def cancel(self):
        self.result = None
        self.window.withdraw()

    def show(self):
        self.reset_value()
        self.window.deiconify()


class Application(object):
    """
    应用程序主窗体
    """

    def __init__(self, title, width, height):
        """
        构造函数
        :param title: 窗体标题
        :param width: 窗体的宽
        :param height: 窗体的高
        """
        # init window
        self.window = Tk()
        self.window.title(title)
        self.window.resizable(False, False)
        self.window['bg'] = bg_color
        self.width = width
        self.height = height

        # center screen
        sw = self.window.winfo_screenwidth()
        sh = self.window.winfo_screenheight()
        self.x = (sw - width) / 2
        self.y = (sh - height) / 2
        self.window.geometry("%dx%d+%d+%d" % (width, height, self.x, self.y))

        # query toplevel
        self.query_window = QueryToplevel(self)

        # create frame
        frame_l = Frame(self.window, bg=bg_color)
        frame_tr = Frame(self.window, bg=bg_color)
        frame_br = Frame(self.window, bg=bg_color)
        frame_l.pack(fill=Y, side=LEFT)
        frame_tr.pack(side=TOP)
        frame_br.pack(side=BOTTOM)

        self.name_label = Label(frame_l, text="姓名：", bg=bg_color)
        self.num_label = Label(frame_l, text="学号：", bg=bg_color)
        self.grade_label = Label(frame_l, text="成绩：", bg=bg_color)

        self.var_name = StringVar()
        self.var_num = StringVar()
        self.var_grade = StringVar()

        self.name_entry = Entry(frame_l, width=25, textvariable=self.var_name)
        self.num_entry = Entry(frame_l, width=25, textvariable=self.var_num)
        self.grade_entry = Entry(frame_l, width=25, textvariable=self.var_grade)

        self.name_entry.configure()

        self.prev_button = Button(frame_l, bg='#FFC102', text="上一个", width=8, command=self.prev_record)
        self.query_button = Button(frame_l, bg='#FFC102', text="查询", width=8, command=self.query_window.show)
        self.next_button = Button(frame_l, bg='#FFC102', text="下一个", width=8, command=self.next_record)

        # read excel data
        self.df = pd.DataFrame(pd.read_excel(excel_file_name, engine='openpyxl'))
        self.current = 0
        self.show_record()

    def pack(self):
        """
        放置组件
        :return: None
        """
        self.name_label.grid(column=0, row=0, padx=(10, 0), pady=(50, 10))
        self.num_label.grid(column=0, row=1, padx=(10, 0), pady=10)
        self.grade_label.grid(column=0, row=2, padx=(10, 0), pady=10)

        self.name_entry.grid(column=1, row=0, columnspan=2, padx=(0, 15), pady=(50, 10))
        self.num_entry.grid(column=1, row=1, columnspan=2, padx=(0, 15))
        self.grade_entry.grid(column=1, row=2, columnspan=2, padx=(0, 15))

        self.prev_button.grid(column=0, row=3, pady=15, padx=(15, 0), ipadx=10)
        self.query_button.grid(column=1, row=3, padx=10, ipadx=12)
        self.next_button.grid(column=2, row=3, padx=(0, 15), ipadx=10)

    def show_record(self):
        """
        显示当前current处的学生信息
        :return: None
        """
        self.var_name.set(self.df.iloc[self.current, 0])
        self.var_num.set(self.df.iloc[self.current, 1])
        self.var_grade.set(self.df.iloc[self.current, 2])

    def show(self):
        """
        显示主窗体
        :return: None
        """
        self.pack()
        self.window.mainloop()

    def prev_record(self):
        """
        显示上一条记录
        :return: None
        """
        if self.current > 0:
            self.current -= 1
            self.show_record()
        else:
            tkinter.messagebox.showinfo('提示', '第一条记录')

    def next_record(self):
        """
        显示下一条记录
        :return: None
        """
        if self.current + 1 < self.df.shape[0]:
            self.current += 1
            self.show_record()
        else:
            tkinter.messagebox.showinfo('提示', '最后一条记录')

    def query_record(self):
        """
        查询记录
        :return: None
        """
        if self.query_window.result is None:
            return

        # 显示查询结果
        result = self.df[self.df[self.query_window.result[0]] == self.query_window.result[1]]
        if result is not None and not result.empty:  # 显示第一条记录
            self.current = result.index[0]
            self.show_record()
        else:
            tkinter.messagebox.showinfo('提示', '未查询到任何记录')


if __name__ == '__main__':
    app = Application("基于Excel文件的数据管理", 640, 300)
    app.show()
