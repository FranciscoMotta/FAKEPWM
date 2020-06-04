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
#define TOPE 50 //Valor max para los 2.5 milis  
#define PISO 2 //Valor piso para los 0.5 milis


void limpiaPuertos(void); //Función para inicializar los puertos de control

void main(void) {
    int counter, variableRandonDeCuentaXD = 0; // Variables de control 
    limpiaPuertos();
    counter = 22;
FAKE:
    for (variableRandonDeCuentaXD = 0; variableRandonDeCuentaXD <= 400; variableRandonDeCuentaXD++) {
        if (variableRandonDeCuentaXD <= counter) {
            LED_PWM = 1;
        } else {
            LED_PWM = 0;
        }
        if (UP == 1 && DOWM == 0) {
            if (counter <= TOPE) {
                counter++;
            } else {
                counter = counter;
            }
SEN:
            if (UP == 1) goto SEN;
        } else {
            if (UP == 0 && DOWM == 1) {
                if (counter >= PISO) {
                    counter--;
                } else {
                    counter = counter;
                }
SEN1:
                if (DOWM == 1) goto SEN1;
            } else {
                counter = counter;
            }
        }
        __delay_us(50);
    }
    goto FAKE;
    return;
}

void limpiaPuertos(void) {
    TRISBbits.RB0 = 0; // Ponemos como salida el pin que servirá de pwm
    TRISBbits.RB1 = 1; // Ponemos en 1 el pin RB1 para que sea entrada 
    TRISBbits.RB2 = 1; // Ponemos en 1 al pin RB2 para que sea entrada 
}
