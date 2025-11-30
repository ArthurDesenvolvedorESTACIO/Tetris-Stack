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

// Definição da fila circular.
// Usamos um array para armazenar as peças, com índices para frente e trás.
// Tamanho máximo fixo para simplicidade (10, mas inicializamos com 5).
#define TAMANHO_MAX 10
Peca fila[TAMANHO_MAX];
int frente = 0;  // Índice da frente da fila
int tras = 0;    // Índice do trás da fila (próxima posição para inserir)
int tamanhoAtual = 0;  // Número de elementos na fila
int idGlobal = 0;  // Contador global para ids únicos

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
// Isso configura o estado inicial do jogo.
void inicializarFila() {
    for (int i = 0; i < 5; i++) {
        Peca p = gerarPeca();
        fila[tras] = p;
        tras = (tras + 1) % TAMANHO_MAX;  // Avança trás circularmente
        tamanhoAtual++;
    }
}

// Função para exibir o estado atual da fila.
// Percorre a fila da frente para trás, imprimindo nome e id de cada peça.
// Mostra a fila no formato [Nome ID] [Nome ID] ...
void exibirFila() {
    printf("Fila de pecas\n");
    if (tamanhoAtual == 0) {
        printf("Fila vazia\n");
        return;
    }
    int i = frente;
    for (int count = 0; count < tamanhoAtual; count++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAMANHO_MAX;
    }
    printf("\n");
}

// Função para jogar uma peça (dequeue).
// Remove a peça da frente da fila, se não estiver vazia.
// Atualiza frente e tamanhoAtual.
// Retorna 1 se sucesso, 0 se fila vazia.
int jogarPeca() {
    if (tamanhoAtual == 0) {
        printf("Fila vazia! Nao ha peca para jogar.\n");
        return 0;
    }
    Peca removida = fila[frente];
    frente = (frente + 1) % TAMANHO_MAX;  // Avança frente
    tamanhoAtual--;
    printf("Peca jogada: [%c %d]\n", removida.nome, removida.id);
    return 1;
}

// Função para inserir uma nova peça (enqueue).
// Gera uma nova peça e adiciona ao final da fila, se não estiver cheia.
// Atualiza tras e tamanhoAtual.
// Retorna 1 se sucesso, 0 se fila cheia.
int inserirPeca() {
    if (tamanhoAtual >= TAMANHO_MAX) {
        printf("Fila cheia! Nao e possivel inserir nova peca.\n");
        return 0;
    }
    Peca nova = gerarPeca();
    fila[tras] = nova;
    tras = (tras + 1) % TAMANHO_MAX;  // Avança tras
    tamanhoAtual++;
    printf("Nova peca inserida: [%c %d]\n", nova.nome, nova.id);
    return 1;
}

int main() {
    srand(time(NULL));  // Inicializa gerador de números aleatórios para gerarPeca
    
    inicializarFila();  // Inicializa com 5 peças
    
    int opcao;
    while (1) {
        exibirFila();  // Exibe fila após cada ação
        
        printf("\nOpcoes de acao:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        if (opcao == 0) {
            printf("Saindo do jogo...\n");
            break;
        } else if (opcao == 1) {
            jogarPeca();
        } else if (opcao == 2) {
            inserirPeca();
        } else {
            printf("Opcao invalida! Tente novamente.\n");
        }
    }
    
    return 0;
}