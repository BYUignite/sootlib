#ifndef STATIC_H_
#define STATIC_H_

#include <vector>

namespace soot {
////////////////////////////////////////////////////////////////////////////////
/*! Wheeler algorithm for computing weights and abscissas from moments
 *
 *      From Marchisio and Fox (2013) Computational Models for Polydisperse and
 *      Multiphase Systems. Uses eispack function tql2 for eigenvalues and
 *      eigenvectors of a symmetric tridiagonal matrix. If eispack version tql2
 *      is desired, download eispack.hpp and eispack.cpp. LApack's dstev
 *      function to compute eigenvalues and eigenvectors of symmetrical
 *      tridiagonal matrix.
 *
 *      @param m    \input     vector of moments (size = 2N)
 *      @param N    \input     number of quadrature nodes (abscissas)
 *      @param w    \output    weights
 *      @param x    \output    abscissas
 */
void wheeler(const std::vector<double>& m, int N, std::vector<double>& w, std::vector<double>& x) {
    int N2 = N * 2;
    std::vector<std::vector<double> > sigma(N + 1, std::vector<double>(N2, 0.0));
    std::vector<double> a(N, 0.0);
    std::vector<double> b(N, 0.0);
    std::vector<double> eval(N);
    std::vector<double> evec(N * N);
    std::vector<double> j_diag(N);
    std::vector<double> j_ldiag(N);

    for (int l = 0; l <= N2 - 1; l++)
        sigma.at(1).at(l) = m.at(l);

    a.at(0) = m.at(1) / m.at(0);

    for (int k = 1; k <= N - 1; k++) {
        for (int l = k; l <= N2 - k - 1; l++)
            sigma.at(k + 1).at(l) = sigma.at(k).at(l + 1) - a.at(k - 1) * sigma.at(k).at(l) - b.at(k - 1) * sigma.at(k - 1).at(l);
        a.at(k) = -sigma.at(k).at(k) / sigma.at(k).at(k - 1) + sigma.at(k + 1).at(k + 1) / sigma.at(k + 1).at(k);
        b.at(k) = sigma.at(k + 1).at(k) / sigma.at(k).at(k - 1);
    }

    j_diag = a;
    for (int i = 1; i <= N - 1; i++)
        j_ldiag.at(i) = -sqrt(std::abs(b.at(i)));

    for (int i = 0; i < N; i++)
        evec.at(i + N * i) = 1.0;

//    int flag = tql2(N, &j_diag.at(0), &j_ldiag.at(0), &evec.at(0));       // for eispack

    //char VorN = 'V';
    //vector<double> work(2*N-2);
    //int info;
    //dstev_( &VorN, &N, &j_diag.at(0), &j_ldiag.at(1), &evec.at(0), &N, &work.at(0), &info);

    x = j_diag;      // j_diag are now the vector of eigenvalues.

    for (int j = 0; j < N; j++)
        w.at(j) = pow(evec.at(0 + j * N), 2.0) * m.at(0);
}

////////////////////////////////////////////////////////////////////////////////
/*! getWtsAbs function
 *
 *      Calculates weights and abscissas from moments using PD algorithm or
 *      wheeler algorithm.
 *
 *      @param M        \input  vector of moments
 *      @param wts      \input  weights
 *      @param absc     \input  abscissas
 *
 *      Notes:
 *      - Use wheeler over pdalg whenever possible.
 *      - wts and abs DO NOT change size; if we downselect to a smaller number
 *      of moments, the extra values are set at and stay zero
 *      - using w_temp and a_temp means we don't have to resize wts and absc,
 *      which is more convenient when wts and absc are used to reconstitute
 *      moment source terms.
 */
 void getWtsAbs(const std::vector<double>& M, std::vector<double>& weights, std::vector<double>& abscissas) {
    int N = M.size();              // local nMom; may change with moment deselection

    for (int k = 0; k < N; k++) {                // if any moments are zero, return with zero wts and absc
        if (M.at(k) <= 0.0)
            return;
    }

    // FIXME this variable is updated but never used
    bool negs = false;                          // flag for downselecting if there are negative wts/abs

    std::vector<double> w_temp(N / 2, 0.0);
    std::vector<double> a_temp(N / 2, 0.0);

    do {                                        // downselection loop

        negs = false;                           // reset flag

        for (int k = 0; k < N / 2; k++) {             // reinitialize weights and abscissas with zeros
            w_temp.at(k) = 0.0;
            a_temp.at(k) = 0.0;
        }

        if (N == 2) {                           // in 2 moment case, return monodisperse output
            weights.at(0) = M.at(0);
            abscissas.at(0) = M.at(1) / M.at(0);
            return;
        }

        //pdAlg(N,N/2,ymom,wts,absc);           // PD algorithm
        wheeler(M, N / 2, w_temp, a_temp);        // wheeler algorithm

        for (int k = 0; k < N / 2; k++) {
            if (w_temp.at(k) < 0.0 || a_temp.at(k) < 0.0 || a_temp.at(k) > 1.0)
                negs = true;
        }

        if (negs) {                     // if we found negative values
            N = N - 2;                          // downselect to two fewer moments and try again
            w_temp.resize(N / 2);
            a_temp.resize(N / 2);
        }

    }
    while (negs);                     // end of downselection loop

    for (int k = 0; k < w_temp.size(); k++) {   // assign temporary variables to output
        weights.at(k) = w_temp.at(k);
        abscissas.at(k) = a_temp.at(k);
    }
 }

////////////////////////////////////////////////////////////////////////////////
/** Mk function
*
*  calculates fractional moments from weights and abscissas.
*
*  @param exp  \input  fractional moment to compute, corresponds to exponent
*  @param wts  \input  weights
*  @param absc \input  abscissas
*  @param Mk   \output fractional moment value
*/
[[nodiscard]] double Mk(double exp, const std::vector<double>& wts, const std::vector<double>& absc) {
    double Mk = 0;

    for (int k = 0; k < wts.size() / 2; k++) {
        if (wts.at(k) == 0 || absc.at(k) == 0)
            return 0;
        else
            Mk += wts.at(k) * pow(absc.at(k), exp);
    }

    return Mk;
}
}

#endif //STATIC_H_
