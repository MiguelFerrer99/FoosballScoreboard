/* Librerías para manejar el display LCD y la interfaz I2C */
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

/* Instancias displays de cada equipo (DIRECCIÓN, PIN E, PIN RW, PIN RS, PIN D4, PIN D5, PIN D6, PIN D7) */
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7);  
LiquidCrystal_I2C lcd2(0x27,2,1,0,4,5,6,7);

/* Constantes para los pines de cada equipo */
const byte pin_equipo_uno = 7;
const byte pin_equipo_dos = 6;

/* Variables para detectar si hay un obstaculo en el sensor o no */
int hayObstaculo_uno;
int hayObstaculo_dos;

/* Nombres equipos */
String equipo_uno;
String equipo_dos;

/* Abreviatura de los nombres de los equipos */
String abreviatura_uno;
String abreviatura_dos;

/* Numero de goles de cada equipo */
int goles_equipo_uno;
int goles_equipo_dos;

/* Numero de bolas restantes del partido */
int bolas_restantes;

/* FUNCIÓN SETUP (solo se ejecuta la 1a vez) */
void setup()
{
  lcd.setBacklightPin(3,POSITIVE);          // Establecemos el PIN del backLight del display 1
  lcd.setBacklight(HIGH);                   // Encendemos la iluminación posterior backlight del display 1
  lcd.begin(16,2);                          // Indicamos que el display 1 tiene 16 columnas y 2 filas
  lcd.clear();                              // Limpiamos pantalla del display 1
  
  lcd2.setBacklightPin(3,POSITIVE);         // Establecemos el PIN del backLight del display 2
  lcd2.setBacklight(HIGH);                  // Encendemos la iluminación posterior backlight del display 2
  lcd2.begin(16,2);                         // Indicamos que el display 2 tiene 16 columnas y 2 filas
  lcd2.clear();                             // Limpiamos pantalla del display 2
  
  Serial.begin(9600);                       // Iniciamos el monitor serial (9600 para carácteres leíbles)

  /* INICIALIZAMOS VARIABLES DECLARADAS ANTERIORMENTE */
  hayObstaculo_uno = HIGH;
  hayObstaculo_dos = HIGH;

  equipo_uno = "Equipo 1";
  equipo_dos = "Equipo 2";

  abreviatura_uno = "EQ1";
  abreviatura_dos = "EQ2";

  goles_equipo_uno = 0;
  goles_equipo_dos = 0;

  bolas_restantes = 9;
}

/* FUNCIÓN LOOP (se ejecuta siempre repetidamente después del setup) */
void loop()
{
  /* LEEMOS EL PIN DE CADA EQUIPO PARA SABER SI HAY UN OBSTACULO EN EL SENSOR O NO */
  hayObstaculo_uno = digitalRead(pin_equipo_uno);
  hayObstaculo_dos = digitalRead(pin_equipo_dos);

  /* CASO 1: QUEDAN BOLAS DE LA PARTIDA POR JUGAR */
  if (bolas_restantes > 0)
  {
    /* IMPRIMIMOS EL MARCADOR GENERAL EN EL DISPLAY 1 */
    lcd.setCursor(4,0);                
    lcd.print("MARCADOR");
    lcd.setCursor(1,1);                
    lcd.print(abreviatura_uno+":"+goles_equipo_uno+" - "+goles_equipo_dos+":"+abreviatura_dos);

    /* IMPRIMIMOS EL MARCADOR GENERAL EN EL DISPLAY 1 */
    lcd2.setCursor(4,0);                
    lcd2.print("MARCADOR");
    lcd2.setCursor(1,1);                
    lcd2.print(abreviatura_uno+":"+goles_equipo_uno+" - "+goles_equipo_dos+":"+abreviatura_dos);

    /* CASO 1.1: HAY UN OBSTACULO EN EL SENSOR DEL EQUIPO 1, LO CUAL SIGNIFICA QUE HA MARCADO GOL EL EQUIPO 2 */
    if (hayObstaculo_uno == LOW)
    {
      goles_equipo_uno++;                     // Se suma 1 gol al equipo 1
      bolas_restantes--;                      // Se resta 1 bola a las bolas del partido
      
      lcd.clear();                            // Limpiamos el display 1
      lcd2.clear();                           // Limpiamos el display 2

      /* Imprimimos el texto "Ha marcado el + equipo_uno" por el display 1 */
      lcd.setCursor(0,0);                
      lcd.print("Ha marcado el");
      lcd.setCursor(2,1);                
      lcd.print(equipo_uno);

      /* Imprimimos el texto "Ha marcado el + equipo_uno" por el display 2 */
      lcd2.setCursor(0,0);                
      lcd2.print("Ha marcado el");
      lcd2.setCursor(2,1);                
      lcd2.print(equipo_uno);

      /* ESPERAMOS 3 SEGUNDOS DESPUÉS DE CUALQUIER GOL */
      delay(3000);

      /* LIMPIAMOS LOS DISPLAYS 1 Y 2 */
      lcd.clear();
      lcd2.clear();
      
    }
    /* CASO 1.2: HAY UN OBSTACULO EN EL SENSOR DEL EQUIPO 2, LO CUAL SIGNIFICA QUE HA MARCADO GOL EL EQUIPO 1 */
    else if (hayObstaculo_dos == LOW)
    {
      goles_equipo_dos++;                     // Se suma 1 gol al equipo 1
      bolas_restantes--;                      // Se resta 1 bola a las bolas del partido
      
      lcd.clear();                            // Limpiamos el display 1
      lcd2.clear();                           // Limpiamos el display 2

      /* Imprimimos el texto "Ha marcado el + equipo_dos" por el display 1 */
      lcd.setCursor(0,0);                
      lcd.print("Ha marcado el");
      lcd.setCursor(2,1);                
      lcd.print(equipo_dos);

      /* Imprimimos el texto "Ha marcado el + equipo_dos" por el display 2 */
      lcd2.setCursor(0,0);                
      lcd2.print("Ha marcado el");
      lcd2.setCursor(2,1);                
      lcd2.print(equipo_dos);

      /* ESPERAMOS 3 SEGUNDOS DESPUÉS DE CUALQUIER GOL */
      delay(3000);

      /* LIMPIAMOS LOS DISPLAYS 1 Y 2 */
      lcd.clear();
      lcd2.clear(); 
    }
    
  }
  /* CASO 2: YA NO QUEDAN BOLAS DE LA PARTIDA POR JUGAR, FINAL DE LA PARTIDA */
  else
  {
    /* EL GANADOR SERÁ IGUAL AL EQUIPO QUE CON MAYOR NÚMERO DE GOLES */
    String ganador = goles_equipo_uno > goles_equipo_dos ? equipo_uno : equipo_dos;

    /* IMPRIMIMOS EN EL DISPLAY 1 EL GANADOR */
    lcd.setCursor(4,0);                
    lcd.print("GANADOR:");
    lcd.setCursor(4,1);                
    lcd.print(ganador);

    /* IMPRIMIMOS EN EL DISPLAY 2 EL GANADOR */
    lcd2.setCursor(4,0);                
    lcd2.print("GANADOR:");
    lcd2.setCursor(4,1);                
    lcd2.print(ganador);

    /* DEJAMOS 10 SEGUNDOS DE SEPARACIÓN ENTRE EL FINAL DE UNA PARTIDA Y EL COMIENZO DE OTRA */
    delay(10000);

    /* LLAMAMOS A LA FUNCIÓN SETUP() PARA EMPEZAR OTRA PARTIDA */
    setup();
  }
}
