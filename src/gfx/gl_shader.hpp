#ifndef GL_SHADER_HPP
#define GL_SHADER_HPP

#define GLEW_STATIC
#include <GL/glew.h>

#include "gfx/shader.hpp"

namespace mg {
    class GLShader : public Shader {
		protected:
		    GLuint loadShader(const std::string&, GLenum);
			GLuint id, vs, fs;
        public:
            GLShader();
            ~GLShader();

			void createID();
			void deleteID();
			void bindID();
			bool hasValidID();

            bool loadFromFile(const std::string&, const std::string&);

			int getAttribLocation(const std::string&);

            bool link();
    };
}

#endif //GL_SHADER_HPP
