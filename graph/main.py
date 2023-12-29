import matplotlib.pyplot as plt
import numpy as np

archivo = 'ejerC.csv'  
# Leer el archivo CSV con numpy
datos = np.genfromtxt(archivo, delimiter=',')
resultados_kdtree = datos[::2]  # Seleccionar filas pares (0, 2, 4, ...)
resultados_fuerza_bruta = datos[1::2]  # Seleccionar filas impares (1, 3, 5, ...)
k = [5, 15, 25, 50, 75]
n_valores = [1000, 1150, 1300, 1450, 1600, 1750, 1900, 2050, 2200, 2400]

def graph_c(k,file_name):
    plt.plot(n_valores, resultados_kdtree[k], label='KDTree', marker='o')
    plt.plot(n_valores, resultados_fuerza_bruta[k], label='Fuerza Bruta', marker='o')
    plt.title('Comparación de Tiempos de Ejecución para KDTree y Fuerza Bruta')
    plt.xlabel('n (Número de Datos)')
    plt.ylabel('Running Time(ms)')
    plt.legend()
    plt.grid(True)
    plt.savefig(file_name)
    plt.clf()
    # plt.show()

for i in range(5):
    graph_c(i,f'EjercicioC_k{i}.png')

archivo = 'ejerD.csv'
datos = np.genfromtxt(archivo, delimiter=',')
resultados_kdtree = datos[::2]  # Seleccionar filas pares (0, 2, 4, ...)
resultados_fuerza_bruta = datos[1::2]  # Seleccionar filas impares (1, 3, 5, ...)
k = [5, 15, 25, 50, 75, 100, 125, 150, 200]
n_valores = [1000, 1450, 1900, 2400]

def graph_d(col,file_name):
    plt.plot(k, resultados_kdtree[:,col], label='KDTree', marker='o')
    plt.plot(k, resultados_fuerza_bruta[:,col], label='Fuerza Bruta', marker='o')
    plt.title('Comparación de Tiempos de Ejecución para KDTree y Fuerza Bruta')
    plt.xlabel('k (Número de clusteres)')
    plt.ylabel('Running Time(ms)')
    plt.legend()
    plt.grid(True)
    plt.savefig(file_name)
    plt.clf()
    # plt.show()

for i in range(4):
    graph_d(i,f'EjercicioD_k{i}.png')
