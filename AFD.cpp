#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

struct Transicao
{
	string pos_Estado;
	string valor_Lido;
};

struct Estado
{
	string nome{};
	Transicao transicao[2]{};
	bool inicial = false;
	bool final = false;
	
	const string returnPos_Estado(string valor_lido) {
		for (size_t i = 0; i < 2; i++)
		{
			if (valor_lido == transicao[i].valor_Lido) {
				return transicao[i].pos_Estado;
			}
		}
	}
};

void line(char simbolo = '-', int tam = 34);
bool checkCadeia(Estado * estados[], string& cadeia, int& quantEst);

int main() {
	system("chcp 1252 > nul");
	cout << "Insira as informações do autômato!" << endl;
	line('=');
	cout << "\nQuantos estados serão? ";
	int quantEst = 0;
	cin >> quantEst;
	line();

	Estado * estados = new Estado[quantEst];

	for (size_t i = 0; i < quantEst; i++)
	{
		cout << "Qual o estado " << i << "? ";
		cin >> estados[i].nome;
		cout << endl;
	}

	line();

	cout << "Quais serão os simbolos do alfabeto?" << endl;

	string simbolos[2]{};

	for (size_t i = 0; i < 2; i++)
	{
		cout << "Simbolo " << i + 1 << ": ";
		cin >> simbolos[i];
		cout << endl;
	}

	line('-',81);

	cout << "Entre com as transições de cada estado!" << endl;
	cout << "Para cada estado é perguntado, qual será o estado resultado da leitura do símbolo." << endl;
	cout << "Você precisa responder baseado na tabela de estados que você informou." << endl;
	line('-',81);
	cout << "TABELA DE ESTADOS" << endl;
	for (size_t i = 0; i < quantEst; i++)
	{
		cout << "Estado " << i+1 << ": " << estados[i].nome << endl;
	}
	line();

	for (int i = 0; i < quantEst; i++)
	{
		for (size_t j = 0; j < 2; j++)
		{
			bool check = false;
			do
			{
				cout << "Transição do estado " << estados[i].nome << " lendo " << simbolos[j] << ": ";
				cin >> estados[i].transicao[j].pos_Estado;
				for (size_t c = 0; c < quantEst; c++)
				{
					if (estados[i].transicao[j].pos_Estado == estados[c].nome) {
						check = true;
						break;
					}
				}

				if (check == false) {
					line();
					cout << "Estado inexistente, tente novamente!";
					line();
				}
				
			} while (check == false);
			estados[i].transicao[j].valor_Lido = simbolos[j];
		}
	}
	
	line();
	string inicial{};

	bool check1;

	do
	{
		check1 = false;
		cout << "Quais é o estado inicial? " << endl;
		cin >> inicial;

		for (size_t i = 0; i < quantEst; i++)
		{
			check1 = false;

			if (inicial == estados[i].nome) {
				estados[i].inicial = true;
				check1 = true;
				break;
			}
		}

		if (check1 == false) {
			line();
			cout << "Estado inexistente, tente novamente!" << endl;
			line();
		}

	} while (check1 == false);

	line();

	cout << "Agora informa quais estados são finais!\n" << endl;

	string final;

	for (size_t i = 0; i < quantEst; i++)
	{
		check1 = false;
		cout << "Estado final " << i + 1 << ": ";
		cin >> final;

		std::transform(final.begin(), final.end(), final.begin(), [](unsigned char c) { return std::tolower(c); });

		if (final == "true") {
			estados[i].final = true;
		}
	}

	line('=', 82);

	cout << "Agora vamos testar com entradas do seu autômato!" << endl;
	cout << "Case queira parar, apenas pressione \"Enter\"\n" << endl;
	string cadeia;
	do
	{
		line();
		cout << "Cadeia: ";
		cin >> cadeia;
		bool result = checkCadeia(&estados, cadeia, quantEst);
		if (result == true) {
			cout << "Cadeia é aceita pelo autômato!" << endl;
		}
		else {
			cout << "Cadeia não é aceita pelo autômato!" << endl;
		}
	} while (cadeia != "");

	delete[] estados;

	return 0;
}

bool checkCadeia(Estado* estados[], string & cadeia, int & quantEst) {
	Estado estadoAtual;
	int index = 0;
	int tamanho = cadeia.length();

	for (int i = 0; i < tamanho; i++) {
		string valorLido = cadeia.substr(i, 1); // Lê um caractere da cadeia

		estadoAtual.nome = (*estados)[index].returnPos_Estado(valorLido);

		// Encontra o próximo estado com o valor lido
		bool transicaoEncontrada = false;
		for (int c = 0; c < quantEst; c++) {
			if (estadoAtual.nome == (*estados)[c].nome) {
				estadoAtual = (*estados)[c];
				index = c; // Atualiza o índice para o próximo estado
				transicaoEncontrada = true;
				break;
			}
		}

		// Se não houver transição para o próximo estado, a cadeia é rejeitada
		if (!transicaoEncontrada) {
			return false;
		}
	}

	// Verifica se o estado atual é final
	if (estadoAtual.final) {
		return true;
	}

	return false;
}

void line(char simbolo, int tam) {
	for (size_t i = 0; i < tam; i++)
	{
		cout << simbolo;
	}
	cout << "\n";
}