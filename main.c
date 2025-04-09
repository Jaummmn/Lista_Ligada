#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct Pessoa {
    char *nome;
    int idade;
    float altura;
    struct Pessoa *next;
} Pessoa;

typedef struct {
    Pessoa *inicio, *fim;
    int tamanho;
} Lista;

void InserirInicioLista(Lista *lista, char *nome, int idade, float altura)
{
    Pessoa *novaPessoa = (Pessoa*)malloc(sizeof(Pessoa));
    novaPessoa->nome = strdup(nome); // Aloca memória para o nome
    novaPessoa->altura = altura;
    novaPessoa->idade = idade;

    if (lista->inicio == NULL) {
        novaPessoa->next = NULL;
        lista->inicio = novaPessoa;
        lista->fim = novaPessoa;
    } else {
        novaPessoa->next = lista->inicio;
        lista->inicio = novaPessoa;
    }
    lista->tamanho++;
    printf("Elemento inserido com sucesso no inicio \n");
}

void InserirMeioLista(Lista *lista, char *nome, int idade, float altura) {

    printf("\nTamanho da lista: %d\n", lista->tamanho);
    Pessoa *novaPessoa = (Pessoa*)malloc(sizeof(Pessoa));
    novaPessoa->nome = strdup(nome); // Aloca memória para o nome
    novaPessoa->altura = altura;
    novaPessoa->idade = idade;

    if (lista->inicio == NULL)// A lista deve ter mais de um elemento
    {
        lista->inicio = novaPessoa;
        lista->fim = novaPessoa;
        novaPessoa->next = NULL;
    }
    else
    {
        novaPessoa->next = lista->inicio->next;
        lista->inicio->next = novaPessoa;
    }
    lista->tamanho++;
    printf("Elemento inserido com sucesso no inicio \n");
}


void InserirFimLista(Lista *lista, char *nome, int idade, float altura)
{
    Pessoa *novaPessoa = (Pessoa*)malloc(sizeof(Pessoa));
    novaPessoa->nome = strdup(nome); // Aloca memória para o nome
    novaPessoa->altura = altura;
    novaPessoa->idade = idade;
    novaPessoa->next = NULL;

    if(lista->inicio == NULL) {
        lista->inicio = novaPessoa;
        lista->fim = novaPessoa;
    }
    else
    {
        lista->fim->next = novaPessoa;
        lista->fim = novaPessoa; // Atualiza o ponteiro do fim
    }
    lista->tamanho++;
    printf("Elemento inserido com sucesso no final \n");
}
///funcao para exibir todo conteudo da Lista
void ExibirLista(Lista *lista)
{


    Pessoa *inicio = lista->inicio;
    printf("\nTamanho da lista: %d\n", lista->tamanho);

    while (inicio != NULL)
    {
        printf(" %s", inicio->nome);

        printf("->");

        inicio = inicio->next;
    }

printf("null\n");

}

void DeletarPessoa(Lista *lista, char *nomeRemover) {
    Pessoa *inicio = lista->inicio;
    Pessoa *noRemover = NULL;

    // Verifica se a lista está vazia
    if (inicio == NULL) return;

    // Verifica se o primeiro elemento deve ser removido
    if (strcmp(inicio->nome, nomeRemover) == 0) {
        noRemover = inicio;
        lista->inicio = inicio->next;

        // Atualiza o final da lista se necessário
        if (lista->inicio == NULL) {
            lista->fim = NULL;
        }
    } else {
        // Busca o elemento no meio/final da lista
        Pessoa *anterior = inicio;
        while (anterior->next != NULL &&
               strcmp(anterior->next->nome, nomeRemover) != 0) {
            anterior = anterior->next;
        }

        // Verifica se o elemento foi encontrado
        if (anterior->next != NULL) {
            noRemover = anterior->next;
            anterior->next = noRemover->next;

            // Atualiza o final da lista se necessário
            if (anterior->next == NULL) {
                lista->fim = anterior;
            }
        }
    }

    // Libera a memória do nó removido
    if (noRemover) {
        free(noRemover);
        lista->tamanho--;
    }
    printf("removido com sucesso %s \n",nomeRemover);
}

int main() {
    Lista pessoas = {NULL, NULL, 0};
    char nome[100], nomeRemover[100]; // Aloca espaço para o nome
    int idade;
    float altura;

    int opcMenu = 0;
    while(1) {

        puts("-----Menu------");
        puts("1 - Inserir no inicio da lista");
        puts("2 - Inserir no fim da lista");
        puts("3 - Deletar da lista");
        puts("4 - Mostrar lista");
        puts("5 - Inserir meio da lista");
        puts("6 - Sair");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcMenu);

        switch(opcMenu) {
            case 1:
                puts("Inserir no inicio");
                printf("Nome: ");
                scanf("%s", nome);
                printf("Idade: ");
                scanf("%d", &idade);
                printf("Altura: ");
                scanf("%f", &altura);
                InserirInicioLista(&pessoas, nome, idade, altura);
                break;
            case 2:
                puts("Inserir no fim");
                printf("Nome: ");
                scanf("%s", nome);
                printf("Idade: ");
                scanf("%d", &idade);
                printf("Altura: ");
                scanf("%f", &altura);
                InserirFimLista(&pessoas, nome, idade, altura);
                break;
            case 3:
                puts("Deletar");
                printf("Nome para remover: ");
                scanf("%s", nomeRemover);
                DeletarPessoa(&pessoas, nomeRemover);
                break;
            case 4:
                puts("Mostrar lista");
                ExibirLista(&pessoas);
                break;
            case 5:
                puts("Inserir no meio");
                printf("Nome: ");
                scanf("%s", nome);
                printf("Idade: ");
                scanf("%d", &idade);
                printf("Altura: ");
                scanf("%f", &altura);
                InserirMeioLista(&pessoas,nome,idade,altura);
            break;
            case 6:
                puts("Saindo...");
                exit(0);
                break;
            default:
                puts("Opção invalida");
        }
        // Pausa para visualização
        printf("Pressione Enter para continuar...");
        getchar();
    }
    return 0;
}