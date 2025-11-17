#ifndef CONTROLADORGAMIFICACAO_H
#define CONTROLADORGAMIFICACAO_H

class ControladorGamificacao {
protected:
    int _tempo_de_estudo;
    int pontos;
    
    // Status de Badges e Níveis
    bool badge1, badge2, badge3, badge4;
    bool nivel1, nivel2, nivel3, nivel4;

public:
    ControladorGamificacao(int tempo_inicial);
    ~ControladorGamificacao();

    // Lógica
    void atualizarStatusBaseadoNoTempo(); // Antigo Badges()
    bool gastarPontos(int valor);

    // Getters
    int getPontos();
    int getHoras();
    
    void comunicarSubidaDeNivel();
    void comunicarBadges();
};

#endif // CONTROLADORGAMIFICACAO_H