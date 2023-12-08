int main() {
    // Initialize LCD module
    lcd_init(LCD_DISP_ON);

    // Initialize button
    button_init();

    int hours = 0;
    int minutes = 0;

    while (1) {
        // Check if the button is pressed
        if (button_pressed()) {
            // Increment minutes
            minutes++;
            if (minutes >= 60) {
                minutes = 0;
                hours++;
                if (hours >= 24) {
                    hours = 0;
                }
            }
        }

        // Display the current time on the LCD
        lcd_clrscr();
        lcd_gotoxy(0, 0);
        printf("%02d:%02d", hours, minutes);

        _delay_ms(500); // Delay for display refresh
    }

    return 0;
}
