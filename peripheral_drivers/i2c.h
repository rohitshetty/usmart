void TWIInit(void){
// from peter flury
unsigned char i2c_start(unsigned char);
unsigned char i2c_write( unsigned char);
unsigned char i2c_readAck(void);
unsigned char i2c_readNak(void);
void i2c_stop(void);
void i2c_init(void);
