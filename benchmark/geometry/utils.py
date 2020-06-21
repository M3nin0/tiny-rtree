#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
from shapely.geometry import box


def to_xy(bbox):
    """Função para gerar as coordenadas (x, y) de um Bounding Box
    """
    return bbox.exterior.xy

def bbox(coords):
    """Transforma as coordenadas x, y de um Bounding Box em um conjunto
    de pontos pronto para visualização
    """
    return to_xy(box(float(coords[0]),
                     float(coords[2]),
                     float(coords[1]),
                     float(coords[3])))
