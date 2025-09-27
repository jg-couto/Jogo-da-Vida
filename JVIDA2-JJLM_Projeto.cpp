//JVIDA2-JJLM - Projeto (Main) - Etapa 6
//29/11/2023
//Grupo: JJLM
//Luis Augusto Coelho de Souza
//Joao Guilherme Costa Couto
//Matheus Heimrath Barbosa
//Joao Alfredo

#include "JVIDA2-JJLM_Model.cpp"
#include "JVIDA2-JJLM_Controller.cpp"

main()
{
	TamanhoMatriz(); //Recolhe o tamanho da matriz que o usuario deseja
	CriaMatriz(); //"Cria" a Matriz de acordo com o tamanho que o usuario pediu (Preenche os espaços da matriz a ser utilizada com '.'
	Menu(); //Apresenta o menu principal de jogo
}
