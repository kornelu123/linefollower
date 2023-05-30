#include "main.h"
#include "stm32wbxx.h"
#include <stdint.h>
#include "uart.h"

int main(void)
{
  uint32_t baud = 115200;
  uint32_t periph = 32000000;
  uint32_t uart_presc = 8;
  uart_init_tx(baud,periph,uart_presc);
  RCC->AHB2ENR |= (1U<<1);
  GPIOB->MODER |= (1U<<0);
  GPIOB->MODER &=~(1U<<1);
  prints("No, ja chciałem się wypowiedzieć, na ten temat, co wy ludzie mówicie ogółem. Ja mogę, czy ja mogę wstanąć, czy mogę usiąść, ale ogółem.Czy jest ziemia płaska? Płaska, jaka pł— no pła.Ja byłem na księżycu,\n prawie, i poprostu księżyc patrzył na ziemię, ale ziemia czy jest płaska? no czy jest stół płaski?Ale ziemia czy jest płaska? Ludzie ogółem zastanówcie się.Ja byłem ostatnio na \nksiężycu i spadała czy na ziemię płaską czy na kulą odporną od płaskiego.Ja nie wiem jeszcze. ogółem spotkałem człowieka takiego wspaniałego i o to nie był człowiek.To był \nżuber z sarną, i spadałem i spadłem na żubra i on powiedział nie to niezabardzo jest płaska ziemia, to jest pół okrągła. Ale ja mówię co ty pierdolisz to musi być inaczej, \njak inacz—, jak a on mówi do mnie inaczej? O Jak inaczej.A ja za róg go mówi Inaczej, mówi Inaczej, jak inaczej. Ktoś wymyślił ziemię. Czy jest płaska. Ja mówię co ty \npierdolisz kurwa głupoty jak jest pół okrągła a z tej strony jest okrągła. I on mi zaczeliśmy myśleć.O cholera. Dobry człowiek! Jakie, ja mówię, myślę to dobry człowiek? \nPopatrzcie na historię na którą niektórzy lecieli na księ— kśniżyc, polecieli dalej i lądowali na żubra.To ja byłem ostatnio na księżycu? Okrągła... A słońce?! Słońce się obraca na\n, na czym się obraca? Na płaskim? To kurwa musiało przepraszam musiałoby mieć sto lat, to musi być coś okrągłego.Prostu ja chciałem się na ten temat wypowiedzieć bo ja nie jestem \nhistorykiem, bo ja byłem tam i jestem tutaj. Po prostu pewne rzeczy no świat nauczył mnie i prostu chciałem wam powiedzieć że zastanówcie się czy jest ziemia okrągła. \n");
  while (1)
  {
    GPIOB->ODR ^= (1U<<0);
    for(int i=0;i<1000000;i++);
  }
 } 
