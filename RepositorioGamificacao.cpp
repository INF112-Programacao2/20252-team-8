#include "RepositorioGamificacao.h"
#include "RepositorioBase.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

RepositorioGamificacao::RepositorioGamificacao(const std::string& nomeUsuario) :
    RepositorioBase(nomeUsuario) {
    
    // Verifica se usuário é novo
    bool usuarioNovo = true;
    std::string linhaAtual;
    std::ifstream checkArquivo(this->caminhoArquivo);
    
    if (checkArquivo.is_open()) {
        while (std::getline(checkArquivo, linhaAtual)) {
            // Verifica se a linha contem a chave "Moedas:"
            if (linhaAtual.find("Moedas:") != std::string::npos) {
                usuarioNovo = false;
                break; // Não precisa ler o resto.
            }
        }
        checkArquivo.close();
    }

    // Escreve informações se o usuário for novo
    if (usuarioNovo) {
        std::cout << "Criando perfil de gamificação padrão...\n";

        // Inicialização de vetor com informações do repositório
        std::vector<std::string> linhasParaAdicionar = {
            "Moedas: 0",
            "Pontos: 0",
            "Nivel: 0",
            "Badges: NULL"
        };

        this->escreverLinhasNoArquivo(linhasParaAdicionar);
    } 
    else {
        std::cout << "Perfil de gamificação carregado.\n";
    }
}


bool RepositorioGamificacao::getBadge(int badge_idx) {

}


void RepositorioGamificacao::setBadge (int badge_idx, bool obtido) {

}

int RepositorioGamificacao::getNivel() {

}

void RepositorioGamificacao::setNivel (int nivel_atual) {

}

int RepositorioGamificacao::getMoedas() {

}

void RepositorioGamificacao::setMoedas (int qtd_moedas) {

}

int RepositorioGamificacao::getPontos() {

}

void RepositorioGamificacao::setPontos (int qtd_pontos) {

}
