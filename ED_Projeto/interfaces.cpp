// ======================
// ARQUIVO: interfaces.cpp
// FUNCIONALIDADES:
//      Responsavel por controlar a interface textual do sistema. Contem os menus e a logica de navegacao entre as telas
//      principais, incluindo: tela principal, telas de cadastro, listagem e emergencia. Tambem contem os menus que
//      direcionam para as respectivas funcionalidades em outros modulos.
// ======================

#include <bits\stdc++.h>
#include "header/cadastros.h"
#include "header/interfaces.h"
#include "header/atendimentos.h"

using namespace std;

// Inicializacao e declaracao de variaveis reusaveis.
extern FilaAtendimento fila_ambulancia;
extern FilaAtendimento fila_bombeiro;
extern FilaAtendimento fila_policia;
extern int tempo_simulado;
string cpf_login;
string nome_login;


//  Limpa a tela
void limpar_tela()
{
    system("cls");
    return ;
}



// ----- TELAS ----- // ----- Interface da interface das telas


//  Interface da tela principal
void tela_principal()
{   
    setlocale(LC_ALL, "");
    int op;
    
    do{
        cout << "/* Simulador de Atendimentos de Emergencias *\\ \n";
        cout << "(1) - Cadastrar\n";
        cout << "(2) - Listar\n";
        cout << "(3) - Atendimento\n";
        cout << "(4) - Sair\n";
        cout << "\n";
        cout << "Opcao: ";
        cin >> op;
        cin.ignore();

        menu_principal(op);
        limpar_tela();

    } while(op != 4);

    return ;
}


//  Interface da tela de cadastro
void tela_cadastro()
{
    setlocale(LC_ALL, "");
    int op;
    do{
        limpar_tela();

        cout << "/* Cadastrar *\\ \n";
        cout << "(1) - Cadastrar Cidadaos\n";
        cout << "(2) - Cadastrar Unidades de servicos\n";
        cout << "(3) - Voltar\n";
        cout << "\n";
        cout << "Opcao: ";
    
        cin >> op;
        cin.ignore();

        menu_cadastro(op);
        limpar_tela();

    } while (op != 3);

    return ;
}


//  Interface da tela de listagem
void tela_listar()
{
    setlocale(LC_ALL, "");

    int op;
    do{
        limpar_tela();

        cout << "/* Listar *\\ \n";
        cout << "(1) - Listar Bairros\n";
        cout << "(2) - Listar Cidadaos\n";
        cout << "(3) - Listar Unidades de servico por bairros\n";
        cout << "(4) - Voltar\n";
        cout << "\n";
        cout << "Opcao: ";
    
        cin >> op;
        cin.ignore();

        menu_listar(op);
        limpar_tela();

    } while (op != 4);

    return ;
}


//  Interface da tela de atendimentos. Acesso somente a cidadao cadastrado, via CPF.
void tela_atendimentos()
{
    setlocale(LC_ALL, "");

    limpar_tela();
    if(!login(&nome_login, &cpf_login)) return ; // Verifica o login

    int op;

    do
    {
        limpar_tela();
        cout << "/* Painel de Atendimentos */\n";
        cout << "Bem vindo, " << nome_login << "\n\n";
        cout << "Tempo atual simulado: " << tempo_simulado << "\n\n";
        cout << "(1) - Registrar nova ocorrencia\n";
        cout << "(2) - Visualizar fila de atendimentos\n";
        cout << "(3) - Visualizar historico do cidadao\n";
        cout << "(4) - Simular proxima unidade de tempo (1 atendimento)\n";
        cout << "(5) - Voltar\n";
        cout << "Entre com a opcao: ";
        cin >> op;
        cin.ignore();

        limpar_tela();
        
        menu_atendimentos(op);

    } while (op != 5);
    

    return ;
}



// ----- MENUS ----- // ----- Interface dos menus nas respectivas telas


//  Menu da tela principal
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


//  Menu da tela de cadastro
void menu_cadastro(int op)
{
    limpar_tela();
    switch(op)
    {
        case 1:
            cadastrar_cidadaos();

        break;

        case 2:
            cadastrar_unidades();

        break;

        default:
        break;
    }
    return ;
}


//  Menu da tela de listagem
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
        {
            string nome_bairro;
            cout << "Entre com o nome do bairro: ";
            getline(cin, nome_bairro);

            limpar_tela();  
            listar_unidades_por_bairros(nome_bairro);
            system("pause");
        break;
        }

        default:
        break;
    }
    return ;
}


// Menu da tela de atendimentos
// obs: observando essa funcao, da para refatorar os cases em outras funcoes. Nao sei se e a melhor opcao para 
// legibilidade, as vezes menos e mais...
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
                cout << "Tipo de servico invalido! Ocorrencia nao pode ser completada!\n";
                delete nova;
            }
            system("pause");
            break;
        }

        case 2:
        {
            listar_fila(&fila_bombeiro, "Bombeiros");
            listar_fila(&fila_ambulancia, "Ambulancia");
            listar_fila(&fila_policia, "Polacia");
            system("pause");
            break;
        }

        case 3:
            listar_historico(cpf_login);
            system("pause");
        break;

        case 4:
        {
            tempo_simulado++;
            cout << "/* Fila de ocorrencias *\\ \n\n";
            if(fila_bombeiro.inicio)
            {
                Ocorrencia *atendida = desenfileirar(&fila_bombeiro);
                cout << "[Bombeiro] Atendendo ocorrencia: " << atendida->descricao << "\n";
                delete(atendida);
            }

            if(fila_ambulancia.inicio)
            {
                Ocorrencia *atendida = desenfileirar(&fila_ambulancia);
                cout << "[Ambulancia] Atendendo ocorrencia: " << atendida->descricao << "\n";
                delete(atendida);
            }

            if(fila_policia.inicio)
            {
                Ocorrencia *atendida = desenfileirar(&fila_policia);
                cout << "[Policia] Atendendo ocorrencia: " << atendida->descricao << "\n";
                delete(atendida);
            }
            system("pause");
            break;
        }

        default:
        break;
    }

    return ;
}


