#include "Auxiliary.h"
#include "Plan.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include "Facility.h"
#include <string>
#include <iostream>

using namespace std;

//--------------------------------------------------------------
//FacilityType class
//--------------------------------------------------------------
FacilityType::FacilityType(
    const string &name,
    const FacilityCategory category,
    const int price,
    const int lifeQuality_score,
    const int economy_score,
    const int environment_score)
    : name(name),
      category(category),
      price(price),
      lifeQuality_score(lifeQuality_score),
      economy_score(economy_score),
      environment_score(environment_score){}
     
FacilityType::FacilityType(const FacilityType &other)
        : name(other.name),
          category(other.category),
          price(other.price),
          lifeQuality_score(other.lifeQuality_score), 
          economy_score(other.economy_score),
          environment_score(other.environment_score) {}

FacilityType& FacilityType::operator=(const FacilityType &other) {
        if (this != &other) 
        {
            const_cast<string &>(name) = other.name; 
            const_cast<FacilityCategory &>(category) = other.category;
            const_cast<int &>(price) = other.price;
            const_cast<int &>(lifeQuality_score) = other.lifeQuality_score;
            const_cast<int &>(economy_score) = other.economy_score;
            const_cast<int &>(environment_score) = other.environment_score;
        }
        return *this;
}

FacilityType::FacilityType(FacilityType &&other) noexcept
        : name(move(other.name)), 
          category(other.category), 
          price(other.price),
          lifeQuality_score(other.lifeQuality_score), 
          economy_score(other.economy_score),
          environment_score(other.environment_score) {}

FacilityType& FacilityType::operator=(FacilityType &&other) noexcept {
        if (this != &other) {
            const_cast<string &>(name) = move(other.name); 
            const_cast<FacilityCategory &>(category) = other.category;
            const_cast<int &>(price) = other.price;
            const_cast<int &>(lifeQuality_score) = other.lifeQuality_score;
            const_cast<int &>(economy_score) = other.economy_score;
            const_cast<int &>(environment_score) = other.environment_score;
        }
        return *this;
    }

const string &FacilityType::getName() const
{
    return name;
}

int FacilityType::getCost() const
{
    return price;
}

int FacilityType::getLifeQualityScore() const
{
    return lifeQuality_score;
}

int FacilityType::getEnvironmentScore() const
{
        return environment_score;
}

int FacilityType::getEconomyScore() const
{
        return economy_score;
}

FacilityCategory FacilityType::getCategory() const
{
    return category;
}

//--------------------------------------------------------------
//Facility class
//--------------------------------------------------------------
Facility::Facility(
    const string &name,
    const string &settlementName,
    const FacilityCategory category,
    const int price,
    const int lifeQuality_score,
    const int economy_score,
    const int environment_score)
    : FacilityType(name, category, price, lifeQuality_score, economy_score, environment_score),
      settlementName(settlementName),
      status(FacilityStatus::UNDER_CONSTRUCTIONS),
      timeLeft(price){}

       
Facility::Facility (const FacilityType &type, const string &settlementName):
    FacilityType(type),
    settlementName(settlementName),
    status(FacilityStatus::UNDER_CONSTRUCTIONS),
    timeLeft(type.getCost()) {}

Facility::Facility(const Facility& other)
    : FacilityType(other),
      settlementName(other.settlementName),
      status(other.status),
      timeLeft(other.timeLeft) {}

Facility& Facility::operator=(const Facility &other) {
    if (this != &other) 
    {
        FacilityType::operator=(other); 
        const_cast<string &>(settlementName) = other.settlementName; 
        status = other.status;
        timeLeft = other.timeLeft;
    }
    return *this;
}
Facility::Facility(Facility &&other) noexcept
    : FacilityType(move(other)), 
      settlementName(move(other.settlementName)),
      status(other.status), 
      timeLeft(other.timeLeft) {}

Facility& Facility::operator=(Facility &&other) noexcept {
    if (this != &other) 
    {
        FacilityType::operator=(move(other)); 
        const_cast<string &>(settlementName) = move(other.settlementName); 
        status = other.status;
        timeLeft = other.timeLeft;
    }
    return *this;
}

const string &Facility::getSettlementName() const
{
    return this->settlementName;
}
     
const int Facility::getTimeLeft() const
{
    const int retTimeLeft = this->timeLeft;
    return retTimeLeft;
}
        
FacilityStatus Facility::step()
{
    if (timeLeft==1)
    {
        status = FacilityStatus::OPERATIONAL;
    }
    timeLeft--;
    return status;
}


void Facility::setStatus(FacilityStatus status)
{
    status=status;
}

const FacilityStatus& Facility::getStatus() const
{
    return status;
}

Facility* Facility::clone() const {
    Facility* a = new Facility(this->getName(), 
    this->getSettlementName(),
    this->getCategory(),
    this->getCost(),
    this->getLifeQualityScore(),
    this->getEconomyScore(),
    this->getEnvironmentScore());
    a->setTimeLeft(this->timeLeft);
    return a;
}

void Facility::setTimeLeft(int time) {
    timeLeft = time;
}
        
const string Facility::toString() const
{
    return  "settlement: " + getSettlementName() + ", faciility: " + getName() + ", price: " + std::to_string(getCost()) + ", time left: " + std::to_string(getTimeLeft()) + ", life quality score: " + std::to_string(getLifeQualityScore())
    + ", economy score: " + std::to_string(getEconomyScore()) + ", environment score: " + std::to_string(getEnvironmentScore());
}
        







