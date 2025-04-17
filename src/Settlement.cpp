#include "Auxiliary.h"
#include "Plan.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include "Facility.h"

Settlement::Settlement(const string &name, SettlementType type): name(name), type(type) {}

Settlement::Settlement(const Settlement &other): name(other.name), type(other.type) {}

Settlement &Settlement::operator=(const Settlement &other) {
    if (this != &other) 
    {
        const_cast<string&>(name) = other.name; 
        type = other.type;
    }
    return *this;
}

const string &Settlement::getName() const {
    return name;
}

SettlementType Settlement::getType() const {
    return type;
}

const string Settlement::toString() const {
    string ret = name;
    if (type == SettlementType::VILLAGE)
    {
        ret += "is a village";
    }
    else if (type == SettlementType::CITY)
    {
        ret += "is a city";
    }
    else if (type == SettlementType::METROPOLIS)
    {
        ret += "is a metropolis";
    }
    return ret;
}