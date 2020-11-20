//
// Created by kouushou on 2020/11/19.
//

#ifndef CG_OBJECT_H
#define CG_OBJECT_H

#include <bits/stdc++.h>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera{
    float l,r,b,t,n,f;
    glm::mat4x4 projectionMatrix;
    float lookat[4];
    float w,h,_n,_f;
    void load4ofmtx(int row,float _x,float _y,float _z,float _w){
        projectionMatrix[row].x=_x;
        projectionMatrix[row].y=_y;
        projectionMatrix[row].z=_z;
        projectionMatrix[row].w=_w;

    }
    void initMatrix() {
        // -1 = (n-f)/(f-n)
        //
        //*
        /*load4ofmtx(0, 2 / (r - l), 0, 0, -(r + l) / (r - l));
        load4ofmtx(1, 0, 2 / (t - b), 0, -(t + b) / (t - b));
        load4ofmtx(2, 0, 0, -2 / (f - n), -(f + n) / (f - n));
        load4ofmtx(3, 0, 0, 0, 1);
         */
        load4ofmtx(0, 2 *n/ (r - l), 0, (r + l) / (r - l),0);
        load4ofmtx(1, 0, 2*n / (t - b),  (t + b) / (t - b),0);
        load4ofmtx(2, 0, 0, -(f+n) / (f - n), -2*f * n / (f - n));
        load4ofmtx(3, 0, 0, -1, 0);
        //*/


    }

public:
    glm::vec3 location;
    explicit Camera(float x=0,float y=0,float z=0):location(x,y,z){}
    void initializeCameraValue(){
        l = location.x - w / 2;
        r = location.x + w / 2;
        t = location.y + h / 2;
        b = location.y - h / 2;
        f = location.z - _f;
        n = location.z - _n;
        initMatrix();
    }
    void setWH(float _w,float _h,float d_n,float d_f) {
        w = _w;
        h = _h;
        if(d_f!=INFINITY) {
            _f = d_f;
        }
        if(d_n!=INFINITY) {
            _n = d_n;
        }
        initializeCameraValue();
        lookat[0] = 0;
        lookat[1] = 0;
        lookat[2] = -1;
        lookat[3] = 1;

    }
    void updateMatrix(){

    }
    float *getMatrix(){
        return &projectionMatrix[0][0];
    }
};
class World{
public:
    Camera cam;
    std::vector<float> points;
    std::vector<int> breaks;
    std::vector<unsigned int> types;
    std::vector<float*>modeViewMatrices;
    explicit World():cam(0,0,0){}
    int cnts = 0;
    const float Pi=acos(-1.0);
    void load(unsigned int ShaderProgramID);
    void showSelf(){
        int _in_cnt = 0;
        for(auto it : points){
            if(_in_cnt++%6==0){
                printf("\n");
            }
            printf("%f ",it);

        }
    }
    float * getPoints(){
        return points.begin().base();
    }
    size_t pointsSize(){
        return points.size()*sizeof(float );
    }
    void init(unsigned int *VAO,unsigned int *VBO);

    void MoveCamera(const glm::vec3 &loc){
        cam.location+=loc;
        cam.initializeCameraValue();
    }

    void SetCamera(float w,float h,float n=INFINITY,float f=INFINITY){
        cam.setWH(w,h,n,f);
    }

};

class Object {
protected:
    glm::vec3 location;
    glm::mat4x4 modelViewMatrix;
public:
    explicit Object(float x = 0,float y = 0,float z = 0);
    void rotate(float angle,const glm::vec3&);
    void move(const glm::vec3&);
    virtual void init(World&the_world);
};

class Sphere: public Object{
    float r;

    void addPoint(const glm::vec3&loca,World&the_world);
    void addPoint(float x,float y,float z,World&the_world);
    void addColor(const glm::vec3&loca,World&the_world);

    glm::vec3 color;

public:
    explicit Sphere(float x=0,float y=0,float z=0,float r=1);
    void setColors(const glm::vec3&col);
    void init(World&the_world);

};

#endif //CG_OBJECT_H
