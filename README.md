Montador de Passagem Única
CiC - Software Básico

Guilherme ...
Victor Gabriel Rodrigues de Almeida 14/0052399

MONTADOR
Na mesma pasta encontram-se todos os códigos do trabalho
O arquivo main.cpp deve ser compilado e executado a fim de que o montador seja utilizado.
Para que a montagem seja feita, a seguinte linha de comando deve ser inserida no g++ aopós o acesso à pasta:

  g++ main.cpp -o main

E para execução do código:

  ./main

Quando executado, o programa pedirá o nome do arquivo .asm a ser montado (não é necessário digitar a extensão .asm no nome)
Uma vez digitado corretamente o nome do arquivo, os arquivos .pre e .obj serão gerados na mesma pasta para consulta.

SIMULADOR
Nessa mesma pasta, encontra-se o arquivo "simulador.cpp". Para compilá-lo é necessário digitar a seguinte linha de comando deve ser inserida no g++ aopós o acesso à pasta:

  g++ simulador.cpp -o simulador

E para execução do código:

  ./simulador

Quando executado, o programa pedirá o nome do arquivo .obj a ser simulado. Não é necessário digitar o nome com a extensão .obj

OBSERVAÇÕES

Foi utilizada a seguinte versão do g++ nos testes:

g++ (Debian 6.3.0-18+deb9u1) 6.3.0 20170516
Copyright (C) 2016 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
