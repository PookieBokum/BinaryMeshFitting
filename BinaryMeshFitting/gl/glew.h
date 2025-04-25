#pragma once

#include <Windows.h>

// Basic OpenGL types
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;
typedef char GLchar;

// OpenGL constants
#define GL_FALSE 0
#define GL_TRUE 1
#define GL_TRIANGLES 0x0004
#define GL_FLOAT 0x1406
#define GL_UNSIGNED_INT 0x1405
#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_STATIC_DRAW 0x88E4
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_INFO_LOG_LENGTH 0x8B84

// Function declarations
extern "C" {
    // Buffer functions
    void glGenBuffers(GLsizei n, GLuint* buffers);
    void glBindBuffer(GLenum target, GLuint buffer);
    void glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
    void glDeleteBuffers(GLsizei n, const GLuint* buffers);
    
    // Shader functions
    GLuint glCreateShader(GLenum type);
    void glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
    void glCompileShader(GLuint shader);
    void glGetShaderiv(GLuint shader, GLenum pname, GLint* params);
    void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
    void glDeleteShader(GLuint shader);
    
    // Program functions
    GLuint glCreateProgram();
    void glAttachShader(GLuint program, GLuint shader);
    void glLinkProgram(GLuint program);
    void glGetProgramiv(GLuint program, GLenum pname, GLint* params);
    void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
    void glDeleteProgram(GLuint program);
    void glUseProgram(GLuint program);
    
    // Attribute functions
    GLint glGetAttribLocation(GLuint program, const GLchar* name);
    void glEnableVertexAttribArray(GLuint index);
    void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
    
    // Uniform functions
    GLint glGetUniformLocation(GLuint program, const GLchar* name);
    void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    void glUniform3fv(GLint location, GLsizei count, const GLfloat* value);
    void glUniform1f(GLint location, GLfloat v0);
    
    // Drawing functions
    void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
    void glDrawArrays(GLenum mode, GLint first, GLsizei count);
}

// GLEW initialization
GLenum glewInit(); 