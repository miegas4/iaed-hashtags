/******************************************************************************
* File Name: avl.h
* Author:      Goncalo Marques (84719) / Manuel Sousa (84740)
* Revision:
* NAME
*      avl - prototipos
* SYNOPSIS:    #include <stdio.h>
	       #include <string.h> - strdup
	       #include <stdlib.h> - qsort
	       #include "item.h"   - prototipos das funcoes que violam abstracao
* DESCRIPTION
*		Prototipos e estruturas da AVL TREE
* DIAGNOSTICS
*          OK
*****************************************************************************/
#ifndef _AVL_
#define _AVL_
#include <stdio.h>
#include <stdlib.h>
#include "item.h"

typedef struct STnode* link;

//no da arvore
struct STnode { 
	Item item; 
	link l, r; 
	int peso;
};

Item AVLprocura(link head, Key v);

Item searchR(link h, Key v);

link max(link h);

link min(link h);

link rotL(link h);

link rotR(link h);

link rotLR(link h);

link rotRL(link h);

link NOVO(Item item, link l, link r);

link AVLbalance(link h);

link deleteR(link h, Key k) ;

link insertR(link h, Item item);

link freeR(link h);

void AVLinicializa(link*);

void AVLapaga(link*,Key);

void AVLinsere(link*,Item);

void decrescente(link h, void (*visit)(Item));

void AVLimprime(link ,void (*visit)(Item));

void AVLliberta(link*);

void AVL_para_array(link h,Item *vec,int *i);

int AVLconta(link);

int Balance(link h);

int count(link h);

int peso(link h);


#endif
