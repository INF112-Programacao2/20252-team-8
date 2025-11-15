#ifndef REPOSITORIO_GAMIFICACAO_H
#define REPOSITORIO_GAMIFICACAO_H

#include <string>
#include <vector>
#include "RepositorioBase.h"
#include "Badge.h"

class RepositorioGamificacao : public RepositorioBase {
    public:
        std::vector <Badge> carregarBadges();
        
};

#endif