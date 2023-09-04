#include "vec.hpp"
#include "rand.hpp"

#include <math.h>

const double PI = 3.1415926535897932385;


vec3::vec3() : m_buf{0,0,0}
{
}

vec3::vec3(double x, double y, double z)
{
	m_buf[0] = x;
	m_buf[1] = y;
	m_buf[2] = z;
}

double vec3::x() const
{
	return m_buf[0];
}

double vec3::y() const
{
	return m_buf[1];
}

double vec3::z() const
{
	return m_buf[2];
}

double vec3::operator[](int i) const
{
	return m_buf[i];
}

double& vec3::operator[](int i)
{
	return m_buf[i];
}

vec3 vec3::operator-() const
{
	return vec3(-m_buf[0], -m_buf[1], -m_buf[2]);
}

vec3 vec3::operator+(const vec3 &o) const
{
	return vec3(m_buf[0] + o[0], m_buf[1] + o[1], m_buf[2] + o[2]);
}

vec3 vec3::operator-(const vec3 &o) const
{
	return vec3(m_buf[0] - o[0], m_buf[1] - o[1], m_buf[2] - o[2]);
}

vec3 vec3::operator*(const vec3 &o) const
{
	return vec3(m_buf[0] * o[0], m_buf[1] * o[1], m_buf[2] * o[2]);
}

vec3 vec3::operator*(double s) const
{
	return vec3(m_buf[0] * s, m_buf[1] * s, m_buf[2] * s);
}

vec3 vec3::operator/(const vec3 &o) const
{
	return vec3(m_buf[0] / o[0], m_buf[1] / o[1], m_buf[2] / o[2]);
}

vec3 vec3::operator/(double s) const
{
	return vec3(m_buf[0] / s, m_buf[1] / s, m_buf[2] / s);
}



vec3& vec3::operator+=(const vec3 &o)
{
	m_buf[0] += o[0];
	m_buf[1] += o[1];
	m_buf[2] += o[2];
	return *this;
}

vec3& vec3::operator-=(const vec3 &o)
{
	m_buf[0] -= o[0];
	m_buf[1] -= o[1];
	m_buf[2] -= o[2];
	return *this;
}

vec3& vec3::operator*=(const vec3 &o)
{
	m_buf[0] *= o[0];
	m_buf[1] *= o[1];
	m_buf[2] *= o[2];
	return *this;
}

vec3& vec3::operator*=(double s)
{
	m_buf[0] *= s;
	m_buf[1] *= s;
	m_buf[2] *= s;
	return *this;
}

vec3& vec3::operator/=(const vec3 &o)
{
	m_buf[0] /= o[0];
	m_buf[1] /= o[1];
	m_buf[2] /= o[2];
	return *this;
}

vec3& vec3::operator/=(double s)
{
	m_buf[0] /= s;
	m_buf[1] /= s;
	m_buf[2] /= s;
	return *this;
}

double vec3::length() const
{
	return std::sqrt(m_buf[0] * m_buf[0] + m_buf[1] * m_buf[1] + m_buf[2] * m_buf[2]);
}

vec3 vec3::normalize() const
{
	return (*this) / (length());
}

#include <iostream>

std::ostream& operator<<(std::ostream &os, const vec3 &v)
{
	os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
	return os;
}

double dot(const vec3 &a, const vec3 &b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

vec3 cross(const vec3 &a, const vec3 &b)
{
	return vec3(
		a[1] * b[2] - a[2] * b[1],
		a[2] * b[0] - a[0] * b[2],
		a[0] * b[1] - a[1] * b[0]
	);
}

vec3 random_unit_sphere()
{
	double u1 = random_double();
	double u2 = random_double();
	double lambda = std::acos(2.0 * u1 - 1.0) - PI / 2.0;
	double phi = 2.0 * PI * u2;
	return vec3(
		std::cos(lambda) * std::cos(phi),
		std::cos(lambda) * std::sin(phi),
		std::sin(lambda)
	);
}

vec3 random_on_hemisphere(const vec3 &normal)
{
	vec3 v = random_unit_sphere();
	if (dot(v, normal) < 0.0) {
		return -v;
	}
	return v;
}

const vec3 UP = vec3(0.0f, 0.0f, 1.0f);