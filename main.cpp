#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "estruturas.h"
#include "pre_processador.h"
#include "montador.h"
#include "montador_ligador.h"

int main (int argc, char **argv){
	//printf("Digite o nome do código fonte a ser lido (sem extensao .asm): ");

	std::string file_name = argv[1];
	std::string aux = file_name.substr(file_name.find('.')+1, file_name.size());

	if (aux == "asm"){
		file_name.resize(file_name.find('.'));
		pre_process(file_name);
	}
	else{
		std::cout << "Extensão inválida\n";
	}

	//build(file_name, 2);
}
