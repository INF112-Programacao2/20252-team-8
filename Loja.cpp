#include "Loja.h" 
#include <iostream> 
#include <fstream>
#include <algorithm>
#include <stdexcept>

Loja::Loja(int capacidade) : capacidadeMaxima(capacidade) {}

void Loja::adicionarItem(const Item& item) {
    try {
        // Verifica se a loja está cheia 
        if (itens.size() >= capacidadeMaxima) {
            throw std::runtime_error("Erro: Inventário está cheio! Capacidade máxima atingida: " + 
                                    std::to_string(capacidadeMaxima));
        }
        
        // Verifica se item com mesmo ID já existe 
        for (const auto& itemExistente : itens) {
            if (itemExistente.getId() == item.getId()) {
                throw std::runtime_error("Erro: Item com ID '" + item.getId() + "' já existe no inventário");
            }
        }
        
        itens.push_back(item);
        
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }
}

int Loja::getQuantidadeAtual() const {
    try {
        return itens.size();  
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}

int Loja::getCapacidadeMaxima() const {
    return capacidadeMaxima;
}

bool Loja::estaCheia() const {
    return itens.size() >= capacidadeMaxima;
}

const std::vector<Item>& Loja::getItens() const {
    return this->itens;
}

bool Loja::salvarLoja(const std::string& nomeArquivo) const {
    try {
        // Validação do nome do arquivo 
        if (nomeArquivo.empty()) {
            throw std::invalid_argument("Erro: Nome do arquivo não pode estar vazio");
        }
        
        std::ofstream arquivoSaida(nomeArquivo);

        // Verifica se o arquivo foi aberto corretamente 
        if (!arquivoSaida.is_open()) {
            throw std::runtime_error("Erro: Não foi possível abrir o arquivo: " + nomeArquivo);
        }

        // Verifica se há itens para salvar 
        if (itens.empty()) {
            std::cout << "Aviso: Nenhum item para salvar no inventário" << std::endl;
            arquivoSaida.close();
            return true;
        }

        // Itera sobre os itens existentes 
        for (size_t i = 0; i < itens.size(); ++i) {
            const Item& item = itens[i];

            // Escreve os dados do item no arquivo no formato CSV
            arquivoSaida << item.getId() << ","
                         << item.getNome() << ","
                         << item.getDescricao() << ","
                         << item.getValor();
            
            // Adiciona quebra de linha se não for o último item
            if (i < itens.size() - 1) {
                arquivoSaida << "\n";
            }

            // Verifica se ocorreu erro durante a escrita 
            if (arquivoSaida.fail()) {
                throw std::runtime_error("Erro de escrita no arquivo");
            }
        }

        // Verifica se a gravação foi bem-sucedida
        if (arquivoSaida.bad()) {
            throw std::runtime_error("Erro crítico durante a gravação do arquivo");
        }

        arquivoSaida.close();
        
        std::cout << "Inventário salvo com sucesso em: " << nomeArquivo 
                  << " (" << itens.size() << " itens salvos)" << std::endl;
        return true;

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

bool Loja::carregarLoja(const std::string& nomeArquivo) {
    try {
        // Validação do nome do arquivo 
        if (nomeArquivo.empty()) {
            throw std::invalid_argument("Erro: Nome do arquivo não pode estar vazio");
        }
        
        std::ifstream arquivoEntrada(nomeArquivo);
        
        // Verifica se arquivo existe 
        if (!arquivoEntrada.is_open()) {
            throw std::runtime_error("Erro: Não foi possível abrir o arquivo para leitura: " + nomeArquivo);
        }
        
        // Limpa itens atuais antes de carregar
        itens.clear();
        
        std::string linha;
        int linhaNumero = 0;
        int itensCarregados = 0;
        
        while (std::getline(arquivoEntrada, linha)) {
            linhaNumero++;
            
            // Pula linhas vazias
            if (linha.empty()) {
                continue;
            }
            
            // Verifica se a loja está cheia 
            if (itens.size() >= capacidadeMaxima) {
                std::cout << "Aviso: Capacidade máxima atingida. Parando carregamento na linha " << linhaNumero << std::endl;
                break;
            }
            
            // Processamento do CSV (usuário pode ter arquivo corrompido)
            size_t pos1 = linha.find(',');
            size_t pos2 = linha.find(',', pos1 + 1);
            size_t pos3 = linha.find(',', pos2 + 1);
            
            if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos) {
                std::cerr << "Aviso: Formato inválido na linha " << linhaNumero << " - pulando" << std::endl;
                continue;
            }
            
            std::string id = linha.substr(0, pos1);
            std::string nome = linha.substr(pos1 + 1, pos2 - pos1 - 1);
            std::string descricao = linha.substr(pos2 + 1, pos3 - pos2 - 1);
            int valor;
            
            try {
                valor = std::stoi(linha.substr(pos3 + 1));
            } catch (const std::exception&) {
                std::cerr << "Aviso: Valor inválido na linha " << linhaNumero << " - pulando" << std::endl;
                continue;
            }
            
            // Verifica se item já existe (pode acontecer em arquivo com duplicatas)
            bool duplicata = false;
            for (const auto& itemExistente : itens) {
                if (itemExistente.getId() == id) {
                    std::cerr << "Aviso: Item duplicado com ID '" << id << "' na linha " << linhaNumero << " - pulando" << std::endl;
                    duplicata = true;
                    break;
                }
            }
            
            if (!duplicata) {
                itens.push_back(Item(id, nome, descricao, valor));
                itensCarregados++;
            }
        }
        
        if (arquivoEntrada.bad()) {
            throw std::runtime_error("Erro de leitura do arquivo");
        }
        
        arquivoEntrada.close();
        
        if (itensCarregados == 0) {
            std::cout << "Aviso: Nenhum item válido foi carregado do arquivo" << std::endl;
        } else {
            std::cout << "Carregados " << itensCarregados << " itens do arquivo: " << nomeArquivo << std::endl;
        }
        
        return true;
        
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}