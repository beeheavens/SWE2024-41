#include <stdio.h> //Must delete
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int strcompare(char* str1, char* str2){ // put into header file after
	char* p1 = str1;
	char* p2 = str2;
	while(*p1 != '\0' || *p2 != '\0'){
		if(*p1 != *p2){
			return 1;
		}
		p1++;
		p2++;
	}
	return 0;
}

int functionHandler(char* str){
	char* p = str;
	while(*p != '\0'){
		if(*p=='\"'){
			printf("function number 3\n");
			return 3;
		}
		if(*p == ' '){
			printf("function number 2\n");
			return 2;
		}
		if(*p == '*'){
			printf("fucntion number 4\n");
			return 4;
		}
		p++;
	}
	printf("function number 1\n");
	return 1;
}


int main(int argc,char* argv[]){
	int fd;
	fd = open(argv[1],O_RDWR,0755);
	char buffer[1];
	char inputs[4096]; //Maximum length of input is 4096
	while(1){
		gets(inputs,4096,stdin); //Use gets function for input. fgets stores \n in the string.
		if(strcompare(inputs,"PA1EXIT")==0){
			return 0; //
		}
		else{
			switch(functionHandler(inputs)){
				case 1:
					//implement function 1
					int index = 1;
					int line = 0;
					while(
				case 2:
					//implement function 2
				case 3:
					//implement function 3
				case 4:
					//implement function 4

			}
		}

	}

		
}

