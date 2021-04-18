#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>

class Shape{
private:
    std::string mShape;
    double mArea;
    double mPerimeter;

public:
    Shape(std::string pShape, double pArea, double pPerimeter) {
        mShape = pShape;
        mArea = pArea;
        mPerimeter = pPerimeter;
    }

    void print() {
        std::cout << mShape << " " << std::fixed << std::setprecision(6) << mArea << " " << std::fixed << std::setprecision(6) << mPerimeter << '\n';
    }

    double getArea() {
        return mArea;
    }

    double getPerimeter() {
        return mPerimeter;
    }
};

double getAreaSquare(double xDr, double yDr, double xSt, double ySt) {
    double area;
    area = (double)((ySt-yDr)*(ySt-yDr));
    if (area < 0)
        return area * (-1);
    return area;
}

double getAreaRectangle(double xDr, double yDr, double xSt, double ySt) {
    double area;
    area = (double)((ySt-yDr)*(xSt-xDr));
    if (area < 0)
        return area * (-1);
    return area;
}

double getAreaCircle(double radius) {
    return (double)(M_PI * radius * radius);
}

double getPerimeterSquare(double xDr, double yDr, double xSt, double ySt) {
    double perimeter;
    perimeter = (double)(4*(ySt-yDr));
    if (perimeter < 0)
        return perimeter * (-1);
    return perimeter;
}

double getPerimeterRectangle(double xDr, double yDr, double xSt, double ySt) {
    double perimeter;
    perimeter = (double)(2*((ySt-yDr)+(xSt-xDr)));
    if (perimeter < 0)
        return perimeter * (-1);
    return perimeter;
}

double getPerimeterCircle(double radius) {
    return (double)(2 * M_PI * radius);
}

bool cmp(Shape &a, Shape &b) {
    if(a.getArea() != b.getArea()) {
        return (a.getArea() < b.getArea());
    } else {
        return (a.getPerimeter() < b.getPerimeter());
    }
}

bool checkCoordinates(double xDr, double yDr, double xSt, double ySt) {
    if (xDr < -1000 || xDr > 1000 || xSt < -1000 || xSt > 1000) {
        return true;
    }

    if (yDr < -1000 || yDr > 1000 || ySt < -1000 || ySt > 1000) {
        return true;
    }

    return false;
}

int main() {
    int n;
    double min, max;
    std::string line;

    std::string tmpShape;
    double tmpRadius, tmpCenter1, tmpCenter2;
    double tmpXDr, tmpYDr;
    double tmpXSt, tmpYSt;

    std::vector<Shape> shapes;

    std::cin >> n >> min >> max;
    scanf("\n");

    if (min >= max || n < 1 || n > 500) {
        std::cout << "Valoare de intrare invalida" << '\n';
        return 0;
    }

    for (int i = 0; i < n; i++) {
        std::getline(std::cin, line);
        std::istringstream input(line);

        input >> tmpShape;

        if (tmpShape == "cerc") {
            input >> tmpCenter1 >> tmpCenter2 >> tmpRadius;

            if (tmpRadius < 0 || tmpRadius > 1000 || tmpCenter1 < -1000 || tmpCenter1 > 1000 || tmpCenter2 < -1000 || tmpCenter2 > 1000) {
                std::cout << "Valoare de intrare invalida" << '\n';
                return 0;
            }

            shapes.push_back(Shape("cerc", getAreaCircle(tmpRadius), getPerimeterCircle(tmpRadius)));
        } else if (tmpShape == "dreptunghi") {
            input >> tmpXSt >> tmpYSt >> tmpXDr >> tmpYDr;

            if(checkCoordinates(tmpXDr, tmpYDr, tmpXSt, tmpYSt) == true) {
                std::cout << "Valoare de intrare invalida" << '\n';
                return 0;
            }

            shapes.push_back(Shape("dreptunghi", getAreaRectangle(tmpXDr, tmpYDr, tmpXSt, tmpYSt), getPerimeterRectangle(tmpXDr, tmpYDr, tmpXSt, tmpYSt)));
        } else if (tmpShape == "patrat") {
            input >> tmpXSt >> tmpYSt >> tmpXDr >> tmpYDr;

            if(checkCoordinates(tmpXDr, tmpYDr, tmpXSt, tmpYSt) == true) {
                std::cout << "Valoare de intrare invalida" << '\n';
                return 0;
            }

            shapes.push_back(Shape("patrat", getAreaSquare(tmpXDr, tmpYDr, tmpXSt, tmpYSt), getPerimeterSquare(tmpXDr, tmpYDr, tmpXSt, tmpYSt)));
        }
    }

    std::sort(shapes.begin(), shapes.end(), cmp);

    for(auto it : shapes) {
        it.print();
    }

    return 0;
}