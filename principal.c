#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "minha_biblioteca.h"

/* MINOR BUGS FIXED */

int main() {
	
	int op = 0;
	filme *v = 0;
	cliente *vCliente = 0;
	int i, nfilme = 0, ncliente = 0; 
	v = carrega_filme_arquivo(v, &nfilme);
	vCliente = carrega_cliente_arquivo(vCliente, &ncliente);
	
	while (op != 10) {
		
		menu();
		
		scanf("%d", &op);
		
		switch(op) {
			
			case 1: {
				filme a = cadastrar_filme(); // filme a eh o filme a ser lido, depois incluido.
				v = inserirCadastro(v, &nfilme, a);
				system("cls"); // funcao para limpar a tela(Cabivel de mudanca)
				printf("Filme adicionado com sucesso!\n");
				break;
			}
			
			case 2: {
				cliente c = cadastrar_cliente(); // Cliente a ser lido, depois incluido.
				vCliente = inserirCliente(vCliente, &ncliente, c);
				system("cls"); // funcao para limpar a tela(Cabivel de mudanca)
				printf("Cliente adicionado com sucesso!\n");
				break;
			}
			
			case 3: {  //listar filmes
    			for(i = 0; i < nfilme; i++) {
    				printf("ID: %d\nTitulo: %sGenero: %sClassificacao: %sAlugado para: %s\n", v[i].id, v[i].titulo, v[i].genero, v[i].clas, v[i].cpf_usuario_alugou);
				}
				
				if(nfilme == 0) // caso a quantidade n do vetor volte a ser 0, nao vai ter nada, entao adicionei essa condicao
				printf("Nao ha nenhum filme cadastrado.\n"); 
				break;
			}
			
			case 4: { // listar clientes
    			for (i = 0; i < ncliente; i++) {
    				printf("Nome: %sCPF: %sEndereco: %sTelefone: %s\n", vCliente[i].nome, vCliente[i].cpf, vCliente[i].endereco, vCliente[i].telefone);
				}
				if(ncliente == 0) // caso a quantidade n do vetor volte a ser 0, nao vai ter nada, entao adicionei essa condicao
					printf("Nao ha nenhum cliente cadastrado.\n"); 
				break;
			}
			
			case 5: { // remover filme
				int id;
				printf("Digite o ID do filme a ser removido: ");
				scanf("%d", &id);
				v = removerfilme(v, id, &nfilme);
				//system("cls"); // funcao para limpar a tela(Cabivel de mudanca)
				break;
			}
			
			case 6: { // remover cliente
				char cpf[13];
				printf("Digite o CPF do cliente a ser removido: ");
				getchar();
				fgets(cpf, sizeof(cpf), stdin);
				setbuf(stdin, NULL);
				vCliente = removerCliente(vCliente, cpf, &ncliente); // vCliente recebe pq a funcao retorna para ele
				//system("cls"); // funcao para limpar a tela(Cabivel de mudanca)
				break;
			}
			
			case 7: { // alugar o filme
				alugar_filme(v, vCliente, &nfilme, &ncliente);
				break;
			}	
			
			case 8: {
				devolver_filme(v, &nfilme, vCliente, &ncliente);
				break;
			}
			
			case 9: { // relatórios de filmes alugados
				relatorios_de_filmes(v, &nfilme);
				break;
			}
			case 10: {
				filmes_para_arquivo(v, &nfilme); //colocando os dados no arquivo
				clientes_para_arquivo(vCliente, &ncliente);	
				return 0;	
				break;
			}
	    }		      
	}   
			
	if (v == 0) {
        printf("Erro na alocacao!\n");
        return 1;
    }
	
	free(v);
	
	if(vCliente == 0) {
		printf("Erro na alocacao!\n");
		return 1;
	}
	
	free(vCliente);
	
	return 0;
}
