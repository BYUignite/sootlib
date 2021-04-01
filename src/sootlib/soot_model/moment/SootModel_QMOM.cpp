/**
 * @file SootModel_QMOM.cpp
 * Source file for class SootModel_QMOM
 */

#include "SootModel_QMOM.h"
#include "lib/eispack/eispack.h"

using namespace std;
using namespace soot;

SootModel_QMOM::SootModel_QMOM(unique_ptr<CoagulationModel> coagulationModel,
                               unique_ptr<GrowthModel> growthModel,
                               unique_ptr<NucleationModel> nucleationModel,
                               unique_ptr<OxidationModel> oxidationModel)
    : SootModel_Base(move(coagulationModel),
                     move(growthModel),
                     move(nucleationModel),
                     move(oxidationModel)) {}

SootModel_QMOM* SootModel_QMOM::getInstance(unique_ptr<CoagulationModel> coagulationModel,
                                            unique_ptr<GrowthModel> growthModel,
                                            unique_ptr<NucleationModel> nucleationModel,
                                            unique_ptr<OxidationModel> oxidationModel) {

    return new SootModel_QMOM(move(coagulationModel),
                              move(growthModel),
                              move(nucleationModel),
                              move(oxidationModel));
}

////////////////////////////////////////////////////////////////////////////////
/** getSourceTerms function
 *  
 *      Calculates soot source terms using quadrature method of momdents
 *      (QMOM). Returns soot, gas, and PAH source terms (where applicable). 
 *
 *      @param  state    \input gas/soot state (?)
 *
 */

SourceTerms SootModel_QMOM::getSourceTerms(MomentState& state) const {

    MassRateRatios massRateRatios;

    int nMom = state.getNumMoments();
    vector<double> M(nMom, 0.0);
    vector<double> weights = {0};
    vector<double> abscissas = {0};

    //---------- get moments

    //TODO throw error if number of moments is not an even number and at least 2

    for (int k = 0; k < nMom; k++)
        M.at(k) = state.getMoment(k);

    //---------- set weights and abscissas

    getWtsAbs(M, weights, abscissas);           // wheeler algorithms applied here

    for (int i = 0; i < weights.size(); i++) {
        if (weights[i] < 0.0) weights[i] = 0.0;
        if (abscissas[i] < 0.0) abscissas[i] = 0.0;
    }

    //---------- get chemical rates

    const double jNuc = nucleationModel->getNucleationRate(state, abscissas, weights, massRateRatios);
    const double kGrw = growthModel->getGrowthRate(state, massRateRatios);
    const double kOxi = oxidationModel->getOxidationRate(state, massRateRatios);
    const double coag = coagulationModel->getCoagulationRate(state, abscissas.at(0), abscissas.at(0));

    //---------- nucleation terms

    vector<double> nucleationSourceM(nMom, 0.0);                        // nucleation source terms for moments
    double mNuc = state.getCMin() * MW_C / Na;                              // mass of a nucleated particle
    for (int k = 0; k < nMom; k++)
        nucleationSourceM[k] = pow(mNuc, k) * jNuc;                          // Nuc_rate = m_nuc^r * jNuc

    //---------- PAH condensation terms

    vector<double> condensationSourceM(nMom, 0.0);                            // PAH condensation source terms
    if (nucleationModel->getMechanism()
        == NucleationMechanism::PAH) {      // do PAH condensation if PAH nucleation is selected
        for (int k = 1; k < nMom;
             k++) {                                         // M0 = 0.0 for condensation by definition
            for (int ii = 0; ii < abscissas.size(); ii++)
                condensationSourceM.at(k) +=
                    coagulationModel->getCoagulationRate(state, state.getMDimer(), abscissas.at(ii))
                        * pow(abscissas.at(ii), k - 1) * weights.at(ii);
            condensationSourceM.at(k) *= state.getDimer() * state.getMDimer() * k;
        }
    }

    //---------- growth terms

    vector<double> growthSourceM(nMom, 0.0);                                      // growth source terms for moments
    double Acoef = M_PI * pow(abs(6.0 / M_PI / state.getRhoSoot()), 2.0 / 3.0);   // Acoef (=) kmol^2/3 / kg^2/3
    for (int k = 1; k < nMom;
         k++)                                                   // M0 = 0.0 for growth by definition
        growthSourceM.at(k) = kGrw * Acoef * k * Mk(k - 1.0 / 3.0, weights, abscissas);                  // kg^k/m3*s

    //---------- oxidation terms

    vector<double> oxidationSourceM(nMom, 0.0);                                   // oxidation source terms
    for (int k = 1; k < nMom;
         k++)                                                   // M0 = 0.0 for oxidation by definition
        oxidationSourceM.at(k) = -kOxi * Acoef * k * Mk(k - 1.0 / 3.0, weights, abscissas);              // kg^k/m3*s

    //---------- coagulation terms

    vector<double>
        coagulationSourceM(nMom, 0.0);                                 // coagulation source terms: initialize to zero!
    for (int k = 0; k < nMom; k++) {
        if (k == 1)
            continue;                                                       // M1 = 0.0 for coagulation by definition
        for (int ii = 1; ii < abscissas.size();
             ii++)                                 // off-diagonal terms (looping half of them) with *2 incorporated
            for (int j = 0; j < ii; j++)
                coagulationSourceM.at(k) +=
                    coagulationModel->getCoagulationRate(state, abscissas[ii], abscissas[j]) * weights[ii] * weights[j]
                        * (k == 0 ? -1.0 : (pow(abscissas[ii] + abscissas[j], k)) - pow(abscissas[ii], k)
                            - pow(abscissas[j], k));
        for (int ii = 0; ii < abscissas.size(); ii++)                                      // diagonal terms
            coagulationSourceM.at(k) +=
                coagulationModel->getCoagulationRate(state, abscissas[ii], abscissas[ii]) * weights[ii] * weights[ii]
                    * (k == 0 ? -0.5 : pow(abscissas[ii], k) * (pow(2, k - 1) - 1));
    }

    //---------- combinine to make source terms

    vector<double> sootSourceTerms(nMom, 0.0);

    for (int k = 0; k < nMom; k++)
        sootSourceTerms.at(k) = (nucleationSourceM[k] + condensationSourceM[k] + growthSourceM[k] + oxidationSourceM[k]
            + coagulationSourceM[k]) / state.getRhoGas();

    //---------- get gas source terms

    map<GasSpecies, double> gasSourceTerms;
    map<size_t, double> PAHSourceTerms;

    // Nucleation
    for (auto it = massRateRatios.nucCond().gasSpeciesBegin(); it != massRateRatios.nucCond().gasSpeciesEnd(); it++)
        gasSourceTerms[it->first] += nucleationSourceM[1] * it->second / state.getRhoGas();
    for (auto it = massRateRatios.nucCond().PAHBegin(); it != massRateRatios.nucCond().PAHEnd(); it++)
        PAHSourceTerms[it->first] += nucleationSourceM[1] * it->second / state.getRhoGas();

    // Growth
    for (auto it = massRateRatios.groOxi().gasSpeciesBegin(); it != massRateRatios.groOxi().gasSpeciesEnd(); it++)
        gasSourceTerms[it->first] += growthSourceM[1] * it->second / state.getRhoGas();

    // Oxidation
    for (auto it = massRateRatios.groOxi().gasSpeciesBegin(); it != massRateRatios.groOxi().gasSpeciesEnd(); it++)
        gasSourceTerms[it->first] += oxidationSourceM[1] * it->second / state.getRhoGas();
    for (auto it = massRateRatios.groOxi().PAHBegin(); it != massRateRatios.groOxi().PAHEnd(); it++)
        PAHSourceTerms[it->first] += oxidationSourceM[1] * it->second / state.getRhoGas();

    // Coagulation - n/a

    return SourceTerms(sootSourceTerms, gasSourceTerms, PAHSourceTerms);
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

void SootModel_QMOM::getWtsAbs(vector<double> M, vector<double>& weights, vector<double>& abscissas) const {

    int N = M.size();              // local nMom; may change with moment deselection

    for (int k = 0; k < N; k++) {                // if any moments are zero, return with zero wts and absc
        if (M[k] <= 0.0)
            return;
    }

    bool negs = false;                          // flag for downselecting if there are negative wts/abs

    vector<double> w_temp(N / 2, 0.0);
    vector<double> a_temp(N / 2, 0.0);

    do {                                        // downselection loop

        negs = false;                           // reset flag

        for (int k = 0; k < N / 2; k++) {             // reinitialize weights and abscissas with zeros
            w_temp[k] = 0.0;
            a_temp[k] = 0.0;
        }

        if (N == 2) {                           // in 2 moment case, return monodisperse output
            weights[0] = M[0];
            abscissas[0] = M[1] / M[0];
            return;
        }

        //pdAlg(N,N/2,ymom,wts,absc);           // PD algorithm
        wheeler(M, N / 2, w_temp, a_temp);        // wheeler algorithm

        for (int k = 0; k < N / 2; k++) {
            if (w_temp[k] < 0.0 || a_temp[k] < 0.0 || a_temp[k] > 1.0)
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
        weights[k] = w_temp[k];
        abscissas[k] = a_temp[k];
    }

}

////////////////////////////////////////////////////////////////////////////////
/* Wheeler algorithm for computing weights and abscissas from moments
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

void SootModel_QMOM::wheeler(const vector<double>& m, int N, vector<double>& w, vector<double>& x) const {

    int N2 = N * 2;
    vector<vector<double> > sigma(N + 1, vector<double>(N2, 0.0));
    vector<double> a(N, 0.0);
    vector<double> b(N, 0.0);
    vector<double> eval(N);
    vector<double> evec(N * N);
    vector<double> j_diag(N);
    vector<double> j_ldiag(N);

    for (int l = 0; l <= N2 - 1; l++)
        sigma[1][l] = m[l];

    a[0] = m[1] / m[0];

    for (int k = 1; k <= N - 1; k++) {
        for (int l = k; l <= N2 - k - 1; l++)
            sigma[k + 1][l] = sigma[k][l + 1] - a[k - 1] * sigma[k][l] - b[k - 1] * sigma[k - 1][l];
        a[k] = -sigma[k][k] / sigma[k][k - 1] + sigma[k + 1][k + 1] / sigma[k + 1][k];
        b[k] = sigma[k + 1][k] / sigma[k][k - 1];
    }

    j_diag = a;
    for (int i = 1; i <= N - 1; i++)
        j_ldiag[i] = -sqrt(abs(b[i]));

    for (int i = 0; i < N; i++)
        evec[i + N * i] = 1.0;

    int flag = tql2(N, &j_diag[0], &j_ldiag[0], &evec[0]);       // for eispack

    //char VorN = 'V';
    //vector<double> work(2*N-2);
    //int info;
    //dstev_( &VorN, &N, &j_diag[0], &j_ldiag[1], &evec[0], &N, &work[0], &info);

    x = j_diag;      // j_diag are now the vector of eigenvalues.

    for (int j = 0; j < N; j++)
        w[j] = pow(evec[0 + j * N], 2.0) * m[0];

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

double SootModel_QMOM::Mk(double exp, vector<double> wts, vector<double> absc) const {

    double Mk = 0;

    for (int k = 0; k < wts.size() / 2; k++) {
        if (wts[k] == 0 || absc[k] == 0)
            return 0;
        else
            Mk += wts[k] * pow(absc[k], exp);
    }

    return Mk;
}
