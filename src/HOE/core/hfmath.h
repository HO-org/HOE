#pragma once
// #define __STDC_LIMIT_MACROS
#include <cfloat>
#include <math.h>
#include <iostream>


namespace HFMath
{
    inline float pythagorean(float a, float b)
    {
        return sqrt(pow(a, 2) + pow(b, 2));
    }

    inline float lerp(float from, float to, float delta)
    {
        return (from * (1.0f - delta)) + (to * delta);
    }

    class Vector2
    {
    public:
        Vector2()
        {
            m_X = 0.0f;
            m_Y = 0.0f;
        }
        Vector2(float x, float y)
        {
            m_X = x;
            m_Y = y;
        }

        /* #region Overloaded Operators */
        HFMath::Vector2 operator=(HFMath::Vector2 const &other)
        {
            if (this == &other)
            {
                return *this;
            }
            SetX(other.m_X);
            SetY(other.m_Y);
            return *this;
        }
        HFMath::Vector2 operator+(HFMath::Vector2 &other)
        {
            return HFMath::Vector2(
                GetX() + other.GetX(),
                GetY() + other.GetY());
        }
        HFMath::Vector2 operator+(HFMath::Vector2 &&other)
        {
            return HFMath::Vector2(
                GetX() + other.GetX(),
                GetY() + other.GetY());
        }
        HFMath::Vector2 operator+=(HFMath::Vector2 &other)
        {
            *this = *this + other;
            return *this;
        }
        HFMath::Vector2 operator-(HFMath::Vector2 &other)
        {
            return HFMath::Vector2(
                GetX() - other.GetX(),
                GetY() - other.GetY());
        }
        HFMath::Vector2 operator-(HFMath::Vector2 &&other)
        {
            return HFMath::Vector2(
                GetX() - other.GetX(),
                GetY() - other.GetY());
        }
        HFMath::Vector2 operator-=(HFMath::Vector2 &other)
        {
            *this = *this - other;
            return *this;
        }
        HFMath::Vector2 operator*(float amount)
        {
            return HFMath::Vector2(
                GetX() * amount,
                GetY() * amount);
        }
        HFMath::Vector2 operator*(int amount)
        {
            return HFMath::Vector2(
                GetX() * amount,
                GetY() * amount);
        }
        HFMath::Vector2 operator*(double amount)
        {
            return HFMath::Vector2(
                GetX() * amount,
                GetY() * amount);
        }
        HFMath::Vector2 operator*=(float amount)
        {
            *this = *this * amount;
            return *this;
        }
        HFMath::Vector2 operator*=(int amount)
        {
            *this = *this * amount;
            return *this;
        }
        HFMath::Vector2 operator*=(double amount)
        {
            *this = *this * amount;
            return *this;
        }
        HFMath::Vector2 operator/(float amount)
        {
            return HFMath::Vector2(
                GetX() / amount,
                GetY() / amount);
        }
        HFMath::Vector2 operator/(int amount)
        {
            return HFMath::Vector2(
                GetX() / amount,
                GetY() / amount);
        }
        HFMath::Vector2 operator/(double amount)
        {
            return HFMath::Vector2(
                GetX() / amount,
                GetY() / amount);
        }
        HFMath::Vector2 operator/=(float amount)
        {
            *this = *this / amount;
            return *this;
        }
        HFMath::Vector2 operator/=(int amount)
        {
            *this = *this / amount;
            return *this;
        }
        HFMath::Vector2 operator/=(double amount)
        {
            *this = *this / amount;
            return *this;
        }
        HFMath::Vector2 operator*(HFMath::Vector2 other)
        {
            return HFMath::Vector2(
                GetX() * other.GetX(),
                GetY() * other.GetY()
            );
        }
        HFMath::Vector2 operator*=(HFMath::Vector2 other)
        {
            *this = *this * other;
            return *this;
        }
        friend std::ostream& operator<<(std::ostream& os, const HFMath::Vector2& vector)
        {
            os << "(" << vector.m_X << ", " << vector.m_Y << ")";
            return os;
        }
        bool operator==(const HFMath::Vector2& other)
        {
            return this->GetX() == other.m_X && this->GetY() == other.m_Y;
        }
        /* #endregion */

        static HFMath::Vector2 ZERO()
        {
            return HFMath::Vector2(0.0f, 0.0f);
        }

        float Length()
        {
            return HFMath::pythagorean(GetX(), GetY());
        }

        HFMath::Vector2 Normalized()
        {
            float length = this->Length();
            if (length == 0.0f)
            {
                return HFMath::Vector2::ZERO();
            }
            return HFMath::Vector2(
                this->GetX() / length,
                this->GetY() / length);
        }

        HFMath::Vector2 directionTo(HFMath::Vector2 target)
        {
            return (target - *this).Normalized();
        }

        void SetX(float value) { m_X = value; }
        void SetY(float value) { m_Y = value; }
        float GetX() { return m_X; }
        float GetY() { return m_Y; }
        void AddX(float amount) { SetX(GetX() + amount); }
        void AddY(float amount) { SetY(GetY() + amount); }

    private:
        float m_X;
        float m_Y;
    };

    // inline Vector2 lineIntersection(Vector2 A, Vector2 B, Vector2 C, Vector2 D)
    // {
    //     double a = B.GetY() - A.GetY();
    //     double b = A.GetX() - B.GetX();
    //     double c = a * A.GetX() + b * A.GetY();
    //     double a1 = D.GetY() - C.GetY();
    //     double b1 = C.GetX() - D.GetX();
    //     double c1 = a1 * C.GetX() + b1 * C.GetY();
    //     double det = a * b1 - a1 * b;

    //     if (det == 0) { return Vector2(FLT_MAX, FLT_MAX); }
        
    //     return Vector2(
    //         (b1*c - b*c1) / det,
    //         (a*c1 - a1*c) / det
    //     );
    // }
}