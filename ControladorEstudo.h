#ifndef CONTROLADOR_ESTUDO_H
#define CONTROLADOR_ESTUDO_H

#include "Usuario.h"
#include "SessaoEstudo.h"
#include "ControladorGamificacao.h"
#include <string>

class ControladorEstudo {
private:
    // ===== ESTADO DA SESSÃO =====
    SessaoEstudo* sessaoAtiva;
    ControladorGamificacao* controladorGami;
    std::string estado; // "parado", "rodando", "pausado"

public:
    // ===== CONSTRUTOR E DESTRUTOR =====
    ControladorEstudo(ControladorGamificacao* controladorG);
    ~ControladorEstudo();
    
    // ===== MÉTODOS PRINCIPAIS =====
    
    // Inicia uma nova sessão 
    void iniciarSessao();
    
    // Pausa a sessão atual
    void pausarSessao();
    
    // Continua uma sessão pausada
    void continuarSessao();
    
    // Finaliza a sessão atual e salva
    void finalizarSessao(Usuario* usuario);
    
    // Cancela a sessão atual sem salvar
    void cancelarSessao();
    
    // ===== MÉTODOS DE CONSULTA =====
    
    // Mostra progresso atual da sessão
    void mostrarProgresso() const;
    
    // Mostra estatísticas do usuário
    void mostrarEstatisticas() const;
    
    // Mostra histórico de sessões
    void mostrarHistorico() const;
    
    // Mostra histórico completo com detalhes
    void mostrarHistoricoCompleto(Usuario* usuario) const;
    
    // ===== GETTERS =====
    
    // Verifica se há sessão ativa
    bool temSessaoAtiva() const;
    
    // Obtém o estado atual
    std::string getEstado() const;
    
    // Obtém a sessão ativa
    SessaoEstudo* getSessaoAtiva() const;

private:
    // ===== MÉTODOS PRIVADOS =====
    
    // Salva a sessão no repositório
    void salvarSessao(Usuario* usuario);
    
    // Atualiza gamificação com tempo estudado
    void atualizarGamificacao(long long segundos);
    
    // Formata tempo para exibição
    std::string formatarTempo(long long segundos) const;
    
    // Exibe resumo da sessão
    void exibirResumoSessao() const;
};

#endif
