#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

enum class FacilityStatus {
    UNDER_CONSTRUCTIONS,
    OPERATIONAL,
};

enum class FacilityCategory {
    LIFE_QUALITY,
    ECONOMY,
    ENVIRONMENT,
};


class FacilityType {
    public:
        FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score);
        virtual ~FacilityType() = default; // Destructor
        FacilityType(const FacilityType &other); // Copy constructor
        FacilityType& operator=(const FacilityType& other); // Assignment operator
        FacilityType(FacilityType &&other) noexcept; // Move constructor
        FacilityType& operator=(FacilityType&& other) noexcept; // Move assignment operator
        const string &getName() const;
        int getCost() const;
        int getLifeQualityScore() const;
        int getEnvironmentScore() const;
        int getEconomyScore() const;
        FacilityCategory getCategory() const;

    protected:
        const string name;
        const FacilityCategory category;
        const int price;
        const int lifeQuality_score;
        const int economy_score;
        const int environment_score;
};



class Facility: public FacilityType {

    public:
        Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score);
        Facility(const FacilityType &type, const string &settlementName);
        Facility(const Facility &other); // Copy constructor
        Facility &operator=(const Facility &other); // Assignment operator
        Facility(Facility &&other) noexcept; // Move constructor
        Facility &operator=(Facility &&other) noexcept; // Move assignment operator
        virtual ~Facility() override = default;
        const string &getSettlementName() const;
        const int getTimeLeft() const;
        FacilityStatus step();
        void setStatus(FacilityStatus status);
        const FacilityStatus& getStatus() const;
        Facility* clone() const;
        void setTimeLeft(int time);
        const string toString() const;

    private:
        const string settlementName;
        FacilityStatus status;
        int timeLeft;
};