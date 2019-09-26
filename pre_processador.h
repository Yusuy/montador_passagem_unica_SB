//Declarações das Funções de pré-processamento
std::vector<std::string> file_reader(std::string input_file);
std::vector<std::string> directive_placer(std::vector<std::string> code_vector);

//Função que gera um vetor do código ignorando os comentário e passando tudo para caixa alta a partir de um arquivo de entrada
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
				c = '\n';
				word_c.push_back(c);
			}
			else {
				if(c == '\n'){
					word_c.push_back(' ');
					word_c.push_back('\n');
					word_c.push_back(' ');

				}
				else{
					word_c.push_back(toupper(c));
				};
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
				}

				word.push_back(word_aux);
			}

			else if (word_c[i] == '\n'){
				word_aux[j] = '\n';
				word.push_back(word_aux);
			};

			//Zerando vetor de símbolo
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

//Função que substitui diretivas
std::vector<std::string> directive_placer(std::vector<std::string> code_vector){

	int value;
	int i, j;
	std::string label;
	std::vector<std::string> output_code;

	symbols aux;
	std::vector<symbols> directive_bank;
	std::vector<directives> directives_list = directives_vector_build();

	for(i = 0; i < code_vector.size(); i++){
		if((code_vector[i].back() == ':') and (code_vector[i+1] == "EQU") and (i < code_vector.size()-2)) {
			code_vector[i].resize(code_vector[i].size() -1);
			aux.symbol_label = code_vector[i];
			i++;
			aux.symbol_name = code_vector[i];
			i++;
			aux.symbol_address = stoi(code_vector[i]);
			directive_bank.push_back(aux);
			i++;
			output_code.push_back(code_vector[i]);
		}

		else if (code_vector[i] == "IF"){
			for (j = 0; j < directive_bank.size(); j++){
				if((directive_bank[j].symbol_label == code_vector[i+1]) and (i < code_vector.size()-2)){
					value = directive_bank[j].symbol_address;
				};
			};

			i++;
			i++;
			i++;
			if (value == 0){
				while( (code_vector[i] != "\n") and (i<code_vector.size()-2) ) {
					i++;
				};
			};
			output_code.push_back(code_vector[i]);
		}

		else{
			output_code.push_back(code_vector[i]);
		};
	};

	return output_code;
}

std::string pre_process(){

	std::string file_name;
	printf("Digite o nome do arquivo a ser lido: ");
	std::cin >> file_name;
	std::vector<std::string> file = file_reader(file_name.append(".asm"));				//Extensão do arquivo a ser lido é adicionado ao nome do arquivo
	printf("\n");

	std::vector<std::string> file_pre_processed = directive_placer(file);

	for(unsigned i; i<file_pre_processed.size();i++)
		std::cout << file_pre_processed[i] << ' ';

}
