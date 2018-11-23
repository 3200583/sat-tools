// Copyright 2017 Hakan Metin - LIP6

#include "sattools/Group.h"

namespace sat {

Group::Group() {
}

Group::~Group() {
}

bool Group::addPermutation(std::unique_ptr<Permutation>&& permutation) {
    CHECK_NOTNULL(permutation.get());

    const unsigned int permutation_index = _permutations.size();
    const unsigned int num_cycles = permutation->numberOfCycles();

    if (num_cycles == 0)
        return false;

    if (permutation->isSpurious())
        return false;

    for (unsigned int c = 0; c < num_cycles; ++c) {
        Literal element = permutation->lastElementInCycle(c);

        for (const Literal& image : permutation->cycle(c)) {
            if (image.isPositive()) {
                const int index = image.variable().value();
                _watchers.store(index, permutation_index);
            }
            const BooleanVariable variable = image.variable();
            _symmetric.insert(variable);

            if (element == image.negated())
                _inverting.insert(variable);

            element = image;
        }
    }

    _permutations.emplace_back(permutation.release());

    return true;
}


Watcher<int, int>::Iterator Group::watch(Literal literal) const {
    const int index = literal.variable().value();
    return _watchers.watch(index);
}

Watcher<int, int>::Iterator Group::watch(BooleanVariable var) const {
    const int index = var.value();
    return _watchers.watch(index);
}

std::string Group::debugString() const {
    std::string str;

    unsigned int i = 0;
    for (const std::unique_ptr<Permutation>& permutation : _permutations) {
        if (!str.empty())
            str += '\n';
        str += "[" + std::to_string(i++) + "]: " + permutation->debugString();
    }

    return str;
}

}  // namespace sat


/*
 * Local Variables:
 * mode: c++
 * indent-tabs-mode: nil
 * End:
 */
