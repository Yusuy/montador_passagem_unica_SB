//Declarações das Funções de pré-processamento
std::vector<std::string> file_reader(std::string input_file_name);
std::vector<std::string> directive_placer(std::vector<std::string>);
void program_counter(std::vector<std::string> treated_code);

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
std::cout << c;
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
	int i=0, j;
	std::string label;
	std::vector<std::string> output_code;

	symbols aux;
	std::vector<symbols> directive_bank;

	while(i < code_vector.size()){
		if((code_vector[i].back() == ':') and (code_vector[i+1] == "EQU")) {
			code_vector[i].resize(code_vector[i].size() -1);
			aux.symbol_label = code_vector[i];
			i++;

			aux.symbol_name = code_vector[i];
			i++;

			aux.symbol_address = stoi(code_vector[i]);
			aux.symbol_line = 0;
			aux.symbol_type = "DIRETIVA";

			directive_bank.push_back(aux);
			i+=2;
		}

		else if (code_vector[i] == "IF"){
			for (j = 0; j < directive_bank.size(); j++){
				if(directive_bank[j].symbol_label == code_vector[i+1]){
					value = directive_bank[j].symbol_address;
				};
			};
			i+=3;
			if (value == 0){
				while((code_vector[i] != "\n") and (i<code_vector.size())) {
					i++;
				};
				i++;
			}
			else{
				output_code.push_back(code_vector[i]);
				i++;
			};
		}

		else{
			output_code.push_back(code_vector[i]);
			i++;
		};
	};

	return output_code;
}

//Função para contar quantidade de linhas
void program_counter(std::vector<std::string> treated_code){

	std::vector<std::string> aux;
	unsigned i = 0;
	unsigned j = 0;
	while(i <treated_code.size()-1){
		if (treated_code[i] == "\n") {
			j++;
		};
		aux.push_back(treated_code[i]);
		i++;
	};
	printf("\nLinhas: %d\n", j);
}
