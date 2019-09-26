#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "estruturas.h"
#include "pre_processador.h"

int main (int argc, char **argv){
		std::string file_name;
		//Testes

		//unsigned i;
		//Vetor de Instruções
		/**std::vector<instructions> teste = instructions_vector_build();
		unsigned i;
		for(i=0; i<teste.size();i++)
			std::cout << teste[i].instruction_name << ' ' << teste[i].instruction_opcode << ' ' << teste[i].arg_number << std::endl;**/

		//Vetor de Diretivas
		/**std::vector<directives> teste2 = directives_vector_build();
		for(i=0;i<teste2.size();i++)
			std::cout << teste2[i].directive_name << std::endl;**/

		//Vetor de instruções de código
		/**for(i=0;i<teste.size();i++)
			std::cout << teste[i] << ' ';**/

		printf("Digite o nome do arquivo a ser lido: ");
		std::cin >> file_name;
		std::vector<std::string> teste = file_reader(file_name.append(".asm"));				//Extensão do arquivo a ser lido é adicionado ao nome do arquivo
		printf("\n");
}
