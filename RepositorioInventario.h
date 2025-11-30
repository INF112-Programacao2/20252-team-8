#ifndef REPOSITORIO_INVENTARIO_H
#define REPOSITORIO_INVENTARIO_H

#include <string>
#include <vector>
#include "RepositorioBase.h"
#include "Item.h"

class RepositorioInventario : public RepositorioBase {
    public:
        std::vector <Item> carregarCatalogo();        
};

#endif