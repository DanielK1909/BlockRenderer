#include "RenderWindow.h"

#include "Log.h"

#include <glm/gtc/matrix_transform.hpp>

std::vector<RenderWindow*> RenderWindow::window_instances_;

RenderWindow::RenderWindow(const char* title) {
    window_instances_.push_back(this);

    vao_ = 0;
    vbo_ = 0;
    ebo_ = 0;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfw_window_ = glfwCreateWindow(config_.window_width_, config_.window_height_, title, NULL, NULL);

    if (!glfw_window_) {
        Log::error("Could not create GLFW window.");
        return;
    }

    glfwMakeContextCurrent(glfw_window_);

    glfwSetFramebufferSizeCallback(glfw_window_, windowSizeCallback);

    gladLoadGL();
    glViewport(0, 0, config_.window_width_, config_.window_height_);

    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);
    glGenVertexArrays(1, &vao_);

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture co-ord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    // Repeat textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Load 2D sprite shader (no 3D transforms) and 3D shader
    sm_.loadShaderProgram("glsl/sprite_shader.vert", "glsl/sprite_shader.frag");
    sm_.loadShaderProgram("glsl/3d_default.vert", "glsl/3d_default.frag");

    input_.setGLFWWindow(glfw_window_);

}

RenderWindow::~RenderWindow() {
    // Remove deleted RenderWindow from instances vector
    std::remove(window_instances_.begin(), window_instances_.end(), this);
}

bool RenderWindow::beginFrame() {
    // Update event polling (input etc.) in GLFW
    glfwPollEvents();

    // Clear the screen and set its colour to the specified background colour
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    game_objects_.clear();
    sprites_.clear();

    return !glfwWindowShouldClose(glfw_window_);
}

bool RenderWindow::endFrame() {
    camera_.update();

    render3d();

    // reset depth buffer for 2d sprites
    glClear(GL_DEPTH_BUFFER_BIT);
    drawSprites();

    glfwSwapBuffers(glfw_window_);

    return true;
}

void RenderWindow::renderObject(GameObject* object) {
    game_objects_.push_back(object);
}

void RenderWindow::drawSprite(Sprite* sprite) {
    sprites_.push_back(sprite);
}

void RenderWindow::windowSizeCallback(GLFWwindow* window, int width, int height) {
    for (RenderWindow* w : window_instances_) {
        if (window == w->getGLFWWindow()) {
            auto config = w->getConfig();
            config.window_width_ = width;
            config.window_height_ = height;

            glViewport(0, 0, width, height);
        }
    }
}

void RenderWindow::drawSprites() {
    sm_.useShaderProgram(0);

    glBufferData(GL_ARRAY_BUFFER, sizeof(SPRITE_BOX), SPRITE_BOX, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SPRITE_INDEX), SPRITE_INDEX, GL_STATIC_DRAW);

    glm::mat4 view_mat(1.f);
    view_mat = glm::scale(view_mat, glm::vec3(1.f / config_.render_width_, 1.f / config_.render_height_, 1.f));
    view_mat = glm::scale(view_mat, glm::vec3(((float)config_.window_width_ / (float)config_.render_width_), ((float)config_.window_height_ / (float)config_.render_height_), 1));

    sm_.setUniformMat4(0, "view", view_mat);

    for (Sprite* s : sprites_) {
        s->getTexture()->apply();

        sm_.setUniformMat4(0, "sprite", s->getTransform());

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void RenderWindow::render3d() {
    sm_.useShaderProgram(0);

    glm::mat4 view_mat(1.f);
    view_mat = camera_.getLookAtMatrix();
    sm_.setUniformMat4(1, "view", view_mat);

    glm::mat4 proj_mat(1.f);
    proj_mat = glm::perspective(glm::radians(config_.fov_), ((float)config_.render_width_ / (float)config_.render_height_), 0.1f, 100.0f);
    sm_.setUniformMat4(1, "projection", proj_mat);

    for (GameObject* g : game_objects_) {
        sm_.setUniformMat4(1, "model", g->getTransform());

        glBufferData(GL_ARRAY_BUFFER, g->getDataSize() * sizeof(float), g->getData(), GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, g->getIndexSize() * sizeof(unsigned int), g->getIndex(), GL_STATIC_DRAW);

        glDrawElements(GL_TRIANGLES, g->getIndexSize(), GL_UNSIGNED_INT, 0);
    }

}
