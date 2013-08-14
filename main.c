

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "ardos/ardos.h"


void p1()
{
    ardos_pin_mode(9, ARDOS_OUT);
    ardos_pin_mode(10, ARDOS_IN);
    
    for (; ; )
    {
        if (ardos_digital_read(10))
        {
            ardos_digital_write(9, ARDOS_HIGH);
            ardos_process_sleep(1000);
            ardos_digital_write(9, ARDOS_LOW);
            ardos_process_sleep(500);
        }
    }
    
    ardos_process_exit();
}

void _main()
{
    ardos_pin_mode(7, ARDOS_OUT);
    ardos_pin_mode(8, ARDOS_IN);

    ardos_process_create(p1);

    for (; ; )
    {
        if (ardos_digital_read(8))
        {
            ardos_digital_write(7, ARDOS_HIGH);
            ardos_process_sleep(500);
            ardos_digital_write(7, ARDOS_LOW);
            ardos_process_sleep(500);
        }
    }

    ardos_process_exit();
}

int main()
{
    ardos_init(_main);

    for (; ; ) { }

    return 0;
}
