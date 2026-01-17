#include "../include/texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

namespace Precision{

void Texture::init(const char *file_path, unsigned int tex_unit){
  img_data img = read_from_file(file_path);

  glGenTextures(1, &m_ID);
  glActiveTexture(GL_TEXTURE0 + tex_unit);
  glBindTexture(GL_TEXTURE_2D, m_ID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.width, img.height, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(img.data);
  std::cout << "TEXTURE::LOADED::" << m_ID << std::endl;
}

img_data Texture::read_from_file(const char *file_path){ 
  int width {0}, 
      height {0}, 
      channels {0};
  unsigned char* data = stbi_load(file_path, &width, &height, &channels, 0);
  if(!data){
    std::cout << "TEXTURE::LOAD_IMG::ERROR" << std::endl;
  }
  img_data img = {width, height, channels, data};
  return img;
}

} // namespace Precision
