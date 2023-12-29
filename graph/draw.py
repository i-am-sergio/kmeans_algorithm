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


draw_clusters_result('/home/neodev/Develop/kmeans_algorithm/build/cluster.csv','clusters_x.png')