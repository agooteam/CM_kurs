#include "functions.h"

TYPE MKE::get_lyambda(int number_felem, int num_node){//������
	if(flag_lyambda){
		//------ ������� �� ���������

	}
	else{
		int area = felem[number_felem].nvkat;
		switch(area){
			case 1:return 10;	
			case 2:return 1;
		};
	}
};

TYPE MKE::get_gamma(int number_felem, int num_node){//�����
	if(flag_gamma){
		//------ ������� �� ��������� ��� ��������� �� ���� �������
		return 0;
	}
	else{
		int area = felem[number_felem].nvkat;
		switch(area){
			//case 1:return 10;	
			//case 2:return 1;
		};
	}
};

TYPE MKE::get_gamma(int number_felem, int num_node){//�����
	int area = felem[number_felem].nvkat;
	switch(area){
		case 1:return -20;	
		case 2:return 0;
	};
};