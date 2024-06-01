#pragma once
#include <iostream>
#include <string>

class GeomObject
{
public:
    std::string name;

};


class Cube : public GeomObject {
private:
    static int IDs;
public:
    Cube() {
        name = "Cube" + std::to_string(IDs);
        IDs++;
    };
};


class Sphere : public GeomObject{
private:
    static int IDs;
public:
    Sphere() {
        name = "Sphere" + std::to_string(IDs);
        IDs++;
    };
};

class Cone : public GeomObject {
private:
    static int IDs;

public:
    Cone() {
        name = "Cone" + std::to_string(IDs);
        IDs++;

    };
};


class Cylinder : public GeomObject {
private:
    static int IDs;
public:
    Cylinder() {
        name = "Cylinder" + std::to_string(IDs);
        IDs++;
    }

};
