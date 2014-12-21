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
	A.ig = new int[count_node + 1];
	A.ig[0] = 1;
	A.N = count_node;
	int count = 0 , pos = 0;
	for(int i = 0 ; i < count_node; i++){
		for(int j = 0 ; j < temp_count[i]; j++){
			if(list[i][j] < i )count++;
		}
		A.ig[i+1] = count + 1;
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
	pr = new TYPE[count_node];
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
	for(int i = 0; i < 3;i++){
		for(int j = 0; j < 3; j++){
			
		};
	};
};

void MKE::calc_global(){
	for(int i = 0; i < count_felem ; i++){
		calc_D(i);
		calc_local(i);
	}
};