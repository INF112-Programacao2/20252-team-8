#include "RepositorioBase.h"
#include <vector>

class RepositorioInventario : public RepositorioBase {
public:
    RepositorioInventario(const std::string& nomeUsuario);
    
    void adicionarItem(int id);
    bool possuiItem(int id);
    
    // Retorna apenas os IDs brutos
    std::vector<int> carregarIds(); 
};