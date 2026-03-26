
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
typedef struct 
{
    char nome[100]; 
    char numero[100]; 
    int idade; 
} Contato; 
Contato* adicionarContato(Contato *agenda, int *tamanho)
{
        
        
        char continuar = 's';
        while (continuar == 's' || continuar == 'S'){
            Contato *temp = realloc(agenda, (*tamanho + 1) * sizeof(Contato));
            if (temp == NULL) {
            printf("Erro de memoria\n");
            return agenda;
        }
        agenda = temp;
        printf("nome: "); 
        scanf(" %[^\n]", agenda[*tamanho].nome);
        printf("numero: "); 
        scanf("%s", agenda[*tamanho].numero);
        printf("idade: "); 
        scanf("%d", &agenda[*tamanho].idade);
        (*tamanho)++;
        printf("Continuar? (s/n): "); 
        scanf(" %c", &continuar); 
         
        if (continuar == 's' || continuar == 'S')
        {
            1; 
        }else if (continuar == 'n' || continuar == 'N' )
        {
            break; 
        }else
        {
            printf("caracter invalido"); 
            scanf(" %c", &continuar); 
        }
        }
    return agenda;
    
}
Contato* removerContato(Contato *agenda, int *tamanho)
{
    printf("Qual contato voce deseja remover?: ");
    int escolha; 
    scanf("%d", &escolha); 
    if (escolha < 0 || escolha >= *tamanho) {
        printf("Escolha invalida.\n");
        return agenda;
    }
    for (int i = escolha; i < *tamanho - 1; i++) {
        agenda[i] = agenda[i + 1];
    }

    (*tamanho)--;

    agenda = realloc(agenda, (*tamanho) * sizeof(Contato));

    return agenda;

    
}
void listarContatos(Contato *agenda, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("\nContato %d:\n", i);
        printf("Nome: %s\n", agenda[i].nome);
        printf("Numero: %s\n", agenda[i].numero);
        printf("Idade: %d\n", agenda[i].idade);
    }
}
void salvarContatos(Contato *agenda, int tamanho) {
    FILE *f = fopen("contatos.bin", "wb");

    if (f == NULL) {
        printf("ERRO: nao conseguiu criar arquivo!\n");
        return;
    }

    fwrite(&tamanho, sizeof(int), 1, f);
    fwrite(agenda, sizeof(Contato), tamanho, f);

    fclose(f);

    printf("Arquivo salvo!\n"); 
}
Contato* carregarContatos(int *tamanho) {
    FILE *f = fopen("contatos.bin", "rb");

    if (f == NULL) {
        *tamanho = 0;
        return NULL;
    }

    if (fread(tamanho, sizeof(int), 1, f) != 1) {
        fclose(f);
        *tamanho = 0;
        return NULL;
    }

    if (*tamanho == 0) {
        fclose(f);
        return NULL;
    }

    Contato *agenda = malloc((*tamanho) * sizeof(Contato));

    if (agenda == NULL) {
        fclose(f);
        return NULL;
    }

    fread(agenda, sizeof(Contato), *tamanho, f);

    fclose(f);

    return agenda;
}
int main()
{
    Contato *agenda = NULL;
    int tamanho = 0; 
    agenda = carregarContatos(&tamanho);
    int digito; 
    do {
        printf("\n===== MENU =====\n");
        printf("1- Adicionar Contato\n2- Remover contato\n3- Mostrar Contatos\n4- Sair\n");
        printf("\n================\n");
        scanf("%d", &digito);
        printf("\n"); 
        if (digito == 1)
        {
        agenda = adicionarContato(agenda, &tamanho); 
        }else if (digito == 3)
        {
        listarContatos(agenda, tamanho);
        }else if(digito == 2)
        {
        agenda = removerContato(agenda, &tamanho);
        }
    } while (digito != 4);
    salvarContatos(agenda, tamanho);
    free (agenda);

    return 0;
}
