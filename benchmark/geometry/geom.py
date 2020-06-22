"""
Arquivo para a geração das geometrias utilizadas nos testes base da estrutura de dados.
"""

from utils import *

BASE_PATH = "figures"


def test_1():
    fig = plt.figure(dpi = 300)
    x, y = bbox((1, 2, 3, 5))
    plt.plot(x, y)

    x, y = bbox((3, 7, 4, 6))
    plt.plot(x, y)

    x, y = bbox((3, 9, 1, 3))
    plt.plot(x, y)

    x, y = bbox((8, 9, 6, 3.5))
    plt.plot(x, y)

    x, y = bbox((3, 7.5, 3.3, 3.9))
    plt.plot(x, y)

    x, y = bbox((1.5, 4.5, 4.7, 5.7))
    plt.plot(x, y, 'k--')
    fig.savefig(f'{BASE_PATH}/teste_1.png', dpi = fig.dpi)


def test_2():
    fig = plt.figure(dpi = 300)
    x, y = bbox((1, 2, 3, 5))
    plt.plot(x, y)

    x, y = bbox((3, 7, 4, 6))
    plt.plot(x, y)

    x, y = bbox((3, 9, 1, 3))
    plt.plot(x, y)

    x, y = bbox((8., 9., 3.5, 6.))
    plt.plot(x, y)

    x, y = bbox((3, 7.5, 3.3, 3.9))
    plt.plot(x, y)

    x, y = bbox((1.5, 4.5, 1.5, 2.9))
    plt.plot(x, y)

    x, y = bbox((2.1, 2.9, 1, 6.7))
    plt.plot(x, y)

    x, y = bbox((1., 2.9, 1.2, 5.9))
    plt.plot(x, y, 'k--')
    fig.savefig(f'{BASE_PATH}/teste_2.png', dpi = fig.dpi)


def test_3():
    fig = plt.figure(dpi = 300)
    x, y = bbox((1, 2, 3, 5))
    plt.plot(x, y)

    x, y = bbox((3, 7, 4, 6))
    plt.plot(x, y)

    x, y = bbox((3, 9, 1, 3))
    plt.plot(x, y)

    x, y = bbox((8., 9., 3.5, 6.))
    plt.plot(x, y)

    x, y = bbox((3, 7.5, 3.3, 3.9))
    plt.plot(x, y)

    x, y = bbox((1.5, 4.5, 1.5, 2.9))
    plt.plot(x, y)

    x, y = bbox((2.1, 2.9, 1, 6.7))
    plt.plot(x, y)

    x, y = bbox((4.1, 8.7, 6.2, 7.1))
    plt.plot(x, y)

    x, y = bbox((3.7, 4.8, 4.9, 7.6))
    plt.plot(x, y)

    x, y = bbox((3.4, 4.9, 5.2, 5.9))
    plt.plot(x, y, 'k--')
    fig.savefig(f'{BASE_PATH}/teste_3.png', dpi = fig.dpi)

def test_4():
    fig = plt.figure(dpi = 300)
    x, y = bbox((1, 2, 3, 5))
    plt.plot(x, y)

    x, y = bbox((3, 7, 4, 6))
    plt.plot(x, y)

    x, y = bbox((3, 9, 1, 3))
    plt.plot(x, y)

    x, y = bbox((8., 9., 3.5, 6.))
    plt.plot(x, y)

    x, y = bbox((3, 7.5, 3.3, 3.9))
    plt.plot(x, y)

    x, y = bbox((1.5, 4.5, 1.5, 2.9))
    plt.plot(x, y)

    x, y = bbox((2.1, 2.9, 1, 6.7))
    plt.plot(x, y)

    x, y = bbox((4.1, 8.7, 6.2, 7.1))
    plt.plot(x, y)

    x, y = bbox((3.7, 4.8, 4.9, 7.6))
    plt.plot(x, y)

    x, y = bbox((7.7, 8.1, 3.8, 4.5))
    plt.plot(x, y, 'k--')
    fig.savefig(f'{BASE_PATH}/teste_4.png', dpi = fig.dpi)


def test_5():
    fig = plt.figure(dpi = 300)
    x, y = bbox((1, 2, 3, 5))
    plt.plot(x, y)

    x, y = bbox((3, 7, 4, 6))
    plt.plot(x, y)

    x, y = bbox((3, 9, 1, 3))
    plt.plot(x, y)

    x, y = bbox((8., 9., 3.5, 6.))
    plt.plot(x, y)

    x, y = bbox((3, 7.5, 3.3, 3.9))
    plt.plot(x, y)

    x, y = bbox((1.5, 4.5, 1.5, 2.9))
    plt.plot(x, y)

    x, y = bbox((2.1, 2.9, 1, 6.7))
    plt.plot(x, y)

    x, y = bbox((4.1, 8.7, 6.2, 7.1))
    plt.plot(x, y)

    x, y = bbox((3.7, 4.8, 4.9, 7.6))
    plt.plot(x, y)

    x, y = bbox((2.6, 3.9, 1.7, 2.2))
    plt.plot(x, y, 'k--')
    fig.savefig(f'{BASE_PATH}/teste_5.png', dpi = fig.dpi)

def test_6():
    fig = plt.figure(dpi = 300)
    x, y = bbox((1, 2, 3, 5))
    plt.plot(x, y)

    x, y = bbox((3, 7, 4, 6))
    plt.plot(x, y)

    x, y = bbox((3, 9, 1, 3))
    plt.plot(x, y)

    x, y = bbox((8., 9., 3.5, 6.))
    plt.plot(x, y)

    x, y = bbox((3, 7.5, 3.3, 3.9))
    plt.plot(x, y)

    x, y = bbox((1.5, 4.5, 1.5, 2.9))
    plt.plot(x, y)

    x, y = bbox((2.1, 2.9, 1, 6.7))
    plt.plot(x, y)

    x, y = bbox((4.1, 8.7, 6.2, 7.1))
    plt.plot(x, y)

    x, y = bbox((3.7, 4.8, 4.9, 7.6))
    plt.plot(x, y)

    x, y = bbox((6.1, 6.9, 1.8, 6.99))
    plt.plot(x, y)

    x, y = bbox((2.9, 8.02, 4.9, 5.5))
    plt.plot(x, y, 'k--')
    fig.savefig(f'{BASE_PATH}/teste_6.png', dpi = fig.dpi)

def test_7():
    fig = plt.figure(dpi = 300)
    x, y = bbox((1, 2, 3, 5))
    plt.plot(x, y)

    x, y = bbox((3, 7, 4, 6))
    plt.plot(x, y)

    x, y = bbox((3, 9, 1, 3))
    plt.plot(x, y)

    x, y = bbox((8., 9., 3.5, 6.))
    plt.plot(x, y)

    x, y = bbox((3, 7.5, 3.3, 3.9))
    plt.plot(x, y)

    x, y = bbox((1.5, 4.5, 1.5, 2.9))
    plt.plot(x, y)

    x, y = bbox((2.1, 2.9, 1, 6.7))
    plt.plot(x, y)

    x, y = bbox((4.1, 8.7, 6.2, 7.1))
    plt.plot(x, y)

    x, y = bbox((3.7, 4.8, 4.9, 7.6))
    plt.plot(x, y)

    x, y = bbox((6.1, 6.9, 1.8, 6.99))
    plt.plot(x, y)

    x, y = bbox((3.5, 3.9, 4.1, 4.4))
    plt.plot(x, y)

    x, y = bbox((4.5, 4.9, 4.2, 4.7))
    plt.plot(x, y)

    x, y = bbox((5.3, 5.7, 3.7, 4.8))
    plt.plot(x, y)

    x, y = bbox((3.2, 9.1, 1.74, 2.7))
    plt.plot(x, y)

    x, y = bbox((6.3, 6.8, 2.2, 2.6))
    plt.plot(x, y)

    x, y = bbox((7.8, 7.9, 1.9, 5.2))
    plt.plot(x, y)

    x, y = bbox((2.1, 9.2, 2.5, 5.5))
    plt.plot(x, y, 'k--')
    fig.savefig(f'{BASE_PATH}/teste_7.png', dpi = fig.dpi)


if __name__ == "__main__":
    for test in range(1, 8):
        globals()[f"test_{test}"]()
