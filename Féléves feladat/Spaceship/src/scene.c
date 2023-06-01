#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->spaceship), "assets/models/ss.obj");
    scene->object_texture_id = load_texture("assets/textures/1_Default_color.jpg");

    for(int i = 0; i < 12; i++){
        load_model(&(scene->asteroid[i]), "assets/models/Cliff_Rock_Two.obj");
    }
    
    scene->asteroid_texture_id = load_texture("assets/textures/Cliff_Rock_Two_BaseColor.png");

    scene->instructions_texture = load_texture("assets/textures/instructions.jpg");

    scene->obj_position.x = 10.0f;
    scene->obj_position.y = 0.0f;
    scene->obj_position.z = 0.0f;
    
    //Aszteroida pozíciók
    scene->asteroid_position[0].x = 500.0f;
    scene->asteroid_position[0].y = -100.0f;
    scene->asteroid_position[0].z = 0.0f;

    scene->asteroid_position[1].x = 100.0f;
    scene->asteroid_position[1].y = 200.0f;
    scene->asteroid_position[1].z = 0.0f;

    scene->asteroid_position[2].x = -400.0f;
    scene->asteroid_position[2].y = 300.0f;
    scene->asteroid_position[2].z = 0.0f;

    scene->asteroid_position[3].x = 200.0f;
    scene->asteroid_position[3].y = -200.0f;
    scene->asteroid_position[3].z = 0.0f;

    scene->asteroid_position[4].x = 300.0f;
    scene->asteroid_position[4].y = -300.0f;
    scene->asteroid_position[4].z = 0.0f;

    scene->asteroid_position[5].x = -200.0f;
    scene->asteroid_position[5].y = 400.0f;
    scene->asteroid_position[5].z = 0.0f;

    scene->asteroid_position[6].x = -100.0f;
    scene->asteroid_position[6].y = -400.0f;
    scene->asteroid_position[6].z = 0.0f;

    scene->asteroid_position[7].x = -300.0f;
    scene->asteroid_position[7].y = 100.0f;
    scene->asteroid_position[7].z = 0.0f;

    scene->asteroid_position[8].x = 0.0f;
    scene->asteroid_position[8].y = 500.0f;
    scene->asteroid_position[8].z = 0.0f;

    scene->asteroid_position[9].x = 200.0f;
    scene->asteroid_position[9].y = 600.0f;
    scene->asteroid_position[9].z = 0.0f;

    scene->asteroid_position[10].x = -400.0f;
    scene->asteroid_position[10].y = -700.0f;
    scene->asteroid_position[10].z = 0.0f;

    scene->asteroid_position[11].x = 100.0f;
    scene->asteroid_position[11].y = -800.0f;
    scene->asteroid_position[11].z = 0.0f;

    scene->movement_speed = 0.5f;

    scene->rotation = 90.0f;

    scene->brightness = 1.0f;

    scene->speed = 0.0f;

    scene->is_instructions_on = 0;

    //Skybox textúrák
    scene->texture_ids[0] = load_texture("assets/textures/bkg1_back.png");
    scene->texture_ids[1] = load_texture("assets/textures/bkg1_bot.png");
    scene->texture_ids[2] = load_texture("assets/textures/bkg1_front.png");
    scene->texture_ids[3] = load_texture("assets/textures/bkg1_left.png");
    scene->texture_ids[4] = load_texture("assets/textures/bkg1_right.png");
    scene->texture_ids[5] = load_texture("assets/textures/bkg1_top.png");

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 0.5;
    scene->material.diffuse.green = 0.5;
    scene->material.diffuse.blue = 0.5;

    scene->material.specular.red = 0.5;
    scene->material.specular.green = 0.5;
    scene->material.specular.blue = 0.5;

    scene->material.shininess = 0.0;
}

void set_lighting(float brightness)
{
    float ambient_light[] = { brightness, brightness, brightness, brightness };
    float diffuse_light[] = { brightness, brightness, brightness, brightness };
    float specular_light[] = { brightness, brightness, brightness, brightness };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene)
{
    for(int i = 0; i < 5; i++)
    {
        scene->asteroid_position[i].z += scene->movement_speed;
    }

    for(int i = 5; i < 12; i++)
    {
        scene->asteroid_position[i].z -= scene->movement_speed;
    }

    if (scene->asteroid_position[0].z >= 50.0f) {
        scene->movement_speed = -0.5f;
        return;
    } else if (scene->asteroid_position[0].z <= -50.0f) {
        scene->movement_speed = 0.5f;
        return;
    }
}

void render_scene(Scene* scene)
{
    move_object(scene);

    //Skybox --

    //Bottom oldal
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, scene->texture_ids[1]);
    glScalef(50.0f, 50.0f, 50.0f);
    draw_skybox_bottom();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Top oldal
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, scene->texture_ids[5]);
    glScalef(50.0f, 50.0f, 50.0f);
    draw_skybox_top();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Left oldal
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, scene->texture_ids[3]);
    glRotatef(-90, 1, 0, 0);
    glScalef(50.0f, 50.0f, 50.0f);
    draw_skybox_left();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Right oldal
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, scene->texture_ids[4]);
    glScalef(50.0f, 50.0f, 50.0f);
    glRotatef(-90, 1, 0, 0);
    draw_skybox_right();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Back
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, scene->texture_ids[0]);
    glScalef(50.0f, 50.0f, 50.0f);
    glRotatef(180, 0, 1, 0);
    draw_skybox_back();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Front oldal
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, scene->texture_ids[2]);
    glScalef(50.0f, 50.0f, 50.0f);
    draw_skybox_front();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Skybox--

    set_material(&(scene->material));
    set_lighting(scene->brightness);

    for(int i = 0; i < 4; i++){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->asteroid_texture_id);
        glEnable(GL_TEXTURE_2D);
        glScalef(0.01, 0.01, 0.01);
        glTranslatef(scene->asteroid_position[i].x, scene->asteroid_position[i].y, scene->asteroid_position[i].z);
        draw_model(&(scene->asteroid[i]));
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }

    for(int i = 4; i < 7; i++){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->asteroid_texture_id);
        glEnable(GL_TEXTURE_2D);
        glScalef(0.02, 0.02, 0.02);
        glTranslatef(scene->asteroid_position[i].x, scene->asteroid_position[i].y, scene->asteroid_position[i].z);
        draw_model(&(scene->asteroid[i]));
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }

    for(int i = 7; i < 12; i++){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->asteroid_texture_id);
        glEnable(GL_TEXTURE_2D);
        glScalef(0.04, 0.04, 0.04);
        glTranslatef(scene->asteroid_position[i].x, scene->asteroid_position[i].y, scene->asteroid_position[i].z);
        draw_model(&(scene->asteroid[i]));
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, scene->object_texture_id);
    glScalef(0.1f, 0.1f, 0.1f);
    glTranslatef(scene->obj_position.x, scene->obj_position.y, scene->obj_position.z+5);
    glRotatef(90, 1, 0, 0);
    glRotatef(scene->rotation, 0, 1, 0);
    draw_model(&(scene->spaceship));
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    if(scene->is_instructions_on == 1){
        show_instructions(scene);
    } 
}

void draw_skybox_bottom()
{

    glEnable(GL_TEXTURE_2D);

    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBegin(GL_QUADS);

    // Hátsó oldal
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    glEnd();
}

void draw_skybox_top()
{
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    // Elülső oldal
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();
}

void draw_skybox_left()
{
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    // Bal oldal
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    glEnd();
}

void draw_skybox_right()
{
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    // Jobb oldal
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    glEnd();
}

void draw_skybox_back()
{
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    // Plafon
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    glEnd();
}

void draw_skybox_front()
{
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    // Alsó oldal
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    glEnd();
}

void move_object(Scene* scene)
{
    float angle_rad = (scene->rotation - 90) * M_PI / 180.0;

    scene->obj_position.x += cos(angle_rad)*scene->speed;
    scene->obj_position.y += sin(angle_rad)*scene->speed;
        
}

vec3 get_position(Scene* scene)
{
    return scene->obj_position;
}

void show_instructions(Scene* scene)
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, scene->instructions_texture);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex3f(-2, 1.5f, -3);
    glTexCoord2f(1, 0);
    glVertex3f(2, 1.5f, -3);
    glTexCoord2f(1, 1);
    glVertex3f(2, -1.5f, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-2, -1.5f, -3);
    
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
}

void reset_spaceship(Scene* scene)
{
    scene->obj_position.x = 10.0f;
    scene->obj_position.y = 0.0f;
    scene->obj_position.z = 0.0f;
    scene->rotation = 90.0f;
}