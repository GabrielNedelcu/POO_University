#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

class Point {
private:
    double x;
    double y;
    double z;
public:
    Point(){
        x = 0;
        y = 0;
        z = 0;
    }

    Point(double px, double py) {
        x = px;
        y = py;
        z = 0;
    }

    Point(double px, double py, double pz) {
        x = px;
        y = py;
        z = pz;
    }

    double getX() {
        return x;
    }

    double getY() {
        return y;
    }

    double getZ() {
        return z;
    }

    double getAbsoluteValue() {
        return std::sqrt(x*x+y*y+z*z);
    }
};


int main() {
    std::vector<Point> myPoints;
    std::string line;
    std::string tmpLine;
    int n;
    double tmpX;
    double tmpY;
    double tmpZ;
    double xSum;
    double ySum;
    double zSum;

    xSum = 0;
    ySum = 0;
    zSum = 0;

    char tmp;
    while (scanf("%lf;%lf",&tmpX, &tmpY)!=EOF) {
        scanf("%c", &tmp);
        if (tmp == ';') {
            scanf("%lf", &tmpZ);
            xSum += tmpX;
            ySum += tmpY;
            zSum += tmpZ;
            Point tmpPoint(tmpX, tmpY, tmpZ);
            myPoints.push_back(tmpPoint);
        } else {
            xSum += tmpX;
            ySum += tmpY;
            Point tmpPoint(tmpX, tmpY);
            myPoints.push_back(tmpPoint);
        }
    }

    Point sumPoint(xSum, ySum, zSum);

    for(auto it : myPoints) {
        if(it.getAbsoluteValue() > sumPoint.getAbsoluteValue()) {
            if (it.getX() != 0) {
                if (it.getX() < 0) {
                    std::cout << std::fixed << std::setprecision(3) << it.getX() << "i";
                } else {
                    std::cout << std::fixed << std::setprecision(3) << it.getX() << "i";
                }
            }
            if (it.getY() != 0) {
                if (it.getY() < 0) {
                    std::cout << std::fixed << std::setprecision(3) << it.getY() << "j";
                } else {
                    std::cout << std::fixed << std::setprecision(3) << "+" << it.getY() << "j";
                }
            }
               // std::cout << std::fixed << std::setprecision(3) << std::showpos << it.getY() << "j";
            if (it.getZ() != 0) {
                if (it.getZ() < 0) {
                    std::cout << std::fixed << std::setprecision(3) << it.getZ() << "k";
                } else {
                    std::cout << std::fixed << std::setprecision(3) << "+" << it.getZ() << "k";
                }
            }
               // std::cout << std::fixed << std::setprecision(3) << std::showpos << it.getZ() << "k";
            std::cout << std::endl;
        }
    }


    return 0;
}