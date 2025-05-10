import networkx as nx
import pylab 
import numpy as np

def find_least_turn(pathlist):
    minturns = 0x3f3f3f3f
    for p in pathlist:
        turns = 0
        l = len(p)
        for i in range(l-2):
            if p[i]-p[i+1]!=p[i+1]-p[i+2]:
                turns+=1
        if turns < minturns:
            min_path = p
            minturns = turns
        print(p)
        print(turns)
    return min_path


if __name__ == "main":
    colors = ['black','white','blue','green','yellow']
    with open('field.txt', "r") as f:
        tiles = f.readline()

    G = nx.Graph()
    for i in range(0, 81):
        G.add_node(i, desc =str(i))
    for target in range(0, 81):
        up = target - 9;
        down = target + 9;
        left = target - 1;
        right = target + 1;
        if tiles[target] == '4':
            start = target
        if tiles[target] == '2':
            treasure = target
        if tiles[target] == '3':
            destination = target    
        if up >= 0:
            if tiles[up] == '0' or tiles[target] == '0':
                G.add_weighted_edges_from([(target,up,1000)],"weight")
            else:
                G.add_weighted_edges_from([(target,up,1)],"weight")
        if down < 81:
            if tiles[down]=='0'or tiles[target] == '0':
                G.add_weighted_edges_from([(target,down,1000)],"weight")
            else:
                G.add_weighted_edges_from([(target,down,1)],"weight")
        if left >= 0 and left // 9 == target // 9:
            if tiles[left]=='0'or tiles[target] == '0':
                G.add_weighted_edges_from([(target,left,1000)],"weight")
            else:
                G.add_weighted_edges_from([(target,left,1)],"weight")
        if right < 81 and right % 9 == target % 9:
            if tiles[right]=='0'or tiles[target] == '0':
                G.add_weighted_edges_from([(target,right,1000)],"weight")
            else:
                G.add_weighted_edges_from([(target,right,1)],"weight")
    pos=nx.shell_layout(G)
    pos = {}
    for i in range(0, 81):
        pos[i] = [i%9, 8-i//9]



    elarge=[(u,v) for (u,v,d) in G.edges(data=True) if d['weight'] >1]
    esmall=[(u,v) for (u,v,d) in G.edges(data=True) if d['weight'] <=1]

    find_treasure=nx.dijkstra_path(G,source=start,target=treasure)
    print(find_treasure)
    pathes = [p for p in nx.all_shortest_paths(G, source=start, target=treasure)]

    print(pathes)
    treasure_edge = []
    for i in range(len(find_treasure)-1):
        treasure_edge.append((find_treasure[i],find_treasure[i+1]))
    find_exit=nx.dijkstra_path(G,source=treasure,target=destination)
    pathes = [p for p in nx.all_shortest_paths(G, source=treasure, target=destination, weight="weight")]
    find_exit = find_least_turn(pathes)
    print(pathes)
    exit_edge = []
    for i in range(len(find_exit)-1):
        exit_edge.append((find_exit[i],find_exit[i+1]))
    print(find_exit)
    nx.draw_networkx_nodes(G,pos,node_size = 50,node_color = [colors[int(n)] for n in tiles])
    nx.draw_networkx_labels(G,pos,labels = nx.get_node_attributes(G, 'desc'))
    nx.draw_networkx_edges(G,pos,edgelist = treasure_edge, width = 5, edge_color = 'red', alpha = 0.25)
    nx.draw_networkx_edges(G,pos,edgelist = exit_edge, width = 5, edge_color = 'red', alpha = 0.25)

    # nx.draw_networkx_edges(G,pos,edgelist=elarge,
    #                     width=6)
    # nx.draw_networkx_edges(G,pos,edgelist=esmall,
    #                     width=6,alpha=0.5,edge_color='b',style='dashed')


    pylab.title('Field',fontsize=15)
    pylab.show()

