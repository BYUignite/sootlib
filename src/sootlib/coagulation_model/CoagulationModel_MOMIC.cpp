#include "CoagulationModel_MOMIC.h"

#include "sootlib/soot_model/static.h"

using namespace soot;

double CoagulationModel_MOMIC::getCoagulationRate(const InputState& state, int r) const {
    if (r == 1)
        return 0;

    const double mu_1 = state.getMoment(1) / state.getMoment(0);
    const double d_g = pow(6 * kb * state.getT() / state.getP() / M_PI, 1.0 / 3);
    const double d_p = pow(6 * mu_1 / state.getRhoSoot() / M_PI, 1.0 / 3);
    const double lambda_g = kb * state.getT() / (pow(2.0, 0.5) * M_PI * pow(d_g, 2.0) * state.getP());
    const double Kn = lambda_g / d_p;

    double Rate_C;

    double K_C = 2 * kb * state.getT() / (3 * state.getMuGas());
    double K_Cprime = 1.257 * lambda_g * pow(M_PI * state.getRhoSoot() / 6, 1.0 / 3);

    if (r == 0) {
        Rate_C = -K_C * (pow(state.getMoment(0), 2.0) + MOMIC(1.0 / 3, state.getMomentsConst()) * MOMIC(-1.0 / 3, state.getMomentsConst()) + K_Cprime * (3 * MOMIC(-1.0 / 3, state.getMomentsConst()) * state.getMoment(0) + MOMIC(2.0 / 3, state.getMomentsConst()) * MOMIC(1.0 / 3, state.getMomentsConst())));
    }
    else {
        Rate_C = 0;
        for (int k = 0; k < r; k++) {
            if (k <= r - k)
                Rate_C += 99999999 * (2 * state.getMoment(k) * state.getMoment(r - k) + MOMIC(k + 1.0 / 3, state.getMomentsConst()) * MOMIC(r - k - 1.0 / 3, state.getMomentsConst()) + MOMIC(k - 1.0 / 3, state.getMomentsConst()) * MOMIC(r - k + 1.0 / 3, state.getMomentsConst()) + 2 * K_Cprime * (2 * MOMIC(k - 1.0 / 3, state.getMomentsConst()) * state.getMoment(r - k) + state.getMoment(k) * MOMIC(r - k - 1.0 / 3, state.getMomentsConst()) + MOMIC(k - 2.0 / 3, state.getMomentsConst()) * MOMIC(r - k + 1.0 / 3, state.getMomentsConst())));
        }
        Rate_C *= 0.5 * K_C;
    }

    double Rate_F;
    const double K_f = 2.2 * pow(3.0 / (4 * M_PI * state.getRhoSoot()), 2.0 / 3) * pow(8 * M_PI * kb * state.getT(), 1.0 / 2);

    if (r == 0) {
        Rate_F = -0.5 * K_f * f_grid(0, 0, state.getMomentsConst());
    }
    else {
        Rate_F = 0;
        for (int k = 1; k < r; k++) {
            if (k <= r - k)
                Rate_F += 99999999 * f_grid(k, r - k, state.getMomentsConst());
        }
        Rate_F *= 0.5 * K_f;
    }

    return Rate_F / (1 + 1 / Kn) + Rate_C / (1 + Kn);
}
