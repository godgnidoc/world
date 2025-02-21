#ifndef __WORLD_GEO_H__
#define __WORLD_GEO_H__

#include "fmt/format.h"
#include <cmath>
#include <optional>
#include <stdexcept>

namespace world {

struct Num {
  static constexpr double epsilon = 1e-6;
  double value{0};

  Num(double v = 0.0) : value{v} {}
  Num(Num const& n) : value(n.value) {}
  Num(Num&& n) : value(n.value) {}
  Num& operator=(Num const& n) { return value = n.value, *this; }
  Num& operator=(Num&& n) { return value = n.value, *this; }
  ~Num() = default;

  Num operator=(double v) { return value = v, *this; }
  Num operator-() const { return {-value}; }
  Num operator+(Num const& n) const { return {value + n.value}; }
  Num operator-(Num const& n) const { return {value - n.value}; }
  Num operator*(Num const& n) const { return {value * n.value}; }
  Num operator/(Num const& n) const { return {value / n.value}; }
  Num& operator+=(Num const& n) { return (value += n.value), *this; }
  Num& operator-=(Num const& n) { return (value -= n.value), *this; }
  Num& operator*=(Num const& n) { return (value *= n.value), *this; }
  Num& operator/=(Num const& n) { return (value /= n.value), *this; }
  bool operator<(Num const& n) const { return value - n.value < -epsilon; }
  bool operator>(Num const& n) const { return value - n.value > epsilon; }
  bool operator<=(Num const& n) const { return value - n.value <= 0; }
  bool operator>=(Num const& n) const { return value - n.value >= 0; }
  bool operator==(Num const& n) const {
    return fabs(value - n.value) < epsilon;
  }
  bool operator!=(Num const& n) const {
    return fabs(value - n.value) >= epsilon;
  }
};

using MaybeNum = std::optional<Num>;

Num sin(Num n) { return sin(n.value); }
Num cos(Num n) { return cos(n.value); }
Num tan(Num n) { return tan(n.value); }
Num asin(Num n) { return asin(n.value); }
Num acos(Num n) { return acos(n.value); }
Num atan(Num n) { return atan(n.value); }
Num atan2(Num y, Num x) { return atan2(y.value, x.value); }
Num sqrt(Num n) { return sqrt(n.value); }
Num abs(Num n) { return fabs(n.value); }
Num pow(Num n, Num e) { return pow(n.value, e.value); }
Num exp(Num n) { return exp(n.value); }
Num log(Num n) { return log(n.value); }
Num log10(Num n) { return log10(n.value); }
Num floor(Num n) { return floor(n.value); }
Num ceil(Num n) { return ceil(n.value); }
Num round(Num n) { return round(n.value); }
Num fmod(Num n, Num d) { return fmod(n.value, d.value); }
Num deg(Num rad) { return rad.value * 180.0 / M_PI; }
Num rad(Num deg) { return deg.value * M_PI / 180.0; }

struct Vec {
  Num x;
  Num y;

  Vec(Num v = 0) : x{v}, y{v} {}
  Vec(Num x, Num y) : x{x}, y{y} {}
  Vec(Vec const& v) : x(v.x), y(v.y) {}
  Vec(Vec&& v) : x(v.x), y(v.y) {}
  Vec& operator=(Vec const& v) { return x = v.x, y = v.y, *this; }
  Vec& operator=(Vec&& v) { return x = v.x, y = v.y, *this; }
  ~Vec() = default;

  Vec operator+(Vec const& v) const { return {x + v.x, y + v.y}; }
  Vec& operator+=(Vec const& v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  Vec operator-(Vec const& v) const { return {x - v.x, y - v.y}; }
  Vec& operator-=(Vec const& v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  Vec operator*(Num s) const { return {x * s, y * s}; }
  Vec& operator*=(Num s) {
    x *= s;
    y *= s;
    return *this;
  }

  Vec operator/(Num s) const { return {x / s, y / s}; }
  Vec& operator/=(Num s) {
    x /= s;
    y /= s;
    return *this;
  }

  bool operator==(Vec const& v) const { return x == v.x && y == v.y; }
  bool operator!=(Vec const& v) const { return x != v.x || y != v.y; }

  Num Dot(Vec const& v) const { return x * v.x + y * v.y; }
  Num Cross(Vec const& v) const { return x * v.y - y * v.x; }
  Num Length() const { return sqrt(x * x + y * y); }
  Num Length2() const { return x * x + y * y; }

  Num Angle() const {
    if (y == 0) {
      if (x >= 0)
        return 0;
      else
        return M_PI;
    }

    Num a = atan2(y, x);
    if (a < 0)
      a += 2 * M_PI;
    return a;
  }

  Vec Normalize() const { return (*this) / Length(); }

  Vec Rotate(Num rad) const {
    Num c = cos(rad);
    Num s = sin(rad);
    return {x * c - y * s, x * s + y * c};
  }
};

using MaybeVec = std::optional<Vec>;

struct Line {
  Vec A;
  Vec B;

  Line(Vec p = {0, 0}) : A{p}, B{p} {}
  Line(Vec a, Vec b) : A{a}, B{b} {}
  Line(Line const& l) : A(l.A), B(l.B) {}
  Line(Line&& l) : A(l.A), B(l.B) {}
  Line& operator=(Line const& l) { return A = l.A, B = l.B, *this; }
  Line& operator=(Line&& l) { return A = l.A, B = l.B, *this; }
  ~Line() = default;

  Vec V() const { return B - A; }

  MaybeVec Intersect(Vec P) {
    auto c = (P - A).Cross(V());
    if (c != 0)
      return std::nullopt;

    auto a = A - P;
    auto b = B - P;
    if (a.Dot(b) <= 0)
      return P;

    return std::nullopt;
  }

  MaybeVec Intersect(Line L) {
    auto c = V().Cross(L.V());
    if (c == 0) {
      // 平行
      auto as = (L.A - A).Cross(V());
      auto bs = (L.B - A).Cross(V());
      if (as != 0 || bs != 0)
        return std::nullopt;

      // 共线
      auto ain = (L.A - A).Dot(L.A - B) <= 0;
      auto bin = (A - L.A).Dot(A - L.B) <= 0;
      auto main = (A - L.A).Cross(A - L.B) <= 0;
      auto mbin = (B - L.A).Cross(B - L.B) <= 0;
      size_t i = 0;
      if (ain)
        i |= 1;
      if (bin)
        i |= 2;
      if (main)
        i |= 4;
      if (mbin)
        i |= 8;
      switch (i) {
      case 0:
        return std::nullopt;
      case 1:
      case 2:
      case 4:
      case 8:
      case 13:
      case 14:
        throw std::runtime_error("unreachable");
      case 3:
      case 7:
      case 11:
      case 15:
        return (L.A + L.B) / 2;
      case 5:
        return (L.A + A) / 2;
      case 6:
        return (L.A + B) / 2;
      case 9:
        return (L.B + A) / 2;
      case 10:
        return (L.B + B) / 2;
      case 12:
        return (A + B) / 2;
      }
      throw std::runtime_error("unreachable");
    }

    auto a = L.A - A;
    auto t = a.Cross(L.V()) / c;
    if (t < 0 || t > 1)
      return std::nullopt;

    auto u = a.Cross(V()) / c;
    if (u < 0 || u > 1)
      return std::nullopt;

    return A + V() * t;
  }
};
} // namespace world

namespace fmt {

template <> struct formatter<world::Num> : formatter<string_view> {
  // parse is inherited from formatter<string_view>.

  auto format(world::Num n, format_context& ctx) const
      -> format_context::iterator {
    auto result = fmt::format("{}", n.value);
    return formatter<string_view>::format(result, ctx);
  }
};

template <> struct formatter<world::Vec> : formatter<string_view> {
  // parse is inherited from formatter<string_view>.

  auto format(world::Vec v, format_context& ctx) const
      -> format_context::iterator {
    auto result = fmt::format("({}, {})", v.x, v.y);
    return formatter<string_view>::format(result, ctx);
  }
};

template <> struct formatter<world::Line> : formatter<string_view> {
  // parse is inherited from formatter<string_view>.

  auto format(world::Line L, format_context& ctx) const
      -> format_context::iterator {
    auto result = fmt::format("<{}, {}>", L.A, L.B);
    return formatter<string_view>::format(result, ctx);
  }
};
} // namespace fmt

#endif