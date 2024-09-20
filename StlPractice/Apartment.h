#pragma once
#include "pch.h"
#include "Object.h"

// �������� � �������� ��������: 
//     � ���������� ������
//     � �������
//     � ����
//     � �����.
class Apartment: public Object
{
protected:
	// ���������� ������
	int rooms_;

	// �������
	double area_;

	// ����
	int floor_;
	
	// �����
	string district_;

public:
	#pragma region ������������
	Apartment();
	Apartment(int rooms, double area, int floor, const string &district);
	#pragma endregion

	// ������� ���� (����� � �� ��������, �� �������, ��� ������������ ����� ������)
	// Apartment(const Apartment& other) = default;
	// virtual ~Apartment() override = default;
	// Apartment& operator=(const Apartment& other) = default;
	
	#pragma region ���������
	// ���������� ������
	int  getRooms() const;
	void setRooms(int value);

	// �������
	double getArea() const;
	void   setArea(double value);

	// ����
	int getFloor() const;
	void setFloor(int value);

	// �����
	string getDistrict() const;
	void setDistrict(const string &value);
	#pragma endregion

	#pragma region ������ ������
	virtual string toString() override;
	virtual bool equals(const Object &other) override;
	#pragma endregion

	// ������������� ��������
	friend ostream& operator<<(ostream &os, Apartment &other);
};
