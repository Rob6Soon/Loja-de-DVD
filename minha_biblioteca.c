#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "minha_biblioteca.h"

cliente cadastrar_cliente() {
	cliente c;
	
	printf("Nome: ");
	getchar();
	fgets(c.nome, sizeof(c.nome), stdin);
	setbuf(stdin, NULL);
	
	printf("CPF: ");
	
	fgets(c.cpf, sizeof(c.cpf), stdin);
	setbuf(stdin, NULL);
	
	printf("Endereco: ");
	fgets(c.endereco, sizeof(c.endereco), stdin);
	setbuf(stdin, NULL);
	
	printf("Telefone: ");
	fgets(c.telefone, sizeof(c.telefone), stdin);
	setbuf(stdin, NULL);
	
	return c;
}

cliente* inserirCliente(cliente *vCliente, int *ncliente, cliente novo ) {
	
	vCliente = (cliente*) realloc(vCliente, (*ncliente+1)*sizeof(cliente)); 
	if(vCliente == 0) return 0;
	
	vCliente[*ncliente] = novo;
	(*ncliente)++;
	
	return vCliente;
}

cliente* removerCliente(cliente *vCliente , char cpf[11], int *ncliente) {

    int i, encontrou = 0;
    for(i = 0; i < *ncliente; i++) {
        if(strcmp(vCliente[i].cpf, cpf) == 0) {
            vCliente[i] = vCliente[*ncliente-1];
            vCliente = (cliente*) realloc(vCliente, (*ncliente-1)*sizeof(cliente));
            (*ncliente)--;
            encontrou = 1;
        }
    }
    if(!encontrou)
       	printf("CPF nao encontrado.\n");
    else
    	printf("Cliente removido.\n");
    	
    return vCliente;
}

void clientes_para_arquivo(cliente *vCliente, int *ncliente) {
	
     FILE *f = fopen("qtd_clientes.txt", "w");
	if(f != NULL && *ncliente > 0) {
		fwrite(ncliente, sizeof(int), 1, f);
		fclose(f);
	} // descobrir a quantidade de n
	
	f = fopen("clientes.txt", "w");
	if(f != NULL && *ncliente > 0) {
		fwrite(vCliente, sizeof(cliente), *ncliente, f);
		fclose(f);
	}
}

cliente* carrega_cliente_arquivo(cliente *vCliente, int *ncliente) { // ler do arquivo para o sistema

	FILE *f = fopen("qtd_clientes.txt", "r");
	if(f != NULL){
		fread(ncliente, sizeof(int), 1, f);
		fclose(f);
	} // descobrir a quantidade de n
	
	f = fopen("clientes.txt", "r");
	if(f != NULL) {
		vCliente = malloc (sizeof(cliente)*(*ncliente));
		fread(vCliente, sizeof(cliente), *ncliente, f);
		fclose(f);
	}	
	
	return vCliente;
}

filme cadastrar_filme() {
	
	filme f;
	
	printf("ID: ");
	scanf("%d", &f.id);
	setbuf(stdin, NULL); // limpar o buffer do teclado
	
	printf("Nome: ");
	fgets(f.titulo, sizeof(f.titulo), stdin);
	
	printf("Genero: ");
	fgets(f.genero, sizeof(f.genero), stdin);
	setbuf(stdin, NULL);
	
	printf("Classificacao: ");
	fgets(f.clas, sizeof(f.clas), stdin);
	setbuf(stdin, NULL);
	
	f.cpf_usuario_alugou[0] = '0';
	f.cpf_usuario_alugou[1] = 0;
	
	
	return f; 
}

filme* inserirCadastro(filme *v, int *nfilme, filme novo) {
	
	v = (filme*) realloc(v, (*nfilme+1)*sizeof(filme));
	if(v == 0) return 0;
	
	v[*nfilme] = novo;
	(*nfilme)++;
	return v;
}

filme* removerfilme(filme *v , int id, int *nfilme) {

    int i, encontrou = 0;
    for(i = 0; i < *nfilme; i++) {
        if(v[i].id == id) {
            v[i] = v[*nfilme-1];
            v = (filme*) realloc(v, (*nfilme-1)*sizeof(filme));
            (*nfilme)--;
            encontrou = 1;
		}
    }
    if(!encontrou)
       	printf("ID nao encontrado.\n");
    else
    	printf("Filme removido.\n");
    return v;
}

void alugar_filme(filme *v, cliente *vCliente, int *nfilme, int *ncliente) {
	
	int id, i, j, alugado = 0, filme_existe = 0;
	char cpf[13];
	
	printf("Digite o ID do filme: ");
	scanf("%d", &id);
	setbuf(stdin, NULL);
	printf("Digite o CPF do cliente: ");
	fgets(cpf, sizeof(cpf), stdin);
	
	for(i = 0; i < *nfilme; i++) {
		for(j = 0; j < *ncliente; j++) {		
			if(id == v[i].id) {
				filme_existe = 1;
				if(strcmp (cpf, vCliente[j].cpf) == 0) {
					strcpy(v[i].cpf_usuario_alugou, cpf);
					alugado = 1;
				}
			}
		}
	}
	system("cls");
	if(alugado)printf("Filme %d alugado por cliente de CPF %s\n", id, cpf);
	else if(!filme_existe) printf("O filme nao existe.\n");
	else printf("Cliente nao existe.\n");
}

void devolver_filme(filme *v, int *nfilme, cliente *vCliente, int *ncliente) {
	
	int id, i, devolveu = 0, id_existe = 0;
	char cpf[13];
	printf("Digite o ID do filme a ser devolvido: ");
	scanf("%d", &id);
	setbuf(stdin, NULL);
	printf("Digite o CPF do cliente: ");
	fgets(cpf, sizeof(cpf), stdin);
	
	for(i = 0; i < *nfilme; i++) {
		if(id == v[i].id) {
			id_existe = 1;
			if(strcmp(cpf, v[i].cpf_usuario_alugou) == 0) {
				v[i].cpf_usuario_alugou[0] = '0';
				v[i].cpf_usuario_alugou[1] = 0;
				devolveu = 1;
			}
		}
	}
	if(devolveu) printf("Filme devolvido.\n");
	else if(!id_existe) printf("ID incorreto.\n");
	else printf("Locacao inexistente.\n");
}

void relatorios_de_filmes(filme *v, int *nfilme) {
	
	int i;
	for(i = 0; i < *nfilme; i++) {
		if( !(v[i].cpf_usuario_alugou[0] == '0' && v[i].cpf_usuario_alugou[1] == 0) )
			printf("ID: %d\nTitulo: %sGenero: %sClassificacao: %sAlugado para: %s\n", v[i].id, v[i].titulo, v[i].genero, v[i].clas, v[i].cpf_usuario_alugou);
	}
}

void filmes_para_arquivo(filme *v, int *nfilme) {
    
    FILE *f = fopen("qtd_filmes.txt", "w");
	if(f != NULL && *nfilme > 0) {
		fwrite(nfilme, sizeof(int), 1, f);
		fclose(f);
	} // descobrir a quantidade de n
	
	f = fopen("filmes.txt", "w");
	if(f != NULL && *nfilme > 0) {
		fwrite(v, sizeof(filme), *nfilme, f);
		fclose(f);
	}

}

filme* carrega_filme_arquivo(filme *v, int *nfilme) { // ler do arquivo para o sistema

	FILE *f = fopen("qtd_filmes.txt", "r");
	if(f != NULL){
		fread(nfilme, sizeof(int), 1, f);
		fclose(f);
	} // descobrir a quantidade de n
	
	f = fopen("filmes.txt", "r");
	if(f != NULL) {
		v = malloc (sizeof(filme)*(*nfilme));
		fread(v, sizeof(filme), *nfilme, f);
		fclose(f);
	}	
	return v;
}

void menu() {
		
	printf("\t\t|******************************************************|\n");
	printf("\t\t|*                                                    *|\n");
	printf("\t\t|*                    BEM VINDO!                      *|\n");
	printf("\t\t|*                                                    *|\n");
	printf("\t\t|*                LOCADORA DO BARUEL                  *|\n");
	printf("\t\t|*                                                    *|\n");
	printf("\t\t|*~~~~~~~~~~~~~~~~~~~~~~~ MENU ~~~~~~~~~~~~~~~~~~~~~~~*|\n");
	printf("\t\t|*                                                    *|\n");
	printf("\t\t|*                 1 - Cadastrar Filme                *|\n");
	printf("\t\t|*                 2 - Cadastrar Cliente              *|\n");
	printf("\t\t|*                 3 - Listar Filmes                  *|\n");
	printf("\t\t|*                 4 - Listar Clientes                *|\n");
	printf("\t\t|*                 5 - Remover Filme                  *|\n");
	printf("\t\t|*                 6 - Remover Cliente                *|\n");
	printf("\t\t|*                 7 - Alugar Filme                   *|\n");
	printf("\t\t|*                 8 - Devolucao                      *|\n");
	printf("\t\t|*                 9 - Relatorios                     *|\n");
	printf("\t\t|*                 10 - Sair                          *|\n");
	printf("\t\t|*                                                    *|\n");
	printf("\t\t|******************************************************|\n");	

}

