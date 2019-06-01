/* UNIVERSIDADE FEDERAL DE SANTA CATARINA
    Alunos: Matheus Francisco Batista Machado (14202492)
            Mayara Sousa Stein(14104266)
            Ale Chaito (14205353)
*/
/*Exercicio programa , consiste na implementac˜ao de um sistema de escalonamento de
processos simplificado. A estrutura de dados fila de prioridade implementada em um
max-heap deve ser usada. O max-heap tamb´em deve ser implementado em um
vetor.*/


/* TODOS OS CODIGOS FOI VISTO EM SALA DE AULA*/
/** Tentamos explicar o que foi feito pedimos que qualquer duvida  entre em com
contato..
O codigo consiste em receber processos onde tem nome , tempo e prioridade , o processo vai ser executado
de acordo com sua prioridade mas se o tempo for maior que 50ms então o processo é mandado de novo para fila se não o processo é removido
da fila */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 23

typedef struct especificacao {
    char id[N];
    int tempo;
    int prioridade;
};

typedef struct especificacao PROC;

/*----------FUNÇÕES-------------*/

int Constroiheap(PROC *vet, int n, PROC x); /* Construindo heap, inserindo processo no vetor*/
int remover(PROC *vet, int n);
int indmaximo(PROC *vet, int n, int p, int fe, int fd);
void heapfica(PROC vet[], int n);/*recebe um quase heap e transforma em um heap*/
void maxheap(PROC *vet, int n);/* constroi maxheap*/


/*----------FUNÇÕES-------------*/
int main(){
    int nlinhas;
    int numprocessos;
    int i, k, j = 0;
    PROC vet[5001];
    PROC executado[5001];

    /*numero de linhas n, n>0*/

    scanf("%i", &nlinhas);


    while(--nlinhas >= 0){/*numero de processos */
        scanf("%i", &numprocessos);

        for(k = j; k < j+numprocessos; k++){ /*nome do processo*/
            scanf("%s", vet[k].id);
        }
        for(k = j; k < j+numprocessos; k++){/*prioridade do processo*/
            scanf("%i", &vet[k].prioridade);
        }
        for(k = j; k < j+numprocessos; k++) {  /*tempo do processo*/
            scanf("%i", &vet[k].tempo);
        }
        j += numprocessos;
        if(numprocessos+j != 0)        {
                maxheap(vet, j);
            executado[i] = vet[0];
            printf("Execuntando processo : %s\n", executado[i].id);
            if(vet[0].tempo > 50)    { /*manda de novo para fila com tempo -50*/
                vet[0].tempo -= 50;
            }
            else
            {
                j = remover(vet, j); /*tempo <50 remove da fila o processo*/
            }

        }
        else
        {
            printf("!!!PROCESSO OCIOSO!!! \n");
        }
    }
    if(j != 0){
    for(i = 0; i < j; i++)
    {
        printf("%s ", vet[i].id);
        printf("%i\t", vet[i].prioridade);
        printf("%i\t", vet[i].tempo);
    }
    }else{
    printf("\nNao sobraram processos");
    }
    return 0;
}

/*vamos passar o vetor o tamanho e a prioridade*/
int Constroiheap(PROC *vet, int n, PROC x){ /* Inseri no vetor*/
    int f;
    PROC aux;
    strcpy(vet[n].id, x.id);
    vet[n].prioridade = x.prioridade;
    vet[n].tempo = x.tempo;
    f = n;
    while(f > 0 && vet[f/2].prioridade < vet[f].prioridade){ /* troca */
        aux = vet[f/2];
        vet[f/2] = vet[f];
        vet[f] = aux;
        f = f/2;
    }
    return n+1;
}

int remover(PROC *vet, int n){
    PROC aux;
    aux = vet[0];
    vet[0] = vet[n-1]; /* n-1 é o ultimo*/
    vet[n-1] = aux;
    heapfica(vet, n-2); /*passa o vetor sem o ultimo pois foi ("removido", mandado para o final)*/
    return n-1;
}


int indmaximo(PROC *vet, int n, int p, int fe, int fd){ /*procura qual tem a maior prioridade */
    if (fe > n)
        return p;
    else {
        if(fd > n) {
            if ( vet[fe].prioridade > vet[p].prioridade)
                return fe;
            else return p;
        }
        else {
            if (vet[fe].prioridade > vet[fd].prioridade){
                if ( vet[fe].prioridade > vet[p].prioridade)
                    return fe;
                else return p;
            }
            else {
                if (vet[fd].prioridade > vet[p].prioridade)
                    return fd;
                else return p;
            }
        }
    }
}


void heapfica(PROC vet[], int n){/* Recebe um não heap e transforma em heap*/
    int pai, maximo;
    PROC aux;
    pai = 0;
    maximo = indmaximo(vet, n, pai, pai*2+1, pai*2+2); /*recebe o indice de maior prioridade */
    while(pai != maximo){    /*verifica se o indce de maior prio não é o pai */
        aux = vet[maximo];
        vet[maximo] = vet[pai];
        vet[pai] = aux;
        pai = maximo;
        maximo = indmaximo(vet, n, pai, pai*2+1, pai*2+2);  /*recebe o novo maximo, para verificar novamente*/
    }
}

/*outro jeito de montar maxheap ( com for)

void maxheap(PROC *vet, int n){
    int i;
    for (i = 1; i < n; i++)
        Constroiheap(v, i, v[i]);
}
*/
void maxheap(PROC *vet, int n){ /* faz maxheap*/
    int t;
    t =1 ;
    while(t!=n){
        t = Constroiheap(vet, t, vet[t]);
    }
}

