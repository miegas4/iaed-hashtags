/******************************************************************************************
* File Name:   main.c
* Author:      Goncalo Marques (84719) / Manuel Sousa (84740)
* Revision:
* NAME:        Hashtags - IST/IAED - 2015/2016 2º Semestre
* SYNOPSIS:    #include <stdio.h>
	       #include <string.h> - strdup
	       #include <stdlib.h> 	- qsort
	       #include <stdbool.h> - bool's
	       #include "avl.h" - toda a estrura da Arvore AVL
	       #include "auxiliares.h" - funcoes auxiliares a main 
* DESCRIPTION: funcao main
* DIAGNOSTICS: tested
* USAGE:       make clean
	       make all
	       make run
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"
#include "auxiliares.h"

#define MAXCHAR 142

/******************************************************************************************
* main()
*
* Arguments: nenhum
* Returns: 0
* Description: 	Menu de comandos - Processa informacao e insere na AVL (estrutura de dados utilizada)	   
*****************************************************************************************/
int main(){
	link avl;
	bool le_hashtag = false;
	int len_mensagem = 0, indice = 0, contador = 0, repeticoes = 0;
	char c, palavra[MAXCHAR], *p;
	Item aux, max_hashtag=NULL;
	AVLinicializa(&avl);

	while (1){
		c = getchar();
		switch (c){
			case 'a':
				c = getchar();
				len_mensagem = 0;
				
				while((c = getchar()))
				{ 
					len_mensagem++;
					
					if(e_caracter_branco(c) && le_hashtag){
						le_hashtag = false;
						palavra[indice] = '\0';
						indice = 0;
						p = palavra;
						p++;
						aux = STsearch(avl, p);

						if (aux == NULLitem){
							contador++;
							repeticoes++;

							STinsert(&avl, newItem(p, 1));

							if (max_hashtag != NULL){
								//verifica a hashtag mais popular
								if (1 == max_hashtag->rep && strcmp(p, max_hashtag->hashtag) < 0){
									max_hashtag = STsearch(avl, p);
								}
							}
							else
								max_hashtag = STsearch(avl, p);
						}
						else{
							aux->rep++;

							//verifica a hashtag mais popular
							if (aux->rep > max_hashtag->rep){
								max_hashtag = aux;
							}
							else if (aux->rep == max_hashtag->rep && strcmp(p, max_hashtag->hashtag) < 0){
								max_hashtag = aux;
							}

							repeticoes++;
						}
					}
					if(le_hashtag){
						if (c >= 65 && c <= 90)
							palavra[indice++] = tolower(c);
						else
							palavra[indice++] = c;
					}

					if (c == '#' && !(le_hashtag)){
						le_hashtag = true;
						palavra[indice++] = c;
					}
					if (c == '\n' || len_mensagem == MAXCHAR)
						break;
				}
				break;

			case 's':
				printf("%d %d\n", contador, repeticoes);
				break;

			case 'm':
				if (max_hashtag != NULL)
					printf("#%s %d\n", max_hashtag->hashtag, max_hashtag->rep);
				break;

			case 'l':
			{
				Item *vetor;
				int i=0,a=0;
				vetor=(Item*)malloc(sizeof(Item)*contador);
				arvore_para_array(avl,vetor,&a);
				qsort(vetor, contador, sizeof(Item), ordenaHashtags);
				for(i=0;i<contador;i++){
					printf("#%s %d\n",vetor[i]-> hashtag,vetor[i]->rep);
				}
				free(vetor);
				break;
			}
		}
		if (c == 'x'){
			STfree(&avl);
			return 0;
		}
	}
	return 0;
}
