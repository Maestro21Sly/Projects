import numpy as np 

def X_a(w, a, w0):
    """
    X(jω) = (jw + a)/((jw + a)² + (w0)²)
    """
    jw = 1j * w
    return (jw + a) / ((jw + a)**2 + w0**2)

def X_b(w):
    return -12*1j*w/(w**4+16*w**2+100)

def X_c(w):
    """
    X(jω) = 2sinc(w) + sinc(w-π) + sinc(w+π)
    """
    def my_sinc(x):
        # Handle the case where x is 0
        if isinstance(x, np.ndarray):
            result = np.ones_like(x, dtype=np.float64)
            mask = x != 0
            result[mask] = np.sin(x[mask]) / x[mask]
            return result
        else:
            return 1.0 if x == 0 else np.sin(x) / x
    
    return (2 * my_sinc(w) + 
            my_sinc(w - np.pi) + 
            my_sinc(w + np.pi))

def X_d(w, a, T):
    
    return 1 / (1 -(a * np.exp(-1j*w *T)))


def X_e(w):
    """
    X(jω) = (8wj + 16)/[(jw+2)² + 16]²
    """
    return (8 * 1j * w + 16) / ((1j * w + 2)**2 + 16)**2

def X_f(w):
    return (((-3*np.pi < w) & (w < -np.pi)) *(-1j*(np.exp(-1j*w)+1)/2/np.pi) ((np.pi < w) & (w < 3*np.pi)) *(1j*(np.exp(-1j*w)+1)/2/np.pi))

def X_g(w):
    term1 = -1 / (1j * w) * np.exp(1j * w * 2)
    term2 = 1 / (1j * w)**2 * np.exp(1j * w * 1)
    term3 = -1 / (1j * w)**2 * np.exp(-1j * w * 1)
    term4 = -1 / (1j * w) * np.exp(-1j * w * 2)

    # Combine terms to get X(w)
    result = term1 + term2 + term3 + term4 
    return result

def X_i(w):
    term1 = 1 / (1j * w)
    term2 = -2 / (1j * w)**3
    term3 = (2 / (1j * w)**3) * np.exp(-1j * w)
    term4 = (2 / (1j * w)**2) * np.exp(-1j * w)

    # Combine terms to get the final result
    result = term1 + term2 + term3 + term4
    return result