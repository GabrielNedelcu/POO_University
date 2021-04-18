#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>


class Vector {
private:
    uint16_t mDim;
    double* mValues;

public:
    Vector(uint16_t pDim) {
        mDim = pDim;
        mValues = new double[mDim];
    }

    Vector() {
        mDim = 0;
        mValues = new double[0];
    }

    Vector(const Vector& pVector) {
        mDim = pVector.mDim;
        mValues = pVector.mValues;
    }

    Vector operator + (const Vector& pVector) {
        if (mDim == pVector.mDim) {
            Vector sum(mDim);

            for (int i = 0; i < mDim; i++) {
                *(sum.mValues + i) = *(mValues + i) + *(pVector.mValues + i);
            }

            return sum;

        } else {
            return Vector();
        }

    }

    double operator * (const Vector& pVector) {
        double sum = 0.0;
        uint16_t dim = std::min(mDim, pVector.mDim);

        for (int i = 0; i < dim; i++) {
            sum += *(mValues + i) * *(pVector.mValues + i);
        }

        return sum;
    }

    double operator ! () {
        double sum = 0.0;

        for ( int i = 0; i < mDim; i++) {
            sum+= *(mValues + i) * *(mValues + i);
        }

        return std::sqrt(sum);
    }

    Vector operator ^ (const Vector& pVector) {

        if (mDim == pVector.mDim) {

            Vector result(mDim+1);

            if (mDim == 2) {
                *(result.mValues) = 0;
                *(result.mValues + 1) = 0;
                *(result.mValues + 2) = *(mValues) * *(pVector.mValues + 1) - *(mValues + 1) * *(pVector.mValues);
            } else if(mDim == 3) {

                *(result.mValues) = *(mValues+1) * *(pVector.mValues + 2) - *(mValues + 2) * *(pVector.mValues + 1);
                *(result.mValues + 1) = *(mValues) * *(pVector.mValues + 2) - *(mValues + 2) * *(pVector.mValues);
                *(result.mValues + 2) = *(mValues) * *(pVector.mValues + 1) - *(mValues + 1) * *(pVector.mValues);
            } else {
                for (int i = 0; i < mDim; i++) {
                    *(result.mValues + i) = 1;
                }
            }

            return result;

        } else {
            return Vector();
        }

    }

    double getValue(uint16_t poz) {
        return *(mValues + poz);
    }

    void setValue(uint16_t poz, double toSet) {
        *(mValues + poz) = toSet;
    }

    ~Vector() {

    }
};

int main() {
    uint16_t dim1;
    uint16_t dim2;

    std::cin >> dim1 >> dim2;

    Vector a(dim1);
    Vector b(dim2);

    double tmp;

    for (int i = 0; i < dim1; i++) {
        std::cin >> tmp;
        a.setValue(i, tmp);
    }

    for (int i = 0; i < dim2; i++) {
        std::cin >> tmp;
        b.setValue(i, tmp);
    }

    if (dim1 == dim2 && (dim1 == 2 || dim1 == 3)) {
        if(dim1 == 2) {
            Vector aux = a ^ b;

            Vector tmpVector(3);

            tmpVector.setValue(0, a.getValue(0));
            tmpVector.setValue(1, a.getValue(1));
            tmpVector.setValue(2, 0);

            aux = aux + tmpVector;
            double auxModul = aux.operator!();
            for (int i = 0; i < 3; i++) {
                aux.setValue(i, aux.getValue(i) / auxModul);
            }

            double sum = 0.0;
            for (int i = 0; i < 3; i++) {
                sum += aux.getValue(i);
            }

            std::cout << std::fixed << std::setprecision(2) << sum/3;
        } else {
            Vector aux = a ^ b;

            Vector tmpVector(4);

            tmpVector.setValue(0, a.getValue(0));
            tmpVector.setValue(1, a.getValue(1));
            tmpVector.setValue(2, a.getValue(2));

            aux = aux + tmpVector;
            double auxModul = aux.operator!();
            for (int i = 0; i < 3; i++) {
                aux.setValue(i, aux.getValue(i) / auxModul);
            }

            double sum = 0.0;
            for (int i = 0; i < 3; i++) {
                sum += aux.getValue(i);
            }

            std::cout << std::fixed << std::setprecision(2) << sum/3;
        }


    } else if (dim1 != dim2 || ( dim1 == dim2 && dim1 > 3)) {
        double prod = a*b;

        Vector aux(std::max(dim1, dim2));

        for ( int i = 0; i < std::max(dim1, dim2); i++) {
            aux.setValue(i, prod);
        }

        if (dim1 > dim2) {
            aux + a;
        } else {
            aux + b;
        }

        double modul = aux.operator!();
        double sum = 0.0;
        for (int i = 0; i < std::max(dim1, dim2); i++) {
            sum += aux.getValue(i)/modul;
        }

        std::cout << std::fixed << std::setprecision(2) << sum/std::max(dim1, dim2);
    }



    return 0;
}