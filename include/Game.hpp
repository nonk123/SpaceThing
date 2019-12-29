#ifndef SPACE_THING_HPP
#define SPACE_THING_HPP

#include "irrlicht.h"

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
