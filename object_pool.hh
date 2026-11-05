#pragma once
#include "entity.hh"
#include <vector>
#include <algorithm>
#include "pool_item.hh"

//functor to count all active items
struct TotalActivesFunctor {
    int totalActives = 0;

    void operator()(PoolItem* p) {
        if (p->active)
            totalActives++;
    }
};

//functor to find an item with specific name
struct NameFinderFunctor {
    const char* nameToFind;

    bool operator()(PoolItem* p) {
        return (p->name == nameToFind);
    }
};

//functor to find object with specific reference
struct ReferenceFinderFunctor {
    PoolItem* itemToFind;

    bool operator()(PoolItem* p) {
        return (p == itemToFind);
    }
};

//functor to update all items
struct UpdaterFunctor {
    void operator()(PoolItem* p) {
        p->update();
    }
};

//functor to draw all items
struct DrawerFunctor {
    void operator()(PoolItem* p) {
        p->draw();
    }
};

//functor to update all active items
struct SelectiveUpdaterFunctor {
    void operator()(PoolItem* p) {
        if (p->active)
            p->update();
    }
};

//functor to draw all active items
struct SelectiveDrawerFunctor {
    void operator()(PoolItem* p) {
        if (p->active)
            p->draw();
    }
};

//functor tha gives all inactive items
struct ActiveFinderFunctor {
    bool operator()(PoolItem* p) {
        return p->active == false;
    }
};

class ObjectPool
{
private:
    //container of items
    std::vector<PoolItem*>(items);
public:
    //function to add items
    void add(PoolItem& newItem);
    //function to count items
    int count();
    //function to count active items
    int countActive();
    //function to find items by name
    PoolItem* findByName(const char* name);
    //function to find items by reference
    PoolItem* findByRef(PoolItem& item);
    //function to activate items
    void activate(const char* name);
    //function to deactivate items
    void deactivate(const char* name);
    //function to update all items
    void updateAll();
    //function to draw all items
    void drawAll();
    //function to update active items
    void updateActive();
    //function to draw active items
    void drawActive();
    //function to remove items by name
    void removeByName(const char* name);
    //function to remove inactive items
    void removeInactive();
};