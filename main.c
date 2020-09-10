#include<ubertooth.h>
#include<ubertooth_control.h>
#include <unistd.h>

int main(int argc, char** argv){
  int ubertooth_device = -1;
  ubertooth_t* ut = ubertooth_init();
  uint8_t mac_address[6] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
  uint8_t adv_data[] = {/* Service class */ 0x03, 0x03, 0x6f, 0xfd,
                        /* Actual data: length 23 */ 0x17,
                        /* Actual data: uuid */ 0x16, 0x6f, 0xfd,
                        /* RSI (16 bytes) */ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
                        /* metadata (4 bytes) */0xaa,0xbb,0xcc,0xdd
  };


  int r = ubertooth_connect(ut, ubertooth_device);
  if(r<0){
    printf("Can not connect");
    return 0;
  }

  r = ubertooth_check_api(ut);
  if(r<0){
    printf("Can not connect");
    return 0;
  }

  cmd_set_channel(ut->devh, 2426);
  cmd_le_set_adv_data(ut->devh, adv_data, sizeof(adv_data));
  cmd_set_palevel(ut->devh,7); // Transmit level, 7 is the highest
  cmd_set_access_address(ut->devh, 37); // there are 3 channels, but 37 is fine
  cmd_btle_slave(ut->devh, mac_address);

  return 0;
}
