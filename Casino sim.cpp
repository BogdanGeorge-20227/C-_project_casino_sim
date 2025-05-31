#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <memory>
#include <typeinfo>
/*
!!! GENERAL IMPORTANT NOTES !!!
-This version serves mostlyas a prototype, some of the more fringe features were removed

-Input and output files need to be in the directory where the .exe file is
-Changing the size of the terminal console window during runtime makes outputs weird
*/
namespace CasinoSim{
    struct card{
        int value;
        std::string card_name;  //this struct is used in deckbuilding and simulating the game
        char symbol;            //it is featured outside a class because some functions and methods use the card type outside of classes
   //     ♥ is char 3
   //     ♦ is char 4
   //     ♣ is char 5
   //     ♠ is char 6
    };

    std::string PlayersChoice(std::string correct1,std::string correct2,std::string correct3,std::string correct4){ //these 4 functions are for making sure the player inputs
        std::string input;                                                                                          //a correct string input, for integer inputs we trust the
        while(true){                                                                                                //player to be capable of putting in a simple number
            std::cin>>input;                                                              //though a future version would use some std::stoi() implementation to ensure int compliance
            if(input==correct1 || input==correct2 || input==correct3 || input==correct4)return input;
            std::cout<<"Incorrect input"<<std::endl;
        }
    }
    std::string PlayersChoice(std::string correct1,std::string correct2){
        std::string input;
        while(true){
            std::cin>>input;
            if(input==correct1 || input==correct2)return input;
            std::cout<<"Incorrect input"<<std::endl;
        }
    }
    std::string PlayersChoice(std::string correct1,std::string correct2,std::string correct3){
        std::string input;
        while(true){
            std::cin>>input;
            if(input==correct1 || input==correct2 || input==correct3)return input;
            std::cout<<"Incorrect input"<<std::endl;
        }
    }
class Person{
    protected:
    int id, money, salary;
    std::string name;
    public:
    virtual void Interact()=0;  //virtual function for polymorphism

    int getMoney(){
        return money;
    }
    void setMoney(int m){     
        money =m;
    }
    std::string getName(){
        return name;
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
int discount_gift=0;        
class Customer:public Person{
    protected:
    int addiction_level; //the higher the addiction level the more they will bet
    std::vector<std::string> dialogue;
    public:
    void Interact()override{
        for(int i=0;i<=dialogue.size()-1;i++){
            std::cout<<dialogue.at(i)<<std::endl;       //displays dialogue
        }
        if(addiction_level<2)addiction_level++;
    }
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
    void DialogueInit(){
    dialogue.clear();
    std::ifstream ReadCuststats("Customer_Dialogue.txt");   //open up dialogue file !!!FILE NEEDS TO BE NEXT TO .EXE FILE!!! (for me that was in "output" folder)

    std::string currentstr,compstr;                             //as the file is read, one string holds the current line and the other looks for the header we want
    compstr="client "+std::to_string(id)+" dialogue "+std::to_string(addiction_level+1)+':'; //header formation ex: "client 1 dialogue 3:"
    while(std::getline(ReadCuststats,currentstr)){              //read file until end
        if(currentstr==compstr){        //if we find the header
                std::getline(ReadCuststats,currentstr); 
                dialogue.push_back(currentstr);                
         }
    }
    ReadCuststats.close();      //closing the file
    }
    std::string GetDialogueLine(int line_nr){   //it indexes from 0
        return dialogue[line_nr];
    }
    void DebugDisplayAllInfo(){
        std::cout<<name<<' '<<money<<' '<<salary<<' '<<addiction_level<<' '<<id<<std::endl;
    }
    ~Customer(){}
};

class MobsterCustomer:public Customer{ //each mobster customers offer bribe discounts once bonded with and bet more
    protected:
    int discount_percentage;
    bool discount_given;
    public:
        void Interact()override{
        for(int i=0;i<=dialogue.size()-1;i++){
            std::cout<<dialogue.at(i)<<std::endl;
        }
        if(addiction_level<2)addiction_level++;
        else{
            if(addiction_level==2 && !discount_given){  //at bond level 2 the player receives a "bribe discount", making any bribe money they offer more effective
            std::cout<<"Le Puissant sends his regards, you're getting a "<<discount_percentage<<"\% sale on any money that go where they need to go"<<std::endl;
            discount_gift=discount_percentage;
            }
    }
    }
    MobsterCustomer():Customer(){
        discount_percentage=0;
        discount_given=false;
    }
    MobsterCustomer(int cons_id, int cons_money, int cons_salary,std::string cons_name, int cons_addiction_level, int cons_discount_percentage):Customer(cons_id,cons_money,cons_salary,cons_name,cons_addiction_level){
        discount_percentage=cons_discount_percentage;
        discount_given=false;
    }
        void DebugDisplayAllInfo(){
        std::cout<<name<<' '<<money<<' '<<salary<<' '<<addiction_level<<' '<<id<<' '<<discount_percentage<<std::endl;
    }
    ~MobsterCustomer(){}
};

class Employee:public Person{
    protected:
    int daily_profits;
    public:
    void Interact()override{}   //currently, there is no need or way to interact with employees, aside from hiring them
    Employee():Person(){
        daily_profits=0;
    }
    Employee(int cons_id, int cons_money, int cons_salary,std::string cons_name, int cons_daily_profits):Person(cons_id,cons_money,cons_salary,cons_name){
        daily_profits=cons_daily_profits;
    }
    int getDailyProfits(){
        return daily_profits;
    }
    void setDailyProfits(int profits){
        daily_profits=profits;
    }
    void UpdateSalary(int new_salary){
        salary=new_salary;
    }
    void DebugDisplayAllInfo(){
    std::cout<<name<<' '<<money<<' '<<salary<<' '<<daily_profits<<' '<<id<<std::endl;
    }
    ~Employee(){}
};

class CardDeck{
    private:
    std::vector<card> deck;
    card base_card;         //either just a card container or a sneaky cheat card
    public:
    CardDeck(){
        
        //initialisation of one 52 card deck
        for(int i=0;i<=51;i++){
            base_card.value=i%13+2;
            base_card.symbol=i%4+3;     //the number and suit of the cards are determined mathematically, the values range from 2 to 14, the symbol chars from 3 to 6
            if(base_card.value<=10)base_card.card_name=std::to_string(base_card.value);
            else{
                switch(base_card.value){
                    case 11:
                    base_card.card_name="Ace";
                    break;
                    case 12:
                    base_card.card_name="Jack";
                    break;
                    case 13:
                    base_card.card_name="Queen";
                    break;
                    case 14:
                    base_card.card_name="King";
                    break;
                }
            }
            deck.push_back(base_card);
        }
    }
    CardDeck(bool Rigged){
        if(Rigged){
            card ace_under_the_sleeve;
            ace_under_the_sleeve.card_name="Ace";
            ace_under_the_sleeve.symbol=5;
            ace_under_the_sleeve.value=11;
            base_card=ace_under_the_sleeve;         //an ace of spades is added in a rigged hand, allowing the player or the dealer to add an ace whenever their hand's sum is at 10, for an easy 21
        }
    }
    //getcard function that also puts the returned card at the bottom of the draw pile
    card GetCard(){
        deck.insert(deck.begin(),deck.back());      //the last card in the deck is the one returned first
        deck.pop_back();                            //the current last card is copied in front, deleted from the back and then the new last card is returned
        return deck.back();
    }
    card AceUnderSleeve(){
        return base_card;       //cheat card is returned
    }
    void AddCard(card card_to_add){
        deck.push_back(card_to_add);
    }
    //this function looks at the card currently drawn during the game and at who drew it, and sets up win/lose, turn over flags as well as updates the hand's sum
    void DrawEvaluation(bool &first_turn,bool &blackjack,bool &turn_ongoing,bool is_dealer,int dealers_target, int &deck_sum, card card_in_play){
        if(card_in_play.value<=10)deck_sum=deck_sum+card_in_play.value;
        else{
            if(card_in_play.value==11)deck_sum=deck_sum+11;     //if the card in play is a 10 or below it has the value of its number
            else deck_sum=deck_sum+10;                          //if it's a J, Q, K or Ace they have values 10, 10, 10 and 11, respectively
        }
        if(first_turn){
            first_turn=false;           //if it's the first turn the customer draws 2 cards before making any other decision
        }
        else{
            if(deck_sum==21){
                blackjack=true;
                turn_ongoing=false;
            }
            else{
                if(deck_sum>21)turn_ongoing=false;
                if(deck_sum>=dealers_target&&is_dealer)turn_ongoing=false;
                if(deck_sum>16 && !is_dealer)turn_ongoing=false;    //customers hold at 16+, dealers need to hit until they get a sum bigger than cust or go over 21
                }
            }

        }

    void ShuffleDeck(int seed){
        card shuffle_card;
        for(int shufflecount=0;shufflecount<=seed;shufflecount++){
            int i_midend=deck.size()/2;
            int i_stmid=0;
            while(i_midend<deck.size()-1){
                 shuffle_card=deck.at(i_midend);           //for shuffling, we basically simulate taking the bottom half of the deck and putting each card between two cards of the first half of the deck
                 deck.erase(deck.begin()+i_midend);        //seed is also the number of times a deck is shuffled at the start of each game, since shuffling is deterministic this makes for a good seeded game system
                 deck.insert(deck.begin()+i_stmid,shuffle_card);     
                 i_midend=i_midend+2;
                 i_stmid=i_stmid+2;
            }
        }
    }
    void DeckDisplayDebug(){
        for(card loop_card:deck){
            std::cout<<loop_card.card_name<<' '<<loop_card.symbol<<' '<<loop_card.value<<std::endl;
        }
    }
    ~CardDeck(){
        deck.clear();                       //clears the vector
        std::vector<card>().swap(deck);     //makes it take the memory of a null object, effectively deleting it
    }                                       //this form of deconstructor is widely used throughout the code
    friend std::ostream& operator<<(std::ostream& os, const CardDeck& dk);
    friend CardDeck operator+(CardDeck &dk,card const& cd);
};
std::ostream& operator<<(std::ostream& os, const CardDeck& dk){
    for(int i=0;i<dk.deck.size();i++){
        os<<dk.deck.at(i).card_name<<' '<<dk.deck.at(i).symbol<<std::endl;      //overloading of << to display card deck contents
    }
    return os;
}
CardDeck operator+(CardDeck &dk,card const& cd){
    dk.deck.push_back(cd);
    return dk;                      //overloading + operator to allow adding cards to decks
}
//this function is not part of a class since it doesn't neatly fit into any class. A deck is necessary to play, yet the function makes decks of its own
//in a future version this would likely part of a deck-derived class "Deck Games" where multiple card game methods would be stored, this class would also be related in some way to the casino class, since games being part of a casino makes sense
void SimulateBlackJack(CardDeck* play_deck,bool RiggedCustomer,bool RiggedDealer,int seed,bool &dealerwin,bool &draw){ 
    play_deck->ShuffleDeck(seed);   //we begin by shuffling
    dealerwin=false;
    draw=false;
    int cust_sum=0;
    bool cust_turn=true;        //customer comes first, these bools are flags to know when their turn is over
    bool dealer_turn=true;
    bool first_turn=true;       //if the customer loses then there is no need to go to dealer's turn
    bool cust_blackjack=false;
    bool dealer_blackjack=false;
    int sum_dealer=0;                                   //the rules of the game are simplified for this prototype version
    CardDeck* dealer_hand=new CardDeck(RiggedDealer);   //there is no double down, split, surrender, ace counts as 11 always
    CardDeck* customer_hand=new CardDeck(RiggedCustomer);
    card card_in_play;
                    //the player is assumed to be the dealer, the character bets and makes decisions, the player can interact with the character after each game
    while(cust_turn){
        card_in_play=play_deck->GetCard();
        customer_hand->AddCard(card_in_play);
        customer_hand->DrawEvaluation(first_turn,cust_blackjack,cust_turn,false,0,cust_sum,card_in_play);
        if(RiggedCustomer&&cust_sum==10)customer_hand->DrawEvaluation(first_turn,cust_blackjack,cust_turn,false,0,cust_sum,customer_hand->AceUnderSleeve()); //if customer/dealer are rigged, they may add the ace to a hand with sum 10
    }
    customer_hand->DeckDisplayDebug();
    std::cout<<cust_sum<<std::endl;
    if(cust_blackjack){
        std::cout<<"Customer wins by blackjack"<<std::endl;
        dealerwin=false;
    }
    else{
        if(cust_sum>21){
            std::cout<<"Customer loses, over 21"<<std::endl;
            dealerwin=true;
        }
        else{
            std::cout<<std::endl;
           while(dealer_turn){          //dealer's turn
            card_in_play=play_deck->GetCard();
            dealer_hand->AddCard(card_in_play);
            dealer_hand->DrawEvaluation(first_turn,dealer_blackjack,dealer_turn,true,cust_sum,sum_dealer,card_in_play);
            if(RiggedDealer&&sum_dealer==10)dealer_hand->DrawEvaluation(first_turn,dealer_blackjack,dealer_turn,true,cust_sum,sum_dealer,dealer_hand->AceUnderSleeve());
            } 
            dealer_hand->DeckDisplayDebug();
            std::cout<<sum_dealer<<std::endl;
            if(sum_dealer>21){
                std::cout<<"Customer wins, dealer over 21"<<std::endl;
                dealerwin=false;
            }
            else{
                if(sum_dealer>cust_sum){
                    std::cout<<"Customer loses, dealer higher sum"<<std::endl;
                    dealerwin=true;
                }
                if(sum_dealer==cust_sum){
                    std::cout<<"Draw"<<std::endl;
                    draw=true;
                }
                if(sum_dealer<cust_sum){
                    std::cout<<"Customer wins, dealer lower sum"<<std::endl;
                    dealerwin=false;
                }
            }
        }
    }
    delete dealer_hand;
    delete customer_hand;
}

class Casino{
    private:
    int funds, crime_meter, bribe_discount,profits, tax_rate,employee_count;
    std::vector<std::shared_ptr<Customer>> customers_present,all_customers;     //customers and employees are all stored in a vector, and put into a "present" vector which denotes the employees and customers that are in play at a given day
    std::vector<Employee*> employees_present,all_employees;
    std::vector<std::string> news;                                          //all news are stored in a vector, and displayed one by one when needed
    std::map<std::string, int> crimesCommitted;
    std::map<std::string, bool> bonded_today;                           //this map has the purpose of seeing which customers have been already talked to in one day, we didn't want players getting a max level bond in ONE day
    CardDeck* play_deck;    
    enum DailyRoutine:unsigned char     //enum for state machine
    {
        Morning=0,
        News,
        Tables,
        Play,
        Bond,
        NightBreakdown,
        Crime,
        Employ,
        EndCheck,
    };
    public:

    Casino(){
        funds=0;
        crime_meter=0;
        bribe_discount=0;
        profits=0;
        tax_rate=0;
        employee_count=0;
        NewsCycleInit();
        CrimeInit();
        AllCustomersInit();
        AllEmployeesInit();
        play_deck=new CardDeck();   //only default constructor needed for now
    }

    void CrimeInit(){
        crimesCommitted.insert({"Minor tax evasion",0});
        crimesCommitted.insert({"Major tax evasion",0});
        crimesCommitted.insert({"Employee mismanagement",0});
        crimesCommitted.insert({"Jaywalking",0});
        crimesCommitted.insert({"Conspiracy to international terrorism",0});
        crimesCommitted.insert({"Illegal substance abuse",0});
    }
    void NewsCycleInit(){
    std::ifstream ReadNews("News_stories.txt");                 //function very similar to the one reading dialogue, customer stats and employee stats due to the standardised format of the txt files

    std::string currentstr,compstr;                             //as the file is read, one string holds the current line and the other looks for the header we want
    int i=1;
    while(std::getline(ReadNews,currentstr)){ 
        compstr="news "+std::to_string(i)+':';             //read file until end
        if(currentstr=="news danger:" || currentstr=="news very danger:"){
                std::getline(ReadNews,currentstr);                   
                news.push_back(currentstr);  
        }
        if(currentstr==compstr){                               
                std::getline(ReadNews,currentstr);                   
                news.push_back(currentstr);                
                i++;                                  
         }
    }
    ReadNews.close();      //closing the file
    }
    void AllCustomersInit(){
    std::ifstream ReadCustStats("Customer_stats.txt");   

    std::string currentstr,compstr,read_cust_name;                             //as the file is read, one string holds the current line and the other looks for the header we want

    int i=1, money, salary, addiction_lvl;
    while(std::getline(ReadCustStats,currentstr)){ 
        compstr="client "+std::to_string(i)+':';             //read file until end
        if(currentstr==compstr){                               
                std::getline(ReadCustStats,currentstr);
                money=std::stoi(currentstr);
                std::getline(ReadCustStats,currentstr); 
                salary=std::stoi(currentstr);  
                std::getline(ReadCustStats,currentstr);         //when reading a stat, it reads a string that needs to be converted to int
                read_cust_name=currentstr;
                std::getline(ReadCustStats,currentstr); 
                addiction_lvl=std::stoi(currentstr);
                std::getline(ReadCustStats,currentstr); 
                if(currentstr!="@%") all_customers.push_back(std::shared_ptr<Customer>(new MobsterCustomer(i,money,salary,read_cust_name,addiction_lvl,std::stoi(currentstr)))); //if there's an additional stat that means the customer is a mobster, and that stat is the bribe discount
                else all_customers.push_back(std::shared_ptr<Customer>(new Customer(i,money,salary,read_cust_name,addiction_lvl)));    
                i++;                                  
         }
    }
    ReadCustStats.close();      //closing the file
    }
    void AllEmployeesInit(){
        std::ifstream ReadEmployeeStats("Employee_stats.txt"); 

    std::string currentstr,compstr,read_employee_name;                             //as the file is read, one string holds the current line and the other looks for the header we want
    int i=1, money, salary, addiction_lvl;
    while(std::getline(ReadEmployeeStats,currentstr)){ 
        compstr="employee "+std::to_string(i)+':';             //read file until end
        if(currentstr==compstr){                               
                std::getline(ReadEmployeeStats,currentstr);
                money=std::stoi(currentstr);
                std::getline(ReadEmployeeStats,currentstr); 
                salary=std::stoi(currentstr);  
                std::getline(ReadEmployeeStats,currentstr); 
                read_employee_name=currentstr;
                std::getline(ReadEmployeeStats,currentstr); 
                addiction_lvl=std::stoi(currentstr);    
                all_employees.push_back(new Employee(i,money,salary,read_employee_name,addiction_lvl));      
                i++;                                  
         }
    }
    ReadEmployeeStats.close();      //closing the file
    }
    void CustomerArrival(int current_day){
        customers_present.clear();
        bonded_today.clear();       //every day we refresh the customers present and their interaction status
        while(current_day>all_customers.size())current_day=current_day-all_customers.size();
        for(int i=0;i<=2;i++){
            if(current_day+i<=all_customers.size())customers_present.push_back(all_customers.at(current_day+i-1));
            else{
                customers_present.push_back(all_customers.at(current_day+i-all_customers.size()-1));    //code makes it so every day we get 3 clients, in the following order (ex for 4 clients): 1 2 3, 2 3 4, 3 4 1, 4 1 2, 1 2 3, etc
            }
            //customers_present.at(i)->DebugDisplayAllInfo();
            bonded_today.insert({customers_present.at(i)->getName(),false});
            customers_present.at(i)->DialogueInit();    //the dialogue of a customer is dependent on their bond level, it is different each time the customer has been bonded with the previous day (for now only 3 bond levels per customer)
        }
    }
    void CommitCrime(std::string Crimename){
        crimesCommitted.at(Crimename)++;
        UpdateCrimeMeter();
    }
    void UpdateCrimeMeter(){
        crime_meter=0;
        for(auto const& [key, val]:crimesCommitted){
            if(key=="Major tax evasion")crime_meter=crime_meter+val*200;
            else{
            if(key=="Conspiracy to international terrorism")crime_meter=crime_meter+val*450;    //severe crimes are treated separately, jaywalking is a silly crime, by contrast, that actually lowers criminality
            else{
                if(key=="Jaywalking")crime_meter=crime_meter-50;
                else crime_meter=crime_meter+val*50;
            }
            }

        }
    }
    void BribePolice(int amount){ //if bribe is smaller than 500 nothing happens
        if(amount>=500 && amount<1000){
            crime_meter=crime_meter-(5 + 10*bribe_discount/100); //the discount works as a modifier that makes bribes stronger
        }
        else{
            if(amount>=1000 && amount<10000000/(bribe_discount+100))crime_meter=crime_meter-(amount +amount*bribe_discount/100)/100;  //upper bound is chosen so that crime meter may not become negative
            else{
                if(!(amount<500))crime_meter=0;
            }
        }
    }
    void UpdateDiscount(int percentage){
        bribe_discount=bribe_discount+percentage;//updates whenever a new bond with a Mobster Customer is made
        discount_gift=0;
    } 
    int EmploymentProfits(){
        int profits=0;
        for(int i=0;i<employees_present.size();i++){
            profits=profits+employees_present.at(i)->getDailyProfits();
        }
        return profits;
    }
    void UpdateProfits(int amount){
        profits=profits+amount;
    }   
    void UpdateFunds(int profits){
        funds=funds+profits;
    }
    void DebugDisplayFunds(){
        std::cout<<std::endl<<"current funds:"<<funds<<std::endl;
    }
    void DebugShowNews(){
        std::cout<<std::endl<<"All news:"<<news.size()<<std::endl;
        for(int i=0;i<=news.size()-1;i++){
            std::cout<<news.at(i)<<std::endl;
        }
    }
    std::string GetNews(int seeded_position){
        return news.at(seeded_position);
    }

    void SimulateDay(int seed){//day/night cycle, state machine, I love to see it, we love to see it, give it up for state machineee. I say N E X T you say S T A T E wooooooo
    bool exit=false;
    bool game_draw=false;
    bool game_dealer_win=false;
    DailyRoutine time_of_day=Morning;
    std::string input;
    int day_count=0;
    int warning_level=0;
    int table_choice;
    int seeded_news;
    int tax;
    int bet;
    int energy=7;       //the amount of interactions+games the player can do per day
    while(!exit){
        switch(time_of_day){
            case Morning:
            {
                day_count++;
                tax_rate=day_count*2;
                energy=7;
                std::cout<<std::endl<<"Good morning! Start of day "<<day_count<<", would you like to Start or Leave? [Start/Leave]";
                input=PlayersChoice("Start", "Leave");
                if(input=="Leave")exit=true;
                if(input=="Start")time_of_day=News;
            break;
            }

            case News:
            {
                if(day_count+seed>=news.size()){
                  seeded_news=day_count+seed-20;
                }
                else{
                   seeded_news=day_count+seed;
                }
                if(warning_level==2){
                    std::cout<<GetNews(1); //news 0 and 1 are warnings
                    warning_level=-2;       //-1 is indicator for when a warning has already been issued, -2 is for when final warning has been issued
                }
                else{
                    std::cout<<"You open up you computer and glance upon the headlines:"<<std::endl;
                    if(warning_level==1){
                        std::cout<<GetNews(0)<<std::endl;
                        warning_level=-1;
                    }
                    else std::cout<<GetNews(seeded_news)<<std::endl;
                }
                std::cout<<"Enter anything to proceed:";
                std::cin>>input;            //we dont care what the player inputs
                time_of_day=Tables;
                CustomerArrival(day_count);
                //exit=true;
            break;
            }

            case Tables:
            {
                if(energy>0){
                std::cout<<"Today there are "<<customers_present.size()<<" customers present"<<std::endl<<std::endl;
                std::cout<<"At table 1 sits "<<customers_present.at(0)->getName()<<std::endl;
                std::cout<<"At table 2 sits "<<customers_present.at(1)->getName()<<std::endl;
                std::cout<<"At table 3 sits "<<customers_present.at(2)->getName()<<std::endl;
                std::cout<<std::endl<<"Choose the table you'd like to deal at, alternatively end the day early [1]/[2]/[3]/[End]: ";
                input=PlayersChoice("1","2","3","End");
                if(input!="End"){
                table_choice=std::stoi(input)-1;
                std::cout<<"Would you like to talk or play with "<<customers_present.at(table_choice)->getName()<<"? [Talk]/[Play]:";
                input=PlayersChoice("Talk","Play");
                if(input=="Talk")time_of_day=Bond;
                if(input=="Play")time_of_day=Play;
                }
                if(input=="End")time_of_day=NightBreakdown;
                }
                else{
                    std::cout<<std::endl<<"After a long day, it is closing hour, input anything to poceed:";
                    std::cin>>input;
                    time_of_day=NightBreakdown;
                }
            break;
            }

            case Play:
            {
             bet=2000*customers_present.at(table_choice)->GetAddictionLevel();
             if(bet>customers_present.at(table_choice)->getMoney()/5){      //if cutomer doesnt have much money left they wont bet
                std::cout<<customers_present.at(table_choice)->getName()<<" currently can't affort to maintain their addiction, please be nice to them"<<std::endl;
             }
             else{
             SimulateBlackJack(play_deck,false, false,seed,game_dealer_win,game_draw);
             if(game_draw){}
                else{
                if(game_dealer_win){
                    UpdateProfits(bet);
                    customers_present.at(table_choice)->SpendMoney(bet);
                }
                else{
                    UpdateProfits(-1*bet);
                    customers_present.at(table_choice)->SpendMoney(-1*bet);
                }
             }
             }
                time_of_day=Tables;
                energy--;
            break;
            }
            case Bond:
            {
                if(!bonded_today.at(customers_present.at(table_choice)->getName())){    //customers may be only bonded with once per day
                    customers_present.at(table_choice)->Interact();
                    UpdateDiscount(discount_gift);
                    bonded_today.at(customers_present.at(table_choice)->getName())=true;
                    energy--;
                }
                else{
                    std::cout<<"You have already talked to this person today!"<<std::endl;
                }
                time_of_day=Tables;
            break;
            }
            case NightBreakdown:
            {
                std::cout<<std::endl<<"Good job, today you made "<<profits<<" money, how much do you think you should pay in taxes? The rate is at"<<tax_rate<<"\% of profits. [Input the amount of money to pay]";
                std::cin>>tax;
                if(tax==0){
                    CommitCrime("Major tax evasion");
                }
                else{
                    if(tax<profits*tax_rate/100)CommitCrime("Minor tax evasion");
                }
                std::cout<<std::endl<<"After tax you're left with a total of "<<profits-tax<<" money"<<std::endl;
                UpdateFunds(profits-tax);
                DebugDisplayFunds();
                std::cout<<"You could also employ someone or give your mob friends a call and see if they got anything for you. [Employ]/[Crime]/[End]"<<std::endl;
                input=PlayersChoice("Employ","Crime","End");
                if(input=="Employ")time_of_day=Employ;
                if(input=="Crime")time_of_day=Crime;
                if(input=="End")time_of_day=EndCheck;
                profits=0;
            break;
            }
            case Crime:
            {
            std::cout<<"You may help the mob in it's activities, yielding lots of money, or just have some fun crimes as a treat [Help_mob]/[Jaywalk]/[Do_some_coke]/[Bribe_police]"<<std::endl;
            input=PlayersChoice("Help_mob","Jaywalk","Do_some_coke","Bribe_police");
            if(input=="Help_mob"){
                CommitCrime("Conspiracy to international terrorism");
                std::cout<<std::endl<<"Under the veil of night you helped gangs of criminals and outlaws to bring their plans to fruition, there's no hiding what you've done. Though, you were rewarded for your efforts with "<<50000<<" money"<<std::endl;
                UpdateFunds(500000);
            }
            if(input=="Jaywalk")CommitCrime("Jaywalking");
            if(input=="Do_some_coke")CommitCrime("Illegal substance abuse");
            if(input=="Bribe_police"){
                std::cout<<"How much money will you offer as a bribe? [insert a number]:";
                std::cin>>tax; //recycling tax variable as bribe
                BribePolice(tax);
            }
            time_of_day=EndCheck;
            break;
            }
            case Employ:
            {
                std::cout<<std::endl<<"Employ "<<all_employees.at(employee_count)->getName()<<" ? They will bring "<<all_employees.at(employee_count)->getDailyProfits()<<" money in.[Yes]/[No]"<<std::endl;
                input=PlayersChoice("Yes","No");
                if(input=="Yes"){
                employees_present.push_back(all_employees.at(employee_count));
                std::cout<<"Succesfully employed "<<employees_present.at(employee_count)->getName()<<std::endl;
                employee_count++;
                }
                 else{
                    std::cout<<"So boooring"<<std::endl;
                }
                UpdateProfits(EmploymentProfits());
                time_of_day=EndCheck;
            break;
            }

            case EndCheck:
            {
                if(crime_meter>1000){   //"bad" ending
                      std::cout<<"During a night raid by Pristinian police you were arrested, even though you were warned, your hubris brought your downfall"<<std::endl;
                      exit=true;
                 }
                 else{
                   if(crime_meter>900 && warning_level==-1)warning_level=2;
                     else{
                         if(crime_meter>500 && warning_level>0)warning_level=1;
                         if(crime_meter<300)warning_level=0;                       //warning system, at 50% crime meter level news will show that the police is investigating the player, at 90%+ a mobster will come warn the player
                        }                                                       //if crime level goes below a certain value, the warning level refreshes
                    if(funds>2000000){  //"good" ending(?)
                        std::cout<<"Congratulations! You broke families and households, but at least made more money than the Vaticus himself! You will be remembered by many as just another bag of money, but by some as someone who \"Didn't let my husband home\""<<std::endl;
                        exit=true;
                    }
                } 
                time_of_day=Morning;  
                break;
            }
        }
    }

} 
~Casino(){
    customers_present.clear();
    std::vector<std::shared_ptr<Customer>>().swap(customers_present);
    all_customers.clear();
    std::vector<std::shared_ptr<Customer>>().swap(all_customers);
    employees_present.clear();
    std::vector<Employee*>().swap(employees_present);
    all_employees.clear();
    std::vector<Employee*>().swap(all_employees);
    news.clear();
    std::vector<std::string>().swap(news);
    crimesCommitted.clear();
    std::map<std::string,int>().swap(crimesCommitted);
}
};
}
int main(){
    CasinoSim::Casino* game =new CasinoSim::Casino();
    int seed;
    std::cout<<"Welcome to casino simulator! The game where greed IS good! Insert a seed and begin [number higher than 0]:";
    std::cin>>seed;
    std::cout<<std::endl;
    game->CasinoSim::Casino::SimulateDay(seed);
    delete game;
    return 0;
}
