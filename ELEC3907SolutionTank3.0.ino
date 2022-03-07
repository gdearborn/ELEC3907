int levelMax = A0; //Probe declarations
int levelFull = A1;
int levelHalf = A2;
int levelStop = A3;
int Overide = A4; //Button for user overide to  stop system

int fillPump = 7; //pump for filling solution tank with pure water
int outPump = 6; //pump for transporting solution to plants
int dosingPump1 = 5; //dosing pump for nutrients
int dosingPump2 = 4;
int dosingPump3 = 3;
int dosingPump4 = 2;


int a, b, c, d, e; //variables for status of probes & overide
int s; //fill Pump status
int m = 0; //flag for pump
int z = 111; //Value for comparison

int ledGreen = 13;
int ledYellow = 12;
int ledRed = 11;



void setup()   //initialization of components
{
  pinMode(levelMax, INPUT);
  pinMode(levelFull, INPUT);
  pinMode(levelHalf, INPUT);
  pinMode(levelStop, INPUT);
  pinMode(Overide, INPUT);
  
  pinMode(fillPump, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);

  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledRed, LOW);
}

void loop() 
{
  s = digitalRead(fillPump);
  
  a = analogRead(levelMax);
  b = analogRead(levelFull);
  c = analogRead(levelHalf);
  d = analogRead(levelStop);
  e = analogRead(Overide);

  //if(e == 0){
//     digitalWrite(dosingPump1, LOW);
//     digitalWrite(dosingPump2, LOW);
//     digitalWrite(dosingPump3, LOW);
//     digitalWrite(dosingPump4, LOW);
//     digitalWrite(outPump, LOW); 
//     digitalWrite(fillPump, LOW);
//      
//     digitalWrite(ledGreen, LOW);
//     digitalWrite(ledYellow, LOW);
//     digitalWrite(ledRed, LOW);
//  }

// else{
    if (a >= z && b > z && c > z && d > z) //condition makes sure absolutely no liquid is allowed to be added
    {
        digitalWrite(dosingPump1, LOW);
        digitalWrite(dosingPump2, LOW);
        digitalWrite(dosingPump3, LOW);
        digitalWrite(dosingPump4, LOW);
        digitalWrite(outPump, HIGH); 
        digitalWrite(fillPump, LOW);
      
        digitalWrite(ledGreen, HIGH);
        digitalWrite(ledYellow, LOW);
        digitalWrite(ledRed, LOW);
        m == 0; // reseting pump flag
      
      
  
     }
    else if (a < z && b >= z && c > z && d > z) //condition allows nutrients to be added but not pure water
    { 
        digitalWrite(fillPump, LOW);
        digitalWrite(outPump, HIGH);
    
        digitalWrite(ledGreen, HIGH);
        digitalWrite(ledYellow, LOW);
        digitalWrite(ledRed, LOW);

        m = 0; //reseting pump flag
     
    }
    else if (a < z && b < z && c >= z && d > z) //conditon will allow nutrients to be added and water can be addded also if needed. 
    {
        if(m == 1){                    //allows the water tank to be filled to the top
          digitalWrite(fillPump, HIGH);
          digitalWrite(outPump, LOW); 
    
          digitalWrite(ledGreen, LOW); 
          digitalWrite(ledYellow, HIGH);
          digitalWrite(ledRed, LOW); 
        }
        else{                         // m==0
          digitalWrite(fillPump, LOW);
          digitalWrite(outPump, HIGH); 
    
          digitalWrite(ledGreen, LOW); 
          digitalWrite(ledYellow, HIGH);
          digitalWrite(ledRed, LOW); //allows tank to continue being emptied until redLED level to conserve pump life
      
        }

    
   
    }
    else if (a < z && b < z && c < z && d <= z) //condition will fill tank until maximum pure water is reached, adjustments to pH and nutrient levels can be made once water is done filling.
    {
      digitalWrite(fillPump, HIGH);
      digitalWrite(outPump, LOW); //fill pump is turned on to fill solution tank with water & outpump to system is disabled
    
      digitalWrite(ledGreen, LOW); 
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledRed, HIGH);

      m = 1; //Flag status that the tank is being filled with pure water.
    
    }
  
  
}
