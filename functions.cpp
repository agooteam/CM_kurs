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

void MKE::read_inter_point(char *filename){//функция чтения данных внутренних точек
	FILE *fp = fopen(filename,"r");
	fscanf(fp,"%d",&count_inter_point);
	if(count_inter_point != 0 ) interpoint = new int[count_inter_point];
	for(int i = 0; i < count_inter_point; i++){
		fscanf(fp,"%d",&interpoint[i]);
		interpoint[i] -- ;
	};
	fclose(fp);
};

int MKE::count_adjacence_node(int node_number){//подсчет смежных узлов с i - узлом
	bool mue = false;
	int count;
	for(int k = 0; k < count_inter_point && mue != true; k++) if(interpoint[k] == node_number) mue = true;
	if(!mue) count = 1;
	else count = 0;
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
	bool sort = true;
	while(sort){
		sort = false;
		for(int i = 0 ; i < length - 1 ;i++){
			if(list[i] > list[i+1]){
				int tt = list[i];
				list[i] = list[i+1];
				list[i+1] = tt;
				sort = true;
			}
		};
	};
};

void MKE::create_portrate(int **list,int *temp_count){//функция подсчета узлов до диагонали
	A.di = new TYPE[count_node];
	A.cdi = new TYPE[count_node];
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
		A.cdi[i] = 0;
		pr[i] = 0;
	};
	A.ggl = new TYPE[count];
	A.cggl = new TYPE[count];
	A.ggu = new TYPE[count];
	A.cggu = new TYPE[count];
	for(int i = 0 ; i < count ;i++){
		A.ggu[i] = 0;
		A.ggl[i] = 0;
		A.cggu[i] = 0;
		A.cggl[i] = 0;
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
	delete [] A.cdi;
	delete [] A.cggl;
	delete [] A.cggu;
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
	TYPE l1,l2,l3,r1,r2,r3,r_summ,g1,g2,g3,g_average, r_avarage,gg[3][3],mm[3][3];
	r1 = nodes[a].node_coord.r;
	r2 = nodes[b].node_coord.r;
	r3 = nodes[c].node_coord.r;
	l1 = get_lyambda(number_felem,a);
	l2 = get_lyambda(number_felem,b);
	l3 = get_lyambda(number_felem,c);
	g1 = get_gamma(number_felem,a);
	g2 = get_gamma(number_felem,b);
	g3 = get_gamma(number_felem,c);
	g_average = (g1+g2+g3)/3.0;
	r_avarage = (r1+r2+r3)/3.0;
	r_summ = r1+r2+r3;
	//-------- Вычисление матрицы жесткости
	for(int i = 0; i < 3;i++){
		for(int j = 0; j < 3; j++){
			 TYPE t;
			 t = det*((r_avarage*D[i][1]*D[j][1]) + (1.0/r_avarage*D[i][2]*D[j][2]));
			 gg[i][j]  = l1*t + l2*t + l3*t;
		};
	};
	//-------- Вычисление матрицы массы
	for(int i = 0; i < 3;i++){
		for(int j = 0; j < 3; j++){
			 TYPE t = g_average*r_avarage;
			 if( i == j ) t *= abs(detD)/12.0;
			 else t *= abs(detD)/24.0;
			 mm[i][j] = t;
		};
	};
	for(int i = 0; i < 3;i++){
		for(int j = 0; j < 3; j++){
			Local[i][j] = gg[i][j] + mm[i][j];
		};
	};
};

void MKE::calc_local_pr(int number_felem){//вычисление локальной вектора правой части
	int a,b,c;
	TYPE MM[3][3],r_avarage;
	a = felem[number_felem].num[0];
	b = felem[number_felem].num[1];
	c = felem[number_felem].num[2];
	TYPE r1,r2,r3,r_summ, f[3];
	r1 = nodes[a].node_coord.r;
	r2 = nodes[b].node_coord.r;
	r3 = nodes[c].node_coord.r;
	r_summ = r1+r2+r3;
	f[0] = get_f(number_felem,a);
	f[1] = get_f(number_felem,b);
	f[2] = get_f(number_felem,c);
	r_avarage = r_summ/3.0;
	
	Local_pr[0] = r_avarage*abs(detD)/24.0*(2*f[0]+ f[1] + f[2]);
	Local_pr[1] = r_avarage*abs(detD)/24.0*(f[0]+ 2*f[1] + f[2]);
	Local_pr[2] = r_avarage*abs(detD)/24.0*(f[0]+ f[1] + 2*f[2]);
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

void MKE::read_kraevie(char *filename){//Чтение краевых условий
	FILE *fp = fopen(filename,"r");
	fscanf(fp,"%d",&count_kraevie);
	kraevie = new Kraevie[count_kraevie];
	for(int i = 0; i < count_kraevie; i++){
		fscanf(fp,"%d",&kraevie[i].Begin);
		fscanf(fp,"%d",&kraevie[i].End);
		fscanf(fp,"%d",&kraevie[i].NumUsl);
		fscanf(fp,"%d",&kraevie[i].NumFunc);
		kraevie[i].Begin --;
		kraevie[i].End --;
	};
	fclose(fp);
};

void MKE::application_kraevie(){//Применение краевых условий
	TYPE tt =  A.di[0] + A.ggu[0] + A.ggu[1] + A.ggl[0] ;
	for(int i = 0; i < count_kraevie ; i++){
		int UslType = kraevie[i].NumUsl;
		if(UslType == 1) kraevie_1(kraevie[i].Begin,kraevie[i].End,kraevie[i].NumFunc);
		else if(UslType == 2) kraevie_2(kraevie[i].Begin,kraevie[i].End,kraevie[i].NumFunc);
		else kraevie_3(kraevie[i].Begin,kraevie[i].End,kraevie[i].NumFunc);
	};

};

void MKE::kraevie_1(int begin,int end,int func){//Первые краевые
	A.di[begin] = 1;
	A.di[end] = 1;
	pr[begin] = get_kraevie_1(begin,func);
	pr[end] = get_kraevie_1(end,func);	
	for(int i = A.ig[begin]; i < A.ig[begin+1]; i++) A.ggl[i] = 0;
	for(int i = A.ig[end]; i < A.ig[end+1]; i++) A.ggl[i] = 0;
	int count = A.ig[count_node];
	for(int i = 0; i < count ;i++) {
		if(A.jg[i] == begin || A.jg[i] == end) A.ggu[i] = 0;
	}
};

void MKE::kraevie_2(int begin,int end,int func){//Вторые краевые
	TYPE tetta1,tetta2,r_avarage;
	r_avarage = (nodes[begin].node_coord.r + nodes[end].node_coord.r)/2.0;
	TYPE hm = pow(nodes[begin].node_coord.r - nodes[end].node_coord.r,2);
	hm += pow(nodes[begin].node_coord.fi - nodes[end].node_coord.fi,2);
	hm = sqrt(hm);
	tetta1 = get_kraevie_2(begin,func);
	tetta2 = get_kraevie_2(end,func);
	pr[begin] += hm/6.0*r_avarage*(2.0 * tetta1 + tetta2);
	pr[end] += hm/6.0*r_avarage*(tetta1 + 2.0 *tetta2);
};

void MKE::kraevie_3(int begin,int end,int func){//Третьи краевые
	TYPE r_avarage,betta, ub[2], temp,MM[2][2];
	int global_num[2];
	global_num[0] = begin;
	global_num[1] = end;
	r_avarage = (nodes[begin].node_coord.r + nodes[end].node_coord.r)/2.0;
	TYPE hm = pow(nodes[begin].node_coord.r - nodes[end].node_coord.r,2);
	hm += pow(nodes[begin].node_coord.fi - nodes[end].node_coord.fi,2);
	hm = sqrt(hm);
	betta = get_kraevie_3(begin,end,func,ub);
	MM[0][0] = betta*hm*r_avarage/6.0*2.0;
	MM[0][1] = betta*hm*r_avarage/6.0;
	MM[1][0] = betta*hm*r_avarage/6.0;
	MM[1][1] = betta*hm*r_avarage/6.0*2.0;
	for(int i = 0; i < 2;i++){
		int ii = global_num[i];
		for(int j = 0; j < 2 ;j++){
			int jj = global_num[j];
			if(ii == jj) A.di[ii] += MM[i][j]; 
			else if(jj < ii){
				int begin = A.ig[ii];
				int end = A.ig[ii+1];
				int pos = num_pos_in_profile(begin,end,jj);
				A.ggl[pos] += MM[i][j];
			}
			else{
				int begin = A.ig[jj];
				int end = A.ig[jj+1];
				int pos = num_pos_in_profile(begin,end,ii);
				A.ggu[pos] += MM[i][j];
			}
		};
		pr[ii] += MM[i][0]*ub[0] + MM[i][1]*ub[1];
	};
};


void MKE::mul_matrix_vector(TYPE *v){
	for(int i = 0 ; i < count_node ;i++) temp[i] = 0;
	for(int i = 0 ; i < count_node ; i++){
		temp[i] += A.di[i]*v[i];
		int count_elem = A.ig[i+1] - A.ig[i];
		for(int p = 0 ; p < count_elem; p++){
			int m = A.ig[i]+p;
			int column = A.jg[m];
			temp[i] += A.ggl[m]*v[column];
			temp[column] += A.ggu[m] * v[i];
		}
	}
};

void MKE::sovle_LOS(){
	int k = 1;
	dec_LU_sq();
	calc_start_values();
	for(; k < maxiter && calc_otn_nevazka() > eps; k++) LOS_LU_sq();
	TYPE mm = calc_otn_nevazka();
	write_result(k,mm);
};
//------------------------------- ЛОС -------------------------------------
TYPE square_norma(TYPE *v, TYPE *m , int size){
	TYPE summ = 0;
	for(int i = 0; i < size ; i++ ) summ += v[i]*m[i];
	return summ;
};

TYPE norma(TYPE *v, TYPE *m , int size){
	TYPE summ = 0;
	for(int i = 0; i < size ; i++ ) summ += v[i]*m[i];
	summ = sqrt(summ);
	return summ;
};

TYPE summ_vector(TYPE *v, TYPE *m , TYPE *res, int size){
	TYPE summ = 0;
	for(int i = 0; i < size ; i++ ) res[i] = v[i]+m[i];
	return *res;
};


TYPE MKE::calc_otn_nevazka(){
	TYPE q1,q2;
	q1 = norma(r,r,A.N);
	q2 = norma(pr,pr,A.N);
	q1 /= q2; 
	return q1;
};

void MKE::LOS_LU_sq(){
	alfa = square_norma(p,r,A.N)/square_norma(p,p,A.N);
	for(int i = 0; i < A.N ; i++){
		x[i] += alfa*z[i];
		r[i] -= alfa*p[i];
	}
	reverse(r,temp2);
	mul_matrix_vector(temp2);
	direct(temp,temp2);
	betta = -square_norma(p,temp2,A.N)/square_norma(p,p,A.N);
	reverse(r,temp);
	for(int i = 0; i < A.N ; i++){
		z[i] = temp[i] + betta*z[i];//
		p[i] = temp2[i] + betta*p[i];
	}
};


void MKE::write_result(int total,TYPE nevyazka){
	FILE * fp = fopen("result.txt","w");
	for(int i = 0; i < A.N ; i++) fprintf(fp,FRM_STR_OUT,x[i]);
	fprintf(fp,"\n");
	fprintf(fp,"Невязка: "FRM_STR_EPS,nevyazka);
	fprintf(fp,"Выполнено: %d итерций\n",total);
	fclose(fp);
};

void MKE::calc_start_values(){
	for(int i = 0; i < A.N ;i++) x[i] = 0;
	direct(pr,r);
	reverse(r,z);
	mul_matrix_vector(z);
	direct(temp,p);
	
};

void MKE::dec_LU_sq(){
	int i,j,kol,kl=0,ku=0;
	for(i = 0 ; i < A.N; i++){
		kol = A.ig[i+1] - A.ig[i];
		for(j = 0; j < kol; j++){
			A.cggl[kl] = (A.ggl[kl] - dec_calc_elem(i,j,kl)) / A.cdi[A.jg[kl]];
			kl++;
		}
		for(j = 0;j < kol; j++){
			A.cggu[ku] = (A.ggu[ku] - dec_calc_elem(i,j,ku)) / A.cdi[A.jg[ku]];
			ku++;
		}
		A.cdi[i] = sqrt(A.di[i] - dec_calc_diag(j,kl));
	}

};

TYPE MKE::dec_calc_elem(int i, int j, int current_elem){
	TYPE s = 0;
	int k,J=A.jg[current_elem],p;
	for( k = j ; k > 0; k--){
		for(p = A.ig[J];p < A.ig[J+1]; p++) if(A.jg[p] == A.jg[current_elem - k]) s+= A.cggl[current_elem - k]*A.cggu[p];
	}
	return s;
};

TYPE MKE::dec_calc_diag(int j, int current_elem){
	TYPE s=0;
	int k;
	for( k = current_elem-j; k < current_elem; k++) s += A.cggl[k]*A.cggu[k];
	return s;
};

void MKE::direct(TYPE *in,TYPE *out){
	int k = 0,column,count;
	for(int i = 0; i < A.N; i++) out[i] = in[i];
	for(int i = 0 ; i < A.N; i++){	
		TYPE s=0;
		count = A.ig[i+1] - A.ig[i];
		for(int j = 0; j < count; j++, k++){ 	
			column = A.jg[k];
			s+= A.cggl[k]*out[column];
		}
		out[i] = (out[i]-s) / A.cdi[i];
	}
};

void MKE::reverse(TYPE *in,TYPE *out){
	int k = A.ig[A.N] - A.ig[0]-1,count,column;
	for(int i = 0; i < A.N; i++) out[i] = in[i];
	for(int i = A.N-1; i>=0; i--){	
		out[i] = out[i]/A.cdi[i];
		count = A.ig[i+1] - A.ig[i];
		for(int j = 0; j < count; j++, k--){	
			column = A.jg[k];
			out[column] -= A.cggu[k]*out[i];
		}	
	}
};
