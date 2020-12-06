#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 
using namespace std;
enum Specialnist { KOMPUTERNI_NAUKY, INFORMATYKA, MATEMATYKA_TA_EKONOMIKA, PHISYKA_TA_INFORMATYKA, TRUDOVE_NAVCHANNYA };
string specialnistStr[] = { "КН", "інф", "мат&екон", "фіз&інф", "труд.навч" };
struct Student
{
	string prizv;
	unsigned kurs;
	Specialnist specialnist;
	unsigned phisyka;
	unsigned matematyka;
	union
	{
		unsigned programuvannia;
		unsigned chiselni_metody;
		unsigned pedagogika;
	};

};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int BinSearch(Student* p, const int N, const string prizv, const unsigned kurs, const unsigned phisyka);
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int N;
	cout << "Введіть N: "; cin >> N;
	Student* p = new Student[N];
	string prizv;
	unsigned kurs;
	unsigned phisyka;
	int found;
	Create(p, N);
	Print(p, N);
	Sort(p, N);
	cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
	cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
	cout << " прізвище: "; getline(cin, prizv);
	cout << endl;
	cout << "курс: "; cin >> kurs;
	cout << endl;
	cout << "оцінка з фізики: "; cin >> phisyka;
	if ((found = BinSearch(p, N, prizv, kurs, phisyka)) != -1)
		cout << "Знайдено студента в позиції " << found << endl;
	else
		cout << "Шуканого студента не знайдено" << endl;
	return 0;
}
void Create(Student* p, const int N)
{
	int specialnist;

	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();
		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " курс: "; cin >> p[i].kurs;
		cout << " спеціальність (0 - комп'ютерні науки, 1 - інформатика, 2 - математика та економіка, 3 - фізика та інформатика, 4 - трудове навчання):";
		cin >> specialnist;
		cout << " оцінка з фізики: "; cin >> p[i].phisyka;
		cout << "оцінка з математики: "; cin >> p[i].matematyka;
		p[i].specialnist = Specialnist(specialnist);
		switch (p[i].specialnist)
		{
		case KOMPUTERNI_NAUKY:
			cout << " оцінка з програмування : "; cin >> p[i].programuvannia;
			break;
		case INFORMATYKA:
			cout << "оцінка з чисельних методів: "; cin >> p[i].chiselni_metody;
			break;
		case MATEMATYKA_TA_EKONOMIKA:
		case PHISYKA_TA_INFORMATYKA:
		case TRUDOVE_NAVCHANNYA:
			cout << " оцінка з педагогігики : "; cin >> p[i].pedagogika;
			break;
		}
		cout << endl;
	}
}
void Print(Student* p, const int N)
{
	cout << "========================================================================================================"
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Програмування | Чис. методи | Педагогіка |"
		<< endl;
	cout << "--------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(10) << left << p[i].prizv
			<< "| " << setw(2) << right << p[i].kurs << " "
			<< "| " << setw(15) << left << specialnistStr[p[i].specialnist]
			<< "| " << setw(6) << right << p[i].phisyka << " "
			<< "| " << setw(10) << left << p[i].matematyka << " ";
		switch (p[i].specialnist)
		{
		case KOMPUTERNI_NAUKY:
			cout << "| " << setw(13) << right << p[i].programuvannia << " " << "|" << setw(14) << "|" << setw(13) << "|";
			break;
		case INFORMATYKA:
			cout << "|" << setw(16) << right << fixed << "|" << setw(13) << left << p[i].chiselni_metody << "|" << setw(11) << right << " " << " |";
			break;
		case MATEMATYKA_TA_EKONOMIKA:
		case PHISYKA_TA_INFORMATYKA:
		case TRUDOVE_NAVCHANNYA:
			cout << "|" << setw(17) << right << fixed << "| " << setw(12) << left << " " << "| " << setw(11) << right << p[i].pedagogika << "|";
			break;
		}
		cout << endl;
	}
	cout << "========================================================================================================"
		<< endl;
	cout << endl;
}
void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].phisyka > p[i1 + 1].phisyka)
				||
				(p[i1].phisyka == p[i1 + 1].phisyka &&
					p[i1].kurs > p[i1 + 1].kurs)
				||
				(p[i1].phisyka == p[i1 + 1].phisyka &&
					p[i1].kurs == p[i1 + 1].kurs &&
					p[i1].prizv < p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}
int BinSearch(Student* p, const int N, string prizv, unsigned kurs, unsigned phisyka)
{
	int L = 0, R = N - 1, i;
	do {
		i = (L + R) / 2;
		if (p[i].prizv == prizv && p[i].kurs == kurs && p[i].phisyka == phisyka)
			return i;
		if ((p[i].kurs < kurs)
			||
			(p[i].kurs == kurs &&
				p[i].prizv < prizv))
		{
			L = i + 1;
		}
		else
		{
			R = i - 1;
		}
	} while (L <= R);
	return -1;
}