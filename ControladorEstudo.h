#ifndef CONTROLADOR_ESTUDO_H
#define CONTROLADOR_ESTUDO_H

#include "Usuario.h"
#include "SessaoEstudo.h"
#include "ControladorGamificacao.h"
#include "RepositorioEstudos.h"
#include "RepositorioGamificacao.h"
#include <string>

class ControladorEstudo {
private:
    // ===== DADOS DO USUÁRIO =====
    Usuario* usuario;
    RepositorioEstudos* repoEstudos;
    RepositorioGamificacao* repoGamificacao;
    
    // ===== ESTADO DA SESSÃO =====
    SessaoEstudo* sessaoAtiva;
    ControladorGamificacao* controladorGami;
    std::string estado; // "parado", "rodando", "pausado"

public:
    // ===== CONSTRUTORES =====
    
    // Construtor principal (com todos os componentes)
    ControladorEstudo(Usuario* usuario, 
                     ControladorGamificacao* controladorGami = nullptr,
                     RepositorioEstudos* repoEstudos = nullptr,
                     RepositorioGamificacao* repoGamificacao = nullptr);
    
    // Construtor simplificado (cria repositórios automaticamente)
    ControladorEstudo(const std::string& nomeUsuario, 
                     ControladorGamificacao* controladorGami = nullptr);
    
    // Destrutor
    ~ControladorEstudo();
    
    // ===== MÉTODOS PRINCIPAIS =====
    
    // Inicia uma nova sessão 
    void iniciarSessao();
    
    // Pausa a sessão atual
    void pausarSessao();
    
    // Continua uma sessão pausada
    void continuarSessao();
    
    // Finaliza a sessão atual e salva
    void finalizarSessao();
    
    // Cancela a sessão atual sem salvar
    void cancelarSessao();
    
    // ===== MÉTODOS DE CONSULTA =====
    
    // Mostra progresso atual da sessão
    void mostrarProgresso() const;
    
    // Mostra estatísticas do usuário
    void mostrarEstatisticas() const;
    
    // Mostra histórico de sessões
    void mostrarHistorico() const;
    
    // ===== MÉTODOS DE CONFIGURAÇÃO =====
    
    // Define o usuário atual
    void setUsuario(Usuario* usuario);
    
    // Define o controlador de gamificação
    void setControladorGamificacao(ControladorGamificacao* controladorGami);
    
    // ===== GETTERS =====
    
    // Verifica se há sessão ativa
    bool temSessaoAtiva() const;
    
    // Obtém o estado atual
    std::string getEstado() const;
    
    // Obtém a sessão ativa
    SessaoEstudo* getSessaoAtiva() const;
    
    // Obtém o usuário
    Usuario* getUsuario() const;
    
    // Obtém estatísticas de estudo
    void getEstatisticasEstudo(long long& tempoTotal, int& totalSessoes) const;

private:
    // ===== MÉTODOS PRIVADOS =====
    
    // Inicializa repositórios
    void inicializarRepositorios();
    
    // Salva a sessão no repositório
    void salvarSessao();
    
    // Atualiza gamificação com tempo estudado
    void atualizarGamificacao(long long segundos);
    
    // Formata tempo para exibição
    std::string formatarTempo(long long segundos) const;
    
    // Exibe resumo da sessão
    void exibirResumoSessao() const;
    
    // Exibe barra de progresso
    void exibirBarraProgresso(long long segundos) const;
    
    // Carrega dados do usuário dos repositórios
    void carregarDadosUsuario();
};
#endif