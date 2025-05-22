#ifndef CADASTROS_H
#define CADASTROS_H
using namespace std;

// Estruturas
struct estr_bairro
{
    int id;
    string nome;
    struct estr_bairro *prox;
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
};
typedef struct estr_cidadao Cidadao;


// Inicialização
void inicializar_tabelas();

// Cadastros
void cadastrar_bairros();
void cadastrar_cidadaos();
void cadastrar_unidades();

// Impressão
void listar_bairros();
void listar_cidadaos();

// Criação
Bairro *criar_bairro();
Cidadao *criar_cidadao(); 

// Funções
int hash_map(string valor);


#endif 