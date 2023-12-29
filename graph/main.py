import matplotlib.pyplot as plt
import numpy as np

def leer_csv_centroides(nombre_archivo :str) -> tuple | None:
    try:
        with open(nombre_archivo, 'r') as archivo:
            # Leer la primera línea: número de centroides
            num_centroides = int(archivo.readline().strip())
            # Leer la segunda línea: tamaños de los clústeres
            sizes_clusters = list(map(int, archivo.readline().strip().split(',')))
            # Leer las posiciones de los centroides
            posiciones_centroides = []
            for _ in range(num_centroides):
                linea = archivo.readline().strip().split(',')
                x, y = map(float, linea)
                posiciones_centroides.append([x, y])

            clusteres = []
            for size in sizes_clusters:
                cluster = []
                for _ in range(size):
                    linea = archivo.readline().strip().split(',')
                    x, y = map(float, linea)
                    cluster.append([x, y])
                clusteres.append(cluster)

        return num_centroides, sizes_clusters, posiciones_centroides, clusteres

    except Exception as e:
        print(f"Error al leer el archivo CSV: {e}")
        return None


def draw_clusters(posiciones_centroides, clusteres, graph_name):
    # Dibujar los puntos de cada clúster
    for cluster in clusteres:
        x = [punto[0] for punto in cluster]
        y = [punto[1] for punto in cluster]
        plt.scatter(x, y, s=20)
    # Dibujar los centroides
    for x, y in posiciones_centroides:
        plt.scatter(x, y, marker='+', color='black', s=50)
    plt.title("Clusters")
    plt.savefig(graph_name)
    plt.show()


def extract_data_from_csv(nombre_archivo):
    resultado = leer_csv_centroides(nombre_archivo)
    num_centroides, sizes_clusters, posiciones_centroides, clusteres = resultado
    return num_centroides, sizes_clusters, posiciones_centroides, clusteres

def draw_clusters_result(file_name,graph_name):
    num_centroides, sizes_clusters, posiciones_centroides, clusteres = extract_data_from_csv(file_name)
    print("Número de centroides:", num_centroides)
    print("Tamaños de los clústeres:", sizes_clusters)
    draw_clusters(posiciones_centroides, clusteres, graph_name)


draw_clusters_result('clusters1.csv','clusters_75.png')

# draw_clusters_result('clusters2.csv','clusters_3.png')
# draw_clusters_result('clusters3.csv','clusters_15.png')
# draw_clusters_result('clusters4.csv','clusters_50.png')


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
