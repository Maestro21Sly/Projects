function[A, B, X] = analysis(x);
M = length(x);
A = zeros (1, M);
B = zeros (1, M);
X = zeros (1, M);

%calculating A[k], B[k], and X[k]
for k = 0:M-1
        for m = 0:M-1
            A(k+1) = A(k+1) + x(m+1) * cos(2 * pi * k * m / 5);
            B(k+1) = B(k+1) + x(m+1) * sin(2 * pi * k * m / 5);
            X(k+1) =  X(k+1) + x(m+1) * exp(-1j * 2 * pi * k * m / 5);
        end
    end

end

x_test= [1, 5, 2, 3, 1];
[test1, test2, test3] = analysis(x_test)



    
function[x]= trig_synth(A, B);
M = length(A);
x = [];

for k = 1:M
    x_sum=0;
        for m = 1:M
            x_sum = x_sum + ((A(m) * cos(2 * pi * (k-1) * (m-1) / M)) +(B(m) * sin(2 * pi * (k-1) * (m-1) / M)));
        end
        x = [x (1/M)*x_sum];
end
end 

%second_test = trig_synth(test1, test2)

function[x] = exp_synth(X);
M = length(X);
x = [];
     
for k = 1:M
    x_sum=0;
        for m = 1:M
            x_sum = x_sum + X(m)*exp((1i*2*pi*(k-1)*(m-1)/M));
        end
        x = [x (1/M)*x_sum];
end
end 

x_back= exp_synth(test3)