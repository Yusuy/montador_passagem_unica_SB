struct code{
	unsigned addr;
  int opcode;
};

int get_value_by_addr(int opcode, std::vector<code> object);

int get_value_by_addr(int opcode, std::vector<code> object){
	for(unsigned i = 0; i<object.size(); i++){
		if(object[i].addr == opcode){
			return object[i].opcode;
		};
	};
}
