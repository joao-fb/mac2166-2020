#include <stdio.h>

int main(int agrc, char *argv[]){

    long N, counter, number, n1=2, n2=3, n3=5, n4=7, i=0, soma, isSum=0, indicador=0;

    scanf("%ld", &N);
    while(N != 0){
        while(N > i){

            soma = n1*n1+n2*n2+n3*n3+n4*n4;

            if(soma == N){
                isSum = 1;
                break;
            }

            for(counter=n1+1; counter; counter++){
                for(number = 2; counter > number; number++){
                    if(counter%number == 0){
                        indicador = 1;
                        break;
                    }
                }

                if(indicador==0){
                    n1 = counter;
                    break;
                }
                indicador = 0;
            }

            for(counter=n2+1; counter; counter++){
                for(number = 2; counter > number; number++){
                    if((counter%number) == 0){
                        indicador = 1;
                        break;
                    }
                }

                if(indicador==0){
                    n2 = counter;
                    break;
                }
                
                indicador = 0;
            }

            for(counter=n3+1; counter; counter++){
                for(number = 2; counter > number; number++){
                    if(counter%number == 0){
                        indicador = 1;
                        break;
                    }
                }

                if(indicador==0){
                    n3 = counter;
                    break;
                }
                indicador = 0;
            }

            for(counter=n4+1; counter; counter++){
                for(number = 2; counter > number; number++){
                    if(counter%number == 0){
                        indicador = 1;
                        break;
                    }
                }

                if(indicador==0){
                    n4 = counter;
                    break;
                }
                indicador = 0;
            }

            i ++;        
        }

        if(isSum == 0){
            printf("Nao existem 4 primos consecutivos cujos quadrados somam %ld\n", N);
        }

        else{
            printf("%ld = %ld^2 + %ld^2 + %ld^2 + %ld^2\n", N, n1, n2, n3, n4);
        }

        scanf("%ld", &N);
        isSum = 0;
        n1=2;
        n2=3;
        n3=5;
        n4=7;
        i=0;
        soma=0;
        indicador=0;

    }
}
