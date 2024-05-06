# Contextualização
Os serviços de transporte por aplicativo, como o Uber, operam com base na comunicação entre cliente e servidor, onde um cliente faz a solicitação de uma corrida, que é direcionada para motoristas disponíveis na região. O presente trabalho tem por objetivo emular esse funcionamento descrito através da programação de soquetes, reduzindo o escopo a um único servidor como sendo o único motorista disponível para aceitar ou recusar as corridas.  
  
Quando o cliente solicita uma corrida, estabelece-se uma conexão TCP com o servidor central, transmitindo as coordenadas. O servidor processa essa requisição instanciando um soquete para comunicação com o cliente, calcula a distância e dá ao usuário a opção de aceitar ou recusar a corrida recebida, entregando a resposta ao cliente.  
  
Se o servidor recusar a corrida, o cliente volta ao menu inicial onde pode solicitar uma nova corrida ou sair do aplicativo. Caso o servidor aceite a corrida, a distância entre servidor e cliente reduzirá em 400 metros a cada 2 segundos, sendo que o servidor enviará essas atualizações ao cliente até que a distância seja menor ou igual a zero. No momento de chegada do motorista, o cliente será finalizado e o servidor estará apto para receber novas solicitações.  
  
# Organização dos arquivos
Inicialmente, o projeto consistirá de duas pastas e três arquivos, que são:  

* **include/**: Pasta com os arquivos de cabeçalho que contém as definições de TAD e funções utilizadas para o funcionamento do programa.
* **src/**: Pasta com os arquivos de código fonte que implementam os cabeçalhos e permitem o funcionamento da conexão.
* **.gitignore**: Arquivos a serem ignorados pelo Git ao fazer o versionamento.
* **Makefile**: Arquivo com as regras necessárias para a compilação do código fonte.
* **README.md**: Documentação simplificada em markdown do projeto.

Quando o usuário faz a compilação dos programas do cliente e do servidor, de acordo com as instruções que serão dadas na próxima subseção, surgem duas novas pastas. São elas:  
  
* **bin/**: Pasta com os binários gerados pela compilação do código fonte. Serão gerados dois arquivos: client e server, representando o programa do cliente e do servidor respectivamente.
* **obj/**: Pasta com os arquivos de objeto gerados como subproduto da compilação dos programas de cliente e servidor.

## Instruções de compilação
Para que o programa seja compilado, basta que o usuário acesse a pasta raiz do projeto e digite “`make all`”, ou apenas “`make`”, que a compilação será feita, gerando os binários na pasta “bin/”.  
  
Para que os objetos e binários sejam removidos, basta que o usuário, também na pasta raiz do projeto, digite o comando “`make clean`”, que as pastas “bin/” e “obj/” serão apagadas.  
  
# Explicação do código
Ao longo das próximas subseções, cada uma das funções utilizadas nos arquivos principais para a comunicação TCP serão explicados. Note que já existem comentários e documentação no próprio código, que podem auxiliar o leitor mais profundamente no entendimento do propósito e funcionamento de cada um.  
  
## Configurações de rede (network_config.c)
As funções implementadas nesse arquivo são:  

* **logError(...)**: Essa função é chamada quando ocorre um erro no programa. Ela exibe uma mensagem customizada junto com a causa do erro e finaliza o programa com código 1 (erro).
* **clientSocketInit(...)**: Essa função é chamada ao iniciar o cliente, recebendo uma estrutura do tipo sockaddr_storage, que funciona como uma “superclasse” para endereços do tipo IPv4 e IPv6. De acordo com a versão de IP recebida pela linha de comando, é feita uma tentativa de conversão do endereço em string para uma sequência de bytes IPv4 ou IPv6 na chamada da função inet_pton(...). Caso a conversão seja bem sucedida, a estrutura recebida é especializada através de um type casting para sockaddr_in ou sockaddr_in6 e é retornado 0 indicando sucesso. Caso uma versão de IP desconhecida seja informada, ou o endereço informado na linha de comando seja inválido, a função retorna -1 indicando falha.
* **serverSocketInit(...)**: Essa função tem o mesmo objetivo da anterior, executando inclusive passos muito parecidos. Porém, ela não recebe um endereço IP por linha de comando, dessa forma o servidor pode ser acessado por qualquer endereço local disponível na máquina de hosting. Como não há endereço IP para tentar a conversão, a função se baseia apenas na versão do IP informada na linha de comando para execução do programa do servidor.
* **convertAddressToString(...)**: Essa função recebe uma estrutura do tipo sockaddr, que é uma versão base do endereço do soquete funcionando tanto para IPv4 quanto para IPv6, e converte essa estrutura para uma identificação do endereço IP em string. Para fazer essa conversão, é chamada a função inet_ntop(...), que é o oposto da inet_pton(...) usada nas funções descritas anteriormente para converter a string do IP para a estrutura. Essa função é apenas para informar os endereços e portas nas conexões entre cliente e servidor, não desempenhando papel crucial para a conexão em si.
  
## Cliente (client.c)
As funções implementadas nesse arquivo são:  
  
* **createClient(...)**: Define as coordenadas do cliente de forma fixa e chama a função clientSocketInit(...), que foi descrita na seção anterior, para inicializar as informações necessárias para o soquete do cliente.
* **printClientUsage()**: Imprime as instruções de utilização do programa do cliente.
* **parseClientArguments(...)**: Recebe os parâmetros informados na linha de comando para execução do programa do cliente e cria o TAD do cliente para uso posterior no programa.
* **printMenu()**: Imprime as opções que o cliente tem para utilização do programa.
* **handleMenuOption(...)**: Lê do terminal a opção do menu escolhida pelo usuário, chamando a função relativa ao tratamento daquela opção.
* **connectToServer(...)**: Essa função é chamada quando o usuário seleciona a opção de solicitar uma corrida. Ela cria um soquete com a função socket(...), que retorna um número inteiro como descritor do arquivo de soquete criado com base na versão do IP informado e o tipo de conexão, que pode ser SOCK_STREAM (TCP) ou SOCK_DGRAM (UDP). A conexão é feita através da função connect(...), que usa o soquete do cliente e as informações armazenadas na estrutura sockaddr_storage para se conectar ao servidor. Por fim, com a conexão confirmada, o endereço do servidor ao qual o cliente se conectou é transformado em string pela função convertAddressToString(...) anteriormente descrita e imprime essa informação na tela.
* **trackDriverLocation(...)**: Essa função recebe constantemente mensagens do servidor informando a distância atual que ele está do cliente através da função recv(...), que atribui a mensagem recebida a uma variável double, já que há um contrato estabelecido que somente será enviada a mensagem. Quando a distância recebida é menor ou igual a zero, a função para de esperar mensagens do servidor e imprime que o motorista chegou.
* **handleRideRequest(...)**: Essa função faz a chamada de connectToServer(...), que foi descrita anteriormente, enviando as coordenadas ao servidor através da função send(...), que recebe o descritor de arquivo do soquete do servidor. Após o envio, o cliente aguarda uma resposta na função recv(...), que armazena a resposta na variável rideAccepted se o servidor aceitou ou recusou a corrida. Caso o servidor tenha aceitado, a função trackDriverLocation(...) é invocada, fechando o soquete do servidor quando a última mensagem chegar.
* **handleExit()**: Função invocada quando o usuário do cliente opta por sair do aplicativo, finalizando o programa com código 0.
   
## Servidor (server.c)
As funções implementadas nesse arquivo são:  
  
* **createServer(...)**: Define as coordenadas do cliente de forma fixa na praça Raul Soares (centro de Belo Horizonte) e chama a função serverSocketInit(...), que foi descrita anteriormente, para inicializar as informações necessárias para o soquete do servidor. Logo após, o soquete do servidor é de fato criado pela função socket(...) e é invocada a função setsockopt(...) para liberar a porta ocupada pelo servidor imediatamente após ele ser encerrado.
* **printServerUsage()**: Imprime as instruções de utilização do programa do servidor.
* **parseServerArguments(...)**: Recebe os parâmetros informados na linha de comando para execução do programa do servidor e cria o TAD do servidor para uso posterior no programa.
* **printRideOptions(...)**: Função invocada quando a conexão do cliente com o servidor é estabelecida com sucesso, ela imprime a distância a ser percorrida para chegar ao cliente junto com as opções que o servidor tem relativas a corrida. Para calcular a distância é usada a função calculateHarversineDistance(...) implementada no arquivo coordinates.c, essa distância é atribuída ao objeto do servidor.
* **handleDriverOptions(...)**: Lê do terminal a opção do menu escolhida pelo usuário, chamando a função relativa ao tratamento daquela opção.
* **updateDriverDistance(...)**: Decrementa a distância entre cliente e servidor em 400 metros a cada 2 segundos, enviando a distância atualizada para o cliente através da função send(...). Quando a distância está igual ou inferior a zero, é feito um último envio para o cliente, que interpreta o valor como um indicativo que o motorista chegou.
* **handleAcceptRide(...)**: Função invocada quando o usuário decide aceitar a corrida solicitada, enviando uma mensagem de confirmação com o valor “1” para o cliente. Após isso, é invocada a função updateDriverDistance(...) para atualizar o cliente sobre a distância do motorista. Ao fim, o soquete do cliente é fechado.
* **handleRejectRide(...)**: Função invocada quando o usuário decide recusar a corrida solicitada, enviando uma mensagem de confirmação com o valor “0” para o cliente. Ao fim, o soquete do cliente é fechado.
* **setupServer(...)**: Faz a ligação (binding) do soquete do servidor ao endereço e porta que foram alocados a ele através da função bind(...). Após isso, invoca a função listen(...) para fazer o soquete do servidor de fato escutar no endereço e porta ligados a ele no passo anterior. Por fim, usa a função convertAddressToString(...) implementada em network_config.c para imprimir o endereço e porta que o servidor está usando para receber solicitações.
* **connectToClient(...)**: Função invocada para aguardar uma solicitação de conexão de algum cliente, fazendo o aceite de qualquer solicitação que seja recebida através da função accept(...), que recebe uma estrutura sockaddr_storage para armazenar as informações de endereço do cliente. O retorno da função mencionada é o descritor de arquivo do soquete do cliente, que será “-1” em caso de erro. Ao fim, o endereço do cliente é impresso na tela e o soquete é retornado.
