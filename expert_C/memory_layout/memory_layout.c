#include <stdio.h>

struct sample_t {
	char first;
	char second;
	char third;
	short fourth;
	short five;
};

void print_size(struct sample_t *var){
	printf("Size: %lu byte\n", sizeof(*var));
}

void print_bytes(struct sample_t *var){
	unsigned char *ptr = (unsigned char *)var;
	for(int i = 0; i < sizeof(*var); i++, ptr++){
		printf("%d ", (unsigned int)*ptr);
	}
	printf("\n");
}

void print_adress(struct sample_t *var){
	unsigned char *ptr = (unsigned char *)var;
	for(int i = 0; i < sizeof(*var); i++, ptr++){
		printf("%p ", ptr);
	}
	printf("\n");
}

int main(int argc, char **argv){
	struct sample_t var;

	var.first = 'A';
	var.second = 'B';
	var.third = 'C';
	var.fourth = 765;
	var.five = 800;

	print_size(&var);
	printf("A B C 765 800\n");
	print_bytes(&var);
	print_adress(&var);
	
	return 0;
}
