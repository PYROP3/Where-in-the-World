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

enum alterarCadastro {
	alterarNome = 1, alterarLogin, alterarSenha, excluirConta, sairAlterarCadastro
};


void cripto(char* key, char* orig, char* cript);

int main() {
	setlocale(LC_ALL, "Portuguese");

	adminType adm, aux, cmp;
	enum alterarCadastro change;

	strcpy(adm.keycripto, "sleepycabin");
	loginType log;
	admOptions casesadm;
	chgLoginOptions caseschglogin;
	playerOptions opcaojogador;
	FILE *admin;

  FILE *reserva;
	tipoJogador jogador, auxlogin, player;
	char resposta;
	bool valido = true, login = true, jaescreveu, condicao = false,  sairalteracaoadm=false;

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
							case chgsair:sairalteracaoadm = true;
								break;
							}
							system("cls");
						} while (sairalteracaoadm == false);
						sairalteracaoadm = false;
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
				case cadastroJogador: //-------------------------------------------------CADASTRO JOGADOR

					printf("\n\tOpção 1. Cadastro novo Jogador:\n\n\tDigite seu primeiro nome: ");
					scanf("%s", jogador.nome);

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

				case loginjogador: //-------------------------------------------------------LOGIN JOGADOR

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

						} while (!feof(players));

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

				case alterarcadastro: //------------------------------------------------------ALTERAR CADASTRO

					rewind(players);

					system("cls");

					valido = true;

					do {

						system("cls");

						printf("\n\tOpção 3. Alterar cadastro:\n\n\tDigite o login da conta que deseja alterar: ");
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

						} while (!feof(players));

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

					//-----------------------------VALIDACAO LOGIN FIM--------------------------------------------------------

					if (valido == true)
					{
						valido = false;

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
								printf("\n\n\tPor favor aguarde um momento!");
								Sleep(5000);
								valido = true;
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

						//---------------------------------------FIM VERIFICACAO SENHA------------------------------------------------------

						if (valido == true)
						{
							do {

								system("cls");

								printf("\n\n\tSeja bem vindo %s", jogador.nome);
								printf("\n\n\tPor gentileza insira a opcao desejada:");
								printf("\n\n\t1. Alterar nome");
								printf("\n\t2. Alterar login");
								printf("\n\t3. Alterar senha");
								printf("\n\t4. Excluir conta");
								printf("\n\t5. Sair");
								printf("\n\n\tDigite a opcao desejada: ");
								scanf("%i", &change);

								switch (change)
								{
								case alterarNome: //-------------------------------------------------------ALTERAR NOME

									reserva = fopen("reserva.dat", "a+b");

									system("cls");

									printf("\n\tOpcao escolhida 1.Alterar nome");
									printf("\n\n\tDigite o novo nome: ");
									scanf("%s", &player.nome);

									do  //INICIO VERIFICAÇÃO NOME EXISTENTE
									{
										rewind(players);

										do
										{
											fread(&auxlogin, sizeof(auxlogin), 1, players);

											if (strcmp(player.nome, auxlogin.nome) == 0)
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
											printf("\n\tTente digitar um nome diferente: ");
											scanf("%s", player.nome);
										}

									} while (login == false);

									//JOGADOR NOME ANTERIOR
									//PLAYER NOME ATUAL

									rewind(players);
									rewind(reserva);

									jaescreveu = false;

									do
									{

										fread(&auxlogin, sizeof(auxlogin), 1, players);

										if (strcmp(jogador.nome, auxlogin.nome) == 0)
										{
											if (jaescreveu == false)
											{
												strcpy(auxlogin.nome, player.nome);
												fwrite(&auxlogin, sizeof(tipoJogador), 1, reserva);
											}

											jaescreveu = true;
										}
										else if (!feof(players))
										{
											fwrite(&auxlogin, sizeof(tipoJogador), 1, reserva);
										}

									} while (!feof(players));

									fclose(players);
									fclose(reserva);

									players = fopen("players.dat", "wb");
									reserva = fopen("reserva.dat", "rb");

									do
									{
										fread(&jogador, sizeof(jogador), 1, reserva);

										if (!feof(reserva))
											fwrite(&jogador, sizeof(tipoJogador), 1, players);

									} while (!feof(reserva));

									fclose(reserva);
									fclose(players);

									remove("reserva.dat");

									break;

								case alterarLogin: //----------------------------------------------------ALTERAR LOGIN

									//reserva = fopen("reserva.dat", "a+b");

									system("cls");

									printf("\n\tOpcao escolhida 2.Alterar alterar login");
									printf("\n\n\tDigite o novo login: ");
									scanf("%s", &player.login);

									fclose(players);
									players = fopen("players.dat", "a+b");

									do  //INICIO VERIFICAÇÃO NOME EXISTENTE
									{
										rewind(players);

										do
										{
											fread(&auxlogin, sizeof(auxlogin), 1, players);

											if (strcmp(player.login, auxlogin.login) == 0)
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

											printf("\n\n\tLogin ja cadastrado!\n");
											printf("\n\tTente digitar um login diferente: ");
											scanf("%s", player.login);
										}

									} while (login == false);

									//JOGADOR NOME ANTERIOR
									//PLAYER NOME ATUAL

									reserva = fopen("reserva.dat", "wb");

									rewind(players);

									jaescreveu = false;

									do
									{

										fread(&auxlogin, sizeof(auxlogin), 1, players);

										if (strcmp(jogador.login, auxlogin.login) == 0)
										{
											if (jaescreveu == false)
											{
												strcpy(auxlogin.login, player.login);
												fwrite(&auxlogin, sizeof(tipoJogador), 1, reserva);
												jaescreveu = true;
											}

											jaescreveu = true;
										}
										else if (!feof(players))
										{
											fwrite(&auxlogin, sizeof(tipoJogador), 1, reserva);
										}

									} while (!feof(players) && !feof(reserva));

									fclose(players);
									fclose(reserva);

									players = fopen("players.dat", "wb");
									reserva = fopen("reserva.dat", "rb");

									do
									{
										fread(&jogador, sizeof(jogador), 1, reserva);

										if (!feof(reserva))
											fwrite(&jogador, sizeof(tipoJogador), 1, players);

									} while (!feof(reserva));

									fclose(reserva);
									fclose(players);

									remove("reserva.dat");

									break;
								
								case alterarSenha://------------------------------------------------------ALTERAR SENHA

									system("cls");

									printf("\n\tOpcao escolhida 3.Alterar senha");
									printf("\n\n\tDigite a nova senha: ");
									scanf("%s", &player.senha);

									//JOGADOR NOME ANTERIOR
									//PLAYER NOME ATUAL

									fclose(players);

									reserva = fopen("reserva.dat", "wb");
									players = fopen("players.dat", "rb");

									jaescreveu = false;

									do
									{
										fread(&auxlogin, sizeof(auxlogin), 1, players);

										if (strcmp(jogador.senha, auxlogin.senha) == 0)
										{
											if (jaescreveu == false)
											{
												strcpy(auxlogin.senha, player.senha);
												fwrite(&auxlogin, sizeof(tipoJogador), 1, reserva);
											}

											jaescreveu = true;
										}
										else if (!feof(players))
										{
											fwrite(&auxlogin, sizeof(tipoJogador), 1, reserva);
										}

									} while (!feof(players));

									fclose(players);
									fclose(reserva);

									players = fopen("players.dat", "wb");
									reserva = fopen("reserva.dat", "rb");

									do
									{
										fread(&jogador, sizeof(jogador), 1, reserva);

										if (!feof(reserva))
											fwrite(&jogador, sizeof(tipoJogador), 1, players);

									} while (!feof(reserva));

									fclose(reserva);
									fclose(players);

									remove("reserva.dat");

									break;

								case excluirConta://----------------------------------------------------EXLUIR CONTA

									system("cls");

									printf("\n\tTem certeza que deseja excluir a conta?");
									printf("\n\n\t1. Sim");
									printf("\n\t2. Nao\n\n\tOpcao: ");
									scanf("%i", &change);

									if (change == 2)
										break;
									else
									{

										do {
											system("cls");

											printf("\n\tPara exluirmos a conta %s por favor reinsira sua senha", jogador.nome);
											printf("\n\n\tSenha: ");
											scanf("%s", auxlogin.senha);

											//jogador  - antigo
											//auxlogin - novo

											if (strcmp(auxlogin.senha, jogador.senha) == 0)
											{
												fclose(players);

												reserva = fopen("reserva.dat", "wb");
												players = fopen("players.dat", "rb");

												do
												{
													fread(&player, sizeof(player), 1, players);

													if (!feof(players) && strcmp(player.nome, jogador.nome) != 0)
													{
														fwrite(&player, sizeof(tipoJogador), 1, reserva);
													}

												} while (!feof(players) && !feof(reserva));

												fclose(reserva);
												fclose(players);

												reserva = fopen("reserva.dat", "rb");
												players = fopen("players.dat", "wb");


												do
												{
													fread(&player, sizeof(player), 1, reserva);

													if (!feof(players) && !feof(reserva))
														fwrite(&player, sizeof(tipoJogador), 1, players);

												} while (!feof(players) && !feof(reserva));

												fclose(reserva);
												fclose(players);

												remove("reserva.dat");

												break;
											}

											else
											{
												system("cls");

												printf("\n\tSenha invalida, deseja digitar novamente?");
												printf("\n\n\t1. Sim");
												printf("\n\t2. Nao\n\n\tOpcao: ");
												scanf("%i", &change);

												if (change == 2)
												{
													break;
												}
											}
										} while (true);
									}



									break;

								case sairAlterarCadastro:
									condicao = true;
										break;
									break;

								default:
									break;
								}

							} while (condicao == false);
						}
					}
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
