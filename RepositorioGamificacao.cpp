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
    // MAPEAMENTO: Traduz o ID (1,2,3,4) para o Texto esperado
    std::string badgeEsperada;
    
    switch (badge_idx) {
        case 1: badgeEsperada = "Calouro"; break;
        case 2: badgeEsperada = "Estudante"; break;
        case 3: badgeEsperada = "Veterano"; break;
        case 4: badgeEsperada = "Formando"; break;
        default: 
            // Se passar um número inválido (ex: 5), retorna false 
            return false; 
    }
    std::ifstream repositorio (this->caminhoArquivo);

    std::string linhaAtual;
    std::string badgeNoArquivo = "NULL"; // Valor padrão caso não ache nada

    // LEITURA DO ARQUIVO
    if (repositorio.is_open()) {
        while (std::getline(repositorio, linhaAtual)) {
            // Verifica se a linha contem a chave "Badges: "
            if (linhaAtual.find("Badges: ") != std::string::npos) {
                badgeNoArquivo = linhaAtual.substr(8);  // Le até o fim da linha
                break;
            }
        }
        repositorio.close();
    }
    // COMPARAÇÃO E RETORNO
    // Se o que está no arquivo for igual ao que o ID pede, retorna true.
    if (badgeNoArquivo == badgeEsperada) {
        return true;
    } else {
        return false;
    }

}


void RepositorioGamificacao::setBadge (int badge_idx) {

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
