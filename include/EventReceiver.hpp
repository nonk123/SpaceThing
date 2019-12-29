#ifndef EVENT_RECEIVER_HPP
#define EVENT_RECEIVER_HPP

#include "irrlicht.h"

namespace SpaceThing {
    class EventReceiver : public irr::IEventReceiver {
      private:
        bool keys[irr::KEY_KEY_CODES_COUNT];

      public:
        EventReceiver() {
            clear();
        }

        bool OnEvent(const irr::SEvent& event) override {
            if (event.EventType == irr::EET_KEY_INPUT_EVENT)
                keys[event.KeyInput.Key] = event.KeyInput.PressedDown;
            return false;
        }

        void clear() {
            for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
                keys[i] = false;
        }

        bool isDown(irr::EKEY_CODE code) const {
            return keys[code];
        }

        bool isUp(irr::EKEY_CODE code) const {
            return !isDown(code);
        }
    };

}

#endif
