//
// Created by kouushou on 2020/11/19.
//

#ifndef CG_OBJECT_H
#define CG_OBJECT_H

#include <bits/stdc++.h>
class vec3 {
private:
    std::tuple<float, float, float> info;
public:
    vec3(float x, float y, float z) {
        info = std::make_tuple(x, y, z);
    }

    float x() const {
        return std::get<0>(info);
    }

    float y() const {
        return std::get<1>(info);
    }

    float z() const {
        return std::get<2>(info);
    }

    vec3& operator+=(const vec3&other) {
        std::get<0>(info) += other.x();
        std::get<1>(info) += other.y();
        std::get<2>(info) += other.z();
        return *this;
    }
};

class Camera{
    float l,r,b,t,n,f;
    float mat4x4[16];
    float lookat[4];
    float w,h,_n,_f;
    void load4ofmtx(int row,float x,float y,float z,float w){
        mat4x4[row*4+0] = x;
        mat4x4[row*4+1] = y;
        mat4x4[row*4+2] = z;
        mat4x4[row*4+3] = w;
    }
    void initMatrix(){
        // -1 = (n-f)/(f-n)
        //
        load4ofmtx(0,2/(r-l),0,0,-(r+l)/(r-l));
        load4ofmtx(1,0,2/(t-b),0,-(t+b)/(t-b));
        load4ofmtx(2,0,0,-2/(f-n),-(f+n)/(f-n));
        load4ofmtx(3,0,0,0,1);
    }

public:
    vec3 location;
    explicit Camera(float x=0,float y=0,float z=0):location(x,y,z){}
    void initializeCameraValue(){
        l = location.x() - w / 2;
        r = location.x() + w / 2;
        t = location.y() + h / 2;
        b = location.y() - h / 2;
        f = location.z() - _f;
        n = location.z() - _n;
        initMatrix();
    }
    void setWH(float _w,float _h,float d_n,float d_f) {
        w = _w;
        h = _h;
        _f = d_f;
        _n = d_n;
        initializeCameraValue();
        lookat[0] = 0;
        lookat[1] = 0;
        lookat[2] = -1;
        lookat[3] = 1;
    }
    void updateMatrix(){

    }
    float *getMatrix(){
        return mat4x4;
    }
};
class World{
    Camera cam;
public:
    std::vector<float> points;
    std::vector<int> breaks;
    std::vector<unsigned int> types;
    explicit World():cam(0,0,0){}
    int cnts = 0;
    const float Pi=acos(-1.0);
    void load();
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

    void MoveCamera(const vec3 &loc){
        cam.location+=loc;
        cam.initializeCameraValue();
    }

    void SetCamera(float w,float h,float n,float f){
        cam.setWH(w,h,n,f);
    }

};

class Object {
protected:
    vec3 location;
public:
    explicit Object(float x = 0,float y = 0,float z = 0);
    virtual void init(World&the_world);
};

class Sphere: public Object{
    float r;
    void addPoint(const vec3&loca,World&the_world);
    void addPoint(float x,float y,float z,World&the_world);
    void addColor(const vec3&loca,World&the_world);

    vec3 color;

public:
    explicit Sphere(float x=0,float y=0,float z=0,float r=1);
    void setColors(const vec3&col);
    void init(World&the_world);

};

#endif //CG_OBJECT_H
