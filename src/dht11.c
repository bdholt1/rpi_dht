/* 
 * Taken from http://www.rpiblog.com/2012/11/interfacing-temperature-and-humidity.html
 */

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAX_TIME 85
#define ATTEMPTS 5

int dht11_read_val(int pin)
{
  uint8_t lststate = HIGH;
  uint8_t counter = 0;
  uint8_t j = 0,i;

  int dht11_val[5] = {0,0,0,0,0};
  for(i = 0; i < 5; i++)
    dht11_val[i] = 0;

  pinMode(pin,OUTPUT);
  digitalWrite(pin, LOW);
  delay(18);
  digitalWrite(pin, HIGH);
  delayMicroseconds(40);
  pinMode(pin, INPUT);
  for (i = 0; i < MAX_TIME; i++)
  {
      counter=0;
      while (digitalRead(pin)==lststate)
      {
          counter++;
          delayMicroseconds(1);
          if (counter == 255)
              break;
      }

      lststate = digitalRead(pin);
      if (counter == 255)
          break;

      // top 3 transistions are ignored
      if ((i >= 4) && (i%2 == 0))
      {
          dht11_val[j/8] <<= 1;
          if (counter > 16)
              dht11_val[j/8] |= 1;
          j++;
      }
  }

  // verify checksum and print the verified data
  if ( (j>=40) && (dht11_val[4]==((dht11_val[0]+dht11_val[1]+dht11_val[2]+dht11_val[3])& 0xFF)))
  {
      printf("%d.%d,%d.%d\n", dht11_val[0], dht11_val[1], dht11_val[2], dht11_val[3]);
      return 1;
  }
  else
      return 0;
}

int main(int argc, char *argv[])
{
    if ( argc != 2 )
    {
        printf("Usage: dht11 pin \n");
        exit(1);
    }

    int attempts = ATTEMPTS;
    if (wiringPiSetup() == -1)
        exit(1);
    while (attempts)
    {
        int success = dht11_read_val(atoi(argv[1]));
        if (success) {
            break;
        }
        attempts--;
        delay(500);
    }
    return 0;
}
