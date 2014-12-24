#include "functions.h"

TYPE MKE::get_lyambda(int number_felem, int num_node){//лямбда
	if(flag_lyambda){
		//------ зависит от координат

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
			//case 1:return 10;	
			//case 2:return 1;
		};
	}
};

TYPE MKE::get_f(int number_felem, int num_node){//гамма
	int area = felem[number_felem].nvkat;
	switch(area){
		case 1:{
			return -20;	
			break;
		}
		case 2:{
			return 0;
			break;
		}
	};
};

TYPE MKE::get_kraevie_1(int node, int func){//получение значение первых краевых
	switch(func){
		case 1:{
			return nodes[node].node_coord.fi * nodes[node].node_coord.fi ;	//fi^2
			break;
		}
	};
};

TYPE MKE::get_kraevie_2(int func){//получение значение первых краевых
	switch(func){
		case 1:{
			return 20;
			break;
		}
		case 2:{
			return 0;
			break;
		}
	};
};

TYPE MKE::get_kraevie_3(int begin,int end,int func, TYPE *u_b){//получение значение третьих краевых
	betta = 2.0;
	switch(func){
		case 1:{
			u_b[0] = -20.0 * nodes[begin].node_coord.fi + 27.0 ;
			u_b[1] = -20.0 * nodes[end].node_coord.fi + 27.0 ;
			return betta;
			break;
		}
	};
};