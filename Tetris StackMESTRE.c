#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição da struct Peca.
// Esta struct representa uma peça do jogo, com um nome (tipo) e um id único.
// O nome é um caractere representando formas como 'I', 'O', 'T', 'L'.
// O id é um número inteiro incremental para identificar a ordem de criação.
typedef struct {
    char nome;  // Tipo da peça ('I', 'O', 'T', 'L')
    int id;     // Identificador único da peça
} Peca;

// Definição da fila circular para peças futuras.
// Usamos um array para armazenar as peças, com índices para frente e trás.
// Tamanho máximo fixo (10), mas inicializamos com 5 e mantemos cheia.
#define TAMANHO_MAX_FILA 10
Peca fila[TAMANHO_MAX_FILA];
int frente = 0;  // Índice da frente da fila
int tras = 0;    // Índice do trás da fila (próxima posição para inserir)
int tamanhoAtualFila = 0;  // Número de elementos na fila

// Definição da pilha para peças reservadas.
// Usamos um array linear, com topo indicando a posição do último elemento.
// Capacidade máxima de 3 peças.
#define TAMANHO_MAX_PILHA 3
Peca pilha[TAMANHO_MAX_PILHA];
int topo = -1;  // Índice do topo da pilha (-1 se vazia)

int idGlobal = 0;  // Contador global para ids únicos das peças

// Função para gerar uma nova peça automaticamente.
// Seleciona um nome aleatório entre 'I', 'O', 'T', 'L' e atribui um id incremental.
// Retorna a peça gerada.
Peca gerarPeca() {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    novaPeca.nome = tipos[rand() % 4];  // Escolhe tipo aleatório
    novaPeca.id = idGlobal++;           // Atribui id único e incrementa
    return novaPeca;
}

// Função para inicializar a fila com 5 peças.
// Chama gerarPeca 5 vezes e insere na fila usando enqueue.
// Configura o estado inicial da fila.
void inicializarFila() {
    for (int i = 0; i < 5; i++) {
        Peca p = gerarPeca();
        fila[tras] = p;
        tras = (tras + 1) % TAMANHO_MAX_FILA;  // Avança trás circularmente
        tamanhoAtualFila++;
    }
}

// Função para inicializar a pilha vazia.
// Define topo como -1, indicando pilha vazia.
void inicializarPilha() {
    topo = -1;
}

// Função para exibir o estado atual da fila e pilha.
// Mostra a fila no formato [Nome ID] ... e a pilha de topo para base.
// Separa visualmente fila e pilha para clareza.
void exibirEstado() {
    printf("Estado atual:\n");
    
    // Exibe fila
    printf("Fila de pecas\t");
    if (tamanhoAtualFila == 0) {
        printf("Fila vazia\n");
    } else {
        int i = frente;
        for (int count = 0; count < tamanhoAtualFila; count++) {
            printf("[%c %d] ", fila[i].nome, fila[i].id);
            i = (i + 1) % TAMANHO_MAX_FILA;
        }
        printf("\n");
    }
    
    // Exibe pilha
    printf("Pilha de reserva\t(Topo -> base): ");
    if (topo == -1) {
        printf("Pilha vazia\n");
    } else {
        for (int i = topo; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para jogar uma peça (dequeue da fila).
// Remove a peça da frente da fila, se não estiver vazia.
// Em seguida, gera e insere uma nova peça para manter a fila cheia.
// Retorna 1 se sucesso, 0 se fila vazia.
int jogarPeca() {
    if (tamanhoAtualFila == 0) {
        printf("Fila vazia! Nao ha peca para jogar.\n");
        return 0;
    }
    Peca removida = fila[frente];
    frente = (frente + 1) % TAMANHO_MAX_FILA;  // Avança frente
    tamanhoAtualFila--;
    printf("Peca jogada: [%c %d]\n", removida.nome, removida.id);
    
    // Gera e insere nova peça para manter fila cheia
    Peca nova = gerarPeca();
    fila[tras] = nova;
    tras = (tras + 1) % TAMANHO_MAX_FILA;
    tamanhoAtualFila++;
    printf("Nova peca gerada e adicionada: [%c %d]\n", nova.nome, nova.id);
    
    return 1;
}

// Função para reservar uma peça (move da fila para pilha).
// Remove da frente da fila e empilha no topo, se pilha não estiver cheia.
// Em seguida, gera e insere nova peça na fila.
// Retorna 1 se sucesso, 0 se fila vazia ou pilha cheia.
int reservarPeca() {
    if (tamanhoAtualFila == 0) {
        printf("Fila vazia! Nao ha peca para reservar.\n");
        return 0;
    }
    if (topo >= TAMANHO_MAX_PILHA - 1) {
        printf("Pilha cheia! Nao e possivel reservar peca.\n");
        return 0;
    }
    
    // Remove da fila
    Peca reservada = fila[frente];
    frente = (frente + 1) % TAMANHO_MAX_FILA;
    tamanhoAtualFila--;
    
    // Empilha
    topo++;
    pilha[topo] = reservada;
    printf("Peca reservada: [%c %d]\n", reservada.nome, reservada.id);
    
    // Gera e insere nova peça na fila
    Peca nova = gerarPeca();
    fila[tras] = nova;
    tras = (tras + 1) % TAMANHO_MAX_FILA;
    tamanhoAtualFila++;
    printf("Nova peca gerada e adicionada: [%c %d]\n", nova.nome, nova.id);
    
    return 1;
}

// Função para usar uma peça reservada (pop da pilha).
// Remove a peça do topo da pilha, se não estiver vazia.
// Simula uso da peça.
// Retorna 1 se sucesso, 0 se pilha vazia.
int usarPecaReservada() {
    if (topo == -1) {
        printf("Pilha vazia! Nao ha peca reservada para usar.\n");
        return 0;
    }
    Peca usada = pilha[topo];
    topo--;
    printf("Peca reservada usada: [%c %d]\n", usada.nome, usada.id);
    return 1;
}

// Função para trocar a peça da frente da fila com o topo da pilha.
// Se fila não vazia e pilha não vazia, troca os valores.
// Não gera nova peça, pois não há remoção.
// Retorna 1 se sucesso, 0 se fila ou pilha vazia.
int trocarPecaAtual() {
    if (tamanhoAtualFila == 0) {
        printf("Fila vazia! Nao ha peca para trocar.\n");
        return 0;
    }
    if (topo == -1) {
        printf("Pilha vazia! Nao ha peca para trocar.\n");
        return 0;
    }
    
    // Troca os valores
    Peca temp = fila[frente];
    fila[frente] = pilha[topo];
    pilha[topo] = temp;
    
    printf("Troca realizada: frente da fila [%c %d] com topo da pilha [%c %d]\n", 
           fila[frente].nome, fila[frente].id, pilha[topo].nome, pilha[topo].id);
    return 1;
}

// Função para troca múltipla: alterna as três primeiras peças da fila com as três peças da pilha.
// Se fila tem >=3 e pilha tem >=3, troca fila[frente], fila[frente+1], fila[frente+2] com pilha[topo], pilha[topo-1], pilha[topo-2].
// Como fila é circular, calcula índices corretamente.
// Retorna 1 se sucesso, 0 se não houver peças suficientes.
int trocaMultipla() {
    if (tamanhoAtualFila < 3) {
        printf("Fila tem menos de 3 pecas! Nao e possivel troca multipla.\n");
        return 0;
    }
    if (topo < 2) {  // Pilha precisa de pelo menos 3 peças (índices 0,1,2)
        printf("Pilha tem menos de 3 pecas! Nao e possivel troca multipla.\n");
        return 0;
    }
    
    // Índices da fila: frente, frente+1, frente+2 (circular)
    int idxFila[3];
    idxFila[0] = frente;
    idxFila[1] = (frente + 1) % TAMANHO_MAX_FILA;
    idxFila[2] = (frente + 2) % TAMANHO_MAX_FILA;
    
    // Índices da pilha: topo, topo-1, topo-2
    int idxPilha[3] = {topo, topo - 1, topo - 2};
    
    // Troca as peças
    for (int i = 0; i < 3; i++) {
        Peca temp = fila[idxFila[i]];
        fila[idxFila[i]] = pilha[idxPilha[i]];
        pilha[idxPilha[i]] = temp;
    }
    
    printf("Troca multipla realizada: 3 primeiras da fila com 3 da pilha.\n");
    return 1;
}

int main() {
    srand(time(NULL));  // Inicializa gerador de números aleatórios
    
    inicializarFila();   // Inicializa fila com 5 peças
    inicializarPilha();  // Inicializa pilha vazia
    
    int opcao;
    while (1) {
        exibirEstado();  // Exibe estado após cada ação
        
        printf("Opcoes disponiveis:\n");
        printf("1 - Jogar peca da frente da fila\n");
        printf("2 - Enviar peca da fila para a pilha de reserva\n");
        printf("3 - Usar peca da pilha de reserva\n");
        printf("4 - Trocar peca da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 pecas da pilha\n");
        printf("0 - Sair\n");
        printf("Opcao escolhida: ");
        scanf("%d", &opcao);
        
        if (opcao == 0) {
            printf("Saindo do jogo...\n");
            break;
        } else if (opcao == 1) {
            jogarPeca();
        } else if (opcao == 2) {
            reservarPeca();
        } else if (opcao == 3) {
            usarPecaReservada();
        } else if (opcao == 4) {
            trocarPecaAtual();
        } else if (opcao == 5) {
            trocaMultipla();
        } else {
            printf("Opcao invalida! Tente novamente.\n");
        }
    }
    
    return 0;
}