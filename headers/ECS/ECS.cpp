//
// Created by Jakub Górski on 17/06/2022.
//

#include "ECS/ECS.h"
void Entity::addGroup(Group _group) {
    groupBitset[_group] = true;
    mManager.addToGroup(this, _group);
}