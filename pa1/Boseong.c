#define INSIZE 4096
#define SEEK_CUR 1
int strCmp(char str1[], char str2[]){
	int index = 0;
	while(str1[index] != '\0' && str1[index] != '\n' && str2[index] != '\0' && str2[index] != '\n'){
		if(str1[index] != str2[index]) return 0;
		index++;
	}
	return 1;
}

int checkLen(char* str){
    int i = 0;

    while((str[i] != '\n') && (str[i] != '\0'))
        i++;

    return i;
}

void swap(char* x, char* y){
    char t = *x;
    *x = *y;
    *y = t;
}

char* reverse(char* str, int a, int b){
    while(a < b)
        swap(&str[a++], &str[b--]);

    return str;
}

char* itoa(int value, char* str){
    int n = value;
    int i = 0;

    while(n){
        int r = n % 10;
        str[i++] = '0' + r;
        n /= 10;
    }

    if(i == 0)
        str[i++] = '0';

    str[i] = '\0';

    return reverse(str, 0, i - 1);
}

char ch_capital(char c){
    if(('a' <= c) && (c <= 'z'))
        return c - 32;
    else if (('A' <= c) && (c <= 'Z'))
        return c + 32;
    else
        return c;
}

int spaceLen(char* str){
    int i = 0;

    while(str[i] != ' ')
        i++;

    return i;
}

int IsAlphabet(char c){
    if((('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')))
        return 1;
    else
        return 0;
}

int exLen(char* str){
    int i = 0;

    while(str[i] != '*')
        i++;
    while(!IsAlphabet(str[i]))
        i++;

    return i - 1;
}

int whichType(char str[]){
    int space = 0;
    if(str[0] == '"')
        return 3;

    for(int i = 0; i < INSIZE ; i++){
        if(str[i] == ' ')
            space++;

        if(str[i] == '\n'){
            if(space == 0)
                return 1;

            else
                return 2;
        }

        if(str[i] == '*')
            return 4;

    }
}

void case_one(int fd, char str[]){
    int line = 1, index = 0;
    int len = checkLen(str);
    char c;
    char prev = ' ';
    int sindex = 0;
    char lineStr[10];
    char indexStr[10];
    char can_be = 0;
    
    int cur = 0;
    while(read(fd, &c, 1) > 0){
        if(cur == len){
            if(can_be && ((c == '\n') || (c == ' '))){
                char* pline = itoa(line, lineStr);
                char* pindex = itoa(sindex, indexStr);
                write(1,pline,checkLen(pline));
                write(1,":",1);
                write(1,pindex,checkLen(pindex));
                write(1," ",1);
            }
            can_be = 0;
            cur = 0;
        }
        
        if((c == str[cur]) || (c == ch_capital(str[cur]))){
            if(cur == 0){ 
                if((prev == ' ') || (prev == '\n')){
                    can_be = 1;
                    sindex = index;
                }
                else
                    cur = -1;
            }
            cur++;
        }
        else{
            if(can_be)
                can_be = 0;

            cur = 0;
        }

        prev = c;
        
        if(c == '\n'){
            line++;
            index = 0;
            continue;
        }
        
        index++;
    }
}


void case_two(int fd, char str[]){
    int line = 1, index = 0;
    int mid = spaceLen(str);
    int len = checkLen(str);
    char c;
    char prev = ' ';
    char lineStr[10];
    char first = 0;
    char can_be = 0;
    
    int init = 0;
   /int last = mid;
    int cur = 0;
        
    while(read(fd, &c, 1) > 0){
        if(cur == last){
            if(can_be && ((c == '\n') || (c == ' '))){
                if(!first){
                    first = 1;
                    init = mid + 1;
                    last = len;
                    cur++;

                    lseek(fd, -2, SEEK_CUR);
                    read(fd, &c, 1);
                    while(c != '\n'){
                        lseek(fd, -2, SEEK_CUR);
                        read(fd, &c, 1);
                    }
                    prev = c;
                    read(fd, &c, 1);
                }
                else{
                    char* pline = itoa(line, lineStr);
                    write(1,pline,checkLen(pline));
                    write(1," ",1);

                    while(c != '\n')
                        read(fd, &c, 1);
                }
            }
            can_be = 0;
            cur = init;
        }
        
        if((c == str[cur]) || (c == ch_capital(str[cur]))){
            if(cur == init){ 
                if((prev == ' ') || (prev == '\n'))
                    can_be = 1;
                else
                    cur = init - 1;
            }
            cur++;
        }
        else{
            if(can_be)
                can_be = 0;

            cur = init;
        }

        prev = c;
        
        if(c == '\n'){
            first = 0;
            init = 0;
            last = mid;
            line++;
            index = 0;
            continue;
        }
        
        index++;
    }
}

void case_three(int fd, char str[]){
    int line = 1, index = 0;
    int len = checkLen(str);
    char c;
    char prev = ' ';
    int sindex = 0;
    char lineStr[10];
    char indexStr[10];
    char can_be = 0;

    int cur = 1;
    while(read(fd, &c, 1) > 0){
        if(cur == (len - 1)){
            if(can_be && ((c == '\n') || (c == ' ') || (c == '.') || (c == ','))){
                char* pline = itoa(line, lineStr);
                char* pindex = itoa(sindex, indexStr);
                write(1,pline,checkLen(pline));
                write(1,":",1);
                write(1,pindex,checkLen(pindex));
                write(1," ",1);
            }
            can_be = 0;
            cur = 1;
        }
        
        if((c == str[cur]) || (c == ch_capital(str[cur]))){
            if(cur == 1){
                if((prev == ' ') || (prev == '\n')){
                    sindex = index;
                    can_be = 1;
                }
                else
                    cur = 0;
            }
            cur++;
        }
        else{
            if(can_be)
                can_be = 0;

            cur = 1;
        }

        prev = c;

        if(c == '\n'){
            line++;
            index = 0;
            continue;
        }
        
        index++;
    }
}

void case_four(int fd, char str[]){
    int line = 1, index = 0;
    int len = checkLen(str);
    int mid = exLen(str);
    char c;
    char prev = ' ';
    char lineStr[10];
    char first = 0;
    char can_be1 = 0, can_be2 = 0;
    int init = 0;
    int last = mid;
    int cur = 0;

    while(read(fd, &c, 1) > 0){
        if(((str[cur] == ' ') || (str[cur] == '*')) && can_be1 && ((c == '\n') || (c == ' '))){
            first = 1;
            init = mid + 1;
            last = len;
                
            while((str[cur] != ' ') && (str[cur] != '*'))
                cur++;
            
            while(!IsAlphabet(c)){
                if(c == '\n')
                    break;
                else
                    read(fd, &c, 1);
            }
            while(c != ' '){
                if(c == '\n')
                    break;
                else
                    read(fd, &c, 1);
            }
        }

        if(cur == len){
            if(can_be2 && ((c == '\n') || (c == ' ') || (c == '.') || (c == ','))){
                char* pline = itoa(line, lineStr);
                write(1,pline,checkLen(pline));
                write(1," ",1);
            }
            can_be1 = 0;
            can_be2 = 0;
            cur = 0;
        }
        
        if((c == str[cur]) || (c == ch_capital(str[cur]))){
            if(cur == init){ 
                if((prev == ' ') || (prev == '\n')){
                    if(!can_be1)
                        can_be1 = 1;
                    if(!can_be2)
                        can_be2 = 1;
                }
                else
                    cur = init - 1;
            }
            cur++;
        }
        else{
            if(!first){
                if(can_be1)
                    can_be1 = 0;
            }
            else{
                if(can_be2)
                    can_be2 = 0;
            }
            cur = init;
        }

        prev = c;
        
        if(c == '\n'){
            first = 0;
            init = 0;
            last = mid;
            cur = 0;
            line++;
            index = 0;
            continue;
        }
        
        index++;
    }

}

