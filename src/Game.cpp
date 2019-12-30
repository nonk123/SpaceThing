#include "Game.hpp"

#include <algorithm>

#include "Utils.hpp"
#include "SimpleEntity.hpp"
#include "RenderUtils.hpp"
#include "Math.hpp"

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

static irr::f32 cameraPitch = Pi<irr::f32>;
static irr::f32 cameraYaw = HalfPi<irr::f32>;
static irr::f32 cameraRadius = 20;

static irr::scene::ICameraSceneNode* camera = nullptr;

void Game::acceptInput(const EventReceiver& receiver) {
    if (receiver.isDown(irr::KEY_KEY_Q))
        running = false;

    irr::f32 dp = 0, dy = 0;
    static const irr::f32 d = Pi<irr::f32> / 32;
    static const irr::f32 r = 0.5;

    if (receiver.isDown(irr::KEY_KEY_A))
        dy = -d;
    else if (receiver.isDown(irr::KEY_KEY_D))
        dy = +d;

    if (receiver.isDown(irr::KEY_KEY_W))
        dp = +d;
    else if (receiver.isDown(irr::KEY_KEY_S))
        dp = -d;

    if (receiver.isDown(irr::KEY_KEY_R))
        cameraRadius -= r;
    else if (receiver.isDown(irr::KEY_KEY_F))
        cameraRadius += r;

    cameraRadius = std::clamp(cameraRadius, irr::f32(0.05), irr::f32(25));

    cameraPitch += dp;
    cameraPitch = std::clamp(cameraPitch, -HalfPi<irr::f32>, HalfPi<irr::f32>);

    cameraYaw += dy;

    if (cameraYaw < 0)
        cameraYaw = Pi2<irr::f32>;
    else if (cameraYaw > Pi2<irr::f32>)
        cameraYaw = 0;

    const irr::core::vector3df origin(2.5, 2.5, 2.5);

    camera->setPosition(origin + irr::core::vector3df(std::cos(cameraYaw),
                                                      std::sin(cameraPitch),
                                                      std::sin(cameraYaw))
                        * cameraRadius);
    camera->setTarget(origin);
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

    camera = session.smg->addCameraSceneNode();

    session.gui->addStaticText(L"Q to quit", {0, 0, 100, 10})
        ->setOverrideColor({255, 255, 255, 255});

    session.smg->addLightSceneNode(nullptr, {12.5,  10, 12.5});

    world.add(new SimpleEntity(box({5, 5, 5}, {255, 255, 255, 255})));

    while (running && device->run()) {
        session.driver->beginScene(true, true, {255, 8, 8, 10});

        acceptInput(receiver);
        world.update();

        session.smg->drawAll();
        session.gui->drawAll();

        session.driver->endScene();
    }

    return 0;
}
