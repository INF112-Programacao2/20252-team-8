#ifndef CONTROLADOR_ESTUDO_H
#define CONTROLADOR_ESTUDO_H

#include "Usuario.h"
#include "RepositorioEstudos.h"
#include "RepositorioGamificacao.h"
#include "RepositorioInventario.h"
#include "TelaEstudo.h"
#include "SessaoEstudo.h"
#include "miniaudio.h"
class ControladorEstudo {
private:
    // Poteiros para os objetos principais do sistema (Injeção de Dependência)
    // O Controlador usa estes objetos, mas não é dono deles (não dá delete)
    Usuario* usuario;
    RepositorioEstudos* repoEstudos;
    RepositorioGamificacao* repoGamificacao; 
    RepositorioInventario* repoInventario;

    // Instância da Tela (Composição)
    // Criada automaticamente quando o controlador nasce
    TelaEstudo tela;

    // Objeto que representa a sessão que está acontecendo agora
    // Mantemos na memória para controlar o cronômetro
    SessaoEstudo sessaoAtual;

    // --- Variáveis de Controle de Áudio ---
    ma_engine engine;
    ma_sound musicaFundo; // Objeto que controla o som tocando
    bool audioInicializado;
    std::string caminhoMusicaEscolhida;

    void selecionarMusica();

public:
    
    ControladorEstudo(Usuario* usuario, RepositorioEstudos* repoEstudos, RepositorioGamificacao* repoGamificacao, RepositorioInventario* repoInventario);

    // Método Principal
    // Inicia o loop do menu de estudos (Chamado pelo ControladorPrincipal)
    void executar();

    ~ControladorEstudo();

private:
    // --- Métodos Auxiliares  ---

    // 1. Pede disciplina/descrição e prepara o objeto sessaoAtual
    void iniciarNovaSessao();

    // 2. Loop do cronômetro (Pausar, Continuar, Finalizar)
    // Fica travado aqui enquanto o usuário estuda
    void gerenciarSessaoEmAndamento();

    // 3. Chamado ao encerrar: Salva no repo e dá XP/Moedas ao usuário
    void finalizarSessao();

    // 4. Busca dados no repoEstudos e manda a tela exibir
    void exibirHistorico();

};

#endif

