

int verificaConst(std::string &label,std::stringstream &streamLine, std::vector<symbols_Table>	&symbolTable, std::vector<int> codigoObj){
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
				tabelaSimbolo[i].isCONST = 1; //Sinalizado como 1 caso seja uma CONST diferente de zero
			}
		}
	}

	codigoObj.push_back(valAuxiliar);
	return 0;

}

int verificaSpace(std::string &label, std::stringstream &streamLine,std::vector<symbols_Table> symbolTable, std::vector<int> codigoObj){
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
		streamLinha >> fourthArg;

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
		codigoObj.push_back('00');
	}
	return 0;

}


void passagemUnica(std::ifstream &file, std::vector<symbols_Table> &symbolTable){
	
	std::string line, word, label, secondArg;
	int i, j, errorLabel, labelNumber, lineNumber,constant, okLabel, section, lineObjNumber;
	symbols_Table Auxiliar;

	std::vector<int> codigoObj;

	lineNumber = 0;
	labelNumber = 0;
	lineObjNumber = 0;

	while(!file.eof()){

		errorLabel = 0; // Zera variável que indica ocorrência de erro no rótulo
		constant = 0;

		getline(file,line);	//Lê linha do arquivo



		if(line.empty()){
			break;
		}

		lineNumber = lineNumber + 1; //Contagem de linha
		okLabel = 0;



		label.clear();
		std::stringstream streamLine(line);

		streamLine >> label; 	 //Pega palavra da linha

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

		if(label.back() == ':'){	// Verifica se é uma definição de rótulo
			// std::stringstream streamLine(line);
			// streamLine >> word;
			streamLine >> secondArg;

			label.pop_back(); //Retira dois pontos do rótulo

			if(label.empty()){ //Verifica ausência de rótulo (Quando tem apenas ":")
				errorLabel = 1;
				std::cout << "Erro sintático: Rótulo ausente. Linha: " << lineNumber << std::endl;
			}

			else{

			//Verifica se rótulo é igual a nome de instrução
			if(label == "ADD" || label == "SUB" || label == "MULT" || label == "DIV" || label == "JMP" || label == "JMPN" || label == "JMPP" || label == "JMPZ" || label == "COPY" || label == "LOAD" || label == "STORE" || label == "INPUT" || label == "OUTPUT" || label == "STOP"){
				errorLabel = 1;
				std::cout << "Erro semântico: Rótulo com nome de instrução. Linha: " << lineNumber << std::endl;	
			}

			//Verifica se rótulo é igual a nome de diretiva
			if(label == "CONST" || label == "SPACE" || label == "SECTION" || label == "EQU" || label == "MACRO" || label == "END"){
				errorLabel = 1;
				std::cout << "Erro semântico: Rótulo com nome de diretiva. Linha: " << lineNumber << std::endl;
			}

			//Verifica se há Token inválido no rótulo
            for (i = 0; i < label.length(); i++){
               if((label.at(i) > '9' || label.at(i) < '0') && (label.at(i) != '_') && (label.at(i) > 'Z' || label.at(i) < 'A')){
                	errorLabel = 1;
                	std::cout << "Erro léxico: Token inválido. Linha: " << lineNumber << std::endl;
               }
            }

            //Verifica se rótulo é iniciado com número
            if(label.front() <= '9' && label.front() >= '0' ){
                errorLabel = 1;
                std::cout << "Erro léxico: Rótulo iniciado com número. Linha: " << lineNumber << std::endl;
            }

            //Verifica se há outro rótulo com mesmo nome
            for (j = 0; j <= labelNumber; ++j){
                if (label == symbolTable[j].symbolName){
                    errorLabel = 1;
                    std::cout << "Erro semântico: Rótulo repetido. Linha: " << lineNumber << std::endl;
                }
            }

          	if(errorLabel == 0){ // Se não deu nenhum erro até agr
          						 //Adiciona simbolo na tabela
          		Auxiliar.symbolName = label;
          		Auxiliar.symbolAddress = lineObjNumber;
          		Auxiliar.isCONST = 0;  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<-------------Verificar isso
          		Auxiliar.isSPACE = 0;  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<-------------Verificar isso
          		symbolTable.push_back(Auxiliar);

          		labelNumber = labelNumber + 1; //Incrementa numero de Labels adicionados.

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
					std::cout << "Erro sintático. Mais de um rotulo na mesma linha. Linha: " << lineNumber << stf::endl;
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
           			errorLabel = verificaConst(label, streamLine,symbolTable,codigoObj);
           			lineObjNumber = lineObjNumber + 1; //CONST ocupa 1 espaço de memória;
           			if(section != 2){
           				errorLabel = 1;
           				std::cout << "Erro semântico. Diretiva CONST deve estar na SECTION DATA. Linha:  " << lineNumber << std::endl;
           			}
            	}

           		if(secondArg == "SPACE"){ //Verifica se é um SPACE
       				errorLabel = verificaSpace(label, streamLine,symbolTable,codigoObj);
           			lineObjNumber = lineObjNumber + 1; //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<-------------Verificar isso
           			if(section != 2){
           				errorLabel = 1;
           				std::cout << "Erro semântico. Diretiva SPACE deve estar na SECTION DATA. Linha:  " << lineNumber << std::endl;
           			}       				
           		}

    //         	if(secondArg == "EQU"){ 	//Verifica se é um EQU

				// //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<-----Verificar isso
    //         	}

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
		else{	// Caso não, é uma definição de instrução ou diretiva
			streamLine >> secondArg;

			std::size_t initialPos = 0;
			std::size_t colonPos = line.find(':', initialPos);
			if(colonPos != std::string::npos){
				std::cout << "Erro sintático. Definição de rótulo não está no inicio da linha. Linha: " << lineNumber << stf::endl;				
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
						std::cout << "Erro léxico. Diretiva inválida. Linha:  " << lineNumber << std::endl;
					}
				}
			}


			if((isDirective == 1)){
				if(label == "SECTION"){
					if(secondArg == "TEXT"){
						std::string thirdArg;
						streamLine >> thirdArg;
						if(!thirdArg.empty()){
							std::cout << "Erro sintático. SECTION TEXT não pode ter argumentos. Linha:  " << lineNumber << std::endl;
						}
					}
					if(secondArg == "DATA"){
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
        			lineObjNumber = lineObjNumber + 3;
        		}
        		else{
        			if(label == "STOP"){
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
}

void fazerMontagem(std::ifstream &inputFile, std::ofstream &outputFile ){
	std::vector<symbols_Table> symbolTable;

	passagemUnica(inputFile,symbolTable);

}
