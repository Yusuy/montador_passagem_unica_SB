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
	printf("Digite o nome do arquivo a ser lido: ");
	std::cin >> file_name;
	std::vector<std::string> file = file_reader(file_name.append(".asm"));				//Extensão do arquivo a ser lido é adicionado ao nome do arquivo
	printf("\n");

	std::vector<std::string> file_pre_processed = directive_placer(file);

	//Contador de linhas
	program_counter(file_pre_processed);

	//Imprime codigo original
	/*for(unsigned i=0; i<file.size();i++)
		std::cout << file[i] << ' ';*/

	//Imprime codigo com diretivas tratadas
	for(unsigned i=0; i<file_pre_processed.size();i++)
		std::cout << file_pre_processed[i] << ' ';
}
