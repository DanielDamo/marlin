#pragma once
#include <unordered_map>
#include <functional>
#include <memory>

#include "engine/Scene.hpp"

class Test : public Scene {
public:
    Test();
    ~Test() override = default;

    void onEnter(GameState&) override;
    void onExit(GameState&) override;
    void update(GameState&, float dt) override;

    SceneDrawData getDrawData() const override;
};
