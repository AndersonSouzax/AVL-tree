#include<stdio.h>
#include<stdlib.h>
#include "Arv_avl.h"
#include<string.h>
int main(){

Arvore * a = criar();
FILE * f;
char p[15],m[9],n[20];
int i=0;
f = fopen("Contatos.txt","r");
if(f==NULL){
	printf("Erro ao abrir o arq.\n");
}
carregar_arquivo(a,f);
while(i!=6){
printf("\t****************************************************\n");
printf("\t**********************AGENDA************************\n");
printf("\t****************************************************\n\n\n");
printf("1.Recarregar Lista\n");
printf("2.Mostrar Contatos em ordem alfabetica\n");
printf("3.Consultar Fone e e-mail\n");
printf("4.Remover um contato\n");
printf("5.Inserir Contato\n");
printf("6.sair\n");
printf("---------------------------------------------------\n");
scanf("%d",&i);
switch(i){
case 1:
recarregar_lista(a,f);
break;

case 2:
imprimir(a);
break;

case 3:
fflush(stdin);
printf("Digite o nome do contato: ");
gets(p);
buscar(a,p);
break;

case 4:
printf("Digite o nome do contato: ");
fflush(stdin);
gets(p);
remover(a,p);
break;

case 5:
printf("Digite o nome do contato: ");
fflush(stdin);
gets(p);
printf("Digite o telefone do contato: ");
gets(m);
printf("Digite o email do contato: ");
gets(n);
inserir(a,p,m,n);
break;

case 6:
i=6;
break;

default:
printf("Digite um numero de 1 a 6\n");
}
system("pause");
system("cls");
}
return 0;
}