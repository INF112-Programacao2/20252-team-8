#ifndef CONTROLADOR_GAMIFICACAO_H
#define CONTROLADOR_GAMIFICACAO_H

#include "RepositorioGamificacao.h"
#include "Usuario.h"
#include <string>

// --- DEFINIÇÕES (Mudança solicitada) ---
#define XP_POR_NIVEL 100
#define RECOMPENSA_MOEDAS 50

class ControladorGamificacao {
private:
    Usuario* usuarioAtual;
    RepositorioGamificacao* repositorio;
    
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
    Usuario* getUsuario() const;
    int getXP() const;
    int getNivel() const;      // Calcula nível baseado no XP total
    int getMoedas() const;
    std::string getBadge() const;
};

#endif