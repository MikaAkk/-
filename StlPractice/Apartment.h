#pragma once
#include "pch.h"
#include "Object.h"

// Сведения о квартире содержат: 
//     • количество комнат
//     • площадь
//     • этаж
//     • район.
class Apartment: public Object
{
protected:
	// количество комнат
	int rooms_;

	// площадь
	double area_;

	// этаж
	int floor_;
	
	// район
	string district_;

public:
	#pragma region конструкторы
	Apartment();
	Apartment(int rooms, double area, int floor, const string &district);
	#pragma endregion

	// правило трех (модно и не задавать, но покажем, для демонстрации наших знаний)
	// Apartment(const Apartment& other) = default;
	// virtual ~Apartment() override = default;
	// Apartment& operator=(const Apartment& other) = default;
	
	#pragma region аксессоры
	// количество комнат
	int  getRooms() const;
	void setRooms(int value);

	// площадь
	double getArea() const;
	void   setArea(double value);

	// этаж
	int getFloor() const;
	void setFloor(int value);

	// район
	string getDistrict() const;
	void setDistrict(const string &value);
	#pragma endregion

	#pragma region методы класса
	virtual string toString() override;
	virtual bool equals(const Object &other) override;
	#pragma endregion

	// перегруженные операции
	friend ostream& operator<<(ostream &os, Apartment &other);
};
