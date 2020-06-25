<div align = "center">
    <img src="images/logo_inpe.png">
</div>

## CAP-241 - Estrutura de dados

Docente:
- Dr. Gilberto Ribeiro de Queiroz

Discentes:
- Felipe Menino Carlos (felipe.carlos@fatec.sp.gov.br)
- Natália Motta Costa Marau Pedroso (nataliammarau@gmail.com)

<hr>

Repositório para armazenar a implementação da estrutura de dados [R-Tree](https://dl.acm.org/doi/10.1145/971697.602266), trabalho proposto na disciplina de Computação Aplicada 1 do programa de pós-graduação em Computação Aplicada do Instituto Nacional de Pesquisas Espaciais.

## Requisitos

Para este projeto é considerado como **objetivo**: Projetar e implementar uma estrutura de dados do tipo R-tree dinâmica, que permita realizar operações de inserção, busca por intervalos (consultas de janela). A operação de inserção deverá utilizar umas das técnicas apresentadas em Guttman (1984)

## Organização do repositório

Abaixo, uma descrição de cada um dos diretórios do projeto

- [benchmark](benchmark): Diretório com as baterias de testes criadas para o teste e avaliação do desempenho da estrutura de dados implementada;
- [rtree](rtree): Diretório com a implementação realizada.

## Build

Como forma de tornar o código implementado consumível, foi proposto pelo professor a disponibilização do código em formato de biblioteca. Para este trabalho este processo foi feito através do uso do [CCmakeList](CmakeLists).

Para realizar o *build* do projeto em formato de biblioteca, faça a execução do script [compile.sh](compile.sh).

```shell
$ chmod +x compile.sh
$ ./compile.sh
```

> Note que o build do projeto foi criado considerando o ambiente Ubuntu 18.04. Caso seja necessário, as dependências base para o build do projeto podem ser feitas através do comando `sudo apt install build-essential`

## Visual Studio Code

Tanto a execução do código base, como os testes de desempenho foram realizados no [Visual Studio Code](https://code.visualstudio.com/). Assim, caso preferir, já estão disponíveis no repositório os arquivos de configuração do ambiente, o que faz com que, ao abrir o diretório deste projeto no VSCode, as opções de *build* e debug já serão disponibilizadas.

> Cabe lembrar que para a execução do *benchmark* no VSCode faz-se necessário que o diretório do *benchmark* seja aberto no VSCode.
