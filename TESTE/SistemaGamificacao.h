#ifndef SISTEMAGAMIFICACAO_H
#define SISTEMAGAMIFICACAO_H
#include <string>

class SistemaGamificacao
{
protected:
    int _tempo_de_estudo;
    int pontos=0;
    bool badge1=false;
    bool badge2=false;
    bool badge3=false;
    bool badge4=false;
    bool nivel1=false;
    bool nivel2=false;
    bool nivel3=false;
    bool nivel4=false; 

public:
    SistemaGamificacao(int temp);
    ~SistemaGamificacao();

    void Badges();
    void ComunicarSubidaDeNivel();
    void ComunicarBadges();
    int getPontos();
    int getHoras();
};

#endif //SISTEMAGAMIFICACAO_H
