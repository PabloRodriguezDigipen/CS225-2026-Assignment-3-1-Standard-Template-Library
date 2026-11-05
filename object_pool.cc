#include "object_pool.hh"

void ObjectPool::add(PoolItem& newItem){
    //add the given item to the container
    items.push_back(&newItem);
}

int ObjectPool::count(){
    //get the size of the container
    return items.size();
}

int ObjectPool::countActive(){
    //loop in a for each using a functor to count the active items
    TotalActivesFunctor activesCount;
    std::for_each(items.begin(), items.end(), std::ref(activesCount));

    return activesCount.totalActives;
}

PoolItem* ObjectPool::findByName(const char* name){
    //set the functors name
    NameFinderFunctor finder;
    finder.nameToFind = name;

    //loop in a for each using the functor to find the item
    auto it = std::find_if(items.begin(), items.end(), finder);

    //return the item if it exists
    if (it != items.end())
        return *it;
    return nullptr;
}

PoolItem* ObjectPool::findByRef(PoolItem& item){
    //set the functors reference
    ReferenceFinderFunctor finder;
    finder.itemToFind = &item;

    //loop in a for each using the functor to find the item
    auto it = std::find_if(items.begin(), items.end(), finder);

    //return the item if it exists
    if (it != items.end())
        return *it;
    return nullptr;
}

void ObjectPool::activate(const char* name){
    //call the name finder
    PoolItem* item = findByName(name);
    //activate the item
    item->active = true;
}
void ObjectPool::deactivate(const char* name){
    //call the name finder
    PoolItem* item = findByName(name);
    //deactivate the item
    item->active = false;
}

void ObjectPool::updateAll(){
    //loop the vector with a for loop and use a functor to update all the items
    UpdaterFunctor updater;
    std::for_each(items.begin(), items.end(), std::ref(updater));
}

void ObjectPool::drawAll(){
    //loop the vector with a for loop and use a functor to draw all the items
    DrawerFunctor drawer;
    std::for_each(items.begin(), items.end(), std::ref(drawer));
}

void ObjectPool::updateActive(){
    //loop the vector with a for loop and use a functor to update the active items
    SelectiveUpdaterFunctor updater;
    std::for_each(items.begin(), items.end(), std::ref(updater));
}

void ObjectPool::drawActive(){
    //loop the vector with a for loop and use a functor to draw the active items
    SelectiveDrawerFunctor updater;
    std::for_each(items.begin(), items.end(), std::ref(updater));
}

void ObjectPool::removeByName(const char* name){
    //set the functors name
    NameFinderFunctor finder;
    finder.nameToFind = name;

    //loop using the functor to find the item
    auto it = std::remove_if(items.begin(), items.end(), finder);

    //delete the item from the vector
    items.erase(it, items.end());
}

void ObjectPool::removeInactive(){
    //loop with an active finder functor
    ActiveFinderFunctor finder;
    auto it = std::remove_if(items.begin(), items.end(), finder);

    //delete the items
    items.erase(it, items.end());
}