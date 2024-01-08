#pragma once
#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{

private:
    std::string m_Filepath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;

public:
    Shader(const std::string &filepath);
    ~Shader();

    void Bind() const;
    void UnBind() const;

    void SetUniform4f(const std::string &name, float v0, float v1, float f2, float f3);

private:
    unsigned int CompileShader(unsigned int type, const std::string &source);
    unsigned int CreateShader(const std::string &vertexSharder, const std::string &fragmentShader);
    ShaderProgramSource ParseShader(const std::string filepath);
    unsigned int GetUniformLocation(const std::string &name);
};