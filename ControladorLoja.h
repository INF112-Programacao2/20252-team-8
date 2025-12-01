#ifndef CONTROLADORLOJA_H
#define CONTROLADORLOJA_H

#include "Musica.h"
#include <vector>

class ControladorLoja {
private:
    Usuario* usuario;
    RepositorioGamificacao* repo;
    RepositorioInventario* repoInv;
    std::vector<Musica> musicas; 

public:
    ControladorLoja(Usuario* usuario, RepositorioInventario* repoInv, RepositorioGamificacao* repo);
    
    bool comprarMusica(int indice); 
    std::vector<Musica>& getMusicas(); 
};
#endif
