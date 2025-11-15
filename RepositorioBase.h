#ifndef REPOSITORIO_BASE_H
#define REPOSITORIO_BASE_H

#include <string>
#include <vector>

class RepositorioBase {
    protected:
        std::string caminhoArquivo;
        std::vector <std::string> LerLinhasDoArquivo();
        void escreverLinhasNoArquivo(std::vector <std::string>);
};

#endif