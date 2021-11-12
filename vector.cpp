#include "vector.hpp"

Vector Vector::operator+(const Vector who) const
{
    Vector result;
    result.x = this->x + who.x;
    result.y = this->y + who.y;
    return result;
}

Vector Vector::operator-(const Vector who) const
{
    Vector result;
    result.x = this->x - who.x;
    result.y = this->y - who.y;
    return result;
}

Vector Vector::operator*(const Vector who) const
{
    Vector result;
    result.x = this->x * who.x;
    result.y = this->y * who.y;
    return result;
}

void Vector::operator+=(const Vector who)
{
	*this = *this + who;
}

void Vector::operator+=(const float who)
{
	*this = *this + who;
}

Vector Vector::operator/(const Vector who) const
{
    Vector result;
    result.x = this->x / who.x;
    result.y = this->y / who.y;
    return result;
}

bool Vector::operator==(const Vector who) const
{
    return
    (
        this->x == who.x &&
        this->y == who.y
    );
}

bool Vector::operator!=(const Vector who) const
{
    return !(*this == who);
}

void Vector::operator=(const Vector who)
{
    this->x = who.x;
    this->y = who.y;
}


Vector Vector::operator+(const float who) const
{
    Vector result;
    result.x = this->x + who;
    result.y = this->y + who;
    return result;
}

Vector Vector::operator-(const float who) const
{
    Vector result;
    result.x = this->x - who;
    result.y = this->y - who;
    return result;
}

Vector Vector::operator*(const float who) const
{
    Vector result;
    result.x = this->x * who;
    result.y = this->y * who;
    return result;
}

Vector Vector::operator/(const float who) const
{
    Vector result;
    result.x = this->x / who;
    result.y = this->y / who;
    return result;   
}

bool Vector::operator==(const float who) const
{
    return
    (
        this->x == who &&
        this->y == who
    );
}

bool Vector::operator!=(const float who) const
{
    return !(*this == who);
}

void Vector::operator=(const float who)
{
    this->x = who;
    this->y = who;
}

Vector Vector::operator-() const
{
    Vector result;
    result.x = -this->x;
    result.y = -this->y;
    return result;
}

Vector::operator bool() const
{
    return *this != 0.0;
}