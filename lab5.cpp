#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "Template.h"
using namespace std;


class FishingStrategy;

class Wobbler {
protected:
    const wstring Attach = L"Зацепили леску к вобблеру";
    const wstring Throw = L"Закинули вобблер в воду";
    const wstring Take = L"Вытянули спиннинг с вобблером из воды и сняли рыбу";
private:
    int Weight;
    int Length;
    wstring BuoyancyType;
    wstring WobblerType;
    FishingStrategy* strategy;
public:
    Wobbler(int Weight, int Length, wstring BuoyancyType, wstring WobblerType, FishingStrategy* strategy);
    virtual ~Wobbler();
    int GetWeight() const { return Weight; }
    int GetLength() const { return Length; }
    wstring GetBuoyancyType() const { return BuoyancyType; }
    wstring GetWobblerType() const { return WobblerType; }
    virtual void AttachLine() = 0;
    virtual void ThrowWobbler() = 0;
    virtual void TakeFish() = 0;
    void getInfo() {
        wcout << L"Тип вобблера - " << WobblerType << L", тип плавучести - " << BuoyancyType << endl;
    }

    void ApplyStrategy();
};

Wobbler::Wobbler(int Weight, int Length, wstring BuoyancyType, wstring WobblerType, FishingStrategy* strategy)
    : Weight(Weight), Length(Length), BuoyancyType(BuoyancyType), WobblerType(WobblerType), strategy(strategy) {
}

Wobbler::~Wobbler() {}


class FishingStrategy {
public:
    virtual ~FishingStrategy() {}
    virtual void Apply(Wobbler* wobbler) = 0;
};

class AggressiveStrategy : public FishingStrategy {
public:
    void Apply(Wobbler* wobbler) override {
        wcout << L"Убираем вобблер " << wobbler->GetWobblerType() << L" подальше и глушим рыбу бомбочками" << endl;
    }
};

class CautiousStrategy : public FishingStrategy {
public:
    void Apply(Wobbler* wobbler) override {
        wcout << L"Медленно подтягиваем вобблер " << wobbler->GetWobblerType() << endl;
    }
};
void Wobbler::ApplyStrategy() {
    if (strategy)
        strategy->Apply(this);
}



class NoriesPelican : public Wobbler {
public:
    NoriesPelican(int Weight, int Length, wstring BuoyancyType, wstring WobblerType, FishingStrategy* strategy);
    ~NoriesPelican();
    void AttachLine();
    void ThrowWobbler();
    void TakeFish();
};

NoriesPelican::NoriesPelican(int Weight, int Length, wstring BuoyancyType, wstring WobblerType, FishingStrategy* strategy)
    : Wobbler(Weight, Length, BuoyancyType, WobblerType, strategy) {
    wcout << L"Достали упаковку вобблеров Nories Pelican" << endl;
}
NoriesPelican::~NoriesPelican() {
    wcout << L"Убрали упаковку с вобблерами в чемодан" << endl;
}
void NoriesPelican::AttachLine() {
    wcout << Attach << endl;
}
void NoriesPelican::ThrowWobbler() {
    wcout << Throw << endl;
}
void NoriesPelican::TakeFish() {
    wcout << Take << endl;
}

class HMKLShad : public Wobbler {
public:
    HMKLShad(int Weight, int Length, wstring BuoyancyType, wstring WobblerType, FishingStrategy* strategy);
    ~HMKLShad();
    void AttachLine();
    void ThrowWobbler();
    void TakeFish();
};

HMKLShad::HMKLShad(int Weight, int Length, wstring BuoyancyType, wstring WobblerType, FishingStrategy* strategy)
    : Wobbler(Weight, Length, BuoyancyType, WobblerType, strategy) {
    wcout << L"Достали упаковку вобблеров HMKL Shad" << endl;
}
HMKLShad::~HMKLShad() {
    wcout << L"Убрали упаковку с вобблерами в чемодан" << endl;
}
void HMKLShad::AttachLine() {
    wcout << Attach << endl;
}
void HMKLShad::ThrowWobbler() {
    wcout << Throw << endl;
}
void HMKLShad::TakeFish() {
    wcout << Take << endl;
}

class ValkeINJuJu : public Wobbler {
public:
    ValkeINJuJu(int Weight, int Length, wstring BuoyancyType, wstring WobblerType, FishingStrategy* strategy);
    ~ValkeINJuJu();
    void AttachLine();
    void ThrowWobbler();
    void TakeFish();
};

ValkeINJuJu::ValkeINJuJu(int Weight, int Length, wstring BuoyancyType, wstring WobblerType, FishingStrategy* strategy)
    : Wobbler(Weight, Length, BuoyancyType, WobblerType, strategy) {
    wcout << L"Достали упаковку вобблеров ValkeIN JuJu" << endl;
}
ValkeINJuJu::~ValkeINJuJu() {
    wcout << L"Убрали упаковку с вобблерами в чемодан" << endl;
}
void ValkeINJuJu::AttachLine() {
    wcout << Attach << endl;
}
void ValkeINJuJu::ThrowWobbler() {
    wcout << Throw << endl;
}
void ValkeINJuJu::TakeFish() {
    wcout << Take << endl;
}

enum class WobblerList : int {
    NoriesPelican = 1,
    HMKLShad = 2,
    ValkeINJuJu = 3
};

Wobbler* TakeWobbler(WobblerList w, FishingStrategy* strategy) {
    Wobbler* curWobbler = nullptr;
    switch (w) {
    case WobblerList::NoriesPelican:
        curWobbler = new NoriesPelican(15, 50, L"Плавающий", L"Minnow", strategy);
        break;
    case WobblerList::HMKLShad:
        curWobbler = new HMKLShad(55, 65, L"Нейтральный", L"Shad", strategy);
        break;
    case WobblerList::ValkeINJuJu:
        curWobbler = new ValkeINJuJu(23, 44, L"Тонущий", L"Stick", strategy);
        break;
    default:
        break;
    }
    return curWobbler;
}

void WobblerActions(Iterator<Wobbler*>* iterator, bool noActions = false) {
    for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
        Wobbler* newWobbler = iterator->GetCurrent();
        if (!noActions) {
            newWobbler->getInfo();
        }
    }
}

class getFishByWobbler : public IteratorDecorator<Wobbler*> {
private:
    wstring getFish(Wobbler* wobbler) {
        wstring fish;
        if (wobbler->GetWobblerType() == L"Shad") { return L"судака"; }
        else if (wobbler->GetWobblerType() == L"Minnow") { return L"щуки"; }
        else { return L"окуня"; }
    }
public:
    getFishByWobbler(Iterator<Wobbler*>* it) : IteratorDecorator<Wobbler*>(it) {}
    void Next() {
        Wobbler* wobbler = It->GetCurrent();
        if (!It->IsDone()) {
            wcout << L"На вобблер типа " << wobbler->GetWobblerType() << L" лучше всего ловить " << getFish(wobbler) << endl;
            It->Next();
        }
    }
};

class getWobblerByType : public IteratorDecorator<Wobbler*> {
private:
    wstring wobblertype;
public:
    getWobblerByType(Iterator<Wobbler*>* it, wstring wtype) : IteratorDecorator<Wobbler*>(it), wobblertype(wtype) {}
    void First() {
        It->First();
        while (!It->IsDone() && It->GetCurrent()->GetWobblerType() != wobblertype) {
            It->Next();
        }
    }
    void Next() {
        It->Next();
        while (!It->IsDone() && It->GetCurrent()->GetWobblerType() != wobblertype) {
            It->Next();
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    size_t stacksize;
    wcout << L"Введите кол-во элементов: ";
    cin >> stacksize;

    ArrayClass<Wobbler*> wobblerArray;
    list<Wobbler*> wobblerList;

    FishingStrategy* strat1 = new AggressiveStrategy();
    FishingStrategy* strat2 = new CautiousStrategy();

    for (size_t i = 0; i < stacksize; i++) {
        FishingStrategy* strategy = (rand() % 2 == 0) ? strat1 : strat2;
        WobblerList type = static_cast<WobblerList>(rand() % 3 + 1);
        Wobbler* wobbler = TakeWobbler(type, strategy);
        wobblerArray.Add(wobbler);
        wobblerList.push_back(wobbler);
    }

    Iterator<Wobbler*>* wobblerIt = new ConstIteratorAdapter<list<Wobbler*>, Wobbler*>(&wobblerList);

    wcout << L"Все вобблеры в массиве:" << endl;
    WobblerActions(wobblerArray.GetIterator());

    wcout << L"\nПрименяем стратегию ловли:" << endl;
    for (wobblerIt->First(); !wobblerIt->IsDone(); wobblerIt->Next()) {
        Wobbler* w = wobblerIt->GetCurrent();
        w->ApplyStrategy();
    }

    delete strat1;
    delete strat2;
    return 0;
}