//
// Created by kouushou on 2020/11/19.
//

#ifndef CG_SHADER_H
#define CG_SHADER_H
#include <bits/stdc++.h>
typedef unsigned int __Index;

class Shader {
public:
    __Index ID;

    explicit Shader(const char *vertexPath, const char *fragmentPath);

    void use()const;

    // uniform工具函数
    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

private:
    void checkCompileErrors(__Index shader, const std::string& type)const;

};


#endif //CG_SHADER_H
