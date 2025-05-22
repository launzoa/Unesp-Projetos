#ifndef INTERFACES_H
#define INTERFACES_H
using namespace std;

// Limpeza
void limpar_tela();

// Tela
void tela_principal();
void tela_cadastro();
void tela_atendimentos();
void tela_listar();

// Interface - Menu
void menu_principal(int op);
void menu_cadastro(int op);
void menu_listar(int op);
void menu_atendimentos(int op);

#endif 