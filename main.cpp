#include "data.h"
#include "functions.h"

char *file="node.txt";
char *file2="finit_elem.txt";
char *file3="los.txt";
MKE solve;

void main(){
	setlocale(LC_CTYPE,"rus");
	solve.read_node(file);//считываем данные об узлах
	solve.read_felem(file2);//считываем данные конечных элементов
	solve.read_los(file3);//считываем данные дл€ Ћќ—
	solve.generate_portrate();//генерируем портрет матрицы
	solve.calc_global();//вычисление глобальной матрицы
	solve.clear_memory();//освобождаем пам€ть
	system("pause");
};