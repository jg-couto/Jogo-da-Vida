//JVIDA2-JJLM - Projeto (Controller) - Etapa 6
//29/11/2023
//Grupo: JJLM
//Luis Augusto Coelho de Souza
//Joao Guilherme Costa Couto
//Matheus Heimrath Barbosa
//Joao Alfredo

void Menu(); //inicia o menu 
void AttMatriz(); //recebe se o usuario deseja inserir ou remover um celula, assim como mudar o espacao de ' '(vazio) para O (ocupado) e vice-versa
void CriaMatriz(); //cria a matriz das celulas
void AttMortos(); //adiciona os mortos ao matriz
void EscondeMorto(); //Apaga todos os mortos da matriz
void ProxGeracao(); //Muda para a proxima geracao
void NextFilho(); //Carrega as celulas que irao nascer na prox geracao na lista 
void NextSobrevive(); //Carrega as celulas que irao sobreviver na prox geracao na lista 
char ProcuraPosicao(int i, int j); //Procura a posicao da celula nos setores da matriz
void carregaVivo(int ii, int jj); //Carrega um vivo na lista simplesmente ligada
void excluiLVivo(int ii, int jj); //Exclui um vivo na lista simplesmente ligada
void carregaMortoVizinho(int ii, int jj); //Carrega um morto vizinho na lista simplesmente ligada
void carregaVivoProx(int ii, int jj); //Carrega um vivo da proxima geracao
void CarregaListaMorto(); //Carrega a lista dos mortos atuais com base na matriz original
void CarregaMatriz(); //Carrega na matriz as mudancas que ocorreram por meio das listas ligadas
void LimpaListaVivo(); //Limpa a lista dos vivos
void LimpaListaMorto(); //Limpa a lista dos mortos
void gravaCelulas(); //Salva as celulas vivas atuais
void carregaConfig(); //Busca a ultima config salva
void recuperaCelulas(); //Carrega a lista de vivos coma ultima config
void deletaConfig(); //Limpa as configuracoes
void limpaGer(); //Limpa as configuracoes
void ftempo(int seg); //Provoca atraso na execucao do codigo em segundos
void fclear(); //Realiza a limpeza de Buffer do teclado
