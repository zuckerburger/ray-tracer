#pragma once
#include <iostream>
#include <cmath>

class Vec3 {
  public:
    double x;
    double y;
    double z;

    constexpr Vec3() : x(0), y(0), z(0) {}
    constexpr Vec3(double x, double y, double z) {
      this->x = x;
      this->y = y;
      this->z = z;
    }

    double length() const {
      return std::sqrt(x*x + y*y + z*z);
    }

    friend Vec3 operator+(const Vec3& a, const Vec3& t) {
      return Vec3{t.x + a.x, t.y + a.y, t.z + a.z};
    }

    friend Vec3 operator+(const Vec3&a, const double t) {
      return Vec3{a.x + t, a.y + t, a.z + t};
    }

    friend Vec3 operator+(const double t, const Vec3&a) {
      return a + t;
    }

    friend Vec3 operator-(const Vec3&a, const Vec3&t) {
      return Vec3{a.x - t.x, a.y - t.y, a.z - t.z};
    }

    friend Vec3 operator-(const Vec3&a, const double t) {
      return Vec3{a.x - t, a.y - t, a.z - t};
    }

    friend Vec3 operator-(const double t, const Vec3&a) {
      return Vec3{t-a.x, t-a.y, t-a.z};
    }

    friend Vec3 operator*(const Vec3& a, const double t) {
      return Vec3{t * a.x, t * a.y, t * a.z};
    }

    friend Vec3 operator*(const double t, const Vec3& a) {
      return a * t;
    }

    friend Vec3 operator/(const Vec3& a, const double t) {
      return a * (1/t);
    }

    friend bool operator==(const Vec3&a, const Vec3&b) {
      return (a.x == b.x && a.y == b.y && a.z == b.z);
    }

    friend std::ostream& operator<<(std::ostream& out, const Vec3& a) {
      return out << a.x << " "<< a.y << " "<< a.z;
    }
};

inline Vec3 normalise(const Vec3&a) {
  return (a.length() == 0) ? a : a / a.length();
}

inline double dotProduct(const Vec3& a, const Vec3& b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}
