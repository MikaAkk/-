#include "pch.h"
#include "Apartment.h"

#pragma region ������������
Apartment::Apartment() :Apartment(3, 120., 3, "������������") {}

Apartment::Apartment(int rooms, double area, int floor, const string& district)
{
	setRooms(rooms);
	setArea(area);
	setFloor(floor);
	setDistrict(district);
} // Apartment::Apartment
#pragma endregion


#pragma region ���������
// ���������� ������
int  Apartment::getRooms() const { return rooms_; }
void Apartment::setRooms(int value)
{
	rooms_ = (value <= 0 || value > 36) 
		? throw exception("Apartment: ������������ ���������� ������")
		: value;
}  // Apartment::setRooms

// �������
double Apartment::getArea() const { return area_; }
void   Apartment::setArea(double value)
{
	area_ = (value <= 0 || value > 3600)
		? throw exception("Apartment: ���������� ������� ��������")
		: value;;
}

// ����
int  Apartment::getFloor() const { return floor_; }
void Apartment::setFloor(int value)
{
	floor_ = (value <= 0 || value > 366)
		? throw exception("Apartment: ������������ ���������� ������")
		: value;
}

// �����
string Apartment::getDistrict() const { return district_; }
void Apartment::setDistrict(const string& value)
{
	district_ =  value.empty()
		? throw exception("Apartment: ������������ �������� ������")
		: value;
}

#pragma endregion
string Apartment::toString()
{
	ostringstream oss;
	oss << "Apartment {������ " << rooms_ << ", ������� " << area_ << " �2, ���� " << floor_ << ", ����� " << district_ << "}";
	return oss.str();
} // Apartment::toString


// �� �������� ������ �� ���������
bool Apartment::equals(const Object &other)
{
	const Apartment &ap = (const Apartment &)other;

	// �������� �� ������� ������� - 10%, �� �������
	double eps = 0.1 * area_;
	return rooms_ == ap.rooms_ && floor_ == ap.floor_ && abs(area_ - ap.area_) <= eps;
} // Apartment::equals
#pragma endregion


// ������������� ��������
ostream& operator<<(ostream& os, Apartment& apartment)
{
	os << apartment.toString();
	return os;
}