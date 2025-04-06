#include <16F676.h>
#device ADC=8
#fuses INTRC_IO,NOWDT,PROTECT,NOMCLR					//El bit "INTRC_IO" activa el ocsilador interno pero sin salida de reloj. "INTRC" activa la salida de reloj e inhabilita RA4
#use delay(clock=4M)
#use fast_io(a)
#use fast_io(c)

int cont_CO = 0, cont_ROCIO = 0, set_CO = 0, set_ROCIO = 0;

void main(){
	set_tris_a(0xff);
	set_tris_c(0x00);
	output_c(0);
	setup_adc(ADC_CLOCK_INTERNAL);
	setup_adc_ports(sAN0);
	setup_adc_ports(sAN1);

//	PRESENCIA DE "AC"

	output_bit(pin_c1,1); 					// Así permanece mientras el sistema esté encendido


//	BLOQUE DE GENERACIÓN DE ALARMAS Y SEÑALES DE ACTIVACIÓN DE VÁLVULAS

	while(true){

		set_adc_channel(0);
		delay_us(10);
		set_CO = (255 - read_adc())/2;		// Ajusta el valor de la variable CO_time, para generar una cuenta entre 0 y 50
		set_adc_channel(1);
		delay_us(10);
		set_ROCIO = (255 - read_adc())/2;	// EL mismo ajuste para ROCIO_time

		if(input(pin_a4)){					//	Señal de CO
			output_bit(pin_c3,0);
			if(cont_CO < set_CO)
				cont_CO++;
		}
		else{
			output_bit(pin_c3,1);
			cont_CO = 0;
		}

		if(input(pin_a5)){					//	Señal de Punto de rocío
			output_bit(pin_c0,0);
			if(cont_ROCIO < set_ROCIO)
				cont_ROCIO++;
		}
		else{
			output_bit(pin_c0,1);
			cont_ROCIO = 0;
		}

//		SALIDAS DE VÁLVULA PRINCIPAL Y MANIFOIL TEMPORIZADAS

		if((input(pin_a4) && (cont_CO >= set_CO)) || (input(pin_a5) && (cont_ROCIO >= set_ROCIO))){
			output_bit(pin_c4,1);
			output_bit(pin_c2,1);
		}
		else{
			output_bit(pin_c4,0);
			output_bit(pin_c2,0);
		}

		delay_ms(500);						// Base de tiempo para los contadores
	}
}