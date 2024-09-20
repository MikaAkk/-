#pragma once
#include "pch.h"
#include "Applying.h"

class App
{
	#pragma region вспомогательные методы для решения задачи 1
	void show(vector <double>& data, const string& title);
	void writeBin(vector <double>& data, const string& fileName);
	void readBin	(vector <double>& data, const string& fileName);
	#pragma endregion

	// данные второй задачи
	list<Applying> data2_;  // картотека квартир на обмен
	string fileName2_;      // имя файла данных

	#pragma region вспомогательные методы для решения задачи 2
	// сохранить картотеку в файле формата CSV
	void saveCsv();

	// загрузить картотеку из файла в формате CSV
	void loadCsv();

	// вывод карточек 
	void showAll(const string& title);

	// поиск вариантов обмена и добавление карты в картотеку при отсуттсвии варианта обмена
	void addCard(Applying applying);
	#pragma endregion

public:
	// конструктор по умолчанию
	App():fileName2_("applyings.csv") { }

	// правило трех
	App(const App &otgher) = default;
	~App() = default;
	App &operator=(const App &other) = default;

	// примеры методов - реализаций команж меню
	void doFirstCommand();
	void doSecondCommand();


	// заполнение картотеки (коллекции заявок) на обмен
	void initializeCards();

	// Вывод всей картотеки
	void showCards();

	// Вывод картотеки, упорядоченной по количеству комнат
	void orderByRoomsNumber();

	// Вывод картотеки, упорядоченной по районам (для имеющейся квартиры
	void orderByDistrict();

	// Добавление карточки в картотеку (с подбором варианта обмена)
	void addCardTest();

};

