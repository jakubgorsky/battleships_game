//
// Created by Jakub Górski on 16/06/2022.
//

#ifndef BATTLESHIPS_GAME_VECTOR2D_H
#define BATTLESHIPS_GAME_VECTOR2D_H
#include <iostream>
class Vector2D {
public:
    float x, y;

    Vector2D();
    Vector2D(float x, float y);

    Vector2D& add(const Vector2D& vec);
    Vector2D& subtract(const Vector2D& vec);
    Vector2D& multiply(const Vector2D& vec);
    Vector2D& divide(const Vector2D& vec);

    friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

    Vector2D& operator+=(Vector2D& vec);
    Vector2D& operator-=(Vector2D& vec);
    Vector2D& operator*=(Vector2D& vec);
    Vector2D& operator/=(Vector2D& vec);

    friend bool operator==(const Vector2D& vec1, const Vector2D& vec2);
    friend bool operator!=(const Vector2D& vec1, const Vector2D& vec2);

    friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);

    ~Vector2D();
};
#endif //BATTLESHIPS_GAME_VECTOR2D_H
