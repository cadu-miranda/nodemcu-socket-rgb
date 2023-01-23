
# NodeMCU Websocket
## :rocket: Funcionalidades

- Cria um servidor WebSocket no microcontrolador
- Formata os dados recebidos em JSON
- Muda a intensidade de brilho de um LED RGB de acordo com os parâmetros recebidos
## :sparkles: Exemplo de Uso

1. Coloque o NodeMCU em uma protoboard e faça as conexões necessárias do LED RGB:

 - R →  GPIO 12 (D6)
 - G →  GPIO 4 (D2)
 - B →  GPIO 15 (D8)

2. Faça o upload do código utilizando o PlatformIO.
3. Abra o Serial Monitor e veja qual o IP do microcontrolador.
4. Utilizando o Insomnia, crie uma requisição de WebSocket.
5. Na URL da requisição, coloque: ```ws://{IP_DO_NODE_MCU}:8081/rgb``` e conecte-se ao microcontrolador.
6. Envie uma requisição ao microcontrolador utilizando o seguinte padrão:

```javascript
{
	"data": {
		"r": 127,
		"g": 127,
		"b": 127
	}
}

- Sendo 'r' o respectivo à intensidade da luz vermelha (0-255)
- Sendo 'g' o respectivo à intensidade da luz verde (0-255),
- Sendo 'b' o respectivo à intensidade da luz azul (0-255),

```

Com isso, você verá que a intensidade do LED mudará, respeitando os valores passados na requisição do WebSocket.