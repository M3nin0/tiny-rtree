import numpy as np
import pandas as pd
from viz import plot_time


if __name__ == '__main__':
    df = pd.read_csv('../output.csv', index_col = None)

    # Visualização da altura com inserção de dados reais
    dd = df[df.test_name.str.contains('insert_test_realdata')]
    dd.index = np.arange(0, dd.shape[0])
    
    plot_time(dd, 'Tempo de inserção com dados reais')
    
    # Visualização da altura com inserção de dados sintéticos
    dd = df[df.test_name.str.contains('insert_test_syntheticdata')]
    dd.index = np.arange(0, dd.shape[0])
    
    plot_time(dd, 'Tempo de inserção com dados sintéticos')
