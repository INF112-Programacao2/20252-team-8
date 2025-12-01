#ifndef CONTROLADOR_INVENTARIO_H
#define CONTROLADOR_INVENTARIO_H

#include "Usuario.h"
#include "RepositorioInventario.h"
#include "TelaInventario.h" // Composição: O controlador "tem" uma tela
#include "Item.h"
#include <vector>
#include <string>

class ControladorInventario {
private:
    // Associações (objetos que existem fora daqui)
    Usuario* usuario;
    RepositorioInventario* repositorio;

    // Composição (objeto gerenciado por esta classe)
    TelaInventario tela;

    // Lista polimórfica de itens (pode conter Item ou ItemAudio)
    std::vector<Item*> itensCarregados;

    // Métodos auxiliares para organizar a memória
    void limparMemoria();
    void carregarItensDoRepositorio();

public:
    // Construtor recebe os dados externos
    ControladorInventario(Usuario* usuario, RepositorioInventario* repo);
    
    // Destrutor limpa a lista de itens
    ~ControladorInventario();

    // Loop principal do inventário
    void executar();
};

#endif