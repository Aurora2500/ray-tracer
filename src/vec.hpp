#include <iostream>
#ifndef VEC_H_
#define VEC_H_


class vec3 {
private:
	double m_buf[3];

public:
	vec3();
	vec3(double x, double y, double z);
	double x() const;
	double y() const;
	double z() const;
	double operator[](int i) const;
	double& operator[](int i);
	
	vec3 operator-() const;
	vec3 operator+(const vec3 &o) const;
	vec3 operator-(const vec3 &o) const;
	vec3 operator*(const vec3 &o) const;
	vec3 operator*(double s) const;
	vec3 operator/(const vec3 &o) const;
	vec3 operator/(double s) const;
	vec3& operator+=(const vec3 &o);
	vec3& operator-=(const vec3 &o);
	vec3& operator*=(const vec3 &o);
	vec3& operator*=(double s);
	vec3& operator/=(const vec3 &o);
	vec3& operator/=(double s);

	double length() const;
	vec3 normalize() const;
};
std::ostream& operator<<(std::ostream &os, const vec3 &v);
double dot(const vec3 &a, const vec3 &b);
vec3 cross(const vec3 &a, const vec3 &b);

vec3 random_unit_sphere();

vec3 random_on_hemisphere(const vec3 &normal);

extern const vec3 UP;

#endif