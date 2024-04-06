#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc,char *argv[]){
	int fd,fd2;
	fd = open(argv[1],O_RDWR | O_CREAT, 0755);
	int target_fd;
	char buffer2[16];
	fd2 = open(argv[1],O_RDWR | O_CREAT, 0755);
	int total_line = 1;
	while(read(fd2,buffer2,1)>0){
		if(buffer2[0]=='\n'){
			total_line++;
		}
	}
	int number = 2;
	
	target_fd = open("Aladdin_num.txt",O_WRONLY | O_CREAT,0755);
	char buffer[16];
	char start = '1';
	char form[3];
	form[0] = ' ';
	form[1] = '|';
	form[2] = ' ';
	write(target_fd,&start,1);	
	write(target_fd,form,3);
	while((read(fd,buffer,1)) >0){
		if(buffer[0]=='\n' && number<total_line){
			char array[5];
			int k = 0;
			int i = number;
			while(i>0){
				array[k] = i%10+'0';
				i=i/10;
				k++;
			}	
			write(target_fd,buffer,1);
			for(;k>0;k--){
				write(target_fd,&array[k-1],1);
			}
			write(target_fd,&form,3);
			number++;	
	}
		else{
			write(target_fd,buffer,1);
		}
	}
}
