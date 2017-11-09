#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <Windows.h>

struct tipoPersonagem {
	float altura;
	int idade;
	char nome[50];
	char corCabelo[20];
	char hobby[50];
};

struct tipoCaso {
	char historiaGeral[999];
	char historiaCidade[30][999];
	char cidades[30][50];
	char personagens[30][50];
	char dicas[100][999];
};

struct adminType {
	char nome[30];
	char login[30];
	char senha[30];
	char keycripto[13];
};

struct tipoJogador {
	char nome[30];
	char login[30];
	char senha[30];
	int pontos;
};

enum loginType {
	administrador = 1, jogado, sair
};
enum admOptions {
	cadastroadm = 1, loginadm, returnmenu
};
enum admLoginOptions {
	chgn = 1, chgl, chgs, cadastrocasos, cadastropersonagem, removecasos, deladm, chgsair
};
enum playerOptions {
	cadastroJogador = 1, loginjogador, saair
};

enum alterarCadastro {
	alterarNome = 1, alterarLogin, alterarSenha, excluirConta, sairAlterarCadastro
};

enum playerLogadoOptions {
	alterarCadastro = 1, jogar = 2, logOut
};

enum personas {
	cadastrarPersonagem = 1, usarCadastrado
};

void cripto(char* key, char* orig, char* cript);
void newPersona();
void oldPersona(tipoPersonagem* personagem);

int main()
{
	setlocale(LC_ALL, "Portuguese");
	char cleberson[50];
	tipoCaso caso;
	adminType adm, aux, cmp;
	enum personas matsf;
	enum alterarCadastro change;
	enum playerLogadoOptions jorge;
	strcpy(adm.keycripto, "sleepycabin");
	loginType log;
	admOptions casesadm;
	admLoginOptions casesloginadm;
	playerOptions opcaojogador;
	tipoPersonagem personagem[100], ajudadora;
	FILE *admin;
	FILE *reserva;
	FILE *casos;
	FILE *personagens;
	tipoJogador jogador, auxlogin, player;
	char resposta;
	int quantidade = 0, i;
	bool valido = true, login = true, jaescreveu, condicao = false, sairalteracaoadm = false, logou = false, logFora, returntomenu = false;
	char ajuda = 'N';

	do {
		system("cls");
		system("color F2");
		printf("\n\tBem vindo ao jogo Where in the world!");
		printf("\n\tDeseja logar como administrador ou jogador?\n\n\t1. Administrador\n\t2. Jogador\n\t3. Sair\n\n\tOpcao desejada: ");

		scanf("%i", &log);
		if (log != sair)
		{
			switch (log)
			{
			case administrador:
				do {
					system("cls");
					system("color 04");
					printf("\n\tOpção escolhida: 1. Administrador\n\tEscolha uma das opções abaixo:\n\n\t1. Cadastro de Administrador\n\t2. Login do Administrador\n\t3. Retornar ao menu anterior\n\n\tOpcao desejada: ");
					scanf("%i", &casesadm);
					if (casesadm > 0 && casesadm < 4)
					{
						switch (casesadm)
						{
						case cadastroadm:
							system("cls");
							admin = fopen("logincripto.dat", "rb");

							if (admin != NULL)
							{
								fclose(admin);
								printf("\n\tAdministrador já cadastrado! Desculpe\n\tRetornando ao menu...");
								Sleep(3000);
							}
							else
							{
								//fclose(admin);

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
								else
									fwrite(&aux, sizeof(adminType), 1, admin);

								fclose(admin);
							}

							system("cls");

							break;

						case loginadm:
							system("cls");
							admin = fopen("logincripto.dat", "rb");
							if (admin == NULL)
							{
								printf("\n\t É necessário o cadastro de administrador primeiro!");
								Sleep(3000);
							}
							else
							{
								fclose(admin);
								printf("\n\tOpção 2. Login Administrativo:\n\n\tDigite o login atual: ");
								getchar();
								fgets(adm.login, 30, stdin);
								printf("\n\tSenha atual: ");
								fgets(adm.senha, 30, stdin);
								cripto(adm.keycripto, adm.login, cmp.login);
								cripto(adm.keycripto, adm.senha, cmp.senha);
								admin = fopen("logincripto.dat", "r+b");

								if (admin == NULL)
									printf("\n\tErro na abertura do arquivo de login do administrador. Contacte o desenvolvedor!");
								else
									fread(&aux, sizeof(adminType), 1, admin);

								fclose(admin);
								system("cls");

								if (strcmp(cmp.login, aux.login) == 0 && strcmp(cmp.senha, aux.senha) == 0)
								{
									do {
										printf("\n\tLogin bem sucedido!\n\tSr(a) %s\tQuais das opções deseja executar?\n\n\t1. Alterar nome\n\t2. Alterar login\n\t3. Alterar senha", aux.nome);
										printf("\n\t4. Cadastrar caso\n\t5. Cadastrar personagem \n\t6. Remover caso\n\t7. Excluir credencial de administrador\n\t8. Sair\n\n\tOpcao desejada: ");
										scanf("%i", &casesloginadm);
										system("cls");
										admin = fopen("logincripto.dat", "w+b");

										if (admin == NULL)
											printf("\n\tErro na abertura do arquivo de login do administrador. Contacte o desenvolvedor!");
										else
											fread(&aux, sizeof(adminType), 1, admin);

										switch (casesloginadm)
										{
										case chgn:

											printf("\n\tOpção 1.2.1. Alterar nome:\n\n\tDigite o novo nome: ");
											getchar();
											fgets(adm.nome, 30, stdin);
											strcpy(aux.nome, adm.nome);
											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);
											break;

										case chgl:

											printf("\n\tOpção 1.2.2. Alterar login:\n\n\tDigite o novo login: ");
											getchar();
											fgets(adm.login, 30, stdin);
											cripto(adm.keycripto, adm.login, aux.login);
											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);
											break;

										case chgs:

											printf("\n\tOpção 1.2.3. Alterar senha:\n\n\tDigite a nova senha: ");
											getchar();
											fgets(adm.senha, 30, stdin);
											cripto(adm.keycripto, adm.senha, aux.senha);
											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);
											break;

										case cadastrocasos: //-------------------------------------------------------------------CADASTRO CASOS

											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);

											casos = fopen("casos.dat", "a + b");

											//HISTORIA

											system("cls");
											printf("\n\tOpção 1.2.4. Cadastrar casos:");
											printf("\n\n\tPrimeiro digite a história do caso: (MAX 999 caracteres): ");
											getchar();
											fgets(caso.historiaGeral, 999, stdin);
											printf("\n\tHistória cadastrada com sucesso! Agurdade um momento....");
											Sleep(2000);

											quantidade = 1;

											do //CIDADES
											{
												system("cls");
												printf("\n\tAgora digite as cidades que farão parte: (MAX 30 cidades e 50 caracteres)");
												printf("\n\tPara encerrar o cadastro digite 'Sair' (Sem as aspas)");
												printf("\n\n\tDigite o nome da %i cidade: ", quantidade);
												fflush(stdin);
												fgets(cleberson, 50, stdin); //30 cidades 50 caracteres

												if (strcmp(cleberson, "Sair") == 0 || strcmp(cleberson, "sair") == 0 || strcmp(cleberson, "sair\n") == 0 || strcmp(cleberson, "Sair\n") == 0 && quantidade < 31)
												{
													if (quantidade == 31)
													{
														system("cls");
														printf("\n\tLimite máximo de cidades atingido! Aguarde enquanto vamos ao proximo passo...");
													}
													else
													{
														printf("\n\tAguarde enquanto lhe redirecionamos ao proximo passo...");
													}

													Sleep(3000);

													fclose(casos);

													break;
												}

												else
												{
													for (i = 0; i < strlen(cleberson); i++)
													{
														if (cleberson[i] == '\n')
															cleberson[i] = '\0';
													}

													strcpy(caso.cidades[quantidade - 1], cleberson);
												}

												quantidade++;

											} while (true);

											for (i = 0; i < quantidade - 1; i++)
											{
												system("cls");
												printf("\n\tCadastre agora a descrição / historia de cada cidade: (MAX 999 Caracteres)");
												printf("\n\n\tHistoria da cidade %s: ", caso.cidades[i]);
												fflush(stdin);
												fgets(caso.historiaCidade[i], 999, stdin);
											}

											system("cls");

											printf("\n\tCidades concluidas com sucesso!");
											printf("\n\n\tDigite a opção desejada: \n");
											printf("\n\t1.Cadatrar novos personagens");
											printf("\n\t2.Usar personagens ja cadastrados");
											printf("\n\n\tOpcao: ");
											scanf("%i", &matsf);

											system("cls");

											switch (matsf)
											{
											case cadastrarPersonagem:

												newPersona(); //=================AQUIIII BURROOOOO
												oldPersona(personagem);

												break;
											case usarCadastrado:
												
												oldPersona(personagem);

												break;
											default:
												break;
											}

											Sleep(1000);

											fclose(casos);

											break;

										case cadastropersonagem:

											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);

											newPersona(); //=================AQUIIII BURROOOOO

											break;

										case removecasos:

											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);

											fclose(admin);
											system("cls");
											printf("\tOpção 1.2.5. Remover casos:\n\n");
											system("cls");
											break;

										case deladm:

											printf("\n\tOpção 1.2.6. Excluir credencial de administrador:\n\tTem certeza desta opção?(S/N): ");
											getchar();
											scanf("%c", &resposta);

											if (resposta == 'S' || resposta == 's')
											{
												fclose(admin);
												printf("\n\tVocê será redirecionado para o menu administrativo em instantes...");
												Sleep(2000);
												sairalteracaoadm = true;
												remove("logincripto.dat");
											}
											else
												fclose(admin);
											break;

										case chgsair:
											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);
											sairalteracaoadm = true;
											break;
										}

										system("cls");

									} while (sairalteracaoadm == false);

									sairalteracaoadm = false;
								}
								else
								{
									printf("\n\tLogin ou senha incorretos! Voltando ao menu inicial...");
									Sleep(2000);
								}
							}

							system("cls");
							break;

						case returnmenu:returntomenu = true;
							break;
						}
					}
					else
					{
						printf("\n\n\tOpção inválida! Tente novamente em instantes...");
						Sleep(3000);
					}
				} while (returntomenu == false);
				returntomenu = false;
				break;

			case jogado:
				system("cls");

				printf("\n\tOpção escolhida: 2. Jogador\n\tEscolha uma das opções abaixo:\n\n\t1. Cadastrar novo jogador\n\t2. Login Jogador\n\t3. Retornar ao menu anterior\n\n\tOpcao desejada: ");
				scanf("%i", &opcaojogador);

				FILE*players = fopen("players.dat", "a+b");
				system("cls");

				switch (opcaojogador)
				{
				case cadastroJogador: //-------------------------------------------------CADASTRO JOGADOR INICIO

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

					fclose(players);

					printf("\n\tCadastro realizado com sucesso! Aguarde um momento...");
					logou = true;
					Sleep(2000);

					break; //-------------------------------------------------------------------FIM LOGIN CADASTRO JOGADOR

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
								printf("\n\n\tCarregando pagina jogador...");
								Sleep(5000);
								logou = true;
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

				case saair:
					break;
				}

				if (logou == true)
				{
					logFora = false;

					players = fopen("players.dat", "a+b");
					do {
						system("cls");
						printf("\n\tBem vindo %s!", jogador.nome);
						printf("\n\n\tEscolha uma das opções abaixo:");
						printf("\n\n\t1.Alterar Cadastro");
						printf("\n\t2.Jogar");
						printf("\n\t3.Log out");
						printf("\n\n\tOpção desejada: ");
						scanf("%i", &jorge);

						switch (jorge)
						{
						case alterarCadastro:
							rewind(players);

							system("cls");

							valido = true;

							if (valido == true)
							{
								do {

									system("cls");

									printf("\n\tSeja bem vindo %s", jogador.nome);
									printf("\n\n\tPor gentileza insira a opcao desejada:");
									printf("\n\n\t1. Alterar nome");
									printf("\n\t2. Alterar login");
									printf("\n\t3. Alterar senha");
									printf("\n\t4. Excluir conta");
									printf("\n\t5. Voltar");
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

										//remove("reserva.dat");

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
													condicao = true;
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

							break;
						case jogar:
							break;
						case logOut:
							logFora = true;
							break;
						default:
							break;
						}
					} while (logFora == false);
				}
				break;
			}
		}

	} while (log != sair);

	return 0;
}

void oldPersona(tipoPersonagem* personagens)
{
	FILE* fd = fopen("personagem.dat", "a + b");
	int i = 0, qtdPersonas = 0, minAjuda = 0;
	char personaEscolhida[200];
	tipoPersonagem aux[300], intermediaria;

	system("cls");

	printf("\n\tEscolha o personagem que deseja colocar em seu caso\n\n");
	
	rewind(fd);

	do
	{
		fread(&intermediaria, sizeof(tipoPersonagem), 1, fd);
		printf("\t%i. %s, %i anos, %.2fm de altura, cabelo %s, gosta de %s\n", i + 1, intermediaria.nome, intermediaria.idade, intermediaria.altura, intermediaria.corCabelo, intermediaria.hobby);
		qtdPersonas++;
		
		{
			strcpy(aux[i].corCabelo, intermediaria.corCabelo);
			strcpy(aux[i].hobby, intermediaria.hobby);
			strcpy(aux[i].nome, intermediaria.nome);
			aux[i].altura = intermediaria.altura;
			aux[i].idade = intermediaria.idade;
		}
		
		i++;
	} while (!feof(fd));
		
	printf("\t\nOpcoes (digite os numeros separados por virgula, MAX 100 personagens): ");
	scanf("%s", personaEscolhida);
	
	for (i = 0; i < strlen(personaEscolhida); i++)
	{
		if (personaEscolhida[i] != ',')
		{
			minAjuda = personaEscolhida[i] - 49;

			strcpy(personagens[i].corCabelo, aux[minAjuda].corCabelo);
			strcpy(personagens[i].hobby, aux[minAjuda].hobby);
			strcpy(personagens[i].nome, aux[minAjuda].nome);
			personagens[i].altura = aux[minAjuda].altura;
			personagens[i].idade = aux[minAjuda].idade;
		}
	}

	fclose(fd);

}

void newPersona()
{
	FILE* fd = fopen("personagem.dat", "a + b");
	bool flag = false;
	char resposta;
	int i;
	tipoPersonagem aux, ajudadora;

	do {
		system("cls");
		printf("\n\tCadastro de personagens\n");
		printf("\n\tDigite o nome do seu novo personagem (sem espaço): ");
		fflush(stdin);
		scanf("%s", aux.nome);

		rewind(fd);

		do
		{
			fread(&ajudadora, sizeof(ajudadora), 1, fd);

			if (strcmp(ajudadora.nome, aux.nome) == 0 && fd != NULL)
			{
				do
				{
					system("cls");
					printf("\n\tNome ja cadastrado!");
					printf("\n\n\tTente um nome diferente: ");
					scanf("%s", aux.nome);

				} while (strcmp(ajudadora.nome, aux.nome) == 0);
			}

		} while (!feof(fd));


		printf("\tDigite a idade do %s: ", aux.nome);
		scanf("%i", &aux.idade);
		
		fflush(stdin);
		printf("\tDigite a altura do(a) %s (use virgula): ", aux.nome);
		scanf("%f", &aux.altura);
		
		getchar();
		printf("\tDigite a cor do cabelo do(a) %s: ", aux.nome);
		fflush(stdin);
		fgets(aux.corCabelo, 20, stdin);
		
		
		printf("\tDigite um hobby do(a) %s: ", aux.nome);
		fflush(stdin);
		fgets(aux.hobby, 50, stdin);

		printf("\n\tDeseja cadastrar mais personagens (S/N): ");
		scanf("%c", &resposta);

		for (i = 0; i < strlen(aux.corCabelo) || i < strlen(aux.hobby); i++)
		{
			if (aux.corCabelo[i] == '\n')
				aux.corCabelo[i] = '\0';

			if (aux.hobby[i] == '\n')
				aux.hobby[i] = '\0';
		}



		fwrite(&aux, sizeof(tipoPersonagem), 1, fd);

		if (resposta == 'n' || resposta == 'N')
		{
			flag = true;
			fclose(fd);
		}

	} while (flag == false);


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
