#ifndef SIMPLE_ENTITY_HPP
#define SIMPLE_ENTITY_HPP

#include "Entity.hpp"
#include "RenderUtils.hpp"

namespace SpaceThing {
    class SimpleEntity : public Entity {
      private:
        std::unique_ptr<IMesh> mesh;
        ISceneNode* node = nullptr;

      public:
        SimpleEntity(irr::scene::IMesh* mesh) : mesh(mesh) {
        }

        virtual void addNodes() override {
            this->node = session.smg->addMeshSceneNode(mesh.get());
        }

        virtual void removeNodes() override {
            this->node->remove();
        }
    };
}

#endif
