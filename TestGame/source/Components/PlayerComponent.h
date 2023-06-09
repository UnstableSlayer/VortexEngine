#include <VortexEngine.h>

namespace TestGameComponents
{
    struct PlayerComponent
    {
        glm::vec2 maxVelocity;
        glm::vec2 currentVelocity;
        glm::vec2 acceleration;
        glm::vec2 drag;
        float health;

        Vortex::SpriteComponent tankBody;

        Vortex::TransformComponent headTransform;
        Vortex::SpriteComponent tankHead;
    };

}
