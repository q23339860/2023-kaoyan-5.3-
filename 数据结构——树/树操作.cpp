#include<stdio.h>
#include<stdlib.h>
#include "windows.h"
#include <math.h>
#include "树头文件.h"
int main() {
	BSTree T = NULL;
	//注意T必须先置空，非常重要 
	int i, ran[100];
	//i为计数器，ran数组用于存放从RandomHundred函数随机得来的1－100 
	Status taller;
	//长高与否标志，可以不初始化 
	printf("数据结构课程设计题目：\n");
	printf("1－－利用随机函数产生20个(不大于20且各不相同的)随机整数\n");
	printf("2－－用这些整数来生成一棵二叉树\n");
	printf("产生20个(不大于20且各不相同的)随机整数：\n");
	RandomHundred(ran);
	for (i = 0; i < 20; ++i)printf(FORMAT, ran[i]);
	printf("\n\n");
	for (i = 0; i < 20; ++i)InsertAVL(&T, ran[i], &taller);
	GetCurrentCursorPosition(t1, t2);
	Traverse(T);
	int select;
	do {
		printf("\n**************************************************************\n");
		printf("1、二叉树先序遍历\n");
		printf("2、二叉树中序遍历\n");
		printf("3、二叉树后序遍历\n");
		printf("4、二叉树先序遍历（非递归）\n");
		printf("5、二叉树中序遍历（非递归）\n");
		printf("6、二叉树后序遍历（非递归）\n");
		printf("7、二叉树层次遍历\n");
		printf("**************************************************************\n");
		printf("请输入选择：");
		scanf_s("%d", &select);
		switch (select)
		{
		case 1:printf("二叉树先序遍历\n");
			PreOrder_BSTree(T);
			break;

		case 2:printf("二叉树中序遍历\n");
			InOrder_BSTree(T);
			break;

		case 3:printf("二叉树后序遍历\n");
			PostOrder_BSTree(T);
			break;

		case 4:printf("二叉树先序遍历（非递归）");
			PreOrder1_BSTree(T);
			break;

		case 5:printf("二叉树中序遍历（非递归）");
			InOrder1_BSTree(T);
			break;

		case 6:printf("二叉树后序遍历（非递归）");
			PostOrder1_BSTree(T);
			break;

		case 7:printf("二叉树层次遍历");
			LeveOrder(T);
			break;

		case 0: printf("操作结束\n"); break;

		default:printf("输入选择出错! \n");
		}
	} while (select != 0);
}