import matplotlib.pyplot as plt

LABEL_TEMPLATE = 'R-Tree({m}, {M})'


def plot_height(dd, title = ""):
    """Função para plotar a relação de altura de cada uma das árvores geradas
    nos testes
    """
            
    plt.figure(dpi = 300)
    plt.plot(dd.tree_height, 'k--')
    
    for i in range(dd.shape[0]):
        _data = dd.iloc[i]
        plt.plot(i, _data.tree_height, 
             marker = '^',
             label = LABEL_TEMPLATE.format(
                 m = _data.m, M = _data.M
             ))
    
    plt.xlabel("Tipo de teste")
    plt.ylabel("Altura da árvore")
    plt.title(title)
    plt.legend()
    plt.show()


def plot_time(dd, title = ""):
    """Função para plotar a relação de tempo e insert das árvores geradas
    nos testes
    """
            
    plt.figure(dpi = 300)
    plt.plot(dd.time_in_ms, 'k--')
    
    for i in range(dd.shape[0]):
        _data = dd.iloc[i]
        plt.plot(i, _data.time_in_ms, 
             marker = '^',
             label = LABEL_TEMPLATE.format(
                 m = _data.m, M = _data.M
             ))
    
    plt.xlabel("Tipo de teste")
    plt.ylabel("Tempo (ms)")
    plt.title(title)
    plt.legend()
    plt.show()
