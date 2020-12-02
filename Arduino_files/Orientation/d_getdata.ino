void GetData()
{
  // At least one data packet is available
 
  mpuIntStatus = mpu.getIntStatus();
  fifoCount = mpu.getFIFOCount();// get current FIFO count
 
  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus & _BV(MPU6050_INTERRUPT_FIFO_OFLOW_BIT)) || fifoCount >= 1024)
  {
    // reset so we can continue cleanly
    mpu.resetFIFO();
    Serial.println(F("FIFO overflow!"));
 
    // otherwise, check for DMP data ready interrupt (this should happen frequently)
  }
  else if (mpuIntStatus & _BV(MPU6050_INTERRUPT_DMP_INT_BIT))
  {
    // read all available packets from FIFO
    while (fifoCount >= packetSize) // Lets catch up to NOW, in case someone is using the dreaded delay()!
    {
      mpu.getFIFOBytes(fifoBuffer, packetSize);
      // track FIFO count here in case there is > 1 packet available
      // (this lets us immediately read more without waiting for an interrupt)
      fifoCount -= packetSize;
    }
    global_fifo_count = mpu.getFIFOCount(); //should be zero here
 
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    
    mpu.dmpGetAccel(&aa, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
    mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
  }

  acc = aaWorld.x*g/16384; 
  out[1] = ypr[0]*180/M_PI;
  out[2] = ypr[1]*180/M_PI;
  out[3] = ypr[2]*180/M_PI;
}
