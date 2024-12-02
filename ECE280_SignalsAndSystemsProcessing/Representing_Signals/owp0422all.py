import numpy as np 

# Unit step function
u = lambda t: (t > 0) * 1.0

def x_a(t):
    # Create the rectangular pulse using unit step functions
    u = lambda t: (t>0)*1.0
    rect = lambda t: np.where(np.abs(t) < 3, 1.0, 0.0)
    sgn_t_3 = (2 * u(t - 3)) - 1
    result = -1* rect(t)* sgn_t_3 * np.exp(1j * 2 * np.pi * t)
    
    return result

# Function x_b(t): returns 
# b has impulses - not done

# Function x_c(t): 1/pi * (sin(t-3)/(t-3)) + (cos(t-3)-1)/(t-3)**2
def x_c(t):
    return (1 / np.pi) * (np.sin(t - 3) / (t - 3) + (np.cos(t - 3) - 1) / (t - 3)**2)

# Function x_b(t): j*2*(1/pi)*sin(t) + 3*(1/pi)*cos(2*pi*t)
def x_d(t):
    return 1j * 2 * (1 / np.pi) * np.sin(t) + 3 * (1 / np.pi) * np.cos(2 * np.pi * t)


# Function x_e(t): np.cos(3*t)/(1j*np.pi*t) + (np.sin(t) - np.sin(2*t))/(1j*np.pi*t**2)
def x_e(t):
    return np.cos(3 * t) / (1j * np.pi * t) + (np.sin(t) - np.sin(2 * t)) / (1j * np.pi * t**2)

