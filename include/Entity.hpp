#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "irrlicht.h"

#include <vector>

namespace SpaceThing {
    class World;
}

#include "World.hpp"
#include "Game.hpp"

using irr::scene::IMesh;
using irr::scene::ISceneNode;

namespace SpaceThing {
    class Entity {
      private:
        World* world = nullptr;

      public:
        void addTo(World* world) {
            this->world = world;
            addNodes();
        }

        void onRemove() {
            removeNodes();
            this->world = nullptr;
        }

      protected:
        virtual void addNodes() {
        }

        virtual void removeNodes() {
        }

      public:
        virtual void update() {
        }

        ~Entity() {
            onRemove();
        }
    };
}

#endif
