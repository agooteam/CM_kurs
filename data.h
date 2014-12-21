#pragma once
#include <stdio.h>
#include <conio.h>
#include "Math.h"
#include "iostream"
using namespace std;

//для быстрой смены точности
typedef double TYPE;
typedef double TYPE2;

//структура вектора
struct Vector{
	TYPE2 *mas;
};

//структура матрицы
struct Matrix{
	TYPE *di; //диагональные элементы
	TYPE *ggu;//верхнего треугольника
	TYPE *ggl;//нижнего треугольника
	int *ig;//массив указателей строк
	int *jg;//номера столбцов
	int N;//размерность матрицы
};
//cтруктура точки с координатами(r,fi)
struct coord {
	TYPE r;
	TYPE fi;
};

//структура конечного элемента
struct FELEM {
	//порядковый номер конечного элемента - его номер в массиве
	int num[3]; //массив соответствия локальных номеров узлов глобальным
	int nvkat; //номер подобласти
};
struct node{
	coord node_coord;//координаты узла
};
//структура краевых условий
struct Kraevie {
	int NumUsl; //номер краевого (I, II, III)
	coord Begin;// координаты начала ребра
	coord End; //координаты конца ребра
	int NumFunc; //номер функции, соответствующей краевому условию
};
