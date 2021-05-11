/***************************************************************/
/**                                                           **/
/**   João Pedro Barreto         Número USP 11805360          **/
/**   Exercício-Programa 03                                   **/
/**   Professor: Yoshiharu Kohayakawa                         **/
/**   Turma: 03                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX        400
#define MAX2    160000
#define FNMAX      200

int LeDesenho(char nomearq[FNMAX], int M[MAX][MAX], int *pm, int *pn, int *pmax);
int LeTexto( char nomearq[FNMAX], char T[MAX2], int *pk );
int BeDe( int k, int m, int n, int *pb, int *pd );
int ProximosBBits( char T[MAX2], int b, int *pik, int *pib );
void Codifica( int D[MAX][MAX], int m, int n, char T[MAX2], int k, int Dl[MAX][MAX], int b, int d, int modo );
int Maximo( int D[MAX][MAX], int m, int n );
int EscreveDesenho( char nomearq[FNMAX], int M[MAX][MAX], int m, int n, int max );
void DeBeDe( int D[MAX][MAX], int Dl[MAX][MAX], int m, int n, int *pb, int *pd );
int DeCodifica( int D[MAX][MAX], int Dl[MAX][MAX], int m, int n, int b, int d, char T[MAX2], int modo );
int EscreveTexto( char nomearq[FNMAX], char T[MAX2], int k );



int LeDesenho(char nomearq[FNMAX], int M[MAX][MAX], int *pm, int *pn, int *pmax){

    int i, j, erro = 0;
    char jogafora[10];
    FILE *fp;

    if (!(fp = fopen(nomearq, "r"))) {
        printf("Erro ao abrir o arquivo %s\n", nomearq);
        erro = 1;
        /* mais comandos para lidar com o erro na abertura do arquivo */
    }
    else{
        fp = fopen(nomearq, "r");

        fscanf(fp, "%s", jogafora);
        fscanf(fp, "%d %d", &*pn, &*pm);
        fscanf(fp, "%d", &*pmax);

        for(i = 0; i < *pm; i++){
            for(j = 0; j < *pn; j++){
                fscanf(fp, "%d", &M[i][j]);
            }
        }

        printf("m = %d n = %d\n", *pm, *pn);

        fclose(fp);
    }

    return erro;


}

int LeTexto( char nomearq[FNMAX], char T[MAX2], int *pk ){

     int i, erro = 0;       
     FILE *fp;

    if (!(fp = fopen(nomearq, "r"))) {
        printf("Erro ao abrir o arquivo %s\n", nomearq);
        erro = 1;
        /* mais comandos para lidar com o erro na abertura do arquivo */
    }
    else{
        fp = fopen(nomearq, "r");

        i = 0;
        while(fscanf(fp, "%c", &T[i]) > 0)
            i++;
        
        T[i] = '\0';
        
        *pk = i;

        printf("k = %d\n", *pk);

        fclose(fp);
    }   

    return erro;
}

int BeDe( int k, int m, int n, int *pb, int *pd ){
    int charBits, razaoMD, razaoND, erro = 0;
    double intermedB;

    charBits = k*8;

    *pb = charBits/(m*n-1);
    intermedB = (double) charBits/(m*n-1);

    if(intermedB > *pb){
        *pb += 1;
    }

    while(8 % *pb != 0 && *pb <= 8){
        *pb += 1;
    }

    if(*pb > 8 || *pb < 1){
        erro = 1;
    }

    *pd = 1;

    razaoMD  = m/(*pd);
    razaoND = n/(*pd);

    while(razaoMD*razaoND*(*pb) >= charBits + (*pb) && !erro){
        *pd +=1;
        razaoMD  = m/(*pd);
        razaoND = n/(*pd);
    }

    *pd -= 1;

    if(*pd < 1 || *pd > m || *pd > n){
        erro = 1;
    }

    if(!erro){
        printf("b = %d d = %d\n", *pb, *pd);
    }
    
    return erro;
}


int ProximosBBits( char T[MAX2], int b, int *pik, int *pib ){
    int ascii, notDump, bits;

    ascii = (int) T[*pik];
    notDump = ascii / (1<<(*pib));
    bits = notDump % (1<<b);

    *pib += b;
    if(*pib == 8){
        *pib = 0;
        *pik += 1;
    }

    return bits;
}

void Codifica( int D[MAX][MAX], int m, int n, char T[MAX2], int k, int Dl[MAX][MAX], int b, int d, int modo ){
    int i, j, di, dj, pik, pib, x, y, notDump;

    pik = 0;
    pib = 0;

    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            Dl[i][j] = D[i][j];
        }
        
    }

    for(di = d - 1; di < (m/d) && pik < k;){
        for(dj = d - 1; dj < (n/d) && pik < k;){

            if(di == d-1 && dj == d-1){

                x = D[di][dj];

                notDump = b / (1<<(0));
                y = notDump % (1<<b);

                Dl[di][dj] = (x/(1<<b))*(1<<b) + ((x + y) % (1<<b));

            }
            else{
                x = D[di][dj];
                y = ProximosBBits(T, b, &pik, &pib); 

                Dl[di][dj] = (x/(1<<b))*(1<<b) + ((x + y) % (1<<b));
            }
            if(modo == 1){
                printf("(%d, %d) bits %d original %02x codificado %02x\n", di, dj, y, x, Dl[di][dj]);
            }
            dj += d;
        }
        di += d;
    }

}

int Maximo( int D[MAX][MAX], int m, int n ){
    int i, j, max = 0;

    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            if(D[i][j] > max){
                max = D[i][j];
            }
        }
    }

    return max;
    
}

int EscreveDesenho( char nomearq[FNMAX], int M[MAX][MAX], int m, int n, int max ){

    int i, j, erro = 0;
    FILE *fp;
    fp = fopen(nomearq, "w");

    fprintf(fp, "P2\n");
    fprintf(fp, "%d %d\n", n, m);
    fprintf(fp, "%03d\n", max);

    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            fprintf(fp, "%03d ", M[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    return erro;
}


void DeBeDe( int D[MAX][MAX], int Dl[MAX][MAX], int m, int n, int *pb, int *pd ){

    int i, j, b = 1;

    *pd = 0;
    *pb = 1;
    for(i = 0; i < m && *pd == 0; i++){
        for(j = 0; j < n && *pd == 0; j++){
            if((Dl[i][j] - D[i][j]) != 0){
                for(b = 0; *pb != ((Dl[i][j] - D[i][j] + 256) % (1<<*pb)) && *pb <= 8; b++){
                    *pb = (1<<b);
                }
                *pd = i + 1;
            }
        }
    }

    printf("b = %d d = %d\n", *pb, *pd);
}


int DeCodifica( int D[MAX][MAX], int Dl[MAX][MAX], int m, int n, int b, int d, char T[MAX2], int modo ){

    int di, dj, bits = 0, charc = 0, pib = 0, pik = 0;

    for(di = d-1; di <= ((m/d)*d)-1;){
        for(dj = d-1; dj <= ((n/d)*d)-1;){
            if(di == d-1 && dj == d-1){
                dj += d;
                continue;
            }
            else{
                bits = (Dl[di][dj] - D[di][dj] + 256) % (1<<b);
                charc += bits * (1<<pib);

                pib += b;
                if(pib == 8){
                    if(charc == 0){
                        break;
                    }
                    T[pik] = charc;
                    charc = 0;
                    pib = 0;
                    pik +=1;
                }
                if(modo == 1){
                    printf("(%d, %d) bits %d original %02x codificado %02x\n", di, dj, bits, D[di][dj], Dl[di][dj]);
                }
            }
            dj += d;
        }
        di += d;
    }
    printf("k = %d\n", pik);

    return pik;
}


int EscreveTexto( char nomearq[FNMAX], char T[MAX2], int k ){
    int i, erro = 0;
    FILE *fp;

    fp = fopen(nomearq, "w");

    for(i = 0; i < k; i++){
        fprintf(fp, "%c", T[i]);
    }

    fclose(fp);

    return erro;
}

int main(){

    int m, n, max, D[MAX][MAX], k, b, d, Dl[MAX][MAX], modo=0, operacao=5, erro, i;
    char nomearqDesenho[FNMAX], nomearqTexto[FNMAX], nomearqDesenhoCodificado[FNMAX], T[MAX2];

    while(operacao != 0){

        printf("\nDigite a operacao desejada:\n");
        printf("  1. Codificar\n");
        printf("  2. Decodificar\n");
        printf("  3. Mostrar mensagem\n");
        if(modo == 0){
            printf("  4. Ativar modo verborragico\n");
        }
        else{
            printf("  4. Desativar modo verborragico\n");
        }
        printf("  0. Finalizar\n\n");

        printf("OPCAO: ");
        scanf("%d", &operacao);

        while(operacao == 1){
            printf("Arquivo que contem o desenho original: ");
            scanf(" %[^\n]", nomearqDesenho);

            erro = LeDesenho(nomearqDesenho, D, &m, &n, &max);
            
            if(erro){
                printf("\nERRO: Operacao abortada devido a erro na leitura\n");
                operacao = 5;
                break;
            }

            printf("Arquivo que contem a mensagem a ser ocultada: ");
            scanf(" %[^\n]", nomearqTexto);

            erro = LeTexto(nomearqTexto, T, &k);

            if(erro){
                printf("\nERRO: Operacao abortada devido a erro na leitura\n");
                operacao = 5;
                break;
            }

            erro = BeDe(k, m, n, &b, &d);

            if(erro){
                printf("\nERRO: Nao e possivel ocultar os %d caracteres da mensagem\n", k);
                printf("\nERRO: Operacao abortada pois mensagem nao pode ser ocultada\n");
                operacao = 5;
                break;
            }

            Codifica( D, m, n, T, k, Dl, b, d, modo );

            max = Maximo(Dl, m, n);

            printf("Gravar desenho esteganografado em: ");
            scanf(" %[^\n]", nomearqDesenhoCodificado);
            erro = EscreveDesenho(nomearqDesenhoCodificado, Dl, m, n, max);

            if(erro){
                printf("\nERRO: Operacao abortada devido a erro na leitura\n");
                operacao = 5;
                break;
            }

            operacao = 5;
        }

        while(operacao == 2){

            printf("Arquivo que contem o desenho original: ");
            scanf(" %[^\n]", nomearqDesenho);

            erro = LeDesenho(nomearqDesenho, D, &m, &n, &max);
            
            if(erro){
                printf("\nERRO: Operacao abortada devido a erro na leitura\n");
                operacao = 5;
                break;
            }

            printf("Arquivo que contem o desenho esteganografado: ");
            scanf(" %[^\n]", nomearqDesenhoCodificado);

            erro = LeDesenho(nomearqDesenhoCodificado, Dl, &m, &n, &max);
            
            if(erro){
                printf("\nERRO: Operacao abortada devido a erro na leitura\n");
                operacao = 5;
                break;
            }

            DeBeDe(D, Dl, m, n, &b, &d);
            k = DeCodifica(D, Dl, m, n, b, d, T, modo);

            printf("Gravar mensagem decodificada em: ");
            scanf(" %[^\n]", nomearqTexto);

            EscreveTexto(nomearqTexto, T, k);

            operacao = 5;
        }

        while(operacao == 3){

            printf("Arquivo que contem a mensagem: ");
            scanf(" %[^\n]", nomearqTexto);

            erro = LeTexto(nomearqTexto, T, &k);

            if(erro){
                printf("\nERRO: Operacao abortada devido a erro na leitura\n");
                operacao = 5;
                break;
            }

            printf("\n\nMENSAGEM contida no arquivo %s (tudo entre ---> e <---)\n", nomearqTexto);
            printf("--->");
            for(i = 0; i < k; i++){
                printf("%c", T[i]);
            }
            printf("<---\n\n");
            operacao = 5;
        }

        if(operacao == 4){
            printf("Modo verborragico ativado\n");
            modo = 1;
            operacao = 5;
        }
    } 

    return 0;

}
