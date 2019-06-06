#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	
	int id;
	char titulo[102];
	char genero[20];
	char clas[30];
	char cpf_usuario_alugou[13]; // se for " " (s[0]=0), ent�o o filme est� dispon�vel
	
} filme;

typedef struct {
	
	char nome[102];
	char cpf[13];
	char endereco[102];
	char telefone[15];
	
} cliente;

cliente cadastrar_cliente();
cliente* inserirCliente(cliente *vCliente, int *ncliente, cliente novo );
cliente* removerCliente(cliente *vCliente , char cpf[11], int *ncliente);
void clientes_para_arquivo(cliente *vCliente, int *ncliente);
cliente* carrega_cliente_arquivo(cliente *vCliente, int *ncliente);
filme cadastrar_filme();
filme* inserirCadastro(filme *v, int *nfilme, filme novo);
filme* removerfilme(filme *v , int id, int *nfilme);
void alugar_filme(filme *v, cliente *vCliente, int *nfilme, int *ncliente);
void devolver_filme(filme *v, int *nfilme, cliente *vCliente, int *ncliente);
void relatorios_de_filmes(filme *v, int *nfilme);
void filmes_para_arquivo(filme *v, int *nfilme);
filme* carrega_filme_arquivo(filme *v, int *nfilme);
void menu();
