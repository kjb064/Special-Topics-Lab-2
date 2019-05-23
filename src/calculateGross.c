// File calculateGross.c

float calculateGross(float hoursWkd, float payrate){
    float gross;
    if(hoursWkd > 40.0){                // Pay time and a half for hoursWkd > 40
        gross = 40.0 * payrate;
        hoursWkd = hoursWkd - 40.0;
        gross += hoursWkd * (payrate * 1.5);
    }
    else{
        gross = hoursWkd * payrate;
    }
    return gross;
}
