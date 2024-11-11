#include <glad/glad.h>
#include<glfw/glfw3.h>
#include<utils/logger.hpp>


namespace Shader
{
    typedef struct {
        GLuint program;
    } shader;

struct ShaderReader{
    char* shadersource;
    const char* filename;

    enum class SHADER_TYPE
    {
        vertex,
        fragment,
        geometry,
        compute
    };

    char* readShaderFile(const char* filename);
    GLuint compileShader(const char* source, GLenum type);
   

};

 shader createShader(const char* vertexPath, const char* fragmentPath);
}