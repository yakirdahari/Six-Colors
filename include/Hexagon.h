#pragma once

#include "Shape.h"

// to make our code more readable we create a class for each shape
class Hexagon : public Shape
{
public:
    /*--------------------------------*\
   |----------- CONSTRUCTOR ------------|
    \*--------------------------------*/

    Hexagon() : Shape(6) {}

};
