#include "Action.h" 
#include "Auxiliary.h"
#include "Plan.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include "Facility.h"
#include "Simulation.h"
#include <iostream>
using namespace std;

//----------------------------------------------------------------
//BaseAction Class
// ---------------------------------------------------------------

BaseAction::BaseAction(): errorMsg("Action is not completed yet!"), status(ActionStatus::ERROR) {}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status = ActionStatus::COMPLETED;
}

void BaseAction::error(string errorMsg) {
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg;
}

const string& BaseAction::getErrorMsg() const {
    return errorMsg;
}

//----------------------------------------------------------------
//SimulateStep Class
//----------------------------------------------------------------

SimulateStep::SimulateStep(const int numOfSteps):BaseAction(), numOfSteps(numOfSteps) {
}

void SimulateStep::act(Simulation& simulation) {
    for (int i = 0; i < numOfSteps; i++) 
    {
        simulation.step();
    }
    complete();
}

const string SimulateStep::toString() const {
    return "step " + to_string(numOfSteps);
}

SimulateStep* SimulateStep::clone() const {
    return new SimulateStep(numOfSteps);
}

//----------------------------------------------------------------
//AddPlan Class
//----------------------------------------------------------------

AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy) :BaseAction(), settlementName(settlementName), selectionPolicy(selectionPolicy) {}

void AddPlan::act(Simulation& simulation) {
    if (!(simulation.Simulation::isSettlementExists(settlementName)))
    {
        BaseAction::error("Cannot create this plan");
        cout << "Error: " + BaseAction::getErrorMsg() << endl;
        return;
    } 
    const Settlement& actSet = simulation.Simulation::getSettlement(settlementName);
    if (selectionPolicy == "bal")
    {
        BalancedSelection* balancedSelection = new BalancedSelection(0,0,0);
        simulation.Simulation::addPlan(actSet, balancedSelection);
    }
    else if (selectionPolicy == "nve")
    {
        NaiveSelection* naiveSelection = new NaiveSelection();
        simulation.Simulation::addPlan(actSet, naiveSelection);
    }
    else if (selectionPolicy == "eco")
    {
        EconomySelection* economySelection = new EconomySelection();
        simulation.Simulation::addPlan(actSet, economySelection);
    }
    else if (selectionPolicy == "env")
    {
        SustainabilitySelection* sustainabilitySelection = new SustainabilitySelection();
        simulation.Simulation::addPlan(actSet, sustainabilitySelection);
    }
    else 
    {
        BaseAction::error("Cannot create this plan");
        cout << "Error: " + BaseAction::getErrorMsg() << endl;
    }
    complete();
}

const string AddPlan::toString() const {
    return "plan " + settlementName + " " + selectionPolicy;
}

AddPlan* AddPlan::clone() const {
    return new AddPlan(settlementName, selectionPolicy);
}

//----------------------------------------------------------------
//AddSettlement Class
//----------------------------------------------------------------

AddSettlement::AddSettlement(const string &settlementName, SettlementType settlementType) : BaseAction(), settlementName(settlementName), settlementType(settlementType) {}

void AddSettlement::act(Simulation& simulation) {
    Settlement* toAdd = new Settlement(settlementName, settlementType);
    if (!(simulation.Simulation::addSettlement(toAdd)))
    {
        BaseAction::error("Settlement already exists");
        cout << "Error: " + BaseAction::getErrorMsg() << endl;
        return;
    }
    complete();
}

AddSettlement* AddSettlement::clone() const {
    return new AddSettlement(settlementName, settlementType);
}

const string AddSettlement::toString() const {
    string type;
    if (settlementType == SettlementType::VILLAGE)
    {
        type = "0";
    }
    else if (settlementType == SettlementType::CITY)
    {
        type = "1";
    }
    else if (settlementType == SettlementType::METROPOLIS)
    {
        type = "2";
    }
    return "settlement " + settlementName + " " + type;
}

//----------------------------------------------------------------
//AddFacility Class
//----------------------------------------------------------------

AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore) : 
    BaseAction(), 
    facilityName(facilityName),
    facilityCategory(facilityCategory),
    price(price),
    lifeQualityScore(lifeQualityScore),
    economyScore(economyScore),
    environmentScore(environmentScore) {}

void AddFacility::act(Simulation& simulation) {
    FacilityType facilityType(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore);
    if (!(simulation.Simulation::addFacility(facilityType)))
    {
        BaseAction::error("Facility already exists");
        cout << "Error: " + BaseAction::getErrorMsg() << endl;
        return;
    }
    complete();
}

AddFacility* AddFacility::clone() const {
    return new AddFacility(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore);
}

const string AddFacility::toString() const {
    string cat;
    if (facilityCategory == FacilityCategory::LIFE_QUALITY)
    {
        cat = "0";
    }
    else if (facilityCategory == FacilityCategory::ECONOMY)
    {
        cat = "1";
    }
    else if (facilityCategory == FacilityCategory::ENVIRONMENT)
    {
        cat = "2";
    }
    return "facility " + facilityName + " " + cat + " " + to_string(price) + " " + to_string(lifeQualityScore) + " " + to_string(economyScore) + " " + to_string(environmentScore);
}

//----------------------------------------------------------------
//PrintPlanStatus Class
//----------------------------------------------------------------

PrintPlanStatus::PrintPlanStatus (int planId) : BaseAction(), planId(const_cast<int const&>(planId)) {}

void PrintPlanStatus::act(Simulation& simulation) {
    if (!(simulation.Simulation::isPlanExists(planId))) 
    {
        BaseAction::error("Plan doesn't exist");
        cout << "Error: " + BaseAction::getErrorMsg() << endl;
        return;
    }
    const Plan& plan = simulation.Simulation::getPlan(planId);
    const vector<Facility*> facilities = plan.Plan::getFacilities();
    const vector<Facility*> underConstructionFacilities = plan.Plan::getUnderConstructionFacilities();
    cout << "Plan ID: " << planId << endl;
    cout << "Settlement name: " << plan.Plan::getSettlementName() << endl;
    cout << "Plan status: " << plan.Plan::getStatus() << endl;
    cout << "Selection Policy: " << plan.Plan::getSelectionPolicyName() << endl;
    cout << "Life Quality Score: " << plan.Plan::getlifeQualityScore() << endl;
    cout << "Economy Score: " << plan.Plan::getEconomyScore() << endl;
    cout << "Environmanation Score: " << plan.Plan::getEnvironmentScore() << endl;
    for (Facility* facility : facilities)
    {
        cout << "Facility Name: " << facility->FacilityType::getName() << endl;
        cout << "Facility Status: Operational" << endl;
    }
    for (Facility* facility : underConstructionFacilities)
    {
        cout << "Facility Name: " << facility->FacilityType::getName() << endl;
        cout << "Facility Status: Under Construction" << endl;
    }
    complete();
}

PrintPlanStatus* PrintPlanStatus::clone() const {
    return new PrintPlanStatus(planId);
}

const string PrintPlanStatus::toString() const {
    return "planStatus " + to_string(planId);
}

//----------------------------------------------------------------
//ChangePlanPolicy Class
//----------------------------------------------------------------

ChangePlanPolicy::ChangePlanPolicy(const int planId, const string& newPolicy) : BaseAction(), planId(planId), newPolicy(newPolicy) {}

void ChangePlanPolicy::act(Simulation& simulation) {
    if (!(simulation.Simulation::isPlanExists(planId)))
    {
        BaseAction::error("Cannot change selection policy");
        cout << "Error: " + BaseAction::getErrorMsg() << endl;
        return;
    }
    Plan &plan = simulation.Simulation::getPlan(planId);
    if (plan.Plan::getSelectionPolicyName() == newPolicy)
    {
        BaseAction::error("Selection policy is already " + newPolicy);
        cout << "Error: " + BaseAction::getErrorMsg() << endl;
        return;
    }
    SelectionPolicy* newPolicyObj;
    if (newPolicy == "nve")
    {
        newPolicyObj = new NaiveSelection();
    }
    else if (newPolicy == "eco")
    {
        newPolicyObj = new EconomySelection();
    }
    else if (newPolicy == "env")
    {
        newPolicyObj = new SustainabilitySelection();
    }
    plan.Plan::setSelectionPolicy(newPolicyObj);
    complete();
}

ChangePlanPolicy* ChangePlanPolicy::clone() const {
    return new ChangePlanPolicy(planId, newPolicy);
}

const string ChangePlanPolicy::toString() const { 
    return "changePolicy " + to_string(planId) + " " + newPolicy;
}

//----------------------------------------------------------------
//PrintActionsLog Class
//----------------------------------------------------------------

PrintActionsLog::PrintActionsLog(): BaseAction() {}

void PrintActionsLog::act(Simulation& simulation) {
    int size = simulation.Simulation::getActionsLog().size();
    for (int i = 0 ; i < size ; i++) 
    {
        string status;
        if (simulation.Simulation::getActionsLog()[i]->getStatus() == ActionStatus::COMPLETED)
        {
            status = "COMPLETED";
        }
        else if (simulation.Simulation::getActionsLog()[i]->getStatus() == ActionStatus::ERROR)
        {
            status = "ERROR";
        }
        cout << simulation.Simulation::getActionsLog()[i]->toString() + " " + status << endl;
    }
    complete();
}

PrintActionsLog* PrintActionsLog::clone() const {
    return new PrintActionsLog();
}

const string PrintActionsLog::toString() const {
    return "log";
}

//----------------------------------------------------------------
//Close Class
//----------------------------------------------------------------

Close::Close(): BaseAction() {}

void Close::act(Simulation& simulation) {
    vector<Plan> simPlans = simulation.Simulation::getPlans();
    for (Plan& plan : simPlans)
    {
        cout << "PlanID: " << plan.Plan::getPlanId() << endl;
        cout << "SettlementName: " << plan.Plan::getSettlementName() << endl;
        cout << "LifeQuality_Score: " << plan.Plan::getlifeQualityScore() << endl;
        cout << "Economy_Score: " << plan.Plan::getEconomyScore() << endl;
        cout << "Environment_Score: " << plan.Plan::getEnvironmentScore() << endl;
    }
    simulation.Simulation::close();
    complete();
}

Close* Close::clone() const {
    return new Close();
}

const string Close::toString() const {
    return "close";
}

//----------------------------------------------------------------
//BackupSimulation Class
//----------------------------------------------------------------

BackupSimulation::BackupSimulation(): BaseAction() {}

void BackupSimulation::act(Simulation &simulation) {
    extern Simulation* backup;
    if (backup != nullptr)
    {
        delete backup;
    }
    backup = new Simulation(simulation);
    complete();                                                                                 
}

BackupSimulation* BackupSimulation::clone() const {
    return new BackupSimulation();
}

const string BackupSimulation::toString() const {
    return "backup";
}

//----------------------------------------------------------------
//RestoreSimulation Class
//----------------------------------------------------------------

RestoreSimulation::RestoreSimulation(): BaseAction() {}

void RestoreSimulation::act(Simulation &simulation) {
    extern Simulation* backup;
    if (backup == nullptr)
    {
        BaseAction::error("No backup available");
        cout << "Error: " + BaseAction::getErrorMsg() << endl;
        return;
    }
    simulation = *backup;
    complete();
}

RestoreSimulation* RestoreSimulation::clone() const {
    return new RestoreSimulation();
}

const string RestoreSimulation::toString() const {
    return "restore";
}