#ifndef EQUATION_H
#define EQUATION_H

//#include <pybind11/eigen.h>

#include <vector>
#include <Eigen/Sparse>

#include "math/Props.h"
#include "math/Local.h"
#include "math/Convective.h"


typedef Eigen::Triplet<double> Triplet;
typedef Eigen::SparseMatrix<double, Eigen::RowMajor> Matrix;
typedef Matrix::InnerIterator MatrixIterator;
typedef Eigen::VectorXd Vector;
typedef Eigen::BiCGSTAB<Eigen::SparseMatrix<double>> BiCGSTAB;


class Equation {

public:

    explicit Equation(
            const std::map<std::string, std::variant<int, double>> &params);

    virtual ~Equation() = default;

    void calculateMatrix();

    void calculateFreeVector(const double &conc_in);

    void calculateGuessVector();

    void calculateConc();

    void calcConcIni(const double &concIni);

    void calcTimeVector();

    void forceDirichletBound(const double &concIni);

    void cfdProcedureOneStep(const std::string &boundCond,
                             const double &concThrWall,
                             const double &radius,
                             const double &effRadius,
                             const double &thrLength,
                             const std::vector<double> &volumes,
                             const std::vector<double> &surfaces,
                             const double &dt);

    void cfdProcedure(const std::string &boundCond,
                      const std::vector<double> &volumes,
                      const std::vector<double> &surfaces);


    void calcFlowRate();

    int &dim;

    std::vector<std::vector<double>> conc;
    std::vector<double> timeStepsVec;
    std::map<double, std::vector<double>> concs;

    const std::vector<double> getConc() const;

    const double getFlowRate() const;

    const std::vector<double> getRadCurr() const;

    Props props;
    Local local;
    Convective convective;

    double &time;
    int iCurr;
    int iPrev;

    double flowRate;

    Matrix matrix;

    Vector freeVector;
    Vector guessVector;
    Vector variable;

};


#endif
