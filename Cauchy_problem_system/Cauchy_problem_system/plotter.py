'''
Ploating functions and set of float points
from .txt files.
Usage:
0) Istall python3.
Install lib numpy( in CMD : pip3 install numpy )
            matplotlib ( in CMD : pip3 install matplotlib )
1) Put script into dir with .txt file in it
2) Put your functions into list f ( using numpy for standart functions )
    !! .txt files must be sorted likewise f list !!
3) Start sctipt
ru
Отрисовка графиков функций и множества вещественных точек
из файлов .txt
Использование:
0) Установить python3
Установить библиотеку numpy ( в командной строке виндовс : pip3 install numpy )
Установить библиотеку matplotlib ( в командной строке виндовс : pip3 install matplotlib )
1) Вставить скрипт в папку с .txt файлами
2) Вставить функции в список f ( использовать numpy для стандартных функций )
    !! .txt файлы должны следовать в том же порядке, что и функции в списке f !!
3) Запустить скрипт
'''
import os
import numpy as np
import matplotlib.pyplot as plt

BORDER = 0.1
EXAMPLE = 1 

if EXAMPLE == 1:
    # Put your fuctions here | Вставлять функции здесь
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
    border_x = (b - a) * BORDER 
    border_y = (y_max - y_min) * BORDER
    
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
