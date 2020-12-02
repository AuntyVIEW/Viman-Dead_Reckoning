void setup()
{
  
  // I2C bus init done in SBWIRE.h
  Serial.begin(115200);
 
  // initialize device
  mpu.initialize();
 
 
  // load and configure the DMP
  devStatus = mpu.dmpInitialize();
 
  // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(4);
    mpu.setYGyroOffset(42);
    mpu.setZGyroOffset(0);
    mpu.setXAccelOffset(-3780);
    mpu.setYAccelOffset(-788);
    mpu.setZAccelOffset(726); // 1688 factory default for my test chip
 
  // make sure it worked (returns 0 if so)
  if (devStatus == 0)
  {
    // Calibration Time: generate offsets and calibrate our MPU6050
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
 
    // turn on the DMP, now that it's ready
    mpu.setDMPEnabled(true);
 
 
    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    dmpReady = true;
 
    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  }
  else
  {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
  }
 
  // configure LED for output
  pinMode(LED_PIN, OUTPUT);
  sinceLastIMUCheck = 0; //this manages 'other program stuff' cycle
}
