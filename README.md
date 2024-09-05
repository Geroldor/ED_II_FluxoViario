# Fluxo Viario
  O prefeito de Bitnópolis quer melhorar o fluxo viário em certas regiões da cidade. Para isso, ele quer alargar as ruas mais lentas daquela região, consequentemente aumentando seu fluxo. Porém, as ruas alargadas devem estar minimamente conectas.  
A cidade possui ruas, avenidas e rotatórias. Também queremos determinar trajetos na cidade. Uma possível consulta seria:  

*"Qual é o melhor (mais curto, mais rápido) trajeto entre os endereço X e Y?".*  

O resultado das consultas são textuais e pictóricas. Um exemplo de uma resposta textual poderia ser:  

*Siga na direção norte na Rua Xxxx até o cruzamento com a Rua Yyyy. Siga na
Rua Yyyy na direção sul.....*  
O resultado pictórico é mostrado no arquivo .svg produzido, evidenciando o caminho a ser percorrido. Note que são apresentados dois caminhos: o mais rápido e o mais curto.

![image](https://github.com/user-attachments/assets/82ab1ea0-ef35-4f02-972d-b2a1a7fb7651)  

Um sistema que resolve este tipo de problema é denominado Sistema de Informações Geográficas (SIG). Para a nossa finalidade, este é um sistema que contém (não exclusivamente) dados geo-referenciados, isto é, dados com algum atributo de localização espacial (uma coordenada).  
O sistema manipulará o mapa de uma cidade e algumas informações relacionadas.  
O mapa de uma cidade é, basicamente, composto por um conjunto de retângulos que representam as quadras.  

![image](https://github.com/user-attachments/assets/502a2502-12c8-46aa-b997-994acad60704)  

A cidade exemplificada acima chama-se Bitnópolis e possui 16 quadras. O sistema de endereçamento de Bitnópolis é inspirado no de nossa capital federal. Cada quadra possui 4 faces (N,S,L,O) e é identificada por um CEP alfanumérico. O número de uma casa ou estabelecimento comercial é a distância da frente da casa até uma projeção do ponto de ancoragem do retângulo que
representa a quadra (veja figura abaixo). Assim, um endereço é da forma CEP/Face/número, por exemplo, cep15/S/45. O ponto de ancoragem do retângulo é o canto sudeste da quadra.

## Entrada
### cidade
A cidade é descrita pelo arquivo **.geo**:

![image](https://github.com/user-attachments/assets/5d404daf-72d7-474e-8ab2-eceeac5790b6)  

### Sistema Viário
A entrada de dados será feita arquivo-texto (**arquivo.via**) com a descrição do sistema viário da cidade. O sistema viário da cidade é representado por um grafo direcionado.

#### Mapa Viário
O mapa viário é um grafo direcionado: os vértices representam os extremos de um segmento de rua e os arcos representam um segmento de rua e indicam o sentido do tráfego.

![image](https://github.com/user-attachments/assets/068638ba-05a2-4116-9417-91019f53bdf9)

Os vértices e os arcos possuem alguns atributos:  

![image](https://github.com/user-attachments/assets/a4aa647a-a2ee-4c3f-8af9-314f7442fe49)  

#### O Arquivo do Mapa Viário
O arquivo do mapa viário possui o seguinte formato (os campos são separados por um espaço em branco):  
![image](https://github.com/user-attachments/assets/a80a0fcb-f4ce-4524-9108-1fad3af1631d)  
Abaixo, um exemplo deste arquivo:

![image](https://github.com/user-attachments/assets/04cf48b4-161c-4597-b2a6-e4c42979e3f3)  

### Consultas
As consultas estão descritas na tabela abaixo. A maior parte das consulta indagam sobre o melhor percurso entre uma origem e um destino. A origem e o destino são referências geográficas. Referências geográficas são obtidas por meio dos comandos iniciados por @ e armazenadas nos registradores R0 .. R10. A referência geográfica armazenada num registrador pode ser utilizada em outras consultas.

![image](https://github.com/user-attachments/assets/76d06e4a-83f0-4e43-a1b0-76b76384ef8f)  
![image](https://github.com/user-attachments/assets/12bfc2ac-c3cd-415b-b307-879de1c72db5)  
![image](https://github.com/user-attachments/assets/b5f1b8b2-099e-4a26-b472-0db73c953e04)  
A Figura 3 mostra uma consulta que utiliza as operações alg e p?. Note que cada operação alg calcula a Árvore Geradora Mínima de 3 regiões diferentes da cidade. Note que as arestas da AGM são indicadas por linhas vermelhas próximas das bordas das quadras. Para facilitar a visualização neste exemplo, o início e o fim do percurso (operação p?) são indicados por hexágonos com as letras I e F. O percurso mais curto está indicado por uma linha verde e o mais rápido por uma linha amarela.

![image](https://github.com/user-attachments/assets/9ecc365e-2580-465f-b857-e532da3afdea)  

## A Implementação
As quadras devem ser armazenadas em alguma árvore balanceada que apresente um
desempenho pelo menos razoável para consultas espaciais. Execuções demoradas (mais que 1 ou 2 minutos) serão interrompidas e consideradas incorretas.
O módulo digraph.h, disponibilizado na descrição do trabalho, deve ser integralmente implementado, tal como especificado. A implementação deve usar listas de adjacência.  
A módulo prio.h também deve ser integralmente implementado, tal como especificado. Deve ser implementado como um Heap.  
Para a determinação de caminhos mínimos deve ser utilizado o algoritmo de Dijkstra. Que deverá usar a fila de prioridades do módulo prio.h e o grafo do módulo digraph.h. A busca por vértices dentro de uma região deve ser eficiente. Uma sugestão: provavelmente, também colocar os vértices do grafo numa árvore facilite consultas espaciais.  
As diversas estruturas de dados devem ser implementadas em módulos separados e bem documentados. Continua expressamente proibido declarar structs em arquivos .h.  
Para facilitar a implementação, alguns fatos podem ser considerados:  
• Existem vértices do grafo posicionado no ponto médio das intersecções de ruas.  
• Normalmente, existirão vértices no ponto médio de um segmento de rua. Isto é, o segmento de rua referente a uma face de uma quadra poderá ser, na prática, representado por duas (ou mais) arestas: (esquina1,meioquadra) e (meioquadra,esquina2). A figura abaixo ilustra onde serão posicionados os vértices extras (em lilás). Isto não altera o cálculo do percurso, apenas
facilita posicionar o início e o fim do percurso.  
![image](https://github.com/user-attachments/assets/f162a0c8-3c90-41fb-9ea0-9d5139f73f72)  
Os percursos devem ser animados. Isto é, alguma figura (retângulo, círculo, etc)2 deve transitar entre o início e o fim do percurso. A figura abaixo mostra um exemplo. Note que <path/> descreve o caminho a ser percorrido. Note o elemento <animateMotion/> dentro do elemento a ser animado (o círculo e o retângulo no nosso exemplo).

![image](https://github.com/user-attachments/assets/50df615c-375d-487f-8997-3ab1536a4a0f)  

## A Saída

O programa deverá produzir um arquivo **.svg** e um arquivo **.txt** ambos com o mesmo nome base do arquivo **.geo**.
Se o arquivo **.geo** (a01.geo, no nosso exemplo) for processado em conjunto com um arquivo **.qry** (q1.qry, no exemplo), além de a01.svg, deverá ser produzido o arquivo a01-q1.svg, contendo as quadras acrescidas aos resultados da consulta.
Também produzir um arquivo-texto (a01-q1.txt, no exemplo) contendo o resultado
textual de todas as consultas. Neste arquivo deve ser copiado em uma linha o texto da consulta e, na linha seguinte, o seu resultado.
**ATENÇÃO**: Cada módulo deve estar bem documentado. Dica: veja os arquivos .h dos módulos de implementação obrigatória e siga o modelo abaixo.

## O Programa

O nome do programa deve ser ted e aceitar até cinco parâmetros:  
*ted [-e path] -f arq.geo [-q consulta.qry] [-v arqvias.via] -o dir*  
O primeiro parâmetro (-e) indica o diretório base de entrada. É opcional. Caso não seja informado, o diretório de entrada é o diretório corrente da aplicação. O segundo parâmetro (-f ) especifica o nome do arquivo de entrada que deve ser encontrado sob o diretório informado pelo primeiro parâmetro. O terceiro parâmetro (-q) é um arquivo de consultas. O último parâmetro (-o)
indica o diretório onde os arquivos de saída (*.svg e *.txt) devem ser colocados. Note que o nome do arquivo pode ser precedido por um caminho relativo; dir e path é um caminho absoluto ou relativo (ao diretório corrente).

## O Que Entregar
Submeter no Classroom o arquivo .zip com os fontes, conforme descrito anteriormente.

### RESUMO DOS PARÂMETROS DO PROGRAMA

![image](https://github.com/user-attachments/assets/cbbf964a-b04f-4ea1-93cf-db4fa19f80dd)  
