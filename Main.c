#include "lexical_analyser.h"



int main() {
    FILE *fp = fopen("input.txt","r");
    if(fp==NULL){
        printf("File does not exist\n");
        return 0;
    }
    printf("----------------------------------------------------------------------------------\n");
printf("open : Code.c :Success\n");
printf("Parsing :                               Code.c :                         Started\n");
printf("----------------------------------------------------------------------------------\n");

    analyzeFile(fp);

    fclose(fp);
    printf("----------------------------------------------------------------------------------\n");
    printf("Parsing :                           Code.c :                          Success\n");
    printf("----------------------------------------------------------------------------------\n");
    return 0;

}
