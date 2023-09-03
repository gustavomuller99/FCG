# FCG - Trabalho Final - Gabriel Viecili Pillonetto e Gustavo Ivan Muller

# Descrição
- Pacman com modo de câmera livre para desenvolvimento e modo jogo. O objetivo do jogo é comer a quantidade máxima de maçãs sem colidir contra: 1. fantasmas, 2. obejtos do mapa e 3. limites do mapa.


### Objetos virtuais representados através de malhas poligonais complexas
- Objetos importados como paredes, fantasmas e itens possuem malhas poligonais complexas.

![image](https://github.com/gustavomuller99/FCG/assets/64417029/75e25e82-2a78-424b-9a5d-839907fc9179)
*Exemplo de assets utilizados*


### Transformações geométricas de objetos virtuais
- Quase todos os objetos passaram por transformações geométricas ao decorrer do jogo.
- 1. Pacman sofre rotação de câmera e movimentação da boca (Gustavo).
- 2. Maçã é movimentada ao longo de um espaço curvo com Curvas de Bézier (Gabriel).
- 3. Maçãs recebem nova posição aleatória ao serem comidas (Gabriel). 
- 4. Fantasmas são movimentados ao longo de um espaço retilíneo (Gabriel).


### Controle de câmeras virtuais. 
- Uma câmera livre no modo de desenvolvimento e uma câmera look-at durante o modo de jogo (Gustavo).

![image](https://github.com/gustavomuller99/FCG/assets/64417029/6f3a1608-73f8-4b46-8cf9-71f6c28d27d6)
*Câmera livre*

![image](https://github.com/gustavomuller99/FCG/assets/64417029/e546b830-2d23-4301-8c0a-40772568335c)
*Câmera de jogo*


### No mínimo um objeto virtual deve ser copiado com duas ou mais instâncias
- Múltiplas instâncias para objetos no mapa: Cubos, fantasmas, maçãs, paredes (feito por ambos da dupla).


### Testes de intersecção entre objetos virtuais. 
- Intersecção entre pacman (esfera) e os elementos no mapa: fantasmas (cubos), obstáculos (cubos), maçãs (esferas) e paredes do mapa (movimento do pacman é um ponto futuro e bordas são definidas como um retângulo) (Gabriel).


### Modelos de iluminação de objetos geométricos. 
- Lambert em objetos como paredes, piso e cubos (feito por ambos da dupla).
- Blinn-Phong nas maçãs, fantasmas e pacman (Gabriel).
- Avaliação de iluminação de Gouraud nos cubos (obstáculos) (Gustavo).
- Avaliação de iluminação de Phong nos demais objetos (Gustavo).

![image](https://github.com/gustavomuller99/FCG/assets/64417029/e2975f51-d0b5-4ed3-8e34-614026ad206a)
*Exemplo de iluminação Blinn-Phong*


### Mapeamento de texturas.
- Todos os elementos são definidos com texturas que se encontram no diretório /data (feito por ambos da dupla).


### Curvas de Bézier. 
- Definidas por 4 pontos de controle e utilizadas para definir o deslocamento das maçãs (Gabriel).


-----

### Contribuições da dupla.
- Estrutura de arquivos/classes do projeto **(GUSTAVO)**
- Definição e animações do personagem Pacman **(GUSTAVO)**
- Definição de estados do jogo (câmeras, textos, atalhos) **(GUSTAVO)**
- Interpolação com modelo de Gouraud e Phong **(GUSTAVO)**
- Layout e animações de paredes, maçãs, obstáculos, fantasmas **(GABRIEL)**
- Implementação de curvas de Bézier **(GABRIEL)**
- Modelo de iluminação de Blinn-Phong **(GABRIEL)**
- Definição e implementação de colisões **(GABRIEL)**
  

### Utilização de Inteligência Artificial para desenvolvimento.
- Não foram utilizadas ferramentas de IA para desenvolver o trabalho.
  

### Teclas de Atalho.
- Para alternar entre o modo de câmera livre e a câmera look-at, pressione **M**
- Para reiniciar o jogo após uma colisão, pressione **R**
- Para movimentação lateral do personagem, utilize **A** e **D**
- Para movimentação da câmera livre, utlilize **WASD**

### Instruções de compilação.
- Utilização das opções de linker 'lib\libglfw3.a -lgdi32 -lopengl32'
- Utilização do padrão C++ 14



