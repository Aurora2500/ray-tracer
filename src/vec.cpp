#include "vec.hpp"
#include <math.h>


vec3::vec3() : m_buf{0,0,0}
{
}

vec3::vec3(float x, float y, float z): m_buf{x,y,z}
{
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

const vec3 UP = vec3(0.0f, 0.0f, 1.0f);