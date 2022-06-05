#include "Definitions.h"

/// 读取文件至数组
void Array_ReadFile(struct Array *array) {
    FILE *fp;
    int i;

    array->size = 0;        // 初始数组长度

    fp = fopen(DATA_FILE_NAME, "r");        // 只读的方式打开文件
    if (fp == NULL) {
        return;
    }

    fscanf(fp, "%d\n", &array->size);     // 读取第一行的元素的个数

    for (i = 0; i < array->size; ++i) {
        Household_ReadFile(fp, &array->data[i]);     // 从文件读取一行数据
    }
    fclose(fp);     // 关闭文件指针
}

/// 将数组中的数据写入文件
void Array_WriteFile(struct Array *array) {
    FILE *fp;
    int i;

    fp = fopen(DATA_FILE_NAME, "w");        // 只写的方式打开文件
    if (fp == NULL) {
        printf("保存数据打开文件失败：%s\n", strerror(errno));
        return;
    }

    fprintf(fp, "%d\n", array->size);     // 第一行写入元素个数

    for (i = 0; i < array->size; i++) {
        Household_WriteFile(fp, array->data[i]);       // 数据写入文件的每一行
    }
    fclose(fp);     // 关闭文件指针
}


/// 根据楼号进行数组排
void Array_SortBuilding(struct Array *array) {
    int i, j, flag;
    Household temp;

    // 冒泡排序
    for (i = 0; i < array->size - 1; i++) {
        flag = 1;
        for (j = 0; j < array->size - i - 1; j++) {
            if (strcmp(array->data[j].building, array->data[j + 1].building) > 0) {
                temp = array->data[j];
                array->data[j] = array->data[j + 1];
                array->data[j + 1] = temp;
                flag = 0;
            }
        }
        if (flag) {
            break;
        }
    }
}

/// 根据户主姓名查询数组
int Array_SearchName(struct Array array, const char *name) {
    int i;
    for (i = 0; i < array.size; i++) {
        if (strcmp(array.data[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

