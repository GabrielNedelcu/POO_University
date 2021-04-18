#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>

class Point {
protected:
    std::vector<double> mCoordinates;
    double mDistance;
    friend class Point2D;
    friend class Point3D;
    friend class Point4D;

public:
    virtual void print() = 0;
    virtual void calculateDistance() = 0;
    virtual Point* add (Point* pPoint) = 0;
    virtual Point* multiply (Point* pPoint) = 0;

    double getDistance() {
        return mDistance;
    }

    unsigned long int getSize() {
        return mCoordinates.size();
    }

};

class Point2D : public Point {
public:
    Point2D(double pR, double pI) {
        mCoordinates.push_back(pR);
        mCoordinates.push_back(pI);
    }

    Point2D() {
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
        mDistance = 0;
    }

    void print() {
        if (mCoordinates.at(0) < 0)
            std::cout << std::fixed << std::setprecision(3) << mCoordinates.at(0);
        else
            std::cout << std::fixed << std::setprecision(3) << mCoordinates.at(0);
        if (mCoordinates.at(1) < 0)
            std::cout << std::fixed << std::setprecision(3) << mCoordinates.at(1) << "i";
        else
            std::cout << "+" << std::fixed << std::setprecision(3) << mCoordinates.at(1) << "i";
    }

    void calculateDistance() {
        double sum;
        double prod;
        double root;

        sum = ( mCoordinates.at(0) + mCoordinates.at(1) ) / 2;
        if (sum < 0) sum *= -1;
        prod = ( mCoordinates.at(0) * mCoordinates.at(1) );
        if (prod < 0) prod *= -1;
        root = std::sqrt(prod);

        mDistance = sum + root;
    }

    Point* add (Point* pPoint) {

        double tmpR;
        double tmpI;


        tmpR = mCoordinates.at(0) + pPoint->mCoordinates.at(0);
        tmpI = mCoordinates.at(1) + pPoint->mCoordinates.at(1);

        Point* newPoint = new Point2D(tmpR, tmpI);

        return newPoint;
    }

    Point* multiply (Point* pPoint) {
        double tmpR;
        double tmpI;

        tmpR = mCoordinates.at(0) * pPoint->mCoordinates.at(0) - mCoordinates.at(1) * pPoint->mCoordinates.at(1);
        tmpI = mCoordinates.at(0) * pPoint->mCoordinates.at(1) + mCoordinates.at(1) * pPoint->mCoordinates.at(0);

        Point* newPoint = new Point2D(tmpR, tmpI);

        return newPoint;
    }
};


class Point3D : public Point {
public:
    Point3D(double pR, double pI,double pJ) {
        mCoordinates.push_back(pR);
        mCoordinates.push_back(pI);
        mCoordinates.push_back(pJ);
    }

    Point3D() {
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
        mDistance = 0;
    }

    void print() {

        std::cout << std::fixed << std::setprecision(3) << mCoordinates.at(0);
        if (mCoordinates.at(1) < 0)
            std::cout << std::fixed << std::setprecision(3) << mCoordinates.at(1) << "i";
        else
            std::cout << "+" << std::fixed << std::setprecision(3) << mCoordinates.at(1) << "i";
        if (mCoordinates.at(2) < 0)
            std::cout << std::fixed << std::setprecision(3) << mCoordinates.at(2) << "j";
        else
            std::cout << "+" << std::fixed << std::setprecision(3) << mCoordinates.at(2) << "j";
    }

    void calculateDistance() {
        double sum;
        double prod;
        double root;

        sum = ( mCoordinates.at(0) + mCoordinates.at(1) + mCoordinates.at(2) ) / 3;
        if (sum < 0) sum *= -1;
        prod = ( mCoordinates.at(0) * mCoordinates.at(1) * mCoordinates.at(2) );
        if (prod < 0) prod *= -1;
        root = std::cbrt(prod);

        mDistance = sum + root;
    }

    Point* add (Point* pPoint) {
        double tmpR;
        double tmpI;
        double tmpJ;

        if (pPoint -> getSize() >= 3) {
            tmpR = mCoordinates.at(0) + pPoint->mCoordinates.at(0);
            tmpI = mCoordinates.at(1) + pPoint->mCoordinates.at(1);
            tmpJ = mCoordinates.at(2) + pPoint->mCoordinates.at(2);

        } else if(pPoint -> getSize() == 2) {
            tmpR = mCoordinates.at(0) + pPoint->mCoordinates.at(0);
            tmpI = mCoordinates.at(1) + pPoint->mCoordinates.at(1);
            tmpJ = mCoordinates.at(2);
        }

        Point* newPoint = new Point3D (tmpR, tmpI, tmpJ);

        return newPoint;
    }


    Point* multiply (Point* pPoint) {
        double tmpR;
        double tmpI;
        double tmpJ;

        if (pPoint -> getSize() >= 3) {
            tmpR = mCoordinates.at(0) * pPoint->mCoordinates.at(0) - mCoordinates.at(1) * pPoint->mCoordinates.at(1) - mCoordinates.at(2) * pPoint->mCoordinates.at(2);
            tmpI = mCoordinates.at(0) * pPoint->mCoordinates.at(1) + mCoordinates.at(1) * pPoint->mCoordinates.at(0);
            tmpJ = mCoordinates.at(0) * pPoint->mCoordinates.at(2) + mCoordinates.at(2) * pPoint->mCoordinates.at(0);
        } else if(pPoint -> getSize() == 2){
            tmpR = mCoordinates.at(0) * pPoint->mCoordinates.at(0) - mCoordinates.at(1) * pPoint->mCoordinates.at(1);
            tmpI = mCoordinates.at(0) * pPoint->mCoordinates.at(1) + mCoordinates.at(1) * pPoint->mCoordinates.at(0);
            tmpJ = mCoordinates.at(2) * pPoint->mCoordinates.at(0);
        }

        Point* newPoint = new Point3D(tmpR, tmpI, tmpJ);

        return newPoint;
    }

};


class Point4D : public Point {
public:
    Point4D(double pR, double pI, double pJ, double pK) {
        mCoordinates.push_back(pR);
        mCoordinates.push_back(pI);
        mCoordinates.push_back(pJ);
        mCoordinates.push_back(pK);
    }

    Point4D() {
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
        mDistance = 0;
    }

    void print() {
        std::cout << std::fixed << std::setprecision(3) << mCoordinates.at(0);
        if (mCoordinates.at(1) < 0)
            std::cout << std::fixed << std::setprecision(3) << mCoordinates.at(1) << "i";
        else
            std::cout << "+" << std::fixed << std::setprecision(3) << mCoordinates.at(1) << "i";
        if (mCoordinates.at(2) < 0)
            std::cout << std::fixed << std::setprecision(3) << mCoordinates.at(2) << "j";
        else
            std::cout << "+" << std::fixed << std::setprecision(3) << mCoordinates.at(2) << "j";
        if (mCoordinates.at(3) < 0)
            std::cout << std::fixed << std::setprecision(3) << mCoordinates.at(3) << "k";
        else
            std::cout << "+" << std::fixed << std::setprecision(3) << mCoordinates.at(3) << "k";
    }

    void calculateDistance() {
        double sum;
        double prod;
        double root;

        sum = ( mCoordinates.at(0) + mCoordinates.at(1) + mCoordinates.at(2) + mCoordinates.at(3)) / 4;
        if (sum < 0) sum *= -1;
        prod = ( mCoordinates.at(0) * mCoordinates.at(1) * mCoordinates.at(2) * mCoordinates.at(3));
        if (prod < 0) prod *= -1;
        root = std::sqrt(std::sqrt(prod));

        mDistance = sum + root;
    }

    Point* add (Point* pPoint) {
        double tmpR;
        double tmpI;
        double tmpJ;
        double tmpK;

        if (pPoint -> getSize() == 4) {
            tmpR = mCoordinates.at(0) + pPoint->mCoordinates.at(0);
            tmpI = mCoordinates.at(1) + pPoint->mCoordinates.at(1);
            tmpJ = mCoordinates.at(2) + pPoint->mCoordinates.at(2);
            tmpK = mCoordinates.at(3) + pPoint->mCoordinates.at(3);
        } else if(pPoint -> getSize() == 3){
            tmpR = mCoordinates.at(0) + pPoint->mCoordinates.at(0);
            tmpI = mCoordinates.at(1) + pPoint->mCoordinates.at(1);
            tmpJ = mCoordinates.at(2) + pPoint->mCoordinates.at(2);
            tmpK = mCoordinates.at(3);
        } else if (pPoint -> getSize() == 2) {
            tmpR = mCoordinates.at(0) + pPoint->mCoordinates.at(0);
            tmpI = mCoordinates.at(1) + pPoint->mCoordinates.at(1);
            tmpJ = mCoordinates.at(2);
            tmpK = mCoordinates.at(3);
        }

        Point* newPoint = new Point4D (tmpR, tmpI, tmpJ, tmpK);

        return newPoint;
    }

    Point* multiply (Point* pPoint) {
        double tmpR;
        double tmpI;
        double tmpJ;
        double tmpK;

        if (pPoint -> getSize() == 4) {
            tmpR = mCoordinates.at(0) * pPoint->mCoordinates.at(0) - mCoordinates.at(1) * pPoint->mCoordinates.at(1) - mCoordinates.at(2) * pPoint->mCoordinates.at(2) - mCoordinates.at(3) * pPoint->mCoordinates.at(3);
            tmpI = mCoordinates.at(0) * pPoint->mCoordinates.at(1) + mCoordinates.at(1) * pPoint->mCoordinates.at(0);
            tmpJ = mCoordinates.at(0) * pPoint->mCoordinates.at(2) + mCoordinates.at(2) * pPoint->mCoordinates.at(0);
            tmpK = mCoordinates.at(0) * pPoint->mCoordinates.at(3) + mCoordinates.at(3) * pPoint->mCoordinates.at(0);
        } else if (pPoint -> getSize() == 3) {
            tmpR = mCoordinates.at(0) * pPoint->mCoordinates.at(0) - mCoordinates.at(1) * pPoint->mCoordinates.at(1) - mCoordinates.at(2) * pPoint->mCoordinates.at(2);
            tmpI = mCoordinates.at(0) * pPoint->mCoordinates.at(1) + mCoordinates.at(1) * pPoint->mCoordinates.at(0);
            tmpJ = mCoordinates.at(0) * pPoint->mCoordinates.at(2) + mCoordinates.at(2) * pPoint->mCoordinates.at(0);
            tmpK = mCoordinates.at(3) * pPoint->mCoordinates.at(0);
        } else if (pPoint -> getSize() == 2) {
            tmpR = mCoordinates.at(0) * pPoint->mCoordinates.at(0) - mCoordinates.at(1) * pPoint->mCoordinates.at(1);
            tmpI = mCoordinates.at(0) * pPoint->mCoordinates.at(1) + mCoordinates.at(1) * pPoint->mCoordinates.at(0);
            tmpJ = mCoordinates.at(2) * pPoint->mCoordinates.at(0);
            tmpK = mCoordinates.at(3) * pPoint->mCoordinates.at(0);
        }

        Point* newPoint = new Point4D (tmpR, tmpI, tmpJ, tmpK);

        return newPoint;
    }
};

/**
 * Function that reads the input and stores it in points
 * @param points -> contains all the points
 */

void getData(std::vector<Point*> &points) {
    double tmpR;
    double tmpI;
    double tmpJ;
    double tmpK;

    char tmp1;
    char tmp2;

    while (std::scanf("%lf;%lf", &tmpR, &tmpI) != EOF) {
        scanf("%c", &tmp1);
        if (tmp1 == ';') {
            std::scanf("%lf", &tmpJ);
            std::scanf("%c", &tmp2);

            if (tmp2 == ';') {
                std::scanf("%lf", &tmpK);
                points.push_back(new Point4D(tmpR, tmpI, tmpJ, tmpK));
            } else {
                points.push_back(new Point3D(tmpR, tmpI, tmpJ));
            }

        } else {
            points.push_back(new Point2D(tmpR, tmpI));
        }
    }
}

/**
 *
 * @param points -> contains all the points
 * @return the sum of all 2 coordinates points
 */

Point* get2DSum (std::vector<Point*> &points) {
    Point* sum = new Point2D(0,0);

    for (auto point : points) {
        if (point->getSize() == 2)
            sum = sum->add(point);
    }

    return sum;
}

/**
 *
 * @param points -> contains all the points
 * @return the sum of all 3 coordinates points
 */

Point* get3DSum (std::vector<Point*> &points) {
    Point* sum = new Point3D(0,0,0);

    for (auto point : points) {
        if (point->getSize() == 3)
            sum = sum->add(point);
    }

    return sum;
}

/**
 *
 * @param points -> contains all the points
 * @return the sum of all 4 coordinates points
 */

Point* get4DSum (std::vector<Point*> &points) {
    Point* sum = new Point4D(0,0,0,0);

    for (auto point : points) {
        if (point->getSize() == 4)
            sum = sum->add(point);
    }

    return sum;
}

static bool comp (Point* p1, Point* p2) {
    if (p1->getSize() != p2->getSize()) {
        return p1->getSize() > p2->getSize();
    } else {
        return p1->getDistance() > p2->getDistance();
    }

}

void solve (std::vector<Point*> &points, double distance2D, double distance3D, double distance4D) {
    std::vector<Point*> pointsToShow;

    for (auto it : points) {
        it -> calculateDistance();
    }

    for (auto it : points) {
        if (it -> getSize() == 2) {
            if (it -> getDistance() >= distance2D) {
                pointsToShow.push_back(it);
            }
        } else if (it -> getSize() == 3) {
            if (it -> getDistance() >= distance3D) {
                pointsToShow.push_back(it);
            }
        } else if (it -> getSize() == 4) {
            if (it -> getDistance() >= distance4D) {
                pointsToShow.push_back(it);
            }
        }
    }

    std::sort(pointsToShow.begin(), pointsToShow.end(), comp);

    for (auto it : pointsToShow) {
        it -> multiply(it) -> print();

        std::cout << " -> " << it->getDistance() << std::endl;
    }

}

int main() {
    Point* sum2D;
    Point* sum3D;
    Point* sum4D;

    std::vector<Point* > points;

    getData(points);

    sum2D = get2DSum(points);
    sum3D = get3DSum(points);
    sum4D = get4DSum(points);

    sum2D -> calculateDistance();
    sum3D -> calculateDistance();
    sum4D -> calculateDistance();

    solve(points, sum2D -> getDistance(), sum3D -> getDistance(), sum4D -> getDistance());


    return 0;
}