#include "gfx/shader.hpp"

mg::Shader::Shader() {
    this->id = -1;
    this->type = SHADER_TYPE::SHADER_TYPE_NONE;
}
mg::Shader::~Shader() {
}

void mg::Shader::createID(SHADER_TYPE t) {
    if(glIsShader(this->id) == GL_FALSE) {
        this->type = t;
        this->id = glCreateShader(shaderTypeToGLEnum(this->type));
    }
}
void mg::Shader::deleteID() {
    if(glIsShader(this->id) == GL_TRUE) {
        glDeleteShader(this->id);
    }
}
bool mg::Shader::hasValidID() {
    if(glIsShader(this->id) == GL_TRUE) {
        return true;
    } else {
        return false;
    }
}

bool mg::Shader::loadFromFile(const std::string& p) {
    std::ifstream infile(p, std::ios::in);
    std::string line;

    if(infile.is_open()) {
        this->src = "";
        this->path = p;
        while(std::getline(infile, line)) {
            this->src += line += "\n";
        }

        infile.close();
    } else {
        std::string errMsg("failed to open shader file ");
        errMsg += this->path;
        errMsg += " for reading, insufficient permissions or non-existing file\n ";
        throw std::runtime_error(errMsg);
        return false;
    }

    return true;
}
bool mg::Shader::loadFromMemory(const std::string& src) {
    this->src = src;

    return true;
}

bool mg::Shader::compile() {
    if(!this->hasValidID()) {
        std::string errMsg("failed to compile invalid GL shader ");
        errMsg += this->path;
        errMsg += ", of type ";
        errMsg += shaderTypeToString(this->type);
        errMsg += "\n";
        throw std::runtime_error(errMsg);

        return false;
    }

    GLint result = GL_FALSE;
    const char* textPtr = this->src.c_str();

    glShaderSource(this->id, 1, &textPtr, NULL);
    glCompileShader(this->id);

    glGetShaderiv(this->id, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE) {
        int errorLogLength = 0;
        glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &errorLogLength);        

        char errorLog[errorLogLength];
        glGetShaderInfoLog(this->id, errorLogLength, NULL, &errorLog[0]);

        std::string errMsg;
		if(this->path.empty()) {
			errMsg += "shader of type ";
		} else {
			errMsg += "shader ";
        	errMsg += this->path;
        	errMsg += ", of type ";
		}
        errMsg += shaderTypeToString(this->type);
        errMsg +=  " failed to compile. Log:\n";
        errMsg += errorLog;
        errMsg += "\n";
        throw std::runtime_error(errMsg);
    }

    return true;
}
