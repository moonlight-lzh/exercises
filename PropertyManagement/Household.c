#include "Definitions.h"

/// ��ӡ��ͷ
void Household_Header() {
    putchar('\n');
    CUTTING_LINE();
    printf("��������  �Ա�  ���֤             ��ϵ�绰      ¥��  ��Ԫ��  ����   ���   ÿƽ����ҵ�۸�    Ӧ����ҵ��    ��ע\n");
    CUTTING_LINE();
}

/// ��ӡһ��ס����Ϣ
void Household_Print( Household data) {
    printf("%-11s%-4s%-19s%-13s%-5s%-6s%-6s%-12.2f%-13.2f%-11.2f%-12s\n",
           data.name, data.gender, data.idcard, data.phone, data.building,
           data.unit, data.room, data.area, data.price, data.payment, data.remark);
}

/// ���ַ����ж�ȡһ���ַ����������ո���ֹ
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

/// ��ȡ�ļ��е�һ�����ݣ�д��ṹ����
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

/// ��ס����Ϣд���ļ���һ��
void Household_WriteFile(FILE *fp, Household data) {
    fprintf(fp, "%s %s %s %s %s %s %s %.2f %.2f %.2f %s\n",
              data.name, data.gender, data.idcard, data.phone, data.building,
              data.unit, data.room, data.area, data.price, data.payment, data.remark);
}