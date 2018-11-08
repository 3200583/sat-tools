// Copyright 2017 Hakan Metin - LIP6

#ifndef SATTOOLS_SIMPLIFIER_H_
#define SATTOOLS_SIMPLIFIER_H_

#include <memory>
#include <vector>

#include "sattools/Assignment.h"
#include "sattools/BinaryImplicationGraph.h"
#include "sattools/BreakerManager.h"
#include "sattools/ClauseInjector.h"
#include "sattools/OrderManager.h"
#include "sattools/CNFModel.h"
#include "sattools/Group.h"

namespace sat {

class Simplifier {
 public:
    Simplifier(const Group &group, CNFModel *model, Order *order);
    ~Simplifier();

    void simplify();

 private:
    const Group &_group;
    CNFModel *_model;
    Assignment _assignment;

    std::unique_ptr<BreakerManager> _breaker_manager;
    std::unique_ptr<OrderManager> _order_manager;

    std::unique_ptr<BinaryImplicationGraph> _big;

    bool addUnitClause(Literal unit);
    void extendsOrder(const std::vector<bool>& actives, Literal unit);
};


}  // namespace sat


#endif  // SATTOOLS_SIMPLIFIER_H_
/*
 * Local Variables:
 * mode: c++
 * indent-tabs-mode: nil
 * End:
 */
