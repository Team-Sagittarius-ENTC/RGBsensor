
float raw_data[9][4] = {
    {0   , 4.36, 2.76, 2.34},
    {31  , 4.93, 3.22, 2.90},
    {63  , 5.68, 3.86, 3.66},
    {95  , 6.55, 4.71, 4.59},
    {127 , 6.79, 4.98, 4.90},
    {159 , 7.21, 5.45, 5.39},
    {191 , 7.56, 5.86, 5.85},
    {223 , 8.11, 6.55, 6.56},
    {255 , 8.35, 6.90, 6.92}
                      };

float coeff_mat[3][3] {};
float RGC[3][3] {};

/*This function will return the minor matrix with signs for given coordinate*/
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
}// end of the minor value find matrix

/*This function will update the coefficiant matrix*/
void update_coeff(byte ref_){
    float beta = 0;
    float gamma = 0;
    float delta = 0;
    float theta = 0;

    for (byte i = 0; i < 9; ++i){
      beta  += raw_data[i][ref_];
      gamma += pow(raw_data[i][ref_], 2);
      delta += pow(raw_data[i][ref_], 3);
      theta += pow(raw_data[i][ref_], 4);
    }// end of the for loop

    coeff_mat[0][0] = gamma;
    coeff_mat[0][1] = beta;
    coeff_mat[0][2] = 9;

    coeff_mat[1][0] = delta;
    coeff_mat[1][1] = gamma;
    coeff_mat[1][2] = beta;

    coeff_mat[2][0] = theta;
    coeff_mat[2][1] = delta;
    coeff_mat[2][2] = gamma;
}// enf of updating coeff matrix

void regression(){
  float ans[3]{};
  float inv[3][3]{};
  float SIG_xy = 0;
  float SIG_xy2 = 0;
  float det;
  
  for (byte m = 1; m < 4; ++m){
    
    SIG_xy = 0;
    SIG_xy2 = 0;

    for(byte i = 0; i < 9; ++i){
        SIG_xy += raw_data[i][0]*raw_data[i][m];
        SIG_xy2 += raw_data[i][0]*pow(raw_data[i][m],2);
    }

    ans[0] = 1152; ans[1] = SIG_xy; ans[2] = SIG_xy2; /*Create the answer matrix*/
    update_coeff(m); /*Update coefficiant matrix*/

    /*Finding the inverse of the matrix*/
    det = coeff_mat[0][0] * minor(0,0) + coeff_mat[0][1] * minor(0,1) + coeff_mat[0][2] * minor(0,2);
    
    for(byte i = 0; i < 3; ++i){
      for(byte k = 0; k < 3; ++k){
//        float ans = minor(k,i)/det;
//        inv[i][k] = ans;
//        Serial.println(ans);
          inv[i][k] = minor(k,i) / det;
      }    
    }

    /*Matrix multiplication and add to RGC matrix*/
    for(byte i = 0; i < 3; ++i){
      for(byte k = 0; k < 3; ++k){
        RGC[m-1][i] += (inv[i][k] * ans[k]);
      }
    }

  
  }// enf of the main for loop  
}// end of regression


void setup(){
  Serial.begin(9600);
  Serial.println("Just Started!!!");
  regression();
  
    for(byte i = 0; i < 3; ++i){
    for(byte k = 0; k < 3; ++k){
      Serial.print(RGC[i][k]);
      Serial.print(k==2 ? "\n" : "\t"); 
    }
    }
    Serial.println("\n\n");
}

void loop(){
  //Serial.println("Hellooooooooo");
  //Serial.println(RGC[0][0]);
}
