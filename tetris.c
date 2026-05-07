#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

// 🧩 Nível Novato: Fila de Peças Futuras
//
// - Crie uma struct Peca com os campos: tipo (char) e id (int).
// - Implemente uma fila circular com capacidade para 5 peças.
// - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
// - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
// - Exiba a fila após cada ação com uma função mostrarFila().
// - Use um menu com opções como:
//      1 - Jogar peça (remover da frente)
//      0 - Sair
// - A cada remoção, insira uma nova peça ao final da fila.

// 🧠 Nível Aventureiro: Adição da Pilha de Reserva
//
// - Implemente uma pilha linear com capacidade para 3 peças.
// - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
// - Permita enviar uma peça da fila para a pilha (reserva).
// - Crie um menu com opção:
//      2 - Enviar peça da fila para a reserva (pilha)
//      3 - Usar peça da reserva (remover do topo da pilha)
// - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
// - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).

#define PIECES_S 4
#define QUEUE_S 5
#define STACK_S 3

typedef struct Piece{
    char tipo;
    int id;
}Piece;

typedef struct Queue{
    int start;
    Piece piece[QUEUE_S];
    int end;
    int total;
}Queue;

typedef struct Stack{
    int top;
    Piece piece[STACK_S];
    int total;
}Stack;

Piece genPiece(){
    Piece piece;
    char pieceList[PIECES_S] = {'T','O','I','L'};
    int rP = rand()%PIECES_S;
    int rID = rand()%100;
    piece.tipo = pieceList[rP];
    piece.id = rID;
    return piece;
}

void initQueue(Queue *q){
    q->start = 0;
    q->end = -1;
    q->total = 0;
    for (int i=0; i<QUEUE_S;i++){
        q->piece[i] = genPiece();
        q->end++;
        q->total++;
    }
}
void initStack(Stack *s){
    s->top=-1;
    s->total=0;
    for (int i=0 ;i<STACK_S;i++){
        s->piece[i].tipo = '\0';
        s->piece[i].id = -1;
    }
}

int fullQueue(Queue *q){
    if(q->total==QUEUE_S){return 1;}else{return 0;}
}
int fullStack(Stack *s){
    if(s->total==STACK_S){return 1;}else{return 0;}
}

int noneQueue(Queue *q){
    if (q->total==0){return 1;}else{return 0;}
}
int noneStack(Stack *s){
    if (s->total==0){return 1;}else{return 0;}
}

void enqueue(Queue *q, Piece p){
    if(fullQueue(q)==1){
        printf("A fila está cheia.\n");
        return;
    }
    q->end = (q->end+1)%QUEUE_S;
    q->piece[q->end] = p;
    q->total++;
}
Piece dequeue(Queue *q){
    Piece naN = {'\0',-1};
    if (noneQueue(q)==1){
        printf("A fila está vazia.\n");
        return naN;
    }

    Piece rem = q->piece[q->start]; 
    q->start = (q->start+1)%QUEUE_S;
    q->total--;
    return rem;
}

void push(Stack *s, Piece p){
    if(fullStack(s)==1){
        printf("A pilha está cheia.\n");
        return;
    }
    s->top++;
    s->piece[s->top] = p;
    s->total++;
}
Piece pop(Stack *s){
    Piece p = {'\0', -1};
    if(noneStack(s)==1){
        printf("A pilha está vazia.\n");
        return p;
    }
    
    Piece rem = s->piece[s->top];
    s->top--;
    s->total--;
    return rem;
}
int pecaNula(Piece p){
    if(p.tipo=='\0'&&p.id==-1){return 1;}else{return 0;}
}

void showState(Queue *q, Stack *s){
    int idx = q->start;
    printf("\n---     Fila de Peças    ---\n");
    for (int i=0; i<q->total;i++){
        printf("['%c'  '%d']  ",q->piece[idx].tipo, q->piece[idx].id);
        idx = (idx+1)%QUEUE_S;
    }
    printf("\n\n---     Pilha de Reservas    ---\n");
    for (int i=s->total-1; i>=0;i--){
        printf("['%c'  '%d']",s->piece[i].tipo, s->piece[i].id);
    }
}

void menu(Queue *q, Stack *s){
    do{
        showState(q,s);
        int opt;
        printf("\n=============================\n");
        printf("        Menu de opções\n");
        printf("=============================\n");
        printf("1 -> Jogar peça\n");
        printf("2 -> Reservar Peça\n");
        printf("3 -> Usar Peça Reservada\n");
        printf("0 -> Sair\n");
        scanf("%d",&opt);
        switch (opt){
            case 1:
                Piece pD = dequeue(q);
                if(pecaNula(pD)==1){
                    printf("Erro ao remover da fila.\n");
                    break;
                }
                printf("Peça '%c' removida da fila de peças!\n", pD.tipo);
                break;
            case 2:
                if(fullStack(s)==1){ // GPT
                    printf("A pilha de reservas está cheia.\n");
                break;
                }

                Piece pDQ = dequeue(q);
                if(pecaNula(pDQ)==1){
                    printf("Erro ao remover da fila.\n");
                    break;
                }
                push(s, pDQ);
                printf("Peça '%c' reservada na pilha!\n", pDQ.tipo);
                break;
            case 3:
                if(fullQueue(q)==1){
                    printf("A fila está cheia.\n");
                    break;
                }
                Piece pS = pop(s);
                if(pecaNula(pS)==1){
                    printf("Erro ao remover da pilha.\n");
                    break;
                }
                enqueue(q, pS);
                printf("Peça '%c' da pilha usada na fila!\n", pS.tipo);
                break;
            case 0:
                printf("Saindo...\n");
                return;
            default:
                printf("Tecla não associada! Tente novamente.\n");
            }
    }while(1);
}


int main(){
    srand(time(NULL));
    Queue q;
    Stack s;
    initQueue(&q);
    initStack(&s);
    menu(&q,&s);
    return 0;
}


// 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
//
// - Implemente interações avançadas entre as estruturas:
//      4 - Trocar a peça da frente da fila com o topo da pilha
//      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
// - Para a opção 4:
//      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
//      Troque os elementos diretamente nos arrays.
// - Para a opção 5:
//      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
//      Use a lógica de índice circular para acessar os primeiros da fila.
// - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
// - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
// - O menu deve ficar assim:
//      4 - Trocar peça da frente com topo da pilha
//      5 - Trocar 3 primeiros da fila com os 3 da pilha
