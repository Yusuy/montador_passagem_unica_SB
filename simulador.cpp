#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "simulador_aux.h"

int main (int argc, char **argv){
  std::string file_name;
	printf("Digite o nome do arquivo objeto a ser lido (sem extensao .obj): ");
	std::cin >> file_name;
  std::ifstream input_file (file_name.append(".obj"));
  std::string aux;
  std::vector<code> object;
  unsigned i = 0, flag = 0;
  int acc = 0, value;
  code aux_code;
  char c;

  if(input_file.is_open()){
    flag = 1;
    while (input_file>>aux) {
      aux_code.opcode = stoi(aux);
      aux_code.addr = i;
      i++;
      object.push_back(aux_code);
    };
  }
  else{
    printf("\nArquivo nao encontrado.\n");
  };

  if (flag == 1) {
    for(i=0;i<object.size();i++){
      switch (object[i].opcode) {
        case 1:
          value = get_value_by_addr(object[i+1].opcode, object);
          acc = acc + value;
          printf("end. %u - ADD %d (end.%d) | ACC = %d\n", object[i].addr, value, object[i+1].opcode, acc);
          i++;
          //std::cin >> c;
          break;
        case 2:
          value = get_value_by_addr(object[i+1].opcode, object);
          acc = acc - value;
          printf("end. %u - SUB %d (end.%d) | ACC = %d\n", object[i].addr, value,object[i+1].opcode,acc);
          i++;
          //std::cin >> c;
          break;
        case 3:
          value = get_value_by_addr(object[i+1].opcode, object);
          acc = acc * value;
          printf("end. %u - MULT %d (end.%d) | ACC = %d\n", object[i].addr, value, object[i+1].opcode,acc);
          i++;
          //std::cin >> c;
          break;
        case 4:
          value = get_value_by_addr(object[i+1].opcode, object);
          acc = acc / value;
          printf("end. %u - DIV %d (end.%d) | ACC = %d\n", object[i].addr, value, object[i+1].opcode,acc);
          i++;
          //std::cin >> c;
          break;
        case 5:
          printf("end. %u - JMP end.%d | ACC = %d\n", object[i].addr, object[i+1].opcode, acc);
          i = object[i+1].opcode - 3;
          i++;
          //std::cin >> c;
          break;
        case 6:
          printf("end. %u - JMPN end.%d | ACC = %d\n", object[i].addr, object[i+1].opcode, acc);
          if (acc < 0) {
            i = object[i+1].opcode - 3;
          };
          i++;
          //std::cin >> c;
          break;
        case 7:
          printf("end. %u - JMPP end.%d | ACC = %d\n", object[i].addr, object[i+1].opcode, acc);
          if (acc > 0) {
            i = object[i+1].opcode - 3;
          };
          i++;
          //std::cin >> c;
          break;
        case 8:
          printf("end. %u - JMPZ end.%d | ACC = %d\n", object[i].addr, object[i+1].opcode, acc);
          if (acc == 0) {
            i = object[i+1].opcode - 3;
          };
          i++;
          //std::cin >> c;
          break;
        case 9:
          value = get_value_by_addr(object[i+1].opcode, object);
          object[object[i+2].opcode].opcode = value;
          printf("end. %u - COPY %d(end.%d), end.%d | ACC = %d\n", object[i].addr, value, object[i+1].opcode, object[i+2].opcode, acc);
          i++;
          i++;
          //std::cin >> c;
          break;
        case 10:
          acc = get_value_by_addr(object[i+1].opcode, object);;
          printf("end. %u - LOAD %d (end.%d)| ACC = %d\n", object[i].addr, acc, object[i+1].opcode, acc);
          i++;
          //std::cin >> c;
          break;
        case 11:
          object[object[i+1].opcode].opcode = acc;
          printf("end. %u - STORE %d (end.%d)| ACC = %d\n", object[i].addr, acc, object[i+1].opcode, acc);
          i++;
          //std::cin >> c;
          break;
        case 12:
          printf("Digite o valor de entrada: ");
          std::cin >> value;
          object[object[i+1].opcode].opcode = value;
          printf("\nend. %u - INPUT %d (end.%d) | ACC = %d\n", object[i].addr, value, object[i+1].opcode, acc);
          i++;
          break;
        case 13:
          value = get_value_by_addr(object[i+1].opcode, object);
          printf("end. %u - OUTPUT %d (end.%d) | ACC = %d\n", object[i].addr, value, object[i+1].opcode, acc);
          i++;
          //std::cin >> c;
          break;
        case 14:
            printf("end. %u - STOP\n", object[i].addr);
            i++;
            //std::cin >> c;
            while(i<object.size()){
              printf("end. %u - %d\n", object[i].addr, object[i].opcode);
              //std::cin >> c;
              i++;
            };
            return 0;
      };
    };
  };
}
