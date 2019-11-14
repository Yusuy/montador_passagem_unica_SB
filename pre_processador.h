//Declarações das Funções de pré-processamento
std::vector<std::string> file_reader(std::string input_file_name);
int is_declared_symbol_label(std::vector<symbols> symbols_table, std::string symbols_aux);
std::vector<std::string> directive_placer(std::vector<std::string>);
std::vector<std::string> program_organizer(std::vector<std::string> treated_code);
void program_counter(std::vector<std::string> code);
std::vector<std::string> section_organizer(std::vector<std::string> program);
std::vector<std::string> spacer(std::vector<std::string> organized_program);
void file_generator(std::vector<std::string> code, std::string file_name);
void pre_process(std::string file_name);

//Função que gera um vetor do código ignorando os comentário e passando tudo para caixa alta a partir de um arquivo de entrada
std::vector<std::string> file_reader(std::string input_file_name){

	std::ifstream input_file (input_file_name.append(".asm"));
	std::vector<std::string> word;
	char c;
	std::vector<char> word_c;
	char word_aux[50];
	unsigned i, j, k;

	word.push_back(" \n ");
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
		i = 0;
		j = 0;
		k = 0;

		while((word_c[i] != ' ') && (word_c[i] != '\t') && (word_c[i] != '\n') && (i < word_c.size())){
				word_aux[j] = word_c[i];
				//std::cout << word_c[i] << "\n";
				i++;
				j++;
			};

		word_aux[i] = '\0';
		word.push_back(word_aux);
		//std::cout << word_aux << "\n";

		for(i = i; i < word_c.size(); i++){
			j = 0;
			if((word_c[i] != ' ') && (word_c[i] != '\t') && (word_c[i] != '\n')){
				while((word_c[i] != ' ') && (word_c[i] != '\t') && (word_c[i] != '\n') && (i < word_c.size())){
					word_aux[j] = word_c[i];
					i++;
					j++;
				}
				word.push_back(word_aux);
				//std::cout << word_aux << "\n";
			}

			else if (word_c[i] == '\n'){
				word_aux[j] = '\n';
				word.push_back(word_aux);
			};

			for(j=0;j<sizeof(word_aux);j++){
				word_aux[j] = '\0';
			};
			k++;
		};
	}

		else{
			printf("\nArquivo nao encontrado. Verifique se digitou o nome correto e se o arquivo está no mesmo diretório do programa.\n");
			word.push_back("");
		};

		return word;
}

int is_declared_symbol_label(std::vector<symbols> symbols_table, std::string symbols_aux){
	//std::cout << "Entrei\n";
	int flag = 0;
	for (unsigned i = 0; i < symbols_table.size(); i++) {
		if (symbols_table[i].symbol_label == symbols_aux) {
			flag = 1;
		}
	};

	return flag;
}

//Função que substitui diretivas
std::vector<std::string> directive_placer(std::vector<std::string> code_vector){

	int value;
	int i=0, j, line = 1;
	std::string label;
	std::vector<std::string> output_code;
	int flag=0;

	symbols aux;
	std::vector<symbols> directive_bank;

	while(i < code_vector.size()){
		if((code_vector[i].back() == ':') and (code_vector[i+1] == "EQU")) {
			code_vector[i].resize(code_vector[i].size() -1);
			aux.symbol_label = code_vector[i];
			//std::cout << "Carreguei: " << code_vector[i] << "\n";
			i++;

			aux.symbol_name = code_vector[i];
			i++;

			aux.symbol_address = stoi(code_vector[i]);
			aux.symbol_line = 0;
			aux.symbol_type = "DIRETIVA";

			directive_bank.push_back(aux);
			i+=2;
			line +=1;
		}

		else if (code_vector[i] == "IF"){
			std::string auxi = code_vector[i+1];
			for (j = 0; j < directive_bank.size(); j++){
				if(directive_bank[j].symbol_label == code_vector[i+1]){
					value = directive_bank[j].symbol_address;
					flag = 1;
					line+=1;
				};
			};
			i+=3;
			if(flag == 1){
				if (value == 0){
					while((code_vector[i] != "\n") and (i<code_vector.size())) {
						i++;
					};
					line+=1;
					i++;
				}
				else{
					output_code.push_back(code_vector[i]);
					i++;
				};
				flag = 0;
			}
			else{
				std::cout << "\nERRO SEMANTICO: DIRETIVA " << auxi << " NAO DECLARADA NA LINHA " << line << " DO CODIGO FONTE\n";
				line +=1;
			};
		}

		else if (is_declared_symbol_label(directive_bank, code_vector[i]) == 1) {
			for (j = 0; j < directive_bank.size(); j++){
				if(directive_bank[j].symbol_label == code_vector[i]){
					value = directive_bank[j].symbol_address;
					flag = 1;
				};
			};
			if (flag == 1) {
				output_code.push_back(std::to_string(value));
			}
			else{
				output_code.push_back(code_vector[i]);
				std::cout << "\nERRO SEMANTICO: DIRETIVA " << code_vector[i] << " NAO DECLARADA NA LINHA " << line << " DO CODIGO FONTE\n";
			}
			i++;
		}

		else{
			output_code.push_back(code_vector[i]);
			if (code_vector[i]=="\n"){
				line +=1;
			};
			i++;
		};
	};

	return output_code;
}

//Função para arrumar e organizar linhas
std::vector<std::string> program_organizer(std::vector<std::string> treated_code){

	std::vector<std::string> aux;
	unsigned i = 0;
	while(i < treated_code.size()-1){
		if ((treated_code[i] == "\n") && (treated_code[i+1] == "\n") && (i < treated_code.size())){
			i++;
		}
		else{
			aux.push_back(treated_code[i]);
			i++;
		};
	};
	return aux;
}

//Contador de linhas do código
void program_counter(std::vector<std::string> code){
	unsigned i;
	unsigned j=1;
	for(i=0;i<code.size();i++){
		if(code[i]=="\n"){
			j++;
		};
	};
	printf("\nLinhas: %d\n", j);
}

//Organizador de segmentos
std::vector<std::string> section_organizer(std::vector<std::string> program){

	unsigned flag = 1;
	unsigned another_flag;
	std::vector<std::string> aux;
	unsigned i, j;

	another_flag = 1;
	i=0;
	while (i < program.size()) {
		if ((program[i] == "SECTION") && (program[i+1] == "TEXT") && (i+1 < program.size())) {
			aux.push_back(program[i]);
			aux.push_back(program[i+1]);
			flag = 0;
			i+=2;

			while (i+2 < program.size()) {
				aux.push_back(program[i]);
				i++;
				if ((program[i+1] == "SECTION") && (program[i+2] == "DATA")) {
					another_flag = 0;
					break;
				};
			};
			if (another_flag == 1) {
				aux.push_back(program[i]);
				aux.push_back(program[i+1]);
			};
		};

			i++;
	};

	aux.push_back("\n");
	i=0;
	another_flag = 1;
	while (i < program.size()) {
		if ((program[i] == "SECTION") && (program[i+1] == "DATA") && (i+1 < program.size())) {
			aux.push_back(program[i]);
			aux.push_back(program[i+1]);
			i+=2;

			while (i+2 < program.size()) {
				aux.push_back(program[i]);
				i++;
				if ((program[i+1] == "SECTION") && (program[i+2] == "TEXT")) {
					another_flag = 0;
					break;
				};
			};
			if (another_flag == 1) {
				aux.push_back(program[i]);
				aux.push_back(program[i+1]);
			};
		};

			i++;
	};

	if(flag == 1){
		printf("\nERRO: Não há segmento de texto declarado.\n");
	};

	return aux;
}

//Ultimo tratamento para que o código de pre processamento seja gerado - retira vírgula de COPY e + de SPACE
std::vector<std::string> spacer(std::vector<std::string> organized_program){

	unsigned i;
	std::vector<std::string> aux;
	std::string token;
	std::string token_aux;
	char k_ant;

	for (i = 0; i < organized_program.size(); i++){
		if (organized_program[i] == "COPY"){
			aux.push_back(organized_program[i]);
			i++;
			token = organized_program[i];

			for(char& c : token){
				if (c != ','){
					token_aux += c;
				}
				else{
					aux.push_back(token_aux);
					token_aux = "";
				};
			};

			aux.push_back(token_aux);
		}
		else{
			aux.push_back(organized_program[i]);
		};
	};

	aux.push_back("\n");
	return aux;
}

//Função que salva arquivo pre processado
void file_generator(std::vector<std::string> code, std::string file_name){

	std::ofstream newFile(file_name.append(".pre"));
	unsigned i;

	for(i = 0; i < code.size(); i++) {
    newFile << code[i] << " ";
	};
}

//Função de pre_processamento
void pre_process(std::string file_name){

	std::vector<std::string> file = file_reader(file_name);				//Extensão do arquivo a ser lido é adicionado ao nome do arquivo
	printf("\n");

	std::vector<std::string> file_pre_processed = directive_placer(file);
	std::vector<std::string> file_organized = program_organizer(file_pre_processed);
	std::vector<std::string> program = section_organizer(file_organized);
	std::vector<std::string> spaced_program = spacer(program);
	file_generator(spaced_program, file_name);

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


	//Imprime codigo com tudo corrigido
	/*for(unsigned i=0; i<spaced_program.size();i++)
			std::cout << spaced_program[i] << ' ';*/

	//Contador de linhas
	//program_counter(program);
}
