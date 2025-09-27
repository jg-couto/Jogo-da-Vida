//JVIDA2-JJLM - Projeto (Model) - Etapa 6
//29/11/2023
//Grupo: JJLM
//Luis Augusto Coelho de Souza
//Joao Guilherme Costa Couto
//Matheus Heimrath Barbosa
//Joao Alfredo

char Vida[60][60]; //Matriz de celulas com tamanho fixo em 60x60
int tamanho; //Tamanho da matriz que será utilizada dentro do jogo que sera determinado posteriormente pelo usuario
int MostraMorto; //Salva a opcao do operador se devem ou nao aparecer os mortos
int totvivo, totmorto, totvivoprox; //Define as variaveis globais que irao armazenar a quantidade de mortos, vivos e vivos da proxima geracao
int qtconf; //quantidade de configurações iniciais cadastradas
int ultrecup = -1; //Guarda a ultima recuperacao
