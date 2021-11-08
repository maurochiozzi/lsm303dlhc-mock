#include <Wire.h>
#include <Arduino.h>

// --------------------------------------------------------------------------------------------- //
// Se usar em modo debug, setar como true
#define DEBUG true

union union_i16_ui8 { 
    uint8_t ui8[6];
    int16_t i16[3];
};

union_i16_ui8 magnetic_fields;

// --------------------------------------------------------------------------------------------- //
// I2C

#define LSM303DLHC_MOCK_ADD (0x1E)

// Valor da requisição. Usado para o master pedir informações específicas via I2C
uint8_t requisicao;

// --------------------------------------------------------------------------------------------- //
// Inicializacao do dispositivo
void inicializacao();
// Inicializacao da comunicação i2c
void inicializaI2C();
// Inicializacao do debug
void inicializaDebug();

// --------------------------------------------------------------------------------------------- //
// Rotina que ficará sendo executada no código
void rotina();

// --------------------------------------------------------------------------------------------- //
// I2C
// Função que será chamada quando o dispositivo for requisitado
void quandoRequisitado();
// Função que será chamada quando o dispositivo receber alguma informação
void quandoReceber(int quantitadeBytes);
// Consome a requisição (seta como 0 o valor da requisição) se ela for realizada com sucesso
void consumirRequisicao();
void escreverDoisBytesWire(int intParaEnviar);

int main(){
    inicializacao();

    while(true){
        rotina();
    }
}

void inicializacao(){
  init();
    // inicializa a comunicação I2c
    inicializaI2C();
    // Inicializa o debug, se for setado true
    inicializaDebug();

    magnetic_fields.i16[0] = 1000;
    magnetic_fields.i16[1] = 1000;
    magnetic_fields.i16[2] = 500;
}

void rotina(){
   #if DEBUG
    Serial.println("olar");
    delay(500);
   #endif
}

void inicializaI2C(){
    // Inicializações do I2C
    Wire.begin(LSM303DLHC_MOCK_ADD);
    Wire.onReceive(quandoReceber);
    Wire.onRequest(quandoRequisitado);
}

void inicializaDebug(){
    // Se setado como debug, inicializa a serial
    #if DEBUG
        Serial.begin(115200);
        Serial.println("Debugando...");
    #endif
}


void quandoReceber(int quantitadeBytes){
    if(Wire.available()){
        requisicao = Wire.read();

        #if DEBUG
            Serial.print("Requisicao recebida: ");
            Serial.println(requisicao);
        #endif
    }
}

void quandoRequisitado(){
    // Quando as requisições forem executadas com sucesso, ela é consumida depois.

    if(requisicao == 0x00){
        #if DEBUG
            Serial.print("Requisicao recebida: ");
            Serial.println(requisicao);
        #endif
        
        consumirRequisicao();     
    }else if(requisicao == 0x01){
         #if DEBUG
            Serial.print("Requisicao recebida: ");
            Serial.println(requisicao);
        #endif
        
        consumirRequisicao();     
    }else if(requisicao == 0x02){
        #if DEBUG
            Serial.print("Requisicao recebida: ");
            Serial.println(requisicao);
        #endif
       

        consumirRequisicao();
    }else if(requisicao == 0x03){
        #if DEBUG
            Serial.print("Requisicao recebida: ");
            Serial.println(requisicao);
        #endif

        escreverDoisBytesWire(magnetic_fields.i16[0]);
        escreverDoisBytesWire(magnetic_fields.i16[1]);
        escreverDoisBytesWire(magnetic_fields.i16[2]);
        

        consumirRequisicao();
    }
}


void consumirRequisicao(){
    requisicao = 0x00;
}

void escreverDoisBytesWire(int intParaEnviar){
    Wire.write((intParaEnviar >> 8) & 0xFF);
    Wire.write((intParaEnviar) & 0xFF);
}
