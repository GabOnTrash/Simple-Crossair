#pragma once  

struct Colore
{
    float R;
    float G;
    float B;

    const float* Array() const;  // funzione che restituisce un puntatore al primo membro di Colore, R
};
