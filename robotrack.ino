#define pino1MotorDireito 3
#define pino2MotorDireito 5
#define pino1MotorEsquerdo 6
#define pino2MotorEsquerdo 9
#define pinoSensorIREsquerdo A1
#define pinoSensorIRDireito A0

/**
  Classe para controlar motor DC
*/
class DCMotor {
  int spd = 255; // Velocidade: 0 ~ 255
  int pin1, pin2;

public:
  /**
    Definir pinagem do motor
  */
  void Pinout(int in1, int in2) {
    pin1 = in1;
    pin2 = in2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }

  /**
    Modificar velocidade do motor.
    Velocidade: 0 ~ 255
  */
  void Speed(int in1) {
    spd = in1;
  }

  /**
    Modificar sentido do motor para ir para frente
  */
  void Forward() {
    analogWrite(pin1, spd);
    digitalWrite(pin2, LOW);
  }

  /**
    Modificar sentido do motor para ir para trás
  */
  void Backward() {
    digitalWrite(pin1, LOW);
    analogWrite(pin2, spd);
  }

  /**
    Fazer motor parar
  */
  void Stop() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
};

DCMotor MotorDireito, MotorEsquerdo;

void setup() {
  // Motores
  MotorDireito.Pinout(pino1MotorDireito, pino2MotorDireito);
  MotorEsquerdo.Pinout(pino1MotorEsquerdo, pino2MotorEsquerdo);

  // Sensores infra-vermelho
  pinMode(pinoSensorIREsquerdo, INPUT);
  pinMode(pinoSensorIRDireito, INPUT);

  // Serial para debugger
  Serial.begin(9600);
}

void loop() {
  if(IREsquerdo() && IRDireito()){ // Se detectar na extremidade das faixas duas cores brancas
    MotorEsquerdo.Stop();
    MotorDireito.Stop();
    Serial.println("Parado!");
  }

  if(IREsquerdo() && !IRDireito()){ // Se detectar um lado preto e o outro branco
    MotorEsquerdo.Stop();
    MotorDireito.Forward();
    Serial.println("Virando para esquerda!");
  }

  if(!IREsquerdo() && IRDireito()){ // Se detectar um lado branco e o outro preto
    MotorEsquerdo.Forward();
    MotorDireito.Stop();
    Serial.println("Virando para direita!");
  }

  if(!IREsquerdo() && !IRDireito()){ // Se detectar na extremidade das faixas duas cores pretas
    MotorEsquerdo.Forward();
    MotorDireito.Forward();
    Serial.println("Indo reto!");
  }
}

/**
  Retorna verdadeiro se o sensor infra-vermelho esquerdo detectar
  a linha preta
*/
bool IREsquerdo() {
  return !(analogRead(pinoSensorIREsquerdo) < 100);
}

/**
  Retorna verdadeiro se o sensor infra-vermelho direito detectar
  a linha preta
*/
bool IRDireito() {
  return !(analogRead(pinoSensorIRDireito) < 100);
}