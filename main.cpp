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
	std::vector<std::string> file_organized = program_organizer(file_pre_processed);
	std::vector<std::string> program = section_organizer(file_organized);
	std::vector<std::string> spaced_program = spacer(program);

	//Imprime codigo original
	/*for(unsigned i=0; i<file.size();i++)
		std::cout << file[i] << ' ';*/

	//Imprime codigo com diretivas tratadas
	/*for(unsigned i=0; i<file_pre_processed.size();i++)
		std::cout << file_pre_processed[i] << ' ';*/

	//Imprime codigo com quebras de linha corrigidas
	/*for(unsigned i=0; i<file_organized.size();i++)
		std::cout << file_organized[i] << ' ';*/

	//Imprime codigo com quebras de linha corrigidas
	/*for(unsigned i=0; i<program.size();i++)
		std::cout << program[i] << ' ';*/

	//Imprime codigo com quebras de linha corrigidas
	for(unsigned i=0; i<spaced_program.size();i++)
		std::cout << spaced_program[i] << ' ';

	program_counter(program);
}
