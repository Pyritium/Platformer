#pragma once
#include <iostream>
#include <cmath>
class Vector2 {
public:
    double X, Y;
    void Diagnose() {
        std::cout << X << "," << Y << " | " << Magnitude() << "\n";
    }
    
    double Magnitude() {
        double Equation = X * X + Y * Y;
        return sqrt(Equation);
    }

    //Vector2() = default;
    Vector2(double t_X, double t_Y);

    // Overload to add two vectors together.
    Vector2 operator+(const Vector2 Vec) {
        Vector2 ReturningVec(X,Y);
        ReturningVec.X = X + Vec.X;
        ReturningVec.Y = Y + Vec.Y;
        return ReturningVec;
    };
    Vector2 operator-(const Vector2 Vec) {
        Vector2 ReturningVec(X, Y);
        ReturningVec.X = X - Vec.X;
        ReturningVec.Y = Y - Vec.Y;
        return ReturningVec;
    }
    Vector2 operator*(const Vector2 Vec) {
        Vector2 ReturningVec(X, Y);
        ReturningVec.X = X * Vec.X;
        ReturningVec.Y = Y * Vec.Y;
        return ReturningVec;
    }
    Vector2 operator/(const Vector2 Vec) {
        Vector2 ReturningVec(X, Y);
        ReturningVec.X = X / Vec.X;
        ReturningVec.Y = Y / Vec.Y;
        return ReturningVec;
    }
private:

};

Vector2::Vector2(double t_X, double t_Y) {
    X = t_X;
    Y = t_Y;
}