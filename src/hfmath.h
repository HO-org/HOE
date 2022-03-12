#pragma once
#include <math.h>
#include <iostream>

namespace HFMath
{
    inline float pythagorean(float a, float b)
    {
        return sqrt(pow(a, 2) + pow(b, 2));
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
        friend std::ostream& operator<<(std::ostream& os, const HFMath::Vector2& vector)
        {
            os << "(" << vector.m_X << ", " << vector.m_X << ")";
            return os;
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
}