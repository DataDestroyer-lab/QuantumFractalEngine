#include "../include/glad/glad.h"
#include <stddef.h>

/* Minimal glad.c: resolve GL function pointers using provided loader (glfwGetProcAddress) */

/* Define the function pointers (prefixed with glad_ to avoid collisions) */
PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays = NULL;
PFNGLGENBUFFERSPROC glad_glGenBuffers = NULL;
PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray = NULL;
PFNGLBINDBUFFERPROC glad_glBindBuffer = NULL;
PFNGLBUFFERDATAPROC glad_glBufferData = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray = NULL;
PFNGLACTIVETEXTUREPROC glad_glActiveTexture = NULL;
PFNGLBINDTEXTUREPROC glad_glBindTexture = NULL;
PFNGLTEXPARAMETERIPROC glad_glTexParameteri = NULL;
PFNGLTEXIMAGE2DPROC glad_glTexImage2D = NULL;
PFNGLTEXSUBIMAGE2DPROC glad_glTexSubImage2D = NULL;
PFNGLGENTEXTURESPROC glad_glGenTextures = NULL;
PFNGLDELETETEXTURESPROC glad_glDeleteTextures = NULL;
PFNGLCREATESHADERPROC glad_glCreateShader = NULL;
PFNGLSHADERSOURCEPROC glad_glShaderSource = NULL;
PFNGLCOMPILESHADERPROC glad_glCompileShader = NULL;
PFNGLCREATEPROGRAMPROC glad_glCreateProgram = NULL;
PFNGLATTACHSHADERPROC glad_glAttachShader = NULL;
PFNGLLINKPROGRAMPROC glad_glLinkProgram = NULL;
PFNGLDELETESHADERPROC glad_glDeleteShader = NULL;
PFNGLDELETEPROGRAMPROC glad_glDeleteProgram = NULL;
PFNGLUSEPROGRAMPROC glad_glUseProgram = NULL;
PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation = NULL;
PFNGLUNIFORM1FPROC glad_glUniform1f = NULL;
PFNGLUNIFORM1IPROC glad_glUniform1i = NULL;
PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv = NULL;
PFNGLUNIFORM3FVPROC glad_glUniform3fv = NULL;
PFNGLUNIFORM4FVPROC glad_glUniform4fv = NULL;
PFNGLGETSHADERIVPROC glad_glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog = NULL;
PFNGLGETPROGRAMIVPROC glad_glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog = NULL;
PFNGLBINDIMAGETEXTUREPROC glad_glBindImageTexture = NULL;
PFNGLDISPATCHCOMPUTEPROC glad_glDispatchCompute = NULL;
PFNGLMEMORYBARRIERPROC glad_glMemoryBarrier = NULL;
PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers = NULL;
PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays = NULL;

/* Core 1.1 functions */
PFNGLENABLEPROC glad_glEnable = NULL;
PFNGLCLEARCOLORPROC glad_glClearColor = NULL;
PFNGLCLEARPROC glad_glClear = NULL;
PFNGLDRAWELEMENTSPROC glad_glDrawElements = NULL;

static void* get_proc(GLADloadproc loader, const char* name) {
    if(!loader) return NULL;
    return loader(name);
}

int gladLoadGLLoader(GLADloadproc loader) {
    /* Load symbols using the provided loader */
    glad_glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)get_proc(loader, "glGenVertexArrays");
    glad_glGenBuffers = (PFNGLGENBUFFERSPROC)get_proc(loader, "glGenBuffers");
    glad_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)get_proc(loader, "glBindVertexArray");
    glad_glBindBuffer = (PFNGLBINDBUFFERPROC)get_proc(loader, "glBindBuffer");
    glad_glBufferData = (PFNGLBUFFERDATAPROC)get_proc(loader, "glBufferData");
    glad_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)get_proc(loader, "glVertexAttribPointer");
    glad_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)get_proc(loader, "glEnableVertexAttribArray");
    glad_glActiveTexture = (PFNGLACTIVETEXTUREPROC)get_proc(loader, "glActiveTexture");
    glad_glBindTexture = (PFNGLBINDTEXTUREPROC)get_proc(loader, "glBindTexture");
    glad_glTexParameteri = (PFNGLTEXPARAMETERIPROC)get_proc(loader, "glTexParameteri");
    glad_glTexImage2D = (PFNGLTEXIMAGE2DPROC)get_proc(loader, "glTexImage2D");
    glad_glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)get_proc(loader, "glTexSubImage2D");
    glad_glGenTextures = (PFNGLGENTEXTURESPROC)get_proc(loader, "glGenTextures");
    glad_glDeleteTextures = (PFNGLDELETETEXTURESPROC)get_proc(loader, "glDeleteTextures");
    glad_glCreateShader = (PFNGLCREATESHADERPROC)get_proc(loader, "glCreateShader");
    glad_glShaderSource = (PFNGLSHADERSOURCEPROC)get_proc(loader, "glShaderSource");
    glad_glCompileShader = (PFNGLCOMPILESHADERPROC)get_proc(loader, "glCompileShader");
    glad_glGetShaderiv = (PFNGLGETSHADERIVPROC)get_proc(loader, "glGetShaderiv");
    glad_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)get_proc(loader, "glGetShaderInfoLog");
    glad_glCreateProgram = (PFNGLCREATEPROGRAMPROC)get_proc(loader, "glCreateProgram");
    glad_glAttachShader = (PFNGLATTACHSHADERPROC)get_proc(loader, "glAttachShader");
    glad_glLinkProgram = (PFNGLLINKPROGRAMPROC)get_proc(loader, "glLinkProgram");
    glad_glGetProgramiv = (PFNGLGETPROGRAMIVPROC)get_proc(loader, "glGetProgramiv");
    glad_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)get_proc(loader, "glGetProgramInfoLog");
    glad_glDeleteShader = (PFNGLDELETESHADERPROC)get_proc(loader, "glDeleteShader");
    glad_glDeleteProgram = (PFNGLDELETEPROGRAMPROC)get_proc(loader, "glDeleteProgram");
    glad_glUseProgram = (PFNGLUSEPROGRAMPROC)get_proc(loader, "glUseProgram");
    glad_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)get_proc(loader, "glGetUniformLocation");
    glad_glUniform1f = (PFNGLUNIFORM1FPROC)get_proc(loader, "glUniform1f");
    glad_glUniform1i = (PFNGLUNIFORM1IPROC)get_proc(loader, "glUniform1i");
    glad_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)get_proc(loader, "glUniformMatrix4fv");
    glad_glUniform3fv = (PFNGLUNIFORM3FVPROC)get_proc(loader, "glUniform3fv");
    glad_glUniform4fv = (PFNGLUNIFORM4FVPROC)get_proc(loader, "glUniform4fv");
    glad_glBindImageTexture = (PFNGLBINDIMAGETEXTUREPROC)get_proc(loader, "glBindImageTexture");
    glad_glDispatchCompute = (PFNGLDISPATCHCOMPUTEPROC)get_proc(loader, "glDispatchCompute");
    glad_glMemoryBarrier = (PFNGLMEMORYBARRIERPROC)get_proc(loader, "glMemoryBarrier");
    glad_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)get_proc(loader, "glDeleteBuffers");
    glad_glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)get_proc(loader, "glDeleteVertexArrays");

    /* Core 1.1 functions */
    glad_glEnable = (PFNGLENABLEPROC)get_proc(loader, "glEnable");
    glad_glClearColor = (PFNGLCLEARCOLORPROC)get_proc(loader, "glClearColor");
    glad_glClear = (PFNGLCLEARPROC)get_proc(loader, "glClear");
    glad_glDrawElements = (PFNGLDRAWELEMENTSPROC)get_proc(loader, "glDrawElements");

    /* Heuristic: return success if core functions loaded */
    return (glad_glGenBuffers && glad_glCreateShader && glad_glCompileShader) ? 1 : 0;
}
