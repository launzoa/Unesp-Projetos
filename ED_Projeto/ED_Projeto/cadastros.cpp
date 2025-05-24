// ======================
// ARQUIVO: cadastro.cpp
// FUNCIONALIDADES:
//      Lida com as principais funcionalidades dos cidadãos, bairros e unidades de serviço. Encontramos nesse
//      arquivo algumas funcionalidades que estão relacionadas a esses 'objetos'. Dentre elas, principalmente
//      temos funções, como: cadastro e criação, listagem, busca e funcionalidades consequentes.   
// ======================

// Bibliotecas usadas
#include <bits\stdc++.h>
#include "header/cadastros.h" 
using namespace std;
#define N 127

// Iteradores globais para ID 
int id_bairro = 1;
int id_unidade = 1;

// Tabelas hash globais
Cidadao *tabela_cidadaos[N];
Bairro *tabela_bairros[N];
UnidadeServico *tabela_unidades[N];




// Função para inicializar as tabelas hash com NULL
void inicializar_tabelas()
{
    for (int i = 0; i < N; i++) 
    {
        tabela_bairros[i] = NULL;
        tabela_cidadaos[i] = NULL;
        tabela_unidades[i] = NULL;
    }
}



// ----- CADASTRO ----- // ----- Funções de cadastro de 'objetos'


/*
    A função cadastra o bairro na sua respectiva tabela-hash. 
    Faz lista cruzada entre o bairro e unidades de serviços contidas no bairro.
    Funções associadas: buscar_bairro(), criar_bairro().
*/
void cadastrar_bairros(UnidadeServico *novo)
{
    Bairro *novo_bairro = buscar_bairro(novo->bairro);
    if(novo_bairro != NULL)
    {
        while(novo_bairro->lista_unidades != NULL) 
        {
            novo_bairro->lista_unidades = novo_bairro->lista_unidades->prox; 
        }    
        novo_bairro->lista_unidades = novo;
    }
    else
    {
        novo_bairro = criar_bairro(novo->bairro);
        while(novo_bairro->lista_unidades != NULL)
        {
            novo_bairro->lista_unidades = novo_bairro->lista_unidades->prox; 
        }
        novo_bairro->lista_unidades = novo;

        int idx = hash_map(novo_bairro->nome);
        tabela_bairros[idx] = novo_bairro;
    }
}


/*
    Cadastra um novo cidadão na sua respectiva tabela-hash.
    Trata possíveis colisões na tabela-hash por lista encadeada.  
*/
void cadastrar_cidadaos()
{

    Cidadao *novo = criar_cidadao();
    novo->prox = NULL;
    int idx = hash_map(novo->cpf);

    if (tabela_cidadaos[idx] == NULL)
    {
        tabela_cidadaos[idx] = novo;
    } 
    else
    {
        Cidadao *atual = tabela_cidadaos[idx];
        while(atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = novo;
    }

    return ;
}


/*
    Cadastra uma nova unidade de serviço a sua respectiva tabela-hash.
    Funções associadas: criar_unidade(), cadastrar_bairros("cadastro.cpp", 48).
*/
void cadastrar_unidades()
{
    setlocale(LC_ALL, " ");

    UnidadeServico *novo = criar_unidade();
    cadastrar_bairros(novo);

    int idx = hash_map(novo->nome);
    UnidadeServico *atual = tabela_unidades[idx];
    while(atual != NULL)
    {
        atual = atual->prox;
    } 
    atual = novo;
    
    return ;
}



// ----- LISTAGEM ----- // ----- Funções de impressão 


//  Faz a listagem e impressão do conteúdo da tabela-hash dos bairros.
void listar_bairros()
{
    cout << "/* Tabela Hash de Bairros */\n\n";

    for (int i = 0; i < N; i++) 
    {
        if (tabela_bairros[i] != NULL) 
        {
            cout << "Hash[" << i << "]: \n";
            Bairro *atual = tabela_bairros[i];
            while (atual != NULL) 
            {
                cout << atual->id << "\n";
                cout << atual->nome << "\n";
                UnidadeServico *unidade = atual->lista_unidades;
                while(unidade != NULL)
                {
                    cout << unidade->tipo << " -> ";
                    unidade = unidade->prox;
                } 
                cout << " NULL\n";
                atual = atual->prox;
                cout << "------------------------------------\n\n";
            }
        }
    }
    cout << "\n";
    return ;
}



//  Faz a listagem e impressão do conteúdo da tabela-hash dos cidadãos.
void listar_cidadaos()
{
    cout << "/* Tabela Hash de Cidadãos */\n\n";
    for (int i = 0; i < N; i++) 
    {
        if (tabela_cidadaos[i] != NULL) 
        {
            cout << "Hash[" << i << "]:\n";
            Cidadao *atual = tabela_cidadaos[i];
            while (atual != NULL) 
            {
                cout << "  CPF: " << atual->cpf << "\n";
                cout << "  Nome: " << atual->nome << "\n";
                cout << "  Email: " << atual->email << "\n";
                cout << "  Endereço: " << atual->endereco << "\n";
                cout << "  Bairro: " << atual->bairro << "\n";
                cout << "  --------------------------\n";
                atual = atual->prox;
            }
        }
    }
    cout << "\n";

    return ;
}



//  Faz a listagem das unidades de serviço associadas a um determinado bairro.
void listar_unidades_por_bairros(string nome)
{
    Bairro *bairro = buscar_bairro(nome);

    if(bairro == NULL) 
    {
        cout << "Bairro não encontrado!\n";
        return ;
    }

    cout << "Unidades de serviço no bairro " << nome << ":\n\n";
    UnidadeServico *atual = bairro->lista_unidades;

    if(atual == NULL) 
    {
        cout << "Nenhuma unidade registrada nesse bairro!\n";
        return ;
    }

    while(atual != NULL)
    {
        cout << " - [" << atual->tipo << "] " << atual->nome << "\n";
        atual = atual->prox;
    }

    return ;
}



// ----- CRIAÇÃO ----- // ----- Cria os 'objetos' (entrada de dados).


//  Cria o 'objeto' bairro
Bairro *criar_bairro(string nome)
{
    Bairro *novo = new Bairro();
    novo->id = id_bairro++;
    novo->nome = nome;
    novo->prox = NULL;
    novo->lista_unidades = NULL;

    return novo;
}


//  Cria o 'objeto' cidadão
Cidadao *criar_cidadao()
{
    setlocale(LC_ALL, " ");

    Cidadao *novo = new Cidadao;

    cout << "/* Cadastrar Cidadão: *\\\n\n";
    
    cout << "CPF: ";
    getline(cin, novo->cpf);
    
    cout << "\nNome: ";
    getline(cin, novo->nome);
    
    cout << "\nEmail: ";
    getline(cin, novo->email);
    
    cout << "\nEndereço: ";
    getline(cin, novo->endereco);
    
    cout << "\nBairro: ";
    getline(cin, novo->bairro);

    novo->historico = NULL;
    
    return novo;
}



//  Cria o 'objeto' unidade
UnidadeServico *criar_unidade()
{
    setlocale(LC_ALL, "");
    UnidadeServico *novo = new UnidadeServico();

    cout << "/* Cadastrar Unidade de Serviço: *\\\n\n";
    novo->id = id_unidade++;
    cout << "Tipo de serviço: ";
    getline(cin, novo->tipo);
    cout << "\nNome: ";
    getline(cin, novo->nome);
    cout << "\nBairro: ";
    getline(cin, novo->bairro);

    return novo;
}



// ----- BUSCA ----- // ----- Faz a busca dos seus respectivos 'objetos'.

//  Busca e retorna um determinado bairro baseado em seu nome. Retorna NULL caso não encontre o bairro.
Bairro *buscar_bairro(string nome)
{
    int idx = hash_map(nome);
    Bairro *atual = tabela_bairros[idx];

    while(atual != NULL)
    {
        if(atual->nome == nome) return atual;
        atual = atual->prox;
    }
    
    return NULL;
}


//  Busca e retorna um determinado cidadão baseado em seu cpf. Retorna NULL caso não encontre o cidadão.
Cidadao *buscar_cidadao(string cpf)
{
    int idx = hash_map(cpf);
    Cidadao *atual = tabela_cidadaos[idx];

    while(atual != NULL)
    {
        if(atual->cpf == cpf) return atual;
        atual = atual->prox;
    }
    
    return NULL;
}



// ----- FUNCIONALIDADES ----- // ----- Funções e estruturas de dados.

/*
    Função que retorna um determinado índice que vai ser usado para acessar a respectiva tabela-hash.
    Para a implementação dessa estrutura de dados, é feito uma soma total baseado no valor da tabela ASCII resultante
    de uma determinada string. Por fim, esse valor sofre uma circulação circular do número primo 127 e por fim é 
    retornado o índice 'exclusivo' da tabela-hash.   
*/
int hash_map(string valor)
{
    int soma = 0;
    for(int i = 0; i < valor.length(); i++)
    {
        soma += valor[i];
    }

    return soma % N;
}










