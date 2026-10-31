#include "pool_item.hh"

PoolItem::PoolItem(const char* newName, bool newActive){
    name = newName;
    active = newActive;
}

void PoolItem::update() {
    //Do not change or delete this line
    Entity::updateBase();            
}

void PoolItem::draw() {
    //Do not change or delete this line
    Entity::drawBase();
}

// Other methods must be here
