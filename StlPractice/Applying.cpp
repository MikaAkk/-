#include "pch.h"
#include "Utils.h"
#include "Apartment.h"
#include "Applying.h"

// начальное значение идентфикатора заявки
int Applying::seedId_ = 1;

// конструкторы
Applying::Applying():Applying(Apartment(), Apartment(3, 110., 5, "Буденновский")) {}
Applying::Applying(const Apartment& exists, const Apartment& wanted): 
    id_(seedId_++),
    exists_(exists),
    wanted_(wanted)
{
} // Applying::Applying

// аксессоры
// получить идентификатор заявки
int Applying::getId() const { return id_; }

// имеющаяся квартира
Apartment Applying::getExists() const { return exists_; }
void Applying::setExists(const Apartment& value) 
{
    exists_ = value;
}

// желаемая квартира
Apartment Applying::getWanted() const { return wanted_; }
void Applying::setWanted(const Apartment& value) 
{
    wanted_ = value;
}

// методы класса
string Applying::toString() 
{
    ostringstream oss;
    oss << setw(3) << id_ << ":  имеется " << exists_ << ", желаемая: " << wanted_ ;
    return oss.str();
}

// сравнение желаемой  квартиры текущей заявки с имеющеся квартирой другой заявки
bool Applying::equals(const Object &other) 
{  
    const Applying &applying = (const Applying &)other;

    return wanted_.equals(applying.exists_);
} // Applying::equals


// формирует строку в формате CSV
string Applying::toCsv() 
{
    ostringstream oss;
    oss << fixed << setprecision(1)
        << id_ << ";"
        // в Apartment вполне можно было бы реализовать toCsv()
        << exists_.getRooms() << ";" << exists_.getArea() << ";" << exists_.getFloor() << ";" << exists_.getDistrict() << ";"
        << wanted_.getRooms() << ";" << wanted_.getArea() << ";" << wanted_.getFloor() << ";" << wanted_.getDistrict();
    return oss.str();
} // Applying::toCsv

// получает данные из строки в формате CSV, при чтении из потока ввода
void Applying::parseCsv(string &csv) 
{
    int rooms1, rooms2;
    double area1, area2;
    int floor1, floor2;
    string district1, district2;

    // делаем строковый поток ввода из строки в формате CSV, 
    // заменить символ ; на "\n" для корректной работы перегруженной 
    // операции ввода из строкового потока ввода, т.е. возможен ввод
    // строк с пробелами, запятыми и т.п.
    for(int i = 0; i < csv.length(); ++i) {
        if (csv[i] == ';') csv[i] = '\n';
    }
    // istringstream iss(replaceAll(csv, ";", "\n"));
    istringstream iss(csv);
    
    // ввод во вспомогательные переменные
    iss >> id_
        >> rooms1 >> area1 >> floor1 >> district1
        >> rooms2 >> area2 >> floor2 >> district2;

    // устанавливаем параметры имеющейся квартиры
    exists_.setRooms(rooms1);
    exists_.setArea(area1);
    exists_.setFloor(floor1);
    exists_.setDistrict(district1);
    
    // устанавливаем параметры желаемой квартиры
    wanted_.setRooms(rooms2);
    wanted_.setArea(area2);
    wanted_.setFloor(floor2);
    wanted_.setDistrict(district2);
} // Applying::parseCsv


// вывод шапки таблицы
string Applying::header() 
{
    ostringstream oss;
    oss << "\t+-----+-------------------------------------------------------+-------------------------------------------------------+\n"
        << "\t|  ид | Имеющаяся квартира для обмена                         | Желаемый вариант обмена                               |\n"
        << "\t+-----+---------------+-------------+------+------------------+---------------+-------------+------+------------------+\n"
        << "\t|     | кол-во комнат | площадь, м2 | этаж | район            | кол-во комнат | площадь, м2 | этаж | район            |\n"
        << "\t+-----+---------------+-------------+------+------------------+---------------+-------------+------+------------------+";

    return oss.str();
} // Applying::header


// вывод подвала таблицы
string Applying::footer()
{
    ostringstream oss;
    oss << "\t+-----+---------------+-------------+------+------------------+---------------+-------------+------+------------------+";
    return oss.str();
} // Applying::footer


// вывод строки таблицы
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


// перегруженные операции
ostream& operator<<(ostream& os, Applying& applying) 
{
    os << applying.toString();
    return os;
} // operator<<