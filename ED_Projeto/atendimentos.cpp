// ======================
// ARQUIVO: atendimentos.cpp
// FUNCIONALIDADES:
//      Responsavel por gerenciar a simulacao de ocorrencias, enfileiramento, atendimento e historico. Este modulo
//      conecta o cidadao logado com as ocorrencias registradas, organiza por tipo de servico e simula o avanco
//      temporal do sistema.
// ======================

// OBS: Ainda em processo de documentacao... 

#include <bits\stdc++.h>
#include <unistd.h>
#include "header/atendimentos.h"
#include "header/cadastros.h"
using namespace std;
#define N 127

// Fila de atendimento por tipo
FilaAtendimento fila_bombeiro = {NULL, NULL};
FilaAtendimento fila_ambulancia = {NULL, NULL};
FilaAtendimento fila_policia = {NULL, NULL};

// Iterador de id
int id_ocorrencia = 1;

// Tempo simulado do sistema
int tempo_simulado = 1;

// Externos
extern Cidadao *tabela_cidadaos[N];
extern string cpf_login;
extern string nome_login;



// ----- CRIACAO DE OCORRENCIA ----- //


Ocorrencia *criar_ocorrencia(int tempo_atual)
{
    setlocale(LC_ALL, "");
    cout << "/*Cadastro de ocorrencia *\\ \n\n";
    Ocorrencia *nova = new Ocorrencia();
    nova->id = id_ocorrencia++;

    cout << "Tipo de servico: ";
    getline(cin, nova->tipo_servico);
    cout << "\nDescricao: ";
    getline(cin, nova->descricao);
    cout << "\nBairro: ";
    getline(cin, nova->bairro);
    
    nova->cpf = cpf_login;
    Cidadao *atual = buscar_cidadao(cpf_login);
    if(atual->historico == NULL) atual->historico = nova;
    else
    {
        Ocorrencia *temp = atual->historico; 
    
        while(temp->prox != NULL) temp = temp->prox; 
        temp->prox = nova;
    }
    nova->tempo_chegada = tempo_atual;
    nova->prox = NULL;
    
    return nova;
}



// ----- FILA ----- // ----- Funcoes respectivas a fila de ocorrencias.



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



// ----- LISTAGEM ----- // ----- Funcoes de listagem e impressao


void listar_fila(FilaAtendimento *fila, string nome_fila)
{
    setlocale(LC_ALL, "");
    cout << "=== " << nome_fila << " ===\n";

    if(fila->inicio == NULL)
    {
        cout << "Fila vazia!\n\n";
        return ;
    }

    Ocorrencia *atual = fila->inicio;

    while(atual != NULL)
    {
        cout << "ID: " << atual->id << "\n";
        cout << "Tipo: " << atual->tipo_servico << "\n";
        cout << "Descricao: " << atual->descricao << "\n";
        cout << "Bairro: " << atual->bairro << "\n";
        cout << "Chegada (tempo simulado): " << atual->tempo_chegada << "\n";
        cout << "--------------------------\n\n";

        atual = atual->prox;
    }
    cout << "\n";

    return ;
}


void listar_historico(string cpf)
{
    Cidadao *atual = buscar_cidadao(cpf);

    if(atual == NULL) 
    {
        cout << "Cidadao nao encontrado.\n";
        return ;
    }

    if(atual->historico == NULL) 
    {
        cout << "Cidadao sem nenhuma ocorrencia no historico.\n";
        return ;
    }

    Ocorrencia* temp = atual->historico;
    cout << "Historico de ocorrencias de " << atual->nome << ":\n";
    
    
    while (temp != NULL) 
    {
        cout << "ID: " << temp->id << " | " << temp->tipo_servico;
        cout << " | " << temp->descricao;
        cout << " | Tempo: " << temp->tempo_chegada << "\n";
        temp = temp->prox;
    }


    return ;
}



// ----- LOGIN DO USUARIO ----- //


 
bool login(string *nome_login, string *cpf_login)
{
    setlocale(LC_ALL, "");
    string nome, cpf;
    
    cout << "Para acessar a tela de atendimentos, solicitamos que o usuario se identifique.\n\n";
    cout << "CPF do solicitante: ";
    getline(cin, cpf);
    cout << "\nNome: ";
    getline(cin, nome);

    int idx = hash_map(cpf);
    Cidadao *atual = tabela_cidadaos[idx];
    if(atual == NULL) 
    {
        cout << "\nNao foi encontrado em nossos registros esse cadastro.\n";
        system("pause");
        return false;
    }

    while(atual->nome != nome)
    {
        if(atual->prox == NULL)
        {
            cout << "\nNao foi encontrado em nossos registros esse cadastro.\n";
            system("pause");
            return false;
        }
        atual = atual->prox;
    }
    
    *nome_login = atual->nome;
    *cpf_login = atual->cpf;

    return true;
}













