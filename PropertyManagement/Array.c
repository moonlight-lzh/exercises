#include "Definitions.h"

/// ��ȡ�ļ�������
void Array_ReadFile(struct Array *array) {
    FILE *fp;
    int i;

    array->size = 0;        // ��ʼ���鳤��

    fp = fopen(DATA_FILE_NAME, "r");        // ֻ���ķ�ʽ���ļ�
    if (fp == NULL) {
        return;
    }

    fscanf(fp, "%d\n", &array->size);     // ��ȡ��һ�е�Ԫ�صĸ���

    for (i = 0; i < array->size; ++i) {
        Household_ReadFile(fp, &array->data[i]);     // ���ļ���ȡһ������
    }
    fclose(fp);     // �ر��ļ�ָ��
}

/// �������е�����д���ļ�
void Array_WriteFile(struct Array *array) {
    FILE *fp;
    int i;

    fp = fopen(DATA_FILE_NAME, "w");        // ֻд�ķ�ʽ���ļ�
    if (fp == NULL) {
        printf("�������ݴ��ļ�ʧ�ܣ�%s\n", strerror(errno));
        return;
    }

    fprintf(fp, "%d\n", array->size);     // ��һ��д��Ԫ�ظ���

    for (i = 0; i < array->size; i++) {
        Household_WriteFile(fp, array->data[i]);       // ����д���ļ���ÿһ��
    }
    fclose(fp);     // �ر��ļ�ָ��
}


/// ����¥�Ž���������
void Array_SortBuilding(struct Array *array) {
    int i, j, flag;
    Household temp;

    // ð������
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

/// ���ݻ���������ѯ����
int Array_SearchName(struct Array array, const char *name) {
    int i;
    for (i = 0; i < array.size; i++) {
        if (strcmp(array.data[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

