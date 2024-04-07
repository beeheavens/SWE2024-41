#include <stdio.h> //Must delete
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int strCompare(char* str1, char* str2){ // put into header file after
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

int functionHandler(char* str){ // Choose the function according to the input string
	char* p = str;
	while(*p != '\0'){
		if(*p=='\"'){
			return 3;
		}
		if(*p == ' '){
			return 2;
		}
		if(*p == '*'){
			return 4;
		}
		p++;
	}
	return 1;
}

int bufferCompare(int fd, char* str){ //Compare strings if the first letters are same.
	char *p = str;
	char buffer[1];
	p++;
	while(*p != '\0'){
		if(read(fd,buffer,1)>0){
			if(buffer[0] != *p){
				return 0;
			}
		
		}
		p++;
	}
	if(read(fd,buffer,1)>0){
		if(buffer[0] == ' ' || buffer[0] == '\n'){
			return 1;
		}
		else{
			return 0;
		}
	}
	return 1;
}

int checkLength(char *str){
	int len = 0;
	while((str[len] != '\n' && str[len] != '\0')){
			len++;
			}
	return len;
}




int main(int argc,char* argv[]){
	int fd;
	fd = open(argv[1],O_RDWR,0755);
	char buffer[1];
	char inputs[4096]; //Maximum length of input is 4096
	int index;
	int line;
	while(1){
		gets(inputs,4096,stdin); //Use gets function for input. fgets stores \n in the string.
		if(strCompare(inputs,"PA1EXIT")==0){
			return 0; //Exit program
		}
		else{
			switch(functionHandler(inputs)){
				case 1: ;
					//implement function 1
					index = 0;
					line = 1;
					read(fd,buffer,1);
					if(buffer[0]==inputs[0]){
                                                                 int fd2;
                                                                 fd2 = fd;
                                                                 if(bufferCompare(fd2,inputs)==1){
                                                                                printf("%d:%d\n",line,index);
                                                                 }
                                        }
					while(read(fd,buffer,1)>0){
						index++;
						if(buffer[0] == '\n'){
							printf("NEWLINE!\n");
							line++;
							index = 0;
							read(fd,buffer,1);
							if(buffer[0]==inputs[0]){
								int fd2;
								fd2 = fd;
								if(bufferCompare(fd2,inputs)==1){
										printf("%d:%d\n",line,index);
								}
								index++;
							}
						}
						/* 
						   implementation idea 1.
						   If find same alphabet, check if it is same string or not.
						   Use lseek()?
						   Or duplicate file descriptor.(Is this possible?) -> success
						*/
						//printf("success read file...\n");
						if(buffer[0] == ' '){ // Check if this character is first letter of word.
							read(fd,buffer,1);
							index++;
							if(buffer[0]==inputs[0]){ // First alphabets are same.
								int fd2;
								fd2 = fd;
								if(bufferCompare(fd2,inputs)==1){
									printf("%d:%d\n",line,index);	
							}
						}
						}

					}
					break;
				/*case 2: ;
					//implement function 2
					   implementation idea:
					   1. preprocess input words. (Tokenize)
					   2. check line.
					   3. If line has one words, check again for second word.
					   4. Again.. Again..
					*/
						
				case 3: ;
					//implement function 3
					// 1. remove quotation marks
					// 2. Check string by using bufferCompare().
					char processed_str[4096];
					int index2 = 1;
					int index3 = 0;
					while(inputs[index2] != '"'){ //Removing quotation marks.
						processed_str[index3] = inputs[index2];
						index2++;
						index3++;
					}
					index = 0;
					line = 1;
					read(fd,buffer,1);
					if(buffer[0]==processed_str[0]){
                                                                 int fd2;
                                                                 fd2 = fd;
                                                                 if(bufferCompare(fd2,processed_str)==1){
                                                                                 printf("%d:%d\n",line,index);
                                                                         }
                                                                 index++;
                                                         }

					while(read(fd,buffer,1)>0){
						index++;
						if(buffer[0] == '\n'){
							line++;
							index = 0;
							read(fd,buffer,1);
							if(buffer[0]==processed_str[0]){
								int fd2;
								fd2 = fd;
								if(bufferCompare(fd2,processed_str)==1){
										printf("%d:%d\n",line,index);
								}
								index++;
							}
						}
						if(buffer[0] == ' '){ // Check if this character is first letter of word.
							read(fd,buffer,1);
							index++;
							if(buffer[0]==processed_str[0]){ // First alphabets are same.
								int fd2;
								fd2 = fd;
								if(bufferCompare(fd2,processed_str)==1){
									printf("%d:%d",line,index);	
							}
						}
						}

					}
					break;
				case 4: ;
					//implement function 4
					/*	
					  implementation idea.
					  1. split 2 words.
					  2. check 2 times.
					*/
					char str1[4096];
					char str2[4096];
					int iter = 0;
					int iter1 = 0;
					int iter2 = 0;
					int flag = 0;
					while(inputs[iter] != '*'){ //split 2 words
						str1[iter1] = inputs[iter];
						iter++;
						iter1++;
					}
					str1[iter1] = '\0';
					iter++;
					while(inputs[iter] != '\0'){
						str2[iter2] = inputs[iter];
						iter++;
						iter2++;
					}
					str2[iter2] = '\0';
					line = 1;
					read(fd,buffer,1);
					if(buffer[0]==str1[0]||buffer[0]==str2[0]){
                                                                 int fd2;
                                                                 fd2 = fd;
								 int fd3;
								 fd3 = fd;
                                                                 if(bufferCompare(fd2,str1)==1){
                                                                        flag = 1;
                                                                 }
								 if(bufferCompare(fd3,str2)==1){
									 flag = 1;
								 }
                                        }
					while(read(fd,buffer,1)>0){
						if(buffer[0] == '\n'){
							if(flag == 1){
								printf("%d ",line);
							}
							flag = 0;
							line++;
							read(fd,buffer,1);
							if(buffer[0]==str1[0] || buffer[0]==str2[0]){
								int fd2;
								fd2 = fd;
								int fd3;
								fd3 = fd;
								if(bufferCompare(fd2,str1)==1){
										flag = 1;
								}

								if(bufferCompare(fd3,str2)==1){
									flag = 1;
								}
							}
						}
						if(buffer[0] == ' '){ // Check if this character is first letter of word.
							read(fd,buffer,1);
							if(buffer[0]==str1[0]||buffer[0]==str2[0]){ // First alphabets are same.
								int fd2 = fd;
								int fd3 = fd;
								if(bufferCompare(fd2,str1)==1){
									printf("same string %s\n",str1);
									flag = 1;	
								}
								lseek(fd3,checkLength(str1),1);
								if(bufferCompare(fd3,str2)==1){
									printf("same string %s\n",str2);
									flag = 1;
								}

							}
						}

					}
					break;			
			}
			
		}
		fd = open(argv[1],O_RDWR,0755);


	}

		
}

