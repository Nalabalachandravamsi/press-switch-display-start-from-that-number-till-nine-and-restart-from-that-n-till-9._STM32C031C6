void delay1(int);
void port_intialization();
void setup() {
  // put your setup code here, to run once:
  volatile int blink[] = {0x0000003f,0x00000006,0x0000005b,0x0000004f,0x00000066,0x0000006d,0x0000007d,0x00000007,0x0000007f,0x00000067};  port_intialization();
  volatile int debounce;
  volatile int *inpA,*inpD,*setA,count1,count2,temp;
  inpA = (volatile  int *)0x50000010;
  inpD = (volatile  int *)0x50000c10;
  setA = (volatile  int *)0x50000018; 
  *setA = 0xffff0000;  
  *inpA=0x00000000;
  *inpD=0x00000000; 
  while(1){  
    for(count1=8;count1<16;count1++){
      if(count1==13) continue;
      if((*inpA & 1<<count1)) {
        for(debounce=0;debounce<10000;debounce++);  
        temp = count1-8;
        while(1){
          *setA = blink[temp];
          delay1(3);
          *setA = 0x00ff0000;
          temp++;
          if(temp>9){
            temp=count1-8;
          }
        }      
                  
      }
    }
    if(*inpD & 0x00000001){
      count2 = 5;
      while(1){
        *setA = blink[count2];
        delay1(3);
        *setA = 0x00ff0000;
        count2++;
        if(count2>9){
          count2=5;
        }
      }
      

    }
  }
}
void loop() {
  // put your main code here, to run repeatedly:
}
void delay1(int num){
  volatile int i;
  while(num){
    for(i=0;i<100000;i++);
    num--;
  }
}
void port_intialization(){
  volatile  int *configA,*configD;
  configA = (volatile  int *)0x50000000;  // Cast to volatile int pointer
  configD = (volatile  int *)0x50000fff;  // Cast to volatile int pointer
  *configA = 0x00005555; 
  *configD = 0x00000001;
}
