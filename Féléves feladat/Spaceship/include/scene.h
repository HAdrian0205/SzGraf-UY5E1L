#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>
#include <SDL2/SDL.h>

typedef struct Scene
{
    Model spaceship;
    Model asteroid[12];
    Model sphere;
    Material material;
    vec3 obj_position;
    vec3 asteroid_position[12];
    GLuint object_texture_id;
    GLuint texture_ids[6];
    GLuint asteroid_texture_id;
    float movement_speed;
    float rotation;
    float brightness;
    GLuint instructions_texture;
    int is_instructions_on;
    float speed;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(float brightness);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene);

/**
 * Render the scene objects.
 */
void render_scene(Scene* scene);

void draw_skybox_top();
void draw_skybox_bottom();
void draw_skybox_front();
void draw_skybox_back();
void draw_skybox_left();
void draw_skybox_right();

void move_object(Scene* scene);

vec3 get_position(Scene* scene);

void show_instructions(Scene* scene);

void reset_spaceship(Scene* scene);

#endif /* SCENE_H */
