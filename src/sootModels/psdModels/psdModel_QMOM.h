#pragma once

#include "psdModel.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
/** An implementation of the psdModel interface following the QMOM model
 *
 *      Associated with enum psdMech:QMOM
 */
class psdModel_QMOM : public psdModel {

//////////////// DATA MEMBERS /////////////////////

public:

    nucleationMech nucleationMechanism;

//////////////// MEMBER FUNCTIONS /////////////////

private:

    ////////////////////////////////////////////////////////////////////////////////
    /** getSourceTermsImplementation function
     *
     *      Calculates soot source terms using quadrature method of moments (QMOM).
     *      Updates soot, gas, and PAH source terms (where applicable).
     *
     *      NOTE: PAH source terms are updated from within the getNucleationSootRate
     *      function associated with PAH nucleation.
     *
     *      @param  state    \input     thermodynamic state object
     *
     */
    void getSourceTermsImplementation(state& state, sourceTermStruct *sourceTerms) const override;

    ////////////////////////////////////////////////////////////////////////////////
    /*! Wheeler algorithm for computing weights and abscissas from moments
     *
     *      From Marchisio and Fox (2013) Computational Models for Polydisperse and
     *      Multiphase Systems. Uses eispack function tql2 for eigenvalues and
     *      eigenvectors of a symmetric tridiagonal matrix. If eispack version tql2
     *      is desired, download eispack.hpp and eispack.cc. LApack's dstev
     *      function to compute eigenvalues and eigenvectors of symmetrical
     *      tridiagonal matrix.
     *
     *      @param m    \input     vector of moments (size = 2N)
     *      @param N    \input     number of quadrature nodes (abscissas)
     *      @param w    \output    weights
     *      @param x    \output    abscissas
     */
    static void wheeler(const std::vector<double>& m, size_t N, std::vector<double>& w, std::vector<double>& x);

    ////////////////////////////////////////////////////////////////////////////////
    /*! getWtsAbs function
     *
     *      Calculates weights and abscissas from moments using wheeler algorithm.
     *
     *      @param M        \input      vector of moments
     *      @param wts      \input      weights
     *      @param absc     \input      abscissas
     *
     *      NOTE: wts and absc variables DO NOT change size during downselection;
     *      instead, the extra values are set to zero. This is more convenient than
     *      resizing when wts and absc are used to reconstitute moment source terms.
     */
    static void getWtsAbs(const std::vector<double>& M, std::vector<double>& weights, std::vector<double>& abscissas);

    ////////////////////////////////////////////////////////////////////////////////
    /** Mk function (QMOM)
    *
    *       calculates fractional moments from weights and abscissas.
    *
    *       @param exp      \input      fractional moment to compute; corresponds to exponent
    *       @param wts      \input      weights
    *       @param absc     \input      abscissas
    *       @param Mk       \output     fractional moment value
    */
    static double Mk(double exp, const std::vector<double>& wts, const std::vector<double>& absc);

//////////////// CONSTRUCTOR ////////////

public:

    explicit psdModel_QMOM(sourceTermStruct* sourceTerms, int nVar = 4,
                           nucleationMech N = nucleationMech::NONE,
                           growthMech G = growthMech::NONE,
                           oxidationMech X = oxidationMech::NONE,
                           coagulationMech C = coagulationMech::NONE);

    ~psdModel_QMOM() override = default;

};
} // namespace soot
