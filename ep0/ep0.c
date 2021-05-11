/***************************************************************/
/**                                                           **/
/**   João Pedro Fileti Barreto                  11805360     **/
/**   Exercício-Programa 0                                    **/
/**   Professor: Yoshiharu Kohayakawa                         **/
/**   Turma: 03                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>


int main(int argc, char *argv[]){

    int N, n1=0, n2=0, n3=0, n4=1, soma, i1=4;
    scanf("%d", &N);

    if (N <= 2){
        printf("0\n");
    }

    if(N == 3){
        printf("1\n");
    }

    if (N > 3){

        while(N >= i1){

            soma = n1+n2+n3+n4;
            n1 = n2;
            n2 = n3;
            n3 = n4;
            n4 = soma;

            i1++;

        }

        printf("%d\n", soma);
    }

    return 0;

}
