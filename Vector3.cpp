#include "Vector3.h"
#include <iostream>
#include <cmath>


Vector3::Vector3() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
Vector3::Vector3(float _x, float _y, float _z) {
	this->x = _x;
	this->y = _y;
	this->z = _z;
}

float Vector3::getX() {
	return this->x;
}

float Vector3::getY() {
	return this->y;
}

float Vector3::getZ() {
	return this->z;
}

Vector3::~Vector3() {
	
}

Vector3 Vector3::add(Vector3 w)
{

	Vector3 res;
	res.x = this->x + w.x;
	res.y = this->y + w.y;
	res.z = this->z + w.z;
	return res;
}

Vector3 Vector3::sub(Vector3 w)
{
	Vector3 res;
	res = this->add(w);
	return res.negate();
}

void Vector3::scale(float i)
{
	this->x = i * this->x;
	this->y = i * this->y;
	this->z = i * this->z;
}

float Vector3::dotProduct(Vector3 w)
{
	return (this->x*w.x + this->y*w.y + this->z*w.z);
}

Vector3 Vector3::negate()
{
	Vector3 res;
	res.scale(-1);
	return res;
}

float Vector3::module()
{
	float mod = sqrt(this->x * this->x + this->y*this->y + this->z * this->z);
	return mod;
}

float Vector3::module2()
{
	return this->module()*this->module();
}

Vector3 Vector3::normalize()
{
	Vector3 res;
	res.x = this->x / this->module();
	res.y = this->y / this->module();
	res.z = this->z / this->module();
	return res;
}

Vector3 Vector3::simetric(Vector3 w)
{
	Vector3 res,wNormalizado;	

	wNormalizado = w.normalize();
	float prod = res.dotProduct(wNormalizado);
	
	wNormalizado.scale(2 * prod);

	res = this->sub(wNormalizado);
	res.negate();
	return res;	
}

Vector3 Vector3::crossProduct(Vector3 w) {
	Vector3 res;
	res.x = this->y * w.z - this->z * w.y;
	res.y = this->z * w.x - this->x * w.z;
	res.z = this->x * w.y - this->y * w.x;
	return res;
}
