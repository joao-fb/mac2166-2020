/***************************************************************/
/**                                                           **/
/** João Pedro Barreto 11805360                               **/
/** Exercício-Programa 2                                      **/
/** Professor: Yoshiharu Kohayakawa                           **/
/** Turma: 03                                                 **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BISSEC_TOL (1e-6)
#define RANDOM_SEED 1234

/* Funções implementadas abaixo, devem ser copiadas no seu código */
void ativa_sorteador();
double sorteia_real();
int sorteia_voto_com_falha(double f);
int calcula_numero_de_votos(int N, double percentage, double f, int *votos_1, int *votos_2);
double prob_erro(int N, double a, double f, int T);
double bissecta (int N, double a, int T, double tol);

/* "dá a partida" no gerador de números aleatórios */
void ativa_sorteador()
{ 
#ifdef RANDOM_SEED
    srand(RANDOM_SEED);
#else
    srand(time(NULL));
#endif
}
/* devolve um real sorteado uniformemente no intervalo [0,1] */
double sorteia_real(){
return (double) rand() / RAND_MAX;
}

int sorteia_voto_com_falha(double f){
    double falha;
    int is_falha;

    falha = sorteia_real();

    if(falha > f){
        is_falha = 0;
    }

    else{
        is_falha = 1;
    }
    
    return is_falha;
}

int calcula_numero_de_votos(int N, double porcentagem, double f, int *votos_1, int *votos_2){
    int n_iter, is_falha, j;

    n_iter = (int) N * porcentagem;

    for(j=0; j<n_iter; j++){
        
        is_falha = sorteia_voto_com_falha(f);

        if(is_falha == 0){

            *votos_1 += 1;

        }

        else{
            
            *votos_2 +=1;

        }
        

    }

    return 0;

}

double prob_erro(int N, double a, double f, int T){
     int nerros=0, votos_a, votos_b, votos_a2, votos_b2, i;
     double b, p_erro;

    for(i=0; i<T; i++){
        votos_a = 0;
        votos_b = 0;

        votos_a2 = 0;
        votos_b2 = 0;
        
        b = 1-a;
        calcula_numero_de_votos(N, a, f, &votos_a, &votos_b);
        calcula_numero_de_votos(N, b, f, &votos_b2, &votos_a2);

        votos_a += votos_a2;
        votos_b += votos_b2;

        if(votos_b >= votos_a){
            nerros +=1;
        }

    }


    p_erro = (double) nerros / T;
    return p_erro;

}

double bissecta (int N, double a, int T, double tol){
    double fa=0, fb=1, f;

    while(fb-fa > tol-BISSEC_TOL){
        f = (fa+fb)/2;
        printf("Printando diferença entre FA e FB %f\n", fb-fa);

        if(prob_erro(N, a, f, T) > tol-BISSEC_TOL){

            fb = f;

        }

        else{

            fa = f;

        }

        printf("\nPrintando f %f\n", f);
    }
    return fa;
}


int main(int agrc, char *argv[]){

    int N, T;
    double a, tol, max_falha;

    printf("\nDigite o numero de votantes (0 < N <= 2x10^9): ");
    scanf("%d", &N);
    printf("\nDigite a porcentagem de votos do candidato A (0.5 < a <= 1): ");
    scanf("%lf", &a);
    printf("\nDigite o numero de simulacoes (0 < T <= 2x10^9): ");
    scanf("%d", &T);
    printf("\nDigite a probabilidade toleravel de erros (0 <= tol <= 1): ");
    scanf("%lf", &tol);

    max_falha = bissecta (N, a, T, tol);

    printf("\n\nMaior falha das urnas toleravel: %f\n", max_falha);
    return 0;
}
