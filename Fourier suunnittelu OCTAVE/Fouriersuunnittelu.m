clear;
load hairio_ja_alkup;

Fs = 8000;
Ts = 1/Fs;

paikka1 = 25001;
paikka2 = 55001;

ffttulos = fft(summa)/length(summa);

tulos = ffttulos(paikka1);
resoluutio = Fs/length(summa);
amplitudi = 2*abs(tulos);
vaihe = angle(tulos);
t = 0:Ts:10-Ts;
taajuus = (paikka1 - 1)*resoluutio;

muodostettu_signaali = amplitudi*cos(2*pi*taajuus*t + vaihe);
suodatettu = (summa - muodostettu_signaali);
soundsc(suodatettu);