#include "data.h"
#include "functions.h"

char *file="node.txt";
char *file2="finit_elem.txt";
char *file3="los.txt";
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
	solve.generate_portrate();//���������� ������� �������
	solve.calc_global();//���������� ���������� �������
	solve.clear_memory();//����������� ������
	system("pause");
};