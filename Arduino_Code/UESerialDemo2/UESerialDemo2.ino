int servopin = 9; //定义数字接口9 连接伺服舵机信号线
int pulsewidth;//定义脉宽变量
String inputBuffer;

void setup() {
  pinMode(servopin,OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    inputBuffer = Serial.readString();
    ProcessSignalData(inputBuffer);
  }
}

void ProcessSignalData(String signalData)
{
  //if(signalData != 
  int speratorIndex = signalData.indexOf('_');
  
  // get the Signal
  int signal = signalData.substring(0,speratorIndex).toInt();
  
  // get the data
  int data = signalData.substring(speratorIndex + 1).toInt();
  
  for(int i=0; i<=50; i++)
  {
    servopulse(servopin, data);
  }
  
}

void servopulse(int servopin, int myangle) //定义一个脉冲函数
{
  pulsewidth = (myangle * 11) + 500; //将角度转化为500-2480 的脉宽值
  digitalWrite(servopin, HIGH); //将舵机接口电平至高
  delayMicroseconds(pulsewidth);//延时脉宽值的微秒数
  digitalWrite(servopin, LOW); //将舵机接口电平至低
  delay(20 - pulsewidth / 1000);
}
