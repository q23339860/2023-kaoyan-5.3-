#include<stdio.h>
#include<stdlib.h>
#include "windows.h"
#include <math.h>
#include "��ͷ�ļ�.h"
int main() {
	BSTree T = NULL;
	//ע��T�������ÿգ��ǳ���Ҫ 
	int i, ran[100];
	//iΪ��������ran�������ڴ�Ŵ�RandomHundred�������������1��100 
	Status taller;
	//��������־�����Բ���ʼ�� 
	printf("���ݽṹ�γ������Ŀ��\n");
	printf("1�������������������20��(������20�Ҹ�����ͬ��)�������\n");
	printf("2��������Щ����������һ�ö�����\n");
	printf("����20��(������20�Ҹ�����ͬ��)���������\n");
	RandomHundred(ran);
	for (i = 0; i < 20; ++i)printf(FORMAT, ran[i]);
	printf("\n\n");
	for (i = 0; i < 20; ++i)InsertAVL(&T, ran[i], &taller);
	GetCurrentCursorPosition(t1, t2);
	Traverse(T);
	int select;
	do {
		printf("\n**************************************************************\n");
		printf("1���������������\n");
		printf("2���������������\n");
		printf("3���������������\n");
		printf("4������������������ǵݹ飩\n");
		printf("5������������������ǵݹ飩\n");
		printf("6������������������ǵݹ飩\n");
		printf("7����������α���\n");
		printf("**************************************************************\n");
		printf("������ѡ��");
		scanf_s("%d", &select);
		switch (select)
		{
		case 1:printf("�������������\n");
			PreOrder_BSTree(T);
			break;

		case 2:printf("�������������\n");
			InOrder_BSTree(T);
			break;

		case 3:printf("�������������\n");
			PostOrder_BSTree(T);
			break;

		case 4:printf("����������������ǵݹ飩");
			PreOrder1_BSTree(T);
			break;

		case 5:printf("����������������ǵݹ飩");
			InOrder1_BSTree(T);
			break;

		case 6:printf("����������������ǵݹ飩");
			PostOrder1_BSTree(T);
			break;

		case 7:printf("��������α���");
			LeveOrder(T);
			break;

		case 0: printf("��������\n"); break;

		default:printf("����ѡ�����! \n");
		}
	} while (select != 0);
}