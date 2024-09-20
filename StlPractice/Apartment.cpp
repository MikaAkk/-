#include "pch.h"
#include "Apartment.h"

#pragma region конструкторы
Apartment::Apartment() :Apartment(3, 120., 3, "Пролетарский") {}

Apartment::Apartment(int rooms, double area, int floor, const string& district)
{
	setRooms(rooms);
	setArea(area);
	setFloor(floor);
	setDistrict(district);
} // Apartment::Apartment
#pragma endregion


#pragma region аксессоры
// количество комнат
int  Apartment::getRooms() const { return rooms_; }
void Apartment::setRooms(int value)
{
	rooms_ = (value <= 0 || value > 36) 
		? throw exception("Apartment: недопустимое количество комнат")
		: value;
}  // Apartment::setRooms

// площадь
double Apartment::getArea() const { return area_; }
void   Apartment::setArea(double value)
{
	area_ = (value <= 0 || value > 3600)
		? throw exception("Apartment: нереальная площадь квартиры")
		: value;;
}

// этаж
int  Apartment::getFloor() const { return floor_; }
void Apartment::setFloor(int value)
{
	floor_ = (value <= 0 || value > 366)
		? throw exception("Apartment: недопустимое количество этажей")
		: value;
}

// район
string Apartment::getDistrict() const { return district_; }
void Apartment::setDistrict(const string& value)
{
	district_ =  value.empty()
		? throw exception("Apartment: недопустимое название района")
		: value;
}

#pragma endregion
string Apartment::toString()
{
	ostringstream oss;
	oss << "Apartment {комнат " << rooms_ << ", площадь " << area_ << " м2, этаж " << floor_ << ", район " << district_ << "}";
	return oss.str();
} // Apartment::toString


// по заданиию районы не учитываем
bool Apartment::equals(const Object &other)
{
	const Apartment &ap = (const Apartment &)other;

	// точность по площади квартир - 10%, по заданию
	double eps = 0.1 * area_;
	return rooms_ == ap.rooms_ && floor_ == ap.floor_ && abs(area_ - ap.area_) <= eps;
} // Apartment::equals
#pragma endregion


// перегруженные операции
ostream& operator<<(ostream& os, Apartment& apartment)
{
	os << apartment.toString();
	return os;
}