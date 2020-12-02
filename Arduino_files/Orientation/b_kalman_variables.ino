// Acceleration (Before jerk integration)
float acc  = 0; // Current acceleration
float accp = 0; // Previous acceleration

// Jerk
float jerk  = 0; // Current jerk
float jerkp = 0; // Previous jerk

// Acceleration (After  jerk integration)
float newacc  = 0; // New acceleration
float newaccp  = 0; // Previous new acceleration

// Velocity (After jerk integartion)
float velp = 0; // Previous velocity
float velc = 0; // Current velocity

// Distance (After jerk integration)
float dist = 0; // Displacement 

// Cycle time
float dt = 0.01; 

// Kalman filter constants
// acc
float aXk   = 0;      // Current state vector
float aXk1  = 0;             // Previous state vector
float aXkk1 = 0;            // Predicted next state vector      
float aPk   = 0;             // Current state estimate uncetainity        
float aPk1  = 0.00001;  // Previous state estimate uncetainity
float aPkk1 = 0; // Predeicted current state estimate uncetainity
float aKk   = 0;   // Kalman gain
float ayk   = 0;   // Innovation matrix                        
float aQ    = 0.00001;  // Process noise matrix                                 
float aRk   = 0.015; // Measurement uncertainity matrix

                         
