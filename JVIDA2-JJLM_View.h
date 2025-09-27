//JVIDA2-JJLM - Projeto (View) - Etapa 6
//29/11/2023
//Grupo: JJLM
//Luis Augusto Coelho de Souza
//Joao Guilherme Costa Couto
//Matheus Heimrath Barbosa
//Joao Alfredo

void apresentaMensagem(char msg[100]); //mostra uma mensagem 
int rconfirma(char msg[100]); //Apresenta uma mensagem que tera resposta S ou N retornando 1 ou 0
int Txtmenuprin(); //mostra as opcoes do menu principal ao usuario
void ApresentaMatriz(); //apresenta a matriz ao usuario
void TamanhoMatriz(); //define o tamanho da matriz de acordo com a resposta do usuario
char Remove(); //Se a celula selecionada estiver ocupada, pergunta ao usuario se ele quer remove-la
int InsereRemoveLinha(); //Coleta a linha da celula a ser removida ou adicionada
int InsereRemoveColuna(); //Coleta a coluna da celula a ser removida ou adicionada
int TxtQtdGeracao(); //Coleta quantas geracoes serao avancadas
int delay(); //Coleta quanto tempo em segundos o usuario deseja de atraso entre geracoes
void GeracaoAtual(int n); //Apresenta a mensagem de texto que indica qual a geracao atual
void regras(); //mostra as regras de evolucao
void mostraLvivo(); //Mostra as coordenadas dos vivos 
void mostraLmorto(); //Mostra as coordenadas dos mortos


