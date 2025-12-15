#pragma once
#include <string>
#include "engine/SceneDrawData.hpp"
#include "engine/InputEvent.hpp"

class Renderer {
    public:
        virtual ~Renderer() = default;
        virtual void render(const SceneDrawData& data) = 0;
        virtual InputEvent pollInput() = 0;
};