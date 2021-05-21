#include <Examen.h>
#include <stdio.h>
#include <stdlib.h>

char buffer[1];
boolean flag = 0;
int client = 0;
int dizaine_client = 0;
int somme = dizaine_client*10 + client;
int seuil = 3;

// interruption lors d'un changement d'�tat sur le port B0, on incr�mente le nombre de clients de 1 unit�.
#INT_EXT 
void  EXT_isr(void) 
{
   client++;
   if(client == 10){
      client = 0;
      dizaine_client++;
   }
}

// interruption lors d'un changement d'�tat sur le port B1, on diminue le nombre de clients de 1 unit�.
#INT_EXT1
void  EXT1_isr(void) 
{
   client--;
   if(client == -1 && dizaine_client == 0){ //si on est d�j� � 0, on reste � 0.
      client = 0;
   }else if(client == -1){ //sinon on diminue la dizaine et nos unit�s passent � 9.
      client = 9;
      dizaine_client--;
   }
}

//on �coute l'interruption via le port COM3 du COMPIM et on l�ve un drapeau
#INT_RDA
void  RDA_isr(void) 
{
   buffer[0] = getc();
   flag = 1;
}

void main()
{
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_INTERNAL);

   enable_interrupts(INT_EXT);
   enable_interrupts(INT_EXT1);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   setup_low_volt_detect(FALSE);

   while(TRUE)
   {
      int somme = dizaine_client*10 + client;
      output_d(client);
      delay_ms(200);
      output_d((dizaine_client<<4));
      delay_ms(200);
      
      
      printf("%d ", somme); //sert � afficher la valeur actuelle sur terminal.exe
      
      
      if(somme >= seuil){ //lorsqu'on atteint le seuil, la led rouge clignote et la verte s'�teint.
         output_bit(pin_b4, 0);
         output_toggle(pin_b2);
      }else{ //sinon la led verte reste allum�e et la rouge s'�teint.
         output_bit(pin_b4, 1);
         output_bit(pin_b2, 0);
      }
      
      if(flag){ //lors de l'interruption du port COM
         flag = 0;
         seuil = atoi(buffer); // le seuil devient la valeur �crite dans l'application python.
       }
   }
}
