#include "pch.h"
#include "Utils.h"
#include "Apartment.h"
#include "Applying.h"

// ��������� �������� ������������� ������
int Applying::seedId_ = 1;

// ������������
Applying::Applying():Applying(Apartment(), Apartment(3, 110., 5, "������������")) {}
Applying::Applying(const Apartment& exists, const Apartment& wanted): 
    id_(seedId_++),
    exists_(exists),
    wanted_(wanted)
{
} // Applying::Applying

// ���������
// �������� ������������� ������
int Applying::getId() const { return id_; }

// ��������� ��������
Apartment Applying::getExists() const { return exists_; }
void Applying::setExists(const Apartment& value) 
{
    exists_ = value;
}

// �������� ��������
Apartment Applying::getWanted() const { return wanted_; }
void Applying::setWanted(const Apartment& value) 
{
    wanted_ = value;
}

// ������ ������
string Applying::toString() 
{
    ostringstream oss;
    oss << setw(3) << id_ << ":  ������� " << exists_ << ", ��������: " << wanted_ ;
    return oss.str();
}

// ��������� ��������  �������� ������� ������ � �������� ��������� ������ ������
bool Applying::equals(const Object &other) 
{  
    const Applying &applying = (const Applying &)other;

    return wanted_.equals(applying.exists_);
} // Applying::equals


// ��������� ������ � ������� CSV
string Applying::toCsv() 
{
    ostringstream oss;
    oss << fixed << setprecision(1)
        << id_ << ";"
        // � Apartment ������ ����� ���� �� ����������� toCsv()
        << exists_.getRooms() << ";" << exists_.getArea() << ";" << exists_.getFloor() << ";" << exists_.getDistrict() << ";"
        << wanted_.getRooms() << ";" << wanted_.getArea() << ";" << wanted_.getFloor() << ";" << wanted_.getDistrict();
    return oss.str();
} // Applying::toCsv

// �������� ������ �� ������ � ������� CSV, ��� ������ �� ������ �����
void Applying::parseCsv(string &csv) 
{
    int rooms1, rooms2;
    double area1, area2;
    int floor1, floor2;
    string district1, district2;

    // ������ ��������� ����� ����� �� ������ � ������� CSV, 
    // �������� ������ ; �� "\n" ��� ���������� ������ ������������� 
    // �������� ����� �� ���������� ������ �����, �.�. �������� ����
    // ����� � ���������, �������� � �.�.
    for(int i = 0; i < csv.length(); ++i) {
        if (csv[i] == ';') csv[i] = '\n';
    }
    // istringstream iss(replaceAll(csv, ";", "\n"));
    istringstream iss(csv);
    
    // ���� �� ��������������� ����������
    iss >> id_
        >> rooms1 >> area1 >> floor1 >> district1
        >> rooms2 >> area2 >> floor2 >> district2;

    // ������������� ��������� ��������� ��������
    exists_.setRooms(rooms1);
    exists_.setArea(area1);
    exists_.setFloor(floor1);
    exists_.setDistrict(district1);
    
    // ������������� ��������� �������� ��������
    wanted_.setRooms(rooms2);
    wanted_.setArea(area2);
    wanted_.setFloor(floor2);
    wanted_.setDistrict(district2);
} // Applying::parseCsv


// ����� ����� �������
string Applying::header() 
{
    ostringstream oss;
    oss << "\t+-----+-------------------------------------------------------+-------------------------------------------------------+\n"
        << "\t|  �� | ��������� �������� ��� ������                         | �������� ������� ������                               |\n"
        << "\t+-----+---------------+-------------+------+------------------+---------------+-------------+------+------------------+\n"
        << "\t|     | ���-�� ������ | �������, �2 | ���� | �����            | ���-�� ������ | �������, �2 | ���� | �����            |\n"
        << "\t+-----+---------------+-------------+------+------------------+---------------+-------------+------+------------------+";

    return oss.str();
} // Applying::header


// ����� ������� �������
string Applying::footer()
{
    ostringstream oss;
    oss << "\t+-----+---------------+-------------+------+------------------+---------------+-------------+------+------------------+";
    return oss.str();
} // Applying::footer


// ����� ������ �������
string Applying::toTableRow()
{
    ostringstream oss;
    oss << fixed << setprecision(1) << "\t"
        << "| " << setw( 3) << id_ << " "
        << "| " << setw(13) << exists_.getRooms() << " " 
        << "| " << setw(11) << exists_.getArea() << " " 
        << "| " << setw( 4) << exists_.getFloor() << " " 
        << "| " << setw(16) << left << exists_.getDistrict() << right << " "
        << "| " << setw(13) << wanted_.getRooms() << " " 
        << "| " << setw(11) << wanted_.getArea() << " " 
        << "| " << setw( 4) << wanted_.getFloor() << " " 
        << "| " << setw(16) << left << wanted_.getDistrict() << right << " |";

    return oss.str();
} // Applying::toTableRow


// ������������� ��������
ostream& operator<<(ostream& os, Applying& applying) 
{
    os << applying.toString();
    return os;
} // operator<<