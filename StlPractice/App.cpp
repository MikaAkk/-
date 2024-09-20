#include "pch.h"
#include "App.h"

#include "Utils.h"

/*
 * Задача 1.
 * В векторе, состоящем из п вещественных элементов, вычислить (сохранить
 * вектор в бинарном файле до обработки, восстановить после всех обработок):
 *    1) минимальный элемент;
 *    2) сумму элементов, расположенных после минимального;
 *    3) преобразовать вектор таким образом, чтобы сначала располагались все
 *       элементы, равные нулю, а потом — все остальные
 */
void App::doFirstCommand()
{
	showNavBarMessage(hintColor, "  Обработка вектора по заданию");

	// формирование вектора из n элементов, сохранение вектора в бинарном файле
	int n = getRand(12, 25);
	vector<double> data(n);

	constexpr double lo = -20, hi = 42;
	generate(data.begin(), data.end(), []() {
		// генерация элементов с получением нуля
		double t = getRand(lo, hi);
		return abs(t) < 10.?0.:t;
	});
	auto fileName = "vector.dat"s;
	writeBin(data, fileName);

	// вывод вектора
	show(data, "\n\n\n\n\tИсходный вектор, выполнено сохранение в бинарный файл \"" + fileName + "\"");

	// минимальный элемент
	// ищем итератор на минимальный элемент
	auto it_min = min_element(data.begin(), data.end());
	double min = *it_min;

	// вычисляем сумму элементов, расположенных после минимального
	double sum = accumulate(++it_min, data.end(), 0., [](double acc, double datum) {
		return acc + datum;
	});

	cout<< "\tПервый минимальный элемент                :       " << color(headerColor) << setw(10) << min << color(mainColor) << "\n"
		<< "\tСумма элементов после первого минимального:       " << color(headerColor) << setw(10) << sum << color(mainColor) << endlm(3);


	// преобразовать вектор таким образом, чтобы сначала располагались все
	// элементы, равные нулю, а потом — все остальные
	sort(data.begin(), data.end(), [](double d1, double d2) {
		return eq(d1, 0.) and !eq(d2, 0.);
	});
	show(data, "\tВектор упорядочен по правилу \"Нули в начало вектора");


	// восставновление вектрра из бинарного файла
	readBin(data, fileName);
	show(data, "\tВектор восстановлен из файла \"" + fileName + "\"");
} // App::doFirstCommand


// Пример выполнения команды меню
void App::doSecondCommand()
{
	showNavBarMessage(hintColor, "  Выполнение вторвой команды меню");

	cout << endlm(4) << "\t" << color(headerColor) << "Вторая команда меню выполнена :)" << color(mainColor) << endlm(5);
} // App::doSecondCommand


// Выволд вектра в стиле C++
void App::show(vector <double>& data, const string& title) 
{
	cout << title << ":\n\t";
	int counterOut = 0;
	constexpr int m = 10;

	// замыкание &counterOut по ссылке дает возмодность менять переменную в лямбда-выражении
	auto outDatum = [&counterOut](double item) {
		cout << color(item < 0 ? arrColor : headerColor) << setw(10) << item << color(mainColor);
		if (++counterOut % m == 0) cout << "\n\t";
	};
	for_each(data.begin(), data.end(), outDatum);
	cout << "\n\n";
} // App::show


// запись вектора в бинарный поток вывода
void App::writeBin(vector <double>& data, const string& fileName)
{
	// открыть бинарный поток для вывода
	ofstream ofs(fileName, ios::binary | ios::trunc);
	if (!ofs.is_open()) {
		throw exception(("Не могу открыть бинарный поток для записи вектора в файл "s + fileName).c_str());
	} // if

	// вывод записей в поток при помощи итератора
	for (auto datum : data) {
		// собственно запись
		ofs.write((char*)&datum, sizeof(datum));
	} // for 

	// закрыть поток вывода
	ofs.close();
} // App::writeBin


// чтение из бинарного файла при помощи потока ввода в вектор
void App::readBin(vector <double>& data, const string& fileName)
{
	// открытие бинарного потока ввода для чтения
	ifstream ifs(fileName, ios::binary);
	if (!ifs.is_open()) {
		throw exception(("Не могу открыть бинарный поток для чтения из файла "s + fileName).c_str());
	} // if

	// чистим список для прочитанных данных
	data.clear();

	// чтение данных
	while (!ifs.eof()) {
		double temp;
		ifs.read((char*)&temp, sizeof(temp));

		data.emplace_back(temp);
		ifs.peek();
	} // while

	// закрыть поток чтения, вернуть прочитанные данные
	ifs.close();
} // App::readBin


#pragma region Задача 2

// сохранить картотеку в файле формата CSV
void App::saveCsv()
{
	// открыть поток для вывода
	ofstream ofs(fileName2_, ios::trunc);
	if (!ofs.is_open()) {
		throw exception(("Не могу открыть поток для записи картотеки в файл \""s + fileName2_ + "\""s).c_str());
	} // if

	// вывод записей в поток при помощи итератора
	for (auto datum : data2_) {
		// собственно запись
		ofs << datum.toCsv() << endl;
	} // for 

	// закрыть поток вывода
	ofs.close();
} // App::saveCsv


// загрузить картотеку из файла в формате CSV
void App::loadCsv()
{
	// открытие потока ввода для чтения
	ifstream ifs(fileName2_);
	if (!ifs.is_open()) {
		throw exception(("Не могу открыть поток для чтения из файла \""s + fileName2_ + "\""s).c_str());
	} // if

	// чистим список для прочитанных данных
	data2_.clear();

	// чтение данных
	while (!ifs.eof()) {
		Applying applying;
		string str;

		getline(ifs, str);
		applying.parseCsv(str);
		data2_.push_back(applying);
		ifs.peek();
	} // while

	// закрыть поток чтения, вернуть прочитанные данные
	ifs.close();
} // App::loadCsv


// вывод всей картотеки
void App::showAll(const string& title)
{
	cout << title << endl << Applying::header() << endl;

	for_each(data2_.begin(), data2_.end(), [](Applying applying)
		{
			cout << applying.toTableRow() << endl;
		});

	cout << Applying::footer() << endl;
} // App::showAll


// поиск вариантов обмена и добавление карты в картотеку при отсуттсвии варианта обмена
void App::addCard(Applying applying) 
{
	// для гарантированного поиска в исходном порядке карточек 
	// загружаем картотеку из файла
	loadCsv();

	// поиск карточики для удаления карточки из картотеки если
	// вариант обмена подходит
	// remove_if() возвращает итератор
	auto it = remove_if(data2_.begin(), data2_.end(), [applying](Applying app1) {
		return app1.equals(applying);
	});
	
	if (it == data2_.end()) {
		// вариант обмена не найден
		data2_.push_back(applying);
	} else {
		// вариант обмена найден, не добавляем новую карточку
		// в картотеку, удаляем карточку с вариантом из картотеки
		data2_.erase(it);
	} // if

	// сохранить картотеку в файле
	saveCsv();
} // App::addCard


// Заполнение картотеки (коллекции заявок) на обмен
void App::initializeCards() 
{
	showNavBarMessage(hintColor, "  Заполнение картотеки (коллекции заявок) на обмен");

	// чистим список
	data2_.clear();

	data2_ = {
		// существующая квартира, желаемая квартира
		Applying(Apartment(3, 120., 4, "Киевский"),     Apartment(2,  60., 5, "Киевский")),
		Applying(Apartment(4, 150., 4, "Киевский"),     Apartment(4, 120., 6, "Кировский")),
		Applying(Apartment(1,  40., 9, "Киевский"),     Apartment(2,  60., 9, "Петровский")),
		Applying(Apartment(1,  40., 3, "Киевский"),     Apartment(1,  60., 5, "Куйбышевский")),
		Applying(Apartment(2,  50., 8, "Куйбышевский"), Apartment(3, 100., 5, "Куйбышевский")),
		Applying(Apartment(2,  50., 3, "Петровский"),   Apartment(2,  50., 5, "Куйбышевский")),
		Applying(Apartment(3,  90., 8, "Петровский"),   Apartment(2,  50., 3, "Куйбышевский")),
		Applying(Apartment(1,  30., 5, "Буденновский"), Apartment(2,  50., 9, "Петровский")),
		Applying(Apartment(4, 150., 5, "Буденновский"), Apartment(4, 150., 9, "Ворошиловский")),
		Applying(Apartment(1,  30., 2, "Пролетарский"), Apartment(1,  30., 3, "Буденновский")),
	};
	saveCsv();

	showAll("\n\n\n\n\tСписок карточек сформирован, записан в файл \"" + fileName2_ + "\":");
	cout << endlm(5);
} // App::initializeCards


// Вывод всей картотеки
void App::showCards()
{
	showNavBarMessage(hintColor, "  Вывод карточек картотеки");

	// загрузить картотееу из файла
	loadCsv();

	// показать картотеку
	showAll("\n\n\n\n\tКартотека обменного фонда (все карточки):");
	cout << endlm(5);
} // App::showCards


// Вывод картотеки, упорядоченной по количеству комнат
void App::orderByRoomsNumber()
{
	showNavBarMessage(hintColor, "  Вывод картотеки, упорядоченной по количеству комнат");

	data2_.sort([](Applying a1, Applying a2){
		return a1.getExists().getRooms() < a2.getExists().getRooms();
	});
	showAll("\n\n\n\n\tКартотека, упорядоченная по количеству комнат в имеющихся квартирах:");
	cout << endlm(5);
} // App::orderByRoomsNumber


// Вывод картотеки, упорядоченной по районам (для имеющейся квартиры
void App::orderByDistrict()
{
	showNavBarMessage(hintColor, "  Вывод картотеки, упорядоченной по районам (для имеющейся квартиры");

	data2_.sort([](Applying a1, Applying a2) {
		return a1.getExists().getDistrict() < a2.getExists().getDistrict();
	});
	showAll("\n\n\n\n\tКартотека, упорядоченная по району в имеющихся квартирах:");
	cout << endlm(5);
} // App::orderByDistrict


// Добавление карточки в картотеку (с подбором варианта обмена)
void App::addCardTest()
{
	showNavBarMessage(hintColor, "  Добавление карточки в картотеку (с подбором варианта обмена)");

	// новая карточка - должна быть добавлена в картотеку
	Applying applying1(Apartment(14, 1500., 5, "Буденновский"), Apartment(14, 1500., 9, "Ворошиловский"));
	addCard(applying1);
	showAll("\n\n\n\n\tВариантов обмена нет, карточка дорбавлена в картотеку:");

	// новая карточка - должна быть найден вариант обмена, карточка не должна быть добавлена в картотеку
	Applying applying2(Apartment(1, 60., 5, "Куйбышевский"), Apartment(1, 40., 3, "Киевский"));
	addCard(applying2);
	showAll("\n\tВариант обмена есть, карточка НЕ добавлена в картотеку, удалена карточка с вариантом обмена:");
	cout << endl;
} // App::addCardTest

#pragma endregion
