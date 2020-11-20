//
// Created by kouushou on 2020/11/19.
//

#include "Object.h"
#include "glad/glad.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace std;
Object::Object(float x, float y, float z):location(x,y,z){
    memset(&modelViewMatrix[0][0],0,sizeof(float )*16);
    for(int i = 0 ; i < 4 ; ++i)modelViewMatrix[i][i] = 1;
}

void Object::init(World&the_world) {}
void Object::rotate(float angle,const glm::vec3 &rotate) {
    memcpy(&modelViewMatrix[0][0],
           &glm::rotate(modelViewMatrix,angle,rotate)[0][0],
           sizeof(float )*16);
}
void Object::move(const glm::vec3 &move) {
    memcpy(&modelViewMatrix[0][0],
           &glm::translate(modelViewMatrix,move)[0][0],
           sizeof(float )*16);

}
Sphere::Sphere(float x, float y, float z, float r) :Object(x,y,z),color(1,1,1){
    this->r=r;

}
void Sphere::setColors(const glm::vec3 &col) {
    this->color = col;
}
void Sphere::addPoint(float x,float y,float z,World&the_world) {
    addPoint(glm::vec3(x,y,z),the_world);
}
void Sphere::addPoint(const glm::vec3 &loca,World&the_world) {
    the_world.points.push_back(loca.x);
    the_world.points.push_back(loca.y);
    the_world.points.push_back(loca.z);
    addColor(color,the_world);
    ++the_world.cnts;
}
void Sphere::addColor(const glm::vec3 &loca,World&the_world) {
    the_world.points.push_back(loca.x);
    the_world.points.push_back(loca.y);
    the_world.points.push_back(loca.z);
}



void Sphere::init(World&the_world) {
    the_world.breaks.push_back(the_world.cnts);
    r*=50;
    float height = location.y+r;
    setColors(glm::vec3(1,1,1));
    addPoint(location.x,height,location.z,the_world);

    for(int i = 0 ; i <4 ; ++i){
        setColors(glm::vec3(i&1,i/2,0));
        addPoint(location.x+r*cos(the_world.Pi/2*i),0,location.z+r*sin(the_world.Pi/2*i),the_world);
    }
    /*
    addPoint(0.5f, -0.5f, 1.0f,the_world);
    addPoint(-0.5f, -0.5f, -1.0f,the_world);
    addPoint(0.0f, 0.0f, 0.0f,the_world);
    */
    the_world.modeViewMatrices.push_back(&modelViewMatrix[0][0]);

    the_world.types.push_back(GL_TRIANGLE_FAN);
    the_world.breaks.push_back(the_world.cnts);
}

void World::load(unsigned int ShaderProgramID) {
    GLuint locas = glGetUniformLocation(ShaderProgramID,"projectionMatrix");
    glUniformMatrix4fv(locas,1,GL_FALSE,cam.getMatrix());
    for(int i = 1 ; i < breaks.size() ; ++i){
        locas = glGetUniformLocation(ShaderProgramID,"modelViewMatrix");
        glUniformMatrix4fv(locas,1,GL_FALSE,modeViewMatrices[i-1]);

        glDrawArrays(types[i-1],breaks[i-1],breaks[i]);
    }

}

void World::init(unsigned int *VAO,unsigned int *VBO) {

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
    //首先绑定顶点数组对象，然后绑定并设置顶点缓冲区，然后配置顶点属性。
    glBindVertexArray((*VAO));

    glBindBuffer(GL_ARRAY_BUFFER, (*VBO));
    glBufferData(GL_ARRAY_BUFFER, pointsSize(), getPoints(), GL_DYNAMIC_DRAW);

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    /*
    glVertexAttribPointer 指定了渲染时索引值为 index 的顶点属性数组的数据格式和位置。
    void glVertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized,
     GLsizei stride,const GLvoid * pointer);
    参数：
    (1)index
    指定要修改的顶点属性的索引值
    (2)size
    指定每个顶点属性的组件数量。必须为1、2、3或者4。初始值为4。（如position是由3个（x,y,z）组成，而颜色是4个（r,g,b,a））
    (4)type
    指定数组中每个组件的数据类型。可用的符号常量有GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT,GL_UNSIGNED_SHORT, GL_FIXED, 和 GL_FLOAT，初始值为GL_FLOAT。
    (5)normalized
    指定当被访问时，固定点数据值是否应该被归一化（GL_TRUE）或者直接转换为固定点值（GL_FALSE）。
    (6)stride
    指定连续顶点属性之间的偏移量。如果为0，那么顶点属性会被理解为：它们是紧密排列在一起的。初始值为0。
    (7)pointer
    指定第一个组件在数组的第一个顶点属性中的偏移量。该数组与GL_ARRAY_BUFFER绑定，储存于缓冲区中。初始值为0；
    */
}