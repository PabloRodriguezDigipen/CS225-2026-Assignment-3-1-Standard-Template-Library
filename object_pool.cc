#include "object_pool.hh"

void ObjectPool::add(PoolItem& newItem){
    items.push_back(&newItem);
}

int ObjectPool::count(){
    return items.size();
}

int ObjectPool::countActive(){
    TotalActivesFunctor activesCount;

    std::for_each(items.begin(), items.end(), std::ref(activesCount));

    return activesCount.totalActives;
}

PoolItem* ObjectPool::findByName(const char* name){
    NameFinderFunctor finder;
    finder.nameToFind = name;

    std::vector<PoolItem*>::iterator it;

    it = std::find_if(items.begin(), items.end(), finder);

    if (it != items.end()) {
        return *it;
    }

    return nullptr;
}

PoolItem* ObjectPool::findByRef(PoolItem& item){
    ReferenceFinderFunctor finder;
    finder.itemToFind = &item;

    std::vector<PoolItem*>::iterator it;

    it = std::find_if(items.begin(), items.end(), finder);

    if (it != items.end()) {
        return *it;
    }

    return nullptr;
}

void ObjectPool::activate(const char* name){
    PoolItem* item = findByName(name);
    item->active = true;
}
void ObjectPool::deactivate(const char* name){
    PoolItem* item = findByName(name);
    item->active = false;
}

void ObjectPool::updateAll(){
    UpdaterFunctor updater;
    std::for_each(items.begin(), items.end(), std::ref(updater));
}

void ObjectPool::drawAll(){
    DrawerFunctor drawer;
    std::for_each(items.begin(), items.end(), std::ref(drawer));
}

void ObjectPool::updateActive(){
    SelectiveUpdaterFunctor updater;
    std::for_each(items.begin(), items.end(), std::ref(updater));
}

void ObjectPool::drawActive(){
    SelectiveDrawerFunctor updater;
    std::for_each(items.begin(), items.end(), std::ref(updater));
}

void ObjectPool::removeByName(const char* name){
    NameFinderFunctor finder;
    finder.nameToFind = name;

    auto it = std::remove_if(items.begin(), items.end(), finder);

    items.erase(it, items.end());
}

void ObjectPool::removeInactive(){
    ActiveFinderFunctor finder;

    auto it = std::remove_if(items.begin(), items.end(), finder);

    items.erase(it, items.end());
}