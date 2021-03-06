#include "data.h"

#define FRM_STR_OUT "%.15lf\n"
#define FRM_STR_EPS "%e\n"

class MKE{
	protected:
		Matrix A;
		TYPE D[3][3];//������� �������������
		TYPE Local[3][3];//��������� �������
		TYPE Local_pr[3];//��������� ������ ������ �����
		int count_felem;//���������� �������� ���������
		int count_node;//���������� �����
		int count_kraevie;//���������� ������� �������
		int count_inter_point;//���������� ���������� �����
		TYPE detD;//������������ ������� D
		TYPE *temp;//��������������� ������
		TYPE *temp2;//��������������� ������ 2
		TYPE *r;//������ �������
		TYPE *z;//������ ������
		TYPE *p;//��������������� ������ ��� ���
		int maxiter;//������������ ���������� ��������
		TYPE eps;//�������� �������
		TYPE alfa;//����������� �����
		TYPE betta;//����������� �����
		TYPE *pr;//������ �����
		TYPE *x;//����������� ������
		node *nodes;//����
		FELEM *felem;//�������� ��������
		Kraevie *kraevie;//������� �������
		int *interpoint;//���������� ����
		bool flag_lyambda;//true - ������ ������� �� ���������, ����� �� �������
		bool flag_gamma;//true - ����� ������� �� ���������, ����� �� �������
	public:
		//*********  �������� ������� ************//
		void read_node(char *filename);//������� ������ ������ �� �����
		void read_felem(char *filename);//������� ������ ������ �������� ���������
		void read_los(char *filename);//������� ������ ������ ��� ���
		void read_kraevie(char *filename);//������ ������� �������
		void read_inter_point(char *filename);//���������� ������� ���������� �����
		void generate_portrate();//������� ��������� ��������
		void clear_memory();//������������ ������
		void calc_global();//���������� ���������� �������
		void set_flag_lyambda(bool value);//��������� �������� ����� ������
		void set_flag_gamma(bool value);//��������� �������� ����� �����
		void application_kraevie();//���������� ������� �������
		void sovle_LOS();//����� �������
		//****** ��������������� ������� *********//
		int count_adjacence_node(int node_number);//������� �������� ������� �����
		bool search_node_in_row(int row, int node, int *list, int *temp_count);//������� ������ ���� � ������
		void add_node_in_row(int row,int node,int *list, int *position);//���������� �������� ���� � ������ ���������������� ������
		void bubble_sort(int *list, int length);//����������� ����������
		void create_portrate(int **list,int *temp_count);//�������� �������� �������
		void calc_D(int number_felem);//���������� ������� D^-1
		void calc_local(int number_felem);//���������� ��������� �������
		void calc_local_pr(int number_felem);//���������� ��������� ������� ������ �����
		TYPE get_lyambda(int number_felem, int num_node);//��������� ������ � ����������� �� ����
		TYPE get_gamma(int number_felem, int num_node);//��������� ����� � ����������� �� ����
		TYPE get_f(int number_felem, int num_node);//��������� ����� � ����������� �� ����
		void local_in_global(int number_felem);//��������� ��������� ������� � ������� � ���������� �������
		int num_pos_in_profile(int begin , int end, int column);//����� ������ ������� � ������� gg
		void kraevie_1(int begin,int end,int func);//������ �������	
		void kraevie_2(int begin,int end,int func);//������ �������
		void kraevie_3(int begin,int end,int func);//������ �������
		TYPE get_kraevie_1(int node_num, int func);//��������� �������� ������ �������
		TYPE get_kraevie_2(int node_num, int func);//��������� �������� ������ �������
		TYPE get_kraevie_3(int begin,int end,int func, TYPE *u_b);//��������� �������� ������� �������
		//********* LOS ***********//
		TYPE calc_otn_nevazka();//���������� ������������� �������
		void LOS_LU_sq();// ��� LU(sq) ������������
		void calc_start_values();//���������� ��������� ��������
		void dec_LU_sq();//LU(sq) ������������
		TYPE dec_calc_elem(int i, int j, int current_elem);//������������ ���������������� ��������
		TYPE dec_calc_diag(int j, int current_elem);//������������ ������������� ��������
		void direct(TYPE *in,TYPE *out);//������ ���
		void reverse(TYPE *in,TYPE *out);//�������� ���
		void write_result(int total,TYPE nevyazka);//����� ����������
		void mul_matrix_vector(TYPE *v);//��������� ������� �� ������
	
};
