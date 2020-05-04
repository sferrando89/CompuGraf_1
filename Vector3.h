
#pragma once
class Vector3
{
private:
    float x, y, z;

public:

    Vector3();
    Vector3(float _x, float _y, float _z);

    float getX();
    float getY();
    float getZ();

    virtual ~Vector3();

    Vector3 add(Vector3 w); 
    //devuelve un nuevo vector que resulta de sumarle w

    Vector3 sub(Vector3 w); 
    //devuelve un nuevo vector que resulta de restarle w

    void scale(float i); 
    //multiplica el vector por i

    float dotProduct(Vector3 w); 
    //devuelve el producto interno del vector

    Vector3 negate();
    //devuelve un nuevo el vector negado

    float module(); 
    // devuelve el modulo del vector

    float module2(); 
    // devuelve el modulo al cuadrado del vector

    Vector3 normalize(); 
    //devuelve el vector normalizado del vector

    Vector3 simetric(Vector3 w);
    //devuelve un vector que es el simetrico segun el vector w

    Vector3 crossProduct(Vector3 w);
    // devuelve el producto vectorial con el vector w
};

