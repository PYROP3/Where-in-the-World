#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <Windows.h>

struct checkPerson {
	char nome[50];
	char sexo[3][10] = { "Masculino", "Feminino", " - " };
	char corCabelo[7][10] = { "Preto", "Castanho", "Loiro", "Vermelho", "Azul", "Branco", " - " };
	char hobby[6][25] = { "Caminhar", "Jogar", "Tocar instrumento(s)", "Ler", "Discutir", " - " };
	char feature[8][10] = { "Chapéu", "Boné", "Tatuagem", "Óculos", "Pulseira", "Anel", "Colar" , " - " };
};

struct tipoPersonagem {
	char nome[50];
	int sexo;
	int corCabelo;
	int hobby;
	int feature;
};

struct tipoCaso {
	tipoPersonagem personagens[30];
	char historiaGeral[999];
	char historiaCidade[30][999];
	char cidades[30][50];
	char pessoaDica[90][50];
	char pistas[90][999];
	char POI[90][20];
	char nomeCaso[40];
	int numeroCidades;
	int quantSusp;
	int culpado[3];//Aqui guardaremos tres variáveis, 1.Quem é, 2.Em que lugar, 3.Em qual POI
	int tempoEntreLocais;
	int tempoParaPOI;
	int tempoDeSolucao;
	int dificuldade;
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
	char casoAtual[40];
	char cidadeAtual[50];
	int tempoAtual;
	tipoPersonagem retratoFalado;
	bool mandato = false;
	bool pessoacerta = false;
	bool saved = false;
};

enum loginType {
	administrador = 1, jogado, README, credit, sair
};
enum admOptions {
	cadastroadm = 1, loginadm, returnmenu
};
enum admLoginOptions {
	chgn = 1, chgl, chgs, cadastrocasos, cadastropersonagem, deladm, chgsair
};
enum playerOptions {
	cadastroJogador = 1, loginjogador, rank, saair
};

enum alterarCadastro {
	alterarNome = 1, alterarLogin, alterarSenha, excluirConta, sairAlterarCadastro
};

enum playerLogadoOptions {
	alterarCadastro = 1, carregarjogo, jogar, logOut
};

enum personas {
	cadastrarPersonagem = 1, usarCadastrado
};

enum QualCaracteristica {
	sexo, corDeCabelo, Hobby, Feature
};

enum Nivel {
	Novato, Experiente, Veterano
};

void cripto(char* key, char* orig, char* cript);
void newPersona();
int oldPersona(tipoPersonagem* personagem);
int checkCarac(QualCaracteristica caracteristica, bool playing);
void rightTime(int tempo);
void writeout(char*, bool, bool, bool);
int returncustomtimer(char);
int checkforcommand(char*, int);
Nivel returnLevel(int lv);
int geraCaso(Nivel x, FILE* arq);
void printMenu(int, bool, bool);
void animaIntro();
void ranking();

void SetWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
}

int main()
{
	setlocale(LC_ALL, "Portuguese");
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
	tipoPersonagem personagem[100];
	FILE *admin;
	FILE *reserva;
	FILE *casos;
	FILE*players;
	tipoJogador jogador, auxlogin, player;
	char resposta;
	int quantidade = 0, i, qtdPersonas, contaCidade, auxiliar;
	bool valido = true, login = true, jaescreveu, condicao = false;
	bool sairalteracaoadm = false, logou = false, logFora, returntomenu = false;
	char ajuda = 'N';

	//VARS DO JOGO
	tipoCaso casoatual;
	FILE *casoatualDesc;
	int casoparaloadar = 1;
	bool gameover = false;
	bool ReadingAgain = false;
	int temporestante;
	int cidadeatual = 0;
	int opcaoemopcao;
	int opcaoemjogo;
	int contaCaracts;
	int MAXCaracts;
	int contaSuspeitos;
	int naoContaEstaCidade;
	int contaCidadesImpressas;
	bool ingame = false;
	char suspeitos[30][50];
	bool stayinoption = true;
	bool casoSalvoEncontrado = true;
	char texto[999];

	SetWindow(90, 40);

	system("color F0");
	animaIntro();
	do {
		system("cls");
		system("color F0");
		printf("\n\tBem vindo ao jogo \"Onde no Universo do Cinema/Série está Carmen Sandiego?\"!");
		printf("\n\tEscolha uma das opções abaixo:\n\t(Caso você seja iniciante, é altamente recomendado a leitura do tutorial!)\n\n\t");
		printMenu(75, false, false);
		printf("\t1. Administrador\n\t2. Jogador\n\t3. Tutorial\n\t4. Créditos\n\t5. Sair\n\n\tOpção: \n\t");
		printMenu(75, true, false);		
		scanf("%i", &log);

		if (log != sair)
		{
			switch (log)
			{
			case administrador:
				do {
					system("cls");
					/*system("color 04");*///Sentirei saudades!! 
					printf("\n\tOpção escolhida: 1. Administrador\n\tEscolha uma das opções abaixo:\n\n\t1. Cadastro de Administrador\n\t2. Login do Administrador\n\t3. Retornar ao menu anterior\n\n\tOpcao desejada: ");
					scanf("%i", &casesadm); //Escolher opção de adm
					if (casesadm > 0 && casesadm < 4)
					{
						switch (casesadm)
						{
						case cadastroadm://Cadastro de adm
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
								//	fclose(admin);

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

						case loginadm://Login de adm
							system("cls");
							admin = fopen("logincripto.dat", "rb");
							if (admin == NULL)
							{
								printf("\n\t É necessário o cadastro de administrador primeiro!");
								Sleep(1000);
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

								if (strcmp(cmp.login, aux.login) == 0 && strcmp(cmp.senha, aux.senha) == 0) //Checa se o login é valido e bate com o salvo no arquivo de players
								{
									do {
										printf("\n\tLogin bem sucedido!\n\tSr(a) %s\tQuais das opções deseja executar?\n\n\t1. Alterar nome\n\t2. Alterar login\n\t3. Alterar senha", aux.nome);
										printf("\n\t4. Cadastrar caso\n\t5. Cadastrar personagem\n\t6. Excluir credencial de administrador\n\t7. Sair\n\n\tOpcao desejada: ");
										scanf("%i", &casesloginadm);
										system("cls");
										admin = fopen("logincripto.dat", "w+b");

										if (admin == NULL)
											printf("\n\tErro na abertura do arquivo de login do administrador. Contacte o desenvolvedor!");
										else
											fread(&aux, sizeof(adminType), 1, admin);

										switch (casesloginadm) //Opções de adm
										{
										case chgn://Troca de nome

											printf("\n\tOpção 1.2.1. Alterar nome:\n\n\tDigite o novo nome: ");
											getchar();
											fgets(adm.nome, 30, stdin);
											strcpy(aux.nome, adm.nome);
											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);
											break;

										case chgl://Troca de login

											printf("\n\tOpção 1.2.2. Alterar login:\n\n\tDigite o novo login: ");
											getchar();
											fgets(adm.login, 30, stdin);
											cripto(adm.keycripto, adm.login, aux.login);
											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);
											break;

										case chgs://Troca de senha

											printf("\n\tOpção 1.2.3. Alterar senha:\n\n\tDigite a nova senha: ");
											getchar();
											fgets(adm.senha, 30, stdin);
											cripto(adm.keycripto, adm.senha, aux.senha);
											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);
											break;

										case cadastrocasos: //CADASTRO CASOS

											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);

											casos = fopen("casos.dat", "a + b");

											//Cadastro do caso começa aqui 

											system("cls");
											printf("\n\tOpção 1.2.4. Cadastrar casos:");
											printf("\n\n\tPrimeiro digite o nome do caso (MAX 40 caracteres): ");
											getchar();
											fgets(caso.nomeCaso, 40, stdin);
											for (int t = 0; t < strlen(caso.nomeCaso); t++)
											{
												if (caso.nomeCaso[t] == '\n' && !((caso.nomeCaso[t + 1] <= 'Z' &&  caso.nomeCaso[t + 1] >= 'A') || (caso.nomeCaso[t + 1] <= 'z' &&  caso.nomeCaso[t + 1] >= 'a')))
													caso.nomeCaso[t] = '\0';
											}

											printf("\n\tNome do caso cadastrado com sucesso! Aguarde um momento....");
											Sleep(1000);
											system("cls");

											printf("\n\n\tDigite a história do caso \"%s\" (MAX 999 caracteres): ", caso.nomeCaso);
											fgets(caso.historiaGeral, 999, stdin);

											printf("\n\tHistória cadastrada com sucesso! Aguarde um momento....");
											Sleep(2000);

											quantidade = 1;
											contaCidade = 0;
											do //Locais, POIs , dicas e quem dá as dicas
											{
												system("cls");

												printf("\n\tAgora digite as localidades que farão parte do caso: ");
												printf("\n\tLembre-se que o primeiro local será o local inicial, ou seja, ");
												printf("\n\to local que o jogador começará.");
												printf("\n\tPara encerrar o cadastro digite 'Sair'. (MAX 30 cidades e 50 caracteres)");
												printf("\n\n\tDigite o nome do local %i: ", quantidade);
												fgets(caso.cidades[contaCidade], 50, stdin); //30 cidades 50 caracteres

												if (strcmp(caso.cidades[contaCidade], "Sair") == 0 || strcmp(caso.cidades[contaCidade], "sair") == 0 || strcmp(caso.cidades[contaCidade], "sair\n") == 0 || strcmp(caso.cidades[contaCidade], "Sair\n") == 0 && quantidade < 32)
												{
													if (!contaCidade) {
														printf("\n\tDigite pelo menos um local!\n");
														Sleep(2000);
													}
													else
													{
														if (quantidade == 31)
														{
															system("cls");
															printf("\n\tLimite máximo de locais atingido! Aguarde enquanto vamos ao próximo passo...");
														}
														else
														{
															printf("\n\tAguarde enquanto lhe redirecionamos ao próximo passo...");
														}
														caso.numeroCidades = quantidade - 1;
														Sleep(2000);
														break;
													}																								
												}
												else
												{
													for (i = 0; i < strlen(caso.cidades[contaCidade]); i++)
													{
														if (caso.cidades[contaCidade][i] == '\n' && !((caso.cidades[contaCidade][i+1] <= 'Z' &&  caso.cidades[contaCidade][i + 1] >= 'A') || (caso.cidades[contaCidade][i + 1] <= 'z' &&  caso.cidades[contaCidade][i + 1] >= 'a')))
															caso.cidades[contaCidade][i] = '\0';
													}
													for (int j = 0; j < 3; j++)
													{
														system("cls");
														printf("\n\n\tPonto de interesse %i do local \"%s\" (MAX 20 carac.):\n\t", j + 1, caso.cidades[contaCidade]);
														fgets(caso.POI[(3 * contaCidade) + j], 20, stdin);
														for (int t = 0; t < strlen(caso.POI[(3 * contaCidade) + j]); t++)
														{
															if (caso.POI[(3 * contaCidade) + j][t] == '\n' && !((caso.POI[(3 * contaCidade) + j][t + 1] <= 'Z' &&  caso.POI[(3 * contaCidade) + j][t + 1] >= 'A') || (caso.POI[(3 * contaCidade) + j][t + 1] <= 'z' &&  caso.POI[(3 * contaCidade) + j][t + 1] >= 'a')))
																caso.POI[(3 * contaCidade) + j][t] = '\0';
														}
														
														printf("\n\n\tPista %i do local \"%s\" (MAX 999 carac.): ", j + 1, caso.cidades[contaCidade]);
														fgets(caso.pistas[(3 * contaCidade) + j], 999, stdin);

														printf("\n\n\tNome de quem dará a pista %i (MAX 50 carac.): ", j + 1);
														fgets(caso.pessoaDica[(3 * contaCidade) + j], 50, stdin);
														for (int t = 0; t < strlen(caso.pessoaDica[(3 * contaCidade) + j]); t++)
														{
															if (caso.pessoaDica[(3 * contaCidade) + j][t] == '\n' && !((caso.pessoaDica[(3 * contaCidade) + j][t + 1] <= 'Z' &&  caso.pessoaDica[(3 * contaCidade) + j][t + 1] >= 'A') || (caso.pessoaDica[(3 * contaCidade) + j][t + 1] <= 'z' &&  caso.pessoaDica[(3 * contaCidade) + j][t + 1] >= 'a')))
																caso.pessoaDica[(3 * contaCidade) + j][t] = '\0';
														}
														system("cls");
													}
													contaCidade++;
												}
												if(contaCidade > 0)
													quantidade++;
											} while (true);
											system("cls");
											do {//"coordenadas" da cidade e do POI que o culpado está
												for (int t = 0; t < caso.numeroCidades; t++)
												{
													printf("\n\t%i . %s", t+1, caso.cidades[t]);
													for (int m = 0; m < 3; m++)
													{
														printf("\n\t\t%i . %s", m + 1, caso.POI[(t*3)+m]);
													}
													printf("\n");
												}
												printf("\n\tInforme agora os números(separados por ponto) X.Y:");
												printf("\n\tX - O número da cidade onde o culpado estará;");
												printf("\n\tY - O número do ponto de interesse em que o culpado estará");
												printf("\n\tExemplos de entrada: 1.3 , 12.2 , 2.1\n\tOpção: ");
												scanf("%s", texto);											
												caso.culpado[1] = texto[0] - 49;
												if (texto[1] != '.')
												{
													caso.culpado[1] = (caso.culpado[1] * 10) + (texto[1] - 49);
													caso.culpado[2] = texto[3] - 49;
												}
												else
												{
													caso.culpado[2] = texto[2] - 49;
												}	
												system("cls");
												printf("\n\tDigite um valor válido!");
											} while ((caso.culpado[1] > caso.numeroCidades || caso.culpado[1] < 0) && !(caso.culpado[2] < 3 && caso.culpado[2] > -1));
											getchar();
											//Cadastro da descrição
											for (i = 0; i < quantidade - 1; i++)
											{
												system("cls");
												printf("\n\tCadastre agora a descrição / história de cada local (MAX 999 Caracteres):");
												printf("\n\n\tHistória do local %s: ", caso.cidades[i]);
												fgets(caso.historiaCidade[i], 999, stdin);
											}

											system("cls");

											printf("\n\tLocais concluídos com sucesso!");
											printf("\n\n\tDigite a opção desejada: \n");
											printf("\n\t1.Cadastrar novos personagens");
											printf("\n\t2.Usar personagens já cadastrados");
											printf("\n\n\tOpção: ");
											scanf("%i", &matsf);

											switch (matsf) //Escolhe se quer cadastrar nova pessoa ou se quer alguém cadastrado
											{
											case cadastrarPersonagem:

												newPersona();
												qtdPersonas = oldPersona(personagem);

												break;
											case usarCadastrado:

												qtdPersonas = oldPersona(personagem);

												break;
											default:
												break;
											}
											do {//Escolha do culpado
												printf("\n\tQuem será o culpado neste caso? (Conforme a tabela acima)\n\tOpção: ");
												scanf("%i", &caso.culpado[0]);
											} while (!(caso.culpado[0] > 0 && caso.culpado[0] < (qtdPersonas+1)));
											caso.culpado[0]--;
											system("cls");

											do {//Dificuldade do caso
												printf("\n\tQual a dificuldade do caso?");
												printf("\n\t1. Fácil (Para jogadores Novatos);");
												printf("\n\t2. Médio (Para jogadores Experientes)");
												printf("\n\t3. Difícil (Para jogadores Veteranos)");
												printf("\n\tOpção: ");
												scanf("%i", &caso.dificuldade);
												system("cls");
												printf("\n\tDigite um valor válido!");
											} while (!(caso.dificuldade > 0 && caso.dificuldade < 4));

											system("cls");//Tempos
											printf("\n\tQuanto tempo o jogador terá para solucionar este caso? (Em segundos)\n\tOpção: ");
											scanf("%i", &caso.tempoDeSolucao);
											printf("\n\tQuanto tempo o jogador terá para viajar entre os locais? (Em segundos)\n\tOpção: ");
											scanf("%i", &caso.tempoEntreLocais);
											printf("\n\tQuanto tempo o jogador terá para visitar um ponto de interesse? (Em segundos)\n\tOpção: ");
											scanf("%i", &caso.tempoParaPOI);
											system("cls");

											caso.quantSusp = qtdPersonas;
											for (i = 0; i < qtdPersonas; i++)//Recebe os valores de personagens 
											{
												strcpy(caso.personagens[i].nome, personagem[i].nome);
												caso.personagens[i].sexo = personagem[i].sexo;
												caso.personagens[i].corCabelo = personagem[i].corCabelo;
												caso.personagens[i].hobby = personagem[i].hobby;
												caso.personagens[i].feature = personagem[i].feature;
											}

											Sleep(1000);

											fwrite(&caso, sizeof(tipoCaso), 1, casos);
											fclose(casos);
											
											break;

										case cadastropersonagem://Opção para só cadastro de personagens

											fwrite(&aux, sizeof(adminType), 1, admin);
											fclose(admin);

											newPersona(); 

											break;
																		

										case deladm://deleta o adm atual

											printf("\n\tOpção 1.2.6. Excluir credencial de administrador:\n\tTem certeza desta opção?(S/N): ");
											getchar();
											scanf("%c", &resposta);

											if (resposta == 'S' || resposta == 's')
											{
												fclose(admin);
												printf("\n\tVocê será redirecionado para o menu administrativo em instantes...");
												Sleep(1500);
												sairalteracaoadm = true;
												remove("logincripto.dat");
											}
											else
												fclose(admin);
											break;

										case chgsair://logout do adm
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
						Sleep(2000);
					}
				} while (returntomenu == false);
				returntomenu = false;
				break;

			case jogado:
				do {
					system("cls");

					printf("\n\tOpção escolhida: 2. Jogador\n\tEscolha uma das opções abaixo:\n\n\t");
					printMenu(75, false, false);
					printf("\t1. Cadastrar novo jogador\n\t2. Login Jogador\n\t3. Ranking Geral\n\t4. Retornar ao menu anterior\n\n\tOpção: \n\t");
					printMenu(75, true, false);
					scanf("%i", &opcaojogador);

					players = fopen("players.dat", "a+b");
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

								printf("\n\tNome já cadastrado!\n");
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

								printf("\n\tLogin já cadastrado!\n");
								printf("\n\tDigite outro login: ");
								scanf("%s", jogador.login);
							}

						} while (login == false);  //FIM VERIFICAÇÃO LOGIN EXISTENTE

						printf("\n\tDigite sua senha: ");
						scanf("%s", jogador.senha);
						jogador.pontos = 0;
						jogador.tempoAtual = 0;
						jogador.saved == false;
						strcpy(jogador.casoAtual, "textoNULL");
						strcpy(jogador.cidadeAtual, "textoNULL");
						fwrite(&jogador, sizeof(tipoJogador), 1, players);

						fclose(players);

						printf("\n\tCadastro realizado com sucesso! Aguarde um momento...");
						logou = true;
						Sleep(2000);

						break; //-------------------------------------------------------------------FIM LOGIN CADASTRO JOGADOR

					case loginjogador: //-------------------------------------------------------LOGIN JOGADOR

						rewind(players);

						system("cls");


						valido = true;

						fread(&jogador, sizeof(jogador), 1, players);
						if (feof(players))
						{
							printf("\n\tNão há jogadores cadastrados! Faça já o seu cadastro!");
							Sleep(2000);
						}
						else
						{
							rewind(players);
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
									printf("\n\tLogin Inválido...\n\n\tDeseja tentar novamente? (S / N)\n\n\tResposta: ");
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

									printf("\n\tOlá %s\n", jogador.nome);
									printf("\n\tDigite sua senha: ");
									scanf("%s", &auxlogin.senha);

									if (strcmp(jogador.senha, auxlogin.senha) == 0)
									{
										system("cls");
										printf("\n\tLogin efetuado com sucesso!");
										printf("\n\n\tCarregando página jogador...\n");
										Sleep(1500);
										logou = true;
										break;
									}
									else
									{
										rewind(players);

										system("cls");
										printf("\n\tSenha Inválida...\n\n\tDeseja tentar novamente? (S / N)\n\n\tResposta: ");
										getchar();
										scanf("%c", &resposta);
									}

								} while (resposta != 'n' || resposta != 'N');
							}

							if (logou == true)
							{
								logFora = false;

								players = fopen("players.dat", "a+b");
								do {
									do {
										system("cls");
										printf("\n\tBem vindo %s!", jogador.nome);
										printf("\n\t");
										printMenu(30, false, false);
										printf("\tAtualmente você tem %i ponto(s)", jogador.pontos);
										switch (returnLevel(jogador.pontos))
										{
										case Novato:printf("\n\n\tSeu nível é: Novato");
											break;
										case Experiente:printf("\n\n\tSeu nível é: Experiente");
											break;
										case Veterano:printf("\n\n\tSeu nível é: Veterano");
											break;
										}
										printf("\n\t");
										printMenu(30, false, false);
										printf("\n\tEscolha uma das opções abaixo:");
										printf("\n\n\t1.Alterar Cadastro");
										if (jogador.saved == false)
										{
											printf("\n\t2. - Slot vazio - (Sem jogo salvo)");
											printf("\n\t3.Jogar");
											printf("\n\t4.Log out");
											printf("\n\n\tOpção desejada: ");
										}
										else
										{
											printf("\n\t2.Carregar jogo salvo");
											printf("\n\t3.Jogar");
											printf("\n\t4.Log out");
											printf("\n\n\tOpção desejada: ");

										}
										scanf("%i", &jorge);
										resposta = 's';
										if (!jogador.saved && jorge == 2)
										{
											system("cls");
											printf("\n\tVocê não tem um jogo salvo! Escolha outra opção...");
											Sleep(1500);
										}
										if (jogador.saved && jorge == 3)
										{
											printf("\n\tVocê perderá o jogo salvo, deseja proceder?\n\tOpção(S/N): ");
											getchar();
											scanf("%c", &resposta);
											if ((resposta == 's' || resposta == 'S'))
											{
												jogador.saved = false;
											}
										}
										if (!(jorge > 0 && jorge < 5))
										{
											system("cls");
											printf("\n\tDigite uma opção válida!");
											Sleep(1500);
										}
									} while (!(jorge > 0 && jorge < 5) || (resposta == 'n' || resposta == 'N') || (!jogador.saved && jorge == 2));


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
												printf("\n\n\tPor gentileza insira a opção desejada:");
												printf("\n\n\t1. Alterar nome");
												printf("\n\t2. Alterar login");
												printf("\n\t3. Alterar senha");
												printf("\n\t4. Excluir conta");
												printf("\n\t5. Voltar");
												printf("\n\n\tDigite a opção desejada: ");
												scanf("%i", &change);

												switch (change)
												{
												case alterarNome: //-------------------------------------------------------ALTERAR NOME

													reserva = fopen("reserva.dat", "a+b");

													system("cls");

													printf("\n\tOpção escolhida 1.Alterar nome");
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

															printf("\n\tNome já cadastrado!\n");
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

													printf("\n\tOpção escolhida 2.Alterar alterar login");
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

															printf("\n\n\tLogin já cadastrado!\n");
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

													printf("\n\tOpção escolhida 3.Alterar senha");
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

												case excluirConta://----------------------------------------------------EXCLUIR CONTA

													system("cls");

													printf("\n\tTem certeza que deseja excluir a conta?");
													printf("\n\n\t1. Sim");
													printf("\n\t2. Não\n\n\tOpção: ");
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

																printf("\n\tSenha inválida, deseja digitar novamente?");
																printf("\n\n\t1. Sim");
																printf("\n\t2. Não\n\n\tOpção: ");
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
									case carregarjogo:
									case jogar:										
										//loadar o caso							

										casoatualDesc = fopen("casos.dat", "r + b");

										if (jogador.saved == true)
										{
											casoSalvoEncontrado = true;
											while (casoSalvoEncontrado == true)
											{
												fread(&casoatual, sizeof(tipoCaso), 1, casoatualDesc);

												if (strcmp(jogador.casoAtual, casoatual.nomeCaso) == 0)
												{
													casoSalvoEncontrado = false;
													temporestante = jogador.tempoAtual;
													strcpy(casoatual.cidades[cidadeatual], jogador.cidadeAtual);
												}
											}
											jogador.saved = false;
										}
										else
										{
											casoparaloadar = geraCaso(returnLevel(jogador.pontos), casoatualDesc);
											rewind(casoatualDesc);
											fseek(casoatualDesc, casoparaloadar * sizeof(tipoCaso), SEEK_SET);//Achar o caso específico para carregar
											fread(&casoatual, sizeof(tipoCaso), 1, casoatualDesc);
											temporestante = casoatual.tempoDeSolucao;
											jogador.pessoacerta = false;
											jogador.mandato = false;
											jogador.retratoFalado.sexo = 3;
											jogador.retratoFalado.corCabelo = 7;
											jogador.retratoFalado.hobby = 6;
											jogador.retratoFalado.feature = 8;
											strcpy(jogador.cidadeAtual, casoatual.cidades[0]);
										}
										gameover = false;
										ReadingAgain = false;
										while (gameover == false && temporestante > 0 && jogador.saved == false) {
											ingame = true;
											system("cls");
											printf("\n\t\t");
											if (ReadingAgain)
											{
												strcpy(texto, "Caso número ");
												writeout(texto, false, false, true);
												printf("%i", casoparaloadar + 1);
												printf(". \"");
												writeout(casoatual.nomeCaso, true, false, true);
												printf("\"\n\n\t");
												strcpy(texto, "Descrição do caso: ");
												writeout(texto, false, false, true);
												writeout(casoatual.historiaGeral, false, true, true);
												printf("\n");
												printf("\t\t");
												strcpy(texto, "Você está em ");
												writeout(texto, false, false, true);
												writeout(casoatual.cidades[cidadeatual], false, false, true);
												printf("\n");
												printf("\t");
												strcpy(texto, "Descrição deste local: ");
												writeout(texto, false, false, true);
												writeout(casoatual.historiaCidade[cidadeatual], false, true, true);
											}
											else
											{
												strcpy(texto, "Caso número ");
												writeout(texto, false, false, false);
												printf("%i", casoparaloadar + 1);
												printf(". \"");
												writeout(casoatual.nomeCaso, true, false, false);
												printf("\"\n\n\t");
												strcpy(texto, "Descrição do caso: ");
												writeout(texto, false, false, false);
												writeout(casoatual.historiaGeral, false, true, false);
												printf("\n");
												printf("\t\t");
												strcpy(texto, "Você está em ");
												writeout(texto, false, false, false);
												writeout(casoatual.cidades[cidadeatual], false, false, false);
												printf("\n");
												printf("\t");
												strcpy(texto, "Descrição deste local: ");
												writeout(texto, false, false, false);
												writeout(casoatual.historiaCidade[cidadeatual], false, true, false);
												ReadingAgain = true;
											}											
											//printf("\t\tVocê está em %s\n\n", casoatual.cidades[cidadeatual]); , false
											printf("\n\n\t\t");
											strcpy(texto, "Seu tempo restante é: ");
											writeout(texto, false, false, false);
											rightTime(temporestante);
											printf("\t\tO que deseja fazer?\n\n\t\t");
											printMenu(70, false, true);
											printf("\t\t1 - Procurar pistas pelo local\n");
											printf("\t\t2 - Viajar para outro local\n");
											printf("\t\t3 - Atualizar o retrato falado\n");
											printf("\t\t4 - Salvar e sair do jogo\n\n");
											printf("\t\tOpção:\n\t\t");
											printMenu(70, true, true);
											scanf("%i", &opcaoemjogo);											
											switch (opcaoemjogo) { //mudar para enum depois
											case 1://Procurar pistas pela cidade
												stayinoption = true;
												while (stayinoption) {
													system("cls");
													//printf("\t\tQual pista você deseja obter? (Pista 1, 2 ou 3, ou digite 4 para VOLTAR)\n");
													//printf("\tSua opção: ");
													printf("\n\t");
													strcpy(texto, "Você está em ");
													writeout(texto, false, false, false);
													writeout(casoatual.cidades[cidadeatual], false, false, false);
													strcpy(texto, ", e pode procurar por pistas nos seguintes lugares:");
													writeout(texto, false, false, false);
													printf("\n\n\t\t");
													strcpy(texto, "Seu tempo restante é: ");
													writeout(texto, false, false, false);
													rightTime(temporestante);
													printf("\n\t\t");
													printMenu(70, false, true);
													printf("\t\t1 - %s\n", casoatual.POI[cidadeatual * 3 + 0]);
													printf("\t\t2 - %s\n", casoatual.POI[cidadeatual * 3 + 1]);
													printf("\t\t3 - %s\n", casoatual.POI[cidadeatual * 3 + 2]);
													printf("\n\t\tOu digite 4 para VOLTAR");
													printf("\n\n\t\tOpção:\n\t\t");
													printMenu(70, true, true);
													scanf("%i", &opcaoemopcao);
													if (opcaoemopcao > 0 && opcaoemopcao < 4) {
														printf("\n\t\t");
														strcpy(texto, "Você vai para o(a) ");
														writeout(texto, false, false, false);
														writeout(casoatual.POI[cidadeatual * 3 + opcaoemopcao - 1], false, false, false);
														if (cidadeatual == casoatual.culpado[1] && (opcaoemopcao - 1) == casoatual.culpado[2] && jogador.mandato == true)
														{
															if (jogador.pessoacerta == true)
															{
																gameover = true;
																stayinoption = false;
																jogador.saved = false;
																strcpy(texto, " e...");
																writeout(texto, true, false, false);
																system("cls");
																printf("\n\n\t\t");
																strcpy(texto, "Se depara com o(a) culpado(a), segundo seu retrato falado.");
																writeout(texto, false, false, false);
																printf("\n\t\t");
																strcpy(texto, "Você conseguiu prender o culpado! Parabéns Sr(a). ");
																writeout(texto, false, false, false);
																writeout(jogador.nome, false, false, false);
																printf("\n\t\t");
																switch (casoatual.dificuldade)
																{
																case 1:
																	if (temporestante > casoatual.tempoDeSolucao / 2) {
																		jogador.pontos += 2000;
																		strcpy(texto, "Deste modo, você foi recompensado com 2000 pontos por\n\t\tacabar antes da metade do tempo!");
																		writeout(texto, false, false, false);
																	}
																	else {
																		jogador.pontos += 1000;
																		strcpy(texto, "Deste modo, você foi recompensado com 1000 pontos!");
																		writeout(texto, false, false, false);
																	}

																	break;
																case 2:
																	if (temporestante > casoatual.tempoDeSolucao / 2) {
																		jogador.pontos += 1000;
																		strcpy(texto, "Deste modo, você foi recompensado com 1000 pontos por\n\t\tacabar antes da metade do tempo!");
																		writeout(texto, false, false, false);
																	}
																	else {
																		jogador.pontos += 500;
																		strcpy(texto, "Deste modo, você foi recompensado com 500 pontos!");
																		writeout(texto, false, false, false);
																	}
																	break;
																case 3:
																	if (temporestante > casoatual.tempoDeSolucao / 2) {
																		jogador.pontos += 500;
																		strcpy(texto, "Deste modo, você foi recompensado com 500 pontos por\n\t\tacabar antes da metade do tempo!");
																		writeout(texto, false, false, false);
																	}
																	else {
																		jogador.pontos += 250;
																		strcpy(texto, "Deste modo, você foi recompensado com 250 pontos!");
																		writeout(texto, false, false, false);
																	}
																}

															}
															else
															{
																gameover = true;
																stayinoption = false;
																jogador.saved = false;
																strcpy(texto, " e...");
																writeout(texto, true, false, false);
																system("cls");
																printf("\n\n\t\t");
																strcpy(texto, "Se depara com o(a) culpado(a), segundo seu retrato falado.");
																writeout(texto, false, false, false);
																printf("\n\t\t");
																strcpy(texto, "Você prendeu o suspeito porém ele(a) era inocente!");
																writeout(texto, false, false, false);
																printf("\n\t\t");
																strcpy(texto, "Isso não deveria ter acontecido Sr(a). ");
																writeout(texto, false, false, false);
																writeout(jogador.nome, false, false, false);
																printf("\n\t\t");
																switch (casoatual.dificuldade)
																{
																case 1:
																	jogador.pontos += 50;
																	strcpy(texto, "Mesmo assim, você foi recompensado com 50 pontos por\n\t\ttentar solucionar este caso!");
																	writeout(texto, false, false, false);

																	break;
																case 2:
																	jogador.pontos += 25;
																	strcpy(texto, "Mesmo assim, você foi recompensado com 25 pontos por\n\t\ttentar solucionar este caso!");
																	writeout(texto, false, false, false);
																	break;
																case 3:
																	jogador.pontos += 10;
																	strcpy(texto, "Mesmo assim, você foi recompensado com 10 pontos por\n\t\ttentar solucionar este caso!");
																	writeout(texto, false, false, false);
																}
															}
															printf("\n\t\t");
															system("pause");
														}
														else
														{
															strcpy(texto, ", e então, recebe uma pista.");
															writeout(texto, false, false, false);
															printf("\n\t\t");
															writeout(casoatual.pessoaDica[cidadeatual * 3 + opcaoemopcao - 1], false, false, false);
															strcpy(texto, " disse:");
															writeout(texto, false, false, false);
															printf("\n\n\t\t");
															writeout(casoatual.pistas[cidadeatual * 3 + opcaoemopcao - 1], false, true, false);
															printf("\n\t\t");
															system("pause");
															temporestante -= casoatual.tempoParaPOI;
														}
													}
													else if (opcaoemopcao == 4)
													{
														stayinoption = false;
														system("cls");
													}
													else printf("\n\t\tPista inválida\n");
												}
												break;
											case 2://Viajar para outra cidade
												stayinoption = true;
												while (stayinoption) {
													system("cls");
													printf("\n\t\t");
													strcpy(texto, "Para qual local você quer ir? (ou digite '0' para VOLTAR)");
													writeout(texto, false, false, false);
													printf("\n\t\t");
													strcpy(texto, "Seu tempo restante é: ");
													writeout(texto, false, false, false);
													rightTime(temporestante);
													printf("\n\t\t");
													printMenu(70, false, true);
													contaCidadesImpressas = 1;
													for (int i = 0; i < casoatual.numeroCidades; i++)
													{
														if (!(strcmp(casoatual.cidades[i], casoatual.cidades[cidadeatual]) == 0))
														{
															printf("\t\t%i - %s\n", contaCidadesImpressas, casoatual.cidades[i]);
															contaCidadesImpressas++;
														}
														else
														{
															naoContaEstaCidade = i;
														}
													}														
													printf("\n\t\tOpção:\n\t\t");
													printMenu(70, true, true);
													scanf("%i", &opcaoemopcao);
													if(opcaoemopcao == 0)
														stayinoption = false;
													else
													{
														if (opcaoemopcao >= naoContaEstaCidade)
															opcaoemopcao++;
														if (opcaoemopcao > 0 && opcaoemopcao < casoatual.numeroCidades + 1) {
															printf("\n\n\t\t");
															strcpy(texto, "Indo para ");
															writeout(texto, false, false, false);
															writeout(casoatual.cidades[opcaoemopcao - 1], false, false, false);
															strcpy(texto, "...");
															writeout(texto, true, false, false);

															cidadeatual = opcaoemopcao - 1;
															temporestante -= casoatual.tempoEntreLocais;
															Sleep(1500);
															stayinoption = false;
														}
														else printf("\n\tCidade inválida\n");
													}													
												}
												break;
											case 3://Retrato falado
												stayinoption = true;

												while (stayinoption) {
													system("cls");
													printf("\n\t\tO retrato falado atual é: \n\n\t\t");
													checkPerson tempcheck;

													printMenu(70, false, true);
													printf("\t\tSexo:             %s\n", tempcheck.sexo[jogador.retratoFalado.sexo - 1]);
													printf("\t\tCor do cabelo:    %s\n", tempcheck.corCabelo[jogador.retratoFalado.corCabelo - 1]);
													printf("\t\tHobby:            %s\n", tempcheck.hobby[jogador.retratoFalado.hobby - 1]);
													printf("\t\tSímbolo marcante: %s\n\t\t", tempcheck.feature[jogador.retratoFalado.feature - 1]);
													printMenu(70, false, true);

													printf("\n\n\t\tQual característica você deseja atualizar?\n");
													printf("\t\t1 - Gênero\n");
													printf("\t\t2 - Cor do cabelo\n");
													printf("\t\t3 - Hobby\n");
													printf("\t\t4 - Símbolo marcante\n");
													printf("\n\t\t5 ----- COMPUTAR -----\n\n");
													printf("\t\t6 - VOLTAR\n");
													printf("\n\n\t\tOpção: ");

													QualCaracteristica car;
													scanf("%i", &car);
													car = (QualCaracteristica)((int)car - 1);

													int newval = checkCarac(car, ingame);
													switch (car) {
													case sexo: jogador.retratoFalado.sexo = newval;
														break;
													case corDeCabelo: jogador.retratoFalado.corCabelo = newval;
														break;
													case Hobby: jogador.retratoFalado.hobby = newval;
														break;
													case Feature: jogador.retratoFalado.feature = newval;
														break;
													case 4: printf("\n\n\t\t");
														strcpy(texto, "--------- Computando possíveis suspeitos... ----------");
														writeout(texto, false, false, false);
														printf("\n\n");
														contaSuspeitos = 0;
														MAXCaracts = 0;
														for (int k = 0; k < casoatual.quantSusp; k++) {
															contaCaracts = 0;
															if (jogador.retratoFalado.sexo == casoatual.personagens[k].sexo)
																contaCaracts++;
															if (jogador.retratoFalado.corCabelo == casoatual.personagens[k].corCabelo)
																contaCaracts++;
															if (jogador.retratoFalado.hobby == casoatual.personagens[k].hobby)
																contaCaracts++;
															if (jogador.retratoFalado.feature == casoatual.personagens[k].feature)
																contaCaracts++;
															if (contaCaracts > MAXCaracts)
																MAXCaracts = contaCaracts;

														}
														for (int k = 0; k < casoatual.quantSusp; k++) {
															contaCaracts = 0;
															if (jogador.retratoFalado.sexo == casoatual.personagens[k].sexo)
																contaCaracts++;
															if (jogador.retratoFalado.corCabelo == casoatual.personagens[k].corCabelo)
																contaCaracts++;
															if (jogador.retratoFalado.hobby == casoatual.personagens[k].hobby)
																contaCaracts++;
															if (jogador.retratoFalado.feature == casoatual.personagens[k].feature)
																contaCaracts++;
															if (contaCaracts == MAXCaracts)
															{
																printf("\t\t\t");
																strcpy(texto, "-> ");
																writeout(texto, false, false, false);
																writeout(casoatual.personagens[k].nome, false, false, false);
																printf("\n");
																strcpy(suspeitos[contaSuspeitos], casoatual.personagens[k].nome);
																contaSuspeitos++;
															}
														}
														printf("\n\n\t\t");
														strcpy(texto, "------------  Fim da lista de suspeitos  ------------");
														writeout(texto, false, false, false);
														printf("\n");
														if (contaSuspeitos == 1)
														{
															jogador.mandato = true;
															printf("\n\n\t");
															strcpy(texto, "Foi emitido o mandato de prisão para ");
															writeout(texto, false, false, false);
															writeout(suspeitos[0], false, false, false);
															jogador.pessoacerta = false;
															for (int k = 0; k < casoatual.quantSusp; k++)
															{
																if (strcmp(casoatual.personagens[k].nome, suspeitos[0]) == 0)
																{
																	if (k == casoatual.culpado[0])
																	{
																		jogador.pessoacerta = true;
																	}
																}
															}
															printf("\n");

														}
														contaSuspeitos = 0;
														system("pause");
														break;
													case 5: stayinoption = false; break;
													default: printf("\n\tCaracterística inválida\n");
														Sleep(1500);
														break;
													}													
												}
												break;
											case 4://salvar jogo
												system("cls");
												printf("\n\t\tO que você deseja fazer?\n\n\t\t");
												printMenu(70, false, true);
												printf("\t\t1 - Salvar o jogo e sair\n\t\t");
												printf("2 - VOLTAR\n");
												printf("\n\t\tOpção:\n\t\t");
												printMenu(70, true, true);
												scanf("%i", &opcaoemopcao);
												if (opcaoemopcao == 1)
												{
													jogador.tempoAtual = temporestante;
													strcpy(jogador.cidadeAtual, casoatual.cidades[cidadeatual]);
													strcpy(jogador.casoAtual, casoatual.nomeCaso);

													printf("\n\tJogo salvo com sucesso! ");
													printf("Retornando ao menu do jogador...");
													jogador.saved = true;
													Sleep(1500);
												}
												break;
											default: printf("Opção não reconhecida, tente novamente...");
												Sleep(2000);
												break;
											}
										}
										if (temporestante < 0)
										{
											system("cls");
											printf("\n\tVocê perdeu! Foi excedido o tempo limite do caso e por isso o culpado fugiu!\n\tVoltando ao menu do jogador...");
											jogador.tempoAtual = 0;
											Sleep(1500);
										}
										fclose(casoatualDesc);
										ingame = false;

										fclose(players);
										players = fopen("players.dat", "r+b");
										i = 0;
										do {
											fread(&player, sizeof(tipoJogador), 1, players);
											if (!feof(players))
											{
												if (strcmp(jogador.login, player.login) == 0)
												{
													fseek(players, i * sizeof(tipoJogador), SEEK_SET);
													fwrite(&jogador, sizeof(tipoJogador), 1, players);
													fseek(players, (i + 1) * sizeof(tipoJogador), SEEK_SET);
												}
												i++;
											}
										} while (!feof(players));

										fclose(players);
										break;
									case logOut:
										logFora = true;
										fclose(players);
										break;
									default:
										break;
									}
								} while (logFora == false);
							}
						}

						fclose(players);

						break;
					case rank:
						ranking();
						break;

					case saair:
						break;
					}
				}while (opcaojogador != 4);
				break;
			case README:
				system("cls");
				system("TYPE tutorialingame.txt");
				system("pause");
				system("cls");
				break;
			case credit:
				system("cls");
				system("TYPE creditos.txt");
				system("pause");
				system("cls");
				break;
			}
		}

	} while (log != sair);

	//newPersona();
	//oldPersona(personagem);
	/*casos = fopen("casos.dat", "a + b");

	fread(&caso, sizeof(caso), 1, casos);

	printf("%s\n", caso.personagens[0].nome);
	printf("%s\n", caso.personagens[1].nome);
	printf("%s\n", caso.personagens[2].nome);

	fclose(casos);
	*/
	return 0;
}

int oldPersona(tipoPersonagem* personagens)
{
	FILE* fd = fopen("personagem.dat", "a + b");
	int i = 0, qtdPersonas = 0, j = 0, recebeOpcao;
	tipoPersonagem aux[200], intermediaria;
	checkPerson checarCaract;
	char verificaListadePersonagem;
	bool repeteLista = true;

	do {
		system("cls");

		printf("\n\tEscolha o personagem que deseja colocar em seu caso\n\n");

		rewind(fd);

		do
		{
			fread(&intermediaria, sizeof(intermediaria), 1, fd);

			if (!feof(fd))
			{
				printf("\t%i. %s do sexo %s, cabelo %s,", i + 1, intermediaria.nome, checarCaract.sexo[intermediaria.sexo - 1], checarCaract.corCabelo[intermediaria.corCabelo - 1]);
				printf(" gosta de %s e seu símbolo marcante é %s \n", checarCaract.hobby[intermediaria.hobby - 1], checarCaract.feature[intermediaria.feature - 1]);
				qtdPersonas++;

				{
					strcpy(aux[i].nome, intermediaria.nome);
					aux[i].sexo = intermediaria.sexo;
					aux[i].corCabelo = intermediaria.corCabelo;
					aux[i].hobby = intermediaria.hobby;
					aux[i].feature = intermediaria.feature;
				}
			}

			i++;
		} while (!feof(fd));

		printf("\n\tDigite o número ou digite '0' quando desejar parar (MAX 30 personagens): ");
		j = 0;
		do {
			printf("\n\tOpção: ");
			scanf("%i", &recebeOpcao);
			if (recebeOpcao > 0)
			{
				strcpy(personagens[j].nome, aux[recebeOpcao - 1].nome);
				personagens[j].sexo = aux[recebeOpcao - 1].sexo;
				personagens[j].corCabelo = aux[recebeOpcao - 1].corCabelo;
				personagens[j].hobby = aux[recebeOpcao - 1].hobby;
				personagens[j].feature = aux[recebeOpcao - 1].feature;
				j++;
			}
		} while (recebeOpcao > 0);
		system("cls");
		printf("\n\tPersonagens selecionados: \n\n");
		for (i = 0; i < j; i++)
		{
			printf("\t%i . %s do sexo %s, cabelo %s,", i + 1, personagens[i].nome, checarCaract.sexo[personagens[i].sexo-1], checarCaract.corCabelo[personagens[i].corCabelo - 1]);
			printf(" gosta de %s e seu símbolo marcante é %s \n", checarCaract.hobby[personagens[i].hobby - 1], checarCaract.feature[personagens[i].feature - 1]);
		}
		i = 0;
		printf("\n\tDeseja refazer a lista de personagens envolvidos neste caso?\n\tOpção(S/N): ");
		getchar();
		scanf("%c", &verificaListadePersonagem);
		if (verificaListadePersonagem == 'n' || verificaListadePersonagem == 'N') 
			repeteLista = false;
	} while (repeteLista);

	fclose(fd);

	return j;
}

void newPersona()
{
	FILE* fd = fopen("personagem.dat", "a + b");
	bool flag = false, ingame = false;
	char resposta;
	tipoPersonagem aux, ajudadora;

	do {
		system("cls");
		printf("\n\tCadastro de personagens\n");
		printf("\n\tDigite o nome do seu novo personagem: ");
		getchar();
		fgets(aux.nome, 50, stdin);
		for (int t = 0; t < strlen(aux.nome); t++)
		{
			if (aux.nome[t] == '\n')
				aux.nome[t] = '\0';
		}

		rewind(fd);

		do
		{
			fread(&ajudadora, sizeof(tipoPersonagem), 1, fd);

			if (strcmp(ajudadora.nome, aux.nome) == 0 && fd != NULL)
			{
				do
				{
					system("cls");
					printf("\n\tNome ja cadastrado!");
					printf("\n\n\tTente um nome diferente: ");
					fflush(stdin);
					fgets(aux.nome, 50, stdin);

				} while (strcmp(ajudadora.nome, aux.nome) == 0);
			}

		} while (!feof(fd));

		system("cls");
		printf("\n\tDigite o sexo de %s, de acordo com a tabela:\n", aux.nome);
		aux.sexo = checkCarac(sexo, ingame);
		system("cls");

		printf("\n\tDigite a cor do cabelo do(a) %s, de acordo com a tabela: ", aux.nome);
		aux.corCabelo = checkCarac(corDeCabelo, ingame);
		system("cls");

		printf("\n\tDigite um hobby do(a) %s, de acordo com a tabela: ", aux.nome);
		aux.hobby = checkCarac(Hobby, ingame);
		system("cls");

		printf("\n\tDigite um símbolo marcante do(a) %s, de acordo com a tabela: ", aux.nome);
		aux.feature = checkCarac(Feature, ingame);
		system("cls");

		getchar();
		printf("\n\tDeseja cadastrar mais personagens (S/N): ");
		scanf("%c", &resposta);

		fwrite(&aux, sizeof(tipoPersonagem), 1, fd);

		if (resposta == 'n' || resposta == 'N')
		{
			flag = true;
			fclose(fd);
		}

	} while (flag == false);


}

int checkCarac(QualCaracteristica caracteristica, bool playing) {
	int escolha;
	fflush(stdin);
	if (playing)
	{
		switch (caracteristica)
		{
		case sexo:
			do {
				printf("\n\n\tSexos disponíveis:\n\n\t1.Masculino;\n\t2.Feminino;\n\t3.  -  \n\n\tOpção: ");
				scanf("%i", &escolha);
				if (escolha < 1 || escolha > 3)
				{
					printf("\n\tDigite uma opção válida!");
					Sleep(1500);
					system("cls");
				}
			} while (escolha < 1 || escolha > 3);
			return escolha;
		case corDeCabelo:
			do {
				printf("\n\n\tCores de cabelo disponíveis:\n\n\t1.Preto;\n\t2.Castanho;\n\t3.Loiro;\n\t4.Vermelho;\n\t5.Azul;\n\t6.Branco;\n\t7.  -  \n\n\tOpção: ");
				scanf("%i", &escolha);
				if (escolha < 1 || escolha > 7)
				{
					printf("\n\tDigite uma opção válida!");
					Sleep(1500);
					system("cls");
				}
			} while (escolha < 1 || escolha > 7);
			return escolha;
		case Hobby:
			do {
				printf("\n\n\tHobbies disponíveis:\n\n\t1.Caminhar;\n\t2.Jogar;\n\t3.Tocar instrumento(s);\n\t4.Ler;\n\t5.Discutir;\n\t6.  -  \n\n\tOpção: ");
				//{ "Caminhar", "Jogar", "Tocar instrumento", "Ler", "Discutir" };
				scanf("%i", &escolha);
				if (escolha < 1 || escolha > 6)
				{
					printf("\n\tDigite uma opção válida!");
					Sleep(1500);
					system("cls");
				}
			} while (escolha < 1 || escolha > 6);
			return escolha;
		case Feature:
			do {
				printf("\n\n\tSímbolos marcantes disponíveis:\n\n\t1.Chapéu;\n\t2.Boné;\n\t3.Tatuagem;\n\t4.Óculos;\n\t5.Pulseira;\n\t6.Anel;\n\t7.Colar;\n\t8.  -  \n\n\tOpção: ");
				//{"Chapéu", "Boné", "Tatuagem", "Óculos", "Pulseira", "Anel", "Colar"};
				scanf("%i", &escolha);
				if (escolha < 1 || escolha > 8)
				{
					printf("\n\tDigite uma opção válida!");
					Sleep(1500);
					system("cls");
				}
			} while (escolha < 1 || escolha > 8);
			return escolha;
		}
	}
	else
	{
		switch (caracteristica)
		{
		case sexo:
			do {
				printf("\n\n\tSexos disponíveis:\n\n\t1.Masculino;\n\t2.Feminino\n\n\tOpção: ");
				scanf("%i", &escolha);
				if (escolha < 1 || escolha > 2)
				{
					printf("\n\tDigite uma opção válida!");
					Sleep(1500);
					system("cls");
				}
			} while (escolha < 1 || escolha > 2);
			return escolha;
		case corDeCabelo:
			do {
				printf("\n\n\tCores de cabelo disponíveis:\n\n\t1.Preto;\n\t2.Castanho;\n\t3.Loiro;\n\t4.Vermelho;\n\t5.Azul;\n\t6.Branco\n\n\tOpção: ");
				scanf("%i", &escolha);
				if (escolha < 1 || escolha > 6)
				{
					printf("\n\tDigite uma opção válida!");
					Sleep(1500);
					system("cls");
				}
			} while (escolha < 1 || escolha > 6);
			return escolha;
		case Hobby:
			do {
				printf("\n\n\tHobbies disponíveis:\n\n\t1.Caminhar;\n\t2.Jogar;\n\t3.Tocar instrumento(s);\n\t4.Ler;\n\t5.Discutir\n\n\tOpção: ");
				//{ "Caminhar", "Jogar", "Tocar instrumento", "Ler", "Discutir" };
				scanf("%i", &escolha);
				if (escolha < 1 || escolha > 5)
				{
					printf("\n\tDigite uma opção válida!");
					Sleep(1500);
					system("cls");
				}
			} while (escolha < 1 || escolha > 5);
			return escolha;
		case Feature:
			do {
				printf("\n\n\tSímbolos marcantes disponíveis:\n\n\t1.Chapéu;\n\t2.Boné;\n\t3.Tatuagem;\n\t4.Óculos;\n\t5.Pulseira;\n\t6.Anel;\n\t7.Colar\n\n\tOpção: ");
				//{"Chapéu", "Boné", "Tatuagem", "Óculos", "Pulseira", "Anel", "Colar"};
				scanf("%i", &escolha);
				if (escolha < 1 || escolha > 7)
				{
					printf("\n\tDigite uma opção válida!");
					Sleep(1500);
					system("cls");
				}
			} while (escolha < 1 || escolha > 7);
			return escolha;
		}
	}
	return caracteristica;
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

void rightTime(int tempo) {
	int temp = tempo / 86400;
	printf("%02d ", temp);
	writeout("dias", false, false, false);
	tempo %= 86400;
	temp = tempo / 3600;
	printf(", %02d ", temp);
	writeout("horas", false, false, false);
	tempo %= 3600;
	temp = tempo / 60;
	printf(", %02d ", temp);
	writeout("minutos", false, false, false);
	tempo %= 60;
	printf(", %02d ", tempo);
	writeout("segundos", false, false, false);
	printf("\n\n");
}
//INC
void writeout(char* texto, bool pauseonnewline, bool newLineIndentation, bool skip) {
	bool backandforth = true, anotherOne = false;
	int add, next=0;
	for (unsigned int i = 0; i < strlen(texto); i++) {
		if (pauseonnewline && texto[i] == '\n')
			system("pause");
		add = checkforcommand(texto, i);
		if (add == 0 && !skip) {
			printf("%c", texto[i]);
			Sleep(returncustomtimer(texto[i]));
		}
		if (skip) {
			printf("%c", texto[i]);
		}
		if (newLineIndentation) {
			next++;
			if (!anotherOne) {
				if (next > 50 && texto[i] == ' ') {
					next = 0;
					printf("\n\t");
					anotherOne = true;
				}
			}
			else {
				if (next > 70 && texto[i] == ' ') {
					next = 0;
					printf("\n\t");
				}
			}
			
		}
		i += add;
	}
}

int returncustomtimer(char c) {
	switch (c) {
	case '.': return 350;
	case ',': return 140;
	case ';': return 500;
	default: return 30;
	}
}

int checkforcommand(char* texto, int curindex) {
	char rcv[20];
	char cmp[20];
	char cmd[20];
	int j, t;
	rcv[0] = '\0';
	strcpy(cmp, "system(\"");
	for (j = curindex; j < curindex + 8; j++)
		rcv[j - curindex] = texto[j];
	rcv[j - curindex] = '\0';
	if (strcmp(cmp, rcv) == 0) {
		t = 0;
		while (texto[j] != '\"') {
			cmd[t] = texto[j];
			j++;
			t++;
		}
		cmd[t] = '\0';
		system(cmd);
		return j + 2 - curindex;
	}
	return 0;
}

 Nivel returnLevel(int lv) {
	 if (lv == 0)
		 return Novato;
	 lv /= 2000;
	 switch(lv)
	 {
	 case 0:
		 return Novato;
		 break;
	 case 1:
		 return Experiente;
		 break;
	 case 2:
		 return Veterano;
		 break;
	 default:
		 return Veterano;
		 break;
	 }
}

 int geraCaso(Nivel x, FILE* arq)
 {
	 srand(time(NULL));
	 rewind(arq);
	 int contador = 1, possivelCaso[10] = {0}, cpC = 0, posicaoVetor;
	 tipoCaso checkDific;
	 do {
		 fread(&checkDific, sizeof(tipoCaso), 1, arq);
		 if (!feof(arq))
		 {
			 if ((checkDific.dificuldade - 1) == x)
			 {
				 if (cpC < 10)
				 {
					 possivelCaso[cpC] = contador;
					 cpC++;
				 }
			 }
			 contador++;
		 }	 
	 } while (!feof(arq));
	 posicaoVetor = rand() % cpC;
	 contador = (possivelCaso[posicaoVetor] - 1);
	 return contador;
 }

 void printMenu(int x, bool IsItTheEnd, bool InGame) {
	 if (InGame) {
		 for (int i = 0; i < (x-6); i++)
			 printf("-");
	 }
	 else
	 {
		 for (int i = 0; i < x; i++)
			 printf("-");
	 }	 
	 if (IsItTheEnd)
	 {
		 if(InGame)
			 printf("\r\b\r\t\tOpção: ");
		 else
			 printf("\r\b\r\tOpção: ");
	 }		 
	 else
		 printf("\n");
 }

 void animaIntro() {
	 for (int i = 0; i < 10; i++)
	 {
		 system("cls");
		 for(int j=0; j < i; j++)
			 printf("\n");
		 printf("\t\t");
		 printMenu(55, false, false);
		 printf("\t\tOnde no Universo do Cinema/Série está Carmen Sandiego?\n\t\t\7");	
		 printMenu(55, false, false);
		 Sleep(50);
	 }
	 for (int i = 0; i < 28; i++)
	 {
		 system("cls");
		 for (int j = 0; j < 9; j++)
			 printf("\n");
		 printf("\t\t");
		 printMenu(55, false, false);
		 printf("\t\tOnde no Universo do Cinema/Série está Carmen Sandiego?\n\t\t\7");
		 printMenu(55, false, false);
		 for (int j = 0; j < (27-i); j++)
			 printf("\n");
		 printf("\t\t\t   Projeto APC-B, escrito em C++");
		 Sleep(50);
	 }
	 printf("\n\n\t\t\t");

	 system("pause");
 }

//for (int t = 0; t < strlen(caso.cidades[contaCidade]); t++)
//{
//	if (caso.cidades[contaCidade][t] == '\n')
//		caso.cidades[contaCidade][t] = '\0';
//}

 void ranking()
 {
	 FILE* fd = fopen("players.dat", "rb");
	 tipoJogador jogador, aux;
	 int maior = 0;
	 int opcao, quantMaior = 0, i, j, min;
	 int quantidadeJogadores;
	 int count;
	 int tamAsc;
	 int point[500], xx;
	 char m[500][30], x[30], tecla;
	 bool primeiro = true, sgundo = true;

	 system("cls");

	 printf("\n\tRanking dos jogadores!");
	 printf("\n\n\tDigite o modo de ordenacao: \n");
	 printf("\n\t1. Por nome"); //Alfabeto	
	 printf("\n\t2. Por nivel"); //Pontos ordem cadastro
	 printf("\n\t3. Por ranking"); //Nivel = logo pontos desempatam
	 printf("\n\t4. Voltar");
	 printf("\n\n\tOpcao: ");
	 getchar();
	 scanf("%i", &opcao);

	 system("cls");

	 switch (opcao)
	 {
	 case 1:

		 printf("\n\tNivel      Nome\n\n");
		 quantidadeJogadores = 0;
		 tamAsc = 0;
		 primeiro = true;
		 i = 0;

		 do
		 {
			 fread(&jogador, sizeof(tipoJogador), 1, fd);

			 if (!feof(fd))
			 {
				 strcpy(m[i], jogador.nome);
				 point[i] = jogador.pontos;
				 quantidadeJogadores++;
			 }
			 i++;

		 } while (!feof(fd));

		 for (i = 0; i < quantidadeJogadores; i++)
		 {
			 for (j = 0; j < quantidadeJogadores - 1; j++)
			 {
				 if (strcmp(m[j], m[j + 1]) > 0)
				 {
					 strcpy(x, m[j]);
					 xx = point[j];
					 strcpy(m[j], m[j + 1]);
					 point[j] = point[j + 1];
					 strcpy(m[j + 1], x);
					 point[j + 1] = xx;
				 }
			 }
		 }

		 for (i = 0; i < quantidadeJogadores; i++)
		 {
			 printf("\t%i         %s\n", point[i] / 100, m[i]);
		 }

		 break;


	 case 2:

		 printf("\n\tPosicao      Nivel      Nome\n\n");
		 quantidadeJogadores = 0;

		 do
		 {
			 fread(&jogador, sizeof(tipoJogador), 1, fd);

			 if ((jogador.pontos / 100) >= maior)
				 maior = jogador.pontos / 100;

			 quantidadeJogadores++;

		 } while (!feof(fd));

		 rewind(fd);

		 quantMaior = 0;
		 i = 1;
		 count = 0;

		 do
		 {
			 fread(&aux, sizeof(tipoJogador), 1, fd);

			 if ((aux.pontos / 100) == maior && !feof(fd))
			 {
				 printf("\t   %i           %i        %s\n", i, aux.pontos / 100, aux.nome);
				 count++;
				 i++;
			 }
			 if (feof(fd))
			 {
				 if (count == quantidadeJogadores - 1)
					 break;

				 rewind(fd);
				 maior--;
			 }

		 } while (count != quantidadeJogadores - 1);

		 rewind(fd);

		 break;

	 case 3:

		 printf("\n\tRanking      Nivel      Nome\n\n");
		 quantidadeJogadores = 0;

		 do
		 {
			 fread(&jogador, sizeof(tipoJogador), 1, fd);

			 if ((jogador.pontos) >= maior)
				 maior = jogador.pontos;

			 quantidadeJogadores++;

		 } while (!feof(fd));

		 rewind(fd);

		 quantMaior = 0;
		 i = 1;
		 count = 0;

		 do
		 {
			 fread(&aux, sizeof(tipoJogador), 1, fd);

			 if (aux.pontos == maior && !feof(fd))
			 {
				 printf("\t   %i           %i        %s\n", i, aux.pontos / 100, aux.nome);
				 count++;
				 i++;
			 }
			 if (feof(fd))
			 {
				 if (count == quantidadeJogadores - 1)
					 break;

				 rewind(fd);
				 maior--;
			 }

		 } while (count != quantidadeJogadores - 1);

		 rewind(fd);

		 break;
	 case 4:
		 fclose(fd);
		 break;
	 default:
		 break;
	 }

	
	 fclose(fd);
	 printf("\n\n\t");
	 system("pause");
 }
