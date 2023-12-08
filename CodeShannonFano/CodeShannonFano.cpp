#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <Windows.h>
using namespace std;

namespace CodeShannonFano {
	class CodeShannonFano {

	public:string NameFile;
	public:int CountLine = 0;
	public:CodeShannonFano(string nameFile) {
		this->NameFile = nameFile;

		string line;
		ifstream file(this->NameFile);
		if (file.is_open()) {
			while (getline(file, line)) {
				CountLine++;
			}
		}
	}

	public:vector<string> GenerationCode(int max) { //Генирируем коды для символов
		vector<string> res;
		res.push_back("0");

		for (int i = 1; i <= max; i++) {
			string a = res[i - 1];
			for (int c = 0; c < a.size(); c++) {
				if (a[c] == '0') {
					a[c] = '1';
					res.push_back(a);
					break;
				}

				if (c == a.size() - 1) {
					string r = "";
					for (int x = 0; x < a.size() + 1; x++) {
						r += "0";
					}
					res.push_back(r);
					break;
				}
			}
		}

		return res;
	}

	public:void Code(vector<vector<string>> resEnd) {//Кодируем информацию
		auto start = time(NULL);
		int summ = 0;
		int countLine = 0;
		string line;
		string l = "";
		string prLine = "=";
		vector<string> chars = resEnd[0];
		vector<string> countChars = resEnd[1];
		vector<string> code = resEnd[2];
		ifstream file;
		ofstream outFile;
		ofstream keyFile;

		file.open(this->NameFile);
		outFile.open("res.txt");
		keyFile.open("key.txt");
		if (file.is_open()) {
			while (getline(file, line)) {
				countLine++;
				transform(line.begin(), line.end(), line.begin(), tolower);
				for (char c : line) {
					for (int ch = 0; ch < chars.size(); ch++) {
						if (chars[ch] == string(1, c)) {
							l += code[ch] + "-";
							break;
						}
					}
				}
				l += "\n";

				int pr = (countLine * 100) / CountLine;
				if (pr % 10 == 0 and countLine % 10 == 0) {
					prLine += prLine[0];
				}

				string resLine = "";
				if (prLine.size() < 10) {
					for (int i = 0; i < 10; i++) {
						if (i > prLine.size()) {
							resLine.append(" ");
						}
						else {
							resLine.append(string(1, prLine[i]));
						}
					}
				}
				else {
					resLine = prLine;
				}

				if (pr % 10 == 5 or pr % 10 == 0) {
					system("cls");
					cout << "Процесс кодирования: [" + resLine + "]" + to_string(pr) + "%\n";
				}
			}
			outFile << l + "\n";
		}

		system("cls");
		cout << "- - - - - - - - Итого - - - - - - - - \n";
		line = "\n";
		for (int ind = 0; ind < chars.size(); ind++) {
			keyFile << chars[ind] + " " + countChars[ind] + " " + code[ind] + " \n";
			cout << +"[" + to_string(ind) + "] " + chars[ind] + " " + countChars[ind] + " " + code[ind] + " \n";
			summ += stoi(countChars[ind]);
		}
		cout << "\nВсего исмволов: " + to_string(summ);
		cout << "\nНа кодирование информации ушло: " + to_string(time(NULL) - start) + " сек.";

	}

	public:vector<vector<string>> CharCount() {//Считаем сколько и какие символы имееються в файле
		auto start = time(NULL);
		int summ = 0;
		int coutLine = 0;
		string line;
		string prLine = "=";
		ifstream file;
		vector<string> chars;
		vector<string> countChars;
		vector<vector<string>> resEnd;

		file.open(this->NameFile);
		if (file.is_open()) {
			while (getline(file, line)) {
				coutLine++;
				transform(line.begin(), line.end(), line.begin(), tolower);
				for (char ch : line) {
					if (chars.size() == 0) {
						chars.push_back(string(1, ch));
						countChars.push_back("1");
					}
					else {
						bool events = false;
						int indChars = 0;
						for (string c : chars) {
							if (c == string(1, ch)) {
								events = true;
								break;
							}
							indChars += 1;
						}

						if (events == false) {
							chars.push_back(string(1, ch));
							countChars.push_back("1");
						}
						else {
							countChars[indChars] = to_string(stoi(countChars[indChars]) + 1);
						}
					}
				}

				int pr = (coutLine * 100) / CountLine;
				if (pr % 10 == 0 and coutLine % 10 == 0) {
					prLine += prLine[0];
				}

				string resLine = "";
				if (prLine.size() < 10) {
					for (int i = 0; i < 10; i++) {
						if (i > prLine.size()) {
							resLine.append(" ");
						}
						else {
							resLine.append(string(1, prLine[i]));
						}
					}
				}
				else {
					resLine = prLine;
				}

				if (pr % 10 == 5 or pr % 10 == 0) {
					system("cls");
					cout << "Файл обработан на: [" + resLine + "]" + to_string(pr) + "%\n";
				}
			}
		}

		if (chars.size() != 0) {
			//Сортировка
			int n = 0;
			int indN = 0;
			int indI = 0;
			while (true) {
				string maxChars = chars[n];
				string chr = "";
				int maxNumber = stoi(countChars[n]);
				int number = 0;
				for (int i = n; i < countChars.size(); i++) {
					number = stoi(countChars[i]);
					chr = chars[i];
					if (maxNumber < number) {
						indN = n;
						indI = i;
						number = maxNumber;
						maxNumber = stoi(countChars[i]);
						chr = maxChars;
						maxChars = chars[i];

						countChars[indN] = to_string(maxNumber);
						countChars[indI] = to_string(number);
						chars[indN] = maxChars;
						chars[indI] = chr;
					}
				}

				n++;
				if (n == countChars.size() - 1) {
					break;
				}
			}

			vector<string> code = GenerationCode(chars.size());
			resEnd.push_back(chars);
			resEnd.push_back(countChars);
			resEnd.push_back(code);

		}
		else {
			cout << "Ошибка чтения из файла!!";
		}

		return resEnd;
	}

	};
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");
	system("cls");

	CodeShannonFano::CodeShannonFano asf = CodeShannonFano::CodeShannonFano("text.txt");
	vector<vector<string>> res = asf.CharCount();
	asf.Code(res);

}
