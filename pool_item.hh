#pragma once
#include "entity.hh"

class PoolItem : public Entity
{        
    public:
        // Other methods or properties must be here
        const char* name;
        bool active;
        
        PoolItem(const char* newName, bool newActive);

        void update() override; // Provided method, do not change
    
        void draw() override; // Provided method, do not change

};
