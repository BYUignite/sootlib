#ifndef PSDMODEL_MONO_H
#define PSDMODEL_MONO_H

#include "psdModel.h"

namespace soot {

    /**
     *  An implementation of the psdModel interface following the MONO model
     *
     *  Associated with enum psdMech:MONO
     */
    class psdModel_MONO : public psdModel {

    //////////////// DATA MEMBERS /////////////////////

    private:

        size_t nMom;

    //////////////// MEMBER FUNCTIONS /////////////////

    private:

        /**
         * source terms calculation function required by psdModel
         *
         * @param state contains soot and gas state data
         * @param out pointer to an out stream for debugging purposes, can be null
         * @return source terms object with computer values
         */
        sourceTermStruct getSourceTermsImplementation(state& state, std::ostream* out) const override;

        /**
         * throws exceptions if the state object is in an illegal state to calculate source terms required by psdModel
         *
         * @param state
         */
        void checkState(const state& state) const override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

        psdModel_MONO(size_t n);
        ~psdModel_MONO() override = default;

    };
}

#endif //PSDMODEL_MONO_H
