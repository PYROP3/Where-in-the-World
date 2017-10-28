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

struct tipoJogador{
	char nome[30];
	char login[30];
	char senha[30];
	int pontos;

};

enum loginType {
	administrador = 1, jogado, sair
};
enum admOptions {
	cadastroadm = 1, chglogin, cadastrocasos, removecasos
};
enum chgLoginOptions {
	chgn = 1, chgl, chgs, deladm, chgsair
};
enum playerOptions {
	cadastroJogador = 1, loginjogador, alterarcadastro, jogar
};


void cripto(char* key, char* orig, char* cript);

int main() {
	setlocale(LC_ALL, "Portuguese");
	adminType adm, aux, cmp;
	strcpy(adm.keycripto, "sleepycabin");
	loginType log;
	admOptions casesadm;
	chgLoginOptions caseschglogin;
	playerOptions opcaojogador;
	FILE *admin;
	tipoJogador jogador, auxlogin;
	char cadastro[100];
	char string[30], resposta;
	int i;
	bool valido = true, login = true;

	char ajuda = 'N';

	do {
		system("cls");

		printf("\n\tBem vindo ao jogo Where in the world!");
		printf("\n\tDeseja logar como administrador ou jogador?\n\n\t1. Administrador\n\t2. Jogador\n\t3. Sair\n\n\tOpcao desejada: ");

		scanf("%i", &log);
		if (log != sair)
		{
			switch (log)
			{
			case administrador:
				system("cls");
				printf("\n\tOpção escolhida: 1. Administrador\n\tEscolha uma das opções abaixo:\n\n\t1. Cadastro de Administrador\n\t2. Alterar dados do Administrador\n\t3. Cadastrar casos\n\t4. Remover casos\n\n\tOpcao desejada: ");
				scanf("%i", &casesadm);
				switch (casesadm) {
				case cadastroadm:
					system("cls");
					if (fopen("logincripto.dat", "rb") != NULL)
					{	
						printf("\n\tAdministrador já cadastrado! Desculpe\n\tRetornando ao menu...");
						Sleep(3000);
					}
					else
					{
						printf("\n\tOpção 1. Cadastro de Administrador:\n\n\tNome: ");
						getchar();
						fgets(adm.nome, 30, stdin);
						printf("\n\tLogin: ");
						fgets(adm.login, 30, stdin);
						printf("\n\tSenha: ");
						fgets(adm.senha, 30, stdin);
						strcpy(aux.nome, adm.nome);
						cripto(adm.keycripto, adm.login, aux.login);
						cripto(adm.keycripto, adm.senha, aux.senha);
						admin = fopen("logincripto.dat", "wb");
						if (admin == NULL)
							printf("Erro na abertura do arquivo de login do administrador. Contacte o desenvolvedor!");
						fwrite(&aux, sizeof(adminType), 1, admin);
						fclose(admin);
					}
					system("cls");
					break;
				case chglogin:
					system("cls");
					printf("\n\tOpção 2. Alterar dados do Administrador:\n\n\tDigite o login atual: ");
					getchar();
					fgets(adm.login, 30, stdin);
					printf("\n\tSenha atual: ");
					fgets(adm.senha, 30, stdin);
					cripto(adm.keycripto, adm.login, cmp.login);
					cripto(adm.keycripto, adm.senha, cmp.senha);
					admin = fopen("logincripto.dat", "r+b");
					if (admin == NULL)
						printf("\n\tErro na abertura do arquivo de login do administrador. Contacte o desenvolvedor!");
					fread(&aux, sizeof(adminType), 1, admin);
					fclose(admin);
					system("cls");
					if (strcmp(cmp.login, aux.login) == 0 && strcmp(cmp.senha, aux.senha) == 0)
					{
						do{
							printf("\n\tLogin bem sucedido!\n\tSr(a) %s\tQuais das opções deseja executar?\n\n\t1. Alterar nome\n\t2. Alterar login\n\t3. Alterar senha\n\t4. Excluir credencial de administrador\n\t5. Sair\n\n\tOpcao desejada: ", aux.nome);
							scanf("%i", &caseschglogin);
							system("cls");
							admin = fopen("logincripto.dat", "w+b");
							if (admin == NULL)
								printf("\n\tErro na abertura do arquivo de login do administrador. Contacte o desenvolvedor!");
							fread(&aux, sizeof(adminType), 1, admin);
							switch (caseschglogin)
							{
							case chgn:printf("\n\tOpção 1.2.1. Alterar nome:\n\n\tDigite o novo nome: ");
								getchar();
								fgets(adm.nome, 30, stdin);
								strcpy(aux.nome, adm.nome);
								fwrite(&aux, sizeof(adminType), 1, admin);
								fclose(admin);
								break;
							case chgl:printf("\n\tOpção 1.2.2. Alterar login:\n\n\tDigite o novo login: ");
								getchar();
								fgets(adm.login, 30, stdin);
								cripto(adm.keycripto, adm.login, aux.login);
								fwrite(&aux, sizeof(adminType), 1, admin);
								fclose(admin);
								break;
							case chgs:printf("\n\tOpção 1.2.3. Alterar senha:\n\n\tDigite a nova senha: ");
								getchar();
								fgets(adm.senha, 30, stdin);
								cripto(adm.keycripto, adm.senha, aux.senha);
								fwrite(&aux, sizeof(adminType), 1, admin);
								fclose(admin);
								break;
							case deladm:printf("\n\tOpção 1.2.4. Excluir credencial de administrador:\n\tTem certeza desta opção?(S/N): ");
								getchar();
								scanf("%c", &resposta);
								if (resposta == 'S' || resposta == 's')
								{
									fclose(admin);
									remove("logincripto.dat");
								}
								else
									fclose(admin);
								break;
							case chgsair:
								break;
							}
							system("cls");
						} while (resposta != 's' || resposta != 'S');
						resposta = 'n';
					}
					else
					{
						printf("\n\tLogin ou senha incorretos! Voltando ao menu inicial...");
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
			case jogado:

				system("cls");

				printf("\n\tOpção escolhida: 2. Jogador\n\tEscolha uma das opções abaixo:\n\n\t1. Cadastrar novo jogador\n\t2. Login Jogador\n\t3. Alterar cadastro do Jogador\n\t4. Jogar\n\n\tOpcao desejada: ");
				scanf("%i", &opcaojogador);

				FILE*players = fopen("players.dat", "a+b");
				system("cls");

				switch (opcaojogador)
				{
				case cadastroJogador:

					printf("\n\tOpção 1. Cadastro novo Jogador:\n\n\tDigite seu primeiro nome: ");
					scanf("%s", jogador.nome);

					printf("\n\tDigite seu login: ");
					scanf("%s", jogador.login);

					do  //INICIO VERIFICAÇÃO NOME EXISTENTE
					{
						rewind(players);

						do
						{

							fread(&auxlogin, sizeof(auxlogin), 1, players);

							if (strcmp(auxlogin.nome, jogador.nome) == 0)
							{
								login = false;
								break;
							}
							else
							{
								login = true;
							}

						} while (!feof(players));

						if (login == false)
						{
							system("cls");

							printf("\n\tNome ja cadastrado!\n");
							printf("\n\tTente digitar diferente: ");
							scanf("%s", jogador.nome);
						}

					} while (login == false);  //FIM VERIFICAÇÃO NOME EXISTENTE

					printf("\n\tDigite seu login: ");
					scanf("%s", jogador.login);

					do  //INICIO VERIFICAÇÃO LOGIN EXISTENTE
					{
						rewind(players);

						do 
						{

							fread(&auxlogin, sizeof(auxlogin), 1, players);

							if (strcmp(auxlogin.login, jogador.login) == 0)
							{
								login = false;
								break;
							}
							else
							{
								login = true;
							}

						} while (!feof(players));

						if (login == false)
						{
							system("cls");

							printf("\n\tLogin ja cadastrado!\n");
							printf("\n\tDigite outro login: ");
							scanf("%s", jogador.login);
						}

					} while (login == false);  //FIM VERIFICAÇÃO LOGIN EXISTENTE

					printf("\n\tDigite sua senha: ");
					scanf("%s", jogador.senha);
					jogador.pontos = 0;

					fwrite(&jogador, sizeof(tipoJogador), 1, players);
					Sleep(1000);

					printf("\n\tCadastro realizado com sucesso! Aguarde um momento...");
					Sleep(3000);

					break;

				case loginjogador: //Login jogador

					rewind(players);

					system("cls");

					valido = true;


					do {

						system("cls");

						printf("\n\tOpção 2. Login Jogador:\n\n\tDigite seu login: ");
						scanf("%s", &auxlogin.login);

						do {
							fread(&jogador, sizeof(jogador), 1, players); //Verifica se o login esta cadastrada

							if (strcmp(jogador.login, auxlogin.login) == 0)
							{
								valido = true;
								break;
							}
							else
							{
								valido = false;
							}

						} while (!feof(players));		// /\

						if (valido == false)
						{
							rewind(players);
							system("cls");
							printf("\n\tLogin Invalido...\n\n\tDeseja tentar novamente? (S / N)\n\n\tResposta: ");
							getchar();
							scanf("%c", &resposta);

							ajuda = resposta;
						}
						else
						{
							break;
						}

					} while (valido == false && ajuda == 'S' || ajuda == 's');

					//rewind(players);

					if (valido == true)
					{

						do
						{
							system("cls");

							printf("\n\tOla %s\n", jogador.nome);
							printf("\n\tDigite sua senha: ");
							scanf("%s", &auxlogin.senha);

							if (strcmp(jogador.senha, auxlogin.senha) == 0)
							{
								system("cls");
								printf("\n\tLogin efetuado com sucesso!");
								printf("\n\n\tSeja bem vindo %s, Atualmente voce tem %i pontos", jogador.nome, jogador.pontos);
								printf("\n\n\tVoltando para paginal inicial...");
								Sleep(5000);
								break;
							}
							else
							{
								rewind(players);

								system("cls");
								printf("\n\tSenha Invalida...\n\n\tDeseja tentar novamente? (S / N)\n\n\tResposta: ");
								getchar();
								scanf("%c", &resposta);
							}

						} while (resposta != 'n' || resposta != 'N');
					}
					fclose(players);

					break;
				}

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
