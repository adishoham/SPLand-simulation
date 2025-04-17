#include "Auxiliary.h"
#include "Plan.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include "Facility.h"
#include<iostream>
using namespace std;

Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
    plan_id(planId),
    settlement(const_cast<Settlement&>(settlement)),
    selectionPolicy(selectionPolicy),
    status(PlanStatus::AVAILABLE),
    facilities(vector<Facility*>()), 
    underConstruction(vector<Facility*>()),
    facilityOptions(facilityOptions),
    life_quality_score(0), economy_score(0), environment_score(0){}

Plan::Plan(const Plan& other)
  : plan_id(other.getPlanId()),
    settlement(other.settlement),
    selectionPolicy(other.selectionPolicy->clone()),
    status(other.status),
    facilityOptions(other.facilityOptions),
    life_quality_score(other.getlifeQualityScore()),
    economy_score(other.getEconomyScore()),
    environment_score(other.getEnvironmentScore()) {
        for(Facility* ptr : other.facilities)
        {
            facilities.push_back(ptr->clone());
        }
        for(Facility* ptr : other.underConstruction)
        {
            underConstruction.push_back(ptr->clone());
        } 
}


Plan::Plan(const Plan& other, Settlement* set)
: plan_id(other.getPlanId()),
    settlement(*set),
    selectionPolicy(other.selectionPolicy->clone()),
    status(other.status),
    facilityOptions(other.facilityOptions),
    life_quality_score(other.getlifeQualityScore()),
    economy_score(other.getEconomyScore()),
    environment_score(other.getEnvironmentScore()) {
        for(Facility* ptr : other.facilities)
        {
            facilities.push_back(ptr->clone());
        }
        for(Facility* ptr : other.underConstruction)
        {
            underConstruction.push_back(ptr->clone());
        } 
}

Plan& Plan::operator=(const Plan& other) {
    if (this != &other)
    {
        plan_id = other.plan_id;
        const_cast<Settlement&>(settlement) = other.settlement;
        delete selectionPolicy;
        selectionPolicy = other.selectionPolicy->clone();
        for (Facility* facility : facilities)
        {
            delete facility;
        }
        facilities.clear();
        for (const Facility* facility : other.facilities)
        {
            facilities.push_back(facility->clone());
        }   
        for (Facility* facility : underConstruction) 
        {
            delete facility;
        }
        underConstruction.clear();
        for (const Facility* facility : other.underConstruction) {
            underConstruction.push_back(facility->clone());
        }
        
        status = other.status;
        const_cast<vector<FacilityType>&>(facilityOptions) = other.facilityOptions;
        life_quality_score = other.life_quality_score;
        economy_score = other.economy_score;
        environment_score = other.environment_score;
    }
    return *this;
}

Plan::Plan(Plan&& other)
    : plan_id(other.plan_id),
      settlement(move(other.settlement)),
      selectionPolicy(move(other.selectionPolicy)),
      status(other.status),
      facilities(move(other.facilities)),
      underConstruction(move(other.underConstruction)),
      facilityOptions(move(other.facilityOptions)),
      life_quality_score(other.life_quality_score),
      economy_score(other.economy_score),
      environment_score(other.environment_score) {
        other.selectionPolicy = nullptr;
      }

Plan& Plan::operator=(Plan&& other) noexcept {
    if (this != &other) 
    {
        plan_id = other.plan_id;
        const_cast<Settlement&>(settlement) = other.settlement;
        const_cast<vector<FacilityType>&>(facilityOptions) = other.facilityOptions;
        delete selectionPolicy;
        selectionPolicy = other.selectionPolicy;
        other.selectionPolicy = nullptr;
        for (Facility* facility : facilities)
        {
            delete facility;
        }
        facilities = std::move(other.facilities);
        for (Facility* facility : underConstruction)
        {
            delete facility;
        }
        underConstruction = std::move(other.underConstruction);
        status = other.status;
        life_quality_score = other.life_quality_score;
        economy_score = other.economy_score;
        environment_score = other.environment_score;
    }
    return *this;
}

const int Plan::getlifeQualityScore() const {
    return life_quality_score;
}

const int Plan::getEconomyScore() const {
    return economy_score;
}
const int Plan::getEnvironmentScore() const {
    return environment_score;
}

void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy) {
    this->selectionPolicy=selectionPolicy;
}
  
void Plan::step(){
    while (status == PlanStatus::AVAILABLE)
    {
        Facility* facil = new Facility(const_cast<FacilityType&>(selectionPolicy->selectFacility(facilityOptions)), settlement.Settlement::getName());
        underConstruction.push_back(facil);
        if ((settlement.getType() == SettlementType::VILLAGE && underConstruction.size() == 1 ) ||
            (settlement.getType() == SettlementType::CITY && underConstruction.size() == 2) || 
            (settlement.getType() == SettlementType::METROPOLIS && underConstruction.size() == 3))
        {
            status = PlanStatus::BUSY;
        }
    }
    size_t i = 0;
    while (i < underConstruction.size()) 
    {
        Facility* ptr = underConstruction[i];
        if (ptr->step() == FacilityStatus::OPERATIONAL)
        {
            facilities.push_back(ptr);
            underConstruction.erase(underConstruction.begin()+i);
            status = PlanStatus::AVAILABLE;
            life_quality_score += ptr->getLifeQualityScore();
            economy_score += ptr->getEconomyScore();
            environment_score += ptr->getEnvironmentScore();
        }
        else 
        {
            i++;
        }
    }
}
void Plan::printStatus() {
    if (status == PlanStatus::AVAILABLE)
    {
        cout << "Plan ID: " << plan_id << ", Status: Available" << endl;
    }
    else if (status == PlanStatus::BUSY) 
    {
        cout << "Plan ID: " << plan_id << ", Status: Busy" << endl;
    }
}

const string Plan::getStatus() const {
    if (status == PlanStatus::AVAILABLE)
    {
        return "Available";
    }
    else 
    {
        return "Busy";
    }
}

const vector<Facility*>& Plan::getFacilities() const {
    return facilities;
}

const vector<Facility*>& Plan::getUnderConstructionFacilities() const {
    return underConstruction;
}

const string& Plan::getSettlementName() const {
    return settlement.getName();
}

const SettlementType Plan::getSettlementType() const{
    return settlement.getType();
}


const string Plan::getSelectionPolicyName() const {
    return selectionPolicy->toString();
}

void Plan::addFacility(Facility* facility) {
    facilities.push_back(facility);
}

const string Plan::toString() const {
    string str;
    str += "this is plan number " + to_string(plan_id) + "for the settlement " + settlement.getName() + "\n";
    str += "Current status: ";
    if (status == PlanStatus::AVAILABLE)
    {
        str += "Available\n";
    }
    else if (status == PlanStatus::BUSY) 
    {
        str += "Busy\n";
    }
    return str;
}

const int Plan::getPlanId() const {
    return plan_id;
}

Plan::~Plan() {
    for (Facility* facil : facilities)
    {
        delete facil;
    }
    facilities.clear();
    for (Facility* facil : underConstruction)
    {
        delete facil;
    }
    underConstruction.clear();
    delete selectionPolicy;
}