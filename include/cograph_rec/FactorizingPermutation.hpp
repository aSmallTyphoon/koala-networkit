//
// Created by scales on 25.04.24.
//
#pragma once

#include <list>
#include <set>
#include <unordered_map>
#include <map>
#include <graph/GraphTools.hpp>


#include "cograph_rec/Part.hpp"

namespace Koala {
    class FactorizingPermutation {
    public:
        part *l, *r, *first_part, *last_part;
        element *origin;
        std::vector<element *> E;
        std::list<part *> garbage;

        FactorizingPermutation();

        ~FactorizingPermutation();

        void Check() const;

        void AddPart(part *l, part *r);

        void EraseElement(element *v);

        void ErasePart(part *p);

        void AddElementToPart(part *P, element *v);

        void Rcheck();

        void Lcheck();

        void ShowTheOrder();

    };
}