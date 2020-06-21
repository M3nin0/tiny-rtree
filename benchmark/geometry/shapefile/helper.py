import geopandas as gpd


def brazilianuf_to_cxx(gdf: gpd.GeoDataFrame):
    """Função para auxiliar a criação do arquivo cpp com os dados de municípios do Brasil
    """
    res = []
    for geom in gdf.geometry:
        b = geom.bounds
        res.append(
            f'rTree.insert(new Rectangle{b[0], b[2], b[1], b[3]});'    
        )
    return res


if __name__ == '__main__':
    brazilianuf = gpd.read_file('BRMUE250GC_SIR.shp')
    
    print("Gerando arquivo cxx")
    with open('BRMUE250GC_SIR.cxx', 'w') as file:
        file.write("\n".join(brazilianuf_to_cxx(brazilianuf)))
    print("Arquivo gerado com sucesso!")
