#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "MSYSTICK_interface.h"
#include "MSPI_interface.h"
#include "TFT_interface.h"
#include "PACKMAN.h"

// Function Prototypes
void GPIO_Init(void);
void SPI_TFT_Init(void);

void main(void)
{
    // Initialize system clock
    MRCC_voidInit();

    // Enable peripheral clocks
    MRCC_voidEnable_Clock_Periphral(AHB1, AHB1_GPIOA);
    MRCC_voidEnable_Clock_Periphral(AHB1, AHB1_GPIOB);
    MRCC_voidEnable_Clock_Periphral(APB2, 12); // SPI1

    // Initialize GPIO
    GPIO_Init();

    // Initialize SysTick timer
    MSYSYTICK_voidInit();

    // Initialize SPI and TFT
    SPI_TFT_Init();

    // Start the Pac-Man game
    PACKMAN_StartGame();

    while (1);
}

void GPIO_Init(void)
{
    // Configure PA0–PA2 as output (e.g., LEDs or control lines)
    for (u8 pin = 0; pin <= 2; pin++)
    {
        MGPIO_SetMode(PORT_A, pin, OUTPUT_MODE);
        MGPIO_SetOutputPinMode(PORT_A, pin, OUT_PUSH_PULL, OUT_MED_SPEED);
    }

    // Configure PB0, PB1, PB6 as input with pull-up (e.g., buttons)
    MGPIO_SetMode(PORT_B, PIN_0, INPUT_MODE);
    MGPIO_SetInputPinMode(PORT_B, PIN_0, PULL_UP);

    MGPIO_SetMode(PORT_B, PIN_1, INPUT_MODE);
    MGPIO_SetInputPinMode(PORT_B, PIN_1, PULL_UP);

    MGPIO_SetMode(PORT_B, PIN_4, INPUT_MODE);
    MGPIO_SetInputPinMode(PORT_B, PIN_4, PULL_UP);

    MGPIO_SetMode(PORT_B, PIN_6, INPUT_MODE);
    MGPIO_SetInputPinMode(PORT_B, PIN_6, PULL_UP);
}

void SPI_TFT_Init(void)
{
    // Configure PA4–PA7 as SPI1 alternate function (AF5)
    for (u8 pin = 4; pin <= 7; pin++)
    {
        MGPIO_SetMode(PORT_A, pin, ALTERNATIVE_FUNC_MODE);
        MGPIO_SetAlternativeFunction(PORT_A, pin, 5);
    }

    // Initialize SPI and TFT display
    MSPI_MasterInit();
    TFT_Init();
}
