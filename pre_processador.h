//Declarações das Funções de pré-processamento
std::vector<std::string> file_reader(std::string input_file);
std::vector<std::string> directive_placer(std::string code_vector);


std::vector<std::string> file_reader(std::string input_file_name){

		std::ifstream input_file (input_file_name);
		std::vector<std::string> word;
		char c;
		std::vector<char> word_c;
		char word_aux[50];
		unsigned i, j, k;

		//Rotina para salvar o código em um vetor de caracteres ignorando os comentátios
		if(input_file.is_open()){
			while (input_file.get(c)){
				if (c == ';'){
					while(c != '\n'){
						input_file.get(c);
					};
					word_c.push_back(c);
				}
				else {
					word_c.push_back(c);
				};
			};

		//Rotina para salvar o código em um vetor de strings ignorando espaços e quebras de linha
			k = 0;
			for(i = 0; i < word_c.size(); i++){
				j = 0;
				if((isalnum(word_c[i])) or (word_c[i] == ':')){
					while(((isalnum(word_c[i]))  or (word_c[i] == ':')) and (i < word_c.size())){
						word_aux[j] = word_c[i];
						i++;
						j++;
					};
					word.push_back(word_aux);
				};

				for(j=0;j<sizeof(word_aux);j++){
					word_aux[j] = '\0';
				};
				k++;
			};
		}
		else{
			printf("Falha ao abrir arquivo. Verifique se digitou o nome correto e se o arquivo está no mesmo diretório do programa.");
		}

		return word;
}
