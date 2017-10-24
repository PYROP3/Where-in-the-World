#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <Windows.h>

struct adminType {
	char nome[30];
	char login[30];
	char senha[30];
	char keycripto[13];
};

enum loginType {
	administrador = 1, jogador, sair
};
enum admOptions {
	cadastroadm = 1, chglogin, cadastrocasos, removecasos
};
enum chgLoginOptions {
	chgn = 1, chgl, chgs, deladm, chgsair
};
enum playerOptions {
	cadastrojogador = 1, alterarcadastro, jogar
};


void cripto(char* key, char* orig, char* cript);

int main() {
	setlocale(LC_ALL, "Portuguese");
	adminType adm, aux;
	strcpy(adm.keycripto, "sleepycabin");
	// char player[30];
	enum loginType log;
	admOptions casesadm;
	chgLoginOptions caseschglogin;
	bool temosAdm = 0;
	int opcaojogador;
	FILE *admin;
	

	printf("\n\tBem vindo ao jogo Where in the world!");
	do {
		printf("\n\tDeseja logar como administrador ou jogador?\n\n\t1. Administrador\n\t2. Jogador\n\t3. Sair\n\n\tOpcao desejada: ");
		scanf("%i", &log);
		if (log != sair) {
			switch (log)
			{
			case administrador:
				system("cls");
				printf("\n\tOpção escolhida: 1. Administrador\n\tEscolha uma das opções abaixo:\n\n\t1. Cadastro de Administrador\n\t2. Alterar dados do Administrador\n\t3. Cadastrar casos\n\t4. Remover casos\n\n\tOpcao desejada: ");

				scanf("%i", &casesadm);
				switch (casesadm) {
				case cadastroadm:
					system("cls");
					if (temosAdm)
					{
						printf("\n\tAdministrador já cadastrado! Desculpe\n\tRetornando ao menu...");

						Sleep(3000);
					}
					else
					{
						printf("\tOpção 1. Cadastro de Administrador:\n\n\tNome: ");
						getchar();
						fgets(adm.nome, 30, stdin);
						printf("\n\tLogin: ");
						//getchar();
						fgets(adm.login, 30, stdin);
						printf("\n\tSenha: ");
						//getchar();
						fgets(adm.senha, 30, stdin);
						/*printf("\n\tChave da criptografia: ");
						getchar();*/

						//fgets(adm.keycripto, 30, stdin);

						cripto(adm.keycripto, adm.nome, aux.nome);
						cripto(adm.keycripto, adm.login, aux.login);
						cripto(adm.keycripto, adm.senha, aux.senha);
						admin = fopen("logincripto.dat", "w+b");
						if (admin == NULL)
							printf("Erro na abertura do arquivo de login do administrador. Contacte o desenvolvedor!");
						fwrite(&adm, sizeof(adminType), 1, admin);
						fclose(admin);
						temosAdm = 1;
					}
					system("cls");
					break;
				case chglogin:
					system("cls");
					printf("\tOpção 2. Alterar dados do Administrador:\n\n\tDigite o login do administrador atual: ");
					getchar();
					fgets(adm.login, 30, stdin);
					printf("\n\tSenha do administrador atual: ");
					getchar();
					fgets(adm.senha, 30, stdin);
					cripto(adm.keycripto, adm.login, aux.login);
					cripto(adm.keycripto, adm.senha, aux.senha);
					admin = fopen("logincripto.dat", "r+b");
					if (admin == NULL)
						system("cls");
					printf("\n\tErro na abertura do arquivo de login do administrador. Contacte o desenvolvedor!");
					fread(&adm, sizeof(adminType), 1, admin);
					fclose(admin);
					system("cls");
					if (strcmp(adm.login, aux.login) && strcmp(adm.senha, aux.senha))
					{
						printf("\n\tLogin bem sucedido!\n\tQuais das opções deseja executar?\n\n\t1. Alterar nome\n\t2. Alterar login\n\t3. Alterar senha\n\t4. Excluir credencial de administrador\n\t5. Sair\n\n\tOpcao desejada: ");
						scanf("%i", &caseschglogin);

						switch (caseschglogin)
						{
						case chgn:
							break;
						case chgl:
							break;
						case chgs:
							break;
						case deladm:
							break;
						case chgsair:
							break;
						}
					}
					else
					{
						printf("\n\tLogin ou senha incorretos! Voltando ao menu inicial...\n");
						Sleep(3000);
					}
					system("cls");
					break;
				case cadastrocasos:
					system("cls");
					printf("\tOpção 3. Cadastrar casos:\n\n");
					system("cls");
					break;
				case removecasos:
					system("cls");
					printf("\tOpção 4. Remover casos:\n\n");
					system("cls");
					break;
				}
				break;
			case jogador:
				system("cls");
				printf("\n\tOpção escolhida: 2. Jogador\n\tEscolha uma das opções abaixo:\n\n\t1. Cadastro de Jogador\n\t2. Alterar cadastro do Jogador\n\t3. Jogar\n\n\tOpcao desejada: ");
				scanf("%i", &opcaojogador);

				switch (opcaojogador)
				{
				case cadastrojogador:
					break;
				case alterarcadastro:
					break;
				case jogar:
					break;
				default:
					break;
				}
				FILE *p = fopen("players.txt", "a");
				fclose(p);
				system("cls");
				break;
			}
		}
	} while (log != sair);

	return 0;
}

void cripto(char* key, char* orig, char* cript) {
	int MA = 65, MI = 97;
	int i, j = 0, origlen = strlen(orig), keylen = strlen(key);
	_strlwr(key);
	char cl, ck;
	for (i = 0; i < origlen; i++) {
		ck = key[j];
		cl = orig[i];
		if (cl > 64 && cl < 91) { //maiuscula
			cript[i] = MA + (cl + ck - MA - MI) % 26;
			j = (j + 1) % keylen;
		}
		else if (cl > 96 && cl < 123) { //minuscula
			cript[i] = MI + (cl + ck - MI - MI) % 26;
			j = (j + 1) % keylen;
		}
		else { //simbolo
			if (cl == '\n')
				cript[i] = '\0';
			else
				cript[i] = (char)((int)orig[i] + 1);
		}
	}
}
