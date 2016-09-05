typedef struct arvore Arvore;

Arvore * criar();
void destruir(Arvore * arv);
void imprimir(Arvore * arv);
void inserir(Arvore * arv, char * nom,char * tel,char * email);
void remover(Arvore * arv,char * nom);
void carregar_arquivo(Arvore *a, FILE *f);
void recarregar_lista(Arvore * a,FILE * f);
int buscar(Arvore * arv, char * nom);