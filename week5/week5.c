#include <linux/limits.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ARGS 1000
int main(){
	while(1){
		
		char* cmd = readline("$ ");
	
		add_history(cmd);

		char* args[MAX_ARGS];
		char* save_ptr;
		char* ptr = strtok_r(cmd, " ",&save_ptr);
		int i = 0;
		while(ptr!=NULL){
			if(i>=MAX_ARGS-1){
				printf("Error: Too many arguments\n");
				exit(2);
			}
			args[i++] = ptr;
			ptr = strtok_r(NULL, " ",&save_ptr);
		}
		args[i]=NULL;
		if(strcmp(args[0],"exit")==0){
			printf("exit\n");
			exit((int) args[1]);
		}
		else{
			switch(fork()){
				case -1:
					perror("fork");
					return 1;
				case 0://child
					execvp(args[0],args);
				 	printf("%s: command not found\n",args[0]);	
				default://parents
					wait(NULL);

	}
}
}
}
