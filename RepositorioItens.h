#ifndef REPOSITORIO_ITENS_H
#define REPOSITORIO_ITENS_H

#include <string>
#include <vector>
#include "RepositorioBase.h"
#include "Item.h"

class RepositorioItens : public RepositorioBase {
    public:
        std::vector <Item> carregarCatalogo();        
};

#endif