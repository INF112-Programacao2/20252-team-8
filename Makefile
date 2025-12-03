# ==========================================
# Configurações do Compilador e Flags
# ==========================================

# Compilador a ser usado
CXX = g++

# Flags de compilação:
# -std=c++17: Usa uma versão moderna do C++
# -Wall: Mostra avisos de código (ajuda a evitar bugs)
# -g: Adiciona símbolos de debug (útil se precisares usar gdb/valgrind)
CXXFLAGS = -std=c++17 -Wall -g

# Bibliotecas necessárias (Baseado no teu comando: -lpthread -ldl -lm)
# Necessárias para o miniaudio funcionar corretamente no Linux/Unix
LIBS = -lpthread -ldl -lm

# Nome do executável final
TARGET = AppEstudos

# ==========================================
# Arquivos do Projeto
# ==========================================

# A função wildcard pega todos os arquivos .cpp da pasta atual automaticamente
SRCS = $(wildcard *.cpp)

# Cria a lista de objetos (.o) trocando a extensão dos fontes
OBJS = $(SRCS:.cpp=.o)

# ==========================================
# Regras de Compilação
# ==========================================

# Regra padrão: executada quando se digita apenas 'make'
all: $(TARGET)

# Fase de Linkagem: Junta todos os objetos (.o) e bibliotecas para criar o executável
$(TARGET): $(OBJS)
	@echo "Linkando o executavel: $(TARGET)..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
	@echo "Sucesso! Execute com: ./$(TARGET) ou make run"

# Fase de Compilação: Transforma cada .cpp em um .o individualmente
# Se você alterar apenas um arquivo, ele só recompila esse arquivo (mais rápido)
%.o: %.cpp
	@echo "Compilando: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ==========================================
# Utilitários
# ==========================================

# Regra para limpar arquivos compilados (útil para recompilar do zero)
# Uso: make clean
clean:
	@echo "Limpando arquivos temporarios..."
	rm -f $(OBJS) $(TARGET)

# Regra para compilar e rodar imediatamente
# Uso: make run
run: all
	@echo "Executando o programa..."
	./$(TARGET)

.PHONY: all clean run
