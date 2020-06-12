# forma do programa: xmin, ymin, xmax, ymax
# forma do nosso projeto: double xmin, double xmax, double ymin, double ymax


def to_cxx_rectangle(tree_name: str, text: str) -> str:
    """Função para transformar o retângulo do programa rtree2.jnlp em inserções
    da árvore desenvolvida no projeto
    """
    el = text[19:-1]

    first_tuple = el[1: el.index(')')]
    second_tuple = el[el[1: ].index('(') + 2: -1]
    cords = (first_tuple + ',' + second_tuple).split(',')

    return f'{tree_name}.insert(new Rectangle({cords[0]}, {cords[2]}, {cords[1]}, {cords[3]});\n'

# Gera os resultados
with open('tree.jnlp.spec.cxx', 'w') as cxxspec:
    with open('tree.jnlp.spec', 'r') as file:
        lines = file.readlines()
        print(f'Gerada (s) {str(len(lines))} linhas')
        for line in lines:
            cxxspec.write(to_cxx_rectangle('rTree', line))
