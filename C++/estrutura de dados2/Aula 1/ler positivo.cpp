#include <stdlib.h>
#include <stdio.h>
#define MAX 50

int testa (int numero, int divisor){
	//divisivel == 1
	//nao divisivel == 0
	if ((numero%divisor)==0)
		return (1);
	else
		return (0);
	
}

void imprime(int numero, char mensagem[50]){
	printf("%d - %s\n",numero,mensagem);
	
}



main(void){
	int i=0;
	do{
		
		printf("Digite um numero inteiro:");
		scanf("%d",&i);
	
		if(i>=0){
			if(testa(i,2)==1)
				imprime(i,"eh par");
			else
				imprime(i, "nao eh par");
		}
		else
			imprime(i,"eh negativo");
	
	
	}while(i!=0);

}
