#pragma once
#include "pch.h"
#include "Object.h"
#include "Apartment.h"

// ������ �� ����� ������� � ���������
class Applying: public Object
{
	// ��� ������������ ������ ������
	static int seedId_;

protected:
	// ������������ ������
	int id_;

	// ��������� ��������
	Apartment exists_;

	// �������� ��������
	Apartment wanted_;

public:
	#pragma region ������������
	Applying();
	Applying(const Apartment &exists, const Apartment& wanted);
	#pragma endregion


	#pragma region ������� ����
	// Applying(const Applying &other) = default;
	// virtual ~Applying() override = default;
	// Applying &operator=(const Applying& other) = default;
	#pragma endregion
	

	#pragma region ���������
	// �������� ������������� ������
	int getId() const;

	// ��������� ��������
	Apartment getExists() const;
	void setExists(const Apartment &alue);

	// �������� ��������
	Apartment getWanted() const;
	void setWanted(const Apartment &value);
	#pragma endregion


	#pragma region ������ ������
	virtual string toString() override;
	virtual bool equals(const Object &other) override;

	// ��������� ������ � ������� CSV
	string toCsv();

	// �������� ������ �� ������ � ������� CSV
	void parseCsv(string& csv);


	// ����� ����� �������
	static string header();

	// ����� ������� �������
	static string footer();
	
	// ����� ������ �������
	string toTableRow();
	#pragma endregion


	// ������������� ��������
	friend ostream& operator<<(ostream& os, Applying & aplying);
};
