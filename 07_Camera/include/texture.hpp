#ifndef TEXTURE_H
#define TEXTURE_H

#include "common.hpp"

namespace Precision{

struct img_data {
  int width {0}, 
      height {0}, 
      channels {0};
  unsigned char *data;
};

class Texture{
public: 
  unsigned int m_ID;

public:
  Texture() {};
  void init(const char *file_path, const unsigned int tex_unit);

private:
  img_data read_from_file(const char *file_path);

};

} // namespace Precision

#endif
