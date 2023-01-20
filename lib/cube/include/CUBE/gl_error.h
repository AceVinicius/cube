//
// Created by Vinícius Ferreira Aguiar on 18/12/22.
//

#ifndef CUBE_GL_ERROR_H
# define CUBE_GL_ERROR_H

# include <signal.h>
# include <stdbool.h>

# ifndef NDEBUG
#  define ASSERT(x) if (!(x)) raise(SIGTRAP)
#  define GL_CALL(x) gl_clear_error(); x; ASSERT(gl_log_call(#x, __FILE__, __LINE__))
# else
#  define GL_CALL(x) x
# endif



void gl_clear_error();
bool gl_log_call(const char *function, const char *file, int line);



#endif //CUBE_GL_ERROR_H
