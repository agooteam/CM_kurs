#include "data.h"
#include "functions.h"

char *file="node.txt";
char *file2="finit_elem.txt";
char *file3="los.txt";
char *file4="kraevie.txt";
char *file5="inter_point.txt";
MKE solve;

void main(){
	setlocale(LC_CTYPE,"rus");
	//------- ƒанные задачи
	solve.set_flag_lyambda(false);//л€мбда зависит от области
	solve.set_flag_gamma(true);//гамма константа
	//---------------------
	solve.read_node(file);//считываем данные об узлах
	solve.read_felem(file2);//считываем данные конечных элементов
	solve.read_los(file3);//считываем данные дл€ Ћќ—
	solve.read_kraevie(file4);//считываем краевые услови€
	solve.read_inter_point(file5);//считывание внутренних узлов
	solve.generate_portrate();//генерируем портрет матрицы
	solve.calc_global();//вычисление глобальной матрицы
	solve.application_kraevie();//применение краевых условий
	solve.sovle_LOS();//–ешение системы уравнений
	solve.clear_memory();//освобождаем пам€ть
	system("pause");
};