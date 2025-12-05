# 📚 Study Tracker - Monitor de Estudos Gamificado

![Language](https://img.shields.io/badge/language-C%2B%2B17-blue.svg)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20Windows%20(MinGW)-lightgrey.svg)
![Status](https://img.shields.io/badge/status-funcional-success.svg)

> **Status:** Versão CLI (Linha de Comando) Funcional 🚀

O **Study Tracker** é uma aplicação desktop via terminal desenvolvida como parte da disciplina de **Programação II - INF 112**. O objetivo é ajudar estudantes a monitorar, analisar e gamificar suas horas de estudo. A ferramenta busca criar um ambiente motivador, transformando o tempo de estudo em pontos (XP) e recompensas virtuais.

---

## 📋 Índice

- [Descrição do Projeto](#-descrição-do-projeto)
- [Funcionalidades](#-funcionalidades)
- [Arquitetura do Sistema](#-arquitetura-do-sistema)
- [Tecnologias Utilizadas](#-tecnologias-utilizadas)
- [Estrutura de Arquivos](#-estrutura-de-arquivos)
- [Como Compilar e Executar](#-como-compilar-e-executar)
- [Contribuidores](#-contribuidores)

---

## 📖 Descrição do Projeto

Muitos estudantes enfrentam dificuldades para manter a disciplina e visualizar seu progresso ao longo do tempo. O Study Tracker resolve esse problema oferecendo uma plataforma centralizada onde o usuário pode cronometrar suas sessões de estudo, visualizar seu histórico e ser recompensado pelo esforço com moedas e níveis, tornando o processo menos isolado e mais engajador.

---

## ✨ Funcionalidades

### ⏰ Monitoramento de Estudos
- **Cronômetro Real:** Funções de iniciar, pausar, continuar e finalizar sessões.
- **Metadados:** Registro de disciplina e descrição da tarefa.
- **Feedback:** Visualização do tempo decorrido em tempo real.

### 🏆 Gamificação
- **XP (Experiência):** Ganhe pontos por cada segundo estudado.
- **Sistema de Níveis:** Suba de nível conforme acumula XP.
- **Badges (Conquistas):** Desbloqueie títulos (Iniciante, Veterano, Lenda) baseados no seu nível.
- **Economia Virtual:** Ganhe moedas para gastar na loja.

### 🎧 Loja e Multimídia
- **Loja de Itens:** Compre músicas e itens cosméticos com suas moedas.
- **Player de Música:** Integração com biblioteca de áudio para tocar músicas de foco (Lofi, Piano, etc.) diretamente pelo terminal enquanto estuda.
- **Inventário:** Gerencie e utilize os itens comprados.

### 💾 Persistência de Dados
- **Salvamento Automático:** Todo o progresso (usuário, inventário, histórico) é salvo em arquivos `.txt`.
- **Histórico:** Recarregue suas sessões anteriores mesmo após fechar o programa.

---

## 🏗 Arquitetura do Sistema

O projeto adota uma arquitetura robusta baseada no padrão **MVC (Model-View-Controller)** adaptado para aplicações de console, garantindo separação de responsabilidades e facilidade de manutenção.

### 1. Controladores (Controllers)
Gerenciam a lógica de negócio e o fluxo da aplicação.
- `ControladorPrincipal`: Gerente geral que roteia a navegação.
- `ControladorEstudo`: Gerencia o cronômetro, a sessão e o motor de áudio.
- `ControladorLoja`: Gerencia o catálogo e transações de compra.
- `ControladorInventario`: Gerencia a lista de itens e polimorfismo (`usar()` item).
- `ControladorGamificacao`: Calcula regras de evolução e recompensas.

### 2. Telas (Views)
Responsáveis apenas pela exibição e captura de entrada (Passivas).
- `TelaBase`: Classe mãe com utilitários de limpeza de tela e tratamento de input.
- `TelaEstudo`, `TelaLoja`, `TelaInventario`, `TelaGamificacao`.

### 3. Repositórios (Persistence Layer)
Abstraem a manipulação de arquivos de texto.
- `RepositorioBase`: Lógica genérica de leitura/escrita.
- `RepositorioEstudos`: Salva histórico de sessões.
- `RepositorioGamificacao`: Salva estado do usuário (XP, Nível).
- `RepositorioInventario`: Salva itens comprados.

### 4. Entidades (Models)
Classes de domínio.
- `Usuario`, `SessaoEstudo`.
- `Item` (Base) -> `ItemAudio` (Polimorfismo para tocar música).

---

## 🛠 Tecnologias Utilizadas

- **Linguagem:** C++17
- **Build System:** GNU Make (Makefile híbrido Windows/Linux)
- **Áudio:** [miniaudio](https://miniaud.io/) (Biblioteca single-header para reprodução MP3)
- **Persistência:** Arquivos de Texto (`fstream`)
- **Interface:** CLI (Command Line Interface) com limpeza de buffer e validação.

---

## 📂 Estrutura de Arquivos

Para o correto funcionamento do áudio e da compilação, a estrutura de pastas deve ser mantida como abaixo:

```text
StudyTracker/
├── assets/                 <-- [IMPORTANTE] Crie esta pasta e coloque os .mp3 aqui
│   ├── lofi.mp3
│   ├── rock.mp3
│   └── ...
├── Makefile                <-- Script de automação
├── miniaudio.h             <-- Biblioteca de áudio
├── main.cpp
├── *.h                     <-- Arquivos de cabeçalho
├── *.cpp                   <-- Arquivos de implementação
└── AppEstudos              <-- Executável gerado após compilação
```

## 🚀 Como Compilar e Executar

Este projeto possui um **Makefile** que detecta automaticamente seu sistema operacional e configura a compilação.

### Pré-requisitos

1.  **Compilador C++** (`g++`) instalado e configurado no PATH.
2.  **Make** instalado.
3.  **Assets:** Arquivos `.mp3` dentro da pasta `assets/` na raiz do projeto.

### Passo a Passo

1.  **Clone o repositório:**

    ```bash
    git clone https://github.com/INF112-Programacao2/20252-team-8.git
    cd study-tracker
    ```

2.  **Compile o projeto:**
    Basta rodar o comando na raiz do projeto:

    ```bash
    make
    ```

3.  **Execute:**
    Utilize o comando do make para rodar:

    ```bash
    make run
    ```

    *Alternativamente, você pode rodar o executável manualmente:*

      * **Linux/WSL:** `./AppEstudos`
      * **Windows:** `AppEstudos.exe`

4.  **Limpar (Opcional):**
    Para apagar os arquivos temporários de compilação (`.o`) e o executável:

    ```bash
    make clean
    ```

-----

## 👥 Contribuidores

Este projeto foi desenvolvido com a colaboração dos seguintes membros:

  - [Nicolas Salvador](https://www.google.com/search?q=https://github.com/NicolasSalvador13)
  - [Gabriel Carneiro](https://www.google.com/search?q=https://github.com/usuario2)
  - [Aloizio Sergio](https://www.google.com/search?q=https://github.com/usuario3)
  - [PedroPaulon](https://www.google.com/search?q=https://github.com/usuario4)
  - [Murilo Sousa](https://www.google.com/search?q=https://github.com/seu-usuario)

-----

*Projeto acadêmico - INF 112 - Universidade Federal de Viçosa (UFV)*