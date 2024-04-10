#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "./Boseong.h"
#define INPUT_SIZE 4096


int main(int argc, char** argv){
    char input[INPUT_SIZE];
    int type, fd;

    while(1){
        fd = open(argv[1], O_RDONLY);
        read(0,input,INPUT_SIZE);
        
        if(strCmp(input,"PA1EXIT") == 1) break;

        type = whichType(input);
	switch(type){
		case 1:
			case_one(fd,input);
			break;
		case 2:
			case_two(fd,input);
			break;
		case 3:
			case_three(fd,input);
			break;
		case 4:
			case_four(fd,input);
			break;
	}
        write(1,"\n",1);
    }
    close(fd);
}
