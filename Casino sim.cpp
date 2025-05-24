#include <iostream>
#include <string>
#include <vector>
#include <map>

class Person{
    protected:
    int id, money, salary;
    std::string name;
    public:
    virtual void Interact()=0;

    int getMoney(){
        return money;
    }
    void setMoney(int m){       //we might need more setters and getters, we'll add them as we need them
        money =m;
    }
    Person(){
        id=0;
        money=0;
        salary=0;
        name="Nameless";
    }
    Person(int cons_id, int cons_money, int cons_salary,std::string cons_name){
        id=cons_id;
        money=cons_money;
        salary=cons_salary;
        name=cons_name;
    }
    ~Person(){};
};

class Customer:public Person{
    protected:
    int addiction_level; //the higher the addiction level the more they will bet
    public:
    //void Interact() to be implemented

    Customer(int cons_id, int cons_money, int cons_salary,std::string cons_name, int cons_addiction_level):Person(cons_id,cons_money,cons_salary,cons_name){
        addiction_level=cons_addiction_level;
    }
    Customer():Person(){
        addiction_level=0;
    }
    void SpendMoney(int amount){
        money=money-amount;
    }
    int GetAddictionLevel(){
        return addiction_level;
    }
    void SetAddictionLevel(int ad_level){
        addiction_level=ad_level;
    }
    ~Customer(){}
};

class MobsterCustomer:public Customer{ //each mobster customers offer bribe discounts once bonded with and bet more
    protected:
    int discount_percentage;
    public:
    //void Interact() maybe has some extra mechanics to it
    MobsterCustomer():Customer(){
        discount_percentage=0;
    }
    MobsterCustomer(int cons_id, int cons_money, int cons_salary,std::string cons_name, int cons_addiction_level, int cons_discount_percentage):Customer(cons_id,cons_money,cons_salary,cons_name,cons_addiction_level){
        discount_percentage=cons_discount_percentage;
    }
    ~MobsterCustomer(){}
};

class Employee:public Person{
    protected:
    int satisfaction, customer_serv_skill_level; //these will factor into how profitable an employee is, the higher the two the more money they will make
                                                //skill level is set, satisfaction depends on the salary
    public:
    Employee():Person(){
        satisfaction=0;
        customer_serv_skill_level=0;
    }
    Employee(int cons_id, int cons_money, int cons_salary,std::string cons_name, int cons_satisfaction, int cons_cust_sk_lvl):Person(cons_id,cons_money,cons_salary,cons_name){
        satisfaction=cons_satisfaction;
        customer_serv_skill_level=cons_cust_sk_lvl;
    }
    int getSatisfaction(){
        return satisfaction;
    }
    void setSatisfaction(int satisf){
        satisfaction=satisf;
    }
    int getCustServSkillLvl(){
        return customer_serv_skill_level;
    }
    void setCustServSkillLvl(int skill_level){
        customer_serv_skill_level=skill_level;
    }
    ~Employee(){}
};
class Casino{
    private:
    int funds, crime_meter, bribe_discount,profits;
    std::vector<Customer*> customers;
    std::vector<Employee*> employees;
    std::map<std::string, bool> crimesCommitted;
    public:

    Casino(){
        funds=0;
        crime_meter=0;
        bribe_discount=0;
        profits=0;
        //need to also initialise the other things with null but idk how yet
    }
    //will make the parameterised constructor later

    void SimulateDay(){} //day/night cycle
    void CommitCrime(std::string Crimename){}
    void UpdateCrimeMeter(){
        //some sort of formula to convert each crime's "severity" into a value
    }
    void BribePolice(int amount){} //lowers crime meter
    void UpdateDiscount(int percentage){
        bribe_discount=bribe_discount+percentage;//updates whenever a new bond with a Mobster Customer is made
    } 
    void HireEmployee(Employee* empl){
        //add a new employee to the vector, add their salary *-1 to profits
    }
    void UpdateProfits(int amount){
        profits=profits+amount;
    }
};

void GameInit(){
                    //optimally we would read names, IDs, money, salaries from one separate "characterInfo" file
                    //dialogue lines would be in a "Dialogue" file
                    //story lines should also be in another file
                    //reading from txt files shouldnt be too difficult
}

void SimulateBlackJack(bool &DealerWin, int bet){
                    //the player is assumed to be the dealer, the character bets and makes decisions, the player can interact with the character after each game
}
int main(){
    return 0;
}