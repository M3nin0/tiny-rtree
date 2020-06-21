## Geometrias - Shapefile

Este diretório armazena a ferramenta criada para preparar os dados de municípios do Brasil no formato consumido pelas baterias de testes

### Utilização

Para fazer a geração destes dados, é necessário ter o Python 3.6 ou superior instalado, junto a biblioteca [GeoPandas](https://geopandas.org/). Além disto, é necessário também descompactar os dados do arquivo [BRMUE250GC_SIR.tar.xz](BRMUE250GC_SIR.tar.xz).

```shell
tar -xf BRMUE250GC_SIR.tar.xz 
```

Com cada uma dessas dependências instaladas e o arquivo extraído, faça a execução do script [helper.py](helper.py), como apresentado abaixo

```shell
python helper.py
```
