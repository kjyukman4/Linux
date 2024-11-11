#include "myStack.h"
#include "myQueue.h"
#include "mydQueue.h"
#include <getopt.h>
#include <string.h>

SQD* Top,* Front,* Rear,* dFront,* dRear;

void usage (char* cmd){
	fprintf(stderr, "usage: \n");
	fprintf(stderr, "   %s -s        : show stack\n", cmd);
	fprintf(stderr, "   %s -q        : show queue\n", cmd);
	fprintf(stderr, "   %s -d        : show dqueue\n", cmd);
}

int main(int argc, char* argv[]){
	Top=create_S();
	Front = create_Q();
	Rear = create_Q();
	dFront = create_D();
	dRear = create_D();
	int opt, option_index=0;
	
	struct option long_options[] = {
	{"stack",0,NULL,'s'},
	{"queue",0,NULL,'q'},
	{"dqueue",0,NULL,'d'},
	{0,0,0,0}
	};
	printf("%d ",strlen(argv[1])); 
	
	while((opt = getopt_long (argc, argv, "sqd", long_options, &option_index)) != -1){
		switch(opt){
			case 's':
				push(1);
				push(2);
				push(3);
				printf("%d ",pop());
				printf("%d ",pop());
				printf("%d ",pop());
				break;
			case 'q':
				enque(1);
				enque(2);
				enque(3);
				printf("%d ",deque());
				printf("%d ",deque());
				printf("%d ",deque());
				break;
			case 'd':
				enque_D(1,1);
				enque_D(2,1);
				enque_D(3,1);
			
				printf("%d ",deque_D(1));
				printf("%d ",deque_D(1));
				printf("%d ",deque_D(1));

				enque_D(1,2);
				enque_D(2,2);
				enque_D(3,2);

				printf("%d ",deque_D(2));
				printf("%d ",deque_D(2));
				printf("%d ",deque_D(2));
		
				enque_D(1,1);
				enque_D(2,1);
				enque_D(3,1);
				
				printf("%d ",deque_D(2));
				printf("%d ",deque_D(2));
				printf("%d ",deque_D(2));

				enque_D(1,2);
				enque_D(2,2);
				enque_D(3,2);

				printf("%d ",deque_D(1));
				printf("%d ",deque_D(1));
				printf("%d ",deque_D(1));
				break;
			default:
				usage(argv[0]);
				return EXIT_FAILURE;

		}
	}
	return EXIT_SUCCESS;
}	
