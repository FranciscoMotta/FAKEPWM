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
#define TOPE 250 //Valor max para los 2.5 milis  
#define PISO 50 //Valor piso para los 0.5 milis


void limpiaPuertos(void); //Función para inicializar los puertos de control

void main(void) {
    int counter, variableRandonDeCuentaXD = 0; // Variables de control 
    limpiaPuertos();
    counter = 200;
FAKE:
    for (variableRandonDeCuentaXD = 0; variableRandonDeCuentaXD <= 2000; variableRandonDeCuentaXD++) {
        if (variableRandonDeCuentaXD <= counter) {
            LED_PWM = 1; // Encendemos el LED     
        } else {
            LED_PWM = 0; // Apagamos el LED
        }
        if (UP == 1 && DOWM == 0) { // Preguntamos por los botones de cambio
            if (counter <= TOPE) { // Ponemos el m�ximo de 2.5 ms para el servo motor
                counter++; //En el caso de que sea menor podremos aumentar la cuenta para el periodo del pwm
            } else {
                counter = counter; //En otro caso mantenemos el valor del counter
            }
SEN:
            if (UP == 1) goto SEN; // Funcion para evitar que entre ruido de conteo
        } else {
            if (UP == 0 && DOWM == 1) { //Preguntamos por la cuenta de descenso 
                if (counter >= PISO) { //En el caso de que la cuenta sea mayor o igual que el PISO para los 0,5ms
                    counter--; //Podremos decrementar la cuenta 
                } else {
                    counter = counter; //De otro caso la variable se mantiene con el valor inicial 
                }
SEN1:
                if (DOWM == 1) goto SEN1; //Funcion para evitar el ruido de conteo
            } else {
                counter = counter;
            }
        }
        __delay_us(10); //Tiempo base de 50 ms 
    }
    goto FAKE;
    return;
}

void limpiaPuertos(void) {
    TRISBbits.RB0 = 0; // Ponemos como salida el pin que servirá de pwm
    TRISBbits.RB1 = 1; // Ponemos en 1 el pin RB1 para que sea entrada 
    TRISBbits.RB2 = 1; // Ponemos en 1 al pin RB2 para que sea entrada 
}
