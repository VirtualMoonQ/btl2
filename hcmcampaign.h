/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 2
 * Programming Fundamentals Spring 2025
 * Date: 02.02.2025
 */

// The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_HCM_CAMPAIGN_H_
#define _H_HCM_CAMPAIGN_H_

#include "main.h"
#include <vector>

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class Unit;
class UnitList;
class Army;
class TerrainElement;

class Vehicle;
class Infantry;

class LiberationArmy;
class ARVN;

class Position;

class Road;
class Mountain;
class River;
class Urban;
class Fortification;
class SpecialZone;

class BattleField;

class HCMCampaign;
class Configuration;

enum VehicleType
{
    TRUCK,
    MORTAR,
    ANTIAIRCRAFT,
    ARMOREDCAR,
    APC,
    ARTILLERY,
    TANK
};
enum InfantryType
{
    SNIPER,
    ANTIAIRCRAFTSQUAD,
    MORTARSQUAD,
    ENGINEER,
    SPECIALFORCES,
    REGULARINFANTRY
};



class Position
{
private:
    int r, c;

public:
    Position(int r = 0, int c = 0) : r(r), c(c) {}

    Position(const string &str_pos)
    {
        sscanf(str_pos.c_str(), "(%d,%d)", &r, &c);
    }

    int getRow() const { return r; }
    int getCol() const { return c; }
    void setRow(int r) { this->r = r; }
    void setCol(int c) { this->c = c; }

    string str() const
    {
        ostringstream oss;
        oss << "(" << r << "," << c << ")";
        return oss.str();
    }
    
    bool equals(const Position& other) const {
            return this->c == other.c && this->r == other.r;
        }
};

class Unit
{
protected:
    int quantity, weight;
    Position pos;

public:
    Unit(int quantity, int weight, Position pos)
        : quantity(quantity), weight(weight), pos(pos) {}
    virtual ~Unit() {}
    virtual int getAttackScore() const = 0;
    Position getCurrentPosition() const { return pos; }
    virtual string str() const = 0;
    
    int getQuantity() const { return quantity; }
    void setQuantity(int q) { quantity = q; }
    
    virtual bool equals(const Unit* other) const = 0;  // pure virtual
    virtual void increaseQuantity(int q) { quantity += q; }
    
    virtual Unit* clone() const = 0; // In Unit base class

};


class TerrainElement
{
public:
    TerrainElement();
    ~TerrainElement();
    virtual void getEffect(Army *army) = 0;
};

class BattleField
{
private:
    int n_rows, n_cols;
    // TODO
public:
    BattleField(int n_rows, int n_cols, vector<Position *> arrayForest,
                vector<Position *> arrayRiver, vector<Position *> arrayFortification,
                vector<Position *> arrayUrban, vector<Position *> arraySpecialZone);
    ~BattleField();
};

class HCMCampaign
{
private:
    Configuration *config;
    BattleField *battleField;
    LiberationArmy *liberationArmy;
    ARVN *arvn;

public:
    HCMCampaign(const string &config_file_path);
    void run();
    string printResult();
};

class Vehicle : public Unit
{
private:
    VehicleType vehicleType;
public:
    Vehicle(int quantity, int weight, const Position pos, VehicleType vehicleType): Unit(quantity, weight, pos), vehicleType(vehicleType) {}
    int getAttackScore() const override;
    string str() const override;
    bool equals(const Unit* other) const override {
        const Vehicle* v = dynamic_cast<const Vehicle*>(other);
        return v && this->vehicleType == v->vehicleType && this->pos.equals(v->pos);
    };
    VehicleType getVehicleType(){
        return vehicleType;
    }
    
    Unit* clone() const override {
        return new Vehicle(*this);  // or with custom constructor
    }
};

class Infantry : public Unit
{
private:
    InfantryType infantryType;
public:
    Infantry(int quantity , int weight , const Position pos , InfantryType infantryType): Unit(quantity, weight, pos), infantryType(infantryType) {}
    int getAttackScore() const override;
    string str() const override;
    
    int digitSum(int n) {
        while (n >= 10) {
            int sum = 0;
            while (n > 0) {
                sum += n % 10;
                n /= 10;
            }
            n = sum;
        }
        return n;
    }
    int computePersonalNumber(int score, int year = 1975) {
        int scoreDigitSum = 0, yDigitSum = 0;
    
        int s = score;
        while (s > 0) {
            scoreDigitSum += s % 10;
            s /= 10;
        }
    
        int y = year;
        while (y > 0) {
            yDigitSum += y % 10;
            y /= 10;
        }
    
        int total = scoreDigitSum + yDigitSum;
        return digitSum(total);  // Reduce to 1 digit
    }
    
    bool equals(const Unit* other) const override {
        const Infantry* i = dynamic_cast<const Infantry*>(other);
        return i && this->infantryType == i->infantryType && this->pos.equals(i->pos);
    }
    
    InfantryType getInfantryType(){
        return infantryType;
    }
    
    Unit* clone() const override {
        return new Infantry(*this);  // or with custom constructor
    }

};




// 3.5 UnitList
class UnitList
{
private:
    struct Node {
        Unit* unit;
        Node* next;
        Node(Unit* unit, Node* next = nullptr) : unit(unit), next(next) {}
    };

    Node* head;
    int capacity;
    int count_vehicle;
    int count_infantry;
    int size;

public:
    UnitList(int capacity) : head(nullptr), capacity(capacity), count_vehicle(0), count_infantry(0), size(0) {}

    vector<Unit*> getUnitsByType(const string& type){
        vector<Unit*> result;
        for(Unit* u : )
    }
    
    ~UnitList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current->unit;
            delete current;
            current = next;
        }
    }

    bool insert(Unit* unit) {
        if (size >= capacity) return false;

        // Check for existing unit of same type
        Node* current = head;
        while (current) {
            if (current->unit->equals(unit)) {
                current->unit->increaseQuantity(unit->getQuantity());
                return true;
            }
            current = current->next;
        }

        // Insert new node
        Node* newNode = new Node(unit);
        if (dynamic_cast<Infantry*>(unit)) {
            newNode->next = head;
            head = newNode;
            count_infantry++;
        } else {
            if (!head) {
                head = newNode;
            } else {
                Node* tail = head;
                while (tail->next) tail = tail->next;
                tail->next = newNode;
            }
            count_vehicle++;
        }

        size++;
        return true;
    }

    bool isContain(VehicleType vehicleType) {
        Node* current = head;
        while (current) {
            Vehicle* v = dynamic_cast<Vehicle*>(current->unit);
            if (v && v->getVehicleType() == vehicleType) return true;
            current = current->next;
        }
        return false;
    }
    bool isContain(InfantryType infantryType){
        Node* current = head;
        while(current){
            Infantry* i = dynamic_cast<Infantry*>(current->unit);
            if (i && i->getInfantryType() == infantryType) return true;
            current = current -> next;
        }
        return false;
    }
    string str() const{
        std::ostringstream oss;
        oss << "UnitList[count_vehicle=" << count_vehicle
            << ";count_infantry=" << count_infantry << ";";
        Node* current = head;
        while (current) {
            oss << current->unit->str();
            if (current->next) oss << ",";
            current = current->next;
        }
        oss << "]";
        return oss.str();
    }
    // TODO
};

class Army
{
protected:
    int LF, EXP;
    string name;
    UnitList *unitList;
    BattleField *battleField;

public:
    Army(Unit **unitArray, int size, string name, BattleField *battleField): LF(0), EXP(0), name(name), battleField(battleField){
        int tempLF = 0, tempEXP = 0;
        for(int i = 0; i < size; i++){
            const Unit* unit = unitArray[i];
            if (const Vehicle* v = dynamic_cast<const Vehicle*>(unit)) {
                tempLF += v->getAttackScore();
            } else if(const Infantry* inf = dynamic_cast<const Infantry*>(unit)){
                tempEXP += inf->getAttackScore();
            }
        }
        int S = tempLF + tempEXP;
        int cap = 8;
        int primes[] = {3, 5, 7};
        for (int p : primes) {
            int sum = 0, base = 1, n = S;
            while (n > 0) {
                sum += base * (n % p);
                base *= p;
                n /= p;
            }
            if (sum == S) {
                cap = 12;
                break;
            }
        }

        unitList = new UnitList(cap);
        LF = std::min(tempLF, 1000);
        EXP = std::min(tempEXP, 500);


        for (int i = 0; i < size; ++i) {
            unitList->insert(unitArray[i]->clone());
        }
    };
    virtual void fight(Army *enemy, bool defense = false) = 0;
    virtual string str() const = 0;
};
    
class LiberationArmy : public Army{
public:
    LiberationArmy(Unit** unitArray, int size, string name, BattleField* battleField): Army(unitArray, size, name, battleField){}
    void fight(Army* enemy, bool defense = false) override{
        if(!defense){
            float modLF = LF*1.5;
            float modEXP = EXP*1.5;
            
            
        }
    }
};

#endif