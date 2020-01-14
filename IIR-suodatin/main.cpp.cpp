#include "mbed.h"
//#include <signaali.h>
#include <aani.h>
//#include <hairio.h>
//#include <kertoimet.h>
#include <IIR-kertoimet.h>

//#define TS 0.0001    //Ts = i/FS = 1/10000 => 0.0001 
#define TS 0.000125   //Ts = i/FS = 1/8000 => 0.000125 
//#define TS 0.001   //Ts = i/FS = 1/8000 => 0.000125 

Serial pc (USBTX,USBRX);
DigitalOut led1(LED1);
Ticker aDDaKello;
AnalogIn AnalogToDigital(A0);
AnalogOut DigitalToAnalog(A2);

float muisti[8][3] = {0};
float tulos = 0.0;

int indeksi = 0;

float suodatin(float nayte)
{
	float tulos = nayte;
	
	for(int i = 0; i < riveja; i++){
		muisti[i][2] = muisti[i][1];
		muisti[i][1] = muisti[i][0];
		muisti[i][0] = tulos - SOS[i][8] * muisti[i][1] - SOS[i][9] * muisti[i][2];
		tulos = SOS[i][0]*muisti[i][0] + SOS[i][1] * muisti[i][1] + SOS[i][2] * muisti[i][2];
	}
	
	return tulos;
}

void aDDaKello_isr(void)
{
    indeksi = (indeksi + 1)%79998;
	DigitalToAnalog = suodatin(taulukko[indeksi]);
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

