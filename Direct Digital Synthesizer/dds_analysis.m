clear

fileBaseName = 'dds_';
FOUT = 80.95736e6; %10.457e6;
LUTDEPTH = '64k';
print_figures = true;
ddsOut_ = importdata('Z:\\FPGA\\Project5\\SinOutput1.dat');
ddsOut = j*ddsOut_(:,1) + ddsOut_(:,2);
fs = 245.76E6;              % sample rate
fig = 1;

figure(fig)
fig = fig + 1;
x = 0 : length(ddsOut)-1;
plot(x, real(ddsOut), 'b', x, imag(ddsOut), 'r');
grid
legend('cos', 'sin');
title('DDS Output - HLS Design');
axis([0,60, -1.1, 1.1]);
xlabel('Time');
ylabel('Amplitude');
fileName = strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(fileBaseName, 'time_' ), 'fs'), num2str(fs/1e6)), '_fout'), num2str(FOUT/1e6)), 'lut'), LUTDEPTH), '.eps');
if print_figures
    %print -depsc2 dds_time_fs245dot76_fout10dot457_64KLUT.eps
    print('-deps2', fileName);
end

% DDS output spectrum

figure(fig)
fig = fig + 1;

wina = bkharris(4096);
winb = bkharris(4097);
win2 = conv(wina,winb);

nFFT = 8192;
beta = 20.5;
win2 = kaiser(nFFT,beta);
plot(win2);
xlabel('Time');
ylabel('Amplitude');
title('Analysis Window');

figure(fig)
fig = fig + 1;

H = abs(fftshift(fft(win2.*ddsOut(1:length(win2)), nFFT)));
H = 20*log10(H/max(H));
xVals = (-0.5 : 1/nFFT : 0.5-1/nFFT)*fs;
plot(xVals, H);
grid
title('DDS Spectrum - HLS Design');
xlabel('Time');
ylabel('dB');
axis([-fs/2 fs/2 -120 5]);
fileName = strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(fileBaseName, 'freq_' ), 'fs'), num2str(fs/1e6)), '_fout'), num2str(FOUT/1e6)), 'lut'), LUTDEPTH), '.eps');
if print_figures
    %print -depsc2 dds_freq_fs245dot76_fout10dot457_64KLUT.eps
    print('-depsc2', fileName);
end



