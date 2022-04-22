from turtle import *
import datetime


class Numeric(object):
    lines = ()
    width = 0

    def draw_line(self, index):
        if self.lines[index] == 1:
            pendown()
            forward(line_width)
        else:
            penup()
            forward(line_width)

    def draw(self):
        setheading(0)  # 默认朝右

        self.draw_line(0)
        draw_gap(gap // 2)
        right(90)
        draw_gap(gap // 2)
        self.draw_line(1)
        draw_gap(gap)
        self.draw_line(2)
        draw_gap(gap // 2)
        right(90)
        draw_gap(gap // 2)
        self.draw_line(3)
        draw_gap(gap // 2)
        right(90)
        draw_gap(gap // 2)
        self.draw_line(4)
        draw_gap(gap)
        self.draw_line(5)

        if self.lines[6] == 1:
            right(180)
            penup()
            forward(line_width + gap // 2)
            left(90)
            forward(gap // 2)
            self.draw_line(6)


class Zero(Numeric):
    def __init__(self):
        super().__init__()
        self.lines = (1, 1, 1, 1, 1, 1, 0)
        self.width = line_width + gap


class One(Numeric):
    def __init__(self):
        super().__init__()
        self.lines = (0, 0, 0, 0, 1, 1, 0)
        self.width = gap

    def draw(self):
        setheading(270)
        draw_gap(gap // 2)
        self.draw_line(4)
        draw_gap(gap)
        self.draw_line(5)


class Two(Numeric):
    def __init__(self):
        super().__init__()
        self.lines = (1, 1, 0, 1, 1, 0, 1)
        self.width = line_width + gap


class Three(Numeric):
    def __init__(self):
        super().__init__()
        self.lines = (1, 1, 1, 1, 0, 0, 1)
        self.width = line_width + gap


class Four(Numeric):
    def __init__(self):
        super().__init__()
        self.lines = (0, 1, 1, 0, 0, 1, 1)
        self.width = line_width + gap


class Five(Numeric):
    def __init__(self):
        super().__init__()
        self.lines = (1, 0, 1, 1, 0, 1, 1)
        self.width = line_width + gap


class Six(Numeric):
    def __init__(self):
        super().__init__()
        self.lines = (1, 0, 1, 1, 1, 1, 1)
        self.width = line_width + gap


class Seven(Numeric):
    def __init__(self):
        super().__init__()
        self.lines = (1, 1, 1, 0, 0, 0, 0)
        self.width = line_width + gap


class Eight(Numeric):
    def __init__(self):
        super().__init__()
        self.lines = (1, 1, 1, 1, 1, 1, 1)
        self.width = line_width + gap


class Nine(Numeric):
    def __init__(self):
        super().__init__()
        self.lines = (1, 1, 1, 1, 0, 1, 1)
        self.width = line_width + gap


def draw_gap(mg):
    penup()
    forward(mg)
    pendown()


def draw_datetime(start_x, start_y, d_num, d_type, d_color):
    color(d_color)  # set color
    penup()
    goto(start_x, start_y)
    str_num = str(d_num)
    if d_num < 10:
        str_num = '0' + str_num  # fill '0'

    for x in str_num:
        num = numbers[int(x)]  # find Numeric object
        num.draw()  # draw Numeric
        penup()
        start_x += num.width + interval  # move to next
        goto(start_x, start_y)

    # draw text
    penup()
    goto(start_x + 14, start_y - 30)
    write(d_type, move=True, align='center', font=('arial', 12, 'normal'))
    start_x += 35
    return start_x, start_y  # update x,y


line_width = 30
gap = 6
interval = 15
sx, sy = -300, 300
numbers = (Zero(), One(), Two(), Three(), Four(), Five(), Six(), Seven(), Eight(), Nine())

if __name__ == '__main__':
    # settings
    hideturtle()
    pensize(3)
    speed(10)

    # get datetime now
    cur_time = datetime.datetime.now()

    # draw year/month/day
    sx, sy = draw_datetime(sx, sy, cur_time.year, '年', 'red')
    sx, sy = draw_datetime(sx, sy, cur_time.month, '月', 'green')
    sx, sy = draw_datetime(sx, sy, cur_time.day, '日', 'blue')

    # goto x,y
    del sx, sy
    sx, sy = -300, 200

    # draw hour/minute/second
    sx, sy = draw_datetime(sx, sy, cur_time.hour, '时', 'red')
    sx, sy = draw_datetime(sx, sy, cur_time.minute, '分', 'green')
    sx, sy = draw_datetime(sx, sy, cur_time.second, '秒', 'blue')

    done()
