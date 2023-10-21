// #include <stdio.h>
// #include <stdlib.h>

// #define LAST_BYTE_MASK 0xff

// int app_main(void){

//     int x = 1234;

//     uint8_t tx_data[16];

//     for(int i = 0; i < 16; i++){
//         tx_data[i] = (x >> 8*(3-i)) & LAST_BYTE_MASK;
//     }

//     for(int i = 0; i < 16; i++){
//         printf("%02d ", tx_data[i]);
//     }

//     return 0;
// }