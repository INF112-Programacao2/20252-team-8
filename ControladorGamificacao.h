#ifndef CONTROLADORGAMIFICACAO_H
#define CONTROLADORGAMIFICACAO_H

class ControladorGamificacao {
protected:
    int _tempo_de_estudo;
    int pontos;
    
    // Variáveis de controle
    bool badge1, badge2, badge3, badge4;
    bool nivel1, nivel2, nivel3, nivel4;

public:
    ControladorGamificacao(int tempo_inicial);
    ~ControladorGamificacao();

    void atualizarStatus(); 
    void mostrarBadges();   
    int getPontos();
};
#endif