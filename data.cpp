#include "functions.h"

TYPE MKE::get_lyambda(int number_felem, int num_node){//лямбда
	if(flag_lyambda){
		//------ зависит от координат
		return 1;
	}
	else{
		int area = felem[number_felem].nvkat;
		switch(area){
			case 1:{
				return 10;
				break;
			}
			case 2:{
				return 1;
				break;
			}
		};
	}
};

TYPE MKE::get_gamma(int number_felem, int num_node){//гамма
	if(flag_gamma){
		//------ зависит от координат или константа на всей области
		return 0;
	}
	else{
		int area = felem[number_felem].nvkat;
		switch(area){
			case 1:
				{
					return 5;
					break;
				}
			case 2:
				{
					return 0;
					break;
				}
		};
	}
};

TYPE MKE::get_f(int number_felem, int num_node){//гамма
	int area = felem[number_felem].nvkat;
	switch(area){
		case 1:{
			return 5.0 * nodes[num_node].node_coord.r + 30.0 * nodes[num_node].node_coord.fi - 10.0;	
			break;
		}
		case 2:{
			return 0;
			break;
		}
	};
};

TYPE MKE::get_kraevie_1(int node_num, int func){//получение значение первых краевых
	switch(func){
		case 1:{
			return 6.0 * nodes[node_num].node_coord.fi + 2.0;	
			break;
		}
	};
};

TYPE MKE::get_kraevie_2(int node_num,int func){//получение значение первых краевых
	switch(func){
		case 1:{
			return -6.0;
			break;
		}
		case 2:{
			return -1.0;
			break;
		}
	    case 3:{
			return 6.0;
			break;
		}
	};
};

TYPE MKE::get_kraevie_3(int begin,int end,int func, TYPE *u_b){//получение значение третьих краевых
	betta = 10.0;
	switch(func){
		case 1:{
			u_b[0] = 6.0 * nodes[begin].node_coord.fi -  2.1;
			u_b[1] = 6.0 * nodes[end].node_coord.fi + 2.1;
			return betta;
			break;
		}
	};
};
