#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Empresa{
    char nome[40];
    int cnpj;
}empresa;

typedef struct Bebida{
    int codigo, quantidadeEstoque;
    char nome[40];
    float conteudoMl, valor, teorAlcoolico;
    struct bebida *anterior, *proximo;
}bebida;

typedef struct SentinelaBebida
{
    bebida *primeiro, *ultimo;
}sentinelaBebida;

typedef struct Cliente{
    int codigo, cpf, idade, inadimplente;
    char nome[40];
    struct Cliente *anterior, *proximo;
}cliente;

typedef struct SentinelaCliente{
    cliente *primeiro, *ultimo;
}sentinelaCliente;

void iniciarSentinelas(sentinelaBebida *sBebida, sentinelaCliente *sCliente){
    sBebida->primeiro = NULL;
    sBebida->ultimo = NULL;

    sCliente->primeiro = NULL;
    sCliente->ultimo = NULL;
}

int verificaExisteBebida(sentinelaBebida *sBebida, int codigo){
    bebida *aux;

    if (sBebida->primeiro == NULL)
    {
        return 0;
    }
    
    for(aux = sBebida->primeiro; aux != NULL; aux = aux->proximo){
        if (aux->codigo == codigo)
        {
            return 1;
        }
    }

    return 0;
}

int retornaTeorAlcoolico(sentinelaBebida *sBebida, int codigo){
    bebida *aux;
    
    for(aux = sBebida->primeiro; aux != NULL; aux = aux->proximo){
        if (aux->codigo == codigo)
        {
            return aux->teorAlcoolico;
        }
    }
}

int retornaIdadeCliente(sentinelaCliente *sCliente, int cpf){
    cliente *aux;
    
    for(aux = sCliente->primeiro; aux != NULL; aux = aux->proximo){
        if (aux->cpf == cpf)
        {
            return aux->idade;
        }
    }
}

int verificaExisteCliente(sentinelaCliente *sCliente, int cpf){
    cliente *aux;

    if (sCliente->primeiro == NULL)
    {
        return 0;
    }
    
    for(aux = sCliente->primeiro; aux != NULL; aux = aux->proximo){
        if (aux->cpf == cpf)
        {
            return 1;
        }
    }

    return 0;
}

empresa cadastrarEmpresa(empresa bodega){
    printf("----Cadastre sua Empresa----\n");
    printf("Nome fantasia: ");
    scanf("%s", &bodega.nome);

    printf("CNPJ(somente números): ");
    scanf("%d", &bodega.cnpj);
    printf("\e[H\e[2J");
    
    return bodega;
}

void cadastrarBebidas(sentinelaBebida *sBebida){
    bebida *drink;
    drink = (bebida *)malloc(sizeof(bebida));

    printf("----Cadastro de Bebidas----\n");

    printf("Código: ");
    scanf("%d", &drink->codigo);

    if (verificaExisteBebida(sBebida, drink->codigo) == 1)
    {
        printf("Bebida Já Cadastrada!\n");
        return "";
    }

    printf("Nome bebida: ");
    scanf("%s", drink->nome);

    printf("Conteúdo em Ml da embalagem: ");
    scanf("%.2f", &drink->conteudoMl);

    printf("Teor alcoólico: ");
    scanf("%f", &drink->teorAlcoolico);

    printf("Quantidade em estoque: ");
    scanf("%d", &drink->quantidadeEstoque);

    printf("Valor de venda: ");
    scanf("%f", &drink->valor);

    drink->anterior = NULL;
    drink->proximo = NULL;

    if (sBebida->primeiro == NULL || sBebida->ultimo == NULL)
    {
        sBebida->primeiro = drink;
        sBebida->ultimo = drink;
    } else {
        sBebida->ultimo->proximo = drink;
        drink->anterior = sBebida->ultimo;
        sBebida->ultimo = drink;
    }    
}

void listarBebidas(sentinelaBebida *sBebida){
    bebida *aux;

    printf("----Estoque de Bebidas----\n");

    if (sBebida->primeiro == NULL)
    {
        printf("Vazio!\n");
        return "";
    }

    for(aux = sBebida->primeiro; aux != NULL; aux = aux->proximo){
        printf("Código: %d\n", aux->codigo);
        printf("Nome: %s\n", aux->nome);
        printf("Conteudo Ml: %f\n", aux->conteudoMl);
        printf("Preço de venda: %f\n", aux->valor);
        printf("Quantidade em Estoque: %d\n", aux->quantidadeEstoque);
        printf("Teor alcoólico: %f\n", aux->teorAlcoolico);
        printf("-----------------------------------------------\n");        
    }
}

void atualizaQuantidadeBebida(sentinelaBebida *sBebida, int codigo, int quantidade){
    bebida *aux;

    for(aux = sBebida->primeiro; aux != NULL; aux = aux->proximo){
        if (aux->codigo == codigo)
        {
            aux->quantidadeEstoque += quantidade;
        }
    }
}

void comprarBebida(sentinelaBebida *sBebida){
    printf("----Comprar Bebida----\n");

    int codigo, quantidade;
    printf("Código da bebida que deseja Comprar: ");
    scanf("%d", &codigo);

    if (verificaExisteBebida(sBebida, codigo) == 0)
    {
        printf("Código Não encontrado!\n");
        return "";
    }
    
    printf("Quantidade: ");
    scanf("%d", &quantidade);

    atualizaQuantidadeBebida(sBebida, codigo, quantidade);

    printf("Compra finalizada com sucesso!\n");
}

int verificarEstoque(sentinelaBebida *sBebida, int codigo, int quantidade){
    bebida *aux;

    for(aux = sBebida->primeiro; aux != NULL; aux = aux->proximo){
        if (aux->codigo == codigo)
        {
            if (aux->quantidadeEstoque < quantidade)
            {
                return 0;
            } else {
                return 1;
            }
        }
    }
}

int retornaInadimplencia(sentinelaCliente *sCliente, int cpf){
    cliente *aux;

    for(aux = sCliente->primeiro; aux != NULL; aux = aux->proximo){
        if (aux->cpf == cpf)
        {
            return aux->inadimplente;
        }
    }
}

void baixaEstoque(sentinelaBebida *sBebida, int codigo, int quantidade){
    bebida *aux;

    for(aux = sBebida->primeiro; aux != NULL; aux = aux->proximo){
        if (aux->codigo == codigo)
        {
            aux->quantidadeEstoque -= quantidade;
        }
    }
}

void atualizaInadimplencia(sentinelaCliente *sCliente, int cpf){
    cliente *aux;

    for(aux = sCliente->primeiro; aux != NULL; aux = aux->proximo){
        if (aux->cpf == cpf)
        {
            aux->inadimplente = 1;
        } 
    }
}

void venderBebida(sentinelaBebida *sBebida, sentinelaCliente *sCliente){
    printf("---Venda de bebidas----\n");

    int cpf, codigo, quantidade, formaPagamento;
    printf("CPF do cliente: ");
    scanf("%d", &cpf);
    if (verificaExisteCliente(sCliente, cpf) == 0)
    {
        printf("CPF não encontrado!\n");
        return "";
    }

    printf("Código bebida: ");
    scanf("%d", &codigo);
    if (verificaExisteBebida(sBebida, codigo) == 0)
    {
        printf("Código não encontrado!\n");
        return "";
    }

    if (retornaTeorAlcoolico(sBebida, codigo) > 0 && retornaIdadeCliente(sCliente, cpf) < 18)
    {
        printf("Negado! É proibida a venda de bebida alcoólica para menores de idade.\n");
        return "";
    }
    
    printf("Quantidade: ");
    scanf("%d", &quantidade);
    if (verificarEstoque(sBebida, codigo, quantidade) == 0)
    {
        printf("Estoque isuficiente!\n");
        return "";
    }
    
    printf("Forma de Pagamento: 1- À vista, 2- Fiado: ");
    scanf("%d", &formaPagamento);

    if (formaPagamento == 2)
    {
        if(retornaInadimplencia(sCliente, cpf) == 1){
            printf("Compra negada! pague o que deve lambaio!\n");
            return "";
        }

        atualizaInadimplencia(sCliente, cpf);

    } else if(formaPagamento != 1){
        printf("Forma de pagamento inválida!\n");
        return "";
    }
    
    baixaEstoque(sBebida, codigo, quantidade);

    printf("Venda finalizada com sucesso!\n");
}

void cadastrarCliente(sentinelaCliente *sCliente){
    cliente *custumer, *aux;
    custumer = (cliente *)malloc(sizeof(cliente));

    printf("----Cadastro de Clientes----\n");

    printf("Código: ");
    scanf("%d", &custumer->codigo);

    printf("Nome cliente: ");
    scanf("%s", custumer->nome);

    printf("CPF: (Apenas números)");
    scanf("%d", &custumer->cpf);

    if (verificaExisteCliente(sCliente, custumer->cpf) == 1)
    {
        printf("Cliente Já Cadastrado!\n");
        return "";
    }

    printf("Idade: ");
    scanf("%d", &custumer->idade);

    custumer->inadimplente = 0;

    custumer->anterior = NULL;
    custumer->proximo = NULL;

    if (sCliente->primeiro == NULL || sCliente->ultimo == NULL)
    {
        sCliente->primeiro = custumer;
        sCliente->ultimo = custumer;
    } else {
        for (aux = sCliente->primeiro; aux != NULL; aux = aux->proximo){
            if (aux->idade >= custumer->idade)
            {
                if (aux == sCliente->primeiro)
                {
                    sCliente->primeiro->anterior = custumer;
                    custumer->proximo = sCliente->primeiro;
                    sCliente->primeiro = custumer;
                    break;
                } else {
                    custumer->anterior = aux->anterior;
                    aux->anterior->proximo = custumer;
                    custumer->proximo = aux;
                    aux->anterior = custumer;
                    break;
                } 
            }
        }

        if (aux == NULL)
        {
            custumer->anterior = sCliente->ultimo;            
            sCliente->ultimo->proximo = custumer;
            sCliente->ultimo = custumer;
        }
        
    }
}

void listarClientes(sentinelaCliente *sCliente){
    cliente *aux;
    printf("----Lista de clientes----\n");

    if (sCliente->primeiro == NULL || sCliente->ultimo == NULL)
    {
        printf("Lista vazia!\n");
        return "";
    }

    for(aux = sCliente->primeiro; aux != NULL; aux = aux->proximo){
        printf("Código: %d\n", aux->codigo);
        printf("Nome: %s\n", aux->nome);
        printf("CPF: %d\n", aux->cpf);
        printf("Idade: %d\n", aux->idade);
        printf("Inadimplente: %d\n", aux->inadimplente);
        printf("-----------------------------------------------\n");
    }
}

void quitarDebitos(sentinelaCliente *sCliente){
    cliente *aux;
    int cpf;

    printf("Digite o CPF do devedor: ");
    scanf("%d", &cpf);

    if (verificaExisteCliente(sCliente, cpf) == 0)
    {
        printf("CPF não cadastrado!\n");
        return "";
    }
    
    for(aux = sCliente->primeiro; aux != NULL; aux = aux->proximo){
        if (aux->cpf == cpf)
        {
            if (aux->inadimplente == 0)
            {
                printf("Cliente não possui pendências.\n");
                return "";
            }
            
            aux->inadimplente = 0;

            printf("Débido quitado.\n");
        }
    }
}

void limparBebida(bebida *primeiro){
    if (primeiro == NULL)
    {
        return "";
    }
    
    limparBebida(primeiro->proximo);
    free(primeiro);     
}

void limparClientes(cliente *primeiro){
    if (primeiro == NULL)
    {
        return "";
    }
    
    limparClientes(primeiro->proximo);
    free(primeiro);     
}

int totalElementos(sentinelaBebida *sCliente, sentinelaBebida *sBebida){
    bebida *aux2;
    cliente *aux;

    int i = 0;

    for(aux = sCliente->primeiro; aux != NULL; aux = aux->proximo){
        i++;
    }

    for(aux2 = sBebida->primeiro; aux2 != NULL; aux2 = aux2->proximo){
        i++;
    }

    return i;
}

void sair(sentinelaBebida *sBebida, sentinelaCliente *sCliente){
    limparBebida(sBebida->primeiro);
    limparClientes(sCliente->primeiro);

    printf("Total de %d elemento(s) deletado(s).\n", totalElementos(sCliente, sBebida));
}

int menu(empresa bodega){
    int op;
    printf("*************BEM VINDO AO BAR %s *** *************\n", bodega.nome);
    printf("************************************************\n");
    printf("1 - Cadastrar bebida\n");
    printf("2 - Mostrar bebidas\n");
    printf("3 - Comprar bebida\n");
    printf("4 - Vender bebida\n");
    printf("5 - Cadastrar cliente\n");
    printf("6 - Mostrar clientes\n");
    printf("7 - Quitar débitos\n");
    printf("8 - Sair do sistema\n");
    printf("============================\n");
    printf("Digite o número da ação desejada: ");
    scanf("%d", &op);

    printf("\e[H\e[2J");
    return op;
}

int main(){    
    sentinelaBebida sBebida;
    sentinelaCliente sCliente;
    iniciarSentinelas(&sBebida, &sCliente);
    
    empresa bodega = cadastrarEmpresa(bodega);
    int op = 0;
    while (op != 8)
    {
        op = menu(bodega);
        switch (op)
        {
        case 1:
            cadastrarBebidas(&sBebida);
            break;
        case 2:
            listarBebidas(&sBebida);
            break;
        case 3:
            comprarBebida(&sBebida);
            break;
        case 4:
            venderBebida(&sBebida, &sCliente);
            break;
        case 5:
            cadastrarCliente(&sCliente);
            break;
        case 6:
            listarClientes(&sCliente);
            break;
        case 7:
            quitarDebitos(&sCliente);
            break;
        case 8:
            sair(&sBebida, &sCliente);
            break;
        default:
            printf("Opção inválida!\n");
            break;
        }
    }
    
    return 0;
}