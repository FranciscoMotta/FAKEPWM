/*
 * File:   main.c
 * Author: HP
 *
 * Created on 3 de junio de 2020, 11:35 PM
 */


#include <xc.h>
#include "configuraciones.h"

#define _XTAL_FREQ 20000000

#define LED_PWM LATBbits.LATB0 
#define UP PORTBbits.RB1
#define DOWM PORTBbits.RB2
#define TOPE 100
#define PISO 0

void limpiaPuertos(void); //Funcion para iniciar los puertos y limparlos 

//EL PRESENTE CÓDIGO BUSCA SIMULAR EL PRINCIPIO DE FUNCIONAMIENTO DEL PWM
//LA REALIZACIÓN DEL MISMO SE HACE SIN LA IMPLEMENTACIÓN DE NINGÚN PERIFÉRICO PARA GENERAR
//LA VARIACIÓN DE ANCHO DE PULSO, PARA ELLO NOS REFERIMOS A QUE UN PWM, EN ESCENCIA, ES UN CONTADOR
//Y UN COMPARADOR 

void main(void) { // Función principal 
    int counter, variableRandonDeCuentaXD = 0; //Creamos unas variables de cuenta cualquiera
    limpiaPuertos(); //Iniciamos los puertos respectivos;
    counter = 50; //Iniciamos el valor de la variable counter
FAKE: 
    for (variableRandonDeCuentaXD = 0; variableRandonDeCuentaXD <= 100; variableRandonDeCuentaXD++) {
        if (variableRandonDeCuentaXD <= counter) {
            LED_PWM = 1;
        } else {
            LED_PWM = 0;
        }
        if (UP == 1 && DOWM == 0) {
            if (counter <= TOPE) {
                counter++;
                __delay_ms(10);
            } else {
                counter = counter;
            }
        } else {
            if (UP == 0 && DOWM == 1) {
                if (counter >= PISO) {
                    counter--;
                    __delay_ms(10);
                } else {
                    counter = counter;
                }
            } else {
                counter = counter;
            }
        }
        __delay_ms(5);
    }
    goto FAKE;
    return;
}

void limpiaPuertos(void) {
    TRISBbits.RB0 = 0; // Ponemos como salida el pin que servirá de pwm
    TRISBbits.RB1 = 1; // Ponemos en 1 el pin RB1 para que sea entrada 
    TRISBbits.RB2 = 1; // Ponemos en 1 al pin RB2 para que sea entrada 
}
