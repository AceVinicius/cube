//
// Created by Vinícius Ferreira Aguiar on 18/12/22.
//
#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>

#include "CUBE/gl_error.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>



void
gl_clear_error()
{
    while (glGetError() != GL_NO_ERROR);
}



bool
gl_log_call(const char *function, const char *file, int line)
{
    GLenum error = glGetError();

    if (error == GL_NO_ERROR) {
        return true;
    }

    while (error != GL_NO_ERROR)
    {
        fprintf(stderr, "[OpenGL error] (%x): %s:%d\n\t%s\n", error, strrchr(file, '/') + 1, line, function);
        error = glGetError();
    }

    return false;
}
