#include <SPI.h>
#define GROUP_NUM (4)
#define CHANNEL_NUM (4)
#define GROUP1   (0x00000001)
#define GROUP2   (0x00000010)
#define GROUP3   (0x00010000)
#define GROUP4   (0x00100000)



class Led_pattern {
  public:
    unsigned long interval;
    unsigned long repeat;

    void stairs(unsigned long space , unsigned long repeat_num);
    void flow(unsigned long space , unsigned long repeat_num);
    void circle(unsigned long space , unsigned long repeat_num , unsigned long pattern_speed);
};

void Led_pattern::stairs(unsigned long space , unsigned long repeat_num) {
  int i, j,k;
  uint32_t input[GROUP_NUM] = {GROUP1, GROUP2, GROUP3, GROUP4};
  uint32_t senddata;

 for(k=0;k<repeat_num;k++){
    for (i = 0; i < GROUP_NUM; i++) {
      senddata = input[i];
      for (j = 0; j < CHANNEL_NUM; j++) {
        delay(space);
        SPI.transfer32(senddata);
        senddata = senddata << 1;
      }
    }
 }

}

void Led_pattern::flow(unsigned long space , unsigned long repeat_num){
    int i, j ,k;
  uint32_t input[4] = {GROUP1, GROUP2, GROUP3, GROUP4};
  uint32_t senddata;

  for(k=0;k<repeat_num;k++){
  
    senddata = input[0] + (input[0]<<1);
  
    for (j = 0; j < CHANNEL_NUM; j++) {
      delay(space);
      SPI.transfer32(senddata);
      senddata = senddata << 2;
    }
  
  
      senddata = input[2] + (input[2]<<1);
  
    for (j = 0; j < CHANNEL_NUM; j++) {
      delay(space);
      SPI.transfer32(senddata);
      senddata = senddata << 2;
    }
  
      senddata = (input[3] + (input[3]<<1))<<2;
  
    for (j = 0; j < CHANNEL_NUM; j++) {
      delay(space);
      SPI.transfer32(senddata);
      senddata = senddata >> 2;
    }
  
        senddata = (input[1] + (input[1]<<1))<<2;
  
    for (j = 0; j < CHANNEL_NUM; j++) {
      delay(space);
      SPI.transfer32(senddata);
      senddata = senddata >> 2;
    }
  }
  
  
}

void Led_pattern::circle(unsigned long space , unsigned long repeat_num , unsigned long pattern_speed) {
  int i, j ,k;
  uint32_t input[GROUP_NUM] = {GROUP1, GROUP2, GROUP3, GROUP4};
  uint32_t senddata;
  #define SPPED_LIMIT_LOW (1)

  for(k=0;k<repeat_num;k++){

      senddata = input[0];
    
      for (j = 0; j < CHANNEL_NUM; j++) {
        delay(space);
        SPI.transfer32(senddata);
        senddata = senddata << 2;
      }
    
      senddata = input[2];
    
      for (j = 0; j < CHANNEL_NUM; j++) {
        delay(space);
        SPI.transfer32(senddata);
        senddata = senddata << 2;
      }
    
      senddata = GROUP4 << 3;
    
      for (j = 0; j < CHANNEL_NUM; j++) {
        delay(space);
        SPI.transfer32(senddata);
        senddata = senddata >> 2;
      }
    
      senddata = GROUP2 << 3;
    
      for (j = 0; j < CHANNEL_NUM; j++) {
        delay(space);
        SPI.transfer32(senddata);
        senddata = senddata >> 2;
      }

      space  = space + pattern_speed;

      if(SPPED_LIMIT_LOW >= space){
          space = SPPED_LIMIT_LOW;
      }

  }


}

Led_pattern pattern;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setHwCs(true);
  Serial.begin(115200);


}

void loop() {
  int i;
  // put your main code here, to run repeatedly:
  
  pattern.interval = 50;
  pattern.repeat = 1;
  
  pattern.stairs(pattern.interval,pattern.repeat);

  pattern.repeat = 2;

  pattern.flow(pattern.interval,pattern.repeat);

  pattern.repeat = 4;
  
  pattern.circle(pattern.interval,pattern.repeat ,-10);
 

  
}
