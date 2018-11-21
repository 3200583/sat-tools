// Copyright 2017 Hakan Metin

#include "sattools/io/Saucy1Writer.h"

namespace sattools {

bool Saucy1Writer::dump(const std::string &filename, const Group& group) {
    StreamBuffer out(filename, kUncompressedWrite);
    unsigned int num_vars = 0;
    unsigned int num_perms = group.numberOfPermutations();
    std::unique_ptr<LiteralGraphNodeAdaptor> adaptor = nullptr;

    out.write("[\n");
    if (num_perms == 0) {  // Empty Group
        out.write("]\n");
        out.flush();
        return true;
    }

    num_vars = group.permutations()[0]->size();
    adaptor = std::make_unique<DoubleLiteralGraphNodeAdaptor>(num_vars);

    for (unsigned int i = 0; i < num_perms; ++i) {
        const std::unique_ptr<Permutation>& perm = group.permutation(i);
        for (unsigned int c = 0; c < perm->numberOfCycles(); ++c) {
            const Literal last = perm->lastElementInCycle(c);
            out.write("(");
            for (const Literal& literal : perm->cycle(c)) {
                unsigned int node = adaptor->literalToNode(literal);
                out.writeInt(node);
                if (literal != last)
                    out.write(",");
            }
            out.write(")");
        }
        if (i != num_perms-1)
            out.write(",");
        out.write("\n");
    }

    out.write("]\n");
    out.flush();

    return true;
}


bool Saucy1Writer::dump(std::ostream &os, const Group& group) {
    unsigned int num_vars = 0;
    unsigned int num_perms = group.numberOfPermutations();
    std::unique_ptr<LiteralGraphNodeAdaptor> adaptor = nullptr;

    os << "[" << std::endl;
    if (num_perms == 0) {  // Empty Group
        os << "]" << std::endl;
        os.flush();
        return true;
    }

    num_vars = group.permutations()[0]->size();
    adaptor = std::make_unique<DoubleLiteralGraphNodeAdaptor>(num_vars);

    for (unsigned int i = 0; i < num_perms; ++i) {
        const std::unique_ptr<Permutation>& perm = group.permutation(i);
        for (unsigned int c = 0; c < perm->numberOfCycles(); ++c) {
            const Literal last = perm->lastElementInCycle(c);
            os << "(";
            for (const Literal& literal : perm->cycle(c)) {
                unsigned int node = adaptor->literalToNode(literal);
                os << node;
                if (literal != last)
                    os << ",";
            }
            os << ")";
        }
        if (i != num_perms-1)
            os <<",";
        os << std::endl;
    }

    os << "]\n";
    os.flush();

    return true;
}

}  // namespace sat
/*
 * Local Variables:
 * mode: c++
 * indent-tabs-mode: nil
 * End:
 */
