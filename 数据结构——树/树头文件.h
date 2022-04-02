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
//�����ʽ��ElemType��Ӧ
int t1, t2;
void RandomHundred(int ran[20])
//����100��������100�Ҹ�����ͬ�������������ran[100]��
{
	int i, temp, ransubscript;
	//temp���ڽ�����ransubscriptΪ����±� 
	for (i = 1; i < 21; ++i)ran[i - 1] = i;
	//�Ȱ�1��100��˳����������� 
	for (i = 20; i > 0; --i)
	{
		ransubscript = rand() % i;
		//��������±� 
		temp = ran[i - 1];
		ran[i - 1] = ran[ransubscript];
		ran[ransubscript] = temp;
		//����ran[i-1]��ran[ransubscript]
	}
}
typedef struct BSTNode
{
	ElemType data;
	int bf;
	/*����ƽ������*/
	struct BSTNode* lchild, * rchild;
	/* ���Һ���ָ�� */
}BSTNode, * BSTree;
#define EQ(a,b)((a)==(b))
#define LT(a,b)((a)<(b))
#define LH +1 /* ��� */
#define EH 0 /* �ȸ� */
#define RH -1 /* �Ҹ� */
void R_Rotate(BSTree* p)
{/* ����*pΪ���Ķ�����������������������֮��pָ���µ�������㣬����ת */
 /* ����֮ǰ���������ĸ���㡣�㷨9.9 */
	BSTree lc;
	lc = (*p)->lchild;
	/* lcָ��p������������� */
	(*p)->lchild = lc->rchild;
	/* lc���������ҽ�Ϊp�������� */
	lc->rchild = *p;
	*p = lc;
	/* pָ���µĸ���� */
}

void L_Rotate(BSTree* p)
{/* ����*pΪ���Ķ�����������������������֮��pָ���µ�������㣬����ת */
 /* ����֮ǰ���������ĸ���㡣�㷨9.10 */
	BSTree rc;
	rc = (*p)->rchild;
	/* rcָ��p������������� */
	(*p)->rchild = rc->lchild;
	/* rc���������ҽ�Ϊp�������� */
	rc->lchild = *p;
	*p = rc;
	/* pָ���µĸ���� */
}


void LeftBalance(BSTree* T)
{/* ����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת�������㷨����ʱ�� */
 /* ָ��Tָ���µĸ���㡣�㷨9.12 */
	BSTree lc, rd;
	lc = (*T)->lchild;
	/* lcָ��*T������������� */
	switch (lc->bf)
	{ /* ���*T����������ƽ��ȣ�������Ӧƽ�⴦�� */
	case LH:
		/* �½�������*T�����ӵ��������ϣ�Ҫ������������ */
		(*T)->bf = lc->bf = EH;
		R_Rotate(T);
		break;
	case RH:
		/* �½�������*T�����ӵ��������ϣ�Ҫ��˫������ */
		rd = lc->rchild;
		/* rdָ��*T�����ӵ��������� */
		switch (rd->bf)
		{ /* �޸�*T�������ӵ�ƽ������ */
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
		/* ��*T��������������ƽ�⴦�� */
		R_Rotate(T);
		/* ��*T������ƽ�⴦�� */
	}
}

void RightBalance(BSTree* T)
{/* ����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת�������㷨����ʱ�� */
/* ָ��Tָ���µĸ���� */
	BSTree rc, rd;
	rc = (*T)->rchild;
	/* rcָ��*T������������� */
	switch (rc->bf)
	{/* ���*T����������ƽ��ȣ�������Ӧƽ�⴦�� */
	case RH:
		/* �½�������*T���Һ��ӵ��������ϣ�Ҫ������������ */
		(*T)->bf = rc->bf = EH;
		L_Rotate(T);
		break;
	case LH:
		/* �½�������*T���Һ��ӵ��������ϣ�Ҫ��˫������ */
		rd = rc->lchild;
		/* rdָ��*T���Һ��ӵ��������� */
		switch (rd->bf)
		{/* �޸�*T�����Һ��ӵ�ƽ������ */
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
		/* ��*T��������������ƽ�⴦�� */
		L_Rotate(T);
		/* ��*T������ƽ�⴦�� */
	}
}

Status InsertAVL(BSTree* T, ElemType e, Status* taller)
{/* ����ƽ��Ķ���������T�в����ں�e����ͬ�ؼ��ֵĽ�㣬�����һ�� */
 /* ����Ԫ��Ϊe���½�㣬������1�����򷵻�0����������ʹ���������� */
 /* ʧȥƽ�⣬����ƽ����ת������������taller��ӳT��������㷨9.11 */
	if (!*T)
	{/* �����½�㣬�������ߡ�����tallerΪTRUE */
		*T = (BSTree)malloc(sizeof(BSTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
		*taller = TRUE;
	}
	else
	{
		if (EQ(e, (*T)->data))
		{/* �����Ѵ��ں�e����ͬ�ؼ��ֵĽ�����ٲ��� */
			*taller = FALSE;
			return FALSE;
		}
		if (LT(e, (*T)->data))
		{/* Ӧ������*T���������н������� */
		/* δ���� */
			if (!InsertAVL(&(*T)->lchild, e, taller))return FALSE;
			/* �Ѳ��뵽*T�����������������������ߡ� */
			/* ���*T��ƽ��� */
			if (*taller)switch ((*T)->bf)
			{
			case LH:
				/* ԭ�����������������ߣ���Ҫ����ƽ�⴦�� */
				LeftBalance(T);
				*taller = FALSE;
				break;
			case EH:
				/* ԭ�����������ȸߣ��������������߶�ʹ������ */
				(*T)->bf = LH;
				*taller = TRUE;
				break;
			case RH:
				(*T)->bf = EH;
				/* ԭ�����������������ߣ������������ȸ� */
				*taller = FALSE;
			}
		}
		else
		{/* Ӧ������*T���������н������� */
		/* δ���� */
			if (!InsertAVL(&(*T)->rchild, e, taller))return FALSE;
			/* �Ѳ��뵽T���������������������ߡ� */
			/* ���T��ƽ��� */
			if (*taller)switch ((*T)->bf)
			{
			case LH:
				(*T)->bf = EH;
				/* ԭ�����������������ߣ������������ȸ� */
				*taller = FALSE;
				break;
			case EH:
				/* ԭ�����������ȸߣ��������������߶�ʹ������ */
				(*T)->bf = RH;
				*taller = TRUE;
				break;
			case RH:
				/* ԭ�����������������ߣ���Ҫ����ƽ�⴦�� */
				RightBalance(T);
				*taller = FALSE;
			}
		}
	}
	return TRUE;
}

typedef BSTree SElemType;//�������Ҫ������ջ��Ԫ������Ϊ���������ָ��BSTree
//ջ��˳��洢��ʾ
//SElemTypeΪջԪ�أ����û����������ж��� 
#define STACK_INIT_SIZE 100 /* �洢�ռ��ʼ������ */
#define STACKINCREMENT 10 /* �洢�ռ�������� */
typedef struct SqStack
{
	SElemType* base; /* ��ջ����֮ǰ������֮��base��ֵΪNULL */
	SElemType* top; /* ջ��ָ�� */
	int stacksize; /* ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ */
}SqStack; /* ˳��ջ */
//˳��ջ���洢�ṹ��SqStack.h���壩�Ļ�������
Status InitStack(SqStack* S)
{ /* ����һ����ջS */
	(*S).base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!(*S).base)
		exit(OVERFLOW); /* �洢����ʧ�� */
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return OK;
}

Status StackEmpty(SqStack S)
{ /* ��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE */
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;
}

Status Push(SqStack* S, SElemType e)
{ /* ����Ԫ��eΪ�µ�ջ��Ԫ�� */
	if ((*S).top - (*S).base >= (*S).stacksize) /* ջ����׷�Ӵ洢�ռ� */
	{
		(*S).base = (SElemType*)realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!(*S).base)
			exit(OVERFLOW); /* �洢����ʧ�� */
		(*S).top = (*S).base + (*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*((*S).top)++ = e;
	return OK;
}

Status Pop(SqStack* S, SElemType* e)
{ /* ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR */
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
////�ǵݹ�������������� 
//{
//	BSTree p, e;
//	SqStack S;
//	InitStack(&S);
//	p = T;
//	while (p || !StackEmpty(S))
//	{//����������
//		while (p)
//		{
//			(*Visit)(p->data);
//			Push(&S, p);
//			p = p->lchild;
//		}
//		//ͨ����һ��ѭ���е���Ƕwhileʵ������������
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
//{/* ��ʼ����: ������T����,Visit�ǶԽ�������Ӧ�ú��� */
///* �������: ����ݹ����T,��ÿ�������ú���Visitһ���ҽ�һ�� */
//	if (T)
//	{
//		InOrderTraverse(T->lchild, (*Visit));
//		/* ��������������� */
//		(*Visit)(T->data);
//		/* �ٷ��ʸ���� */
//		InOrderTraverse(T->rchild, (*Visit));
//		/* ���������������� */
//	}
//}
//
//void PostOrderTraverse(BSTree T, Status(*Visit)(ElemType e))
//{/* ��ʼ����: ������T����,Visit�ǶԽ�������Ӧ�ú��� */
// /* �������: ����ݹ����T,��ÿ�������ú���Visitһ���ҽ�һ�� */
// /* T���� */
//	if (T)
//	{
//		PostOrderTraverse(T->lchild, (*Visit));
//		/* �Ⱥ������������ */
//		PostOrderTraverse(T->rchild, (*Visit));
//		/* �ٺ������������ */
//		(*Visit)(T->data);
//		/* �����ʸ���� */
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
//�ı���λ��
void gotoxy(int x, int y)
{
	// ���¹��λ��
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
* �ݹ��ӡ��ӡ������
* T		���ڴ�ӡ����
* depth	Ŀǰ�ڴ�ӡ���ĵڼ���
* right	�������Ƿ�Ϊ������
* tap	Ŀǰ������Ҫ�����ƫ������
*/
Status Traverse_R(BSTree T, int depth, int right, int tap) {
	if (T == NULL) return OK;

	// ��ȡһ�����ĳ�ʼ�߶ȣ����ڼ������ƫ������
	static int treeDepth = BiTreeDepth(T);
	// ��¼��ǰ���λ�ã������ڵݹ��м�¼��ǰ�ݹ�ʱ����λ��
	int x, y;
	// �����������������������ֿ���
	BSTree L, R;
	BreakBiTree(T, L, R);

	// ���㸸����ƫ����
	int tap1 = tap * pow(2, treeDepth - depth);
	// ����������ƫ����
	int tap2 = right * (pow(2, treeDepth - depth));
	// �����ƫ����
	int tap3 = pow(2, treeDepth - depth - 1);

	// ��ȡ��������
	// x ���㷽��Ϊ����ƫ���� + ��ƫ���� + ��ƫ���� - 1
	// y ���㷽��Ϊ��Ŀǰ��ӡ�Ĳ��� * 2
	x = tap1 + tap2 + tap3 - 1;
	y = depth * 2 + t2;

	// ��ӡ����λ��
	gotoxy(x * 2, y);
	printf("%d", T->data);

	// �ڴ�ӡ����ʱ����ǰ����+1
	depth++;
	// ���������ĸ�ƫ����
	tap = tap * 2 + (right == 1 ? 2 : 0);
	if (L == NULL && R == NULL) return OK;
	else if (R == NULL) {
		// ��ӡ��������λ��
		gotoxy(x * 2 - tap3, y + 1);
		printf("��");
		for (int i = 0; i < tap3 - 1; i++) printf("��");
		printf("��");
		Traverse_R(L, depth, 0, tap);
	}
	else if (L == NULL) {
		// ��ӡ��������λ��
		gotoxy(x * 2, y + 1);
		printf("��");
		for (int i = 0; i < tap3 - 1; i++) printf("��");
		printf("��");
		Traverse_R(R, depth, 1, tap);
	}
	else {
		// ��ӡ����������λ��
		gotoxy(x * 2 - tap3, y + 1);
		printf("��");
		for (int i = 0; i < tap3 - 1; i++) printf("��");
		printf("��");
		for (int i = 0; i < tap3 - 1; i++) printf("��");
		printf("��");
		Traverse_R(L, depth, 0, tap);
		Traverse_R(R, depth, 1, tap);
	}
}

// ��ӡ���νӿ�
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
		printf("��������\n");
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