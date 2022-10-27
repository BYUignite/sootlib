#include "sootmodel.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

sootModel::sootModel(size_t            nsoot_,
                     nucleationMech   nucl_,
                     growthMech       grow_,
                     oxidationMech    oxid_,
                     coagulationMech  coag_) : nsoot(nsoot_) {

}
