#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "estruturas.h"
#include "pre_processador.h"
#include "montador.h"

int main (int argc, char **argv){
	std::string file_name;
	printf("Digite o nome do código fonte a ser lido (sem extensao .asm): ");
	std::cin >> file_name;
	pre_process(file_name);
	//fazerMontagem(file_name);
}
