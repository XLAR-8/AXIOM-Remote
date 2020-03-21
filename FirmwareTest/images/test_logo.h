#include <stdint.h>

static const struct
{
    uint16_t width;
    uint16_t height;
    uint8_t pixel_data[5 * 5 + 1];
}
test_logo = {
 5, 5, 
 {
   0x00, 0x00, 0x03, 0x06, 0x04,
  }
  };
