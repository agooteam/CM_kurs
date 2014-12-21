#pragma once
#include <stdio.h>
#include <conio.h>
#include "Math.h"
#include "iostream"
using namespace std;

//��� ������� ����� ��������
typedef double TYPE;
typedef double TYPE2;

//��������� �������
struct Vector{
	TYPE2 *mas;
};

//��������� �������
struct Matrix{
	TYPE *di; //������������ ��������
	TYPE *ggu;//�������� ������������
	TYPE *ggl;//������� ������������
	int *ig;//������ ���������� �����
	int *jg;//������ ��������
	int N;//����������� �������
};
//c�������� ����� � ������������(r,fi)
struct coord {
	TYPE r;
	TYPE fi;
};

//��������� ��������� ��������
struct FELEM {
	//���������� ����� ��������� �������� - ��� ����� � �������
	int num[3]; //������ ������������ ��������� ������� ����� ����������
	int nvkat; //����� ����������
};
struct node{
	coord node_coord;//���������� ����
};
//��������� ������� �������
struct Kraevie {
	int NumUsl; //����� �������� (I, II, III)
	coord Begin;// ���������� ������ �����
	coord End; //���������� ����� �����
	int NumFunc; //����� �������, ��������������� �������� �������
};
