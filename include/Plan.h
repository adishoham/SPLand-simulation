#pragma once
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
using std::vector;

enum class PlanStatus {
    AVAILABLE,
    BUSY,
};

class Plan {
    public:
        Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions);
        Plan(const Plan& other);
        Plan(const Plan& other, Settlement* set);
        Plan& operator=(const Plan& other);
        Plan(Plan&& other);
        Plan& operator=(Plan&& other) noexcept;
        const int getlifeQualityScore() const;
        const int getEconomyScore() const;
        const int getEnvironmentScore() const;
        void setSelectionPolicy(SelectionPolicy *selectionPolicy);
        void step();
        void printStatus();
        const string getStatus() const;
        const vector<Facility*> &getFacilities() const;
        const vector<Facility*> &getUnderConstructionFacilities() const;
        const string& getSettlementName() const;
        const SettlementType getSettlementType() const;
        const string getSelectionPolicyName() const;
        void addFacility(Facility* facility);
        const string toString() const;
        const int getPlanId() const;
        virtual ~Plan();

    private:
        int plan_id;
        const Settlement &settlement;
        SelectionPolicy *selectionPolicy; //What happens if we change this to a reference?
        PlanStatus status;
        vector<Facility*> facilities;
        vector<Facility*> underConstruction;
        const vector<FacilityType> &facilityOptions;
        int life_quality_score, economy_score, environment_score;
};