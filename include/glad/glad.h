/* Minimal vendor glad header (GL 4.6 core) - generated subset */
#ifndef GLAD_GL_H_
#define GLAD_GL_H_

#include <KHR/khrplatform.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Define calling convention macros if missing */
#ifndef APIENTRY
# ifdef _WIN32
#  define APIENTRY __stdcall
# else
#  define APIENTRY
# endif
#endif

#ifndef WINGDIAPI
# define WINGDIAPI
#endif

typedef khronos_uintptr_t glad_PFNptr;

/* Basic GL types */
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef double GLdouble;
typedef char GLchar;
typedef long GLintptr;
typedef long GLsizeiptr;

/* Tokens needed by this project */
#define GL_FALSE 0
#define GL_TRUE 1
#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_STATIC_DRAW 0x88E4
#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE1 0x84C1
#define GL_RGBA 0x1908
#define GL_FLOAT 0x1406
#define GL_RGBA32F 0x8814
#define GL_READ_WRITE 0x88BA
#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT 0x00000020
#define GL_COMPUTE_SHADER 0x91B9
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_REPEAT 0x2901
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_LINEAR 0x2601
#define GL_PIXEL_UNPACK_BUFFER 0x88EC
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_UNSIGNED_INT 0x1405
#define GL_TRIANGLES 0x0004
/* Additional tokens used by project */
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_RG 0x8227
#define GL_RG32F 0x8230
#define GL_DEPTH_TEST 0x0B71
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82

/* Function pointer typedefs */
typedef void (APIENTRY *PFNGLGENVERTEXARRAYSPROC)(GLsizei, GLuint*);
typedef void (APIENTRY *PFNGLGENBUFFERSPROC)(GLsizei, GLuint*);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC)(GLuint);
typedef void (APIENTRY *PFNGLBINDBUFFERPROC)(GLenum, GLuint);
typedef void (APIENTRY *PFNGLBUFFERDATAPROC)(GLenum, GLsizeiptr, const void*, GLenum);
typedef void (APIENTRY *PFNGLVERTEXATTRIBPOINTERPROC)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
typedef void (APIENTRY *PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint);
typedef void (APIENTRY *PFNGLACTIVETEXTUREPROC)(GLenum);
typedef void (APIENTRY *PFNGLBINDTEXTUREPROC)(GLenum, GLuint);
typedef void (APIENTRY *PFNGLTEXPARAMETERIPROC)(GLenum, GLenum, GLint);
typedef void (APIENTRY *PFNGLTEXIMAGE2DPROC)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*);
typedef void (APIENTRY *PFNGLTEXSUBIMAGE2DPROC)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void*);
typedef void (APIENTRY *PFNGLGENTEXTURESPROC)(GLsizei, GLuint*);
typedef void (APIENTRY *PFNGLDELETETEXTURESPROC)(GLsizei, const GLuint*);
typedef GLuint (APIENTRY *PFNGLCREATESHADERPROC)(GLenum);
typedef void (APIENTRY *PFNGLSHADERSOURCEPROC)(GLuint, GLsizei, const GLchar* const*, const GLint*);
typedef void (APIENTRY *PFNGLCOMPILESHADERPROC)(GLuint);
typedef GLuint (APIENTRY *PFNGLCREATEPROGRAMPROC)(void);
typedef void (APIENTRY *PFNGLATTACHSHADERPROC)(GLuint, GLuint);
typedef void (APIENTRY *PFNGLLINKPROGRAMPROC)(GLuint);
typedef void (APIENTRY *PFNGLDELETESHADERPROC)(GLuint);
typedef void (APIENTRY *PFNGLDELETEPROGRAMPROC)(GLuint);
typedef void (APIENTRY *PFNGLUSEPROGRAMPROC)(GLuint);
typedef GLint (APIENTRY *PFNGLGETUNIFORMLOCATIONPROC)(GLuint, const GLchar*);
typedef void (APIENTRY *PFNGLUNIFORM1FPROC)(GLint, GLfloat);
typedef void (APIENTRY *PFNGLUNIFORM1IPROC)(GLint, GLint);
typedef void (APIENTRY *PFNGLUNIFORMMATRIX4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat*);
typedef void (APIENTRY *PFNGLUNIFORM3FVPROC)(GLint, GLsizei, const GLfloat*);
typedef void (APIENTRY *PFNGLUNIFORM4FVPROC)(GLint, GLsizei, const GLfloat*);
typedef void (APIENTRY *PFNGLBINDIMAGETEXTUREPROC)(GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLint);
typedef void (APIENTRY *PFNGLDISPATCHCOMPUTEPROC)(GLuint, GLuint, GLuint);
typedef void (APIENTRY *PFNGLMEMORYBARRIERPROC)(GLbitfield);
typedef void (APIENTRY *PFNGLDELETEBUFFERSPROC)(GLsizei, const GLuint*);
typedef void (APIENTRY *PFNGLDELETEVERTEXARRAYSPROC)(GLsizei, const GLuint*);
typedef void (APIENTRY *PFNGLSHADERBINARYPROC)(GLsizei, const GLuint*, GLenum, const void*, GLsizei);
typedef void (APIENTRY *PFNGLGETSHADERIVPROC)(GLuint, GLenum, GLint*);
typedef void (APIENTRY *PFNGLGETSHADERINFOLOGPROC)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (APIENTRY *PFNGLGETPROGRAMIVPROC)(GLuint, GLenum, GLint*);
typedef void (APIENTRY *PFNGLGETPROGRAMINFOLOGPROC)(GLuint, GLsizei, GLsizei*, GLchar*);

/* Core 1.1 function typedefs used directly */
typedef void (APIENTRY *PFNGLENABLEPROC)(GLenum);
typedef void (APIENTRY *PFNGLCLEARCOLORPROC)(GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRY *PFNGLCLEARPROC)(GLbitfield);
typedef void (APIENTRY *PFNGLDRAWELEMENTSPROC)(GLenum, GLsizei, GLenum, const void*);

/* Declarations of pointers */
extern PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays;
extern PFNGLGENBUFFERSPROC glad_glGenBuffers;
extern PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray;
extern PFNGLBINDBUFFERPROC glad_glBindBuffer;
extern PFNGLBUFFERDATAPROC glad_glBufferData;
extern PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray;
extern PFNGLACTIVETEXTUREPROC glad_glActiveTexture;
extern PFNGLBINDTEXTUREPROC glad_glBindTexture;
extern PFNGLTEXPARAMETERIPROC glad_glTexParameteri;
extern PFNGLTEXIMAGE2DPROC glad_glTexImage2D;
extern PFNGLTEXSUBIMAGE2DPROC glad_glTexSubImage2D;
extern PFNGLGENTEXTURESPROC glad_glGenTextures;
extern PFNGLDELETETEXTURESPROC glad_glDeleteTextures;
extern PFNGLCREATESHADERPROC glad_glCreateShader;
extern PFNGLSHADERSOURCEPROC glad_glShaderSource;
extern PFNGLCOMPILESHADERPROC glad_glCompileShader;
extern PFNGLCREATEPROGRAMPROC glad_glCreateProgram;
extern PFNGLATTACHSHADERPROC glad_glAttachShader;
extern PFNGLLINKPROGRAMPROC glad_glLinkProgram;
extern PFNGLDELETESHADERPROC glad_glDeleteShader;
extern PFNGLDELETEPROGRAMPROC glad_glDeleteProgram;
extern PFNGLUSEPROGRAMPROC glad_glUseProgram;
extern PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation;
extern PFNGLUNIFORM1FPROC glad_glUniform1f;
extern PFNGLUNIFORM1IPROC glad_glUniform1i;
extern PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv;
extern PFNGLUNIFORM3FVPROC glad_glUniform3fv;
extern PFNGLUNIFORM4FVPROC glad_glUniform4fv;
extern PFNGLGETSHADERIVPROC glad_glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog;
extern PFNGLGETPROGRAMIVPROC glad_glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog;
extern PFNGLBINDIMAGETEXTUREPROC glad_glBindImageTexture;
extern PFNGLDISPATCHCOMPUTEPROC glad_glDispatchCompute;
extern PFNGLMEMORYBARRIERPROC glad_glMemoryBarrier;
extern PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers;
extern PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays;
extern PFNGLENABLEPROC glad_glEnable;
extern PFNGLCLEARCOLORPROC glad_glClearColor;
extern PFNGLCLEARPROC glad_glClear;
extern PFNGLDRAWELEMENTSPROC glad_glDrawElements;

/* Loader function */
typedef void* (*GLADloadproc)(const char *name);
int gladLoadGLLoader(GLADloadproc loader);

/* Map public GL names to glad function pointers */
#define glGenVertexArrays glad_glGenVertexArrays
#define glGenBuffers glad_glGenBuffers
#define glBindVertexArray glad_glBindVertexArray
#define glBindBuffer glad_glBindBuffer
#define glBufferData glad_glBufferData
#define glVertexAttribPointer glad_glVertexAttribPointer
#define glEnableVertexAttribArray glad_glEnableVertexAttribArray
#define glActiveTexture glad_glActiveTexture
#define glBindTexture glad_glBindTexture
#define glTexParameteri glad_glTexParameteri
#define glTexImage2D glad_glTexImage2D
#define glTexSubImage2D glad_glTexSubImage2D
#define glGenTextures glad_glGenTextures
#define glDeleteTextures glad_glDeleteTextures
#define glCreateShader glad_glCreateShader
#define glShaderSource glad_glShaderSource
#define glCompileShader glad_glCompileShader
#define glGetShaderiv glad_glGetShaderiv
#define glGetShaderInfoLog glad_glGetShaderInfoLog
#define glCreateProgram glad_glCreateProgram
#define glAttachShader glad_glAttachShader
#define glLinkProgram glad_glLinkProgram
#define glGetProgramiv glad_glGetProgramiv
#define glGetProgramInfoLog glad_glGetProgramInfoLog
#define glDeleteShader glad_glDeleteShader
#define glDeleteProgram glad_glDeleteProgram
#define glUseProgram glad_glUseProgram
#define glGetUniformLocation glad_glGetUniformLocation
#define glUniform1f glad_glUniform1f
#define glUniform1i glad_glUniform1i
#define glUniformMatrix4fv glad_glUniformMatrix4fv
#define glUniform3fv glad_glUniform3fv
#define glUniform4fv glad_glUniform4fv
#define glBindImageTexture glad_glBindImageTexture
#define glDispatchCompute glad_glDispatchCompute
#define glMemoryBarrier glad_glMemoryBarrier
#define glDeleteBuffers glad_glDeleteBuffers
#define glDeleteVertexArrays glad_glDeleteVertexArrays
/* Core 1.1 functions mapped to glad pointers */
#define glEnable glad_glEnable
#define glClearColor glad_glClearColor
#define glClear glad_glClear
#define glDrawElements glad_glDrawElements

#ifdef __cplusplus
}
#endif

#endif /* GLAD_GL_H_ */
