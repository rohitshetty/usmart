#include<avr/io.h>

void RTCinit(){
    TWIInit();
    return;
}


void RTCSet(char * current_date_time){
    i2c_start(0xD0);
    i2c_write(0x00);
    i2c_write(((current_date_time[4]-48)<<4)|(current_date_time[5]-48));     //seconds
    i2c_write(((current_date_time[2]-48)<<4)|(current_date_time[3]-48));     //minutes
    i2c_write(((current_date_time[0]-48)<<4)|(current_date_time[1]-48));     //hours
    i2c_write((current_date_time[6]-48));                                    // days
    i2c_write(((current_date_time[7]-48)<<4)|(current_date_time[8]-48));    // Date
    i2c_write(((current_date_time[9]-48)<<4)|(current_date_time[10]-48));   // month
    i2c_write(((current_date_time[11]-48)<<4)|(current_date_time[12]-48));  //year
    i2c_stop();
    return;
}

void RTCRead(char * datetime){
    //datetime will be written with the hh:mm:ss:D:dd:mm:yy format with a null terminator.
    uint8_t temp;
    i2c_start(0xD0);
    i2c_write(0x00);
    i2c_start(0xD1);
    //This is for the Seconds
    temp = i2c_readAck();
    datetime[6] = (temp>>4)+48;
    datetime[7] = (temp&(0b00001111))+48;
    datetime[8] = ':';

    //minutes
    temp = i2c_readAck();
    datetime[3] = (temp>>4)+48;
    datetime[4] = (temp&(0b00001111))+48;
    datetime[5] = ':';

    //hours
    temp = i2c_readAck();
    datetime[0] = ((temp>>4)&(1))+48;
    datetime[1] = (temp&(0b00001111))+48;
    datetime[2] = ':';
    //DoW
    temp = i2c_readAck();
    datetime[9] = (temp&(0b00001111))+48;
    datetime[10] = ':';

    // Date
    temp = i2c_readAck();
    datetime[11] = (temp>>4)+48;
    datetime[12] = (temp&(0b00001111))+48;
    datetime[13] = ':';

    // month
    temp = i2c_readAck();
    datetime[14] = (temp>>4)+48;
    datetime[15] = (temp&(0b00001111))+48;
    datetime[16] = ':';

    // year
    temp = i2c_readNak();
    datetime[17] = (temp>>4)+48;
    datetime[18] = (temp&(0b00001111))+48;
    datetime[19] = ' ';
    datetime[20] = '\0';
    i2c_stop();
    return;
}
