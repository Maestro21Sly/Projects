fs =8000;
function PhoneNum = dtmfdial(KeyNames, fs)
% DTMFDIAL Create a signal vector of tones which will dial a
% DTMF telephone system.
%
% usage: PhoneNum = dtmfdial(KeyNames, fs)
% KeyNames = a vector of characters containing valid key names
% fs = sampling frequency
% PhoneNum = signal vector that is the concatenation of DTMF tones
fs =8000;
% Defining the DTMF key matrix and frequency matrices
dtmf.Keys = ['1', '2', '3';
             '4', '5', '6';
             '7', '8', '9';
             '*', '0', '#'];

dtmf.colTones = ones(4,1) * [1209, 1336, 1477];
dtmf.rowTones = [697; 770; 852; 941] * ones(1,3);


% Duration of each tone and pause
toneDuration = 0.5;
pauseDuration = 0.2;

% time vectors for tone and pause
tNote = 0:(1/fs):(toneDuration-1/fs);
tPause = 0:(1/fs):(pauseDuration-1/fs);

% Create pause signal
pauseSignal = zeros(size(tPause));

% Initialize output vector
PhoneNum = [];

% Process each key in the input
for key = KeyNames
    % Find the position of the key in the matrix
    [R, C] = find(dtmf.Keys == key);
    
    if ~isempty(R) && ~isempty(C)
        % Get the corresponding frequencies
        f1 = dtmf.rowTones(R, C);  
        f2 = dtmf.colTones(R, C);  
        
        % Generate the dual tone signal
        toneSignal = sin(2*pi*f1*tNote) + sin(2*pi*f2*tNote);
        
        % Add tone and pause to the output
        PhoneNum = [PhoneNum, toneSignal, pauseSignal];
    end
end
end 

function plot_dtmf_tones_1_5_9()
    % Setting up parameters
    fs = 8000;  % Sampling frequency
    keys = ['1', '5', '9'];  % Keys to analyze
    freqs = [697, 770, 852, 941, 1209, 1336, 1477];  % DTMF frequencies

    % Create figure for all plots
    figure('Position', [100, 100, 1200, 800]);
    
    % Loop through each key and plot its DTMF tone
    for i = 1:length(keys)
        key = keys(i);
        signal = dtmfdial(key, fs);  % Generate DTMF signal
        t = (0:0.5*fs-1)/fs;  
        
        % Plotting the time-domain signal
        subplot(3, 1, i);
        plot(t, signal(1:length(t)), 'DisplayName', ['Key ' key]);
        title(['DTMF Signal in Time Domain for Key ' key]);
        xlabel('Time (s)');
        ylabel('Amplitude');
        legend('show');
        grid on;
    end
end

%creating plots for keys 1, 5, and 9
%plot_dtmf_tones_1_5_9();

%analysis with correlations
function analyze_dtmf_tones()
    % Setup parameters
    fs = 8000;  % Sampling frequency
    keys = ['1', '5', '9'];  
    freqs = [697, 770, 852, 941, 1209, 1336, 1477];  
    
    for i = 1:length(keys)
        % Create a new figure for each key
        figure('Position', [100, 100, 800, 600]);
        
        % Generating the DTMF signal for the current key
        signal = dtmfdial(keys(i), fs);
        t = (0:0.5*fs-1)/fs;  
        
        % Normalizing the signal to the range -1 to 1
        signal = signal / max(abs(signal));  %
        
        % Plotting original signal against each frequency in subplots
        for j = 1:length(freqs)
            % Creating reference signal for the current frequency
            ref = sin(2*pi*freqs(j)*t);
            ref = ref / max(abs(ref));  % Normalize reference signal
            
            % Creating a subplot for the current frequency
            subplot(length(freqs), 1, j);  % Change to vertical layout
            plot(t, signal(1:length(t)), 'k', 'LineWidth', 0.1, 'DisplayName', ['Key ' keys(i)]);  % Black for original
            hold on;
            plot(t, ref, 'Color', [0.778 0.547 0.502], 'LineWidth', 0.01, 'DisplayName', sprintf('%d Hz', freqs(j)));  % Light blue for reference
            hold off;
            title(sprintf('Key %s - Original vs %d Hz', keys(i), freqs(j)));
            xlabel('Time (s)');
            ylabel('Amplitude');
            ylim([-1 1]);  % Set y-axis limits
            grid on;
            legend('show');
        end
    end
end

%plotting the analysis
analyze_dtmf_tones();

%using correlation to find unknown_key
function analyze_unknown_key()
    % Load the unknown key
    load('UnknownKey.mat');

    % Normalize the UnknownKey to be between -1 and 1
    UnknownKey = UnknownKey / max(abs(UnknownKey));
    
    fs = 8000;
    freqs = [697, 770, 852, 941, 1209, 1336, 1477];
    
    figure('Position', [100, 100, 800, 600]);
    
    % Store maximum correlation for each frequency
    max_corrs = zeros(1, length(freqs));
    
    t_ref = 0:1/fs:0.01; % Time reference for sinusoids
    for i = 1:length(freqs)
        ref = sin(2*pi*freqs(i)*t_ref);
        corr_result = xcorr(UnknownKey, ref);
        corr_result = corr_result / max(abs(corr_result)); % Normalize correlation result
        max_corrs(i) = max(abs(corr_result));
        
        lag = (-length(corr_result)/2:length(corr_result)/2-1)/fs;
        
        % Only include non-negative lags
        positive_lags = lag(lag >= 0);
        positive_corrs = corr_result(lag >= 0);
        
        % Create a subplot for each frequency
        subplot(length(freqs), 1, i);
        plot(positive_lags * 1000, positive_corrs, 'DisplayName', sprintf('%d Hz', freqs(i)), 'LineWidth', 0.01);
        hold on;
        
        % Plot the normalized unknown key for reference (time axis adjusted)
        t_unknown = (0:length(UnknownKey)-1) / fs;
        plot(t_unknown * 1000, UnknownKey, 'k', 'LineWidth', 1, 'DisplayName', 'Unknown Key');
        hold off;
        
        title(sprintf('Correlation with %d Hz', freqs(i)));
        xlabel('Lag (ms)');
        ylabel('Normalized Correlation');
        grid on;
        legend('show', 'Location', 'best');
    end    
end

%analyze_unknown_key();
