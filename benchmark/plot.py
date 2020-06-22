#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import numpy as np
import pandas as pd
from plotnine import *
import matplotlib.pyplot as plt

df = pd.read_csv('output.csv', index_col = None)

dd = df[df.test_name.str.contains('insert_test_realdata')]
dd.index = np.arange(0, dd.shape[0])

markers = [
    '.', 'o', 's', 'h', 'v', 'P', '*', 'd'    
]

label_template = 'R-Tree({m}, {M})'

plt.figure(dpi = 300)
plt.plot(dd.time_in_ms, 'k--')

for i in range(dd.shape[0]):
    _data = dd.iloc[i]
    plt.plot(i, _data.time_in_ms, 
             marker = markers[i],
             label = label_template.format(
                 m = _data.m, M = _data.M
             ))

plt.xlabel("Tipo de teste")
plt.ylabel("Tempo (ms)")
plt.title('Resultado de testes com dados reais')
plt.legend()
plt.show()

############### PLOT 2 (Dados sintéticos)

dd = df[df.test_name.str.contains('insert_test_syntheticdata')]
dd.index = np.arange(0, dd.shape[0])

markers = [
    '.', 'o', 's', 'h', 'v', 'P', '*', 'd'    
]

label_template = 'R-Tree({m}, {M})'

plt.figure(dpi = 300)
plt.plot(dd.time_in_ms, 'k--')

for i in range(dd.shape[0]):
    _data = dd.iloc[i]
    plt.plot(i, _data.time_in_ms, 
             marker = markers[i],
             label = label_template.format(
                 m = _data.m, M = _data.M
             ))

plt.xlabel("Tipo de teste")
plt.ylabel("Tempo (ms)")
plt.title('Resultado de testes com dados sintéticos')
plt.legend()
plt.show()

############### PLOT 3 (Busca de dados reais)

dd = df[df.test_name.str.contains('retangulo_menor_search')]
dd.index = np.arange(0, dd.shape[0])

markers = [
    '.', 'o', 's', 'h', 'v', 'P', '*', 'd'    
]

label_template = 'R-Tree({m}, {M})'

plt.figure(dpi = 300)
plt.plot(dd.time_in_ms, 'k--')

for i in range(dd.shape[0]):
    _data = dd.iloc[i]
    plt.plot(i, _data.time_in_ms, 
             marker = markers[i],
             label = label_template.format(
                 m = _data.m, M = _data.M
             ))

plt.xlabel("Tipo de teste")
plt.ylabel("Tempo (ms)")
plt.title('Resultado de testes com dados reais')
plt.legend()
plt.show()

############### PLOT 4 (Busca de dados reais)

dd = df[df.test_name.str.contains('retangulo_maior_search')]
dd.index = np.arange(0, dd.shape[0])

markers = [
    '.', 'o', 's', 'h', 'v', 'P', '*', 'd'    
]

label_template = 'R-Tree({m}, {M})'

plt.figure(dpi = 300)
plt.plot(dd.time_in_ms, 'k--')

for i in range(dd.shape[0]):
    _data = dd.iloc[i]
    plt.plot(i, _data.time_in_ms, 
             marker = markers[i],
             label = label_template.format(
                 m = _data.m, M = _data.M
             ))

plt.xlabel("Tipo de teste")
plt.ylabel("Tempo (ms)")
plt.title('Resultado de testes com dados reais')
plt.legend()
plt.show()

############### PLOT 5 (Busca de dados reais e relação de altura da árvore)
dd = df[df.test_name.str.contains('retangulo_maior_search')]
dd.index = np.arange(0, dd.shape[0])

markers = [
    '.', 'o', 's', 'h', 'v', 'P', '*', 'd'    
]

label_template = 'R-Tree({m}, {M})'

plt.figure(dpi = 300)
plt.plot(dd.tree_height, 'k--')

for i in range(dd.shape[0]):
    _data = dd.iloc[i]
    plt.plot(i, _data.tree_height, 
         marker = markers[i],
         label = label_template.format(
             m = _data.m, M = _data.M
         ))

plt.xlabel("Tipo de teste")
plt.ylabel("Altura da árvore")
plt.title('Altura das árvores geradas em cada teste')
plt.legend()
plt.show()
