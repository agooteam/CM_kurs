#include "functions.h"

TYPE MKE::get_lyambda(int number_felem, int num_node){//������
	if(flag_lyambda){
		//------ ������� �� ���������

	}
	else{
		int area = felem[number_felem].nvkat;
		switch(area){
			case 1:{
				return 1;
				break;
			}
			/*case 2:{
				return 1;
				break;
			}*/
		};
	}
};

TYPE MKE::get_gamma(int number_felem, int num_node){//�����
	if(flag_gamma){
		//------ ������� �� ��������� ��� ��������� �� ���� �������
		return 1;
	}
	else{
		int area = felem[number_felem].nvkat;
		switch(area){
			//case 1:return 10;	
			//case 2:return 1;
		};
	}
};

TYPE MKE::get_f(int number_felem, int num_node){//�����
	int area = felem[number_felem].nvkat;
	switch(area){
		case 1:{
			return 10;	
			break;
		}
		case 2:{
			return 0;
			break;
		}
	};
};

TYPE MKE::get_kraevie_1(int node, int func){//��������� �������� ������ �������
	switch(func){
		case 1:{
			return 10;	
			break;
		}
	};
};

TYPE MKE::get_kraevie_2(int func){//��������� �������� ������ �������
	switch(func){
		case 1:{
			return 1;
			break;
		}
		case 2:{
			return 0;
			break;
		}
	};
};

TYPE MKE::get_kraevie_3(int begin,int end,int func, TYPE *u_b){//��������� �������� ������� �������
	betta = 1.0;
	switch(func){
		case 1:{
			u_b[0] = 10;
			u_b[1] = 10;
			return betta;
			break;
		}
	};
};
