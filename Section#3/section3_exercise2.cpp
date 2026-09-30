/*
- shuffle full deck [13 * 4 cards]
- move five cards (-> p1, p2 handeck)
- sort hand deck (asc num order)
- print p1, p2 cards 
- print table deck : [move p1, p2 each smallest card] 
*/

#include<iostream>
#include<vector>

#include<algorithm>
#include<random>
#include<chrono>

using namespace std; 

typedef struct Card
{
    int shape; 
    int num; 
}Card;

int cardnum = 13; 
int shapes[] = {0, 1, 2, 3}; // 0: clover, 1: heart, 2: spade, 3: diamond 
vector<string> shapestype = {"clover", "heart", "spade", "diamond"}; 
int mode = 0; //order 0: asc, 1: desc
unsigned seed; // random seed value

void generateCards(vector<Card>& drawDeck);
void shuffleCards(vector<Card>& drawdeck);
void moveCards(vector<Card>& from, vector<Card>& to, int Movenum); 
void sortCard(vector<Card>& deck); 
void printDeck(vector<Card>& deck);

int main()
{ 
    seed = chrono::system_clock::now().time_since_epoch().count(); 
    
    vector<Card> draw;
    vector<Card> p1_hand, p2_hand;
    vector<Card> table;
    
    generateCards(draw); 
    shuffleCards(draw); 
    moveCards(draw, p1_hand, 5);
    moveCards(draw, p2_hand, 5);    
    
    mode = 0; 
    cout << "#Player 1 deck" << endl;
    sortCard(p1_hand);  
    printDeck(p1_hand);
    cout << "#Player 2 deck" << endl; 
    sortCard(p2_hand);
    printDeck(p2_hand);

    mode =1;
    sortCard(p1_hand); 
    sortCard(p2_hand); 
    moveCards(p1_hand, table, 1);    
    moveCards(p2_hand, table, 1);    

    cout << "#Table deck" << endl;
    printDeck(table);
}

void generateCards(vector<Card>& drawDeck)
{
    for(int shape : shapes)
    {
        for(int num = 1; num <= 13; num++)
        {
            Card newcard = {shape, num}; 
            drawDeck.push_back(newcard); 
        }
    }
}

void shuffleCards(vector<Card>& drawdeck) 
{
    // idea 
    // 기존 drawdeck 사이즈 (0, length) random value 가져오기 // deck의 크기가 0이 될때까지 
    // 새로운 shuffle deck .push_back으로 shuffle을 
    
    // #algorithm - shuffle function : https://cplusplus.com/reference/algorithm/shuffle/?kw=shuffle 
    
    // reference : Fisher–Yates shuffle method
    /* 
    template <class RandomAccessIterator, class URNG>
    void shuffle (RandomAccessIterator first, RandomAccessIterator last, URNG&& g)
    {
        for (auto i=(last-first)-1; i>0; --i) 
        {
            std::uniform_int_distribution<decltype(i)> d(0,i); // 동일한 확률로 (0, i) 중 임의이 값 선택하는 함수 
            swap (first[i], first[d(g)]);
        }
    }
    */

    shuffle(drawdeck.begin(), drawdeck.end(), default_random_engine(seed)); 

}

void moveCards(vector<Card>& from, vector<Card>& to, int Movenum)
{
    // idea 
    // from vector deck에서 movement 수 만큼 
    // 임시 vector<Card> temp 에 저장 
    // 뒤에서 부터 주고, pop 

    for(int i =0; i < Movenum; i++)
    {
        Card temp = from.back(); 
        to.push_back(temp); 
        from.pop_back(); 
    }

}

bool compareNum(Card i, Card j) // sort 하는 helper함수 
{
    return mode == 0 ? i.num < j.num : i.num > j.num; 
}

void sortCard(vector<Card>& deck)
{
    // idea 
    // if(mode == 0), deck card를 asc 순으로 정렬
    // else, deck을 desc 순으로 정렬 

    // Sorting 의 유형 weak (= unstable) vs strong (= stable)
    // -> https://share.google/aimode/IKNVc6D4uqTM6a3Nm
    // -> https://cplusplus.com/reference/algorithm/sort/?kw=sort

    sort(deck.begin(), deck.end(), compareNum);
}




void printDeck(vector<Card>& deck)
{
    // idea 
    for (int i =0; i < deck.size(); i++)
      {
        cout << shapestype[deck[i].shape] << " " << deck[i].num << endl ;
      }
    cout << endl; 

}