#ifndef _TEXT_H
#define _TEXT_H

void TextRendering_LoadShader(const GLchar* const shader_string, GLuint shader_id);
void TextRendering_Init();
void TextRendering_PrintString(GLFWwindow* window, const std::string &str, float x, float y, float scale = 1.0f);
float TextRendering_LineHeight(GLFWwindow* window);
float TextRendering_CharWidth(GLFWwindow* window);

#endif
