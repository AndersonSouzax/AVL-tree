#include<stdio.h>
#include<stdlib.h>
#include "Arv_avl.h"
#include<string.h>

typedef struct no No;

struct no{
char nome[15];
char tel[9];
char email[20];
int FB;
No * esq;
No * dir;
};

struct arvore{
	No * raiz;
};


Arvore * criar(){
	Arvore * a = (Arvore*)malloc(sizeof(Arvore));
	a->raiz = NULL;
	return a;
}

void destruir_rec(No * raiz) {
	if (raiz != NULL) {
		destruir_rec(raiz->esq);
		destruir_rec(raiz->dir);
		free(raiz);
	}
}

void destruir(Arvore * arv) {
	destruir_rec(arv->raiz);
	arv->raiz = NULL;
	free(arv);
}

void limpar(Arvore * a){
	destruir_rec(a->raiz);
	a->raiz = NULL;
}

void imp_raiz(No * raiz){
	if(raiz != NULL){
    int i;
	printf("|");
	for(i=0;raiz->nome[i]!='\0';i++){
		printf("%c",raiz->nome[i]);
	 }
	printf(" | ");
	for(i=0;i<8;i++){
		printf("%c",raiz->tel[i]);
	 }
	printf(" | ");
	for(i=0;raiz->email[i]!='\0';i++){
		printf("%c",raiz->email[i]);
	 }
	printf("\n");
	}
}
void inordem(No * raiz) {
  if (raiz != NULL) {
    inordem(raiz->esq);
	imp_raiz(raiz);
	inordem(raiz->dir);
  }
}

void posord(No * raiz){
   if(raiz != NULL){
	   posord(raiz->esq);
	   posord(raiz->dir);
	   imp_raiz(raiz);
   }
}
void imprimir(Arvore * a){
	posord(a->raiz);
}

int folha(No * raiz){
 if(raiz!=NULL){
    if(raiz->esq==NULL && raiz->dir==NULL){
       return 1;
    }else{
      return  0;
    }
  }
 return 0;
}

int raiz_comp(No * raiz){
	if(raiz != NULL){
     if(raiz->esq != NULL && raiz->dir !=NULL){
		 return 1;
	 }else{
		 return 0;
	 }
	}else{
	return 0;
	}
}

No * rotacionar_esq(No * no){
	No * aux = no->dir; 
	no->dir = aux->esq; 
	aux->esq = no;
	if(folha(no)==1 || raiz_comp(no)){
	no->FB = 0;
	}
	if(no->esq != NULL && no->dir == NULL){
		no->FB = -1;
	}
	if(no->esq == NULL && no->dir != NULL){
		no->FB = 1;
	}
	aux->FB= 0;
	return aux; 
}

No * rotacionar_dir(No * no){
	No * aux = no->esq; 
	no->esq = aux->dir;  
	aux->dir = no;
	if(folha(no)==1 || raiz_comp(no)){
	no->FB = 0;
	}
	if(no->esq != NULL && no->dir == NULL){
		no->FB = -1;
	}
	if(no->esq == NULL && no->dir != NULL){
		no->FB = 1;
	}
	aux->FB= 0;
	return aux; 
}

No * rotacaoDupla_esq(No * raiz){
  raiz->dir = rotacionar_dir(raiz->dir);
  return rotacionar_esq(raiz);
}

No * rotacaoDupla_dir(No * raiz){
  raiz->esq = rotacionar_esq(raiz->dir);
  return rotacionar_dir(raiz);
}

void inserir_rec(No * * praiz,char * nom,char * tel,char * email){
	No * raiz = *praiz;
	int i,tam;
	if (raiz!= NULL) {
		for(i=0;nom[i]!='\0';i++){
			tam = i;
		}
		if (strncmp(nom,raiz->nome,tam)<0){
			int alt_ant = 50;
			int nulo_ant=0;

			if(raiz->esq!=NULL){
              alt_ant = raiz->esq->FB;
            }
            
			if(raiz->esq == NULL){
               nulo_ant = 1;
            }

			inserir_rec(&(raiz->esq),nom,tel,email);
	
			if(alt_ant != 50){
              if(alt_ant != 0 && raiz->esq->FB==0){
                 return;
              }
		        
            }

			if(raiz->esq != NULL){
             if(nulo_ant == 1){
              raiz->FB--;
             }else{
              if(alt_ant == 0 && abs(raiz->esq->FB) == 1){
               raiz->FB--;
              }
             }
            }

		   if(raiz->FB == -2){
			  if(raiz->esq != NULL && raiz->esq->FB == -1){
              *praiz = rotacaoDupla_dir(raiz);
              }else{
               *praiz = rotacionar_dir(raiz);
              }
            }
	    }
		if (strncmp (nom, raiz->nome,tam)>0) {
		   int alt_ant = 50;
		   int nulo_ant=0;
			if(raiz->dir!=NULL){
              alt_ant = raiz->dir->FB;
            }
			if(raiz->dir == NULL){
				nulo_ant = 1;
			}

		   inserir_rec(&(raiz->dir),nom,tel,email);

		   if(alt_ant != 50){
              if(alt_ant != 0 && raiz->dir->FB==0){
                 return;
              }
            }

		   if(raiz->dir != NULL){
            if(nulo_ant == 1){
             raiz->FB++;
            }else{
             if(alt_ant == 0 && abs(raiz->dir->FB) == 1){
               raiz->FB++;
               }
             }
           }


		  if(raiz->FB == 2){
            if(raiz->dir != NULL && raiz->dir->FB == -1){  
              *praiz = rotacaoDupla_esq(raiz);
              }else{
              *praiz = rotacionar_esq(raiz);
             }
         }
	  }
	}else{
		raiz = (No*)malloc(sizeof(No));
		for(i=0;nom[i]!='\0';i++){
			raiz->nome[i] = nom[i];
		}
		raiz->nome[i] = '\0';
		for(i=0;tel[i]!='\0';i++){
			raiz->tel[i] = tel[i];
		}
		raiz->tel[i] = '\0';
		for(i=0;email[i]!='\0';i++){
			raiz->email[i] = email[i];
		}
		raiz->email[i] = '\0';
		raiz->esq = NULL; 
		raiz->dir = NULL;
		raiz->FB = 0;
		*praiz = raiz;
	 }
}
void inserir(Arvore * arv, char * nom,char * tel,char * email) {
	inserir_rec(&(arv->raiz),nom,tel,email);
}

int buscar_rec(No * raiz, char * nom) {
	int i,tam=0;
	if (raiz != NULL) {
		for(i=0;nom[i]!='\0';i++){
			tam = i;
		}
		if (strncmp(nom,raiz->nome,tam)<0) {
			return buscar_rec(raiz->esq, nom);
		}
		if (strncmp(nom,raiz->nome,tam)>0){
			return buscar_rec(raiz->dir,nom);
		}
		imp_raiz(raiz);
	}
	return 0;
}

int buscar(Arvore * arv, char * nom) {
	return buscar_rec(arv->raiz, nom);
}

int raiz_meio_comp(No * raiz){
	return raiz->dir != NULL ||
		   raiz->esq !=NULL;
}


void remover_menor_rec(No * * praiz,char * nom,char * tel,char * email) {
	int i;
	No * raiz = *praiz;
	int alt_ant;
	if (raiz->esq != NULL) {
    alt_ant = raiz->esq->FB;
    remover_menor_rec(&(raiz->esq),nom,tel,email);

	  if(raiz->esq != NULL){
         if(alt_ant != 0 && raiz->esq->FB == 0 ){
             raiz->FB++;
               } 
           }else{
             if(raiz->FB == 0 || raiz->FB == -1){
                 raiz->FB++;
              }else{ 
              if(raiz->FB == 1 && raiz_meio_comp(raiz->dir)){
                 raiz->FB++;
              }
			 }
         }

	      if(raiz->FB == 2){
             if(raiz->dir->FB ==  -1){
              *praiz = rotacaoDupla_esq(raiz);
               }else{
                *praiz = rotacionar_esq(raiz);
               }
               
           }

           if(raiz->FB == -2){ 
            if(raiz->esq->FB ==  1){
             *praiz = rotacaoDupla_dir(raiz);
              }else{
             *praiz = rotacionar_dir(raiz);
              }
		   }
		
	}else{
	*praiz = raiz->dir;
	for(i=0;raiz->nome[i]!='\0';i++){
		nom[i] = raiz->nome[i];
	}
	nom[i] = '\0';
	for(i=0;raiz->tel[i]!='\0';i++){
		tel[i] = raiz->tel[i];
	}
	tel[i] = '\0';
	for(i=0;raiz->email[i]!='\0';i++){
		email[i] = raiz->email[i];
	}
	email[i] = '\0';
	free(raiz);
	}
}

void remover_rec(No * * praiz, char * nom) {
	No * raiz = *praiz;
	int i,tam;
	if (raiz != NULL) {
	    for(i=0;nom[i]!='\0';i++){
			tam = i;
		}
		if (strncmp(nom,raiz->nome,tam)<0) {
			 int alt_antesq;
            if(raiz->esq != NULL){
                alt_antesq = raiz->esq->FB;
             }
			remover_rec(&(raiz->esq), nom);
			//*******Subida pela esquerda********//
			if(raiz->esq != NULL){
               if(alt_antesq != 0 && raiz->esq->FB == 0 ){
                      raiz->FB++;
                  } 
            }else{
              if(raiz->FB == 0 || raiz->FB == -1){
                 raiz->FB++;
              } else{
               if(raiz->FB == 1 && raiz_meio_comp(raiz->dir)){
                 raiz->FB++;
               }
			  }
			}
			if(raiz->FB == 2){
             if(raiz->dir->FB ==  -1){
              *praiz = rotacaoDupla_esq(raiz);
               }else{
                *praiz = rotacionar_esq(raiz);
               }
              
            }

           if(raiz->FB == -2){ 
            if(raiz->esq->FB ==  1){
             *praiz = rotacaoDupla_dir(raiz);
              }else{
             *praiz = rotacionar_dir(raiz);
             }
	       
         }
		//****************************************//	
		}else{
			if (strncmp(nom,raiz->nome,tam) > 0) {
				 int alt_antdir;
               if(raiz->dir != NULL){
                  alt_antdir = raiz->dir->FB;
                }

				remover_rec(&(raiz->dir), nom);
		//********Subida pela direita**********//
               if(raiz->dir != NULL){
               if(alt_antdir != 0 && raiz->dir->FB == 0 ){
                      raiz->FB--;
                  } 
            }else{
              if(raiz->FB == 0 || raiz->FB == 1){
                 raiz->FB--;
              }else{
               if(raiz->FB == -1 && raiz_meio_comp(raiz->esq)){
                 raiz->FB--;
               }
			  }
			}
			if(raiz->FB == 2){
             if(raiz->dir->FB ==  -1){
              *praiz = rotacaoDupla_esq(raiz);
               }else{
                *praiz = rotacionar_esq(raiz);
               }
              
            }

           if(raiz->FB == -2){ 
            if(raiz->esq->FB ==  1){
             *praiz = rotacaoDupla_dir(raiz);
              }else{
             *praiz = rotacionar_dir(raiz);
             }
	       
           }
		   //********************************//
			} else {
				//FOLHA
				if (raiz->esq == NULL && raiz->dir == NULL) {
					*praiz = NULL;
					free(raiz);
				} else { 
					//1 FILHO
					if (raiz->esq == NULL || raiz->dir == NULL) {
						*praiz = raiz->esq != NULL ? raiz->esq : raiz->dir;
						free(raiz);
					} else { //2 FILHOS
						int alt_antdir;
						if(raiz->dir != NULL){
							alt_antdir = raiz->dir->FB;
						}
						remover_menor_rec(&(raiz->dir),raiz->nome,raiz->tel,raiz->email);

						if(raiz->dir != NULL){
                         if(alt_antdir != 0 && raiz->dir->FB == 0 ){
                             raiz->FB--;
                          } 
                        }else{
                        if(raiz->FB == 0 || raiz->FB == 1){
                           raiz->FB--;
                          }else{ 
                         if(raiz->FB == -1 && raiz_meio_comp(raiz->esq)){
                         raiz->FB--;
                           }
						 }
			           }
		               if(raiz->FB == 2){
                         if(raiz->dir->FB ==  -1){
                          *praiz = rotacaoDupla_esq(raiz);
                           }else{
                            *praiz = rotacionar_esq(raiz);
                           }
                          
                        }
		               
                       if(raiz->FB == -2){ 
                        if(raiz->esq->FB ==  1){
                         *praiz = rotacaoDupla_dir(raiz);
                          }else{
                         *praiz = rotacionar_dir(raiz);
                         }
	        
                       }
					   //**********************************//
					}
				}
			}
		}
	}
}

void remover(Arvore * arv, char * nom) {
	remover_rec(&(arv->raiz),nom);
}

void imprime_l_rec(No * raiz,int id){
	int i;
	if(raiz!=NULL){
	for(i=0;i<id;i++){
		printf(" ");
	}
	for(i=0;raiz->nome[i]!='\0';i++){
	  printf("%c",raiz->nome[i]);
	}
	printf("%d\n",raiz->FB);
	imprime_l_rec(raiz->esq,id+1);
    imprime_l_rec(raiz->dir,id+1);
	}else{
	for(i=0;i<id;i++){
		printf(" ");
	}	
	printf("-\n");
	}
}

void imprime_l(Arvore *a,int id){
	imprime_l_rec(a->raiz,0);
}

void carregar_arquivo(Arvore *a, FILE *f){
	int i,j,k;
	char c = fgetc(f);
	while(c != '*'){
    char  nom[15];
	char  tel[9];
	char  email[20];
	i=0;
	j=0;
	k=0;
	while(c!=' '){
     nom[i] = c;
	 i++;
	 c = fgetc(f);
	}
	nom[i]='\0';
	c = fgetc(f);
	while(c!=' '){
      tel[j] = c;
	  j++;
	  c = fgetc(f);
	}
	tel[j] = '\0';

	c = fgetc(f);
	while(c!=' '){
    email[k] = c;
	k++;
	c = fgetc(f);
	}
	email[k] = '\0';
	inserir(a,nom,tel,email);
	c = fgetc(f);
	}
	rewind(f);
}

void recarregar_lista(Arvore * a,FILE * f){
	limpar(a);
	carregar_arquivo(a,f);
}