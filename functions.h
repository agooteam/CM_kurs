#include "data.h"

class MKE{
	protected:
		Matrix A;
		TYPE D[3][3];//матрица коэффициентов
		TYPE Local[3][3];//локальная матрица
		TYPE Local_pr[3];//локальный вектор правой части
		int count_felem;//количество конечных элементов
		int count_node;//количество узлов
		int count_kraevie;//количество краевых условий
		TYPE detD;//Определитель матрицы D
		TYPE *temp;//Вспомогательный вектор
		TYPE *temp2;//Вспомогательный вектор 2
		TYPE *r;//вектор невязки
		TYPE *z;//вектор спуска
		TYPE *p;//вспомогательный вектор для ЛОС
		int maxiter;//максимальное количество итераций
		TYPE eps;//точность решения
		TYPE alfa;//коэффициент альфа
		TYPE betta;//коэффициент бетта
		TYPE *pr;//правая часть
		TYPE *x;//неизвестный вектор
		node *nodes;//узлы
		FELEM *felem;//конечные элементы
		Kraevie *kraevie;//краевые условия
		bool flag_lyambda;//true - лямбда зависит от координат, иначе от области
		bool flag_gamma;//true - гамма зависит от координат, иначе от области
	public:
		//*********  Основные функции ************//
		void read_node(char *filename);//функция чтения данных об узлах
		void read_felem(char *filename);//функция чтения данных конечных элементов
		void read_los(char *filename);//функция чтения данных для ЛОС
		void read_kraevie(char *filename);//Чтение краевых условий
		void generate_portrate();//функция генерации портрета
		void clear_memory();//освобождение памяти
		void calc_global();//вычисление глобальнйо матрицы
		void set_flag_lyambda(bool value);//установка значения флага лямбды
		void set_flag_gamma(bool value);//установка значения флага гаммы
		void application_kraevie();//Применение краевых условий
		//****** Вспомогательные функции *********//
		int count_adjacence_node(int node_number);//функция подсчета смежных узлов
		bool search_node_in_row(int row, int node, int *list, int *temp_count);//функция поиска узла в строке
		void add_node_in_row(int row,int node,int *list, int *position);//Добавление смежного узла в строку вспомогательного списка
		void bubble_sort(int *list, int length);//пузырьковая сортировка
		void create_portrate(int **list,int *temp_count);//создание портрета матрицы
		void calc_D(int number_felem);//вычисление матрицы D^-1
		void calc_local(int number_felem);//вычисление локальной матрицы
		void calc_local_pr(int number_felem);//вычисление локальной вектора правой части
		TYPE get_lyambda(int number_felem, int num_node);//Получение лямбды в зависимости от узла
		TYPE get_gamma(int number_felem, int num_node);//Получение гаммы в зависимости от узла
		TYPE get_f(int number_felem, int num_node);//Получение гаммы в зависимости от узла
		void local_in_global(int number_felem);//занесение локальной матрицы и вектора в глобальную систему
		int num_pos_in_profile(int begin , int end, int column);//поиск номера позиции в массиве gg
		void kraevie_1(int begin,int end,int func);//Первые краевые	
		void kraevie_2(int begin,int end,int func);//Вторые краевые
		void kraevie_3(int begin,int end,int func);//Третьи краевые
		TYPE get_kraevie_1(int node, int func);//получение значение первых краевых
		TYPE get_kraevie_2(int func);//получение значение вторых краевых
		TYPE get_kraevie_3(int begin,int end,int func, TYPE *u_b);//получение значение третьих краевых
		/*void read_kuslau();
		void read_matrix_data();
		void mul_matrix_vector(TYPE *v);
		void dec_LU_sq();
		TYPE dec_calc_elem(int i, int j, int current_elem);
		TYPE dec_calc_diag(int j, int current_elem);
		void allocation_memory(int type);
		void clear_memory();
		void calc_start_values(int solve);
		TYPE calc_otn_nevazka();
		void LOS_clean();
		void LOS_diag();
		void LOS_LU_sq();
		int get_maxiter();
		TYPE get_eps();
		void write_result(int total,TYPE nevyazka);
		void direct(TYPE *in,TYPE *out);
		void reverse(TYPE *in,TYPE *out);
		void generate();*/
};
