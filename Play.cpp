#include <ctime>
#include <windows.h> // управление консолью
#include <array> // массивы
#include <random>
#include <iostream>
#include <algorithm> // Для find
#include <chrono> //для задержки по времени
#include <thread> //для задержки по времени (поток)
#include <fstream>
#include <vector>
#include <string>


using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

int money = 0;

string vopros[20]; 

string otvet[80];


string potveti[20];


string mainmenu[] = {
	 "Выберите действие: \n",
	"1. Прочитать правила игры \n",
	"2. Начать игру \n",
	"3. Посмотреть заставку ещё раз \n" ,
	"4. Закончить и забрать итоговый выигрыш \n" ,
	"________________________________\n"

};

string gamemenu[] = {
	 "Выберите тему: \n",
	"1. Школьные вопросы \n",
	"2. Наука и технологии \n",
	"3. Видеоигры \n",
	"4. Спорт \n",
	"5. Вернуться в главное меню \n" ,
	"________________________________\n"

};


string op;
string potvet;


int menu(string mm[], int size, int punkt) {
	
	
	int vibor = 0;  //то, что человек выбрал
	bool da = true;
	do {
		system("cls");
		da = false;
		for (int i = 0; i <= size - 1; i++) {
			cout << mm[i];
		}
		cin >> vibor;

		if (cin.fail()) {
			cin.clear(); //очистить состояние ошибки
			cin.ignore();
			cin.get();
			cout << "Вы ввели не число, нажмите ENTER для продолжения";
			da = true;
			cin.get();


		}
		else {
			if (vibor > 0 && vibor <= punkt) {
				da = false;
			}
			else {
				cout << "Ошибка! Число не входит в диапазон";
				da = true;
				cin.get();
				cin.get();

			}

		}

	} while (da);
	return vibor;
}

void zastavka() {
	vector<string> bigM = {
		"##             ##",
		"###           ###",
		"####         ####",
		"## ##       ## ##",
		"##  ##     ##  ##",
		"##   ##   ##   ##",
		"##    ## ##    ##",
		"##     ###     ##",
		"##      #      ##",
		"##             ##",
		"##             ##",
		"##             ##"
	};

	string welcomeText = "Добро пожаловать в игру!";
	string promptText = "Нажмите клавишу ENTER, чтобы продолжить";

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	// размер консоли (ширина и высота)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);
	int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	int bigM_width = (int)bigM[0].size();
	int bigM_height = (int)bigM.size();

	//для большого М по центру
	int startX = (consoleWidth - bigM_width) / 2;
	int startY = (consoleHeight - bigM_height) / 2;

	//для приветствия
	int welcomeX = (consoleWidth - (int)welcomeText.length()) / 2;
	int welcomeY = startY - 2;

	//для подсказки 
	int promptX = (consoleWidth - (int)promptText.length()) / 2;
	int promptY = startY + bigM_height + 1; // под буквой "M"

	//для цветной анимации 
	vector<int> colors = {
		FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		FOREGROUND_RED | FOREGROUND_INTENSITY,
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, 
		FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, 
		FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,  
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY 
	};
	int num_colors = (int)colors.size();

	system("cls");
	COORD welcomePos = { (SHORT)welcomeX, (SHORT)welcomeY };
	SetConsoleCursorPosition(console, welcomePos);
	SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << welcomeText;
	
	for (int col = 0; col < bigM_width; ++col) {
		for (int row = 0; row < bigM_height; ++row) {
			if (bigM[row][col] == '#') {
				COORD pos = { (SHORT)(startX + col), (SHORT)(startY + row) };
				SetConsoleCursorPosition(console, pos);
				int colorIndex = (col + row) % num_colors;
				SetConsoleTextAttribute(console, colors[colorIndex]);
				cout << '#';
				this_thread::sleep_for(chrono::milliseconds(25));
			}
			else {
				COORD pos = { (SHORT)(startX + col), (SHORT)(startY + row) };
				SetConsoleCursorPosition(console, pos);
				cout << ' ';
			}
		}
	}

	COORD promptPos = { (SHORT)promptX, (SHORT)promptY };
	SetConsoleCursorPosition(console, promptPos);
	SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << promptText;
	//сброс цвета и ожидание нажатия клавиши
	SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cin.get();

	system("cls");
}

void pravila() {
	system("cls");
	cout << "Правила: \n";
	cout << "=======================================" << endl;
	cout << "-----Игра “Кто хочет стать миллионером?” - это конкурс викторина, в которой нужно правильно ответить на ряд вопросов с несколькими вариантами ответов. Всего 10 вопросов, каждый вопрос стоит 100 игровых монет. \n";
	cout << "" << endl;
	cout << "-----Вопросы “Кто хочет стать миллионером?” структурированы в соответствии с четырьмя различными категориями, такими как “Школьные вопросы”, “Наука и технологии”, “Видеоигры”, “Спорт”. \n";
	cout << "" << endl;
	cout << "-----При ответах на вопросы запрещено пользоваться подсказками, неважно в каком они виде.\n";
	cout << "" << endl;
	cout << "-----Удачной игры!\n";
	cin.get();
	cin.get();
}

void game() {

	int nzv[10] = {100,100,100,100,100,100,100,100,100,100};
	int x;

	while (true) {
		int n = menu(gamemenu, 7, 5);
		string question, o, po;


		if (n == 1) {
			question = "School_questions.txt";
			o = "School_answers-.txt";
			po = "School_answers+.txt";
		}

		if (n == 2) {
			question = "Science_questions.txt"; 
			o = "Science_answers-.txt";
			po = "Science_answers+.txt";
		}

		if (n == 3) {
			question = "VideoGames_questions.txt";  
			o = "VideoGames_answers-.txt";
			po = "VideoGames_answers+.txt";
		}

		if (n == 4) {
			question = "Sport_questions.txt";  
			o = "Sport_answers-.txt";
			po = "Sport_answers+.txt";
		}

		if (n == 5) {
			break;
		}

		//чтение вопросов
			ifstream inputFile(question);
			if (!inputFile.is_open()) {
				cerr << "Ошибка открытия файла!" << endl;}

			int i = 0;
			while (getline(inputFile, vopros[i]) && i < 21) { 
				i++;}


			if (!inputFile.eof() && i == 20) {
				cerr << "Предупреждение: В файле больше элементов, чем размер массива." << endl;}
			inputFile.close();


			//чтение ответов 80
			ifstream inputFile1(o);
			if (!inputFile1.is_open()) {
				cerr << "Ошибка открытия файла!" << endl;
			}

			i = 0;
			while (getline(inputFile1, otvet[i]) && i < 81) { 

				i++;
			}

			if (!inputFile1.eof() && i == 80) {
				cerr << "Предупреждение: В файле больше элементов, чем размер массива." << endl;
			}
			inputFile1.close();
			
			
			////чтение ответов 20
			ifstream inputFile2(po);
			if (!inputFile2.is_open()) {
				cerr << "Ошибка открытия файла!" << endl;
			}

			i = 0;
			while (getline(inputFile2, potveti[i]) && i < 21) { 
				i++;
			}
		if (!inputFile2.eof() && i == 20) {
				cerr << "Предупреждение: В файле больше элементов, чем размер массива." << endl;
			}
			inputFile2.close();
		
		
		for (int i = 1; i <= 10; i++) {
			system("cls");
			cout << "=======================================" << endl;
			cout << "Вопрос: " << i << endl;
			cout << "=======================================" << endl;
	
			int start = 0;
			int end = 19;
			
			int* da = nullptr;

			do {
				x = rand() % (end - start + 1) + start; //cлучайный номер вопроса
				da = find(nzv, nzv + 10, x);
			} while (da != (nzv + 10));
			nzv[i - 1] = x;


			cout << vopros[x] << endl;//вопрос под номером x
			potvet = potveti[x]; //правильный ответ

			string bukvapotvet = ""; //буква правильного ответа
			if (potvet == otvet[4 * x]) bukvapotvet = "A";
			if (potvet == otvet[4 * x + 1]) bukvapotvet = "C";
			if (potvet == otvet[4 * x + 2]) bukvapotvet = "B";
			if (potvet == otvet[4 * x + 3]) bukvapotvet = "D";


			cout << "A.   " << otvet[4 * x] << "\tC.   " << otvet[4 * x + 1] << endl;
			cout << "B.   " << otvet[4 * x + 2] << "\tD.   " << otvet[4 * x + 3] << endl;

			cout << "Укажите букву, соответствующую правильному ответу: ";

			cin >> op;
			if (op == bukvapotvet) {
				cout << "Правильно" << endl;
				money = money + 100;
				cout << "Ваш баланс: " << money << endl;
			}
			else {
				cout << "Неправильно, правильный ответ: " << potvet << endl;
				money = 0;
				cout << "Ваш баланс: " << money << endl;
			}
			
			cin.get();
			cin.get();
		}
		system("cls");
		cout << "=======================================" << endl;
		cout << "Ваш баланс после раунда: " << money << endl;
		cout << "=======================================" << endl;
		cin.get();
	}
}

int main()
{	
	system("chcp 1251");
	setlocale(LC_ALL, "RU");
	srand(time(0));
	zastavka();
	while (true){
		int n = menu(mainmenu, 6, 4);
		if (n == 1) pravila();
		if (n == 2) game();
		if (n == 3) zastavka();
		if (n == 4) {
			cin.get();
			cout << "=======================================" << endl;
			cout << "Итоговая сумма выигрыша: " << money << endl;
			cout << "=======================================" << endl;
			cin.get();
			
		}

	};
}