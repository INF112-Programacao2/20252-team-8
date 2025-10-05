# Study Tracker - Projeto de Programação

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Status](https://img.shields.io/badge/status-em%20desenvolvimento-yellow.svg)

> Status: Em Desenvolvimento 🚧

O **Study Tracker** é uma aplicação desktop desenvolvida como parte da disciplina de Programação II - INF 112, com o objetivo de ajudar estudantes a monitorar, analisar e gamificar suas horas de estudo. A ferramenta busca criar um ambiente motivador e produtivo, incorporando elementos sociais e de recompensa para incentivar a consistência nos estudos.

## Índice

- [Descrição do Projeto](#1-descrição-do-projeto)
- [Funcionalidades](#2-funcionalidades)
- [Arquitetura do Sistema](#3-arquitetura-do-sistema)
- [Tecnologias Planejadas](#4-tecnologias-planejadas)
- [Como Começar](#5-como-começar)
- [Contribuidores](#6-contribuidores)
- [Licença](#7-licença)

## 1. Descrição do Projeto

Muitos estudantes enfrentam dificuldades para manter a disciplina e visualizar seu progresso ao longo do tempo. O Study Tracker resolve esse problema oferecendo uma plataforma centralizada onde o usuário pode cronometrar suas sessões de estudo, adicionar metadados como disciplinas e descrições, visualizar seu desempenho através de gráficos e interagir com amigos, tornando o processo de estudo menos isolado e mais engajador.

## 2. Funcionalidades

O sistema foi projetado para incluir as seguintes funcionalidades:

⏰ **Monitoramento de Tempo**
- Cronômetro para sessões de estudo com funções de iniciar, pausar, continuar e finalizar.
- Adição de etiquetas (tags) e descrições para cada sessão.

📊 **Análise de Desempenho**
- Visualização do histórico de estudos diário, semanal e mensal.
- Gráficos que demonstram o progresso e a evolução ao longo do tempo.
- Análise do período do dia com maior produtividade.

🏆 **Gamificação**
- Sistema de pontos e moedas recebidos com base nas horas estudadas.
- Conquistas (badges) desbloqueadas ao atingir metas (ex: estudar 7 dias seguidos).
- Loja virtual para trocar moedas por itens de personalização (temas, músicas, etc.).

👥 **Funcionalidades Sociais**
- Sistema de amigos para adicionar e interagir com outros usuários.
- Visualização do progresso de estudo dos amigos (respeitando a privacidade).
- Possibilidade de comparar o desempenho e criar um ambiente de competição saudável.

## 3. Arquitetura do Sistema

O projeto foi modelado utilizando a metodologia de **Cartões-CRC (Classe-Responsabilidade-Colaborador)** para garantir um design coeso e orientado a objetos, baseado nos princípios de Responsabilidade Única (SRP) e no padrão de projeto Repositório para a camada de persistência.

A arquitetura foi dividida nos seguintes módulos:

#### Módulo de Usuários e Social
- `Usuario`: Modela o usuário, suas credenciais e estado.
- `GerenciadorAmizades`: Gerencia a lógica de amizades.
- `Inventario`: Controla os itens que um usuário possui.

#### Módulo de Estudo e Análise
- `SessaoEstudo`: Modela uma sessão de estudo individual.
- `AnalisadorDeDados`: Realiza cálculos e gera estatísticas.

#### Módulo de Gamificação e Recompensas
- `SistemaGamificacao`: Controla a lógica de pontos, níveis e conquistas.
- `Loja`: Gerencia o catálogo de itens e as transações.
- `Item`: Modela um item individual.

#### Módulo de Persistência
- `HistoricoEstudos`: Repositório para salvar e carregar sessões de estudo.
- `RepositorioUsuario`: Repositório para dados de usuários e amizades.
- `RepositorioGamificacao`: Repositório para o progresso de gamificação.
- `RepositorioLoja`: Repositório para os itens da loja.

#### Módulo de Orquestração
- `Aplicacao`: A classe principal que gerencia a interface gráfica e coordena a interação entre todos os outros módulos.

## 4. Tecnologias Planejadas

As seguintes tecnologias foram planejadas para a implementação do projeto:

- **Linguagem: C++23** 
- **Interface Gráfica (GUI): Qt** 
- **Banco de Dados: SQLite 3**
  
## 5. Como Começar

Para executar o projeto em seu ambiente local, siga os passos abaixo.

```bash
# 1. Clone o repositório
git clone [https://github.com/INF112-Programacao2/20252-team-8](https://github.com/INF112-Programacao2/20252-team-8)

# 2. Navegue até o diretório do projeto
cd study-tracker

--- A IMPLEMENTAR ----
# 3. Crie e ative um ambiente virtual (recomendado)
# 4. Instale as dependências
# 5. Execute a aplicação
--- A IMPLEMENTAR ----

```

## 6. Contribuidores

Este projeto foi desenvolvido com a colaboração dos seguintes membros:

- [Nicolas Salvador](https://github.com/NicolasSalvador13)
- [Gabriel Carneiro](https://github.com/usuario2)
- [Aloizio Sergio](https://github.com/usuario3)
- [PedroPaulon](https://github.com/usuario4)
- [Murilo Sousa](https://github.com/seu-usuario)

## 7. Licença

Este projeto está sob a licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.
