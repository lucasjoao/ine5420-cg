# Atividade

## Entrega 3 (11/04)

* Acrescente ao seu Sistema Gráfico Interativo a capacidade de realizar rotações na Window. Para tal:

  * Altere a representação dos objetos do mundo para suportar representação em um dos sistemas de coordenadas vistos em aula: Sistema de Coordenadas Normalizado (SCN) ou o Sistema de Coordenadas do Plano de Projeção (PPC). Agora a transformada de viewport é feita com estas coordenadas novas.
  * Atualize a translação e o zoom da window tendo em vista o novo sistema de coordenadas. A translação em particular deve levar em conta sempre o "para cima" do ponto de vista do usuário.
  * Implemente a rotação implementando o algoritmo para gerar a descrição no sistema de coordenadas escolhido.
  * Atualize a interface da aplicação para que o usuário possa rotacionar a window também. Como a rotação é sempre ao redor do centro da window, basta um campo para colocar o ângulo de rotação.

  OBS: Cuidado para não "quebrar" as funcionalidades que já existiam! Por exemplo, o que acontece com uma translação de um objeto quando a window está rotacionada em um ângulo qualquer? Em geral, o que deve ocorrer com a inclusão de um novo objeto quando a window se encontra fora de sua orientação padrão?

* REQUISITOS ADICIONAIS:

  * O código entregue com este trabalho deve ser capaz de ler/escrever um mundo em formato Wavefront .obj file, devendo inluir todas as rotinas para leitura/escrita de arquivos .obj.

  Sugestões de Modelagem:

  * Crie uma classe DescritorOBJ capaz de transcrever um objeto gráfico para o formato .obj, tomando seu nome, seu tipo, seus vértices e suas arestas.
  * Chame o descritor para cada objeto de seu mundo.
  * Assim você só precisa se preocupar com o cabeçalho do .obj. O resto de se resove através de um percurso do display file com seu descritor.

## Correções e Erros

* Não é possivel ler os nomes dos objetos da tela (gtk_entry)
  * Solucao provisória: gerar nomes automáticos
* Separar GUI do Controlador (impressao objetos)
