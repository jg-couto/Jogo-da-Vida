//JVIDA2-JJLM - Projeto (Model) - Etapa 6
//29/11/2023
//Grupo: JJLM
//Luis Augusto Coelho de Souza
//Joao Guilherme Costa Couto
//Matheus Heimrath Barbosa
//Joao Alfredo

#include "JVIDA2-JJLM_Model.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

//Cria o tipo de estrutura cel que armazena a posicao de uma celula e possui um ponteiro que aponta para proxima celula 
typedef struct cel 
{
	int lin, col; 
 	struct cel *next; 
} TipoCel;

TipoCel *pvivo, *pmorto, *pvivoprox; //Cria os ponterios que irao ajudar no processo de criacao de 3 listas simplesmente ligadas, uma de vivos, uma de mortos e uma de vivos da proxima geracao

typedef struct c
{
	int lin, col;
}Cel;

//Cria a lista que salvara as celulas da lista de vivos atuais
typedef struct list
{
	int cont; //tamanho da lista de ate no maximo 400 celulas vivas iniciais
	Cel L[400];
}TipoLista;

TipoLista Lvivo; //inicia a lista Lvivo

//Cria o arquivo com salvamento de até 50 configuracoes
struct arquivo
{
	TipoLista TL; //1 lista total
}LConfig[50];


