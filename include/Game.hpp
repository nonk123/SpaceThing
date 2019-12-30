#ifndef GAME_HPP
#define GAME_HPP

#include "irrlicht.h"

#include "World.hpp"
#include "EventReceiver.hpp"

namespace SpaceThing {
    inline struct Session {
        irr::IrrlichtDevice* device;
        irr::video::IVideoDriver* driver;
        irr::scene::ISceneManager* smg;
        irr::gui::IGUIEnvironment* gui;
        const irr::scene::IGeometryCreator* gc;
    } session;

    class Game {
      private:
        void initSession(irr::IrrlichtDevice*);
        void nullSession();

        World world;

      public:
        bool running = true;

        Game() {
        }

        void acceptInput(const EventReceiver& receiver);

        int run();

        ~Game() {
            nullSession();
        }
    };
}

#endif
