# Simulador de Atendimento Inteligente em Situações de Emergência Urbana

## 📅 Projeto Semestral - Estrutura de Dados I (2025)

### Contexto:
Este projeto simula um sistema de atendimento de emergência urbana em uma cidade inteligente. A cidade é composta por vários bairros, e os serviços de emergência (como ambulâncias, bombeiros e polícia) respondem a ocorrências em diferentes áreas. Cada emergência pode ter diferentes níveis de gravidade, prioridade e localização.

### Relação com a matéria:
Através de uma simulação de atendimentos de emergência em uma cidade, este sistema tem como objetivo botar em prática os conhecimentos aprendidos na matéria de Estrutura de Dados I, onde utilizando estruturas de dados como tabelas hash, listas encadeadas, filas, pilhas, listas cruzadas e estruturas de árvores podemos representar os elementos e operações do mundo real.

---

## 🔧 Funcionalidades

### Cadastro:

* **Cidadãos** com dados pessoais e bairro de residência
* **Bairros**, registrados automaticamente com as unidades
* **Unidades de serviço** (ambulância, bombeiro, polícia), com ligação cruzada ao bairro correspondente

### Interface:

* Menus de cadastro, listagem, atendimento e saída
* Interface textual direta com o terminal (`cout`), organizada por telas.

### Atendimento:

* Tela de login (com validação via CPF) antes de registrar ocorrências
* Ocorrências classificadas por tipo de serviço (fila de atendimento)
* Simulação de tempo: a cada unidade, um atendimento por tipo é realizado

### Histórico:

* Cada cidadão possui uma lista encadeada com todas as ocorrências registradas

### Listas Cruzadas:

* Cada bairro possui uma lista encadeada com suas unidades de serviço
* Cadastro de unidade verifica ou cria o bairro correspondente

---

## 📂 Estrutura do Projeto

* `main.cpp`: ponto de entrada e organização geral
* `interfaces.cpp`: menus e navegação entre telas
* `cadastros.cpp`: cadastro, listagem, criação, busca de estruturas e funcionalidades
* `atendimentos.cpp`: registro, enfileiramento e atendimento de ocorrências
* `header/*.h`: arquivos de cabeçalho correspondentes

---

## 📊 Estruturas de Dados Utilizadas

* **Tabelas hash** com tratamento de colisão (cidadãos, bairros, unidades)
* **Filas** para atendimento de ocorrências por tipo
* **Listas encadeadas** para histórico e unidades por bairro

---

## 🔄 Status Atual

* [x] Fase 1: cadastro, login, simulação de atendimento
* [x] Fase 2: listas cruzadas e histórico por cidadão
* [ ] Fase 3: integração de árvores (AVL / BST) para priorização

---

## 👤 Desenvolvedores

**Luã do Carmo**
**João Pedro Pina**

Curso de Bacharelado em Ciência da Computação
Disciplina: Estrutura de Dados I - 2025
Professor: Ronaldo Celso Messias Correia

---

## ✅ Compilação

```
g++ main.cpp atendimentos.cpp interfaces.cpp cadastros.cpp -o programa
```

Observação: Tem alguns problemas relacionados à acentuações a depender da sua IDE e padrões de máquina.

---

## 📚 Licença

Uso educacional - Projeto acadêmico.
Sob autoria de Luã do Carmo Ribeiro.
