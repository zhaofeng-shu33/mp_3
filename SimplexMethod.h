#ifndef SIMPLEXMETHOD_H
#define SIMPLEXMETHOD_H

#include <iostream>
#include "stringtoNum.h"

using namespace Eigen;

VectorXd get_solution(const MatrixXd &m, const VectorXd& BV) {
  VectorXd b = m.bottomRightCorner(BV.size(), 1);
  VectorXd x = VectorXd::Zero(m.cols() - 1);

  for (int i = 0; i < BV.size(); i++)
    x(BV(i) - 1) = b(i);
  return x;
}

void order_vector(VectorXd& BV) {
  int n = BV.size();
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (BV(i) > BV(j)) {
        double tmp = BV(j);
        BV(j) = BV(i);
        BV(i) = tmp;
      }
    }
  }
}

double SimplexMethod(MatrixXd &m, VectorXd &BV, bool verbose=false)
{

  MatrixXd A(m.rows() - 1, m.cols() - 1);
  VectorXd c(A.cols());
  VectorXd b(BV.size());
  if (verbose) {
    std::cout << "SimplexMatrix:\n"
              << m << std::endl;
  }
  for (int i = 0; i < BV.size(); i++)
  {
    if (abs(m(i + 1, BV(i) - 1)) < 1e-4 ) {
      for (int j = i + 2; j < m.rows(); j++)
        if (abs(m(j, BV(i) - 1)) > 1e-4 )
          m.row(i + 1) += m.row(j);
    }
    m.row(i + 1) /= m(i + 1, BV(i) - 1);
    for (int j = 0; j < m.rows(); j++)
      if (j != (i + 1))
        m.row(j) -= m.row(i + 1) * m(j, BV(i) - 1);
  }
  if (verbose) {
    std::cout << "SimplexMatrixInCanonicalForm:\n"
              << m << std::endl;
  }
  while (true)
  {
    A = m.bottomLeftCorner(A.rows(), A.cols());
    c = m.topLeftCorner(1, c.size()).transpose();
    b = m.bottomRightCorner(b.size(), 1);

    double min_value = c(0);
    int Spalte = 0;
    for (int i = 1; i < A.cols(); i++)
      if (c(i) < min_value)
      {
        min_value = c(i);
        Spalte = i;
      }
    if (min_value >= 0)
    {
      double optimal_value = -1 * m(0, m.cols() - 1);
      if (verbose) {
        std::cout << "The optimal condition has been reached.\n";
        std::cout << "The basic variables and their corresponding values are:\n";
        for (int i = 0; i < BV.size(); i++)
          std::cout << BV(i) << ":" << b(i) << "\n";
        std::cout << "The optimal value is: " << optimal_value;
      }
      return optimal_value;
    }

    else
    {
      if (verbose) {
        std::cout << "EnterVariable: " << (Spalte + 1) << "\n";
      }
      int Rahne = 0;
      double maximal = 100;
      for (int i = 0; i < A.rows(); i++)
        if (A(i, Spalte) > 0 && (b(i) / A(i, Spalte) < maximal))
        {
          maximal = b(i) / A(i, Spalte);
          Rahne = i;
        }
      if (maximal == 0)
      {
        throw std::logic_error("The LP problem is unbounded");
      }
      if (verbose) {
        std::cout << "OuterVariable: " << BV(Rahne) << "\n";
      }
      BV(Rahne) = Spalte + 1;
      m.row(Rahne + 1) /= m(Rahne + 1, Spalte);
      for (int i = 0; i < m.rows(); i++)
        if (i != (Rahne + 1))
          m.row(i) -= m.row(Rahne + 1) * m(i, Spalte);
      if (verbose) {
        std::cout << "After transformation, the Simplex Matrix changes to:\n"
                  << m << "\n";
      }
    }
  }
}

VectorXd TwoStageSimplexMethod(MatrixXd &MI, bool verbose=false)
{
  VectorXd BV(MI.rows() - 1);
  MatrixXd Ma(MI.rows(), MI.rows() - 1);
  for (int i = 0; i < MI.rows() - 1; i++)
    Ma(i + 1, i) = 1;
  MatrixXd MIA(MI.rows(), MI.cols() + MI.rows() - 1);
  MIA << MI.topLeftCorner(MI.rows(), MI.cols() - 1), Ma, MI.col(MI.cols() - 1);
  for (int i = 0; i < MI.cols() - 1; i++)
    MIA(0, i) = 0;
  for (int i = MI.cols() - 1; i < MI.cols() + MI.rows() - 2; i++)
  {
    MIA(0, i) = 1;
    BV(i + 1 - MI.cols()) = i + 1;
  }
  SimplexMethod(MIA, BV, verbose); // find initial basic feasible solution first
  order_vector(BV);
  SimplexMethod(MI, BV, verbose);
  return BV;
}

#endif