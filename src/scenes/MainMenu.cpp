#include "engine/Scene.hpp"

class MenuScene : public Scene {
    public:
        SceneDrawData getDrawData() const override {
            SceneDrawData data;
            data.topText = "Ahoy!";
            data.art = "#'asd#'a#sd";
            data.menuOptions = {
                "1) Set Sail",
                "2) Fire Cannons",
                "3) Abandon Ship"
            };
            data.inputPrompt = "> ";

            return data;
        };
};