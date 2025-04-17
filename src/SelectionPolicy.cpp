#include "Auxiliary.h"
#include "Plan.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include "Facility.h"
#include <iostream>

using namespace std;

//----------------------------------------------------------------
//NaiveSelection class
//----------------------------------------------------------------
NaiveSelection::NaiveSelection(): lastSelectedIndex(-1) {}

const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    lastSelectedIndex = (lastSelectedIndex+1)%facilitiesOptions.size();
    return facilitiesOptions[lastSelectedIndex];
}

const string NaiveSelection::toString() const {
    return "naive selection";
}

NaiveSelection* NaiveSelection::clone() const {
    NaiveSelection* clone = new NaiveSelection();
    clone->lastSelectedIndex = this->lastSelectedIndex;
    return clone;
}

//----------------------------------------------------------------
//BalancedSelction Class
//----------------------------------------------------------------
BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore)
: LifeQualityScore(LifeQualityScore), EconomyScore (EconomyScore), EnvironmentScore(EnvironmentScore){}

const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    const FacilityType*  ptr = &facilitiesOptions[0];
    int a = ptr->getEconomyScore()+EconomyScore;
    int b = ptr->getLifeQualityScore()+LifeQualityScore;
    int c = ptr->getEnvironmentScore()+EnvironmentScore;
    int diff = max(max(a,b),c) - min(min(a,b),c);
    for (const FacilityType& v:facilitiesOptions)
    {
        int a = LifeQualityScore + v.getLifeQualityScore();
        int b = v.getEconomyScore()+EconomyScore;
        int c = v.getEnvironmentScore()+EnvironmentScore;
        int newDiff = max(max(a,b),c) - min(min(a,b),c);
        if (newDiff < diff)
        {
            diff = newDiff;
            ptr = &v;
        }
    }
    LifeQualityScore += ptr->getLifeQualityScore();
    EconomyScore += ptr->getEconomyScore();
    EnvironmentScore += ptr->getEnvironmentScore();
    return *ptr;
}

const string BalancedSelection::toString() const {
    return "Balanced selection";
}

BalancedSelection* BalancedSelection::clone() const {
    return new BalancedSelection(LifeQualityScore, EconomyScore, EnvironmentScore);
}


//----------------------------------------------------------------
//EconomySelection Class
//----------------------------------------------------------------
EconomySelection::EconomySelection() :lastSelectedIndex(-1){}

const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    lastSelectedIndex = (lastSelectedIndex+1)%facilitiesOptions.size();
    while (facilitiesOptions[lastSelectedIndex].getCategory() != FacilityCategory::ECONOMY)
    {
        lastSelectedIndex = (lastSelectedIndex+1)%facilitiesOptions.size();  
    }
    return facilitiesOptions[lastSelectedIndex];
}

const string EconomySelection::toString() const {
    return "Economy selection";
}


EconomySelection* EconomySelection::clone() const {
    EconomySelection* clone = new EconomySelection();
    clone->lastSelectedIndex = this->lastSelectedIndex;
    return clone;
}

//----------------------------------------------------------------
//SustainabilitySelection Class
//----------------------------------------------------------------
SustainabilitySelection::SustainabilitySelection(): lastSelectedIndex(-1){}

const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    lastSelectedIndex = (lastSelectedIndex+1)%facilitiesOptions.size();
    while (facilitiesOptions[lastSelectedIndex].getCategory() != FacilityCategory::ENVIRONMENT)
    {
        lastSelectedIndex = (lastSelectedIndex+1)%facilitiesOptions.size();  
    }
    return facilitiesOptions[lastSelectedIndex];
}

const string SustainabilitySelection::toString() const {
    return "SustainabilitySelection";
}

SustainabilitySelection* SustainabilitySelection::clone() const {
    SustainabilitySelection* clone = new SustainabilitySelection();
    clone->lastSelectedIndex = this->lastSelectedIndex;
    return clone;
}