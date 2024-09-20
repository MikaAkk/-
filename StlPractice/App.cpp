#include "pch.h"
#include "App.h"

#include "Utils.h"

/*
 * ������ 1.
 * � �������, ��������� �� � ������������ ���������, ��������� (���������
 * ������ � �������� ����� �� ���������, ������������ ����� ���� ���������):
 *    1) ����������� �������;
 *    2) ����� ���������, ������������� ����� ������������;
 *    3) ������������� ������ ����� �������, ����� ������� ������������� ���
 *       ��������, ������ ����, � ����� � ��� ���������
 */
void App::doFirstCommand()
{
	showNavBarMessage(hintColor, "  ��������� ������� �� �������");

	// ������������ ������� �� n ���������, ���������� ������� � �������� �����
	int n = getRand(12, 25);
	vector<double> data(n);

	constexpr double lo = -20, hi = 42;
	generate(data.begin(), data.end(), []() {
		// ��������� ��������� � ���������� ����
		double t = getRand(lo, hi);
		return abs(t) < 10.?0.:t;
	});
	auto fileName = "vector.dat"s;
	writeBin(data, fileName);

	// ����� �������
	show(data, "\n\n\n\n\t�������� ������, ��������� ���������� � �������� ���� \"" + fileName + "\"");

	// ����������� �������
	// ���� �������� �� ����������� �������
	auto it_min = min_element(data.begin(), data.end());
	double min = *it_min;

	// ��������� ����� ���������, ������������� ����� ������������
	double sum = accumulate(++it_min, data.end(), 0., [](double acc, double datum) {
		return acc + datum;
	});

	cout<< "\t������ ����������� �������                :       " << color(headerColor) << setw(10) << min << color(mainColor) << "\n"
		<< "\t����� ��������� ����� ������� ������������:       " << color(headerColor) << setw(10) << sum << color(mainColor) << endlm(3);


	// ������������� ������ ����� �������, ����� ������� ������������� ���
	// ��������, ������ ����, � ����� � ��� ���������
	sort(data.begin(), data.end(), [](double d1, double d2) {
		return eq(d1, 0.) and !eq(d2, 0.);
	});
	show(data, "\t������ ���������� �� ������� \"���� � ������ �������");


	// ��������������� ������� �� ��������� �����
	readBin(data, fileName);
	show(data, "\t������ ������������ �� ����� \"" + fileName + "\"");
} // App::doFirstCommand


// ������ ���������� ������� ����
void App::doSecondCommand()
{
	showNavBarMessage(hintColor, "  ���������� ������� ������� ����");

	cout << endlm(4) << "\t" << color(headerColor) << "������ ������� ���� ��������� :)" << color(mainColor) << endlm(5);
} // App::doSecondCommand


// ������ ������ � ����� C++
void App::show(vector <double>& data, const string& title) 
{
	cout << title << ":\n\t";
	int counterOut = 0;
	constexpr int m = 10;

	// ��������� &counterOut �� ������ ���� ����������� ������ ���������� � ������-���������
	auto outDatum = [&counterOut](double item) {
		cout << color(item < 0 ? arrColor : headerColor) << setw(10) << item << color(mainColor);
		if (++counterOut % m == 0) cout << "\n\t";
	};
	for_each(data.begin(), data.end(), outDatum);
	cout << "\n\n";
} // App::show


// ������ ������� � �������� ����� ������
void App::writeBin(vector <double>& data, const string& fileName)
{
	// ������� �������� ����� ��� ������
	ofstream ofs(fileName, ios::binary | ios::trunc);
	if (!ofs.is_open()) {
		throw exception(("�� ���� ������� �������� ����� ��� ������ ������� � ���� "s + fileName).c_str());
	} // if

	// ����� ������� � ����� ��� ������ ���������
	for (auto datum : data) {
		// ���������� ������
		ofs.write((char*)&datum, sizeof(datum));
	} // for 

	// ������� ����� ������
	ofs.close();
} // App::writeBin


// ������ �� ��������� ����� ��� ������ ������ ����� � ������
void App::readBin(vector <double>& data, const string& fileName)
{
	// �������� ��������� ������ ����� ��� ������
	ifstream ifs(fileName, ios::binary);
	if (!ifs.is_open()) {
		throw exception(("�� ���� ������� �������� ����� ��� ������ �� ����� "s + fileName).c_str());
	} // if

	// ������ ������ ��� ����������� ������
	data.clear();

	// ������ ������
	while (!ifs.eof()) {
		double temp;
		ifs.read((char*)&temp, sizeof(temp));

		data.emplace_back(temp);
		ifs.peek();
	} // while

	// ������� ����� ������, ������� ����������� ������
	ifs.close();
} // App::readBin


#pragma region ������ 2

// ��������� ��������� � ����� ������� CSV
void App::saveCsv()
{
	// ������� ����� ��� ������
	ofstream ofs(fileName2_, ios::trunc);
	if (!ofs.is_open()) {
		throw exception(("�� ���� ������� ����� ��� ������ ��������� � ���� \""s + fileName2_ + "\""s).c_str());
	} // if

	// ����� ������� � ����� ��� ������ ���������
	for (auto datum : data2_) {
		// ���������� ������
		ofs << datum.toCsv() << endl;
	} // for 

	// ������� ����� ������
	ofs.close();
} // App::saveCsv


// ��������� ��������� �� ����� � ������� CSV
void App::loadCsv()
{
	// �������� ������ ����� ��� ������
	ifstream ifs(fileName2_);
	if (!ifs.is_open()) {
		throw exception(("�� ���� ������� ����� ��� ������ �� ����� \""s + fileName2_ + "\""s).c_str());
	} // if

	// ������ ������ ��� ����������� ������
	data2_.clear();

	// ������ ������
	while (!ifs.eof()) {
		Applying applying;
		string str;

		getline(ifs, str);
		applying.parseCsv(str);
		data2_.push_back(applying);
		ifs.peek();
	} // while

	// ������� ����� ������, ������� ����������� ������
	ifs.close();
} // App::loadCsv


// ����� ���� ���������
void App::showAll(const string& title)
{
	cout << title << endl << Applying::header() << endl;

	for_each(data2_.begin(), data2_.end(), [](Applying applying)
		{
			cout << applying.toTableRow() << endl;
		});

	cout << Applying::footer() << endl;
} // App::showAll


// ����� ��������� ������ � ���������� ����� � ��������� ��� ���������� �������� ������
void App::addCard(Applying applying) 
{
	// ��� ���������������� ������ � �������� ������� �������� 
	// ��������� ��������� �� �����
	loadCsv();

	// ����� ��������� ��� �������� �������� �� ��������� ����
	// ������� ������ ��������
	// remove_if() ���������� ��������
	auto it = remove_if(data2_.begin(), data2_.end(), [applying](Applying app1) {
		return app1.equals(applying);
	});
	
	if (it == data2_.end()) {
		// ������� ������ �� ������
		data2_.push_back(applying);
	} else {
		// ������� ������ ������, �� ��������� ����� ��������
		// � ���������, ������� �������� � ��������� �� ���������
		data2_.erase(it);
	} // if

	// ��������� ��������� � �����
	saveCsv();
} // App::addCard


// ���������� ��������� (��������� ������) �� �����
void App::initializeCards() 
{
	showNavBarMessage(hintColor, "  ���������� ��������� (��������� ������) �� �����");

	// ������ ������
	data2_.clear();

	data2_ = {
		// ������������ ��������, �������� ��������
		Applying(Apartment(3, 120., 4, "��������"),     Apartment(2,  60., 5, "��������")),
		Applying(Apartment(4, 150., 4, "��������"),     Apartment(4, 120., 6, "���������")),
		Applying(Apartment(1,  40., 9, "��������"),     Apartment(2,  60., 9, "����������")),
		Applying(Apartment(1,  40., 3, "��������"),     Apartment(1,  60., 5, "������������")),
		Applying(Apartment(2,  50., 8, "������������"), Apartment(3, 100., 5, "������������")),
		Applying(Apartment(2,  50., 3, "����������"),   Apartment(2,  50., 5, "������������")),
		Applying(Apartment(3,  90., 8, "����������"),   Apartment(2,  50., 3, "������������")),
		Applying(Apartment(1,  30., 5, "������������"), Apartment(2,  50., 9, "����������")),
		Applying(Apartment(4, 150., 5, "������������"), Apartment(4, 150., 9, "�������������")),
		Applying(Apartment(1,  30., 2, "������������"), Apartment(1,  30., 3, "������������")),
	};
	saveCsv();

	showAll("\n\n\n\n\t������ �������� �����������, ������� � ���� \"" + fileName2_ + "\":");
	cout << endlm(5);
} // App::initializeCards


// ����� ���� ���������
void App::showCards()
{
	showNavBarMessage(hintColor, "  ����� �������� ���������");

	// ��������� ��������� �� �����
	loadCsv();

	// �������� ���������
	showAll("\n\n\n\n\t��������� ��������� ����� (��� ��������):");
	cout << endlm(5);
} // App::showCards


// ����� ���������, ������������� �� ���������� ������
void App::orderByRoomsNumber()
{
	showNavBarMessage(hintColor, "  ����� ���������, ������������� �� ���������� ������");

	data2_.sort([](Applying a1, Applying a2){
		return a1.getExists().getRooms() < a2.getExists().getRooms();
	});
	showAll("\n\n\n\n\t���������, ������������� �� ���������� ������ � ��������� ���������:");
	cout << endlm(5);
} // App::orderByRoomsNumber


// ����� ���������, ������������� �� ������� (��� ��������� ��������
void App::orderByDistrict()
{
	showNavBarMessage(hintColor, "  ����� ���������, ������������� �� ������� (��� ��������� ��������");

	data2_.sort([](Applying a1, Applying a2) {
		return a1.getExists().getDistrict() < a2.getExists().getDistrict();
	});
	showAll("\n\n\n\n\t���������, ������������� �� ������ � ��������� ���������:");
	cout << endlm(5);
} // App::orderByDistrict


// ���������� �������� � ��������� (� �������� �������� ������)
void App::addCardTest()
{
	showNavBarMessage(hintColor, "  ���������� �������� � ��������� (� �������� �������� ������)");

	// ����� �������� - ������ ���� ��������� � ���������
	Applying applying1(Apartment(14, 1500., 5, "������������"), Apartment(14, 1500., 9, "�������������"));
	addCard(applying1);
	showAll("\n\n\n\n\t��������� ������ ���, �������� ���������� � ���������:");

	// ����� �������� - ������ ���� ������ ������� ������, �������� �� ������ ���� ��������� � ���������
	Applying applying2(Apartment(1, 60., 5, "������������"), Apartment(1, 40., 3, "��������"));
	addCard(applying2);
	showAll("\n\t������� ������ ����, �������� �� ��������� � ���������, ������� �������� � ��������� ������:");
	cout << endl;
} // App::addCardTest

#pragma endregion
