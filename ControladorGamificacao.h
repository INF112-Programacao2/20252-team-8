#ifndef CONTROLADOR_GAMIFICACAO_H
#define CONTROLADOR_GAMIFICACAO_H

#include "RepositorioGamificacao.h"
#include "Usuario.h"

class ControladorGamificacao {
private:
    Usuario* usuarioAtual;
    RepositorioGamificacao* repositorio;
    
    // Configurações de progressão
    static constexpr int XP_POR_NIVEL = 100;
    static constexpr int MOEDAS_POR_NIVEL = 10;
    
    void calcularProgressao(); // Recalcula nível baseado no XP
    
public:
    ControladorGamificacao(Usuario* usuario, RepositorioGamificacao* repo);
    
    // Métodos principais
    void exibirPerfil();
    void adicionarXP(int quantidade);
    void adicionarMoedas(int quantidade);
    void atualizarBadge(int badgeIdx);
    
    // Métodos de atualização
    void sincronizarComRepositorio();
    void salvarEstado();
    
    // Getters
    Usuario* getUsuario() const;
    int getXP() const;
    int getNivel() const;
    int getMoedas() const;
    std::string getBadge() const;
};

#endif