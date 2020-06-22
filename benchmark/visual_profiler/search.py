import numpy as np
import pandas as pd
from viz import plot_time


if __name__ == '__main__':
    df = pd.read_csv('../output.csv', index_col = None)

    # Visualização do tempo de busca com 51 elementos (Retângulo menor)
    # Não entra no documento, só está aqui para verificação
    dd = df[df.test_name.str.contains('retangulo_menor_search')]
    dd.index = np.arange(0, dd.shape[0])
    
    plot_time(dd, 'Tempo de recuperação de 51 elementos')
    
    # Visualização do tempo de busca com 1140 elementos (Retângulo maior)
    dd = df[df.test_name.str.contains('retangulo_maior_search')]
    dd.index = np.arange(0, dd.shape[0])
    
    plot_time(dd, 'Tempo de recuperação de 1140 elementos')

    # Visualização do tempo de busca com 500 elementos
    dd = df[df.test_name.str.contains('retangulo_sintetico_search')]
    dd.index = np.arange(0, dd.shape[0])
    
    plot_time(dd, 'Tempo de recuperação com 500 elementos')
