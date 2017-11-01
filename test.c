#include <stdlib.h>
#include <stdio.h>
#include <string.h>



int main(){
 
int id, id_space;
	FILE* file = NULL;
    char line[100] = "";
    char name[100] = "";
    char* toks = NULL;
char* a;
int b,c;

    file = fopen("objects.dat", "r");

    while (fgets(line, 100, file)) {
        if (strncmp("#o:", line, 3) == 0) {
            toks = strtok(line + 3, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            id_space = atol(toks);
 }

strcpy(a,name);
b=id;
c=id_space;

printf("%s %d %d", a,c,b);

return 0;
}