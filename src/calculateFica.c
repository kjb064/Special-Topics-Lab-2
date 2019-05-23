// File calculateFica.c

float calculateFica(int Flimit, float Frate, float ytd, float gross){
    float total = ytd + gross;

    if(ytd >= Flimit)
        return 0.0;
    else
        if(total <= Flimit)
            return gross * Frate;
        else
            return (Flimit - ytd) * Frate;
        //endif
    //endif
}

