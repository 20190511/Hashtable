#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// h(x) = x mod 13 ��������
// h(x) = (x+i**2) mod 13 2���� ����

//���� �����
int hash_function1(int address, int count)
{
    return (address + count) % 13;
}
//��ó�� �����
int hash_function2(int address, int count)
{
    return (address + (int)pow(count, 2)) % 13;
}
//���� �ּҹ����� �ε��� ã��
int find_OpenAddressing(int method ,int array [],int key)
{
    int count = 0;
    int index = 0;
    while (1)
    {
        //method = 1 : �����ּҹ� , method = 2 : ������ �����
        if (method == 1)
            index = hash_function1(key, count);
        else if (method == 2)
            index = hash_function2(key, count);

        if (array[index] == key)
            break;
        //�ش��ϴ� key���� ã�� ���� ���.
        else if (count > 12)
        {
            index = -1;
            printf("ã�� ���� �����ϴ�. -1�� ��ȯ�մϴ�.");
        }
        count++;
    }
    return index;
}


//����Լ�_������ 4���� ���� ���� �ε����� �������
void print_index(int num_array[] , int find_key [])
{
    for (int i = 0; i < 4; i++)
    {
        printf("key = %d , index = %d \n", find_key[i], num_array[i]);
    }
}
//����Լ� _ ��ü ���̺��� ���¸� �������
void print_hash(int num_array[])
{
    for (int i = 0; i < 13; i++)
    {
        printf("Oper_Addresss_arr[%d] = %d \n",i, num_array[i]);
    }
}

/* Chaining ��� �Լ��� */
//ü�̴� ��� 
typedef struct _Chain {
    int data;
    struct _Chain* link;
}Chain;

//ü�� �ؽ����̺� ���� = ���Ḯ��Ʈ ������� �ؽ��Լ��� �����ϱ� ����.
Chain* table[13];
void input_chain(Chain* root, int key)
{
    int hash_value = key % 13;
    //table�� ��������� �����μ���.
    if (table[hash_value] == NULL)
        table[hash_value] = root;
    else
    {
        root->link = table[hash_value];
        table[hash_value] = root;
    }
}

//link�ּڰ� ��ȯ.
Chain* findData(int address_value)
{
    //1�� ������ �°� �ش� �ε��� ����
    int hash_value = address_value % 13;
    //��� ��尡 ���� ���,
    if (table[hash_value] == NULL)
        return NULL;
    //base Addresss�� ���
    if (table[hash_value]->data == address_value)
    {
        printf("this value is BaseAddress in Hash Table\n");
        printf("key = %d , index = %d\n\n", address_value , hash_value);
        return table[hash_value];
    }
    //���Ḯ��Ʈ�� ����Ǿ� �ִ� ���
    else
    {
        Chain* new_node = table[hash_value];
        while (new_node->link)
        {
            if (new_node->link->data == address_value)
            {
                printf("this value is Collision value , so its structure is linkedlist\n");
                printf("key = %d , base index = %d , linked previous data = %d \n\n", address_value, hash_value, new_node->data);
                return new_node->link;
            }
            new_node->link;
        }
    }
    return NULL;
}
//chain�����Լ�
void execute_chain(int array[], int input_data, int count)
{
    count = 0;
    Chain* node = (Chain*)malloc(sizeof(Chain));
    node->data = input_data;
    node->link = NULL;
    input_chain(node, node->data);
    array[hash_function1(input_data, count)] = node->data;
}

//����� ��ü���� ���¸� ������ִ� �Լ�
void printChainNode()
{
    for (int i = 0; i < 13; i++)
    {
        printf("chain_array [%d] =", i);
        if (table[i] != NULL)
        {
            Chain* print_node = table[i];
            while (print_node->link)
            {
                printf(" %d ", print_node->data);
                print_node = print_node->link;
            }
            printf(" %d", print_node->data);
        }
        else
            printf(" 0 (NULL value)");
        printf("\n");
    }
    printf(" ****** End ******\n");
    printf("\n");
}


//method = �ؽ� ��� , array = �迭����,  input_data = ���� ������
void input_hash(int method, int array[], int input_data)
{

    int address = 0;
    int count = 0;
    //Open Addressing : ���� �ּ� ��� (method = 1 : �����ּҹ� , method 2 : ������ �����)
    if (method == 1 || method == 2)
    {
        while (1)
        {
            if (method == 1)
                address = hash_function1(input_data, count);
            else
                address = hash_function2(input_data, count);
            if (array[address] == 0)
            {
                array[address] = input_data;
                break;
            }
            else
                count++;
        }
    }
    //Chaining : ü�̴� ���
    else
    {
        execute_chain(array, input_data, count);
    }
}

//03�� ������ �ش���. : ���� �ּҹ��� ������ 4���� key ���� ���� index�� �������
void question1(int num1_array[], int input_data[], int find_key [])
{
    printf(" ****** Question1 Find : Linear Probing ******\n");
    int index_bag1[4] = {0,};
    //���� ��������� ���� �ؽ� ���̺� ����
    for (int i = 0; i < 8; i++)
    {
        input_hash(1, num1_array, input_data[i]);
        if (i >= 4)
        {
            printf("Linear Probing : input %d , and print table\n", input_data[i]);
            print_hash(num1_array);
            printf("\n");
        }
    }
    //���� ��������� �ش��ϴ� key���� ã��
    for (int k = 0; k < 4; k++)
    {
        index_bag1[k] = find_OpenAddressing(1, num1_array, find_key[k]);
    }
    print_index(index_bag1,find_key);
    printf(" ****** End ******\n");
    printf("\n");
}

//04�� ������ �ش���. : ������ �ּҹ��� ������ 4���� key ���� ���� index�� �������
void question2(int num2_array[] , int input_data[] , int find_key [])
{
    printf(" ****** Question2 Find : Quadratic Probing ******\n");
    int index_bag2[4] = { 0, };
    //������ ��������� ���� �ؽ����̺� ����
    for (int i = 0; i < 8; i++)
    {
        input_hash(2, num2_array, input_data[i]);
        if (i >= 4)
        {
            printf("Quadratic Probing : input %d , and print table\n", input_data[i]);
            print_hash(num2_array);
            printf("\n");
        }
    }
    //������ ��������� �ش��ϴ� key���� ã��
    for (int k = 0; k < 4; k++)
    {
        index_bag2[k] = find_OpenAddressing(2, num2_array, find_key[k]);
    }
    print_index(index_bag2,find_key);
    printf(" ****** End ******\n");
    printf("\n");
}

//05�� ������ �ش���. : ü�̴� �ּҹ��� ������ 4���� key ���� ���� index�� �������
void question3(int num3_array[] , int input_data[], int find_key [])
{
    printf(" ****** Question3 Find : Chaining ******\n");
    int index_bag3[4] = {0, };
    //ü�̴� ��������� ���� �ؽ����̺� ����
    for (int i = 0; i < 8; i++)
    {
        input_hash(3, num3_array, input_data[i]);
        if (i >= 4)
        {
            printf("Chaining : input %d , and print table\n", input_data[i]);
            printChainNode();
            printf("\n");
        }
    }
    //ü�̴� ��������� �ش��ϴ� key���� ã��
    for (int k = 0; k < 4; k++)
    {
        //return �ּ� ���� �����ϳ�, ������ ������ ���⿡ 
        findData(find_key[k]);
    }
    printf(" ****** End ******\n");
    printf("\n");
}




//�ؽ��Լ��� ����� �ۼ��Ǿ����� ����ϴ� �Լ���.
// 1. ���� ��������� ���� �ؽ����̺�
void question1_print(int num1_array[])
{
    printf(" ****** Print : Linear Probing ******\n");
    print_hash(num1_array);
    printf(" ****** End ******\n");
    printf("\n");
}

// 2. ������ ��������� ���� �ؽ� ���̺�
void question2_print(int num2_array[])
{
    printf(" ****** Print : Quadratic Probing ******\n");
    print_hash(num2_array);
    printf(" ****** End ******\n");
}

// 3. ü�̴� ������� ���� �ؽ� ���̺�
void question3_print(int num3_array[])
{
    printf(" ****** Print : Chaining ******\n");
    printChainNode();
}


int main(void)
{  
    //�ؽ����̺��� ������ �ʱ� ����.
    int input_data[8] = { 10,20,30,40,33,46,50,60 };
    //���� �ؽ����̺� num1 : �����ּҹ� ���̺�, num2 : ���������� ���̺� , num3 : ü�̴� ����� ���̺�
    int num1_array[13] = { 0, };
    int num2_array[13] = { 0, };
    int num3_array[13] = { 0, };




    //������ 4���� ���� ã�� index�� �����.
    int find_key[4] = { 33,46,50,60 };
    printf("\n +++++++++ find index of key = {33,46,50,60} +++++++++\n");
    printf("\n --------- find index : Open Addressing ---------\n");
    question1(num1_array, input_data, find_key);
    question2(num2_array, input_data, find_key);
    printf(" --------- find index : Chaining ---------\n");
    question3(num3_array, input_data , find_key);


    printf("-------------------------------------------------\n");
    printf(" +++++++++ print Whole Array +++++++++ \n\n");


    //�ش��ϴ� �ؽ����̺���� �������.
    printf(" --------- print hash : Open Addressing ---------\n");
    question1_print(num1_array);
    question2_print(num2_array);
    printf(" --------- print hash : Chaining ---------\n");
    question3_print(num3_array);



    return 0;
}