#pragma once
#include "pch.h"

// Базовый класс для организации вывода 
// всех производных классов 
class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	// все потомки класса умеют строить свое строковое представление
	virtual string toString() = 0;

	// все потомки класса умеют проверять себя на раенство другому 
	// объекту - потомку базового класса
	virtual bool equals(const Object &other) = 0;
};
