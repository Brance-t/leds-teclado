
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL02Z4.h"
#include "fsl_debug_console.h"


#include "sdk_hal_uart0.h"

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
/*
 * @brief   Application entry point.
 */


void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 10000000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}



int main(void) {

	/* Define the init structure for the output LED pin*/
			    gpio_pin_config_t led_config = {
			        kGPIO_DigitalOutput, 0,
			    };


  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

 PRINTF("Usar teclado para controlar LEDs\r\n");
    PRINTF("r-R led ROJO\r\n");
    PRINTF("v-V led VERDE\r\n");
    PRINTF("a-A led AZUL\r\n");
    PRINTF("M buscar acelerometro\r\n");

 (void)uart0Inicializar(115200);


    /* Init output LED GPIO. */
            //Configura LED ROJO (PTB6) como salida
            GPIO_PinInit(GPIOB, 6U, &led_config);

            //Configura LED VERDE (PTB7) como salida
            GPIO_PinInit(GPIOB, 7U, &led_config);

            //Configura LED AZUL (PTB10) como salida
            GPIO_PinInit(GPIOB, 10U, &led_config);




            //Sacar 1 por pin LED AZUL (apaga)
                	 GPIO_PortSet(GPIOB, 1u << BOARD_LED_BLUE_GPIO_PIN);

                	 //Sacar 1 por pin LED VERDE (apaga)
                	 GPIO_PortSet(GPIOB, 1u << BOARD_LED_GREEN_GPIO_PIN);

                	 //Sacar 1 por pin LED ROJO (apaga)
                	 GPIO_PortSet(GPIOB, 1u << BOARD_LED_RED_GPIO_PIN);



    while(1) {
    	status_t status;
    	uint8_t nuevo_byte;

    	if(uart0NuevosDatosEnBuffer()>0){
    		status=uart0LeerByteDesdeBufferCircular(&nuevo_byte);

    		if(status==kStatus_Success){


    			if(nuevo_byte=='A'){
    				//Sacar 0 por pin LED AZUL (enciende)
    				GPIO_PortClear(GPIOB, 1u << BOARD_LED_BLUE_GPIO_PIN);
    				printf("Azul enciende:%c\r\n",nuevo_byte);
    			}

    			if(nuevo_byte=='a'){
    				//Sacar 1 por pin LED AZUL (apaga)
    				GPIO_PortSet(GPIOB, 1u << BOARD_LED_BLUE_GPIO_PIN);
    			    printf("Azul apagado:%c\r\n",nuevo_byte);
    			}



    			if(nuevo_byte=='V'){
    				//Sacar 0 por pin LED VERDE (enciende)
    				GPIO_PortClear(GPIOB, 1u << BOARD_LED_GREEN_GPIO_PIN);
    			    printf("Verde enciende:%c\r\n",nuevo_byte);
    			}

    			if(nuevo_byte=='v'){
    				//Sacar 1 por pin LED VERDE (apaga)
    				GPIO_PortSet(GPIOB, 1u << BOARD_LED_GREEN_GPIO_PIN);
    			    printf("Verde apaga:%c\r\n",nuevo_byte);
    			}



    			if(nuevo_byte=='R'){
    				//Sacar 0 por pin LED ROJO (enciende)
    				GPIO_PortClear(GPIOB, 1u << BOARD_LED_RED_GPIO_PIN);
    			    printf("Rojo enciende:%c\r\n",nuevo_byte);
    			}

    			if(nuevo_byte=='r'){
    				//Sacar 1 por pin LED ROJO (apaga)
    				GPIO_PortSet(GPIOB, 1u << BOARD_LED_RED_GPIO_PIN);
    			    printf("Rojo apaga:%c\r\n",nuevo_byte);
    			}

}else{
    			printf("error\r\n");
    		}
    	}
    }
    return 0 ;
}
