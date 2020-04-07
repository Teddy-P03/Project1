#include "abandoned.h"

A_Record* dogs[ALL];
A_Record* shelter[MAX_DOGS];
int _count = 0;
int _num = 0;

int a_is_available(){
	int i;
	for(i=0;i<MAX_DOGS;i++){
		if(dogs[i] == NULL) return 1;
	}
	return 0;
}

int a_first_available(){
	int i;
	for(i=0;i<MAX_DOGS;i++){
		if(dogs[i] == NULL) return i;
	}
	return -1;
}

int a_count(){
	return _count;
}
int a_allcount(){
	return _num;
}

void a_create(char* b, char* se, char* c, float w, char* d){
	int index = a_first_available();
	shelter[index] = (A_Record*)malloc(sizeof(A_Record));
	A_Record* p = shelter[index];
	strcpy(p->breed, b);
	strcpy(p->sex, se);
	strcpy(p->color, c);
	p->weight = w;
	strcpy(p->dis, d);
	strcpy(p->st, "On notice");
	_num++;
	int n[3];
	n[0] = _num / 100;
	n[1] = (_num%100) / 10;
	n[2] = _num%10;
	for(int i=0;i<3;i++){
		p->num[i] = n[i];
	}
	_count++;
	
	dogs[index] = (A_Record*)malloc(sizeof(A_Record));
	A_Record* a = dogs[index];
	strcpy(a->breed, b);
	strcpy(a->sex, se);
	strcpy(a->color, c);
	a->weight = w;
	strcpy(a->dis, d);
	strcpy(a->st, "In shelter");
	for(int i=0;i<3;i++){
		a->num[i] = n[i];
	}
}

A_Record* a_search_by_num(int n){
	int i,j,k;
	int _n[3];
	_n[0] = n / 100;
	_n[1] = (n%100) / 10;
	_n[2] = n%10;
	for(i=0;i<MAX_DOGS;i++){
		if(shelter[i]){
			k=0;
			for(j=0;j<3;j++){
				if(shelter[i]->num[j] == _n[j]){
					k++;
				}
			}
			if(k  == 3) return shelter[i];
		}
	}
	return NULL;
}

char* getnum(A_Record* p){
	char* nums = (char*)malloc(sizeof(4));
	char n1[2], n2[2], n3[2];
	sprintf(n1, "%d", p->num[0]);
	sprintf(n2, "%d", p->num[1]);
	sprintf(n3, "%d", p->num[2]);
	strcat(n1,n2);
	strcat(n1,n3); 
	strcpy(nums,n1);
	return nums;
}

void a_update(A_Record* p){
	strcpy(p->st,"Notice expiration");
}

void a_delete(A_Record* p){
	int i, index;
	for(i=0;i<MAX_DOGS;i++){
		if(shelter[i]==p){
			index=i;
			break;
		}
	}
	free(p);
	shelter[index] = NULL;
	_count--;
}

void before_d(A_Record* p, int h){
	int i;
	for(i=0;i<_num;i++){
		if(dogs[i]){
			int j, k;
			k=0;
			for(j=0;j<3;j++){
				if(dogs[i]->num[j] == p->num[j]){
					k++;
				}
			}
			if(k==3){
				if(h==1){
					strcpy(dogs[i]->st,"Adoption");
					break;
				}
				else if(h==2){
					strcpy(dogs[i]->st,"Temporary protection");
					break;
				}
				else if(h==3){
					strcpy(dogs[i]->st,"Return");
					break;
				}
				else{
					strcpy(dogs[i]->st,"Death");
					break;
				}
			}
		}
	}
}

void a_get_shelter(A_Record* a[]){
	int i, j=0;
	for(i=0;i<MAX_DOGS;i++){
		if(shelter[i]){
			a[j]=shelter[i];
			j++;
		}
	}
}

void a_get_all(A_Record* a[]){
	int i, j=0;
	for(i=0;i<ALL;i++){
		if(dogs[i]){
			a[j]=dogs[i];
			j++;
		}
	}
}

char* a_to_string(A_Record* p){
	static char str[80];
	sprintf(str, "[%s] %d%d%d호 %s %s %s %.1fkg (%s에서 발견됨)", p->st, p->num[0], p->num[1], p->num[2], p->breed, p->sex, p->color, p->weight, p->dis);
	return str;
}

char* a_getbreed(A_Record* p){
	return p->breed;
}

char* a_getsex(A_Record* p){
	return p->sex;
}

char* a_getcolor(A_Record* p){
	return p->color;
}

float a_getweight(A_Record* p){
	return p->weight;
}

char* a_getdiscovery(A_Record* p){
	return p->dis;
}

char* a_getstatus(A_Record* p){
	return p->st;
}

int a_search_by_breed(A_Record* bR[],char* b){
	int i,j=0, size = a_count();
	for(i=0;i<size;i++){
		if((strstr(shelter[i]->breed,b))!=0){
			bR[j]=shelter[i];
			j++;
		}
	}
	return j;
}
int a_search_by_sex(A_Record* seR[], char* se){
	int i, j=0, size = a_count();
	for(i=0;i<size;i++){
		if((strstr(shelter[i]->sex,se))!=0){
			seR[j]=shelter[i];
			j++;
		}
	}
	return j;
}
int a_search_by_color(A_Record* cR[], char* c){
	int i, j=0, size = a_count();
	for(i=0;i<size;i++){
		if((strstr(shelter[i]->color,c))!=0){
			cR[j]=shelter[i];
			j++;
		}
	}
	return j;
}
int a_search_by_dis(A_Record* dR[], char* d){
	int i, j=0, size=a_count();
	for(i=0;i<size;i++){
		if((strstr(shelter[i]->dis,d))!=0){
			dR[j]=shelter[i];
			j++;
		}
	}
	return j;
}
int a_search_by_st(A_Record* sR[],char* s){
	int i,j=0,size=a_count();
	for(i=0;i<size;i++){
		if((strstr(shelter[i]->st,s))!=0){
			sR[j]=shelter[i];
			j++;
		}
	}
	return j;
}

void a_sort(A_Record* p){

}

int mk_class_b(struct class* breeds[]){
	int i,j,k=0,input;
	for(i=0;i<_num;i++){
		input=0;
		if(k!=0){
			for(j=0;j<k;j++){
				if(strcmp(breeds[j]->kind,dogs[i]->breed)==0){
					breeds[j]->num += 1;
					input++;
				}
			}
			if(input==0){
				breeds[k]=(struct class*)malloc(sizeof(struct class));
				strcpy(breeds[k]->kind,dogs[i]->breed);
				breeds[k]->num =1;
				k++;
			}
		}
		else{
			breeds[k]=(struct class*)malloc(sizeof(struct class));
			strcpy(breeds[k]->kind,dogs[i]->breed);
			breeds[k]->num =1;
			k++;
		}
	}
	return k;
}

int mk_class_d(struct class* diss[]){
	int i,j,k=0,input;
	for(i=0;i<_num;i++){
		input=0;
		if(k!=0){
			for(j=0;j<k;j++){
				if(strcmp(diss[j]->kind,dogs[i]->dis)==0){
					diss[j]->num += 1;
					input++;
				}
			}
			if(input==0){
				diss[k]=(struct class*)malloc(sizeof(struct class));
				strcpy(diss[k]->kind,dogs[i]->dis);
				diss[k]->num =1;
				k++;
			}
		}
		else{
			diss[k]=(struct class*)malloc(sizeof(struct class));
			strcpy(diss[k]->kind,dogs[i]->dis);
			diss[k]->num =1;
			k++;
		}
	}
	return k;
}

int for_stat(int cn){
	int i, output;
	if(cn==0){
		return _num;
	}
	else if(cn==1){
		return _count;
	}
	else if(cn==2){
		output=0;
		for(i=0;i<_count;i++){
			if(strstr(shelter[i]->st,"On")!=0){
				output++;
			}
		}
		return output;
	}
	else if(cn==3){
		output=0;
		for(i=0;i<_count;i++){
			if(strstr(shelter[i]->st,"exp")!=0){
				output++;
			}
		}
		return output;
	}
	else if(cn==4){
		output=0;
		for(i=0;i<_num;i++){
			if(strstr(dogs[i]->st,"dopt")!=0){
				output++;
			}
		}
		return output;
	}
	else if(cn==5){
		output=0;
		for(i=0;i<_num;i++){
			if(strstr(dogs[i]->st,"protect")!=0){
				output++;
			}
		}
		return output;
	}
	else if(cn==6){
		output=0;
		for(i=0;i<_num;i++){
			if(strstr(dogs[i]->st,"turn")!=0){
				output++;
			}
		}
		return output;
	}
	else if(cn==7){
		output=0;
		for(i=0;i<_num;i++){
			if(strstr(dogs[i]->st,"eath")!=0){
				output++;
			}
		}
		return output;
	}
	else if(cn==8){
		output=0;
		for(i=0;i<_count;i++){
			if(strstr(shelter[i]->st,"emale")!=0){
				output++;
			}
		}
		return output;
	}
	else if(cn==9){
		output=0;
		for(i=0;i<_count;i++){
			if(strstr(shelter[i]->st,"emale")!=0){
				output++;
			}
		}
		return (_count - output);
	}
	else return 0;
}
	
