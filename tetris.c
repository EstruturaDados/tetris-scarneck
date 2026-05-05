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

#define MAX_PIECES 8
#define MIN_PIECES 4

struct Piece{
    char tipo;
    int id;
};
struct Fila{
    int inicio;
    int fim;
    int total;
    struct Piece peca[MAX_PIECES];
};

int filaCheia(struct Fila *f){
    if( f->total == MAX_PIECES){
        return 1;
    }else {return 0;}
}
int filaVazia(struct Fila *f){
    if(f->total==0){
        return 1;
    }else{return 0;}
}

void showFila(struct Fila *f){
    if(filaVazia(f)==1){
        printf("\nA fila de peças está vazia.\n");
        return;
    }
    
    printf("\n--- Fila de Peças ---\n");
    
    int idx = f->inicio;
    for(int i = 0; i < f->total; i++){
        printf("%d# --> '%c' (id: %d)\n",
            i+1,
            f->peca[idx].tipo,
            f->peca[idx].id);
            
            idx = (idx + 1) % MAX_PIECES;
    }
}

void queue(struct Fila *f, struct Piece piece){
    // Checagem se a fila está cheia
    if (filaCheia(f)==1){
        printf("\nA fila está cheia!\n");
        return;
    }

    // Coloca a peça passada como parâmetro no indice final da fila
    f->peca[f->fim] = piece;
    // Muda o indice final para frente modularizado garantindo que a fila seja circular
    f->fim = (f->fim+1)%MAX_PIECES;
    // Aumenta o valor da quantidade de peças na fila 
    f->total++;
    printf("Peça '%c' Inserida na fila!\n", piece.tipo);
}
struct Piece dequeue(struct Fila *f){
    // Checagem se a fila está vazia, caso esteja retorna uma peça vazia
    struct Piece vazio = {-1};
    if(filaVazia(f)==1){
        printf("\nA fila está vazia!\n");
        return vazio;
    }

    // Coloca a primeira peça em uma variável temporária que será retornada ao ser deletada da fila
    struct Piece removed;
    removed = f->peca[f->inicio];
    // Move o primeiro indice para frente modularizadando garantido que a fila continue circular
    f->inicio = (f->inicio+1)%MAX_PIECES;
    // Diminui a quantidade total de peças na fila
    f->total--;
    printf("Peça '%c' removida da fila!\n", removed.tipo);
    // Retorna a peça removida para impressão.
    return removed;
}

void firstPieces(struct Fila *f){
    char pieces[MIN_PIECES] = {'T','O','I','L'};
    int r = rand()%MIN_PIECES;

    for(int i=0;i<MIN_PIECES;i++){
        struct Piece p;
        p.id = i;
        p.tipo = pieces[(r+i)%MIN_PIECES];
        queue(f, p);
    }
}
void initFila(struct Fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
    firstPieces(f);
    showFila(f);
}

struct Piece genPiece(){
    char pieces[MIN_PIECES] = {'T','O','I','L'};
    int r = rand()%MIN_PIECES;
    struct Piece piece;
    piece.tipo = pieces[r];
    piece.id= rand()%100;
    return piece;
    
}

void menu(struct Fila *fila){
    do{
        int opt;
        printf("\n---     Menu de opções   ---\n");
        printf("1 -> Jogar uma peça\n");
        printf("2 -> Inserir nova peça\n");
        printf("0 -> Sair\n");
        scanf("%d",&opt);
        switch (opt){
            case 1:
                struct Piece rem = dequeue(fila);
                showFila(fila);
                break;
            case 2:
                struct Piece p = genPiece();
                queue(fila, p);
                showFila(fila);
                break;
            case 0:
                printf("\nSaindo...\n");
                return;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    }while(1);
}


int main() {
    srand(time(NULL));
    struct Fila fila;

    initFila(&fila);
    menu(&fila);
    
    return 0;
}



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
