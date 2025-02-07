# to visualize graph using matplotlib in WINDOWS
#   pip install matplotlib
import matplotlib.pyplot as plt 
import scipy
# to save graph in json file in WINDOWS:
#   pip install networkx
import networkx as nx

import json 
from typing import List, Dict
from shortest_path import build_adjacency_list, load_graph

def CalcScale(adjacency_list: Dict[str, List[str]]) -> List[int]:
    node_sizes = []
    for node in adjacency_list:
        node_sizes.append(len(adjacency_list[node]))
    return node_sizes




if __name__ == '__main__':

    # Загрузка графа из JSON файла
    # with open("F:\\PROGRAMMING\\SCHOOL21-BASE\\SCHOOL21_projects\\Python\\Python_Bootcamp.Team_00-1\\src\\wiki.json", 'r') as f:
    #     graph_data = json.load(f)
    graph_data = load_graph()
    adj_list = build_adjacency_list(graph_data, True)

    # Преобразование данных обратно в граф
    G = nx.node_link_graph(graph_data, edges="edges")

    # Визуализация графа
    plt.figure(figsize=(8, 8))  # Размер графика
    pos = nx.spring_layout(G)  # Расположение узлов (можно выбрать другой алгоритм)
    pos = nx.kamada_kawai_layout(G)

    # Отрисовка графа
    # adjacency_list = LoadGraph("F:\\PROGRAMMING\\SCHOOL21-BASE\\SCHOOL21_projects\\Python\\Python_Bootcamp.Team_00-1\\src\\wiki.json")
    # print()
    # for i in adjacency_list:
    #     print(i, adjacency_list[i])
    # print()

    scale = CalcScale(adj_list) 
    node_sizes = []
    for i in scale:
        node_sizes.append(i*100)
    # print(node_sizes)

    font_sizes = {}
    for n,i in zip(G.nodes, scale):
        font_sizes[n] = i * 6
    # print(font_sizes)

    # Отрисовка узлов и ребер
    nx.draw_networkx_nodes(G, pos, node_size=node_sizes, node_color="lightblue")
    nx.draw_networkx_edges(G, pos, width=1.0, edge_color="gray")    
    node_labels = {node: node for node in G.nodes}
    nx.draw_networkx_labels(G, pos, labels=node_labels, font_size=font_sizes)

    # Отображение графика
    plt.title("Визуализация графа")
    plt.show()