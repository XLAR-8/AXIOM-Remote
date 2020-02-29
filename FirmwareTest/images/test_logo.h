#include <stdint.h>

static const struct
{
    uint16_t width;
    uint16_t height;
    uint8_t pixel_data[];
}
test_logo = {
 8, 8, 
 {
   0xFF, 
   0xFF, 
   0xFF, 
   0xFF,
   0xFF, 
   0xFF, 
   0xFF, 
   0xFF,
  }
  }
