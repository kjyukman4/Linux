int* get_integer(){
	int var = 10;
	return &var;
}

int main(int argc, char** argv){
	int* ptr = get_integer();
	*ptr = 5;

	return 0;
}
