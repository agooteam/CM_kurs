#include "data.h"

class MKE{
	protected:
		Matrix A;
		TYPE D[3][3];//матрица коэффициентов
		TYPE Local[3][3];//локальная матрица
		int count_felem;//количество конечных элементов
		int count_node;//количество узлов
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
	public:
		//*********  Основные функции ************//
		void read_node(char *filename);//функция чтения данных об узлах
		void read_felem(char *filename);//функция чтения данных конечных элементов
		void read_los(char *filename);//функция чтения данных для ЛОС
		void generate_portrate();//функция генерации портрета
		void clear_memory();//освобождение памяти
		void calc_global();//вычисление глобальнйо матрицы
		//****** Вспомогательные функции *********//
		int count_adjacence_node(int node_number);//функция подсчета смежных узлов
		bool search_node_in_row(int row, int node, int *list, int *temp_count);//функция поиска узла в строке
		void add_node_in_row(int row,int node,int *list, int *position);//Добавление смежного узла в строку вспомогательного списка
		void bubble_sort(int *list, int length);//пузырьковая сортировка
		void create_portrate(int **list,int *temp_count);//создание портрета матрицы
		void calc_D(int number_felem);//вычисление матрицы D^-1
		void calc_local(int number_felem);//вычисление локальной матрицы



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
