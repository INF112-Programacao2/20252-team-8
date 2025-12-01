#ifndef CONTROLADORGAMIFICACAO_H
#define CONTROLADORGAMIFICACAO_H

#include <string>

class ControladorGamificacao {
protected:
    int _tempo_de_estudo;
    int pontos;
    
    // Variáveis de XP e nível 
    int xp;
    int nivel;
    int moedas;
    std::string badge;
    
    // Variáveis de controle de badges
    bool badge1, badge2, badge3, badge4;
    bool nivel1, nivel2, nivel3, nivel4;

public:
    ControladorGamificacao(int tempo_inicial);
    ~ControladorGamificacao();

    void atualizarStatus(); 
    void mostrarBadges();   
    int getPontos();
    
    // Método para verificar se subiu de nível
    void verificarSubidaNivel();
    
    // Getters para as novas variáveis
    int getXp() const;
    int getNivel() const;
    int getMoedas() const;
    std::string getBadge() const;
    
    // Métodos para adicionar XP e tempo
    void adicionarXp(int quantidade);
    void adicionarTempoEstudo(int minutos);
};
#endif