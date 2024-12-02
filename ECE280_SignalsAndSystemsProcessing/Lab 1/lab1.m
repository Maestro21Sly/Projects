%ECE 280 Lab 1 Charlotte Roh, adapted by Evelyn Putri

%initialize sampling frequency
fs = 8000;

%create array of note frequencies
note = zeros(1,12);
for i = 0:11
    note(i+1) = 220*(2^(i/12));
end
A = note(1);
Asharp = note(2);
B = note(3);
C = note(4);
Csharp = note(5);
D = note(6);
Dsharp = note(7);
E = note(8);
F = note(9);
Fsharp = note(10);
G = note(11);
Gsharp = note(12);

%create time vectors
quarter = 0:1/fs:0.25-1/fs; %[start:increment:end]
half = 0:1/fs:0.5-1/fs;
whole = 0:1/fs:1-1/fs;

%creating rest vectors 
quarter_rest= zeros(size(quarter));
half_rest = zeros(size(half));
whole_rest = zeros(size(whole));

%play quarter note A
%y = cos(2 * pi * A * whole); %cos(2 * pi * frequency * time)
%sound(y,fs);

%playing a 1000Hz frequency note 
%y = cos(2 * pi * 1000 * quarter); %cos(2 * pi * frequency * time)
%sound(y,fs);


%Generating a function that accepts arguments to create a variety of notes
function result = generatesoundnotes (frequency, duration)
    if frequency==1 ||A
            %soundwave = cos(0.5*pi*frequency*duration);
            soundwave = 0.7*exp(-1*duration/2)*cos(0.5*pi*frequency*duration);

        else
            %soundwave = cos(2*pi*frequency*duration);
            soundwave = 0.7*exp(-1*duration/2).*cos(2*pi*frequency*duration);
    end    
        
        result = soundwave;
end

% generating and playing sound
first2measures = [generatesoundnotes(B,quarter)  generatesoundnotes(A,quarter) generatesoundnotes(G,quarter)  generatesoundnotes(A,quarter) generatesoundnotes(B,quarter_rest) generatesoundnotes(B,quarter) generatesoundnotes(B,quarter) generatesoundnotes(B,half) generatesoundnotes(B,quarter_rest)];
second2measures = [generatesoundnotes(A,quarter) generatesoundnotes(A,quarter) generatesoundnotes(A,half)  generatesoundnotes(A,quarter_rest) generatesoundnotes(B,quarter) generatesoundnotes(D,quarter) generatesoundnotes(D,half) generatesoundnotes(B,quarter_rest)];
third2measures = [generatesoundnotes(B,quarter) generatesoundnotes(A,quarter) generatesoundnotes(G,quarter)  generatesoundnotes(A,quarter) generatesoundnotes(B,quarter_rest) generatesoundnotes(B,quarter) generatesoundnotes(B,quarter) generatesoundnotes(B,quarter) generatesoundnotes(B,quarter) generatesoundnotes(B,quarter_rest)];
fourth2measures = [generatesoundnotes(A,quarter) generatesoundnotes(A, quarter) generatesoundnotes(B,quarter) generatesoundnotes(A,quarter) generatesoundnotes(G,whole)];

song =[first2measures second2measures third2measures fourth2measures];
soundsc(song,fs);

%plotting the graph
song =[first2measures second2measures third2measures fourth2measures];
songnorm = song/max(song);
filename = Arizie_SongTitle.wav';
audiowrite(filename, songnorm, fs);
info = audioinfo('Arizie_SongTitle.wav');
t = 0:seconds(1/fs):seconds(info.Duration);
t = t(1:end-1);
plot(t, songnorm);
xlabel('Time')
ylabel('Audio Signal')
