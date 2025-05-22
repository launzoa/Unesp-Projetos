#include <bits\stdc++.h>
#include "header/cadastros.h"
#include "header/interfaces.h"
#include "header/atendimentos.h"

using namespace std;

extern FilaAtendimento fila_ambulancia;
extern FilaAtendimento fila_bombeiro;
extern FilaAtendimento fila_policia;
extern int tempo_simulado;



void limpar_tela()
{
    system("cls");
    return ;
}

// Telas

void tela_principal()
{   
    setlocale(LC_ALL, "");
    int op;
    
    do{
        cout << "/* Simulador de Atendimentos de Emergências *\\ \n";
        cout << "(1) - Cadastrar\n";
        cout << "(2) - Listar\n";
        cout << "(3) - Atendimento\n";
        cout << "(4) - Sair\n";
        cout << "\n";
        cout << "Opção: ";
        cin >> op;
        cin.ignore();
        menu_principal(op);
        limpar_tela();

    } while(op != 4);

    return ;
}


void tela_cadastro()
{
    setlocale(LC_ALL, "");
    int op;
    do{
        limpar_tela();

        cout << "/* Cadastrar *\\ \n";
        cout << "(1) - Cadastrar Bairros\n";
        cout << "(2) - Cadastrar Cidadãos\n";
        cout << "(3) - Cadastrar Unidades de serviços\n";
        cout << "(4) - Voltar\n";
        cout << "\n";
        cout << "Opção: ";
    
        cin >> op;
        cin.ignore();
        menu_cadastro(op);
        limpar_tela();

    } while (op != 4);

    return ;
}


void tela_listar()
{
    setlocale(LC_ALL, "");

    int op;
    do{
        limpar_tela();

        cout << "/* Listar *\\ \n";
        cout << "(1) - Listar Bairros\n";
        cout << "(2) - Listar Cidadãos\n";
        cout << "(3) - Listar Unidades de serviços\n";
        cout << "(4) - Voltar\n";
        cout << "\n";
        cout << "Opção: ";
    
        cin >> op;
        cin.ignore();

        menu_listar(op);
        limpar_tela();

    } while (op != 4);

    return ;
}


void tela_atendimentos()
{
    setlocale(LC_ALL, "");

    limpar_tela();
    string nome_login;
    if(!login(&nome_login)) return ;

    int op;

    do
    {
        limpar_tela();
        cout << "/* Painel de Atendimentos */\n";
        cout << "Bem vindo, " << nome_login << "\n\n";
        cout << "Tempo atual simulado: " << tempo_simulado << "\n\n";
        cout << "(1) - Registrar nova ocorrência\n";
        cout << "(2) - Visualizar fila de atendimentos\n";
        cout << "(3) - Simular próxima unidade de tempo (1 atendimento)\n";
        cout << "(4) - Voltar\n";
        cout << "Entre com a opção: ";
        cin >> op;
        cin.ignore();

        limpar_tela();
        
        menu_atendimentos(op);

    } while (op != 4);
    

    return ;
}



// Menus

void menu_principal(int op)
{
    switch(op)
    {
        case 1:
            tela_cadastro();
        
        break;

        case 2:
            tela_listar();

        break;

        case 3:
            tela_atendimentos();

        break;

        default:
        break;
    }
    
    return ;
}


void menu_cadastro(int op)
{
    limpar_tela();
    switch(op)
    {
        case 1:
            cadastrar_bairros();

        break;

        case 2:
            cadastrar_cidadaos();

        break;

        case 3:
            cadastrar_unidades();

        break;

        default:
        break;
    }
    return ;
}


void menu_listar(int op)
{
    limpar_tela();
    switch(op)
    {
        case 1:
            listar_bairros();
            system("pause");

        break;
        
        case 2:
            listar_cidadaos();
            system("pause");

        break;
        
        case 3:
        
        break;

        default:
        break;
    }
    return ;
}


void menu_atendimentos(int op)
{
    switch(op)
    {
        case 1:
        {
            Ocorrencia *nova = criar_ocorrencia(tempo_simulado);
            if(nova->tipo_servico == "bombeiro")
            {
                enfileirar(&fila_bombeiro, nova);
            }
            else if(nova->tipo_servico == "ambulancia")
            {
                enfileirar(&fila_ambulancia, nova);
            }
            else if(nova->tipo_servico == "policia")
            {
                enfileirar(&fila_policia, nova);
            }
            else
            {
                cout << "Tipo de serviço inválido! Ocorrência não pode ser completada!\n";
                delete nova;
            }
            system("pause");
            break;
        }

        case 2:
        {
            listar_fila(&fila_bombeiro, "Bombeiros");
            listar_fila(&fila_ambulancia, "Ambulância");
            listar_fila(&fila_policia, "Polícia");
            system("pause");
            break;
        }
        case 3:
        {
            tempo_simulado++;

            if(fila_bombeiro.inicio)
            {
                Ocorrencia *atendida = desenfileirar(&fila_bombeiro);
                cout << "[Bombeiro] Atendendo ocorrência: " << atendida->descricao << "\n";
                delete(atendida);
            }

            if(fila_ambulancia.inicio)
            {
                Ocorrencia *atendida = desenfileirar(&fila_ambulancia);
                cout << "[Ambulância] Atendendo ocorrência: " << atendida->descricao << "\n";
                delete(atendida);
            }

            if(fila_policia.inicio)
            {
                Ocorrencia *atendida = desenfileirar(&fila_policia);
                cout << "[Polícia] Atendendo ocorrência: " << atendida->descricao << "\n";
                delete(atendida);
            }
            system("pause");
            break;
        }

        default:
        break;
    }
}


