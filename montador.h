std::string instrucaoSTOP(std::string &instName, std::stringstream &streamLine, std::string codigoObj, int lineNumber ,std::vector<symbols_Table> symbolTable);
std::string instrucaoCOPY(std::string line,std::string &instName, std::string codigoObj, int lineNumber, std::vector<symbols_Table> symbolTable);
std::string instrucaoUmArgumento(std::string line,std::string &instName, std::string codigoObj, int lineNumber,std::vector<symbols_Table> symbolTable);
std::string arrumaObj(std::string codigoObj, std::vector<symbols_Table>	&symbolTable);
int verificaConst(std::string &label,std::stringstream &streamLine, std::vector<symbols_Table>	&symbolTable, std::string codigoObj, int lineNumber);
int verificaSpace(std::string &label, std::stringstream &streamLine,std::vector<symbols_Table> symbolTable, std::string codigoObj, int lineNumber);
void passagemUnica(std::ifstream &file, std::vector<symbols_Table> &symbolTable, std::string codigoObj);
void fazerMontagem(std::string input_file_name);

std::string instrucaoSTOP(std::string &instName, std::stringstream &streamLine, std::string codigoObj, int lineNumber ,std::vector<symbols_Table> symbolTable){

	if(instName == "STOP"){
		std::string opCode = "14";
		codigoObj = codigoObj + " " + opCode + " ";
	}

	if(instName == "STOP"){

		std::string nextArg;
		streamLine >> nextArg;

		if (!nextArg.empty()){
			std::cout << "Erro sintático: STOP não deve ter um argumento. Linha: " << lineNumber << std::endl;
			return codigoObj;
		}
	}
}

std::string instrucaoCOPY(std::string line,std::string &instName, std::string codigoObj, int lineNumber, std::vector<symbols_Table> symbolTable){

	int i;
	if(instName == "COPY"){
		std::string opCode = "9";
		codigoObj = codigoObj + " " + opCode + " ";
	}



	if(instName == "COPY"){

		std::string lixo;
		std::string nextArg;
		std::stringstream streamLine(line);

		streamLine >> lixo;

		streamLine >> nextArg;

		// Pega o proximo token, que é o token dos argumentos

		//streamLine >> nextArg;

		// Se o token de argumentos estiver vazio, da erro
		if (nextArg.empty()){
			std::cout << "Erro sintático: COPY deve ter 2 argumentos. Linha: " << lineNumber << std::endl;
			return codigoObj ;
		}

		std::string extraArg; //Verificaa se tem outro arguemtno
		streamLine >> extraArg;
		if(extraArg.empty()){
			std::cout << "Erro sintático: COPY deve ter 2 argumentos, separados por virgula e sem espaço. Linha: " << lineNumber << std::endl;
			return codigoObj ;
		}

		// Verifica se tem virgula.
		// std::size_t initialPos = 0;
		// std::size_t commaPos = nextArg.find(',', initialPos);

		// if(!(commaPos != std::string::npos)){
		// 	std::cout << "Erro sintático: COPY deve ter 2 argumentos, separados por virgula e sem espaço. Linha: " << lineNumber << std::endl;
		// 	return;
		// }
		std::size_t commaPos;

		std::string firstArg; //Pega primeiro argumento
		// firstArg = nextArg.substr(0,commaPos);


		firstArg = nextArg;
		if(firstArg.empty()){ //Verifica se tem primeiro argumento
			std::cout << "Erro sintático: COPY deve ter 2 argumentos, separados por virgula e sem espaço. Linha: " << lineNumber << std::endl;
			return codigoObj;
		}

		std::size_t sumPos = nextArg.find('+'); //Verifica se há soma

		if(sumPos != std::string::npos){

			std::string beforeSum; //Salva argumento antes da soma
			beforeSum = firstArg.substr(0,sumPos);

			if(beforeSum.empty()){//Verifica se está vazio
				std::cout << "Erro sintático: COPY  - Primeiro argumento inválido. Linha: " << lineNumber << std::endl;
				return codigoObj;
			}

			// Verifica se o rotulo esta na tabela de simbolos
			int isDEFINED = 0;
			int defSPACE = 0;
			int defAddress = 0;

			for(i=0;i<symbolTable.size();i++){
				if(symbolTable[i].symbolName == beforeSum){
					isDEFINED = 1;
					defSPACE = symbolTable[i].isSPACE; //Verifica se é uma diretiva space
					defAddress = symbolTable[i].symbolAddress; //Endereço do rótulo
				}
			}

			// if(isDEFINED == 0){

			// }

			std::string numericalArg;
			numericalArg = firstArg.substr(sumPos+1); //Armazena valor após sinal de soma

			// Verifica se o numeroVetor eh um numero valido. Tem que ser um numero e nao pode ser negativo
			int value;

			char* c;

			// Converte a string para inteiro
			value = strtol(numericalArg.c_str(), &c, 10);

			if(*c != 0 || (*c == 0 && value < 1)){
				std::cout << "Erro sintático: Indice deve ser um número positivo maior ou igual à 1. Linha: " << lineNumber << std::endl;
				return codigoObj;
			}

			// Verifica se o rotulo que esta sendo usado como vetor foi definido com SPACE
			if(defSPACE == 0 && isDEFINED == 1){
				std::cout << "Erro semântico: Rótulo não é SPACE. Linha: " << lineNumber << std::endl;
				return codigoObj;
			}

			// Verifica se o indice excede o tamanho do vetor
			if(defSPACE < value && defSPACE > 0 && isDEFINED == 1){
				std::cout << "Erro semântico: Vetor excede tamanho permitido. Linha: " << lineNumber << std::endl;
				return codigoObj;
			}

			if(isDEFINED == 1){

				int insereSth = defAddress + value;
  				std::stringstream convert;
  				std::string convertido;

				convert << insereSth;
				convert >> convertido;

				codigoObj = codigoObj + " " + convertido;

			}
			if(isDEFINED == 0){
				std::string separator = ("-");
				std::string builder;

				std::stringstream convert;
				std::string convertido;

				convert << value;
				convert >> convertido;

				builder = separator + beforeSum + "+" + convertido + separator;
				codigoObj = codigoObj + " " + builder;
			}
		}

		else{ //Se nao tiver soma

			// Verifica se o rotulo esta na tabela de simbolos
			int isDEFINED = 0;
			int defSPACE = 0;
			int defAddress = 0;

			for(i=0;i<symbolTable.size();i++){
				if(symbolTable[i].symbolName == firstArg){
					isDEFINED = 1;
					defSPACE = symbolTable[i].isSPACE; //Verifica se é uma diretiva space
					defAddress = symbolTable[i].symbolAddress; //Endereço do rótulo
				}
			}

			if(isDEFINED == 1){

				int insereSth = defAddress;
  				std::stringstream convert;
  				std::string convertido;

				convert << insereSth;
				convert >> convertido;

				codigoObj = codigoObj + " " + convertido;

			}
			if(isDEFINED == 0){
				std::string separator = ("-");
				std::string builder;

				// std::stringstream convert;
				// std::string convertido;

				// convert << value;
				// convert >> convertido;

				builder = separator + firstArg + separator;
				codigoObj = codigoObj + " " + builder;
			}
		}


		std::string secondArg;		//Pega segundo argumento
		secondArg = extraArg;
		// secondArg = nextArg.substr(commaPos+1);

		// Verifica se o segundo argumento do copy esta vazio
		if(secondArg.empty()){
			std::cout << "Erro sintático: COPY  - Segundo argumento inválido. Linha: " << lineNumber << std::endl;
			return codigoObj;
		}

		// // Procura por outra virgula.
		// initialPos = commaPos + 1;
		commaPos = extraArg.find(',');
		if(commaPos != std::string::npos){
			std::cout << "Erro sintático: COPY  - Mais de uma virgula. Linha: " << lineNumber << std::endl;
			return codigoObj;
		}

		std::size_t sumPos2 = secondArg.find('+'); //Verifica se há soma

		if(sumPos2 != std::string::npos){

			std::string beforeSum2; //Salva argumento antes da soma
			beforeSum2 = secondArg.substr(0,sumPos2);

			if(beforeSum2.empty()){//Verifica se está vazio
				std::cout << "Erro sintático: COPY  - Segundo argumento inválido. Linha: " << lineNumber << std::endl;
				return codigoObj;
			}

			// Verifica se o rotulo esta na tabela de simbolos
			int isDEFINED2 = 0;
			int defSPACE2 = 0;
			int defAddress2 = 0;

			for(i=0;i<symbolTable.size();i++){
				if(symbolTable[i].symbolName == beforeSum2){
					isDEFINED2 = 1;
					defSPACE2 = symbolTable[i].isSPACE; //Verifica se é uma diretiva space
					defAddress2 = symbolTable[i].symbolAddress; //Endereço do rótulo
				}
			}

			std::string numericalArg2;
			numericalArg2 = secondArg.substr(sumPos2+1); //Armazena valor após sinal de soma

			// Verifica se o numeroVetor eh um numero valido. Tem que ser um numero e nao pode ser negativo
			int value2;

			char* c2;

			// Converte a string para inteiro
			value2 = strtol(numericalArg2.c_str(), &c2, 10);

			if(*c2 != 0 || (*c2 == 0 && value2 < 1)){
				std::cout << "Erro sintático: COPY - Segundo Argumento - Indice deve ser um número positivo maior ou igual à 1. Linha: " << lineNumber << std::endl;
				return codigoObj;
			}

			// Verifica se o rotulo que esta sendo usado como vetor foi definido com SPACE
			if(defSPACE2 == 0 && isDEFINED2 == 1){
				std::cout << "Erro semântico: COPY - Segundo Argumento - Rótulo não é SPACE. Linha: " << lineNumber << std::endl;
				return codigoObj;
			}

			// Verifica se o indice excede o tamanho do vetor
			if(defSPACE2 < value2 && defSPACE2 > 0 && isDEFINED2 == 1){
				std::cout << "Erro semântico: COPY - Segundo Argumento - Vetor excede tamanho permitido. Linha: " << lineNumber << std::endl;
				return codigoObj;
			}

			if(isDEFINED2 == 1){

				int insereSth2 = defAddress2 + value2;
  				std::stringstream convert2;
  				std::string convertido2;

				convert2 << insereSth2;
				convert2 >> convertido2;

				codigoObj = codigoObj + " " + convertido2;

			}
			if(isDEFINED2 == 0){
				std::string separator2 = ("-");
				std::string builder2;

				std::stringstream convert2;
				std::string convertido2;

				convert2 << value2;
				convert2 >> convertido2;

				builder2 = separator2 + beforeSum2 + "+" + convertido2 + separator2;
				codigoObj = codigoObj + " " + builder2;
			}
		}
		// Se nao tiver sinal de '+', entra nesse ELSE
		else{

			// Verifica se o rotulo esta na tabela de simbolos
			int isDEFINED2 = 0;
			int defSPACE2 = 0;
			int defAddress2 = 0;

			for(i=0;i<symbolTable.size();i++){
				if(symbolTable[i].symbolName == secondArg){
					isDEFINED2 = 1;
					defSPACE2 = symbolTable[i].isSPACE; //Verifica se é uma diretiva space
					defAddress2 = symbolTable[i].symbolAddress; //Endereço do rótulo
				}
			}

			if(isDEFINED2 == 1){

				int insereSth2 = defAddress2;
  				std::stringstream convert2;
  				std::string convertido2;

				convert2 << insereSth2;
				convert2 >> convertido2;

				codigoObj = codigoObj + " " + convertido2;

			}
			if(isDEFINED2 == 0){
				std::string separator2 = ("-");
				std::string builder2;

				// std::stringstream convert2;
				// std::string convertido2;

				// convert2 << value2;
				// convert2 >> convertido2;

				builder2 = separator2 + secondArg + separator2;
				codigoObj = codigoObj + " " + builder2;
			}


		}

	}

	std::cout << "final cpoy : cod: " << codigoObj << std::endl;

}

std::string instrucaoUmArgumento(std::string line,std::string &instName, std::string codigoObj, int lineNumber,std::vector<symbols_Table> symbolTable){


	std::cout << "comeco codigoObj: " << codigoObj << std::endl;

	int i;
	if(instName == "ADD"){
		std::string opCode = "1";
		codigoObj = codigoObj + " " + opCode + " ";
	}

	if(instName == "SUB"){
		std::string opCode = "2";
		codigoObj = codigoObj + " " + opCode + " ";
	}

	if(instName == "MULT"){
		std::string opCode = "3";
		codigoObj = codigoObj + " " + opCode + " ";
	}

	if(instName == "DIV"){
		std::string opCode = "4";
		codigoObj = codigoObj + " " + opCode + " ";
	}

	if(instName == "JMP"){
		std::string opCode = "5";
		codigoObj = codigoObj + " " + opCode + " ";
	}

	if(instName == "JMPN"){
		std::string opCode = "6";
		codigoObj = codigoObj + " " + opCode + " ";
	}

	if(instName == "JMPP"){
		std::string opCode = "7";
		codigoObj = codigoObj + " " + opCode + " ";
	}

	if(instName == "JMPZ"){
		std::string opCode = "8";
		codigoObj = codigoObj + " " + opCode + " ";
	}

	if(instName == "LOAD"){
		std::string opCode = "10";
		codigoObj = codigoObj + " " + opCode + " ";
	}

	if(instName == "STORE"){
		std::string opCode = "11";
		codigoObj = codigoObj + " " + opCode + " ";
	}

	if(instName == "INPUT"){
		std::string opCode = "12";
		codigoObj = codigoObj + " " + opCode + " ";
	}

	if(instName == "OUTPUT"){
		std::string opCode = "13";
		codigoObj = codigoObj + " " + opCode + " ";
	}

	if((instName != "STOP") && (instName != "COPY")){ //Garantir que não é um COPY ou STOP

		std::string lixo;
		std::stringstream streamLine(line);

		streamLine >> lixo;



		std::string nextArg;
		streamLine >> nextArg;

		std::cout << "line: " << line << "nextArg :" << nextArg << std::endl;

		if (nextArg.empty()){ //Verifica se há argumentos para a instrução
			std::cout << "Erro sintático: Instrução " << instName << " deve ter um argumento. Linha: " << lineNumber << std::endl;
			return codigoObj;
		}

		std::string extraArg;
		streamLine >> extraArg;

		if(!extraArg.empty()){ //Verifica se há mais de um argumento
			std::cout << "Erro sintático: Instrução " << instName << " deve ter apenas um argumento. Linha: " << lineNumber << std::endl;
			return codigoObj;
		}

		std::size_t searchComma = nextArg.find(',');

		if(searchComma != std::string::npos){	// Procura por virgula no argumento da instrução
			std::cout << "Erro sintático: Instrução " << instName << " não deve possuir virgulas. Linha: " << lineNumber << std::endl;
			return codigoObj;
		}

		std::size_t searchSum = nextArg.find('+');

		if(searchSum != std::string::npos){ //Procura por sinal de soma no argumento, que representa uma operação com vetor

			// Cria uma string para armazenar o simbolo antes do '+'
			std::string firstPartArg;
			firstPartArg = nextArg.substr(0,searchSum);

			if(firstPartArg.empty()){//Verifica se está faltando argumento antes da soma
				std::cout << "Erro sintático: Não há argumento antes da soma para vetor. Linha: " << lineNumber << std::endl;
				return codigoObj;
			}


			int isDEFINED = 0;
			int defSPACE = 0;
			int defAddress = 0;

			for(i=0;i<symbolTable.size();i++){
				if(symbolTable[i].symbolName == firstPartArg){ //Verifica se primeira parte do argumento é um simbolo salvo na tabela de simbolos
					isDEFINED = 1;
					defSPACE = symbolTable[i].isSPACE; //Verifica se é uma diretiva space
					defAddress = symbolTable[i].symbolAddress; //Endereço do rótulo
				}
			}


			if(isDEFINED == 0){
				// if(instName == "JMP" || instName == "JMPN" || instName == "JMPP" || instName == "JMPZ"){
				// 	std::cout << "Erro semântico: Jump para rótulo indefinido. Linha: " << lineNumber << std::endl;
				// 	return;
				// }
				// else{
				// 	if(firstPartArg.front() <= '9' && firstPartArg.front() >= '0'){
				// 		std::cout << "Erro léxico: Rótulo invalido (iniciado com valor numérico) e indefinido. Linha: " << lineNumber << std::endl;
				// 		return;
				// 	}
				// 	else{
				// 		std::cout << "Erro semântico: Rótulo indefinido. Linha: " << lineNumber << std::endl;
				// 		return;
				// 	}
				// }
			}

			std::string numericalArg;
			numericalArg = nextArg.substr(searchSum+1); //Armazena valor após sinal de soma

			// Verifica se o numeroVetor eh um numero valido. Tem que ser um numero e nao pode ser negativo
			int value;

			char* c;

			// Converte a string para inteiro
			value = strtol(numericalArg.c_str(), &c, 10);

			if(*c != 0 || (*c == 0 && value < 1)){
				std::cout << "Erro sintático: Indice deve ser um número positivo maior ou igual à 1. Linha: " << lineNumber << std::endl;
				return codigoObj;
			}

			// Verifica se o rotulo que esta sendo usado como vetor foi definido com SPACE
			if(defSPACE == 0 && isDEFINED == 1){
				std::cout << "Erro semântico: Rótulo não é SPACE. Linha: " << lineNumber << std::endl;
				return codigoObj;
			}

			// Verifica se o indice excede o tamanho do vetor
			if(defSPACE < value && isDEFINED == 1){
				std::cout << "Erro semântico: Vetor excede tamanho permitido. Linha: " << lineNumber << std::endl;
				return codigoObj;
			}

			// if(instName == "JMP" || instName == "JMPN" || instName == "JMPP" || instName == "JMPZ"){ <<<<<<<<<<<<<<---Verificar isso
			// 	if(defSPACE >= 1){
			// 	std::cout << "Erro semântico: Jump para SECTION DATA. Linha: " << lineNumber << std::endl;
			// 	return;
			// 	}
			// }

			if(isDEFINED == 1){

				int insereSth = defAddress + value;
  				std::stringstream convert;
  				std::string convertido;

				convert << insereSth;
				convert >> convertido;
            	std::cout << "instrucao - com soma - defined: "  << std::endl;


				codigoObj = codigoObj + " " + convertido;

			}
			if(isDEFINED == 0){
				std::string separator = ("-");
				std::string builder;

				std::stringstream convert;
				std::string convertido;

				convert << value;
				convert >> convertido;
				std::cout << "instrucao ccom soma- nao defined: "  << std::endl;

				builder = separator + firstPartArg + "+" + convertido + separator;
				codigoObj = codigoObj + " " + builder;
			}
		}
				// Se nao tiver sinal de soma
		else{

				// Verifica se o rotulo esta na tabela de simbolos
			int isDEFINED = 0;
			int defCONST = 0;
			int defAddress = 0;

			for(i=0;i<symbolTable.size();i++){
				if(symbolTable[i].symbolName == nextArg){ //Verifica se primeira parte do argumento é um simbolo salvo na tabela de simbolos
					isDEFINED = 1;
					defCONST = symbolTable[i].isCONST; //Verifica que tipo de constante é
					defAddress = symbolTable[i].symbolAddress;
				}
			}

			if(isDEFINED == 0){
				// if(instName == "JMP" || instName == "JMPN" || instName == "JMPP" || instName == "JMPZ"){
				// 	std::cout << "Erro semântico: Jump para rótulo indefinido. Linha: " << lineNumber << std::endl;
				// 	return;
				// }
				// else{
				// 	if(nextArg.front() <= '9' && nextArg.front() >= '0'){
				// 		std::cout << "Erro léxico: Rótulo invalido (iniciado com valor numérico) e indefinido. Linha: " << lineNumber << std::endl;
				// 		return;
				// 	}
				// 	else{
				// 		std::cout << "Erro semântico: Rótulo indefinido. Linha: " << lineNumber << std::endl;
				// 		return;
				// 	}
				// }
			}

			if(instName == "DIV"){
				if(defCONST == 2){ //Verifica se a constante é zero
					std::cout << "Erro semântico: Divisao por zero. Linha: " << lineNumber << std::endl;
					return codigoObj;
				}
			}
				// Verifica se eh a instrucao INPUT ou STORE e ve se o rotulo eh um valor constante, se for, da erro
			if(instName == "INPUT" || instName == "STORE"){
				if(defCONST == 1 || defCONST == 2){
					std::cout << "Erro semântico: INPUT ou STORE para de constante. Linha: " << lineNumber << std::endl;
					return codigoObj;
				}
			}
				// Verifica se a instrucao eh um pulo, se for, verifica se esta pulando para um rotulo da SECTION DATA
			if(instName == "JMP" || instName == "JMPN" || instName == "JMPP" || instName == "JMPZ"){
				if(defCONST == 1 || defCONST == 2 || defCONST >= 1){
					std::cout << "Erro semântico: Jump para SECTION inválida. Linha: " << lineNumber << std::endl;
					return codigoObj;
				}
			}

			if(isDEFINED == 1){

				int insereAddr = defAddress;
  				std::stringstream convert;
  				std::string convertido;

				convert << insereAddr;
				convert >> convertido;

				codigoObj = codigoObj + " " + convertido;

			}
			if(isDEFINED == 0){
				std::string separator = ("-");
				std::string builder;
				std::cout << "sem soma - nao defined - codigoObj: " << codigoObj << std::endl;

				builder = separator + nextArg + separator;
				codigoObj = codigoObj + builder;
			}

		}
	}


	std::cout << "fim codigoObj: " << codigoObj << std::endl;
	return codigoObj;

}

std::string arrumaObj(std::string codigoObj, std::vector<symbols_Table>	&symbolTable){


	std::string firstPartCod;
  	std::string secondPartCod;
  	std::string desired;
  	std::string medium;
  	std::size_t secondSeparatorPos;

	for(int i=0;i<=symbolTable.size();i++){

  		std::size_t procuraUndefinedPos = codigoObj.find(symbolTable[i].symbolName);
 		 if(procuraUndefinedPos != std::string::npos){

        // Cria uma string para armazenar o simbolo antes do '+'

    		firstPartCod = codigoObj.substr(0,procuraUndefinedPos-1);

    		medium = codigoObj.substr(procuraUndefinedPos,codigoObj.size());


    		secondSeparatorPos = medium.find('-');

    		desired = codigoObj.substr(procuraUndefinedPos-1,secondSeparatorPos+firstPartCod.size());

			//    std::size_t final_s = s.find(final);

    		secondPartCod = codigoObj.substr(secondSeparatorPos+firstPartCod.size()+2,codigoObj.size());

    		int novo_int = symbolTable[i].symbolAddress;

  			std::stringstream convert;

  			convert<<novo_int;

  			std::string novo_string;

  			convert>>novo_string;

    		codigoObj = firstPartCod + novo_string + secondPartCod;

		}

	}
	std::cout << "---->>>>>>><<<<<<--------cod: " << codigoObj << std::endl;
	return codigoObj;


}

int verificaConst(std::string &label,std::stringstream &streamLine, std::vector<symbols_Table>	&symbolTable, std::string codigoObj, int lineNumber){
	//Verifica se a diretiva de constante é válida e atualiza valor de endereço

	std::string thirdArg;
	int valAuxiliar,i;
	char *c;
	int error;

	error = 0;

	streamLine >> thirdArg;

	if(thirdArg.empty()){
		std::cout << "Erro sintático: Constante sem valor. Linha: " << lineNumber << std::endl;
		return 1;
	}

	// Passa para um vetor de caracteres com '\0' no fim, similar à uma string
	const char *c_thirdArg = thirdArg.c_str();

	// Converte para decimal e altera o *c para o ultimo caractere lido
	valAuxiliar = strtol(c_thirdArg, &c, 10);

	// Se nao foi possivel transformar, significa que nao é um decimal válido. Então, verifica se é um hexadecimal
	if(*c != '\0'){
		// Verifica se é um hexadecimal
		if(thirdArg.substr(0,2) == "0X" || thirdArg.substr(0,3) == "-0X"){
			valAuxiliar = strtol(c_thirdArg, &c, 16);
		}
		else{
			*c = 'n';
		}
	}

	if(*c != '\0'){ //Caso não tenha conseguido transformar o valor corretamente, retorna valor de erro
		std::cout << "Erro léxico: Valor da constante inválido. Linha: " << lineNumber << std::endl;
		return 1;
	}


	std::string fourthArg; //Tenta ler mais um argumento
	streamLine >> fourthArg;

	if(!fourthArg.empty()){ //Não deve haver mais um argumento
		std::cout << "Erro sintático: CONST com mais de um valor. Linha: " << lineNumber << std::endl;
		return 1;
	}


	// Atualiza a informação do rótulo, alterando o valor de isCONST
	for(i=0;i<symbolTable.size();i++){
		if(symbolTable[i].symbolName == label){
			if(valAuxiliar == 0){
				symbolTable[i].isCONST = 2; //Sinalizado como 2 caso seja uma CONST igual a zero
			}
			else{
				symbolTable[i].isCONST = 1; //Sinalizado como 1 caso seja uma CONST diferente de zero
			}
		}
	}

	int insereVal = valAuxiliar;
  	std::stringstream convert;
  	std::string convertido;

	convert << insereVal;
	convert >> convertido;

	codigoObj = codigoObj + " " + convertido;

	return 0;

}

int verificaSpace(std::string &label, std::stringstream &streamLine,std::vector<symbols_Table> symbolTable, std::string codigoObj, int lineNumber){
	//Verifica se a diretiva de space é válida e atualiza valor de endereço

	std::string thirdArg;
	int valAuxiliar,i;
	char *c;
	int error;

	error = 0;

	streamLine >> thirdArg;

	if(thirdArg.empty()){ //Space sem argumento, espaço consumido igual a 1
		valAuxiliar = 1;
	}
	else{
		// Converte a string para inteiro
		valAuxiliar = strtol(thirdArg.c_str(), &c, 10);
		if((*c != 0) || (*c == 0 && valAuxiliar < 1)){
			std::cout << "Erro léxico: Valor do SPACE inválido. Linha: " << lineNumber << std::endl;
			return 1;
		}

		std::string fourthArg; //Verifica se há mais um argumento
		streamLine >> fourthArg;

		if(!fourthArg.empty()){ //Se não for vazio, ocorre erro
			std::cout << "Erro sintático: SPACE com mais de um valor. Linha: " << lineNumber << std::endl;
			return 1;
		}

	}
	// Atualiza a informacao do rotulo, alterando o valor de isSPACE
	for(i=0;i<symbolTable.size();i++){
		if(symbolTable[i].symbolName == label){
			symbolTable[i].isSPACE = valAuxiliar;
		}
	}

	// Adiciona no codigo objeto a quantidade de 00 necessario dado o valor de SPACE
	for(i=0;i<valAuxiliar;i++){

		int insereZero = 0;
  		std::stringstream convert;
  		std::string convertido;

		convert << insereZero;
		convert >> convertido;

		codigoObj = codigoObj + " " + convertido + convertido;


	}
	return 0;

}

void passagemUnica(std::ifstream &file, std::vector<symbols_Table> &symbolTable, std::string codigoObj){

	std::string line, word, label, secondArg;
	int i, j, errorLabel, labelNumber, lineNumber,constant, okLabel, section, lineObjNumber, isInstruction, isDirective;
	symbols_Table Auxiliar;


	section = 0;
	lineNumber = 0;
	labelNumber = 0;
	lineObjNumber = 0;

	while(!file.eof()){

		errorLabel = 0; // Zera variável que indica ocorrência de erro no rótulo
		constant = 0;

		getline(file,line);	//Lê linha do arquivo

		if(line.empty() || line == " "){
			break;
		}

		lineNumber = lineNumber + 1; //Contagem de linha
		okLabel = 0;



		label.clear();
		std::stringstream streamLine(line);

		std::cout << "aline: " << line << std::endl;

		streamLine >> label; 	 //Pega palavra da linha

		if(section == 0){
        	if (label == "SECTION"){
        		streamLine >> secondArg;

        		if(secondArg == "TEXT") {
            		section = 1;
     			}

        		if(secondArg == "DATA") {
            		section = 2;
     			}
     		}
     		else{
    			std::cout << "Erro semântico. SECTION não encontrada. Linha: " << lineNumber << std::endl;
    		}
    	}




		if(label.back() == ':'){	// Verifica se é uma definição de rótulo
			// std::stringstream streamLine(line);
			// streamLine >> word;


			std::cout << "achou rotulo" << std::endl;
			streamLine >> secondArg;

			label.pop_back(); //Retira dois pontos do rótulo

			if(label.empty()){ //Verifica ausência de rótulo (Quando tem apenas ":")
				errorLabel = 1;
				std::cout << "Erro sintático: Rótulo ausente. Linha: " << lineNumber << std::endl;
			}

			else{
				std::cout << "entrou else: não  ta vazio" << std::endl;
				//Verifica se rótulo é igual a nome de instrução
				if(label == "ADD" || label == "SUB" || label == "MULT" || label == "DIV" || label == "JMP" || label == "JMPN" || label == "JMPP" || label == "JMPZ" || label == "COPY" || label == "LOAD" || label == "STORE" || label == "INPUT" || label == "OUTPUT" || label == "STOP"){
					errorLabel = 1;
					std::cout << "Erro semântico: Rótulo com nome de instrução. Linha: " << lineNumber << std::endl;
				}
				else{
					std::cout << "1 if n" << std::endl;
				}

				//Verifica se rótulo é igual a nome de diretiva
				if(label == "CONST" || label == "SPACE" || label == "SECTION" || label == "EQU" || label == "MACRO" || label == "END"){
					errorLabel = 1;
					std::cout << "Erro semântico: Rótulo com nome de diretiva. Linha: " << lineNumber << std::endl;
				}
				else{
					std::cout << "2 if n" << std::endl;
				}
				std::cout << label <<" " << label.length() << std::endl;
				//Verifica se há Token inválido no rótulo
	            for (i = 0; i < label.length(); i++){
	               if((label.at(i) > '9' || label.at(i) < '0') && (label.at(i) != '_') && (label.at(i) > 'Z' || label.at(i) < 'A')){
	                	errorLabel = 1;
	                	std::cout << "Erro léxico: Token inválido. Linha: " << lineNumber << std::endl;
	               }
	               else{
	               	std::cout << "3 if for n" << std::endl;
	               }
	            }
	            std::cout << "4 if " << std::endl;
	            //Verifica se rótulo é iniciado com número
	            if(label.front() <= '9' && label.front() >= '0' ){
	                errorLabel = 1;
	                std::cout << "Erro léxico: Rótulo iniciado com número. Linha: " << lineNumber << std::endl;
	            }

	            std::cout << "4 if n - labelNumber:" << labelNumber << std::endl;
	            //Verifica se há outro rótulo com mesmo nome
	            for (j = 0; j <= labelNumber; ++j){
	                if (label == symbolTable[j].symbolName){
	                    errorLabel = 1;
	                    std::cout << "Erro semântico: Rótulo repetido. Linha: " << lineNumber << std::endl;
	                }
	                else{
	                	std::cout << "5 if for n" << std::endl;
	                }

	            }
	            std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaerrorLabel: " << errorLabel << std::endl;

    	      	if(errorLabel == 0){ // Se não deu nenhum erro até agr
       	   						 //Adiciona simbolo na tabela
       		   		Auxiliar.symbolName = label;
          			Auxiliar.symbolAddress = lineObjNumber;
          			Auxiliar.isCONST = 0;  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<-------------Verificar isso
          			Auxiliar.isSPACE = 0;  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<-------------Verificar isso
          			symbolTable.push_back(Auxiliar);

          			std::stringstream convert;
          			std::string convertido;
          			std::size_t alreadySeem = codigoObj.find(label);
          			std::cout << "alreadySeem" << std::endl;


					if(alreadySeem != std::string::npos){

						std::string traco = ("-");
  						std::string firstPartCod;
  						std::string secondPartCod;
  						std::string desired;
  						std::string medium;
  						std::size_t secondSeparatorPos;

	    				firstPartCod = codigoObj.substr(0,alreadySeem-1);

    					medium = codigoObj.substr(alreadySeem,codigoObj.size());

  						secondSeparatorPos = medium.find('-');

   						desired = codigoObj.substr(alreadySeem-1,secondSeparatorPos+firstPartCod.size());

	    				secondPartCod = codigoObj.substr(secondSeparatorPos+firstPartCod.size()+2,codigoObj.size());

    					std::size_t isSUM = desired.find("+");

						if(isSUM != std::string::npos){
							std::string number;
							number = desired.substr(isSUM+1,desired.size()-1); //Armazena valor após sinal de soma

							std::stringstream stringToInt;
							int numberInt;

							stringToInt << number;
							stringToInt >> numberInt;

							int valor_final_obj = lineObjNumber + numberInt;

  							convert << valor_final_obj;

  							convert >> convertido;

							codigoObj = firstPartCod + convertido + secondPartCod;

						}
						else{

  							convert << lineObjNumber;

  							convert >> convertido;

							codigoObj = firstPartCod + convertido + secondPartCod;
						}


  					}

     	     		labelNumber = labelNumber + 1; //Incrementa numero de Labels adicionados.
     	     		std::cout << "aaaaaaaadhgashdashdgasdasdasgdyashdkasdgyuasdbjkasbdhgyu " << std::endl;
     	     		codigoObj = arrumaObj(codigoObj,symbolTable);

   		       	}

    	        // std::stringstream streamLine(line);
     	       // streamLine >> word;
    	        // streamLine >> directive;


				//Procura a posicao do primeiro ':' que deve existir, pois o primeiro token é um rotulo.
				//Atualiza a posicao inicial de busca e procura por outro ':', se encontrar da erro
				std::size_t initialPos = 0;
				std::size_t colonPos = line.find(':', initialPos);
				if(colonPos != std::string::npos){
					initialPos = colonPos + 1;
					colonPos = line.find(':', initialPos);
					//Se encontrar, significa que tem outro rotulo na linha.
					if(colonPos != std::string::npos){
						std::cout << "Erro sintático. Mais de um rotulo na mesma linha. Linha: " << lineNumber << std::endl;
					}
				}


				//Verifica se segundo argumento é igual a nome de instrução
				if(secondArg == "ADD" || secondArg == "SUB" || secondArg == "MULT" || secondArg == "DIV" || secondArg == "JMP" || secondArg == "JMPN" || secondArg == "JMPP" || secondArg == "JMPZ" || secondArg == "COPY" || secondArg == "LOAD" || secondArg == "STORE" || secondArg == "INPUT" || secondArg == "OUTPUT" || secondArg == "STOP"){
					isInstruction = 1;
				}
				else{
					isInstruction = 0;
				}

				//Verifica se segundo argumento é igual a nome de diretiva
				if(secondArg == "CONST" || secondArg == "SPACE" || secondArg == "EQU" || secondArg == "SECTION" || secondArg == "MACRO" || secondArg == "END" || secondArg == "ENDMACRO"){
					isDirective = 1;
				}
				else{
					isDirective = 0;
				}

				//Se o segundo argumento não for uma instrução ou diretiva, significa que é um comando inválido.
				if((isDirective == 0) && (isInstruction == 0)){
					if(section == 1){
						std::cout << "Erro léxico. Instrução inválida. Linha:  " << lineNumber << std::endl;
					}
					else{
						if(section == 2){
							std::cout << "Erro léxico. Diretiva inválida. Linha:  " << lineNumber << std::endl;
						}
					}
				}

				if((isDirective == 1) && (errorLabel == 0)){ //Se for uma diretiva e não tiver tido algum erro até agora

     		       	if(secondArg == "SECTION"){ 	//Verifica se é uma SECTION
        	    		errorLabel = 1;
						std::cout << "Erro sintático. Rótulo para uma SECTION. Linha:  " << lineNumber << std::endl;
       		     	}



        	    	if(secondArg == "CONST"){ 	//Verifica se é uma CONST
        	   			errorLabel = verificaConst(label, streamLine,symbolTable,codigoObj, lineNumber);
          	 			lineObjNumber = lineObjNumber + 1; //CONST ocupa 1 espaço de memória;
        	   			if(section != 2){
        	   				errorLabel = 1;
        	   				std::cout << "Erro semântico. Diretiva CONST deve estar na SECTION DATA. Linha:  " << lineNumber << std::endl;
        	   				std::cout << "section : " << section << std::endl;
        	   			}
         		   	}

        	   		if(secondArg == "SPACE"){ //Verifica se é um SPACE
       					errorLabel = verificaSpace(label, streamLine,symbolTable,codigoObj, lineNumber);
       	    			lineObjNumber = lineObjNumber + 1; //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<-------------Verificar isso
       	    			if(section != 2){
       	    				errorLabel = 1;
       	    				std::cout << "Erro semântico. Diretiva SPACE deve estar na SECTION DATA. Linha:  " << lineNumber << std::endl;
       	    			}
      	     		}

    				//if(secondArg == "EQU"){ 	//Verifica se é um EQU

					//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<-----Verificar isso
    				//}

        		}

        		if((isInstruction == 1) && (errorLabel == 0)){ //Se for uma instrução e não tiver tido algum erro até agora
       		 		if(secondArg == "COPY"){
        				lineObjNumber = lineObjNumber + 3;
        			}
        			else{
        				if(secondArg == "STOP"){
        					lineObjNumber = lineObjNumber + 1;
        				}
        				else{
        					lineObjNumber = lineObjNumber + 2;
        				}
        			}

        			if(section != 1){
        				std::cout << "Erro semântico. Instruções devem estar no SECTION TEXT. Linha:  " << lineNumber << std::endl;
        			}

    	    	}

			}
		}

		else{	// Caso não, é uma definição de instrução ou diretiva SEM RÓTULO
			streamLine >> secondArg;

			std::size_t initialPos = 0;
			std::size_t colonPos = line.find(':', initialPos);
			if(colonPos != std::string::npos){
				std::cout << "Erro sintático. Definição de rótulo não está no inicio da linha. Linha: " << lineNumber << std::endl;
			}

			//Verifica se segundo argumento é igual a nome de instrução
			if(label == "ADD" || label == "SUB" || label == "MULT" || label == "DIV" || label == "JMP" || label == "JMPN" || label == "JMPP" || label == "JMPZ" || label == "COPY" || label == "LOAD" || label == "STORE" || label == "INPUT" || label == "OUTPUT" || label == "STOP"){
				isInstruction = 1;
			}
			else{
				isInstruction = 0;
			}

			//Verifica se segundo argumento é igual a nome de diretiva
			if(label == "CONST" || label == "SPACE" || label == "SECTION" || label == "EQU" || label == "MACRO" || label == "END"|| label == "ENDMACRO"){
				isDirective = 1;
			}
			else{
				isDirective = 0;
			}


			//Se o primeiro argumento não for uma instrução ou diretiva, significa que é um comando inválido.
			if((isDirective == 0) && (isInstruction == 0)){
				if(section == 1){
					std::cout << "Erro léxico. Instrução inválida. Linha:  " << lineNumber << std::endl;
				}
				else{
					if(section == 2){
						std::cout << "aaaaErro léxico. Diretiva inválida. Linha:  " << lineNumber << std::endl;
					}
				}
			}


			if((isDirective == 1)){
				if(label == "SECTION"){
					if(secondArg == "TEXT"){
						std::string thirdArg;
						streamLine >> thirdArg;
						section = 1;
						if(!thirdArg.empty()){
							std::cout << "Erro sintático. SECTION TEXT não pode ter argumentos. Linha:  " << lineNumber << std::endl;
						}
					}
					if(secondArg == "DATA"){
						section = 2;
						std::string thirdArg;
						streamLine >> thirdArg;
						if(!thirdArg.empty()){
							std::cout << "Erro sintático. SECTION DATA não pode ter argumentos. Linha:  " << lineNumber << std::endl;
						}
					}
					if((secondArg != "TEXT") && (secondArg != "DATA")){
						std::cout << "Erro sintático. SECTION inválida. Linha:  " << lineNumber << std::endl;
					}
				}

				if(label == "CONST"){
					std::cout << "Erro sintático. Diretiva CONST deve ser definida por um rótulo. Linha:  " << lineNumber << std::endl;
					if(section != 2){
						std::cout << "Erro semântico. Diretiva CONST deve estar localizada na SECTION DATA. Linha:  " << lineNumber << std::endl;
					}
				}

				if(label == "SPACE"){
					std::cout << "Erro sintático. Diretiva SPACE deve ser definida por um rótulo. Linha:  " << lineNumber << std::endl;
					if(section != 2){
						std::cout << "Erro semântico. Diretiva SPACE deve estar localizada na SECTION DATA. Linha:  " << lineNumber << std::endl;
					}
				}
			}

			if(isInstruction == 1){

        		if(label == "COPY"){
        			codigoObj = instrucaoCOPY(line,label, codigoObj, lineNumber, symbolTable);
        			lineObjNumber = lineObjNumber + 3;
        		}
        		else{
        			if(label == "STOP"){
        				codigoObj = instrucaoSTOP(label, streamLine, codigoObj, lineNumber, symbolTable);
        				lineObjNumber = lineObjNumber + 1;
        			}
        			else{

            			std::cout << "instrução: 3 if" << std::endl;
            			std::cout << codigoObj.length() << std::endl;
        				codigoObj = instrucaoUmArgumento(line, label, codigoObj, lineNumber, symbolTable);
        				lineObjNumber = lineObjNumber + 2;
        			}
        		}

        		if(section != 1){
        			std::cout << "Erro semântico. Instruções devem estar no SECTION TEXT. Linha:  " << lineNumber << std::endl;
        		}

			}

		}

		if(label == "COPY"){
			std::cout<< "final final copy: codigoObj: " << codigoObj << std::endl;
		}
	}


}

void fazerMontagem(std::string input_file_name){
	std::vector<symbols_Table> symbolTable;

	std::string codigoObj;
	int i;

	symbols_Table Aux;

    Aux.symbolName = "label";
    Aux.symbolAddress = 2;
    Aux.isCONST = 0;  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<-------------Verificar isso
    Aux.isSPACE = 0;  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<-------------Verificar isso
    symbolTable.push_back(Aux);

	symbolTable[0].symbolName = "jim";

	for(i=0;i<symbolTable.size();i++){
		std::cout << "\nRotulo: " << symbolTable[i].symbolName << "; Valor: " << symbolTable[i].symbolAddress << "; Valor da def Const: " << std::endl;
	}

	std::ifstream input_file (input_file_name.append(".pre"));

	passagemUnica(input_file,symbolTable, codigoObj);

	std::cout << "fim : "<< codigoObj << std::endl;

}
