struct labels;
struct instructions;
struct directives;

//Estrutura que armazena dados dos rótulos
struct labels {
	std::string label_name;				//Nome do rótulo
	int label_address;					//Endereço do rótulo
	int is_directive;					//1 se o rótulo for diretiva, 0 se não for
	std::string directive;				//Informações da diretiva se "is_directive = 1"
};

//Estrutura que armazena dados de instrução
struct instructions {
	std::string instruction_name;		//Nome da instrução
	int instruction_opcode;				//Opcode da instrução
	int arg_number;						//Número de argumentos da instrução
};

//Estrutura que armazena dados das diretivas
struct directives{
	std::string directive_name;			//Nome da diretiva
	int directive_section;				//0 para TEXT, 1 para DATA
	int directive_value;				//Valor da diretiva - para const
};

//Estrutura que armazena símbolos e dados relevantes
struct symbols{
	std::string symbol_name;			//Nome do símbolo
	std::string symbol_label;		//Rótulo do símbolo, se hover						
	int symbol_address;					//Endereço do símbolo
	int symbol_line;						//Linha do símbolo
	std::string symbol_type;		//Tipo de símbolo
};


//Vetor de Instruções
std::vector<instructions> instructions_vector_build(){
	unsigned i;

	std::string instructions_name[] = {"ADD", "SUB", "MULT", "DIV", "JMP", "JMPN", "JMPP", "JMPZ", "COPY", "LOAD", "STORE", "INPUT", "OUTPUT", "STOP"};
	int instructions_opcode[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	int instructions_args_number[] = {1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 0};

	std::vector<instructions> instructions_vector;
	instructions temp;
	for(i = 0; i < 14; i++){
		temp.instruction_name = instructions_name[i];
		temp.instruction_opcode = instructions_opcode[i];
		temp.arg_number = instructions_args_number[i];
		instructions_vector.push_back(temp);
	};

	return instructions_vector;
}

//Vetor de Diretivas
std::vector<directives> directives_vector_build(){
	unsigned i;

	std::string directive_names[] = {"SECTION", "SPACE", "CONST", "EQU", "IF"};

	std::vector<directives> directives_vector;
	directives temp;
	for(i = 0; i < 5; i++){
			temp.directive_name = directive_names[i];
			directives_vector.push_back(temp);
	};

	return directives_vector;
}
