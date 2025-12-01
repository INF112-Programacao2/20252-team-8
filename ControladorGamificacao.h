#ifndef CONTROLADOR_GAMIFICACAO_H
#define CONTROLADOR_GAMIFICACAO_H

#include "RepositorioGamificacao.h"
#include "Usuario.h"
#include <string>

class ControladorGamificacao {
private:
    Usuario* usuarioAtual;
    RepositorioGamificacao* repositorio;
    
    // Configurações
    static constexpr int XP_POR_NIVEL = 100;
    static constexpr int RECOMPENSA_MOEDAS = 50;
    
    // Método auxiliar para converter nível em nome de badge
    std::string calcularNomeBadge(int nivel);
    // Método auxiliar para converter nível em ID de badge (para o repositorio)
    int calcularIdBadge(int nivel);
    
    void verificarEvolucao(); // Verifica se subiu de nível baseado no XP total

public:
    ControladorGamificacao(Usuario* usuario, RepositorioGamificacao* repo);
    
    // Métodos de Ação
    void adicionarXP(int quantidade);
    void adicionarMoedas(int quantidade);
    void salvarTudo(); // Força o salvamento de todos os dados
    
    // Getters
    // IMPORTANTE: Estes getters calculam o estado real, ignorando 
    // limitações do objeto Usuario se necessário.
    Usuario* getUsuario() const;
    int getXP() const;
    int getNivel() const;      // Calcula nível baseado no XP total
    int getMoedas() const;
    std::string getBadge() const;
};

#endif