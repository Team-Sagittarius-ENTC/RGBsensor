float coeff_mat[3][3] {}; // this is the coefficiant matrix which uses to calculate RGCs

float raw_data[9][6]{
  {0.00,   0.00,   0.00,   3.89, 2.43, 2.04},
  {31.00,  31.00,  31.00,  4.53, 2.85, 2.59},
  {63.00,  63.00,  63.00,  5.32, 3.49, 3.36},
  {95.00,  95.00,  95.00,  6.25, 4.28, 4.28},
  {127.00, 127.00, 127.00, 6.50, 4.60, 4.60},
  {159.00, 159.00, 159.00, 6.96, 5.05, 5.07},
  {191.00, 191.00, 191.00, 7.35, 5.51, 5.61},
  {223.00, 223.00, 223.00, 7.95, 6.25, 6.35},
  {255.00, 255.00, 255.00, 8.20, 6.60, 6.73}                     
}; // this array will use the store sensored data for the callibration purposes

float RGC[3][3]{ //regression constants
  {6.5529613039948345, -21.70716070508206, -10.88222916702216},
  {1.4848949805768825, 46.67373805102034, -119.51068638392826},
  {2.514421337210365, 31.627137726753972, -72.78155680513919 }
};



float minor(byte i, byte j){
  float arr[2][2] = {{0,0},{0,0}};
  
  byte a = 0;
  byte b = 0;
  for (byte i_=0; i_<3; ++i_){
    if( i_ != i){
        b = 0;
        for (byte j_=0; j_<3; ++j_){
          if(j_ != j){
            arr[a][b] = coeff_mat[i_][j_];
            b++;
          }// end of second if
        } // end of second for loop
        a++;
    }// end of main if
  }// end of the main for loop
  
  return (arr[0][0]*arr[1][1] - arr[0][1]*arr[1][0]) * (pow((-1), i) * pow((-1),j));
}// end of the minor function

void update_coeff(byte ref_, byte itter = 9){
  float beta = 0;
  float gamma = 0;
  float delta = 0;
  float theta = 0;

  for (byte i = 0; i < itter; ++i){
    beta  += raw_data[i][ref_];
    gamma += pow(raw_data[i][ref_], 2);
    delta += pow(raw_data[i][ref_], 3);
    theta += pow(raw_data[i][ref_], 4);
  }// end of the for loop

  coeff_mat[0][0] = gamma;
  coeff_mat[0][1] = beta;
  coeff_mat[0][2] = itter;

  coeff_mat[1][0] = delta;
  coeff_mat[1][1] = gamma;
  coeff_mat[1][2] = beta;

  coeff_mat[2][0] = theta;
  coeff_mat[2][1] = delta;
  coeff_mat[2][2] = gamma;
}// end of the update coeff function


//Regression processor
void procRegression(byte itter = 9){
  float ans[3]{};
  float inv[3][3]{};
  float SIG_x = 0;
  float SIG_xy = 0;
  float SIG_xy2 = 0;
  float det;
  
  for (byte m = 3; m < 6; ++m){
    SIG_x = 0;
    SIG_xy = 0;
    SIG_xy2 = 0;

    for(byte i = 0; i < 9; ++i){
        SIG_x  += raw_data[i][m-3];
        SIG_xy  += raw_data[i][m-3] * raw_data[i][m];
        SIG_xy2 += raw_data[i][m-3] * pow(raw_data[i][m],2);
    }

    ans[0] = SIG_x; ans[1] = SIG_xy; ans[2] = SIG_xy2; /*Create the answer matrix*/
    update_coeff(m, itter); /*Update coefficiant matrix*/

    /*Finding the inverse of the matrix*/
    det = coeff_mat[0][0] * minor(0,0) + coeff_mat[0][1] * minor(0,1) + coeff_mat[0][2] * minor(0,2);
    
    for(byte i = 0; i < 3; ++i){
      for(byte k = 0; k < 3; ++k){
          inv[i][k] = minor(k,i) / det;
      }    
    }

    /*Matrix multiplication and add to RGC matrix*/

    for(byte i = 0; i < 3; ++i){
      for(byte k = 0; k < 3; ++k){
        RGC[m-3][i] += (inv[i][k] * ans[k]);
      }
    }
  
  }// enf of the main for loop  
}//end of regressingpric



void setup(){
  Serial.begin(9600);
  Serial.println("Just Started!!!");


  for(byte i = 0; i < 3; ++i){
    for(byte k = 0; k < 3; ++k){
      RGC[i][k] = 0;
    }
    }
  
  procRegression(9);
  
    for(byte i = 0; i < 3; ++i){
    for(byte k = 0; k < 3; ++k){
      Serial.print(RGC[i][k]);
      Serial.print(k==2 ? "\n" : " \t"); 
    }
    }
    Serial.println("\n\n");
}

void loop(){
  //Serial.println("Hellooooooooo");
  //Serial.println(RGC[0][0]);
}
