#pragma once

#include<stdio.h>
#include<stdlib.h>
#include "windows.h"
#include <math.h>
#include<time.h>
#include <random>

typedef int ElemType;
typedef int Status;
typedef double Double;
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define STOCK_MAX_SIZE 500
#define	LISTINCREMENT 10
#define SQQUEUE_MAX_SIZE 50
#define FORMAT "%d " 
//输出格式与ElemType对应
int t1, t2;
void RandomHundred(int ran[20])
//产生100个不大于100且各不相同的整数，存放在ran[100]中
{
	int i, temp, ransubscript;
	//temp用于交换，ransubscript为随机下标 
	for (i = 1; i < 21; ++i)ran[i - 1] = i;
	//先把1－100按顺序放入数组中 
	for (i = 20; i > 0; --i)
	{
		ransubscript = rand() % i;
		//产生随机下标 
		temp = ran[i - 1];
		ran[i - 1] = ran[ransubscript];
		ran[ransubscript] = temp;
		//交换ran[i-1]与ran[ransubscript]
	}
}
typedef struct BSTNode
{
	ElemType data;
	int bf;
	/*结点的平衡因子*/
	struct BSTNode* lchild, * rchild;
	/* 左、右孩子指针 */
}BSTNode, * BSTree;
#define EQ(a,b)((a)==(b))
#define LT(a,b)((a)<(b))
#define LH +1 /* 左高 */
#define EH 0 /* 等高 */
#define RH -1 /* 右高 */
void R_Rotate(BSTree* p)
{/* 对以*p为根的二叉排序树作右旋处理，处理之后p指向新的树根结点，即旋转 */
 /* 处理之前的左子树的根结点。算法9.9 */
	BSTree lc;
	lc = (*p)->lchild;
	/* lc指向p的左子树根结点 */
	(*p)->lchild = lc->rchild;
	/* lc的右子树挂接为p的左子树 */
	lc->rchild = *p;
	*p = lc;
	/* p指向新的根结点 */
}

void L_Rotate(BSTree* p)
{/* 对以*p为根的二叉排序树作左旋处理，处理之后p指向新的树根结点，即旋转 */
 /* 处理之前的右子树的根结点。算法9.10 */
	BSTree rc;
	rc = (*p)->rchild;
	/* rc指向p的右子树根结点 */
	(*p)->rchild = rc->lchild;
	/* rc的左子树挂接为p的右子树 */
	rc->lchild = *p;
	*p = rc;
	/* p指向新的根结点 */
}


void LeftBalance(BSTree* T)
{/* 对以指针T所指结点为根的二叉树作左平衡旋转处理，本算法结束时， */
 /* 指针T指向新的根结点。算法9.12 */
	BSTree lc, rd;
	lc = (*T)->lchild;
	/* lc指向*T的左子树根结点 */
	switch (lc->bf)
	{ /* 检查*T的左子树的平衡度，并作相应平衡处理 */
	case LH:
		/* 新结点插入在*T的左孩子的左子树上，要作单右旋处理 */
		(*T)->bf = lc->bf = EH;
		R_Rotate(T);
		break;
	case RH:
		/* 新结点插入在*T的左孩子的右子树上，要作双旋处理 */
		rd = lc->rchild;
		/* rd指向*T的左孩子的右子树根 */
		switch (rd->bf)
		{ /* 修改*T及其左孩子的平衡因子 */
		case LH:
			(*T)->bf = RH;
			lc->bf = EH;
			break;
		case EH:
			(*T)->bf = lc->bf = EH;
			break;
		case RH:
			(*T)->bf = EH;
			lc->bf = LH;
			break;
		}
		rd->bf = EH;
		L_Rotate(&(*T)->lchild);
		/* 对*T的左子树作左旋平衡处理 */
		R_Rotate(T);
		/* 对*T作右旋平衡处理 */
	}
}

void RightBalance(BSTree* T)
{/* 对以指针T所指结点为根的二叉树作右平衡旋转处理，本算法结束时， */
/* 指针T指向新的根结点 */
	BSTree rc, rd;
	rc = (*T)->rchild;
	/* rc指向*T的右子树根结点 */
	switch (rc->bf)
	{/* 检查*T的右子树的平衡度，并作相应平衡处理 */
	case RH:
		/* 新结点插入在*T的右孩子的右子树上，要作单左旋处理 */
		(*T)->bf = rc->bf = EH;
		L_Rotate(T);
		break;
	case LH:
		/* 新结点插入在*T的右孩子的左子树上，要作双旋处理 */
		rd = rc->lchild;
		/* rd指向*T的右孩子的左子树根 */
		switch (rd->bf)
		{/* 修改*T及其右孩子的平衡因子 */
		case RH:
			(*T)->bf = LH;
			rc->bf = EH;
			break;
		case EH:
			(*T)->bf = rc->bf = EH;
			break;
		case LH:
			(*T)->bf = EH;
			rc->bf = RH;
			break;
		}
		rd->bf = EH;
		R_Rotate(&(*T)->rchild);
		/* 对*T的右子树作右旋平衡处理 */
		L_Rotate(T);
		/* 对*T作左旋平衡处理 */
	}
}

Status InsertAVL(BSTree* T, ElemType e, Status* taller)
{/* 若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个 */
 /* 数据元素为e的新结点，并返回1，否则返回0。若因插入而使二叉排序树 */
 /* 失去平衡，则作平衡旋转处理，布尔变量taller反映T长高与否。算法9.11 */
	if (!*T)
	{/* 插入新结点，树“长高”，置taller为TRUE */
		*T = (BSTree)malloc(sizeof(BSTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
		*taller = TRUE;
	}
	else
	{
		if (EQ(e, (*T)->data))
		{/* 树中已存在和e有相同关键字的结点则不再插入 */
			*taller = FALSE;
			return FALSE;
		}
		if (LT(e, (*T)->data))
		{/* 应继续在*T的左子树中进行搜索 */
		/* 未插入 */
			if (!InsertAVL(&(*T)->lchild, e, taller))return FALSE;
			/* 已插入到*T的左子树中且左子树“长高” */
			/* 检查*T的平衡度 */
			if (*taller)switch ((*T)->bf)
			{
			case LH:
				/* 原本左子树比右子树高，需要作左平衡处理 */
				LeftBalance(T);
				*taller = FALSE;
				break;
			case EH:
				/* 原本左、右子树等高，现因左子树增高而使树增高 */
				(*T)->bf = LH;
				*taller = TRUE;
				break;
			case RH:
				(*T)->bf = EH;
				/* 原本右子树比左子树高，现左、右子树等高 */
				*taller = FALSE;
			}
		}
		else
		{/* 应继续在*T的右子树中进行搜索 */
		/* 未插入 */
			if (!InsertAVL(&(*T)->rchild, e, taller))return FALSE;
			/* 已插入到T的右子树且右子树“长高” */
			/* 检查T的平衡度 */
			if (*taller)switch ((*T)->bf)
			{
			case LH:
				(*T)->bf = EH;
				/* 原本左子树比右子树高，现左、右子树等高 */
				*taller = FALSE;
				break;
			case EH:
				/* 原本左、右子树等高，现因右子树增高而使树增高 */
				(*T)->bf = RH;
				*taller = TRUE;
				break;
			case RH:
				/* 原本右子树比左子树高，需要作右平衡处理 */
				RightBalance(T);
				*taller = FALSE;
			}
		}
	}
	return TRUE;
}

typedef BSTree SElemType;//这个很重要，定义栈的元素类型为二叉树结点指针BSTree
//栈的顺序存储表示
//SElemType为栈元素，由用户在主函数中定义 
#define STACK_INIT_SIZE 100 /* 存储空间初始分配量 */
#define STACKINCREMENT 10 /* 存储空间分配增量 */
typedef struct SqStack
{
	SElemType* base; /* 在栈构造之前和销毁之后，base的值为NULL */
	SElemType* top; /* 栈顶指针 */
	int stacksize; /* 当前已分配的存储空间，以元素为单位 */
}SqStack; /* 顺序栈 */
//顺序栈（存储结构由SqStack.h定义）的基本操作
Status InitStack(SqStack* S)
{ /* 构造一个空栈S */
	(*S).base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!(*S).base)
		exit(OVERFLOW); /* 存储分配失败 */
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return OK;
}

Status StackEmpty(SqStack S)
{ /* 若栈S为空栈，则返回TRUE，否则返回FALSE */
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;
}

Status Push(SqStack* S, SElemType e)
{ /* 插入元素e为新的栈顶元素 */
	if ((*S).top - (*S).base >= (*S).stacksize) /* 栈满，追加存储空间 */
	{
		(*S).base = (SElemType*)realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!(*S).base)
			exit(OVERFLOW); /* 存储分配失败 */
		(*S).top = (*S).base + (*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*((*S).top)++ = e;
	return OK;
}

Status Pop(SqStack* S, SElemType* e)
{ /* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
	if ((*S).top == (*S).base)
		return ERROR;
	*e = *--(*S).top;
	return OK;
}

Status GetTop(SqStack S, SElemType *e) {
	if (S.top == S.base) {
		return ERROR;
	}
	*e = *(S.top-1);
	return OK;
}
//void PreOrderTraverse(BSTree T, Status(*Visit)(ElemType e))
////非递归先序遍历二叉树 
//{
//	BSTree p, e;
//	SqStack S;
//	InitStack(&S);
//	p = T;
//	while (p || !StackEmpty(S))
//	{//遍历左子树
//		while (p)
//		{
//			(*Visit)(p->data);
//			Push(&S, p);
//			p = p->lchild;
//		}
//		//通过下一次循环中的内嵌while实现右子树遍历
//		if (!StackEmpty(S))
//		{
//			Pop(&S, &e);
//			p = e->rchild;
//		}
//	}
//}
//
//
//void InOrderTraverse(BSTree T, Status(*Visit)(ElemType e))
//{/* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
///* 操作结果: 中序递归遍历T,对每个结点调用函数Visit一次且仅一次 */
//	if (T)
//	{
//		InOrderTraverse(T->lchild, (*Visit));
//		/* 先中序遍历左子树 */
//		(*Visit)(T->data);
//		/* 再访问根结点 */
//		InOrderTraverse(T->rchild, (*Visit));
//		/* 最后中序遍历右子树 */
//	}
//}
//
//void PostOrderTraverse(BSTree T, Status(*Visit)(ElemType e))
//{/* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
// /* 操作结果: 后序递归遍历T,对每个结点调用函数Visit一次且仅一次 */
// /* T不空 */
//	if (T)
//	{
//		PostOrderTraverse(T->lchild, (*Visit));
//		/* 先后序遍历左子树 */
//		PostOrderTraverse(T->rchild, (*Visit));
//		/* 再后序遍历右子树 */
//		(*Visit)(T->data);
//		/* 最后访问根结点 */
//	}
//}
void GetCurrentCursorPosition(int& x, int& y)
{
	HANDLE   hStdout;
	CONSOLE_SCREEN_BUFFER_INFO   pBuffer;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdout, &pBuffer);
	x = pBuffer.dwCursorPosition.X;
	y = pBuffer.dwCursorPosition.Y;
}
//改变光标位置
void gotoxy(int x, int y)
{
	// 更新光标位置
	COORD pos;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOutput, pos);
}
int BiTreeDepth(BSTree T) {
	if (T == NULL) return 0;

	int depthLeft, depthRight;
	depthLeft = BiTreeDepth(T->lchild);
	depthRight = BiTreeDepth(T->rchild);

	return 1 + (depthLeft > depthRight ? depthLeft : depthRight);
}
Status BreakBiTree(BSTree& T, BSTree& L, BSTree& R) {
	if (T == NULL) return ERROR;
	L = T->lchild;
	R = T->rchild;

	return OK;
}
/*
* 递归打印打印出树形
* T		正在打印的树
* depth	目前在打印树的第几层
* right	该子树是否为右子树
* tap	目前子树需要的相对偏移数量
*/
Status Traverse_R(BSTree T, int depth, int right, int tap) {
	if (T == NULL) return OK;

	// 获取一次树的初始高度，用于计算相对偏移数量
	static int treeDepth = BiTreeDepth(T);
	// 记录当前光标位置，用于在递归中记录当前递归时树的位置
	int x, y;
	// 拆分树，将树的左右子树拆分开来
	BSTree L, R;
	BreakBiTree(T, L, R);

	// 计算父树的偏移量
	int tap1 = tap * pow(2, treeDepth - depth);
	// 计算子树的偏移量
	int tap2 = right * (pow(2, treeDepth - depth));
	// 计算半偏移量
	int tap3 = pow(2, treeDepth - depth - 1);

	// 获取根的坐标
	// x 计算方法为：父偏移量 + 子偏移量 + 半偏移量 - 1
	// y 计算方法为：目前打印的层数 * 2
	x = tap1 + tap2 + tap3 - 1;
	y = depth * 2 + t2;

	// 打印根的位置
	gotoxy(x * 2, y);
	printf("%d", T->data);

	// 在打印子树时，当前层数+1
	depth++;
	// 计算子树的父偏移量
	tap = tap * 2 + (right == 1 ? 2 : 0);
	if (L == NULL && R == NULL) return OK;
	else if (R == NULL) {
		// 打印左子树的位置
		gotoxy(x * 2 - tap3, y + 1);
		printf("┏");
		for (int i = 0; i < tap3 - 1; i++) printf("━");
		printf("┛");
		Traverse_R(L, depth, 0, tap);
	}
	else if (L == NULL) {
		// 打印右子树的位置
		gotoxy(x * 2, y + 1);
		printf("┗");
		for (int i = 0; i < tap3 - 1; i++) printf("━");
		printf("┓");
		Traverse_R(R, depth, 1, tap);
	}
	else {
		// 打印左右子树的位置
		gotoxy(x * 2 - tap3, y + 1);
		printf("┏");
		for (int i = 0; i < tap3 - 1; i++) printf("━");
		printf("┻");
		for (int i = 0; i < tap3 - 1; i++) printf("━");
		printf("┓");
		Traverse_R(L, depth, 0, tap);
		Traverse_R(R, depth, 1, tap);
	}
}

// 打印树形接口
Status Traverse(BSTree T) {
	Traverse_R(T, 0, 0, 0);
	return OK;
}

Status Visit_BSTree(BSTree T) {
	printf(" %d ", T->data);
	return OK;
}
void PreOrder_BSTree(BSTree T){
	if (T != NULL) {
		Visit_BSTree(T);
		PreOrder_BSTree(T->lchild);
		PreOrder_BSTree(T->rchild);
	}
}

void InOrder_BSTree(BSTree T) {
	if (T != NULL) {
		InOrder_BSTree(T->lchild);
		Visit_BSTree(T);
		InOrder_BSTree(T->rchild);
	}
}

void PostOrder_BSTree(BSTree T) {
	if (T != NULL) {
		PostOrder_BSTree(T->lchild);
		PostOrder_BSTree(T->rchild);
		Visit_BSTree(T);
	}
}

void PreOrder1_BSTree(BSTree T) {
	SqStack s;
	InitStack(&s);
	BSTree q = T;
	while (q || !StackEmpty(s)) {
		if (q != NULL) {
			Visit_BSTree(q);
			Push(&s, q);
			q = q->lchild;
		}
		else {
			Pop(&s, &q);
			q = q->rchild;
		}
	}
}

void InOrder1_BSTree(BSTree T) {
	SqStack s;
	InitStack(&s);
	BSTree q = T;
	while (q || !StackEmpty(s)) {
		if (q != NULL) {
			Push(&s, q);
			q = q->lchild;
		}
		else {
			Pop(&s, &q);
			Visit_BSTree(q);
			q = q->rchild;
		}
	}
}

void PostOrder1_BSTree(BSTree T) {
	SqStack s;
	InitStack(&s);
	BSTree q = T, r = NULL;
	while (q || !StackEmpty(s)) {
		if (q) {
			Push(&s, q);
			q = q->lchild;
		}
		else {
			GetTop(s, &q);
			if (q->rchild && q->rchild != r) {
				q = q->rchild;
			}
			else {
				Pop(&s, &q);
				Visit_BSTree(q);
				r = q;
				q = NULL;
			}
		}
	}
}
typedef struct SqQueue {
	SElemType data[SQQUEUE_MAX_SIZE];
	int front, rear;
};
Status InitSqQueue(SqQueue &sq) {
	sq.front = 0;
	sq.rear = 0;
	return OK;
}
bool IsEmpty_sq(SqQueue sq) {
	if (sq.front == sq.rear) {
		return TRUE;
	}
	return FALSE;
}
Status Enqueue(SqQueue &sq,SElemType e) {
	if ((sq.rear + 1) % SQQUEUE_MAX_SIZE == sq.front) {
		printf("队列已满\n");
		return ERROR;
	}
	sq.data[sq.rear] = e;
	sq.rear = (sq.rear + 1) % SQQUEUE_MAX_SIZE;
	return OK;
}
Status Dequeue(SqQueue& sq, SElemType& e) {
	if (IsEmpty_sq(sq)) {
		return ERROR;
	}
	e = sq.data[sq.front];
	sq.front = (sq.front + 1) % SQQUEUE_MAX_SIZE;
	return OK;
}

Status LeveOrder(BSTree T) {
	BSTree p = T;
	SqQueue sq;
	InitSqQueue(sq);
	Enqueue(sq, p);
	while (!IsEmpty_sq(sq)) {
		Dequeue(sq, p);
		Visit_BSTree(p);
		if (p->lchild != NULL) {
			Enqueue(sq, p->lchild);
		}
		if (p->rchild != NULL) {
			Enqueue(sq, p->rchild);
		}
	}
	return OK;
}