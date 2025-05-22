#ifndef ATENDIMENTOS_H
#define ATENDIMENTOS_H
using namespace std;

// Estruturas
struct estr_ocorrencia
{
    int id;
    string tipo_servico;
    string descricao;
    string bairro;
    int tempo_chegada;
    struct estr_ocorrencia *prox;
};
typedef estr_ocorrencia Ocorrencia;

struct estr_fila
{
    Ocorrencia *inicio;
    Ocorrencia *fim;
};
typedef struct estr_fila FilaAtendimento;

// Funções
Ocorrencia *criar_ocorrencia(int tempo_atual);
void enfileirar(FilaAtendimento * fila, Ocorrencia *nova);
Ocorrencia *desenfileirar(FilaAtendimento *fila);
void listar_fila(FilaAtendimento *fila, string nome_fila);
bool login(string *nome_login);

#endif