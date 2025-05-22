#include <bits\stdc++.h>
#include "header/cadastros.h"
using namespace std;

//Inicialização e definição de variáveis
#define N 127
Cidadao *tabela_cidadaos[N];
Bairro *tabela_bairros[N];
int id_bairro = 1;





void inicializar_tabelas()
{
    for (int i = 0; i < N; i++) 
    {
        tabela_bairros[i] = NULL;
        tabela_cidadaos[i] = NULL;
    }
}





void cadastrar_bairros()
{

    Bairro *novo = criar_bairro();
    novo->prox = NULL;
    int idx = hash_map(novo->nome);

    if (tabela_bairros[idx] == NULL)
    {
        tabela_bairros[idx] = novo;
    } 
    else
    {
        Bairro *atual = tabela_bairros[idx];
        while(atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
    
    return;
}

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

void cadastrar_unidades()
{
    setlocale(LC_ALL, " ");

    cout << "Ambulância\n";
    cout << "Bombeiro\n";
    cout << "Polícia\n";

    return ;
}





void listar_bairros()
{
    cout << "/* Tabela Hash de Bairros */\n\n";

    for (int i = 0; i < N; i++) 
    {
        if (tabela_bairros[i] != NULL) 
        {
            cout << "Hash[" << i << "]: ";
            Bairro *atual = tabela_bairros[i];
            while (atual != NULL) 
            {
                cout << atual->nome << " -> ";
                atual = atual->prox;
            }
            cout << "NULL\n";
        }
    }
    cout << "\n";
    return ;
}


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





Bairro *criar_bairro()
{
    cout << "/* Cadastrar Bairro: *\\\n\n";

    Bairro *novo = new Bairro;

    novo->id = id_bairro++;
    cout << "Entre com o nome do bairro: ";
    getline(cin, novo->nome);

    return novo;
}


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

    return novo;
}





int hash_map(string valor)
{
    int soma = 0;
    for(int i = 0; i < valor.length(); i++)
    {
        soma += valor[i];
    }

    return soma % N;
}










