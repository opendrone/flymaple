#include "wirish.h"
#include "Processing.h"

#define ACC_WEIGHT_MAX 5
/**************** PROCESSING ***********/

float RwAcc[3];         // 通过加速度传感器把重力加速度投影在x/y/z三轴上
float Gyro[3];
float RwGyro[3];        // 重新读取陀螺仪
float Awz[2];           // XZ/ YZ平面和Z轴（度）R的投影之间的角度
float RwEst[3];

boolean firstSample = true;
int lastTime = 0;
int interval = 0;
float wGyro = 10.0;


/* http://www.rcgroups.com/forums/showthread.php?t=1319827&page=5 */
float RwEstt[2];     	//Rw estimated from combining RwAcc and RwGyro
float RwAccc[2];        //projection of normalized gravitation force vector on x/y/z axis, as measured by accelerometer
float fx1, fx2, fx3, fy1, fy2, fy3;
int seq=0;

void processing(int16 * acc, int16 * gyro)
{
    // 把原始数据转换为G
    RwAcc[0] = float(acc[0]) / 256.0;
    RwAcc[1] = float(acc[1])/ 256.0;
    RwAcc[2] = float(acc[2])/ 256.0;

    // 把原始数据转换为"度/秒"
    Gyro[0] = float(gyro[3]) / 14.375;
    Gyro[1] = float(gyro[4]) / 14.375;
    Gyro[2] = float(gyro[5]) / 14.375;
  
    //getInclination();
    getEstimatedInclination(10);
    
    SerialUSB.print(RwEstt[0]);//x
    SerialUSB.print("	");
    SerialUSB.print(RwEstt[1]); //y
    SerialUSB.print("	");
    SerialUSB.println(RwEstt[2]);//z
    delay(50);
}


void getInclination() 
{
  int w = 0;
  float tmpf = 0.0;
  int currentTime, signRzGyro;


  currentTime = millis();
  interval = currentTime - lastTime;
  lastTime = currentTime;

  //if (firstSample || Float.isNaN(RwEst[0])) { // NaN用来等待检查从arduino过来的数据
  if (firstSample) 
  { // NaN用来等待检查从arduino过来的数据
    for (w=0;w<=2;w++) 
    {
      RwEst[w] = RwAcc[w];    // 初始化加速度传感器读数
    }
  }
  else 
  {
    // 对RwGyro进行评估
    if (abs(RwEst[2]) < 0.1) 
    {
      // Rz值非常的小，它的作用是作为Axz与Ayz的计算参照值，防止放大的波动产生错误的结果。
      // 这种情况下就跳过当前的陀螺仪数据，使用以前的。
      for (w=0;w<=2;w++) 
      {
        RwGyro[w] = RwEst[w];
      }
    }
    else 
    {
      // ZX/ZY平面和Z轴R的投影之间的角度，基于最近一次的RwEst值
      for (w=0;w<=1;w++)
      {
        tmpf = Gyro[w];                        // 获取当前陀螺仪的deg/s
        tmpf *= interval / 1000.0f;                     // 得到角度变化值
        Awz[w] = atan2(RwEst[w], RwEst[2]) * 180 / PI;   // 得到角度并转换为度
        Awz[w] += tmpf;             // 根据陀螺仪的运动得到更新后的角度
      }

      // 判断RzGyro是多少，主要看Axz的弧度是多少
      // 当Axz在-90 ..90 => cos(Awz) >= 0这个范围内的时候RzGyro是准确的
      signRzGyro = ( cos(Awz[0] * PI / 180) >=0 ) ? 1 : -1;

      // 从Awz的角度值反向计算RwGyro的公式请查看网页 http://starlino.com/imu_guide.html
      for (w=0;w<=1;w++) 
      {
        RwGyro[0] = sin(Awz[0] * PI / 180);
        RwGyro[0] /= sqrt( 1 + squared(cos(Awz[0] * PI / 180)) * squared(tan(Awz[1] * PI / 180)) );
        RwGyro[1] = sin(Awz[1] * PI / 180);
        RwGyro[1] /= sqrt( 1 + squared(cos(Awz[1] * PI / 180)) * squared(tan(Awz[0] * PI / 180)) );
      }
      RwGyro[2] = signRzGyro * sqrt(1 - squared(RwGyro[0]) - squared(RwGyro[1]));
    }

    // 把陀螺仪与加速度传感器的值进行结合
    for (w=0;w<=2;w++) RwEst[w] = (RwAcc[w] + wGyro * RwGyro[w]) / (1 + wGyro);

  }

  firstSample = false;

  SerialUSB.print(RwEst[0]);//x
  SerialUSB.print("	");
  SerialUSB.print(RwEst[1]); //y
  SerialUSB.print("	");
  SerialUSB.println(RwEst[2]);//z
  delay(50);

}

float squared(float x) 
{
  return x*x;
}

void getEstimatedInclination(unsigned int interval_us){

  static float tmpf;

  tmpf = interval_us/1000.0f;

  if (seq==0)
  {
    RwEstt[0]=0.0f;
    RwEstt[1]=0.0f;

    fx1=0.0f; 
    fx2=0.0f; 
    fx3=0.0f;
    fy1=0.0f; 
    fy2=0.0f; 
    fy3=0.0f;
    seq++;
  }
  //

 
  RwAcc[0]*=57.29577951;


  fx1=((RwAccc[0]-RwEstt[0])*(2*ACC_WEIGHT_MAX));
  fx2+=(((RwAccc[0]-RwEstt[0])*ACC_WEIGHT_MAX*ACC_WEIGHT_MAX)*tmpf);
  fx3=Gyro[0]+fx1+fx2;
  RwEstt[0]+=fx3*tmpf;


  RwAccc[1]=atan2f(RwAcc[1], sqrtf(RwAcc[0]*RwAcc[0]+RwAcc[2]*RwAcc[2]));
  RwAccc[1]*=57.29577951;

  fy1=((RwAccc[1]-RwEstt[1])*(2*ACC_WEIGHT_MAX));
  fy2+=(((RwAccc[1]-RwEstt[1])*ACC_WEIGHT_MAX*ACC_WEIGHT_MAX)*tmpf);
  fy3=Gyro[1]+fy1+fy2;
  RwEstt[1]+=fy3*tmpf;

}
