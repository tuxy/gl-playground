#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Shader {
public:
  unsigned int ID;
  Shader(const char *vertexPath, const char *fragmentPath) {
    string vertextShaderContent;
    string fragmentShaderContent;
    ifstream vShaderFile;
    ifstream fShaderFile;
    try {
      vShaderFile.open(vertexPath);
      fShaderFile.open(fragmentPath);

      stringstream vBuf, fBuf;
      vBuf << vShaderFile.rdbuf();
      fBuf << fShaderFile.rdbuf();

      vShaderFile.close();
      fShaderFile.close();

      vertextShaderContent = vBuf.str();
      fragmentShaderContent = fBuf.str();
    } catch (ifstream::failure e) {
      cerr << "Cannot read shader file" << endl;
    }

    const char *vertexShaderSource = vertextShaderContent.c_str();
    const char *fragmentShaderSource = fragmentShaderContent.c_str();

    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      char infoLog[512];
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      char infoLog[512];
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
           << infoLog << endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
      char infoLog[512];
      glGetProgramInfoLog(ID, 512, NULL, infoLog);
      cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
  }
  void use() { glUseProgram(ID); }
  void setBool(const string &name, bool value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
  }
  void setInt(const string &name, int value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }
  void setFloat(const string &name, float value) {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }
};

#endif
