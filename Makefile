# Nome do projeto
PROJ_NAME=ProgramRelease
 
# recebe todos arquivos com terminacao .c
C_SOURCE=$(wildcard *.c)
 
# recebe todos os arquivos com terminacao .h
H_SOURCE=$(wildcard *.h)
 
# indica todos arquivos .o necessarios baseado na existencia dos arquivos .o
OBJ=$(C_SOURCE:.c=.o)
 
# Compiler
CC=gcc

#flag necessaria para a execucao das funcoes da API pthreads
LDFLAGS = -pthread

# Flags for compiler
CC_FLAGS=-c         \
		-Wall		\
 

# objetivo a ser compilado

all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

#dependencias necessarias para obtencao do executavel 
%.o: %.c %.h
	$(CC) -o $@ $< $(CC_FLAGS)

#limpa todos os arquivos gerados pelo compilador 
clean:
	rm -rf *.o $(PROJ_NAME) *~