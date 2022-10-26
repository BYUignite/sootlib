#pragma once

#include "sootModels/psdModels/psdModel.h"
#include "sootDefs.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
/** An implementation of the psdModel interface following the MOMIC model
 *
 *      Associated with enum psdMech:MOMIC
 */
class psdModel_MOMIC : public psdModel {

//////////////// DATA MEMBERS /////////////////////

private:

//////////////// MEMBER FUNCTIONS /////////////////

    ////////////////////////////////////////////////////////////////////////////////
    /** setSourceTerms function
     *
     *      Calculates soot source terms using the method of moments with interpolative
     *      closure (MOMIC). Updates soot, gas, and PAH source terms (where applicable).
     *
     *      NOTE: PAH source terms are updated from within the getNucleationSootRate
     *      function associated with PAH nucleation.
     *
     *      @param  state    \input     thermodynamic state object
     *
     */
    void setSourceTerms(state& state, sourceTermStruct *sourceTerms) const override;

    ////////////////////////////////////////////////////////////////////////////////
    /*! downselectIfNeeded function
     *
     *      Reduces the number of moments to avoid invalid inversion
     *
     *      @param state      \input      thermodynamic state
     *      @param M          \input      vector of moment values
     *
     */
    void downselectIfNeeded(std::vector<double> &M) const;

    ////////////////////////////////////////////////////////////////////////////////
    /*! f_grid function
     *
     *      Calculates the grid function described in Frenklach 2002 MOMIC paper
     *      using lagrange interpolation between whole order moments
     *
     *      @param x     \input x grid point
     *      @param y     \input y grid point
     *      @param M     \input vector of whole order moments
     *
     */
    static double f_grid(int x, int y, const std::vector<double>& M);


    static double MOMICCoagulationRate(const state& state, size_t r, std::vector<double>& M);

    ////////////////////////////////////////////////////////////////////////////////
    /*! lagrangeInterp function
     *
     *      Calculates the Lagrange interpolated value from whole order moments.
     *
     *      @param x_i  \input      x value of desired interpolation
     *      @param x    \input      vector of x values to interpolate amongst
     *      @param y    \input      vector of y values to interpolate amongst
     *      @param y_i  \output     interpolated y value
     *
     */
    static double lagrangeInterp(double x_i, const std::vector<double>& x, const std::vector<double>& y);

    ////////////////////////////////////////////////////////////////////////////////
    /*! MOMIC function
     *
     *      Calculates the desired fractional moment by lagrange interpolation
     *      between whole order moments. Because it uses log moments, it will crash
     *      if any moment is less than or equal to zero.
     *
     *      @param p     \input     desired interpolation value
     *      @param M     \input     vector of whole order moments
     *
     */
    static double MOMIC(double p, const std::vector<double>& M);

//////////////// CONSTRUCTOR FUNCTIONS ////////////

public:

    explicit psdModel_MOMIC(int nVar,
                            nucleationMech N,
                            growthMech G,
                            oxidationMech X,
                            coagulationMech C);

    ~psdModel_MOMIC() override = default;


};
} // namspace soot
