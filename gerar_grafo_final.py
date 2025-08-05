import sys
import matplotlib.pyplot as plt
import networkx as nx

file_name = sys.argv[1]

with open(file_name, "r") as f:
    linhas = f.readlines()

n = int(linhas[0].strip())
matriz = [list(map(int, l.split())) for l in linhas[1:]]

G = nx.Graph()
for i in range(n):
    G.add_node(f"Civ {i+1}")

for i in range(n):
    for j in range(i+1, n):
        if matriz[i][j] != 0:
            cor = 'green' if matriz[i][j] > 0 else 'red'
            G.add_edge(f"Civ {i+1}", f"Civ {j+1}", label=matriz[i][j], color=cor)

pos = nx.spring_layout(G, seed=42)
colors = [G[u][v]['color'] for u,v in G.edges()]
labels = nx.get_edge_attributes(G, 'label')

plt.figure(figsize=(6,6))
nx.draw(G, pos, with_labels=True, node_size=1500, node_color='white',
        font_weight='bold', edge_color=colors, width=2)
nx.draw_networkx_edge_labels(G, pos, edge_labels=labels, font_size=10)

plt.axis('off')
plt.title("Final Relations Graph", fontsize=14, fontweight='bold')
plt.savefig("graph_final.png")
print("\nGraph saved as graph_final.png")
