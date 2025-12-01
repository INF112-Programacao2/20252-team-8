#ifndef CONTROLADOR_INVENTARIO_H
#define CONTROLADOR_INVENTARIO_H

#include <vector>

// Dependências de Entidades e Repositórios
#include "Usuario.h"
#include "RepositorioInventario.h"
#include "Item.h" // Necessário para manipular os objetos Item*

// Dependência de Interface (Composição)
#include "TelaInventario.h"

class ControladorInventario {
private:
    // --- ASSOCIAÇÕES ---
    // O usuário atual (caso precisemos validar algo ou equipar item nele)
    Usuario* usuario;
    
    // O repositório que sabe QUAIS itens (IDs) o usuário tem
    RepositorioInventario* repoInventario;

    // --- COMPOSIÇÃO ---
    // A tela específica deste controlador
    TelaInventario tela;

public:
    // Construtor: Recebe as dependências da main
    ControladorInventario(Usuario* usuario, RepositorioInventario* repoInventario);

    // Método Principal: Inicia o loop do menu "Meus Itens"
    void executar();

private:
    // 1.Busca IDs no repoInventario
    // 2. Busca os Objetos reais na classe Loja (static)
    // 3. Passa a lista de objetos para a Tela mostrar
    void carregarEListarItens();
    
    void equiparItem(Item* item); 
};

#endif