#include "stm32f10x.h" //
int main(void){
    RCC->APB2ENR = 0x00000010; // Enable GPIOC clock
    GPIOC->CRH = 0x00300000; // Configure PC13 as output
    GPIOC->ODR = 0x00002000; // Set PC13 to high, led off
    //GPIOC->ODR = 0x00000000; // Set PC13 to low, led on

    while(1);
    return 0;
}
