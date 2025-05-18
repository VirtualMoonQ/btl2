#include "hcmcampaign.h"
#include <cmath>

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
////////////////////////////////////////////////////////////////////////

// 3.1 Military Units

// 3.2 Vehicles
int Vehicle::getAttackScore() {
    return (static_cast<int>(vehicleType) * 304 + quantity * weight) / 30;
}

std::string Vehicle::str() {
    std::ostringstream oss;
    oss << "Vehicle[vehicleType=" << static_cast<int>(vehicleType)
        << ", quantity=" << quantity
        << ", weight=" << weight
        << ", pos=" << pos.str() << "]";
    return oss.str();
}

// 3.3 Infantry
int Infantry::getAttackScore(){
    int extra = 0;
    int score = 0;
    int q = getQuantity();

    if (infantryType == SPECIALFORCES && sqrt((double)weight) == (int)sqrt((double)weight)){
        extra = 75;
    }
    score = infantryType * 56 + quantity * weight + extra;
    if (computePersonalNumber(score) < 3){
        q -= q/10;
    } 
    else if (computePersonalNumber(score) > 7){
        q += q/5;
    }
    else{
        return score;
    }
    setQuantity(q);
    return getAttackScore();
} 
string Infantry::str(){
    std::ostringstream oss;
    oss << "Infantry[infantryType=" << infantryType
        << ", quantity=" << quantity
        << ", weight=" << weight
        << ", pos=" << pos.str() << "]";
    return oss.str();
}


//3.5 UnitList

bool Infantry::equals(const Unit* other) const {
    const Infantry* i = dynamic_cast<const Infantry*>(other);
    return i && this->infantryType == i->infantryType && this->pos.equals(i->pos);
}


////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
