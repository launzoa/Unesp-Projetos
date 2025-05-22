#include <bits\stdc++.h>
#include <unistd.h>
#include "header/atendimentos.h"
#include "header/cadastros.h"
using namespace std;

int id_ocorrencia = 1;
FilaAtendimento fila_bombeiro = {NULL, NULL};
FilaAtendimento fila_ambulancia = {NULL, NULL};
FilaAtendimento fila_policia = {NULL, NULL};
int tempo_simulado = 1;
extern Cidadao *tabela_cidadaos[127];


Ocorrencia *criar_ocorrencia(int tempo_atual)
{
    setlocale(LC_ALL, "");
    cout << "/*Cadastro de ocorrência *\\ \n\n";
    Ocorrencia *nova = new Ocorrencia();
    nova->id = id_ocorrencia++;

    cout << "Tipo de serviço: ";
    getline(cin, nova->tipo_servico);
    cout << "Descrição: ";
    getline(cin, nova->descricao);
    cout << "Bairro: ";
    getline(cin, nova->bairro);
    
    nova->tempo_chegada = tempo_atual;
    nova->prox = NULL;
    
    return nova;
}


void enfileirar(FilaAtendimento *fila, Ocorrencia *nova)
{
    if(fila->inicio == NULL)
    {
        fila->inicio = nova;
        fila->fim = nova;
    }
    else
    {
        fila->fim->prox = nova;
        fila->fim = nova;
    }
}


Ocorrencia *desenfileirar(FilaAtendimento *fila)
{

    if(fila->inicio == NULL) return NULL;

    Ocorrencia *atual = fila->inicio;
    fila->inicio = fila->inicio->prox;

    if(fila->inicio == NULL) fila->fim = NULL;

    atual->prox = NULL;
    
    return atual;
}


void listar_fila(FilaAtendimento *fila, string nome_fila)
{
    cout << "=== " << nome_fila << " ===\n\n";

    if(fila->inicio == NULL)
    {
        cout << "Fila vazia!\n";
        return ;
    }

    Ocorrencia *atual = fila->inicio;

    while(atual != NULL)
    {
        cout << "ID: " << atual->id << "\n";
        cout << "Tipo: " << atual->tipo_servico << "\n";
        cout << "Descrição: " << atual->descricao << "\n";
        cout << "Bairro: " << atual->bairro << "\n";
        cout << "Chegada (tempo simulado): " << atual->tempo_chegada << "\n";
        cout << "--------------------------\n";

        atual = atual->prox;
    }
    cout << "\n";

    return ;
}


bool login(string *nome_login)
{
    string nome, cpf;
    
    cout << "Para acessar a tela de atendimentos, solicitamos que o usuário se identifique.\n\n";
    cout << "CPF do solicitante: ";
    getline(cin, cpf);
    cout << "\nNome: ";
    getline(cin, nome);

    int idx = hash_map(cpf);
    Cidadao *atual = tabela_cidadaos[idx];
    if(atual == NULL) 
    {
        cout << "\nNão foi encontrado em nossos registros esse cadastro.\n";
        system("pause");
        return false;
    }

    while(atual->nome != nome)
    {
        if(atual->prox == NULL)
        {
            cout << "\nNão foi encontrado em nossos registros esse cadastro.\n";
            system("pause");
            return false;
        }
        atual = atual->prox;
    }
    
    *nome_login = atual->nome;

    return true;
}













