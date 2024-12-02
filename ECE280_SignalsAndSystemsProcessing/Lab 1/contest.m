
%initialize sampling frequency
fs = 44100;

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

FG = Dsharp + Gsharp + B + G /3;

%create time vectors
quarter = 0:1/fs:0.25-1/fs; %[start:increment:end]
half = 0:1/fs:0.5-1/fs;
whole = 0:1/fs:1-1/fs;

%creating rest vectors 
quarter_rest= zeros(size(quarter));
half_rest = zeros(size(half));
whole_rest = zeros(size(whole));

%play quarter note A
%y = cos(2 * pi * A * quarter); %cos(2 * pi * frequency * time)
%sound(y,fs);

%playing a 1000Hz frequency note 
%y = cos(2 * pi * 1000 * quarter); %cos(2 * pi * frequency * time)
%sound(y,fs);


%Generating a function that accepts arguments to create a variety of notes
function result = generatesoundnotes (note_frequency, duration)
    if note_frequency == 1  
            %soundwave = cos(0.5*pi*frequency*duration);
            soundwave = 0.5*exp(-1*duration/700).*cos(0.5*pi*note_frequency*duration + (2*pi*duration));

        else 
            %soundwave = cos(2*pi*frequency*duration);
            soundwave = 0.8*exp(-1*duration*note_frequency/90).*cos(2*pi*note_frequency*duration);
    end    
        
        result = soundwave;
end

% generating and playing sound
firstrightmeasures = [generatesoundnotes(C,quarter)  generatesoundnotes(C,quarter) generatesoundnotes(G,quarter)  generatesoundnotes(G,quarter) generatesoundnotes(A,quarter) generatesoundnotes(A,quarter) generatesoundnotes(G,quarter) generatesoundnotes(F,quarter) generatesoundnotes(F,quarter) generatesoundnotes(G,whole)];
secondrightmeasures = [generatesoundnotes(E,quarter) generatesoundnotes(E,quarter) generatesoundnotes(D,quarter)  generatesoundnotes(D,quarter) generatesoundnotes(C,quarter) generatesoundnotes(G,quarter) generatesoundnotes(G,quarter) generatesoundnotes(F,quarter)];
thirdrightmeasures = [generatesoundnotes(FG,quarter) generatesoundnotes(E,quarter) generatesoundnotes(E,quarter)  generatesoundnotes(D,quarter) generatesoundnotes(G,quarter) generatesoundnotes(G,quarter) generatesoundnotes(F,quarter) generatesoundnotes(F,quarter) generatesoundnotes(E,quarter) generatesoundnotes(E,quarter)];
fourthrightmeasures = [generatesoundnotes(D,quarter) generatesoundnotes(C, quarter) generatesoundnotes(G,quarter) generatesoundnotes(G,quarter) generatesoundnotes(A,quarter) generatesoundnotes(FG,quarter) generatesoundnotes(F,quarter) generatesoundnotes(F,quarter) generatesoundnotes(E,quarter) generatesoundnotes(E,quarter) generatesoundnotes(D,quarter) generatesoundnotes(C,quarter)];

firstleftmeasures = [generatesoundnotes(E,quarter) generatesoundnotes(E,quarter) generatesoundnotes(E,quarter) generatesoundnotes(FG,quarter) generatesoundnotes(FG,quarter) generatesoundnotes(E,quarter) generatesoundnotes(D,quarter) generatesoundnotes(D,quarter) generatesoundnotes(C,quarter) generatesoundnotes(C,quarter)];
secondleftmeasures =[generatesoundnotes(B,quarter) generatesoundnotes(B,quarter) generatesoundnotes(C,quarter) generatesoundnotes(E,quarter) generatesoundnotes(E,quarter) generatesoundnotes(D,quarter) generatesoundnotes(D,quarter) generatesoundnotes(C,quarter) generatesoundnotes(B,quarter) generatesoundnotes(E,quarter) generatesoundnotes(E,quarter)];
thirdleftmeasures =[generatesoundnotes(D,quarter) generatesoundnotes(C,quarter) generatesoundnotes(C,quarter) generatesoundnotes(G,quarter) generatesoundnotes(E,quarter) generatesoundnotes(E,quarter) generatesoundnotes(E,quarter) generatesoundnotes(FG,quarter) generatesoundnotes(G,quarter) generatesoundnotes(A,quarter) generatesoundnotes(B,quarter) generatesoundnotes(C,quarter)];
fourthleftmeasures =[generatesoundnotes(D,quarter) generatesoundnotes(A,quarter) generatesoundnotes(G,quarter) generatesoundnotes(C,quarter) generatesoundnotes(G,quarter) generatesoundnotes(FG,quarter) generatesoundnotes(C,quarter)];

righthand =[firstrightmeasures secondrightmeasures thirdrightmeasures fourthrightmeasures firstrightmeasures secondrightmeasures thirdrightmeasures fourthrightmeasures firstleftmeasures secondleftmeasures thirdleftmeasures fourthleftmeasures firstleftmeasures secondleftmeasures thirdleftmeasures fourthleftmeasures];
%lefthand = [firstleftmeasures secondleftmeasures thirdleftmeasures fourthleftmeasures firstleftmeasures secondleftmeasures thirdleftmeasures fourthleftmeasures];
soundsc(righthand,fs);
%soundsc(lefthand, fs);


%plotting the graph
song = righthand;
songnorm = song/max(song);
filename = 'Arizie_Twinkle_composed.wav';
audiowrite(filename, songnorm, fs);
info = audioinfo('Arizie_SongTitle.wav');
t = 0:seconds(1/fs):seconds(info.Duration);
t = t(1:end-1);
plot(t, songnorm);
xlabel('Time')
ylabel('Audio Signal')
