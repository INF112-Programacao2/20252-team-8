#ifndef CONTROLADORLOJA_H
#define CONTROLADORLOJA_H

#include "ControladorGamificacao.h"
#include "Musica.h"
#include <vector>

class ControladorLoja : public ControladorGamificacao {
protected:
    std::vector<Musica> musicas; 

public:
    ControladorLoja(int tempo_inicial);
    
    bool comprarMusica(int indice); 
    std::vector<Musica>& getMusicas(); 
};
#endif