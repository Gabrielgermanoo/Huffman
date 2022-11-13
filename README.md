# Huffman
Algoritmo capaz de compactar e descompactar arquivos. Desenvolvido em C para a disciplina de Estrutura de Dados.

## Integrantes do grupo:

* Adonys Henrique
* Alejandro Reyes
* Gabriel Lucas
* Victor Alexandre

## Módulos do projeto

* Seminário de um algoritmo ou estrutura de dados não vista em sala
  *[Red_Black](https://github.com/Gabrielgermanoo/Huffman/blob/main/Red_Black/Árvore%20rubro-negra.pptx)
* Codificação de Huffman
  *[Compactador e Descompactador de Arquivos](https://github.com/Gabrielgermanoo/Huffman/tree/main/Implementação_Huffman)
* Contagem e plotagem de comparações entre Quick Sort e Bubble Sort
  *[Quick Sort x Bubble Sort](https://github.com/Gabrielgermanoo/Huffman/tree/main/Plotagem_e_Contagem)
 * Casos de teste Unitários
  *[Testes Unitários com CUnit](https://github.com/Gabrielgermanoo/Huffman/blob/main/Implementação_Huffman/test/test.c)

## Executando o projeto

### Huffman

Para compilar o compactador e descompactador de arquivos:

```bash
  cd implementacao_huffman
  make huff
```
Para executar:
```
(PARA COMPILAR): ./main -c [NOME_ARQUIVO_ENTRADA] [NOME_ARQUIVO_SAIDA].huffman -> necessário ser .huffman
(PARA DESCOMPILAR): ./main -d [NOME_ARQUIVO_ENTRADA].huffman [NOME_ARQUIVO_SAIDA] -> necessário ser .huffman
```

### Testes Unitários
```bash
  cd implementacao_huffman
  make test
  ./testes
```

### Contagem e Plotagem
Para compilar e executar o programa que realizará a comparação entre as estruturas:
```bash
  cd Plotagem_e_Contagem
  python plot.py
```

