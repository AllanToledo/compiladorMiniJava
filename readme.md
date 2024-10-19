# Trabalho de Compiladores II
### Allan Vitor W. Toledo
O trabalho consiste em 2 projetos, pode ser feito em qualquer linguagem. Lembre-se de adicionar um arquivo de 
documentação explicando como executar o seu projeto.

Deverá ser implementado todo o compilador para atender a gramática dada. Deverá conter o analisador léxico, sintático e 
semântico, conforme Comp 1, porém agora para uma gramática mais complexa. Pode ser utilizado tanto o analisador 
descendente, quanto o ascendente. Além disso deverá ser adicionado o tradutor para nossa linguagem de máquina 
hipotética, salvando em um arquivo de texto mesmo, ou outro formato, consistindo até aqui na parte 1 do projeto. 
Já na parte 2 deverá ser lido esse arquivo e os comandos executados conforme visto em sala (Slide e Video disponibilizado).

1 - Deverá salvar em um arquivo de texto o código objeto gerado, a 
partir de um arquivo de texto com o código do mini java de entrada

2 - Deverá ler o arquivo do código objeto e executar

### Linguagem escolhida: C++
### Para executar o projeto:
É necessário possuir o CMake instalado (https://cmake.org/download/) e o GCC.

Após instalar o cmake e o GCC, para compilar o código fonte é necessário executar o seguinte comando:
```
cmake ./
cmake --build .
```
Para compilar um programa escrito em mini-java basta:
```
./compiler nome_do_programa arquivo_compilado
```
E para executar o programa, é necessário apenas:
```
./interpreter arquivo_compilado
```

### Detalhes sobre a implementação

Variáveis existem apenas dentro do seu escopo ou em um escopo mais aninhado. Variáveis com o mesmo nome é permitido em
escopos diferentes.

lerDouble() e println(double x) fazem parte da biblioteca padrão da linguagem, por isso foram omitidas da gramática.
Funcionam como uma chamada de função qualquer.

Toda função retorna algo, por isso a cada chamada de função é alocado 1 posição na pilha de dados, caso contrário o 
retorno poderia alterar com o topo atual da pilha. 
Funções void retornam 0, entretanto o compilador não permite chamar elas dentro de expressões.
