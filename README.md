# FCG

# Descrição
- Pacman com modo de câmera livre para desenvolvimento e modo jogo. O objetivo do jogo é comer a quantidade máxima de maçãs sem colidir contra: 1. fantasmas, 2. obejtos do mapa e 3. limites do mapa.


### Objetos virtuais representados através de malhas poligonais complexas
- Objetos importados como paredes, fantasmas e itens possuem malhas poligonais complexas.


### Transformações geométricas de objetos virtuais
- Quase todos os objetos passaram por transformações geométricas ao decorrer do jogo.
- 1. Pacman sofre rotação de câmera e movimentação da boca.
- 2. Maçã é movimentada ao longo de um espaço curvo com Curvas de Bézier.
- 3. Maçãs recebem nova posição aleatória ao serem comidas. 
- 4. Fantasmas são movimentados ao longo de um espaço retilíneo.


### Controle de câmeras virtuais. 
- Uma câmera livre no modo de desenvolvimento e uma câmera look-at durante o modo de jogo.


### No mínimo um objeto virtual deve ser copiado com duas ou mais instâncias
- Múltiplas instâncias para objetos no mapa: Cubos, fantasmas, maçãs, paredes.


### Testes de intersecção entre objetos virtuais. 
- Intersecção entre pacman (esfera) e os elementos no mapa: fantasmas (cubos), obstáculos (cubos), maçãs (esferas) e paredes do mapa (movimento do pacman é um ponto futuro e bordas são definidas como um retângulo).


### Modelos de iluminação de objetos geométricos. 
- Lambert em objetos como paredes, piso e cubos.
- Blinn-Phong nas maçãs, fantasmas e pacman.
- Avaliação de iluminação de Gouraud nos cubos (obstáculos).
- Avaliação de iluminação de Phong nos demais objetos.


### Mapeamento de texturas.
- Todos os elementos são definidos com texturas que se encontram no diretório /data.


### Curvas de Bézier. 
- Definidas por 4 pontos de controle e utilizadas para definir o deslocamento das maçãs.


