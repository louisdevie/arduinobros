// fait office de masse
const int groundPin = 7;
// pin de controle du buzzer
const int buzzPin = 9;

// hauteur des notes en Hz (25 premières secondes), 0 = silence
float frequency[113] = {
    659.3, 659.3,   0.0, 659.3,   0.0, 523.3, 659.3,   0.0, 784.0,   0.0, 392.0,
    0.0,   523.3,   0.0, 392.0,   0.0, 329.6,   0.0, 440.0,   0.0, 493.9,   0.0,
    466.2, 440.0,   0.0, 392.0, 659.3, 784.0, 880.0,   0.0, 698.5, 784.0,   0.0,
    659.3,   0.0, 523.3, 587.3, 493.9,   0.0, 523.3,   0.0, 392.0,   0.0, 329.6,
      0.0, 440.0,   0.0, 493.9,   0.0, 466.2, 440.0,   0.0, 392.0, 659.3, 784.0,
    880.0,   0.0, 698.5, 784.0,   0.0, 659.3,   0.0, 523.3, 587.3, 493.9,   0.0,
    784.0, 740.0, 698.5, 622.3,   0.0, 659.3,   0.0, 415.3, 440.0, 523.3,   0.0,
    440.0, 523.3, 587.3,   0.0, 784.0, 740.0, 698.5, 622.3,   0.0, 659.3,   0.0,
    1046.5,   0.0, 1046.5, 1046.5,   0.0, 784.0, 740.0, 698.5, 622.3,   0.0, 659.3,
      0.0, 415.3, 440.0, 523.3,   0.0, 440.0, 523.3, 587.3,   0.0, 622.3,   0.0,
    587.3,   0.0, 523.3};
// durée des notes en ms
unsigned int duration[113] =  {
      160,   160,   160,   160,   160,   160,   160,   160,   160,   480,   160,
      480,   160,   320,   260,   320,   160,   320,   160,   160,   160,   160,
      160,   160,   160,   240,   240,   240,   160,   160,   160,   160,   160,
      160,   160,   160,   160,   160,   320,   160,   320,   160,   320,   160,
      320,   160,   160,   160,   160,   160,   160,   160,   240,   240,   240,
      160,   160,   160,   160,   160,   160,   160,   160,   160,   160,   640,
      160,   160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
      160,   160,   160,   320,   160,   160,   160,   160,   160,   160,   160,
      160,   160,   160,   160,   800,   160,   160,   160,   160,   160,   160,
      160,   160,   160,   160,   160,   160,   160,   160,   320,   160,   320,
      160,   320,   160};

// joue une note
void buzz(float F, float D){
    if(F==0){
        // si c'est un silence
        delay(D);
    } else {
        // période en µs
        int T = 1000000/F;
        // divise la note en deux pour faire un signal carré avec alpha = T1/T
        int T1 = T/2;
        int T2 = T-T1;
        // nombre de répétitions du motif
        int R = (D/T)*1000;
        // temps perdu dans l'arrondi
        int L = (1000*D) - (T*R);
        // signal carré, correspond à un bip
        for(int i=0; i<R; i++){
            digitalWrite(buzzPin, HIGH);
            delayMicroseconds(T1);
            digitalWrite(buzzPin, LOW);
            delayMicroseconds(T2);
        }
        // pour stabiliser le tempo sinon la durée d'une note dépends de sa hauteur et c la rue
        delayMicroseconds(L);
    }
    // espace entre les notes sinon c moche
    delay(5);
}

void setup(){
    pinMode(groundPin, OUTPUT);
    pinMode(buzzPin, OUTPUT);
    pinMode(13, OUTPUT);
    digitalWrite(groundPin, LOW);
    bool state = true;
    for(int i=0; i<113; i++){
        // faire clignoter la led intégrée
        digitalWrite(13, state);
        state = !state;
        buzz(frequency[i], duration[i]);
    }
}

// et g pas besoin de loop
void loop(){}
