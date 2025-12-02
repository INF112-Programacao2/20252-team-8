// Bibliotecas
#include <iostream>
#include <string>

// Controladores
#include "ControladorEstudo.h"
#include "ControladorGamificacao.h"
#include "ControladorInventario.h"
#include "ControladorLoja.h"
#include "ControladorPrincipal.h"

// Repositorios
#include "RepositorioGamificacao.h"
#include "RepositorioInventario.h"
#include "RepositorioEstudos.h"

// Entidades
#include "Usuario.h"
#include "Loja.h"
#include "SessaoEstudo.h"

// Itens    (adicionar itens extras posteriormente)
#include "Item.h"
#include "miniaudio.h"
#include "Musica.h"     // Atualizar para itemAudio

// Classes Auxiliares
#include "Constantes.h"

int main() {
    try {
    // ------------------------------------------------------------
    // PASSO 1: Autenticação Simples (Setup Inicial)
    // ------------------------------------------------------------
    std::string nomeUsuario;
    std::cout << "Bem-vindo ao Monitor de Estudos!" << std::endl;
    std::cout << "Digite seu nome de usuario: ";
    std::getline(std::cin, nomeUsuario);
    
    // ------------------------------------------------------------
    // PASSO 2: Inicializar Repositórios (Camada de Dados)
    // ------------------------------------------------------------
    // Ao passar o nome, eles já preparam os arquivos .txt (ex: joao_inventario.txt)
    RepositorioGamificacao repoGamificacao(nomeUsuario); 
    RepositorioInventario repoInventario(nomeUsuario);
    RepositorioEstudos repoEstudos(nomeUsuario);
       
    // ------------------------------------------------------------
    // PASSO 3: Carregar ou Criar a Entidade Principal (Usuario)
    // ------------------------------------------------------------
    // O RepositorioGamificacao provavelmente é quem sabe os dados vitais (Nome, XP, Nivel)
    // Se o arquivo estiver vazio, ele cria um Usuario novo.
    Usuario* usuarioAtual = repoGamificacao.carregarUsuario();
    
    if (usuarioAtual == nullptr) {
        // Se não existia, cria um novo
        usuarioAtual = new Usuario(nomeUsuario);
    }

    // ------------------------------------------------------------
    // PASSO 4: Inicializar Controladores Específicos (Injeção de Dependência)
    // ------------------------------------------------------------
    // Cada controlador precisa saber QUEM é o usuário e ONDE salvar os dados.
    
    ControladorEstudo ctrlEstudo(usuarioAtual, &repoEstudos, &repoGamificacao, &repoInventario);
    // Nota: Passamos repoGamificacao para o estudo porque estudar gera XP!

    ControladorInventario ctrlInventario(usuarioAtual, &repoInventario);
    
    ControladorLoja ctrlLoja(usuarioAtual, &repoInventario, &repoGamificacao);
    // Nota: Loja precisa de Inventario (add item) e Gamificacao (gastar moedas)

    ControladorGamificacao ctrlGamificacao(usuarioAtual, &repoGamificacao);

    // ------------------------------------------------------------
    // PASSO 5: Inicializar o Controlador Principal (O Gerente)
    // ------------------------------------------------------------
    // O ControladorPrincipal vai gerenciar a navegação entre os outros.
    ControladorPrincipal ctrlPrincipal;
    
    // Configura os sub-controladores dentro do principal
    ctrlPrincipal.setControladorEstudo(&ctrlEstudo);
    ctrlPrincipal.setControladorInventario(&ctrlInventario);
    ctrlPrincipal.setControladorLoja(&ctrlLoja);
    ctrlPrincipal.setControladorGamificacao(&ctrlGamificacao);

    // ------------------------------------------------------------
    // PASSO 6: Executar o Loop da Aplicação
    // ------------------------------------------------------------
    // Este método contém o loop while(true) do menu principal
    try {
        ctrlPrincipal.executar();
    }
    catch (std::exception& e) {
        std::cerr << "ERRO FATAL: " << e.what() << std::endl;
        delete usuarioAtual;    // Garante que não haverá vazamento de memória caso o controlador falhe
        return 1;
    }

    // ------------------------------------------------------------
    // PASSO 7: Deletar ponteiro
    // ------------------------------------------------------------
    delete usuarioAtual;
    }
    catch (std::exception& e) {
        std::cerr << "ERRO FATAL: " << e.what() << std::endl;
        return 1;
    }
}