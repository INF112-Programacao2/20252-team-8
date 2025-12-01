#ifndef TELA_INVENTARIO_H
#define TELA_INVENTARIO_H

#include "TelaBase.h"
#include "Item.h"
#include <vector>

class TelaInventario : public TelaBase {
public:
    // O método principal agora recebe a lista de ponteiros para itens
    // Retorna a opção escolhida pelo usuário (ex: 0 para voltar)
    int mostrarInventario(const std::vector<Item*>& itens);
};

#endif