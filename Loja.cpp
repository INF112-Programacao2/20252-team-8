#include "Loja.h" 
#include <iostream> 
#include <fstream>

Loja::Loja(int capacidadeMaxima) 
    : itens(capacidadeMaxima),  //Pre-aloca o vetor com 'capacidadeMaxima' slots
      quantidadeAtual(0)       
    {}

void Loja::adicionarItem(const Item& item) {
    //retorna a capacidade máxima 
    if (this->quantidadeAtual < this->itens.size()) {
        
        //Adiciona o item no proximo "slot" livre
        this->itens[this->quantidadeAtual] = item;

        //Incrementa o contador de itens
        this->quantidadeAtual++;

    } else {
        std::cerr << "Erro: Inventário está cheio! Capacidade máxima atingida." << std::endl;
    }
}

const std::vector<Item>& Loja::getItens() const {
    return this->itens;
}

int Loja::getQuantidadeAtual() const {
    return this->quantidadeAtual;
}

int Loja::getCapacidadeMaxima() const {
    return this->itens.size();

}

bool Loja::salvarLoja(const std::string& nomeArquivo) const {
    std::ofstream arquivoSaida(nomeArquivo);

    //Verifica se o arquivo foi aberto corretamente
    if (!arquivoSaida.is_open()) {
        std::cerr << "Erro: Não foi possível abrir o arquivo: " << nomeArquivo << std::endl;
        return false;
    }

    //Itera sobre os itens existentes 
    for (int i = 0; i < this->quantidadeAtual; ++i) {
        const Item& item = this->itens[i];

        //Escreve os dados do item no arquivo no formato CSV:
        arquivoSaida << item.getId() << ","
                     << item.getNome() << ","
                     << item.getDescricao() << ","
                     << item.getValor() << "\n";
    }

    arquivoSaida.close();

    std::cout << "Inventário salvo com sucesso em: " << nomeArquivo << std::endl;
    return true;
}
