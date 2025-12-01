# --- Makefile Híbrido (Funciona em Windows e Linux) ---

# Nome do Executável Final
TARGET = sistema_hospital

# Compiladores
CXX = g++       # Para C++
CC  = gcc       # Para C (SQLite)

# Flags de Compilação
# -Wall: Avisos de erro
# -std=c++17: Versão moderna do C++
# -g: Debug
# -pthread: Necessário para Threads
CXXFLAGS = -Wall -std=c++17 -g -pthread
CFLAGS   = -std=c99 -g 

# ---------------------------------------------------------
# DETECÇÃO AUTOMÁTICA DO SISTEMA OPERACIONAL
# ---------------------------------------------------------
ifeq ($(OS),Windows_NT)
    # Configuração para WINDOWS
    # No Windows, não precisamos de -ldl
    LDFLAGS = -pthread
else
    # Configuração para LINUX
    # No Linux, PRECISAMOS de -ldl para o SQLite
    LDFLAGS = -pthread -ldl
endif
# ---------------------------------------------------------

# Pega automaticamente todos os arquivos .cpp
SRCS = $(wildcard *.cpp)

# Cria a lista de objetos .o
OBJS = $(SRCS:.cpp=.o)

# Adiciona o objeto do SQLite
OBJS_ALL = $(OBJS) sqlite3.o

# --- Regras ---

all: $(TARGET)

# Linkagem
$(TARGET): $(OBJS_ALL)
	@echo "Linkando o executavel no sistema: $(OS)"
	$(CXX) $(OBJS_ALL) -o $(TARGET) $(LDFLAGS)
	@echo "Sucesso! Execute: ./$(TARGET)"

# Compila arquivos .cpp
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compila o SQLite separadamente
sqlite3.o: sqlite3.c sqlite3.h
	@echo "Compilando biblioteca SQLite..."
	$(CC) $(CFLAGS) -c sqlite3.c -o sqlite3.o

# Limpeza (Compatível com ambos)
clean:
	rm -f *.o $(TARGET) $(TARGET).exe

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run