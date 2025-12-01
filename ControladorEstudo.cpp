#include "ControladorEstudo.h"
#include "RepositorioEstudos.h"
#include "RepositorioGamificacao.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <stdexcept>
#include <sstream>

// ===== CONSTRUTOR E DESTRUTOR =====

ControladorEstudo::ControladorEstudo(ControladorGamificacao* controladorG)
    : sessaoAtiva(nullptr), controladorGami(controladorG), estado("parado") {
}

ControladorEstudo::~ControladorEstudo() {
    if (sessaoAtiva != nullptr) {
        delete sessaoAtiva;
        sessaoAtiva = nullptr;
    }
}

// ===== MÉTODOS PRINCIPAIS =====

void ControladorEstudo::iniciarSessao() {
    // Verifica se já existe sessão ativa
    if (temSessaoAtiva()) {
        std::cout << "\nERRO: Ja existe uma sessao ativa!" << std::endl;
        std::cout << "Estado atual: " << estado << std::endl;
        std::cout << "Use 'pausar', 'continuar' ou 'finalizar' antes de iniciar nova sessao.\n" << std::endl;
        return;
    }
    
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════╗\n";
    std::cout << "║        NOVA SESSÃO DE ESTUDO           ║\n";
    std::cout << "╚════════════════════════════════════════╝\n";
    
    // Coleta dados da sessão
    std::string disciplina, descricao;
    
    std::cin.ignore(); // Limpa buffer do teclado
    
    // Disciplina 
    while (true) {
        std::cout << "\n📚 Disciplina: ";
        std::getline(std::cin, disciplina);
        
        if (!disciplina.empty()) {
            break;
        }
        std::cout << "AVISO: A disciplina nao pode ficar em branco!\n";
    }
    
    // Descrição (opcional)
    std::cout << "📝 Descricao (opcional, pressione Enter para pular): ";
    std::getline(std::cin, descricao);
    
    try {
        // Cria nova sessão
        sessaoAtiva = new SessaoEstudo(0, 0, disciplina, descricao);
        
        // Inicia a sessão
        sessaoAtiva->iniciar();
        estado = "rodando";
        
        std::cout << "\n";
        std::cout << "╔════════════════════════════════════════╗\n";
        std::cout << "║           SESSÃO INICIADA              ║\n";
        std::cout << "╚════════════════════════════════════════╝\n";
        std::cout << " Disciplina: " << disciplina << std::endl;
        std::cout << " Inicio: " << sessaoAtiva->getDataInicio() 
                  << " as " << sessaoAtiva->getHorarioInicio() << std::endl;
        std::cout << "\n⏱️  Cronometro iniciado! Bons estudos!\n" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "\n ERRO CRITICO: Falha ao iniciar sessao: " << e.what() << std::endl;
        if (sessaoAtiva != nullptr) {
            delete sessaoAtiva;
            sessaoAtiva = nullptr;
        }
        estado = "parado";
    }
}

void ControladorEstudo::pausarSessao() {
    if (!temSessaoAtiva() || estado != "rodando") {
        std::cout << "\n ERRO: Nao ha sessao rodando para pausar.\n" << std::endl;
        return;
    }
    
    try {
        // Pausa a sessão
        sessaoAtiva->pausar();
        estado = "pausado";
        
        // Mostra tempo parcial
        long long segundos = sessaoAtiva->getSegundos();
        
        std::cout << "\n";
        std::cout << "╔════════════════════════════════════════╗\n";
        std::cout << "║           SESSÃO PAUSADA               ║\n";
        std::cout << "╚════════════════════════════════════════╝\n";
        std::cout << " Sessao pausada com sucesso!\n";
        std::cout << "⏸️  Tempo parcial: " << formatarTempo(segundos) << std::endl;
        std::cout << "\nUse 'continuar' para retomar ou 'finalizar' para encerrar.\n" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "\n ERRO: Falha ao pausar sessao: " << e.what() << std::endl;
    }
}

void ControladorEstudo::continuarSessao() {
    if (!temSessaoAtiva() || estado != "pausado") {
        std::cout << "\n ERRO: Nao ha sessao pausada para continuar.\n" << std::endl;
        return;
    }
    
    try {
        // Continua a sessão
        sessaoAtiva->continuar();
        estado = "rodando";
        
        std::cout << "\n";
        std::cout << "╔════════════════════════════════════════╗\n";
        std::cout << "║          SESSÃO RETOMADA               ║\n";
        std::cout << "╚════════════════════════════════════════╝\n";
        std::cout << " Cronometro retomado!\n";
        std::cout << " Disciplina: " << sessaoAtiva->getDisciplina() << std::endl;
        std::cout << " Tempo ate agora: " << formatarTempo(sessaoAtiva->getSegundos()) << std::endl;
        std::cout << "\n⏱️  Continue seus estudos!\n" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "\n ERRO: Falha ao continuar sessao: " << e.what() << std::endl;
    }
}

void ControladorEstudo::finalizarSessao(Usuario* usuario) {
    if (!temSessaoAtiva()) {
        std::cout << "\n ERRO: Nao ha sessao ativa para finalizar.\n" << std::endl;
        return;
    }
    
    // Confirmação do usuário
    std::cout << "\n⚠️  Voce realmente deseja finalizar esta sessao? (s/n): ";
    char confirmacao;
    std::cin >> confirmacao;
    std::cin.ignore(); // Limpa buffer
    
    if (confirmacao != 's' && confirmacao != 'S') {
        std::cout << "Operacao cancelada.\n" << std::endl;
        return;
    }
    
    try {
        // Finaliza a sessão
        sessaoAtiva->finalizar();
        
        // Calcula tempo total
        long long segundosTotais = sessaoAtiva->getSegundos();
        
        // Exibe resumo
        exibirResumoSessao();
        
        // Atualiza gamificação
        atualizarGamificacao(segundosTotais);
        
        // Salva a sessão no repositório
        salvarSessao(usuario);
        
        // Limpa a sessão
        delete sessaoAtiva;
        sessaoAtiva = nullptr;
        estado = "parado";
        
        std::cout << "\n✅ Sessao finalizada e salva com sucesso!\n" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "\n ERRO: Falha ao finalizar sessao: " << e.what() << std::endl;
    }
}

void ControladorEstudo::cancelarSessao() {
    if (!temSessaoAtiva()) {
        std::cout << "\n Nao ha sessao ativa para cancelar.\n" << std::endl;
        return;
    }
    
    std::cout << "\n⚠️  ATENCAO: Esta acao ira descartar a sessao atual! (s/n): ";
    char confirmacao;
    std::cin >> confirmacao;
    std::cin.ignore();
    
    if (confirmacao != 's' && confirmacao != 'S') {
        std::cout << "Operacao cancelada.\n" << std::endl;
        return;
    }
    
    // Descarta a sessão
    delete sessaoAtiva;
    sessaoAtiva = nullptr;
    estado = "parado";
    
    std::cout << "\n🗑️  Sessao descartada.\n" << std::endl;
}

// ===== MÉTODOS DE CONSULTA =====

void ControladorEstudo::mostrarProgresso() const {
    if (!temSessaoAtiva()) {
        std::cout << "\n📊 Nenhuma sessao ativa no momento.\n" << std::endl;
        return;
    }
    
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════╗\n";
    std::cout << "║          PROGRESSO ATUAL               ║\n";
    std::cout << "╚════════════════════════════════════════╝\n";
    
    std::cout << "📚 Disciplina: " << sessaoAtiva->getDisciplina() << std::endl;
    
    std::string descricao = sessaoAtiva->getDescricao();
    if (!descricao.empty()) {
        std::cout << "📝 Descricao: " << descricao << std::endl;
    }
    
    std::cout << "📅 Data inicio: " << sessaoAtiva->getDataInicio() 
              << " as " << sessaoAtiva->getHorarioInicio() << std::endl;
    
    std::cout << "🎯 Estado: ";
    if (estado == "rodando") {
        std::cout << "EM ANDAMENTO ⏱️" << std::endl;
    } else if (estado == "pausado") {
        std::cout << "PAUSADO ⏸️" << std::endl;
    }
    
    long long segundos = sessaoAtiva->getSegundos();
    std::cout << "⏱️  Tempo: " << formatarTempo(segundos) << std::endl;
    
    // Barra de progresso simples
    std::cout << "\n[";
    int pontos = (segundos / 60) % 50; // 1 ponto a cada minuto, máximo 50
    for (int i = 0; i < 50; i++) {
        if (i < pontos) {
            std::cout << "+";
        } else {
            std::cout << "-";
        }
    }
    std::cout << "]\n" << std::endl;
}

void ControladorEstudo::mostrarEstatisticas() const {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════╗\n";
    std::cout << "║           ESTATÍSTICAS                 ║\n";
    std::cout << "╚════════════════════════════════════════╝\n";
    
    if (controladorGami != nullptr) {
        // Usa o método mostrarBadges do ControladorGamificacao
        controladorGami->mostrarBadges();
    } else {
        std::cout << "📊 Sistema de gamificacao nao disponivel.\n" << std::endl;
    }
}

void ControladorEstudo::mostrarHistorico() const {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════╗\n";
    std::cout << "║           HISTÓRICO                    ║\n";
    std::cout << "╚════════════════════════════════════════╝\n";
    
    // Esta funcionalidade agora é possível com os repositórios
    // Mas precisamos de um usuário para buscar o histórico
    std::cout << "📅 Use o método mostrarHistoricoCompleto(Usuario*) para ver o histórico.\n" << std::endl;
}

// Novo método para mostrar histórico completo
void ControladorEstudo::mostrarHistoricoCompleto(Usuario* usuario) const {
    if (usuario == nullptr) {
        std::cout << "\n ERRO: Usuario nao especificado.\n" << std::endl;
        return;
    }
    
    try {
        RepositorioEstudos repo(usuario->getNome());
        std::vector<SessaoEstudo> historico = repo.obterHistorico();
        
        std::cout << "\n";
        std::cout << "╔══════════════════════════════════════════════════╗\n";
        std::cout << "║              HISTÓRICO COMPLETO                  ║\n";
        std::cout << "╚══════════════════════════════════════════════════╝\n";
        
        if (historico.empty()) {
            std::cout << "📭 Nenhuma sessao registrada ainda.\n" << std::endl;
            return;
        }
        
        std::cout << "📊 Total de sessoes: " << historico.size() << std::endl;
        std::cout << "⏱️  Tempo total estudado: " << formatarTempo(repo.getTempoTotal()) << std::endl;
        std::cout << "\n";
        std::cout << "═══════════════════════════════════════════════════\n";
        
        for (size_t i = 0; i < historico.size(); i++) {
            const SessaoEstudo& sessao = historico[i];
            
            std::cout << "\n📚 Sessao #" << (i + 1) << std::endl;
            std::cout << "   Disciplina: " << sessao.getDisciplina() << std::endl;
            
            std::string desc = sessao.getDescricao();
            if (!desc.empty() && desc != " ") {
                std::cout << "   Descricao: " << desc << std::endl;
            }
            
            std::cout << "   Data: " << sessao.getDataInicio();
            if (!sessao.getDataFinal().empty()) {
                std::cout << " a " << sessao.getDataFinal();
            }
            std::cout << std::endl;
            
            std::cout << "   Horario: " << sessao.getHorarioInicio();
            if (!sessao.getHorarioFinal().empty()) {
                std::cout << " - " << sessao.getHorarioFinal();
            }
            std::cout << std::endl;
            
            std::cout << "   Tempo: " << formatarTempo(sessao.getSegundos()) << std::endl;
            
            if (i < historico.size() - 1) {
                std::cout << "   ─────────────────────────────────\n";
            }
        }
        
        std::cout << "\n═══════════════════════════════════════════════════\n" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "\n[ERRO] Falha ao carregar historico: " << e.what() << std::endl;
    }
}

// ===== MÉTODOS AUXILIARES =====

bool ControladorEstudo::temSessaoAtiva() const {
    return sessaoAtiva != nullptr && estado != "parado";
}

std::string ControladorEstudo::getEstado() const {
    return estado;
}

SessaoEstudo* ControladorEstudo::getSessaoAtiva() const {
    return sessaoAtiva;
}

// ===== MÉTODOS PRIVADOS =====

void ControladorEstudo::salvarSessao(Usuario* usuario) {
    if (sessaoAtiva == nullptr || usuario == nullptr) {
        std::cout << "[AVISO] Nao foi possivel salvar a sessao.\n" << std::endl;
        return;
    }
    
    try {
        // Cria repositório de estudos
        RepositorioEstudos repoEstudos(usuario->getNome());
        
        // Adiciona a sessão ao repositório
        repoEstudos.adicionarSessao(*sessaoAtiva);
        
        std::cout << "💾 Sessao salva no repositorio: " << usuario->getNome() << "_estudos.txt" << std::endl;
        
        // Mostra estatísticas atualizadas
        std::cout << "📊 Estatisticas atualizadas:" << std::endl;
        std::cout << "   • Total de sessoes: " << repoEstudos.getQuantidade() << std::endl;
        std::cout << "   • Tempo total: " << formatarTempo(repoEstudos.getTempoTotal()) << std::endl;
        std::cout << "   • Tempo em " << sessaoAtiva->getDisciplina() << ": " 
                  << formatarTempo(repoEstudos.getTempoTotalPorDisciplina(sessaoAtiva->getDisciplina())) << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "[ERRO] Falha ao salvar sessao no repositorio: " << e.what() << std::endl;
    }
}

void ControladorEstudo::atualizarGamificacao(long long segundos) {
    if (controladorGami != nullptr && segundos > 0) {
        int minutos = segundos / 60;
        
        // Adiciona tempo de estudo
        controladorGami->adicionarTempoEstudo(minutos);
        
        std::cout << "🏆 Progresso salvo no sistema de gamificacao!" << std::endl;
        std::cout << "⏱️  " << minutos << " minutos adicionados ao seu tempo total.\n" << std::endl;
    }
}

std::string ControladorEstudo::formatarTempo(long long segundos) const {
    int horas = segundos / 3600;
    int minutos = (segundos % 3600) / 60;
    int segs = segundos % 60;
    
    std::stringstream ss;
    
    if (horas > 0) {
        ss << horas << "h ";
    }
    
    if (minutos > 0 || horas > 0) {
        ss << minutos << "m ";
    }
    
    ss << segs << "s";
    return ss.str();
}

void ControladorEstudo::exibirResumoSessao() const {
    if (sessaoAtiva == nullptr) {
        return;
    }
    
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════╗\n";
    std::cout << "║           RESUMO DA SESSÃO             ║\n";
    std::cout << "╚════════════════════════════════════════╝\n";
    
    std::cout << "📚 Disciplina: " << sessaoAtiva->getDisciplina() << std::endl;
    
    std::string descricao = sessaoAtiva->getDescricao();
    if (!descricao.empty() && descricao != " ") {
        std::cout << "📝 Descricao: " << descricao << std::endl;
    }
    
    std::cout << "📅 Inicio: " << sessaoAtiva->getDataInicio() 
              << " as " << sessaoAtiva->getHorarioInicio() << std::endl;
    
    std::string dataFinal = sessaoAtiva->getDataFinal();
    std::string horaFinal = sessaoAtiva->getHorarioFinal();
    
    if (!dataFinal.empty() && dataFinal != " ") {
        std::cout << "📅 Fim: " << dataFinal << " as " << horaFinal << std::endl;
    }
    
    long long segundos = sessaoAtiva->getSegundos();
    std::cout << "⏱️  Tempo total: " << formatarTempo(segundos) << std::endl;
    std::cout << "==========================================\n" << std::endl;
}