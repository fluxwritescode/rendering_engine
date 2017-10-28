#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#endif
#ifdef __unix__
    #include <SDL2/SDL.h>
#endif
#ifdef _WIN32
    #include <SDL.h>
#endif

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <ctime>
#include <vector>

#include "../gpu/shader.h"
#include "../gpu/shader_storage_buffer.hpp"
#include "../3d/cube.h"


namespace Framework {
    class Pointlight {
    public:
        Pointlight();
        void Init(const GLuint nr_lights);
        void RandomizePosition();
        void Render(const glm::mat4 &view);
        void RenderLightBox(const glm::mat4 &projection, const glm::mat4 &view, glm::mat4 &model);

    private:
        struct Light {
            glm::vec4 Position;
            glm::vec4 Color;
            float Linear;
            float Quadratic;
            float Radius;
            float padding;
        };

        const GLfloat constant;
        const GLfloat linear;
        const GLfloat quadratic;
        int           m_lightCount;

        glm::vec4 GetRandomPosition();
        glm::vec4 GetRandomColor();

        std::vector<Light>     m_lights;
        std::vector<glm::vec3> m_lightRandoms;

        Shader m_shaderLightingPass;
        Shader m_shaderLightBox;

        ShaderStorageBuffer m_ssbo;

        Cube m_lightCube;
    };
}

#endif
