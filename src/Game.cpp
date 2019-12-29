#include "Game.hpp"

#include <iostream>

#include "Utils.hpp"

#include "config.hpp"

using namespace SpaceThing;
using namespace Utils;

void Game::initSession(irr::IrrlichtDevice* device) {
    session.device = device;
    session.driver = device->getVideoDriver();
    session.smg = device->getSceneManager();
    session.gui = device->getGUIEnvironment();
    session.gc = session.smg->getGeometryCreator();
}

void Game::nullSession() {
    session.device = nullptr;
    session.driver = nullptr;
    session.smg = nullptr;
    session.gui = nullptr;
    session.gc = nullptr;
}

void Game::acceptInput(const EventReceiver& receiver) {
    if (receiver.isDown(irr::KEY_KEY_Q))
        running = false;
}

int Game::run() {
    EventReceiver receiver;
    IrrPtr<irr::IrrlichtDevice> device(irr::createDevice(VIDEO_DRIVER,
                                                         {800, 600},
                                                         32,
                                                         false, false, false,
                                                         &receiver));
    initSession(device.get());

    device->setWindowCaption(L"Space Thing");

    session.gui->addStaticText(L"Q to quit", {0, 0, 100, 10})
        ->setOverrideColor({255, 255, 255, 255});

    while (running && device->run()) {
        session.driver->beginScene(true, true, {255, 8, 8, 10});

        acceptInput(receiver);

        session.smg->drawAll();
        session.gui->drawAll();

        session.driver->endScene();
    }

    return 0;
}
