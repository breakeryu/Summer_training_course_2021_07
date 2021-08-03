#include "usart.h"




void usart_init(void){

    Serial1.begin(115200);
    Serial1.write("1");


}









