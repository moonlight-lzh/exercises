#include "Definitions.h"

/// 打印表头
void Household_Header() {
    putchar('\n');
    CUTTING_LINE();
    printf("户主姓名  性别  身份证             联系电话      楼号  单元号  房号   面积   每平方物业价格    应缴物业费    备注\n");
    CUTTING_LINE();
}

/// 打印一行住户信息
void Household_Print( Household data) {
    printf("%-11s%-4s%-19s%-13s%-5s%-6s%-6s%-12.2f%-13.2f%-11.2f%-12s\n",
           data.name, data.gender, data.idcard, data.phone, data.building,
           data.unit, data.room, data.area, data.price, data.payment, data.remark);
}

/// 从字符串中读取一个字符串，遇到空格终止
void Household_ReadString(char *dest, char *src, char **end) {
    while (*src) {
        if (*src == ' ' || *src == '\t' || *src == '\r' || *src == '\n') {
            src++;
            continue;
        }

        *dest++ = *src++;

        if (*src == ' ' || *src == '\t' || *src == '\r' || *src == '\n') {
            *dest = '\0';
            *end = src;
            break;
        }
    }
}

/// 读取文件中的一行数据，写入结构体中
void Household_ReadFile(FILE *fp, Household *data) {
    if (feof(fp)) {
        return;
    }
    char buf[256];
    fgets(buf, 128, fp);

    char *ptr = buf;
    Household_ReadString(data->name, ptr, &ptr);
    Household_ReadString(data->gender, ptr, &ptr);
    Household_ReadString(data->idcard, ptr, &ptr);
    Household_ReadString(data->phone, ptr, &ptr);
    Household_ReadString(data->building, ptr, &ptr);
    Household_ReadString(data->unit, ptr, &ptr);
    Household_ReadString(data->room, ptr, &ptr);

    data->area = (float) strtod(ptr, &ptr);
    data->price = (float) strtod(ptr, &ptr);
    data->payment = (float) strtod(ptr, &ptr);

    Household_ReadString(data->remark, ptr, &ptr);
}

/// 将住户信息写入文件的一行
void Household_WriteFile(FILE *fp, Household data) {
    fprintf(fp, "%s %s %s %s %s %s %s %.2f %.2f %.2f %s\n",
              data.name, data.gender, data.idcard, data.phone, data.building,
              data.unit, data.room, data.area, data.price, data.payment, data.remark);
}