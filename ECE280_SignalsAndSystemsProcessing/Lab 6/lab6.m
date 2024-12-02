function [x, t] = sineWave(A, f0, fs)
    % Define the time vector from 0 to 10ms with a spacing of 1/fs
    t = 0 : 1/fs : 0.01;
    
    % Calculate the sinusoidal signal
    x = A * sin(2 * pi * f0 * t);
end

% Parameters
fs = 8000;      % Sampling rate
A = 1;          % Amplitude

% Frequencies to analyze
frequencies = [100, 200, 400, 800, 7900, 7800, 7600, 7200];

% Plot each frequency
figure;
for i = 1:length(frequencies)
    f0 = frequencies(i);
    [x, t] = sineWave(A, f0, fs);
    
    % Plot the signal
    subplot(4, 2, i);
    plot(t, x);
    title(['f_0 = ', num2str(f0), ' Hz']);
    xlabel('Time (s)');
    ylabel('Amplitude');
end

% Adjust layout
sgtitle('Sinusoidal Signals for Different Frequencies');
