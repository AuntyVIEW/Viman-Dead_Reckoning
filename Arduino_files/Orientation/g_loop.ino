void loop()
{
  // if programming failed, don't try to do anything
  if (!dmpReady) return;
 
  if (mpu.dmpPacketAvailable())
  {
    GetData();
    kalman();
 
    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
  }
 
  //other program stuff block - executes every IMU_CHECK_INTERVAL_MSEC Msec
  //for this test program, there's nothing here except diagnostics printouts
  if (sinceLastIMUCheck >= IMU_CHECK_INTERVAL_MSEC)
  {
    sinceLastIMUCheck -= IMU_CHECK_INTERVAL_MSEC;
    Serial.print(out[0]); // Printing Distance travelled along X-axis
    Serial.print(",");    // For visualizing in oython, comment this and above line
    Serial.print(out[1]); 
    Serial.print(",");
    Serial.print(out[2]);
    Serial.print(",");
    Serial.println(out[3]);
 
    if (global_fifo_count != 0)
    {
      //Serial.print("FIFO Reset!");
      mpu.resetFIFO();
    }
  }
}
