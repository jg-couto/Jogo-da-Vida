//JVIDA2-JJLM - Projeto (View) - Etapa 6
//29/11/2023
//Grupo: JJLM
//Luis Augusto Coelho de Souza
//Joao Guilherme Costa Couto
//Matheus Heimrath Barbosa
//Joao Alfredo

#include "JVIDA2-JJLM_View.h"

void apresentaMensagem(char msg[100]) //Apresenta uma mensagem caso necessario
{
	printf("%s\n", msg); 
}

int rconfirma(char msg[100]) //Apresenta uma mensagem que tera resposta S ou N retornando 1 ou 0
{
	char R;
	while(R!='S' && R!='N') //Enquanto nao obtiver a resposta esperada
		{
		fclear(); //Limpa o buffer	
		printf("%s\n", msg); //Apresenta a mensagem escolhida
		scanf("%c", &R); //recupera a resposta
		R=toupper(R); //Coloca a resposta em Maiusculo
		if(R=='S') //Se for S retorna 1
			return 1;
		}
		
		return 0; //Se nao retorna 0
}

int Txtmenuprin() //Aqui temos a funcao que sera o menu do jogo da vida, aonde o usuario podera escolher a opcao desejada
{
	int op;
	
	printf("(1) - Apresentar o Mapa\n");
	printf("(2) - Limpar o Mapa\n");
	printf("(3) - Incluir/excluir celulas vivas\n");
	printf("(4) - Mostrar/esconder celulas mortas vizinhas\n");
	printf("(5) - Avancar geracao\n");
	printf("(6) - Apresentar as listas de vivos e mortos\n");
	printf("(7) - Salvar configuracao atual de geracao\n");
	printf("(8) - Carregar ultima geracao salva\n");
	printf("(9) - Deletar salvamentos anteriores\n");
	printf("(10) - Regras de evolucao de celulas\n");
	printf("(0) - Sair\n");
	printf("Selecione a opcao desejada: ");
	scanf("%d", &op);
	
	return op;
}

void ApresentaMatriz() 
{
	printf("    ");
	
	for(int c = 0; c < tamanho; c++) //apresnta os numeros das colunas
		printf("%2d  ",c+1);
		
    printf("\n");
	
	for(int k=0; k<tamanho; k++) //apresenta os numeros das linhas
		{
		printf("%2d  ",k+1);
		
		for(int i=0; i<tamanho; i++) //troca os espacos da matriz que foram ocupadas
			printf("%2c  ", Vida[k][i]);
		printf("\n");
		}
		
	printf("\n");
	
	mostraLvivo(); //mostra a lista de vivos
	mostraLmorto(); //mostra a lista de mortos
}

void TamanhoMatriz() //pergunta ao usuario qual vai ser o tamanho da matriz
{
	while(tamanho<10 || tamanho>60)
		{
		system("cls");
		printf("Digite o tamanho da matriz desejada (entre 10 e 60): ");
		scanf("%d", &tamanho);
		}
	system("cls");
}

char Remove() //Se a celula selecionada estiver ocupada, pergunta ao usuario se ele quer remove-la
{	
	char opM = NULL;
	while(opM!='S' && opM!='N')
		{
		fclear();	
		printf("Ja ha uma celula nesta posicao, deseja remove-la: (S para sim, N para nao):");
		scanf("%c",&opM);
		opM = toupper(opM); 
		}
		
	return opM;
}

int InsereRemoveLinha() 
{
	int linha=-1;
	int erro=0;
	while(linha<0 || linha>tamanho) //pedimos em qual linha o usuario quer colocar uma celula viva, e comparamos se esta de acordo com o tamanho da matriz
		{
		system("cls");
		ApresentaMatriz();
		printf("Realize as adicoes necessarias a matriz. Quando terminar digite 0.");
		if(erro==1)
			printf("\nDigite uma linha valida (entre 1 e %d)", tamanho); //Caso nao seja, pedimos novamente	
		printf("\nDigite a linha da posicao a ser alterada. Para desistir da operacao digite 0: "); //aqui pedimos a linha a ser colocada
		scanf("%d", &linha);
		erro=1;
		}
	system("cls");	
		
	return linha;
}

int InsereRemoveColuna() //pedimos em qual coluna o usuario quer colocar uma celula viva, e comparamos se esta de acordo com o tamanho da matriz 
{
	int coluna=-1;
	int erro=0;
	while(coluna<0 || coluna>tamanho)
		{
		system("cls");
		ApresentaMatriz();
		if(erro==1)
			printf("Digite uma coluna valida (entre 1 e %d)", tamanho);	//Caso nao seja, pedimos novamente	
		printf("\nDigite a coluna da posicao a ser alterada. Para desistir da operacao digite 0: "); //aqui pedimos a coluna a ser colocada
		scanf("%d", &coluna);
		erro=1;
		}
	system("cls");
		
	return coluna;
}

int TxtQtdGeracao() //Coleta ate qual geracao sera avancada
{
	int qt=-1;
	int erro=0;
	while(qt<0)
		{
		system("cls");
		ApresentaMatriz();
		if(erro==1)
			printf("Digite um numero valido (maior que 0).");	//Caso nao seja correto, pedimos novamente	
		printf("\nDigite para qual geracao deseja avancar. Para desistir da operacao digite 0: "); 
		scanf("%d", &qt);
		erro=1;
		}
		
	return qt;
}

int delay() //Coleta quanto tempo em segundos o usuario deseja de atraso entre geracoes
{
	int vel=-1;
	int erro=0;
	while(vel<0)
		{
		if(erro==1)
			{
			printf("Digite um numero inteiro valido (maior ou igual a 0).");	//Caso nao seja correto, pedimos novamente	
			}
		fclear();
		printf("\nDetermine a velocidade de apresentacao das geracoes em segundos. (Digite 0 para apresentacao passo a passo)"); 
		scanf("%d", &vel);
		erro=1;
		}
		
	system("cls");
	return vel;
}

void GeracaoAtual(int n) //Apresenta a mensagem de texto que indica qual a geracao atual
{
	printf("_______________________________________________________________");
	printf("\nGeracao %d\n\n", n);
}

void regras()
{
	system("cls");
	printf("Para um espaco com celula viva:\n");
	printf("Cada celula com um ou menos vizinhos vivos morre de solidao\n");
	printf("Cada celula com quatro ou mais vizinhos vivos morre por estar em superpopulacao\n");
	printf("Cada celula com dois ou tres vizinhos sobrevive\n");
	
	printf("Para um espaco vazio:\n");
	printf("Cada celula que tiver tres vizinhos vivos torna-se populada\n");
	system("pause");
	system("cls");
	Menu();
}

void mostraLvivo()
{
	TipoCel *aux; //define um ponteiro auxiliar
	aux = pvivo; //inicializa esse ponteiro auxiliar

	printf("Coordenadas das celulas vivas: ");
	if(totvivo > 0)
		{
	
		while(aux->next != NULL)
			{
			printf("%d,%d ", aux->lin+1, aux->col+1);
			aux = aux->next; //caminha para o próximo ponteiro
			}

		printf("%d,%d ", aux->lin+1, aux->col+1); //mostra a ultima celula
		}
		
	printf("\n");
}

void mostraLmorto()
{
	TipoCel *aux; //define um ponteiro auxiliar
	aux = pmorto; //inicializa esse ponteiro auxiliar

	printf("Coordenadas das celulas mortas: ");
	if(totmorto > 0)
		{
	
		while(aux->next != NULL)
			{
			printf("%d,%d ", aux->lin+1, aux->col+1);
			aux = aux->next; //caminha para o próximo ponteiro
			}

		printf("%d,%d ", aux->lin+1, aux->col+1); //mostra a ultima celula
		}
		
	printf("\n\n");
}
