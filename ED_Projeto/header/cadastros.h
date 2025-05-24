#ifndef CADASTROS_H
#define CADASTROS_H
using namespace std;
#include "atendimentos.h"

// Estruturas
struct estr_bairro
{
    int id;
    string nome;
    struct estr_bairro *prox;
    struct estr_unidade *lista_unidades;
};
typedef struct estr_bairro Bairro;

struct estr_cidadao
{
    string cpf;
    string nome;
    string email;
    string endereco;
    string bairro;
    struct estr_cidadao *prox;
    struct estr_ocorrencia *historico;
};
typedef struct estr_cidadao Cidadao;

struct estr_unidade
{
    int id;
    string tipo;
    string nome;
    string bairro;
    struct estr_unidade *prox;
};
typedef struct estr_unidade UnidadeServico;

// Inicialização
void inicializar_tabelas();

// Cadastros
void cadastrar_cidadaos();
void cadastrar_unidades();
void cadastrar_bairros(UnidadeServico *novo);

// Impressão
void listar_bairros();
void listar_cidadaos();
void listar_unidades_por_bairros(string nome);

// Criação
Bairro *criar_bairro(string nome);
Cidadao *criar_cidadao(); 
UnidadeServico *criar_unidade();

// Busca
Bairro *buscar_bairro(string nome);
Cidadao *buscar_cidadao(string cpf);

// Funções
int hash_map(string valor);


#endif 