// Copyright 2017 Hakan Metin - LIP6

#ifndef SATTOOLS_LITERALGRAPHNODEADAPTOR_H_
#define SATTOOLS_LITERALGRAPHNODEADAPTOR_H_

#include "sattools/CNFModel.h"
#include "sattools/Literal.h"
#include "sattools/Logging.h"

namespace sat {

class LiteralGraphNodeAdaptor {
 public:
    explicit LiteralGraphNodeAdaptor(unsigned int num_vars) :
        _num_vars(num_vars) {}
    virtual ~LiteralGraphNodeAdaptor() {}

    virtual unsigned int literalToNode(const Literal& literal) const = 0;
    virtual LiteralIndex nodeToLiteral(unsigned int node) const = 0;

 protected:
    unsigned int _num_vars;
};

class ConsecutiveLiteralGraphNodeAdaptor: public LiteralGraphNodeAdaptor {
 public:
    explicit ConsecutiveLiteralGraphNodeAdaptor(unsigned int num_vars) :
        LiteralGraphNodeAdaptor(num_vars) {}
    ~ConsecutiveLiteralGraphNodeAdaptor() override {}

    unsigned int literalToNode(const Literal& literal) const override {
        return literal.index().value() + 1;
    }

    LiteralIndex nodeToLiteral(unsigned int node) const override {
        if (node > 0 && node <= 2 * _num_vars)
            return LiteralIndex(node - 1);
        else
            return kNoLiteralIndex;
    }
};


class DoubleLiteralGraphNodeAdaptor: public LiteralGraphNodeAdaptor {
 public:
    explicit DoubleLiteralGraphNodeAdaptor(unsigned int num_vars) :
        LiteralGraphNodeAdaptor(num_vars) {}
    ~DoubleLiteralGraphNodeAdaptor() override {}

    unsigned int literalToNode(const Literal& literal) const override {
        unsigned int v = literal.variable().value();
        if (literal.isPositive())
            return v + 1;
        else
            return _num_vars + v + 1;
    }

    LiteralIndex nodeToLiteral(unsigned int node) const override {
        if (node > 0 && node <= _num_vars)
            return Literal(node).index();
        else if (node > 0 && node <= 2 * _num_vars)
            return Literal(_num_vars - node).index();
        else
            return kNoLiteralIndex;
    }
};


}  // namespace sat


#endif  // SATTOOLS_LITERALGRAPHNODEADAPTOR_H_
/*
 * Local Variables:
 * mode: c++
 * indent-tabs-mode: nil
 * End:
 */
