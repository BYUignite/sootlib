#ifndef PSDMODEL_MOMIC_H
#define PSDMODEL_MOMIC_H

#include "src/sootModels/psdModels/psdModel.h"

namespace soot {

    ////////////////////////////////////////////////////////////////////////////////
    /** An implementation of the psdModel interface following the MOMIC model
     *
     *      Associated with enum psdMech:MOMIC
     */
    class psdModel_MOMIC : public psdModel {

    //////////////// DATA MEMBERS /////////////////////

    private:

        size_t nMom = 4;        // default value

        nucleationMech  nucleationMechanism;
        coagulationMech coagulationMechanism;

    //////////////// MEMBER FUNCTIONS /////////////////

    private:

        ////////////////////////////////////////////////////////////////////////////////
        /** getSourceTermsImplementation function
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
        void getSourceTermsImplementation(state& state, sourceTermStruct *sourceTerms) const override;

        ////////////////////////////////////////////////////////////////////////////////
        /*! downselectIfNeeded function
         *
         *      Reduces the number of moments to avoid invalid inversion
         *
         *      @param state      \input      thermodynamic state
         *      @param M          \input      vector of moment values
         *
         */
        static size_t downselectIfNeeded(state& state, std::vector<double>& M);

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


        static double MOMICCoagulationRate(const state& state, size_t r);

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

        explicit psdModel_MOMIC(sourceTermStruct* sourceTerms, int nVar = 2,
                                nucleationMech N = nucleationMech::NONE,
                                growthMech G = growthMech::NONE,
                                oxidationMech X = oxidationMech::NONE,
                                coagulationMech C = coagulationMech::NONE);

        ~psdModel_MOMIC() override = default;


    };
}

#endif //SOOTMODEL_MOMIC_H
