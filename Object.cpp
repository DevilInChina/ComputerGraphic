//
// Created by kouushou on 2020/11/19.
//

#include "Object.h"
#include "glad/glad.h"
using namespace std;
Object::Object(float x, float y, float z):location(x,y,z){
}

void Object::init(World&the_world) {}

Sphere::Sphere(float x, float y, float z, float r) :Object(x,y,z),color(1,1,1){
    this->r=r;

}
void Sphere::setColors(const vec3 &col) {
    this->color = col;
}
void Sphere::addPoint(float x,float y,float z,World&the_world) {
    addPoint(vec3(x,y,z),the_world);
}
void Sphere::addPoint(const vec3 &loca,World&the_world) {
    the_world.points.push_back(loca.x());
    the_world.points.push_back(loca.y());
    the_world.points.push_back(loca.z());
    addColor(color,the_world);
    ++the_world.cnts;
}
void Sphere::addColor(const vec3 &loca,World&the_world) {
    the_world.points.push_back(loca.x());
    the_world.points.push_back(loca.y());
    the_world.points.push_back(loca.z());
}



void Sphere::init(World&the_world) {
    the_world.breaks.push_back(the_world.cnts);
    float height = location.y()+r;
    addPoint(0.5f, -0.5f, 1.0f,the_world);
    addPoint(-0.5f, -0.5f, -1.0f,the_world);
    addPoint(0.0f, 0.0f, 0.0f,the_world);
    the_world.types.push_back(GL_TRIANGLE_FAN);
    the_world.breaks.push_back(the_world.cnts);
}

void World::load() {
    for(int i = 1 ; i < breaks.size() ; ++i){
        glDrawArrays(types[i-1],breaks[i-1],breaks[i]);
    }
}