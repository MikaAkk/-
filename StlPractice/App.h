#pragma once
#include "pch.h"
#include "Applying.h"

class App
{
	#pragma region ��������������� ������ ��� ������� ������ 1
	void show(vector <double>& data, const string& title);
	void writeBin(vector <double>& data, const string& fileName);
	void readBin	(vector <double>& data, const string& fileName);
	#pragma endregion

	// ������ ������ ������
	list<Applying> data2_;  // ��������� ������� �� �����
	string fileName2_;      // ��� ����� ������

	#pragma region ��������������� ������ ��� ������� ������ 2
	// ��������� ��������� � ����� ������� CSV
	void saveCsv();

	// ��������� ��������� �� ����� � ������� CSV
	void loadCsv();

	// ����� �������� 
	void showAll(const string& title);

	// ����� ��������� ������ � ���������� ����� � ��������� ��� ���������� �������� ������
	void addCard(Applying applying);
	#pragma endregion

public:
	// ����������� �� ���������
	App():fileName2_("applyings.csv") { }

	// ������� ����
	App(const App &otgher) = default;
	~App() = default;
	App &operator=(const App &other) = default;

	// ������� ������� - ���������� ������ ����
	void doFirstCommand();
	void doSecondCommand();


	// ���������� ��������� (��������� ������) �� �����
	void initializeCards();

	// ����� ���� ���������
	void showCards();

	// ����� ���������, ������������� �� ���������� ������
	void orderByRoomsNumber();

	// ����� ���������, ������������� �� ������� (��� ��������� ��������
	void orderByDistrict();

	// ���������� �������� � ��������� (� �������� �������� ������)
	void addCardTest();

};

