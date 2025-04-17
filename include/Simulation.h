#pragma once
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;

class Simulation {
    public:
        Simulation(const string &configFilePath);
        Simulation(Simulation&& other);
        Simulation(Simulation& other);
        Simulation& operator=(Simulation&& other);
        Simulation& operator=(Simulation& other);
        virtual ~Simulation();
        void start();
        void addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy);
        void addAction(BaseAction *action);
        bool addSettlement(Settlement *settlement);
        bool addFacility(FacilityType facility);
        bool isSettlementExists(const string &settlementName);
        Settlement* findSettlement(const string st);
        bool isPlanExists(const int planID);
        Settlement &getSettlement(const string &settlementName);
        Plan &getPlan(const int planID);
        vector<BaseAction*> &getActionsLog();
        vector<Plan> &getPlans();
        void step();
        void close();
        void open();

    private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement*> settlements;
        vector<FacilityType> facilitiesOptions;

};

