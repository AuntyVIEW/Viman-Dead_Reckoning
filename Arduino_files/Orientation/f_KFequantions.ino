// Kalman filtering

void kalman(){
  // Acceleration filtering
  // Step-1: Predict
  aXkk1 = aXk1;           // State extrapolation equation
  aPkk1 = aPk1 + aQ;  // Covariance extrapolation equation

  // Step-2: Measure
  ayk = acc - aXkk1;  // innovation
  
  // Step-3: Update
  aKk = aPkk1/(aPkk1 + aRk); // Kalman gain matrix
  aXk = aXkk1 + (aKk*ayk);           // Filtered state vector
  aPk = (1 - aKk)*aPkk1;         // Covariance update

  // Hard limiting acceleration
  if(fabs(aXk) <= 0.03){
    aXk = 0;
  }
  
  // Velocity estimation
  velc = velp + aXk1*dt + (aXk - aXk1)*dt*0.5;

  // Hard limiting velocity
  if(fabs(velc) <= 0.01){
    velc = 0;
  }

  dist = dist + velp*dt + aXk1*dt*dt*0.5 + (aXk - aXk1)*dt*dt*(1/6); 
  
  out[0] = dist*100; // Distance in cm (Along X-axis)

  
  velp = velc;
  aXk1 = aXk;
  aPk1 = aPk;
}
