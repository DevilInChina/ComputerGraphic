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
};

class World{
public:
    std::vector<float> points;
    std::vector<int> breaks;
    std::vector<unsigned int> types;
    int cnts = 0;
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
