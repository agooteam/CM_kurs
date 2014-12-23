#include "functions.h"

void MKE::read_node(char *filename){//функция чтения данных об узлах
	FILE *fp = fopen(filename,"r");
	fscanf(fp,"%d",&count_node);
	nodes = new node[count_node];//выделяем память под узлы
	for(int i = 0;i < count_node; i++){
		fscanf(fp,"%lf %lf",&nodes[i].node_coord.r,&nodes[i].node_coord.fi);
	};
	fclose(fp);
};

void MKE::read_felem(char *filename){//функция чтения данных конечных элементов
	FILE *fp = fopen(filename,"r");
	fscanf(fp,"%d",&count_felem);
	felem = new FELEM[count_felem];
	for(int i =0; i < count_felem; i++){
		fscanf(fp,"%d %d %d %d",&felem[i].num[0],&felem[i].num[1],&felem[i].num[2],&felem[i].nvkat);
		for(int j = 0 ; j < 3; j++) felem[i].num[j]--;
	};
	fclose(fp);
};

void MKE::read_los(char *filename){//функция чтения данных для ЛОС
	FILE *fp = fopen(filename,"r");
	fscanf(fp,"%d %lf",&maxiter,&eps);
	fclose(fp);
};

int MKE::count_adjacence_node(int node_number){//подсчет смежных узлов с i - узлом
	int count = 1;
	for(int i = 0 ; i < count_felem ; i++){
		for(int j = 0 ; j < 3 ; j++){
			if(felem[i].num[j] == node_number) count++;
		};
	};
	return count;
};

bool MKE::search_node_in_row(int row, int node,int *list, int *temp_count){//функция поиска узла в строке
	bool result = false;
	for(int j = 0; j < temp_count[row]; j++){
		if(list[j] == node) result = true;
	}
	return result;
};

void MKE::add_node_in_row(int row,int node,int *list, int *position){
	int pos = position[row];
	list[pos] = node;
	position[row]++;
};

void MKE::bubble_sort(int *list, int length){//пузырьковая сортировка
	for(int i = 0 ; i < length ;i++){
		for(int j = 0 ; j < length - i - 1 ;j++){
			if(list[j] > list[j+1]){
				int temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		};
	};
};

void MKE::create_portrate(int **list,int *temp_count){//функция подсчета узлов до диагонали
	A.di = new TYPE[count_node];
	pr = new TYPE[count_node];
	A.ig = new int[count_node + 1];
	A.ig[0] = 0;
	A.N = count_node;
	int count = 0 , pos = 0;
	for(int i = 0 ; i < count_node; i++){
		for(int j = 0 ; j < temp_count[i]; j++){
			if(list[i][j] < i )count++;
		}
		A.ig[i+1] = count;
		A.di[i] = 0;
		pr[i] = 0;
	};
	A.ggl = new TYPE[count];
	A.ggu = new TYPE[count];
	for(int i = 0 ; i < count ;i++){
		A.ggu[i] = 0;
		A.ggl[i] = 0;
	};
	A.jg = new int[count];
	for(int i = 0 ; i < count_node; i++){
		for(int j = 0 ; j < temp_count[i]; j++){
			if(list[i][j] < i ){
				A.jg[pos] = list[i][j];
				pos++;
			}
		}
	};
	temp = new TYPE[count_node];
	temp2 = new TYPE[count_node];
	r = new TYPE[count_node];
	z = new TYPE[count_node];
	p = new TYPE[count_node];
	x = new TYPE[count_node];
};

void MKE::generate_portrate(){//функция генерации портрета матрицы
	int **list,*temp_count,*position;
	temp_count = new int[count_node];
	position = new int[count_node];
	for(int i = 0 ; i < count_node; i++) position[i] = 0;
	list = new int*[count_node];
	for(int i = 0; i < count_node; i++){
		int count = count_adjacence_node(i);
		temp_count[i] = count;
		list[i] = new int[count];
	};
	for(int i = 0; i < count_felem ;i++){
		for(int j = 0 ; j < 3 ; j++){
			int node = felem[i].num[j];
			for(int k = 0; k < 3 ;k++){
				if(k != j){
					int row = felem[i].num[k];
					if(!search_node_in_row(row,node,list[row],temp_count)){
						add_node_in_row(row,node,list[row],position);
					}
				}
			}
		};
	};
	for(int i = 0; i < count_node ;  i++) bubble_sort(list[i],temp_count[i]);
	create_portrate(list,temp_count);
	delete [] list;
	delete [] temp_count;
	delete [] position;
};

void MKE::clear_memory(){//Освобождение памяти
	delete [] A.ig;
	delete [] A.jg;
	delete [] A.ggu;
	delete [] A.ggl;
	delete [] A.di;
	delete [] temp;
	delete [] temp2;
	delete [] r;
	delete [] z;
	delete [] p;
	delete [] pr;
	delete [] x;
};

void MKE::calc_D(int number_felem){//вычисление матрицы D^-1
	int a,b,c;
	a = felem[number_felem].num[0];
	b = felem[number_felem].num[1];
	c = felem[number_felem].num[2];
	D[0][0] = nodes[b].node_coord.r * nodes[c].node_coord.fi - nodes[c].node_coord.r * nodes[b].node_coord.fi;
	D[1][0] = nodes[c].node_coord.r * nodes[a].node_coord.fi - nodes[a].node_coord.r * nodes[c].node_coord.fi;
	D[2][0] = nodes[a].node_coord.r * nodes[b].node_coord.fi - nodes[b].node_coord.r * nodes[a].node_coord.fi;
	D[0][1] = nodes[b].node_coord.fi - nodes[c].node_coord.fi;
	D[1][1] = nodes[c].node_coord.fi - nodes[a].node_coord.fi;
	D[2][1] = nodes[a].node_coord.fi - nodes[b].node_coord.fi;
	D[0][2] = nodes[c].node_coord.r - nodes[b].node_coord.r;
	D[1][2] = nodes[a].node_coord.r - nodes[c].node_coord.r;
	D[2][2] = nodes[b].node_coord.r - nodes[a].node_coord.r;
	detD = (nodes[b].node_coord.r - nodes[a].node_coord.r)*(nodes[c].node_coord.fi - nodes[a].node_coord.fi); 
	detD -= (nodes[c].node_coord.r - nodes[a].node_coord.r)*(nodes[b].node_coord.fi - nodes[a].node_coord.fi);
	for(int i = 0 ; i < 3; i++){
		for(int j = 0; j < 3 ; j++) D[i][j] = 1/detD*(D[i][j]);
	};
};

void MKE::calc_local(int number_felem){
	int a,b,c;
	a = felem[number_felem].num[0];
	b = felem[number_felem].num[1];
	c = felem[number_felem].num[2];
	TYPE det = abs(detD)/3.0;
	TYPE l1,l2,l3,r1,r2,r3,r_summ,g1,g2,g3,g_average;
	r1 = nodes[a].node_coord.r;
	r2 = nodes[b].node_coord.r;
	r3 = nodes[c].node_coord.r;
	l1 = get_lyambda(number_felem,a);
	l2 = get_lyambda(number_felem,b);
	l3 = get_lyambda(number_felem,c);
	g1 = get_gamma(number_felem,a);
	g2 = get_gamma(number_felem,a);
	g3 = get_gamma(number_felem,a);
	g_average = (g1+g2+g3)/3.0;
	r_summ = r1+r2+r3;
	//-------- Вычисление матрицы жесткости
	for(int i = 0; i < 3;i++){
		for(int j = 0; j < 3; j++){
			 TYPE t;
			 t = det*((r_summ/3.0*D[i][1]*D[j][1]) + (3.0/r_summ*D[i][2]*D[j][2]));
			 Local[i][j]  = l1*t + l2*t + l3*t;
		};
	};
	//-------- Вычисление матрицы массы
	for(int i = 0; i < 3;i++){
		for(int j = 0; j < 3; j++){
			 TYPE t = g_average*(r_summ/3.0);
			 if( i == j ) t *= abs(detD)/12.0;
			 else t *= abs(detD)/24.0;
			 Local[i][j]  += t;
		};
	};	
};

void MKE::calc_local_pr(int number_felem){//вычисление локальной вектора правой части
	int a,b,c;
	a = felem[number_felem].num[0];
	b = felem[number_felem].num[1];
	c = felem[number_felem].num[2];
	TYPE r1,r2,r3,r_summ,f[3];
	r1 = nodes[a].node_coord.r;
	r2 = nodes[b].node_coord.r;
	r3 = nodes[c].node_coord.r;
	r_summ = r1+r2+r3;
	f[0] = get_f(number_felem,a);
	f[1] = get_f(number_felem,b);
	f[2] = get_f(number_felem,c);
	for(int i = 0 ; i < 3 ;i++){
		Local_pr[i] = 0.0;
		for(int j = 0 ; j < 3; j++){
			TYPE t = (r_summ/3.0)*detD/24.0;
			if( i == j ) t *= 4.0 * f[j];
			else t *= 3.0 * f[j];
			Local_pr[i] += t;
		};
	};
};

void MKE::local_in_global(int number_felem){//занесение локальной матрицы и вектора в глобальную систему
	int global_num[3];
	global_num[0] = felem[number_felem].num[0];
	global_num[1] = felem[number_felem].num[1];
	global_num[2] = felem[number_felem].num[2];

	for(int i = 0; i < 3 ;i++){
		int ii;
		ii = global_num[i];
		for(int j = 0 ; j < 3 ;j++){
			int jj;
			ii = global_num[i];
			jj = global_num[j];
			if(ii == jj) A.di[ii] += Local[i][j]; 
			else if(jj < ii){
				int begin = A.ig[ii];
				int end = A.ig[ii+1];
				int pos = num_pos_in_profile(begin,end,jj);
				A.ggl[pos] += Local[i][j];
			}
			else{
				int begin = A.ig[jj];
				int end = A.ig[jj+1];
				int pos = num_pos_in_profile(begin,end,ii);
				A.ggu[pos] += Local[i][j];
			}
		};
		pr[ii] += Local_pr[i]; 
	};
};

void MKE::calc_global(){//вычисление глобальной матрицы
	for(int i = 0; i < count_felem ; i++){
		calc_D(i);
		calc_local(i);
		calc_local_pr(i);
		local_in_global(i);
	}
};


void MKE::set_flag_lyambda(bool value){//установка значения флага лямбды
	flag_lyambda = value;
};

void MKE::set_flag_gamma(bool value){//установка значения флага гаммы
	flag_gamma = value;
};

int MKE::num_pos_in_profile(int begin , int end, int column){//поиск номера позиции в массиве gg 
	
	for(int i = begin ; i < end; i++){
		if(A.jg[i] == column) return i;
	};
};