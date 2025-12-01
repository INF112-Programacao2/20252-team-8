#ifndef CONTROLADORLOJA_H
#define CONTROLADORLOJA_H

#include "ControladorGamificacao.h"
#include "Musica.h"
#include <vector>

class ControladorLoja : public ControladorGamificacao {
protected:
    std::vector<Musica> musicas; 

public:
    ControladorLoja(Usuario* usuario, RepositorioGamificacao* repo);
    
    bool comprarMusica(int indice); 
    std::vector<Musica>& getMusicas(); 
};
#endif