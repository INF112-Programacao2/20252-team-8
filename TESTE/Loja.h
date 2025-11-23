#ifndef LOJA_H
#define LOJA_H

#include "SistemaGamificacao.h"
#include <string>

class Loja : public SistemaGamificacao{   
protected:

    bool musica1_comprada;
    int musica1_valor;
    std::string nomemusica1;

    bool musica2_comprada;
    int musica2_valor;
    std::string nomemusica2;

    bool musica3_comprada;
    int musica3_valor;
    std::string nomemusica3;
     
public:
 
    Loja(int tempo_de_estudo_inicial);
    ~Loja();
    
    void loja();
    void musicas_compradas();


    bool isMusica1Comprada();
    bool isMusica2Comprada();
    bool isMusica3Comprada();

    std::string getNomeMusica1();

};
#endif // LOJA_H