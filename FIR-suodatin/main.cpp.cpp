#include "mbed.h"
//#include <signaali.h>
#include <aani.h>
//#include <hairio.h>
#include <kertoimet.h>

//#define TS 0.0001    //Ts = i/FS = 1/10000 => 0.0001 
#define TS 0.000125   //Ts = i/FS = 1/8000 => 0.000125 
//#define TS 0.001   //Ts = i/FS = 1/8000 => 0.000125 

Serial pc (USBTX,USBRX);
DigitalOut led1(LED1);
Ticker aDDaKello;
AnalogIn AnalogToDigital(A0);
AnalogOut DigitalToAnalog(A2);

float muisti[pituus] = {0};
float tulos = 0.0;

int indeksi = 0;

float suodatin(float nayte)
{
	for(int i = pituus-1; i > 0; i--){
		muisti[i] = muisti[i-1];
	}
	
	muisti[0] = nayte;
	
	tulos = 0.0;
	
	for(int j = 0; j < pituus; j++){
		tulos += muisti[j] * kertoimet[j];
	}
	
	return tulos;
}

void aDDaKello_isr(void)
{
    indeksi = (indeksi + 1)%79998;
	float tulos = suodatin(taulukko[indeksi]);
	DigitalToAnalog = tulos;
}

int main() {

	aDDaKello.attach(&aDDaKello_isr, TS);
	while (1) 
	{
       //Täällä odotellaan vain, että ticker antaa keskeytyksen.
	   //pc.printf("Taalla odotellaan vain, etta ticker antaa keskeytyksen\r\n");
	   //wait(2);
	   //led1 = !led1;
	}	

}

