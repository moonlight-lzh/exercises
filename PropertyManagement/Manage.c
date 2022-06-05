#include "Definitions.h"


/// �û���¼
void Manage_Login() {
    int flag = 0, i = 0;
    char user[10], pwd[10];
    do {
        system("cls");
        i++;        // ��¼����
        printf("\n----------------------------------------�� �� �� ¼----------------------------------------\n");
        printf("                                    �����û�����");
        scanf("%s", user);
        printf("                                    �������룺");
        scanf("%s", pwd);
        if (strcmp(user, LOGIN_USER) == 0 && strcmp(pwd, LOGIN_PWD) == 0) {
            flag = 1;
            break;
        }
        printf("�û���������������������롣\n");
        _getch();
    } while (i < 3);

    if (!flag) {
        printf("�����������������ϵͳ�����˳�\n");
        exit(0);
    }
    CUTTING_LINE();
}

/// ����ס��
void Manage_Input() {
    Household *data;
    struct LinkedList list;
    char name[32];
    char other_name[32];

    LinkedList_ReadFile(&list);         // ��ȡ�ļ�������

    printf("������\n");
    printf("����������");
    scanf("%s", name);

    if (LinkedList_SearchName(list, name)) {        // ��ѯ�������Ƿ���ڸû�������
        LinkedList_Destroy(&list);                  //�ͷ�����
        printf("����ʧ�ܣ��û�����Ϣ�Ѵ��ڣ�\n");
        return;
    }

    data = (Household *) malloc(sizeof(Household));
    strcpy(data->name, name);

    printf("�������֤��");
    scanf("%s", data->idcard);
    printf("�Ա�");
    scanf("%s", data->gender);
    printf("��ϵ�绰��");
    scanf("%s", data->phone);
    printf("¥�ţ�");
    scanf("%s", data->building);
    printf("��Ԫ�ţ�");
    scanf("%s", data->unit);
    printf("���ţ�");
    scanf("%s", data->room);
    printf("�����ƽ���ף���");
    scanf("%f", &data->area);
    printf("ÿƽ����ҵ�ļ۸�");
    scanf("%f", &data->price);
    printf("Ӧ����ҵ�ѣ�");
    scanf("%f", &data->payment);
    printf("��ע��");
    scanf("%s", data->remark);

    printf("�����뻧����������ס�������ס��֮��");
    scanf("%s", other_name);
    Node *other_node = LinkedList_SearchName(list, other_name);
    if (other_node != NULL) {
        Node *new_node = (Node *) malloc(sizeof(Node));     // �����µ�������
        new_node->data = data;
        new_node->next = other_node->next;
        other_node->next = new_node;
        list.size++;
    } else {
        LinkedList_Insert(&list, data);     // �������ݲ�������
    }

    LinkedList_WriteFile(&list);        // ���������������ļ�
    LinkedList_Destroy(&list);          // �ͷ�����
    printf("�����ɹ���\n");
}

/// ס����Ϣ�޸ĸ�������
int Manage_Modify_Aux(struct LinkedList list, Node **node) {
    char name[32];
    int choice;
    printf("��ѡ���޸�������\n");
    printf(" 1.��������\n");
    printf(" 2.�������֤\n");
    printf(" 3.�Ա�\n");
    printf(" 4.��ϵ�绰\n");
    printf(" 5.¥��\n");
    printf(" 6.��Ԫ��\n");
    printf(" 7.����\n");
    printf(" 8.���\n");
    printf(" 9.ÿƽ����ҵ�ļ۸�\n");
    printf(" 10.Ӧ����ҵ��\n");
    printf(" 11.��ע\n");
    printf(" 0.����\n");

    scanf("%d", &choice);
    printf("�������޸�ֵ��");
    switch (choice) {
        case 1:
            scanf("%s", name);

            if (LinkedList_SearchName(list, name)) {        // ��֤�޸ĺ�Ļ����Ƿ���ڣ���֤��������Ψһ
                printf("�޸�ʧ�ܣ��û��������Ѵ��ڣ�\n");
                return 0;
            }
            strcpy((*node)->data->name, name);
            break;
        case 2:
            scanf("%s", (*node)->data->idcard);
            break;
        case 3:
            scanf("%s", (*node)->data->gender);
            break;
        case 4:
            scanf("%s", (*node)->data->phone);
            break;
        case 5:
            scanf("%s", (*node)->data->building);
            break;
        case 6:
            scanf("%s", (*node)->data->unit);
            break;
        case 7:
            scanf("%s", (*node)->data->room);
            break;
        case 8:
            scanf("%f", (*node)->data->area);
            break;
        case 9:
            scanf("%f", (*node)->data->price);
            break;
        case 10:
            scanf("%f", (*node)->data->payment);
            break;
        case 11:
            scanf("%s", (*node)->data->remark);
            break;
        default:
            return 0;
    }
    return 1;
}

/// �޸�ס����Ϣ
void Manage_Modify() {

    char name[32];
    Node *node;
    struct LinkedList list;

    LinkedList_ReadFile(&list);         // ��ȡ�ļ��е�����������

    printf("��������Ҫ�޸ĵĻ���������");
    scanf("%s", name);

    node = LinkedList_SearchName(list, name);       // ���ݻ���������ѯ������
    if (node == NULL) {
        printf("�޷��޸ģ������ڸû�����Ϣ��\n");
    } else {
        if (Manage_Modify_Aux(list, &node))      // �޸Ľ����Ϣ
        {
            LinkedList_WriteFile(&list);        // ���������������ļ�
            printf("�޸ĳɹ���\n");
        }
    }

    LinkedList_Destroy(&list);      // �ͷ�����
}

/// ɾ��ס����Ϣ
void Manage_Delete() {
    char name[32];
    printf("�������ɾ��������������");
    scanf("%s", name);

    struct LinkedList list;
    LinkedList_ReadFile(&list);         // ��ȡ�ļ��е�����������

    if (LinkedList_Remove(&list, name)) {       // ���ݻ�������ɾ��������
        LinkedList_WriteFile(&list);        // ɾ���ɹ������ļ�
        printf("ɾ���ɹ���\n");
    } else {
        printf("ɾ��ʧ�ܣ������ڸû�����Ϣ��\n");
    }

    LinkedList_Destroy(&list);      // ��������
}

/// ���ȫ��ס����Ϣ
void Manage_Browsing() {
    Household data;
    FILE *fp;
    int size, i;
    fp = fopen(DATA_FILE_NAME, "r");        // ֻ����ʽ���ļ�
    if (fp == NULL) {
        printf("���ʧ�ܣ������ļ������ڣ�\n");
        return;
    }

    fscanf(fp, "%d\n", &size);        // ��ȡ��һ�е�Ԫ�ظ���
    Household_Header();
    for (i = 0; i < size; i++) {
        Household_ReadFile(fp, &data);       // ���ļ��е�һ����Ϣ��ȡ�����ݽṹ��
        Household_Print(data);                     // ��ʾÿһ��ס����Ϣ
    }
    fclose(fp);         // �ر��ļ�ָ��
}

/// ��ѯס����Ϣ
void Manage_Search() {
    int i, size;
    FILE *fp;
    Household data;
    char name[32], building[10], unit[10], room[10];

    printf("��ѡ���ѯ��ʽ��\n");
    printf(" 1.��������\n");
    printf(" 2.¥��+��Ԫ��+����\n");
    scanf("%d", &i);
    if (i != 1 && i != 2) {
        return;
    }

    fp = fopen(DATA_FILE_NAME, "r");        // ֻ����ʽ���ļ�
    if (fp == NULL) {
        printf("���ʧ�ܣ������ļ������ڣ�\n");
        return;
    }

    fscanf(fp, "%d\n", &size);        // ��ȡ��һ�е�Ԫ�ظ���

    if (i == 1) {
        printf("����������");
        scanf("%s", name);
    } else if (i == 2) {
        printf("¥�ţ�");
        scanf("%s", building);
        printf("��Ԫ�ţ�");
        scanf("%s", unit);
        printf("���ţ�");
        scanf("%s", room);   // ����[¥��+��Ԫ��+����]��ѯ����
    }
    Household_Header();
    for (int j = 0; j < size; j++) {
        Household_ReadFile(fp, &data);                  // ���ļ��е�һ����Ϣ��ȡ�����ݽṹ��
        if (i == 1 && strcmp(data.name, name) == 0) {
            Household_Print(data);                          // ��ӡ��ʾÿһ��ס����Ϣ
        }
        if (i == 2 && strcmp(data.building, building) == 0 &&
            strcmp(data.unit, unit) == 0 &&
            strcmp(data.room, room) == 0) {
            Household_Print(data);                     // ��ӡ��ʾÿһ��ס����Ϣ
        }
    }
    fclose(fp);         // �ر��ļ�ָ��
}

/// �Զ�������ҵ��
void Manage_AutoGenPayment() {
    Node *node;
    struct LinkedList list;
    LinkedList_ReadFile(&list);     // ��ȡ����������

    for (node = list.head; node; node = node->next) {
        node->data->payment += node->data->area * node->data->price;        // �Զ�������ҵ��
    }

    LinkedList_WriteFile(&list);        // ���������������ļ�
    LinkedList_Destroy(&list);          // �ͷ�����
    printf("��ҵ�����ɳɹ���\n");
}

/// ����
void Manage_Sort() {
    int i;
    struct Array array;
    Array_ReadFile(&array);            //�ļ�д������
    Array_SortBuilding(&array);        //����
    Household_Header();                //��ͷ
    for (i = 0; i < array.size; i++) {
        Household_Print(array.data[i]);   //������ʾ
    }

}

/// ס���ɷ�
void Manage_Payment() {
    float fee;
    char name[32];
    int pos;
    struct Array array;

    printf("�����뻧��������");
    scanf("%s", name);
    Array_ReadFile(&array);     // ��ȡ�ļ�����������

    pos = Array_SearchName(array, name);        // ���ݻ���������ѯ����

    if (pos < 0) {
        printf("�ɷ�ʧ�ܣ������ڸ�ס����Ϣ��\n");
    } else if (array.data[pos].payment <= 0) {
        printf("��ס���ѽ�����ҵ�ѣ��޷����½ɷѣ�\n");
    } else {
        printf("��ס��δ������ҵ�ѣ�%.2f\n", array.data[pos].payment);
        printf("������ɷѶ");
        scanf("%f", &fee);

        if (fee > 0 && fee <= array.data[pos].payment) {
            array.data[pos].payment -= fee;              // �ɷ�
            Array_WriteFile(&array);                // ���������������ļ�
            printf("�ɷѳɹ���\n");
        } else {
            printf("�ɷ�ʧ�ܣ�������ĽɷѶ��쳣��\n");
        }
    }

}

/// ͳ��δ�ɷ�ס����Ϣ
void Manage_Statistic() {
    struct Array array;
    int i, j, k, count;

    Array_ReadFile(&array);     // ��ȡ�ļ�����������

    Array_SortBuilding(&array);     // ����¥������

    for (i = 0; i < array.size; i++) {
        if (array.data[i].payment <= 0) {
            continue;
        }

        count = 0;      // ����һ�飬��¥���Ƿ����δ�ɷ�ס��
        for (j = 0; j < array.size; j++) {
            if (array.data[j].payment > 0 &&
                strcmp(array.data[j].building, array.data[i].building) == 0) {
                count++;
            }
        }

        if (count == 0) {       // ��¥����ס��ȫ���ɷ�
            continue;
        }

        printf("¥�ţ�%s     δ������ҵ��������%d\n", array.data[i].building, count);

        k = i;
        for (j = i; j < array.size; j++) {
            if (array.data[j].payment > 0 && strcmp(array.data[j].building, array.data[i].building) == 0) {

                printf("    ������%-8s  ��Ԫ�ţ�%-5s  ���ţ�%-5s  δ����ҵ�ѣ�%-8.2f  ��ע��Ϣ��%s\n",
                       array.data[j].name, array.data[j].unit, array.data[j].room, array.data[j].payment,
                       array.data[j].remark);
                k = j;
            }
        }
        putchar('\n');
        i = k;
    }
}