#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>

#include "Entity.hpp"

namespace SpaceThing {
    class World {
      private:
        std::vector<std::unique_ptr<Entity>> entities;

      public:
        World() {
        }

        void add(Entity* entity) {
            entities.push_back(std::unique_ptr<Entity>(entity));
            entity->addTo(this);
        }

        void remove(Entity* entity) {
            for (auto it = entities.begin(); it != entities.end(); it++)
                if (it->get() == entity)
                    entities.erase(it);
        }

        void update() {
            for (auto& entity : entities)
                entity->update();
        }
    };
}

#endif
