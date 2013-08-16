

#include "ardos/ardos.h"

void t1()
{
    ardos_pin_mode(7, ARDOS_OUT);
    ardos_digital_write(7, 1);

    for (; ; )
    {
        if (ardos_serial_receive())
        {
            ardos_serial_request();
            ardos_serial_sends("\'b\' recebido\n\r");
            ardos_serial_release();
            ardos_digital_write(7, 0);
            ardos_process_sleep(50);
            ardos_digital_write(7, 1);
        }
    }
    
    ardos_process_exit();
}

void _main()
{
    ardos_serial_open(9600, ARDOS_NO_PARITY, ARDOS_1STOPBIT, ARDOS_8BIT_SERIAL);

    ardos_process_create(t1);
    
    ardos_pin_mode(8, ARDOS_OUT);
    ardos_digital_write(8, 1);
    
    for (; ; ) 
    {
        if (ardos_serial_receive())
        {
            ardos_serial_request();
            ardos_serial_sends("\'a\' recebido\n\r");
            ardos_serial_release();
            ardos_digital_write(8, 0);
            ardos_process_sleep(50);
            ardos_digital_write(8, 1);
        } 
    }
    
    ardos_process_exit();
}

int main()
{
    ardos_init(_main);
    return 0;
}
