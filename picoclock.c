/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"
#include "hardware/gpio.h"

#define HOURBUTTON 3
#define MINUTEBUTTON 4

/// \tag::hello_rtc_main[]
int main() {
	
	gpio_init(HOURBUTTON);
    gpio_dir(HOURBUTTON, GPIO_IN);
    gpio_pull_up(HOURBUTTON);
	
	gpio_init(MINUTEBUTTON);
    gpio_dir(MINUTEBUTTON, GPIO_IN);
    gpio_pull_up(MINUTEBUTTON);
	
    setup_default_uart();
    printf("Hello RTC!\n");

    char datetime_buf[256];
    char *datetime_str = &datetime_buf[0];

    // Start on Friday 5th of June 2020 15:45:00
	// only using hours and minutes, so the rest don't matter anyway
    datetime_t t = {
            .year  = 2020,
            .month = 06,
            .day   = 05,
            .dotw  = 5, // 0 is Sunday, so 5 is Friday
            .hour  = 15,
            .min   = 45,
            .sec   = 00
    };

    // Start the RTC
    rtc_init();
    rtc_set_datetime(&t);

    // Print the time
	//note can run the neopixels the other core so this little interface can use the sleep and not have any problems with the sleep and timing
    while (true) {
        rtc_get_datetime(&t);
        datetime_to_str(datetime_str, sizeof(datetime_buf), &t);
        printf("\r%s      \n", datetime_str);
		
		
        
		
		if (!gpio_get(HOURBUTTON)){
			t.hour = (t.hour+1)%24;
			rtc_set_datetime(&t);
		}
		
		if (!gpio_get(MINUTEBUTTON)){
			t.min = (t.min+1)%60;
			rtc_set_datetime(&t);
		}
		
		sleep_ms(500);
    }

    return 0;
}
/// \end::hello_rtc_main[]
