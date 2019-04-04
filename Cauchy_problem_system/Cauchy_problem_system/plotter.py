import os
import numpy as np
import matplotlib.pyplot as plt

BORDER = 1.1
EXAMPLE = 1

if EXAMPLE == 1:
    f = [ lambda x : np.exp(x) * x * x / 2 ,
          lambda x : (x + 1) * np.exp(x) ]

def get_list_from_file():
    files = filter(lambda x : ".txt" in x, os.listdir() )
    out = list()
    print("file order")
    for x in files:
        out.append([])
        print(x)
        with open(x,'r') as f:
            for line in f:
                out[-1].append( list(map(float, line.split() ) ) )
    
    return out

def unzip(x):
    if not x:
        return [],[]        
    else:
        y = unzip(x[1:])
        return  [ x[0][0] ] + y[0]  , [x[0][1]] + y[1]
    
def draw(points,func,delta= 0.05):
    a = min(points[0])
    b = max(points[0])
    y_min = min(points[1])
    y_max = max(points[1])
    border_x = (b - a) * (BORDER - 1)
    border_y = (y_max - y_min) * (BORDER - 1)
    
    t = np.arange( a, b+delta, delta)
    a -= border_x
    b += border_x
    y_min -= border_y
    y_max += border_y
    plt.axis([a,b,y_min,y_max])
    plt.plot(t, func(t))
    plt.scatter(points[0],points[1],s=10,c='red')
    plt.grid(True)
    
def main():
    out = get_list_from_file()
    points_list = [ unzip( out[i] ) for i in range(len(out)) ]
    for i in range(len(f)):
        plt.figure()
        draw(points_list[i],f[i])
        
    plt.show()
   
if __name__ == "__main__":
    main()
