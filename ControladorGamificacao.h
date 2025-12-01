#ifndef CONTROLADOR_GAMIFICACAO_H
#define CONTROLADOR_GAMIFICACAO_H

#include "RepositorioGamificacao.h"
#include "Usuario.h"
#include "TelaGamificacao.h" // Inclui a tela para poder usá-la
#include <string>

// Definições (Sem constexpr, como você pediu)
#define XP_POR_NIVEL 100
#define RECOMPENSA_MOEDAS 50

class ControladorGamificacao {
private:
    Usuario* usuarioAtual;
    RepositorioGamificacao* repositorio;
    TelaGamificacao tela; // O controlador DONO da tela
    
    // Métodos auxiliares privados
    std::string calcularNomeBadge(int nivel);
    int calcularIdBadge(int nivel);
    void verificarEvolucao();

public:
    ControladorGamificacao(Usuario* usuario, RepositorioGamificacao* repo);
    
    // Método principal para abrir o perfil
    void executar(); 

    // Métodos chamados por outros controladores (Estudos, Loja)
    void adicionarXP(int quantidade);
    void adicionarMoedas(int quantidade);
    void salvarTudo();
    
    // Getters
    Usuario* getUsuario() const;
    int getXP() const;
    int getNivel() const;
    int getMoedas() const;
    std::string getBadge() const;
};

#endif