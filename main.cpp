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
	//------- ������ ������
	solve.set_flag_lyambda(false);//������ ������� �� �������
	solve.set_flag_gamma(true);//����� ���������
	//---------------------
	solve.read_node(file);//��������� ������ �� �����
	solve.read_felem(file2);//��������� ������ �������� ���������
	solve.read_los(file3);//��������� ������ ��� ���
	solve.read_kraevie(file4);//��������� ������� �������
	solve.read_inter_point(file5);//���������� ���������� �����
	solve.generate_portrate();//���������� ������� �������
	solve.calc_global();//���������� ���������� �������
	solve.application_kraevie();//���������� ������� �������
	solve.sovle_LOS();//������� ������� ���������
	solve.clear_memory();//����������� ������
	system("pause");
};