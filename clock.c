#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv[]) {

    clock_t begin;
    int time_spent=0;
    int param=atoi(argv[1]);

    /* Début de la clokc */
    begin = clock();
    while(time_spent < param)//Param est le nombre de secondes en paramètre d'entrée
        {
        /* Dès que la boucle while commence, on récupère le temps du CPU */
        time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC; //Jusqu'à atteindre param
        }
    return(0);
}
