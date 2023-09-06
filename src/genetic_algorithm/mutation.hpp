#ifndef AG_MUTATION_HPP_
#define AG_MUTATION_HPP_

#include <vector>

namespace ga {

void mutateBitFlip(std::vector<bool> &chromosome, float mutationRate);

};

#endif