//
// Created by Jakub Górski on 16/06/2022.
//

#include "Vector2D.h"

Vector2D &Vector2D::add(const Vector2D &vec) {
    this->x += vec.x;
    this->y += vec.y;

    return *this;
}

Vector2D &Vector2D::subtract(const Vector2D &vec) {
    this->x -= vec.x;
    this->y -= vec.y;

    return *this;
}

Vector2D &Vector2D::multiply(const Vector2D &vec) {
    this->x *= vec.x;
    this->y *= vec.y;

    return *this;
}

Vector2D &Vector2D::divide(const Vector2D &vec) {
    this->x /= vec.x;
    this->y /= vec.y;

    return *this;
}

Vector2D &Vector2D::operator+=(Vector2D &vec) {
    return this->add(vec);
}

Vector2D &Vector2D::operator-=(Vector2D &vec) {
    return this->subtract(vec);
}

Vector2D &Vector2D::operator*=(Vector2D &vec) {
    return this->multiply(vec);
}

Vector2D &Vector2D::operator/=(Vector2D &vec) {
    return this->divide(vec);
}

bool operator==(const Vector2D &vec1, const Vector2D &vec2) {
    if(vec1.x == vec2.x && vec1.y == vec2.y)
        return true;
    return false;
}

bool operator!=(const Vector2D &vec1, const Vector2D &vec2) {
    if(vec1.x == vec2.x && vec1.y == vec2.y)
        return false;
    return true;
}

Vector2D &operator+(Vector2D &v1, const Vector2D &v2) {
    return v1.add(v2);
}

Vector2D &operator-(Vector2D &v1, const Vector2D &v2) {
    return v1.subtract(v2);
}

Vector2D &operator*(Vector2D &v1, const Vector2D &v2) {
    return v1.multiply(v2);
}

Vector2D &operator/(Vector2D &v1, const Vector2D &v2) {
    return v1.divide(v2);
}

Vector2D::Vector2D() {
    this->x=this->y=0;
}

Vector2D::Vector2D(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2D::~Vector2D() {
}

std::ostream &operator<<(std::ostream &stream, const Vector2D &vec) {
    stream << "(" << vec.x << ", " << vec.y << ")";
    return stream;
}
