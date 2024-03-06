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
};

void line(char simbolo = '-', int tam = 34);
bool checkCadeia(Estado * estados [], char cadeia[]);

int main() {
	system("chcp 1252 > nul");
	cout << "Insira as informa��es do aut�mato!" << endl;
	line('=');
	cout << "\nQuantos estados ser�o? ";
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

	cout << "Quais ser�o os simbolos do alfabeto?" << endl;

	string simbolos[2]{};

	for (size_t i = 0; i < 2; i++)
	{
		cout << "Simbolo " << i + 1 << ": ";
		cin >> simbolos[i];
		cout << endl;
	}

	line('-',81);

	cout << "Entre com as transi��es de cada estado!" << endl;
	cout << "Para cada estado � perguntado, qual ser� o estado resultado da leitura do s�mbolo." << endl;
	cout << "Voc� precisa responder baseado na tabela de estados que voc� informou." << endl;
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
				cout << "Transi��o do estado " << estados[i].nome << " lendo " << simbolos[j] << ": ";
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
		cout << "Quais � o estado inicial? " << endl;
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
			cout << "Estado inexistente, tente novamente!";
			line();
		}

	} while (check1 == false);

	//////////////////////////////////////////////////////////////////////////////////////

	line();

	cout << "Agora informa quais estados s�o finais!\n" << endl;

	string final{};

	for (size_t i = 0; i < quantEst; i++)
	{
		check1 = false;
		cout << estados[i].nome << " � estado final? (true = sim | false = n�o): " << endl;
		cin >> final;

		std::transform(final.begin(), final.end(), final.begin(), [](unsigned char c) { return std::tolower(c); });

		if (final == "true") {
			estados[i].final = true;
		}
	}

	line('=', 82);

	cout << "Agora vamos testar com entradas seu aut�mato!" << endl;
	cout << "Case queira parar, digite \"0\" ZERO!\n" << endl;
	do
	{

	} while (true);

	return 0;
}

bool checkCadeia(Estado* estados [], char cadeia[]) {

	return false;
}

void line(char simbolo, int tam) {
	for (size_t i = 0; i < tam; i++)
	{
		cout << simbolo;
	}
	cout << "\n";
}