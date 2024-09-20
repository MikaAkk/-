#pragma once
#include "pch.h"
#include "Object.h"
#include "Apartment.h"

// Заявка на обмен квартир в картотеке
class Applying: public Object
{
	// для формирования номера заявки
	static int seedId_;

protected:
	// идентфикатор заявки
	int id_;

	// имеющаяся квартира
	Apartment exists_;

	// желаемая квартира
	Apartment wanted_;

public:
	#pragma region конструкторы
	Applying();
	Applying(const Apartment &exists, const Apartment& wanted);
	#pragma endregion


	#pragma region правило трех
	// Applying(const Applying &other) = default;
	// virtual ~Applying() override = default;
	// Applying &operator=(const Applying& other) = default;
	#pragma endregion
	

	#pragma region аксессоры
	// получить идентификатор заявки
	int getId() const;

	// имеющаяся квартира
	Apartment getExists() const;
	void setExists(const Apartment &alue);

	// желаемая квартира
	Apartment getWanted() const;
	void setWanted(const Apartment &value);
	#pragma endregion


	#pragma region методы класса
	virtual string toString() override;
	virtual bool equals(const Object &other) override;

	// формирует строку в формате CSV
	string toCsv();

	// получает данные из строки в формате CSV
	void parseCsv(string& csv);


	// вывод шапки таблицы
	static string header();

	// вывод подвала таблицы
	static string footer();
	
	// вывод строки таблицы
	string toTableRow();
	#pragma endregion


	// перегруженные операции
	friend ostream& operator<<(ostream& os, Applying & aplying);
};
