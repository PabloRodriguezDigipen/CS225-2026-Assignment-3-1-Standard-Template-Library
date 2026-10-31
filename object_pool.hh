#pragma once
#include "entity.hh"
#include <vector>
#include <algorithm>
#include "pool_item.hh"

struct TotalActivesFunctor {
    int totalActives = 0;

    void operator()(PoolItem* p) {
        if (p->active)
            totalActives++;
    }
};

struct NameFinderFunctor {
    const char* nameToFind;

    bool operator()(PoolItem* p) {
        return (p->name == nameToFind);
    }
};

struct ReferenceFinderFunctor {
    PoolItem* itemToFind;

    bool operator()(PoolItem* p) {
        return (p == itemToFind);
    }
};

struct UpdaterFunctor {
    void operator()(PoolItem* p) {
        p->update();
    }
};

struct DrawerFunctor {
    void operator()(PoolItem* p) {
        p->draw();
    }
};

struct SelectiveUpdaterFunctor {
    void operator()(PoolItem* p) {
        if (p->active)
            p->update();
    }
};

struct SelectiveDrawerFunctor {
    void operator()(PoolItem* p) {
        if (p->active)
            p->draw();
    }
};

struct ActiveFinderFunctor {
    bool operator()(PoolItem* p) {
        return p->active == false;
    }
};

class ObjectPool
{
    std::vector<PoolItem*>(items);
public:
    void add(PoolItem& newItem);
    int count();
    int countActive();
    PoolItem* findByName(const char* name);
    PoolItem* findByRef(PoolItem& item);
    void activate(const char* name);
    void deactivate(const char* name);
    void updateAll();
    void drawAll();
    void updateActive();
    void drawActive();
    void removeByName(const char* name);
    void removeInactive();
};