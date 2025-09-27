//JVIDA2-JJLM - Projeto (Controller) - Etapa 6
//29/11/2023
//Grupo: JJLM
//Luis Augusto Coelho de Souza
//Joao Guilherme Costa Couto
//Matheus Heimrath Barbosa
//Joao Alfredo

#include "JVIDA2-JJLM_Controller.h"
#include "JVIDA2-JJLM_View.cpp"

void Menu()
{
	MostraMorto=0; //MostraMorto inicia com 0, indicando que os mortos iniciam desativados
	int qtd;
	int vel;
	int op;
	int k;
	do
	{
		//system("cls");
		ApresentaMatriz();
		fclear();
		op = Txtmenuprin(); //op recebe a opcao digitada pelo usuario no menu principal
		system("cls");
		
		switch(op)
			{
				case 1: //Apresenta o mapa
					system("cls");
					ApresentaMatriz();
				break;
				
				case 2: //Limpar o Mapa
					CriaMatriz(); //A recria a Matriz (envolve prencher todas as posicoes com '.' novamente) 
					LimpaListaVivo(); //Limpa a lista dos vivos
					LimpaListaMorto(); //Limpa a lista dos mortos
				break;
				
				case 3: //Incluir/excluir celulas vivas
					AttMatriz();
				break;
				
				case 4: //Mostrar/esconder mortos vizinhos
						if(MostraMorto==0) //Se ao clicar nessa opcao a sentinela for = 0
							{
							MostraMorto=1; //Sera atualizada para 1, indicando que os mortos estao sendo mostrados
							AttMortos(); //Adiciona os mortos a matriz
							}
							
						else 
							{
							MostraMorto=0;	//Sera atualizada para 0, indicando que os mortos estao sendo escondidos
							EscondeMorto(); //Esconde os mortos
							}
				break;
				
				case 5: //iniciar o processo
					qtd=TxtQtdGeracao(); //Inicia a variavel qtd que recolhe quantas geracoes serao avancadas
					
					vel=delay(); //Inicia a mensagem de texto que pedira a velocidade de aparecimento de cada geracao
					
					if(vel==0) //Se a velocidade for = 0, sera mostrado um avanco passo a passo
						{
							apresentaMensagem("Geracao 1"); //Mostra a geracao 1
							ApresentaMatriz();
							for(k=2; k<qtd; k++) //Inicia um loop que rodara qtd-1 vezes mostrando as geracoes novas e pausando com system("pause")
								{
								system("pause");
								GeracaoAtual(k); //Apresenta a mensagem de texto indicando o numero da geracao
								ProxGeracao(); //Avanca a geracao
								ApresentaMatriz(); //Mostra a matriz nova
								}
							ProxGeracao();//Avanca a geracao
							system("pause"); //Pausa uma ultima vez		
							GeracaoAtual(k);	//Apresenta o texto de nova geracao, que sera seguido pela matriz nova (apresentada no inicio do menu em si)
						}
						
					else //Se nao for 0
						{
							apresentaMensagem("Geracao 1"); //Mostra a geracao 1
							ApresentaMatriz();
							for(k=2; k<qtd; k++) //Inicia um loop que rodara qtd-1 vezes mostrando as geracoes novas e pausando com system("pause")
								{
								ftempo(vel); //Atrasa a apresentacao da proxima geracao dependendo da velocidade definida pelo operador
								GeracaoAtual(k); //Apresenta a mensagem de texto indicando o numero da geracao
								ProxGeracao(); //Avanca a geracao
								ApresentaMatriz(); //Mostra a matriz nova
								}
							ftempo(vel); //Atrasa a apresentacao da proxima geracao dependendo da velocidade definida pelo operador
							ProxGeracao(); //Avanca a geracao
							GeracaoAtual(k); //Apresenta o texto de nova geracao, que sera seguido pela matriz nova (apresentada no inicio do menu em si)
						}
				break;
				
				case 6: //Apresentar as listas
					mostraLvivo(); //Mostra as coordenadas dos vivos 
					mostraLmorto(); //Mostra as coordenadas dos mortos
				break;
				
				case 7: //Gravar uma geracao inicial
					gravaCelulas(); //Grava as celulas presentes no mapa
				break;
				
				case 8: //Recuperar uma geracao inicial cadastrada
					carregaConfig(); //Busca a ultima config salva
					if(qtconf>0)
						{	
						CriaMatriz(); //Limpa a matriz
						LimpaListaVivo(); //Limpa a lista dos vivos
						LimpaListaMorto(); //Limpa a lista dos mortos 
						pvivo=NULL; //Limpa a conexao do ponteiro pvivo
						recuperaCelulas(); //Carrega a lista de vivos com a ultima config salva 
						CarregaMatriz(); //Carrega a matriz com a lista dos vivos
						EscondeMorto();//Apaga os mortos antigos
						AttMortos(); //Atualiza os mortos 
						CarregaListaMorto(); //Carrega a lista dos mortos com as atualizacoes da matriz
						
						if(MostraMorto==0) //Esconde os mortos na matriz (se necessario)
							EscondeMorto();
						}
					else
						apresentaMensagem("Nao ha configuracao a ser recuperada");
				break;
				
				case 9: //Limpar o cadastro de geracoes iniciais cadastradas (n geracoes)
					limpaGer(); //Limpa o cadastro de geracoes
				break;
				
				case 10: //Regras de evolucao das celulas 
					regras(); 
				break;
				
				case 0: //Sair
				break;
				
				default:
					system("cls");
					printf("Opcao invalida, por favor selecione um digito entre 0 e 5");
				break;
			}
		
	}while(op!=0);
}

void AttMatriz()
{
	char opM;
	int linha;
	int coluna;
	int fim=0;
	LimpaListaMorto();
	
	do
	{
		ApresentaMatriz();
			
		linha = InsereRemoveLinha(); //linha recebera o numero da linha digitada
		if(linha==0)
			break;
			
		coluna = InsereRemoveColuna(); //coluna recebera o numero da coluna digitada
		if(coluna==0)
			break;
		
		linha--; //tiramos 1 numero de cada pois a matriz comeca em 0, e nao em 1 como e` mostrada pro usuario
		coluna--;
		
		if(Vida[linha][coluna]=='O') //Se houver uma celula viva pergunta se o operador deseja remove-la
			{
				opM=Remove();	
					
				if(opM=='S') //Se desejar, remove a celula e apaga os mortos proximos da celula
					{
					Vida[linha][coluna]='.';
					excluiLVivo(linha, coluna);
					EscondeMorto();
					}
			}
		
		else  //Senao, acresenta uma celula viva na posicao
			{
				carregaVivo(linha, coluna);
				Vida[linha][coluna]='O';
			}
		
		if(MostraMorto==1) //Se for preciso mostrar os mortos, atualiza a matriz adicionando-os
			AttMortos();	

	}while(1);
	
	if(MostraMorto==0) //Se os mortos estiverem desativados ativa-os temporariamente para carregar a lista de mortos com as atualizacoes 
		{
		AttMortos(); 
		CarregaListaMorto();
		EscondeMorto();
		}
		
	else //Se estiverem ativados apenas carrega a lista dos mortos
		CarregaListaMorto(); 
	
}

void CriaMatriz()
{
	for(int l = 0; l < tamanho; l++) //Cria as linhas partindo de 0 ate o tamanho definido
	{
		for (int c = 0; c < tamanho; c++) //Crias as colunas pra cada linha
		{
			Vida[l][c] = '.'; //cada espaco da matriz sera definida com '.'   
		}
	}
}

void AttMortos() //Atualiza a matriz para apresentar os mortos
{
	int l;
	int c;
	
	for (int c = 1; c < tamanho-1; c++) //Verifica apenas a primeira linha, excluindo os cantos final e inicial
		{
			if(Vida[0][c] == 'O') //Se encontra celula viva adiciona os mortos ao seu redor sem invadir espaco nao alocado
				{
					if(Vida[0][c-1]=='.')
						Vida[0][c-1]='+';
					
					if(Vida[0][c+1]=='.')
						Vida[0][c+1]='+';
					
					if(Vida[1][c-1]=='.')
						Vida[1][c-1]='+';
					
					if(Vida[1][c]=='.')
						Vida[1][c]='+';
					
					if(Vida[1][c+1]=='.')	
						Vida[1][c+1]='+';
				}	 
		}
		
	for (int c = 1; c < tamanho-1; c++) //Verifica apenas a ultima linha da matriz (tamanho -1 para adaptar o indice da matriz), excluindo os cantos final e inicial
		{
			if(Vida[tamanho-1][c] == 'O') //Se encontra celula viva adiciona os mortos ao seu redor sem invadir espaco nao alocado
				{
					if(Vida[tamanho-1][c-1]=='.')
						Vida[tamanho-1][c-1]='+';
					
					if(Vida[tamanho-1][c+1]=='.')
						Vida[tamanho-1][c+1]='+';
					
					if(Vida[tamanho-2][c-1]=='.')
						Vida[tamanho-2][c-1]='+';
					
					if(Vida[tamanho-2][c]=='.')
						Vida[tamanho-2][c]='+';
					
					if(Vida[tamanho-2][c+1]=='.')	
						Vida[tamanho-2][c+1]='+';
				}

		} 
		
	for(int l = 1; l < tamanho-1; l++) //Verifica a primeira coluna da matriz, excluindo os cantos final e inicial
		{
			if(Vida[l][0] == 'O') //Se encontra celula viva adiciona os mortos ao seu redor sem invadir espaco nao alocado
				{
					if(Vida[l-1][0]=='.')
						Vida[l-1][0]='+';
					
					if(Vida[l+1][0]=='.')
						Vida[l+1][0]='+';
					
					if(Vida[l-1][1]=='.')
						Vida[l-1][1]='+';
					
					if(Vida[l][1]=='.')
						Vida[l][1]='+';
					
					if(Vida[l+1][1]=='.')	
						Vida[l+1][1]='+';
				}
		}
		
	for(int l = 1; l < tamanho-1; l++) //Verifica a ultima coluna, excluindo os cantos final e inicial
		{
			if(Vida[l][tamanho-1] == 'O') //Se encontra celula viva adiciona os mortos ao seu redor sem invadir espaco nao alocado
				{
					if(Vida[l-1][tamanho-1]=='.')
						Vida[l-1][tamanho-1]='+';
					
					if(Vida[l+1][tamanho-1]=='.')
						Vida[l+1][tamanho-1]='+';
					
					if(Vida[l-1][tamanho-2]=='.')
						Vida[l-1][tamanho-2]='+';
					
					if(Vida[l][tamanho-2]=='.')
						Vida[l][tamanho-2]='+';
					
					if(Vida[l+1][tamanho-2]=='.')	
						Vida[l+1][tamanho-2]='+';
				}
		}
		
	//Verifica a parte interna da matriz (fora as primeiras e ultimas coluna e linha e os cantos da matriz) 	
	for(int l = 1; l < tamanho-1; l++) 
	{
		for (int c = 1; c < tamanho-1; c++) 
		{
			if(Vida[l][c] == 'O') //Se encontra celula viva adiciona os mortos ao seu redor sem invadir espaco nao alocado
				{
					if(Vida[l-1][c-1]=='.')
						Vida[l-1][c-1]='+';
						
					if(Vida[l-1][c]=='.')
						Vida[l-1][c]='+';
					
					if(Vida[l-1][c+1]=='.')
						Vida[l-1][c+1]='+';
					
					if(Vida[l][c-1]=='.')
						Vida[l][c-1]='+';
					
					if(Vida[l][c+1]=='.')
						Vida[l][c+1]='+';
					
					if(Vida[l+1][c-1]=='.')
						Vida[l+1][c-1]='+';
					
					if(Vida[l+1][c]=='.')
						Vida[l+1][c]='+';
					
					if(Vida[l+1][c+1]=='.')
						Vida[l+1][c+1]='+';
					
				}
		}
	} 
	
	if(Vida[0][0]=='O') //Verifica o canto superior esquerdo da matriz
		{
			//Se encontra celula viva adiciona os mortos ao seu redor sem invadir espaco nao alocado
			if(Vida[0][1]=='.')
				Vida[0][1]='+';
			
			if(Vida[1][0]=='.')
				Vida[1][0]='+';
			
			if(Vida[1][1]=='.')
				Vida[1][1]='+';
		}
				
	if(Vida[0][tamanho-1]=='O') //Verifica o canto superior direito da matriz
		{
			//Se encontra celula viva adiciona os mortos ao seu redor sem invadir espaco nao alocado
			if(Vida[0][tamanho-2]=='.')
				Vida[0][tamanho-2]='+';
			
			if(Vida[1][tamanho-2]=='.')
				Vida[1][tamanho-2]='+';
			
			if(Vida[1][tamanho-1]=='.')
				Vida[1][tamanho-1]='+';	
		}
				
	if(Vida[tamanho-1][0]=='O') //Verifica o canto inferior esquerdo da matriz
		{
			//Se encontra celula viva adiciona os mortos ao seu redor sem invadir espaco nao alocado
			if(Vida[tamanho-2][0]=='.')
				Vida[tamanho-2][0]='+';
			
			if(Vida[tamanho-2][1]=='.')
				Vida[tamanho-2][1]='+';
			
			if(Vida[tamanho-1][1]=='.')
				Vida[tamanho-1][1]='+';
		}
				
	if(Vida[tamanho-1][tamanho-1]=='O') //Verifica o canto inferior direito da matriz
		{
			//Se encontra celula viva adiciona os mortos ao seu redor sem invadir espaco nao alocado
			if(Vida[tamanho-2][tamanho-2]=='.')
				Vida[tamanho-2][tamanho-2]='+';
			
			if(Vida[tamanho-1][tamanho-2]=='.')
				Vida[tamanho-1][tamanho-2]='+';
			
			if(Vida[tamanho-2][tamanho-1]=='.')
				Vida[tamanho-2][tamanho-1]='+';
		}
}

void EscondeMorto() //Apaga os mortos da matriz
{
	for(int l = 0; l < tamanho; l++) 
	{
		for (int c = 0; c < tamanho; c++) 
		{
			if(Vida[l][c]=='+')
				Vida[l][c]='.';
		}	
	}
}

void ProxGeracao() //Muda para a proxima geracao falta pensar sobre a geracao das listas
{
	//Preenche a lista dos vivos da prox geracao
	NextFilho(); 
	NextSobrevive();
	
	//Limpa as listas de vivos e mortos atuais
	LimpaListaVivo();
	LimpaListaMorto();
	
	//Copia a lista dos vivos da proxima geracao para os vivos atuais 
	pvivo = pvivoprox; //pvivo recebe o objeto apontado por pvivoprox
	pvivoprox=NULL; //pvivoprox passa a apontar para nada
	totvivo=totvivoprox; //atualiza a quantidade de vivos
	totvivoprox=0; //zera a quantidade de vivos da prox geracao
	
	//Reinicia a matriz original, carrega ela com os dados da proxima geracao e inicia os mortos
	CriaMatriz(); //limpa a matriz
	CarregaMatriz(); //Carrega a matriz com a lista de vivos
	AttMortos(); //Mostra os mortos na matriz original
	
	CarregaListaMorto(); //Carrega a lista dos mortos em preparo para proxima geracao
	
	if(MostraMorto==0) //Se nao estiver mostrando os mortos, atualiza a matriz para esconde-los
		EscondeMorto();
		
}
	
void NextFilho() //Carrega as celulas que irao nascer na prox geracao na lista 
{
	int contador;
	char P;
	int l, c;
	
	TipoCel *aux; //define um ponteiro auxiliar
	aux = pmorto; //inicializa esse ponteiro auxiliar que ira procurar nas posicoes vizinhas para saber se havera o nascimento de uma celula

	if(totvivo > 0) //Se houverem celulas vivas para serem analisadas
	{
	
	do  //O loop rodara ate que analise todas as celulas mortas
		{
		l=aux->lin; //Pega a posicao da celula morta
		c=aux->col;
				
		P=ProcuraPosicao(l, c); //Captura a posicao da celula
		
		if(P=='-')//Verifica apenas a primeira linha, excluindo os cantos final e inicial
			{
				//Soma a um contador quando acha celula viva
				if(Vida[0][c-1]=='O')
					contador++;
					
				if(Vida[0][c+1]=='O')
					contador++;
					
				if(Vida[1][c-1]=='O')
					contador++;
					
				if(Vida[1][c]=='O')
					contador++;
					
				if(Vida[1][c+1]=='O')	
					contador++;
						
				if(contador==3) //Se houverem 3 celulas vivas vizinhas, adiciona uma celula viva na lista
					carregaVivoProx(l, c);
			
				contador=0;	//Zera o contador para reiniciar o processo em outra celula		
				 
			}
		
		else if(P=='_') //Verifica apenas a ultima linha da matriz (tamanho -1 para adaptar o indice da matriz), excluindo os cantos final e inicial
			{
				//Soma a um contador quando acha celula viva
				if(Vida[tamanho-1][c-1]=='O')
					contador++;
					
				if(Vida[tamanho-1][c+1]=='O')
					contador++;
					
				if(Vida[tamanho-2][c-1]=='O')
					contador++;
						
				if(Vida[tamanho-2][c]=='O')
					contador++;
					
				if(Vida[tamanho-2][c+1]=='O')	
					contador++;
						
				if(contador==3)//Se houverem 3 celulas vivas vizinhas, adiciona uma celula viva na lista
					carregaVivoProx(l, c);	
							
				contador=0; //Zera o contador para reiniciar o processo em outra celula	
			} 
		
		else if(P=='[') //Verifica a primeira coluna da matriz, excluindo os cantos final e inicial
			{
				//Soma a um contador quando acha celula viva
				if(Vida[l-1][0]=='O')
					contador++;
					
				if(Vida[l+1][0]=='O')
					contador++;
					
				if(Vida[l-1][1]=='O')
					contador++;
					
				if(Vida[l][1]=='O')
					contador++;
						
				if(Vida[l+1][1]=='O')	
					contador++;			
			
				if(contador==3) //Se houverem 3 celulas vivas vizinhas, adiciona uma celula viva na lista
					carregaVivoProx(l, c);	
							
				contador=0; //Zera o contador para reiniciar o processo em outra celula	
			}
		
		else if(P==']') //Verifica a ultima coluna, excluindo os cantos final e inicial
			{
				//Soma a um contador quando acha celula viva
				if(Vida[l-1][tamanho-1]=='O')
					contador++;
					
				if(Vida[l+1][tamanho-1]=='O')
					contador++;
						
				if(Vida[l-1][tamanho-2]=='O')
					contador++;
					
				if(Vida[l][tamanho-2]=='O')
					contador++;
					
				if(Vida[l+1][tamanho-2]=='O')	
					contador++;
							
				if(contador==3) //Se houverem 3 celulas vivas vizinhas, adiciona uma celula viva na lista
					carregaVivoProx(l, c);
						
				contador=0; //Zera o contador para reiniciar o processo em outra celula	
			}
		
		//Verifica a parte interna da matriz (fora as primeiras e ultimas coluna e linha e os cantos da matriz) 	
		else if(P=='M') 
			{
				//Soma a um contador quando acha celula viva
				if(Vida[l-1][c-1]=='O')
					contador++;
						
				if(Vida[l-1][c]=='O')
					contador++;
					
				if(Vida[l-1][c+1]=='O')
					contador++;
						
				if(Vida[l][c-1]=='O')
					contador++;
						
				if(Vida[l][c+1]=='O')
					contador++;
					
				if(Vida[l+1][c-1]=='O')
					contador++;
						
				if(Vida[l+1][c]=='O')
					contador++;
					
				if(Vida[l+1][c+1]=='O')
					contador++;
						
				if(contador==3) //Se houverem 3 celulas vivas vizinhas, adiciona uma celula viva na lista
					carregaVivoProx(l, c);	
						
				contador=0; //Zera o contador para reiniciar o processo em outra celula	
			} 
	
		else if(P=='1') //Verifica o canto superior esquerdo da matriz
			{
				//Soma a um contador quando acha celula viva
				if(Vida[0][1]=='O')
					contador++;
			
				if(Vida[1][0]=='O')
					contador++;
			
				if(Vida[1][1]=='O')
					contador++;
				
				if(contador==3) //Se houverem 3 celulas vivas vizinhas, adiciona uma celula viva na lista
					carregaVivoProx(l, c);
								
				contador=0; //Zera o contador para reiniciar o processo em outra celula	
			}
				
		else if(P=='2') //Verifica o canto superior direito da matriz
			{
				//Soma a um contador quando acha celula viva
				if(Vida[0][tamanho-2]=='O')
					contador++;
			
				if(Vida[1][tamanho-2]=='O')
					contador++;
			
				if(Vida[1][tamanho-1]=='O')
					contador++;
				
				if(contador==3) //Se houverem 3 celulas vivas vizinhas, adiciona uma celula viva na lista
					carregaVivoProx(l, c);
							
				contador=0; //Zera o contador para reiniciar o processo em outra celula	
			}
				
		else if(P=='3') //Verifica o canto inferior esquerdo da matriz
			{
				//Soma a um contador quando acha celula viva
				if(Vida[tamanho-2][0]=='O')
					contador++;
			
				if(Vida[tamanho-2][1]=='O')
					contador++;
			
				if(Vida[tamanho-1][1]=='O')
					contador++;
				
				if(contador==3)  //Se houverem 3 celulas vivas vizinhas, adiciona uma celula viva na lista
					carregaVivoProx(l, c);	
							
				contador=0; //Zera o contador para reiniciar o processo em outra celula	
			}
				
		else if(P=='4') //Verifica o canto inferior direito da matriz
			{
				//Soma a um contador quando acha celula viva
				if(Vida[tamanho-2][tamanho-2]=='O')
					contador++;
				
				if(Vida[tamanho-1][tamanho-2]=='O')
					contador++;
			
				if(Vida[tamanho-2][tamanho-1]=='O')
					contador++;
					
				if(contador==3) //Se houverem 3 celulas vivas vizinhas, adiciona uma celula viva na lista
					carregaVivoProx(l, c);	

				contador=0; //Zera o contador para reiniciar o processo em outra celula	
		}
		
		aux = aux->next; //caminha para o próximo ponteiro
			
	}while(aux != NULL); 
	
	}
}

void NextSobrevive() //Carrega as celulas que irao sobreviver na prox geracao na lista 
{
	int contador;
	char P;
	int l, c;
	
	TipoCel *aux; //define um ponteiro auxiliar
	aux = pvivo; //inicializa esse ponteiro auxiliar que pegara a celula viva a ser analisada

	if(totvivo > 0) //Se houver celulas vivas
	{
	
	do  //Loop que rodara ate analisar todas celulas vivas 
		{
		l=aux->lin; //Pega a posicao da celula
		c=aux->col;
				
		P=ProcuraPosicao(l, c);
		
		if(P=='-')//Verifica apenas a primeira linha, excluindo os cantos final e inicial
			{
				//Soma a um contador quando acha celula viva
				if(Vida[0][c-1]=='O')
					contador++;
					
				if(Vida[0][c+1]=='O')
					contador++;
					
				if(Vida[1][c-1]=='O')
					contador++;
					
				if(Vida[1][c]=='O')
					contador++;
					
				if(Vida[1][c+1]=='O')	
					contador++;
						
				if(contador==2 || contador==3) //Se houverem 2 ou 3 celulas vivas vizinhas, adiciona a celula a lista
					carregaVivoProx(l, c);
			
				contador=0;	//Zera o contador para reiniciar o processo em outra celula		
				 
			}
		
		else if(P=='_') //Verifica apenas a ultima linha da matriz (tamanho -1 para adaptar o indice da matriz), excluindo os cantos final e inicial
			{
				//Soma a um contador quando acha celula viva
				if(Vida[tamanho-1][c-1]=='O')
					contador++;
					
				if(Vida[tamanho-1][c+1]=='O')
					contador++;
					
				if(Vida[tamanho-2][c-1]=='O')
					contador++;
						
				if(Vida[tamanho-2][c]=='O')
					contador++;
					
				if(Vida[tamanho-2][c+1]=='O')	
					contador++;
						
				if(contador==2 || contador==3) //Se houverem 2 ou 3 celulas vivas vizinhas, adiciona a celula a lista
					carregaVivoProx(l, c);	
							
				contador=0; //Zera o contador para reiniciar o processo em outra celula	
			} 
		
		else if(P=='[') //Verifica a primeira coluna da matriz, excluindo os cantos final e inicial
			{
				//Soma a um contador quando acha celula viva
				if(Vida[l-1][0]=='O')
					contador++;
					
				if(Vida[l+1][0]=='O')
					contador++;
					
				if(Vida[l-1][1]=='O')
					contador++;
					
				if(Vida[l][1]=='O')
					contador++;
						
				if(Vida[l+1][1]=='O')	
					contador++;			
			
				if(contador==2 || contador==3) //Se houverem 2 ou 3 celulas vivas vizinhas, adiciona a celula a lista
					carregaVivoProx(l, c);	
							
				contador=0; //Zera o contador para reiniciar o processo em outra celula	
			}
		
		else if(P==']') //Verifica a ultima coluna, excluindo os cantos final e inicial
			{
				//Soma a um contador quando acha celula viva
				if(Vida[l-1][tamanho-1]=='O')
					contador++;
					
				if(Vida[l+1][tamanho-1]=='O')
					contador++;
						
				if(Vida[l-1][tamanho-2]=='O')
					contador++;
					
				if(Vida[l][tamanho-2]=='O')
					contador++;
					
				if(Vida[l+1][tamanho-2]=='O')	
					contador++;
							
				if(contador==2 || contador==3) //Se houverem 2 ou 3 celulas vivas vizinhas, adiciona a celula a lista
					carregaVivoProx(l, c);
						
				contador=0; //Zera o contador para reiniciar o processo em outra celula	
			}
		
		//Verifica a parte interna da matriz (fora as primeiras e ultimas coluna e linha e os cantos da matriz) 	
		else if(P=='M') 
			{
				//Soma a um contador quando acha celula viva
				if(Vida[l-1][c-1]=='O')
					contador++;
						
				if(Vida[l-1][c]=='O')
					contador++;
					
				if(Vida[l-1][c+1]=='O')
					contador++;
						
				if(Vida[l][c-1]=='O')
					contador++;
						
				if(Vida[l][c+1]=='O')
					contador++;
					
				if(Vida[l+1][c-1]=='O')
					contador++;
						
				if(Vida[l+1][c]=='O')
					contador++;
					
				if(Vida[l+1][c+1]=='O')
					contador++;
						
				if(contador==2 || contador==3) //Se houverem 2 ou 3 celulas vivas vizinhas, adiciona a celula a lista
					carregaVivoProx(l, c);	
						
				contador=0; //Zera o contador para reiniciar o processo em outra celula	
			} 
	
		else if(P=='1') //Verifica o canto superior esquerdo da matriz
			{
				//Soma a um contador quando acha celula viva
				if(Vida[0][1]=='O')
					contador++;
			
				if(Vida[1][0]=='O')
					contador++;
			
				if(Vida[1][1]=='O')
					contador++;
				
				if(contador==2 || contador==3) //Se houverem 2 ou 3 celulas vivas vizinhas, adiciona a celula a lista
					carregaVivoProx(l, c);
								
				contador=0; //Zera o contador para reiniciar o processo em outra celula	
			}
				
		else if(P=='2') //Verifica o canto superior direito da matriz
			{
				//Soma a um contador quando acha celula viva
				if(Vida[0][tamanho-2]=='O')
					contador++;
			
				if(Vida[1][tamanho-2]=='O')
					contador++;
			
				if(Vida[1][tamanho-1]=='O')
					contador++;
				
				if(contador==2 || contador==3) //Se houverem 2 ou 3 celulas vivas vizinhas, adiciona a celula a lista
					carregaVivoProx(l, c);
							
				contador=0; //Zera o contador para reiniciar o processo em outra celula	
			}
				
		else if(P=='3') //Verifica o canto inferior esquerdo da matriz
			{
				//Soma a um contador quando acha celula viva
				if(Vida[tamanho-2][0]=='O')
					contador++;
			
				if(Vida[tamanho-2][1]=='O')
					contador++;
			
				if(Vida[tamanho-1][1]=='O')
					contador++;
				
				if(contador==2 || contador==3) //Se houverem 2 ou 3 celulas vivas vizinhas, adiciona a celula a lista
					carregaVivoProx(l, c);
							
				contador=0; //Zera o contador para reiniciar o processo em outra celula	
			}
				
		else if(P=='4') //Verifica o canto inferior direito da matriz
			{
				//Soma a um contador quando acha celula viva
				if(Vida[tamanho-2][tamanho-2]=='O')
					contador++;
				
				if(Vida[tamanho-1][tamanho-2]=='O')
					contador++;
			
				if(Vida[tamanho-2][tamanho-1]=='O')
					contador++;
					
				if(contador==2 || contador==3) //Se houverem 2 ou 3 celulas vivas vizinhas, adiciona a celula a lista
					carregaVivoProx(l, c);	

				contador=0; //Zera o contador para reiniciar o processo em outra celula	
		}
		
		aux = aux->next; //caminha para o proximo ponteiro
			
	}while(aux != NULL);
	
	}
}

char ProcuraPosicao(int i, int j) //Captura a posicao da celula nos subsetores da matriz
{
	if(i==0 && (j>0 && j<tamanho-1)) //Primeira linha, excluindo os cantos
		return '-';
	  
	else if(i==tamanho-1 && (j>0 && j<tamanho-1)) //Ultima linha, excluindo os cantos
		return '_';
	
	else if(j==0 && (i>0 && i<tamanho-1)) //Primeira coluna, excluindo os cantos
		return '[';
	
	else if(j==tamanho-1 && (i>0 && i<tamanho-1)) //Ultima coluna, excluindo os cantos
		return ']';
		
	else if(i==0 && j==0) //Canto esquerdo superior
		return '1';
	
	else if(i==tamanho-1 && j==tamanho-1) //Canto direito inferior
		return '4';
	
	else if(i==0 && j==tamanho-1) //Canto direito superior
		return '2';
	
	else if(i==tamanho-1 && j==0) //Canto esquerdo inferior
		return '3';
	
	else //Meio da matriz
		return 'M';
	
}

void carregaVivo(int ii, int jj) //Carrega um vivo na lista simplesmente ligada
{
	TipoCel *aux= (TipoCel*)malloc(sizeof(TipoCel)); //Aloca espaco para uma celula na memoria

	if (aux == NULL)
		{
		apresentaMensagem("Sem espaco na memoria para inclusao de celula viva\n");
		return; 
		}

	//Recolhe as coordenadas da celula
	aux->lin = ii; 
	aux->col = jj;

	if(totvivo == 0) 
		{
		pvivo = aux; //agora a lista contem 1 celula
		pvivo->next = NULL; 
		}

	else //lista nao vazia
		{
		aux->next = pvivo; //a nova celula aponta para a que era a primeira
		pvivo = aux; //o inicio da lista passa a ser a nova celula
		}
		
	totvivo++; //incrementa a quantidade total de celulas vivas
}

void excluiLVivo(int ii, int jj) //Exclui um vivo na lista simplesmente ligada
{
	TipoCel *aux, *aux2; //define 2 ponteiros auxiliares
	aux = pvivo;
	aux2 = aux; //guarda a celula como sendo a anterior

	if(totvivo > 0)
		{
		while(aux->lin != ii || aux->col != jj)
			{
			aux2 = aux;
			aux = aux->next;
			}
			
		if(aux->lin == ii && aux->col == jj)
			{
			if(aux2 == aux) //se é o primeiro da lista
				pvivo = aux->next;
		
			else
				aux2->next = aux->next;
				
			free(aux); //Limpa a celula selecionada da memoria
			}
	
		totvivo--; //diminui a qtd de vivos
		}
}

void carregaMortoVizinho(int ii, int jj) //Carrega um morto vizinho na lista simplesmente ligada
{
	TipoCel *aux =  (TipoCel*)malloc(sizeof(TipoCel)); //aloca espaco para uma celula

	if (aux == NULL)
		{
		apresentaMensagem("Sem espaco na memoria para inclusao de celula morta vizinha\n");
		return; 
		}

	//Recolhe as coordenadas da celula
	aux->lin = ii; 
	aux->col = jj; 

	if(totmorto == 0) 
		{
		pmorto = aux; //agora a lista contem 1 celula
		pmorto->next = NULL; 
		}

	else //lista nao vazia
		{
		aux->next = pmorto; //a nova celula aponta para a que era a primeira
		pmorto = aux; //o inicio da lista passa a ser a nova celula
		}
		
	totmorto++; //incrementa a quantidade total de celulas mortas
}

void carregaVivoProx(int ii, int jj) //Carrega um vivo da proxima geracao
{
	TipoCel *aux =  (TipoCel*)malloc(sizeof(TipoCel)); //aloca espaco para uma celula

	if (aux == NULL)
		{
		apresentaMensagem("Sem espaco na memoria para inclusao de celula viva da proxima geracao\n");
		return; 
		}
	
	//Recolhe as coordenadas da celula
	aux->lin = ii; 
	aux->col = jj;

	if(totvivoprox == 0) 
		{
		pvivoprox = aux; //agora a lista contem 1 celula
		pvivoprox->next = NULL; 
		}

	else //lista nao vazia
		{
		aux->next = pvivoprox; //a nova celula aponta para a que era a primeira
		pvivoprox = aux; //o inicio da lista passa a ser a nova celula
		}
		
	totvivoprox++; //incrementa a quantidade total de celulas vivas da prox geracao
}

void CarregaListaMorto() //Carrega a lista dos mortos atuais com base na matriz original
{
	for(int j = 0; j < tamanho; j++) 
	{
		for (int k = 0; k < tamanho; k++) 
			if(Vida[j][k]=='+') //Onde houver mortos na matriz original adiciona na lista de mortos
				carregaMortoVizinho(j, k); //Carrega uma celula na lista de mortos
	}
}

void CarregaMatriz() //Carrega na matriz as mudancas que ocorreram por meio das listas ligadas
{
	TipoCel *aux; //define um ponteiro auxiliar
	aux = pvivo; //inicializa esse ponteiro auxiliar

	if(totvivo > 0) //Se houverem celulas vivas
		{
	
		while(aux->next != NULL)
			{
			Vida[aux->lin][aux->col]='O'; //Coloca um vivo na posicao conforme oferecida pela lista
			aux = aux->next; //caminha para o próximo ponteiro
			}

		Vida[aux->lin][aux->col]='O'; //Coloca o ultimo vivo na posicao conforme oferecida pela lista
		}
		
}

void LimpaListaVivo() //Limpa a lista dos vivos
{
	TipoCel *aux; //define um ponteiro auxiliar
	TipoCel *reserva; //Define o ponteiro que reserva aux para que esse passe a reservar a proxima posicao
	aux = pvivo; //inicializa esse ponteiro auxiliar

	if(totvivo > 0)
		{
	
			do
			{
			reserva = aux;
			aux = aux->next; //Define aux como a proxima posicao
			free(reserva); //libera memoria da posicao anterior de aux
			}while(aux != NULL);
		
		totvivo=0; //Zera a quantidade de vivos
		}
}

void LimpaListaMorto() //Limpa a lista dos mortos
{
	TipoCel *aux; //define um ponteiro auxiliar
	TipoCel *reserva; //Define o ponteiro que reserva aux para que esse passe a reservar a proxima posicao
	aux = pmorto; //inicializa esse ponteiro auxiliar

	if(totmorto > 0)
		{
			do
			{
			reserva = aux;
			aux = aux->next; //Define aux como o proximo item da lista
			free(reserva); //libera memoria da posicao anterior de aux
			}while(aux != NULL);
			
		totmorto=0; //Zera a quantidade de vivos
		}	
}

void gravaCelulas() //Grava as celulas atuais
{
	int k, i, ni; 
	k = qtconf; //Recebe o numero de config ja realizadas

	if(totvivo == 0) //Se o mapa estiver vazio nao salva
		return;

	//carrega o vetor Lvivo com a lista atual de vivos (somente para gravação)
	TipoCel *aux; 
	aux = pvivo;
	ni = 0; //indice do vetor L da estrutura Lvivo
	
	do
		{
		//Salva as coordenadas das celulas atuais
		Lvivo.L[ni].lin = aux->lin; 
		Lvivo.L[ni].col = aux->col;
		ni++;
		aux = aux->next; //move pra outra celula
		}while (aux != NULL);

	Lvivo.cont = totvivo; //guarda a qtd de vivos atual
	LConfig[k].TL = Lvivo; //copia os salvamentos na posicao k (que anteriormente recebeu a ultima posicao livre de salvamento)
	FILE *fp; 

	if((fp = fopen("CONFIG_INIC", "w")) == NULL)
		{
		apresentaMensagem("ERRO: O arquivo CONFIG_INIC nao pode ser aberto para gravacao");
		return;
		}
		
	for(i = 0; i <= qtconf; i++)
 		{
		if (fwrite(&LConfig[i], sizeof(TipoLista), 1, fp) != 1)
			{
			apresentaMensagem("Erro na gravacao do arquivo CONFIG_INIC");
			fclose(fp);
			return;
			}
		}

	fclose(fp);
	qtconf++; //Depois de salvar e escrever o arquivo com a config da tabela, acrescenta em 1 a quantidade de configs salva
	apresentaMensagem("Configuracao gravada OK");
}

void carregaConfig() //Busca a ultima config salva
{
	int k;
	FILE *fp;

	//Encontra a ultima config salva
	if((fp = fopen("CONFIG_INIC", "r")) != NULL)
		{
		//pesquisa a quantidade de configuracoes cadastradas
		qtconf = 0;
		k = 0;
		while(!feof(fp)) //enquanto nao for fim de arquivo
			{
			if (fread(&LConfig[k], sizeof(TipoLista), 1, fp) != 1)
				{
				fclose(fp);
				return;
				}

			qtconf++; 
			k++;
			}
		fclose(fp);
		}
}

void recuperaCelulas() //Recupera as ultimas celulas salvas
{
	int i, j, k, ni;
	
	//Se nao houver nenhum salvamento
	if (qtconf == 0)
		{
		apresentaMensagem("Nao existe configuracao a recuperar");
		return;
		}
	
	
	k = ultrecup + 1; //indice de LConfig onde estao as celulas a serem recuperadas
	
	//Se so houver uma config salva
	if (k >= qtconf)
		k = 0; //volta ao primeiro conjunto de celulas

	Lvivo = LConfig[k].TL; //obtem a lista das celulas a serem recuperadas
	ultrecup = k;

	//carrega a lista de vivos com as informacoes salvas
	for(ni = 0; ni < Lvivo.cont; ni++)
		carregaVivo(Lvivo.L[ni].lin, Lvivo.L[ni].col);
}

void deletaConfig() //Deleta a configuracao salva
{
	if(remove("CONFIG_INIC") != 0)
		{
		apresentaMensagem("ERRO: O arquivo CONFIG_INIC nao pode ser removido");
		return;
		}

	qtconf = 0;
	apresentaMensagem("O arquivo CONFIG_INIC foi removido OK");
}

void limpaGer() //Limpa todas as config
{
	if(qtconf > 0)
		{	
		if (rconfirma("Confirma exclusao das configuracoes iniciais? (S para confirmar e N para desistir): ") == 0)
			return;
		}

	qtconf = 0; //nenhuma configuracao gravada
	ultrecup = -1; //ultimo �ndice recuperado
	deletaConfig(); //apaga os salvamentos
	apresentaMensagem("O deposito de geracoes iniciais esta vazio");
}

void ftempo(int seg) //Provoca atraso na execucao do codigo em segundos
{
	time_t lt1, lt2;

	lt1 = time(NULL);
	lt2 = lt1;
 	
 	while (difftime(lt2, lt1) < seg)
 		lt2 = time(NULL);
}

void fclear() //Realiza a limpeza de Buffer do teclado
{
	char carac;
	while( ( carac = fgetc(stdin)) != EOF && carac != '\n') {}
}
