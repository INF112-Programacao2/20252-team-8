#ifndef REPOSITORIO_INVENTARIO_H
#define REPOSITORIO_INVENTARIO_H

#include <string>
#include <vector>
#include "RepositorioBase.h"
#include "Item.h"

class RepositorioInventario : public RepositorioBase {
    public:
    // Este método vai no arquivo, lê os IDs e retorna os objetos só quando pedirem
        std::vector <Item> getItensUsuario();        
};

#endif