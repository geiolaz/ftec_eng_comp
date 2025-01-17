//programa que gerencia uma lista em memoria 
//permite grava��o e leitura da lista de um arquivo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#define max 50
typedef char TEXTO[max];

typedef struct DADOS{
 int codigo;
 TEXTO nome; 
};

typedef struct LISTA{
 int codigo;
 TEXTO nome;
 LISTA *proximo; 
};

FILE *criaArquivo();
FILE *abreArquivo();
void fecha(FILE *arq);
void grava(FILE *arq, LISTA *elemento);
void ler(FILE *arq, LISTA *elemento);
LISTA *cria();
void aloca(LISTA *elemento, DADOS info);
void mostralista(LISTA *elemento);
DADOS lerElemento();
char menu();

main(){
   
   LISTA *inicio;
   FILE *arquivo;
   DADOS informa;
   char conf;
   char op='Z';
   inicio=NULL;
   while(op!='F'){
     op=menu();
     switch (op){
     case 'I': printf("\nI - inicializa lista\n");
               inicio = cria();//aloca o in�cio da lista  
               system("pause");                       
               break;
     case 'N': printf("\nN - novo elemento\n");
               if(inicio==NULL){
                 printf("\nLista nao inicializada\n");
                 system("pause");
                 }
               else{
                   informa=lerElemento(); 
                   aloca(inicio,informa);
               } 
               break;
     case 'M':      
               printf("\nM - mostra lista\n");
               if (inicio == NULL)
                  printf("\n Lista Vazia \n ");
               else
                  mostralista(inicio); 
               system("pause");
               break;
     case 'G': printf("\nG - grava arquivo\n"); 
               //gravando dados da lista no arquivo 
               if(inicio==NULL){
                 printf("\nLista nao inicializada\n");
                 system("pause");
                 }
               else{                
               printf("\n Gravando dados no arquivo\n");   
               arquivo=criaArquivo();
               grava(arquivo,inicio);
               fecha(arquivo);
               printf("\n Dados gravados....\n");
               system("pause");  
               }
               break;
     case 'L': printf("\nL - ler arquivo\n");
               //lendo dados do arquivo para lista nova
               printf("\n Lendo dados do arquivo\n");   
               arquivo=abreArquivo();
               if (inicio != NULL){
                 printf("\nExistem dados na lista em memoria");
                 printf("\nDeseja substituir pelo arquivo(S/N)?");
                 do{
                 conf=toupper(getche());
                 }while((conf!='S')&&(conf!='N'));
               }
               else
                 conf='S';
               if (conf=='S'){
                   inicio = cria();
                   ler(arquivo,inicio);  
                   mostralista(inicio);
                   printf("\n Dados lidos....\n"); 
               }
               else
                   printf("\n Arquivo nao lido....\n");
               fecha(arquivo);
               system("pause");                             
               break;
                 
     case 'F': free(inicio);
               printf("\nfinalizando sistema\n");
               break;            
                         
     default: printf("\n opcao invalida \n");
              system("pause");             
     }            
   }
   printf("\n");
   system("pause");
}

char menu(){
 system("cls");
 printf("\nI - inicializa lista");
 printf("\nN - novo elemento");
 printf("\nM - mostra lista"); 
 printf("\nG - grava arquivo"); 
 printf("\nL - ler arquivo"); 
 printf("\nF - fim");
 printf("\nDigite opcao: "); 
 fflush(stdin);
 return(toupper(getche()));    
}

//fun��o que abre o arquivo para leitura
FILE *abreArquivo(){
 FILE *arq;
 arq=fopen("dados.bin","rb");
 if (arq == NULL)
   printf("\nArquivo nao existe!\n");
 else
   printf("\nArquivo aberto com sucesso\n"); 
 return(arq);    
}

////fun��o que cria(recria) o arquivo para grava��o
FILE *criaArquivo(){
 FILE *arq;
 arq=fopen("dados.bin","wb");
 if (arq == NULL)
   printf("\nErro ao criar arquivo!\n");
 return(arq);    
}

//fun��o que fecha o arquivo
void fecha(FILE *arq){
   fclose(arq);  
}

//fun��o que grava lista no arquivo
void grava(FILE *arq, LISTA *elementos){
    LISTA *p;
    DADOS registro;
    p=elementos;
    while(p!=NULL){
      registro.codigo=p->codigo;
      strcpy(registro.nome,p->nome);
      fwrite(&registro,sizeof(DADOS),1,arq); 
      printf("\ngravando: %d - %s",registro.codigo,registro.nome);
      p=p->proximo;          
    }
}

//fun��o que le arquivo e coloca dados na lista
void ler(FILE *arq, LISTA *elementos){
    DADOS registro;
    rewind(arq);//garante que o cursor de leitura est� no inicio do arquivo
    while(!feof(arq)){
      if (fread(&registro,sizeof(DADOS),1,arq)==1)                          
         aloca(elementos,registro);  
    }     
}

//fun��o que cria a lista
LISTA *cria(){
    LISTA *p;
    p=(LISTA *)malloc(sizeof(LISTA)); 
    p->codigo=0;
    strcpy(p->nome,"inicio");
    p->proximo=NULL;
    return(p);
}

//aloca novo elemento na lista
void aloca(LISTA *elemento, DADOS info){
    LISTA *p,*n;//n � o ponteiro para alocar o novo elemento
    p=elemento;//p � o ponteiro para navega��o na lista
    if (strcmp(p->nome,"inicio")==0){//para guardar o primeiro elemento da lista no nodo j� criado 
        p->codigo=info.codigo;
        strcpy(p->nome,info.nome);
        p->proximo=NULL;
    }
    else{//para alocar os outros nodos da lista
        n=(LISTA *)malloc(sizeof(LISTA));
        n->codigo=info.codigo;
        strcpy(n->nome,info.nome);
        n->proximo=NULL;//o novo elemento n�o aponta para ninguem, por isso atribui-se NULL     
        while(p->proximo!=NULL)
             p=p->proximo;//navega��o na lista, p recebe o ponteiro do pr�ximo 
        if (p->proximo==NULL)
             p->proximo=n;  
    }     
}

//aloca novo elemento na lista
void mostralista(LISTA *elemento){
    LISTA *p;
    int conta=0;
    p=elemento;//p � o ponteiro para navega��o na lista
    while(p!=NULL){
       conta++;
       printf("Dados [%d]\n",conta);
       printf("Codigo %d \n",p->codigo);
       printf("Nome %s \n",p->nome);
       p=p->proximo;//navega��o na lista, p recebe o ponteiro do pr�ximo
    }     
}

DADOS lerElemento(){
   DADOS info;
   printf("\nDigite o codigo: ");
   scanf("%d",&info.codigo);
   printf("\nDigite o nome: ");
   fflush(stdin);
   gets(info.nome);
   return(info);    
}

