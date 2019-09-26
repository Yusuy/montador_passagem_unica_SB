	TRIANGULO: EQU 0 ;Teste de coment;
	SECTION TEXT
		INPUT		B
		INPUT		H
		LOAD		B
		MULT		H
		IF TRIANGULO
		DIV		DOIS ;aaaa
		store		R
		OUTPUT	R
		STOP
SECTION DATA ;Teste de comentario
	B:		space
	H:		SPACE
	R:		SPACE
	DOIS:	CONST		2
