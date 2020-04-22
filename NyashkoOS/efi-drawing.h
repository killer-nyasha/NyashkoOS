#pragma once
//******************************************************* // UNICODE DRAWING CHARACTERS
//*******************************************************
#define BOXDRAW_HORIZONTAL               0x2500
#define BOXDRAW_VERTICAL                 0x2502
#define BOXDRAW_DOWN_RIGHT               0x250c
#define BOXDRAW_DOWN_LEFT                0x2510
#define BOXDRAW_UP_RIGHT                 0x2514
#define BOXDRAW_UP_LEFT                  0x2518
#define BOXDRAW_VERTICAL_RIGHT           0x251c
#define BOXDRAW_VERTICAL_LEFT            0x2524
#define BOXDRAW_DOWN_HORIZONTAL          0x252c
#define BOXDRAW_UP_HORIZONTAL            0x2534
#define BOXDRAW_VERTICAL_HORIZONTAL      0x253c
#define BOXDRAW_DOUBLE_HORIZONTAL        0x2550
#define BOXDRAW_DOUBLE_VERTICAL          0x2551
#define BOXDRAW_DOWN_RIGHT_DOUBLE        0x2552
#define BOXDRAW_DOWN_DOUBLE_RIGHT        0x2553
#define BOXDRAW_DOUBLE_DOWN_RIGHT        0x2554
#define BOXDRAW_DOWN_LEFT_DOUBLE         0x2555
#define BOXDRAW_DOWN_DOUBLE_LEFT         0x2556
#define BOXDRAW_DOUBLE_DOWN_LEFT         0x2557
#define BOXDRAW_UP_RIGHT_DOUBLE          0x2558
#define BOXDRAW_UP_DOUBLE_RIGHT          0x2559
#define BOXDRAW_DOUBLE_UP_RIGHT          0x255a
#define BOXDRAW_UP_LEFT_DOUBLE           0x255b
#define BOXDRAW_UP_DOUBLE_LEFT           0x255c
#define BOXDRAW_DOUBLE_UP_LEFT           0x255d
#define BOXDRAW_VERTICAL_RIGHT_DOUBLE    0x255e
#define BOXDRAW_VERTICAL_DOUBLE_RIGHT    0x255f
#define BOXDRAW_DOUBLE_VERTICAL_RIGHT    0x2560
#define BOXDRAW_VERTICAL_LEFT_DOUBLE     0x2561
#define BOXDRAW_VERTICAL_DOUBLE_LEFT     0x2562
#define BOXDRAW_DOUBLE_VERTICAL_LEFT     0x2563
#define BOXDRAW_DOWN_HORIZONTAL_DOUBLE   0x2564
#define BOXDRAW_DOWN_DOUBLE_HORIZONTAL   0x2565
#define BOXDRAW_DOUBLE_DOWN_HORIZONTAL   0x2566
#define BOXDRAW_UP_HORIZONTAL_DOUBLE     0x2567
#define BOXDRAW_UP_DOUBLE_HORIZONTAL     0x2568
#define BOXDRAW_DOUBLE_UP_HORIZONTAL     0x2569
#define BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE 0x256a
#define BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL 0x256b
#define BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL 0x256c
//*******************************************************
// EFI Required Block Elements Code Chart
//*******************************************************
#define BLOCKELEMENT_FULL_BLOCK            0x2588
#define BLOCKELEMENT_LIGHT_SHADE           0x2591
//******************************************************* // EFI Required Geometric Shapes Code Chart
//*******************************************************
#define GEOMETRICSHAPE_UP_TRIANGLE         0x25b2
#define GEOMETRICSHAPE_RIGHT_TRIANGLE      0x25ba
#define GEOMETRICSHAPE_DOWN_TRIANGLE       0x25bc
#define GEOMETRICSHAPE_LEFT_TRIANGLE       0x25c4
//******************************************************* // EFI Required Arrow shapes
//*******************************************************
#define ARROW_UP                           0x2191
#define ARROW_DOWN                         0x2193

//*******************************************************
// Attributes
//*******************************************************
#define EFI_BLACK                            0x00
#define EFI_BLUE                             0x01
#define EFI_GREEN                            0x02
#define EFI_CYAN                             0x03
#define EFI_RED                              0x04
#define EFI_MAGENTA                          0x05
#define EFI_BROWN                            0x06
#define EFI_LIGHTGRAY                        0x07
#define EFI_BRIGHT                           0x08
#define EFI_DARKGRAY						 0x08
#define EFI_LIGHTBLUE                        0x09
#define EFI_LIGHTGREEN                       0x0A
#define EFI_LIGHTCYAN                        0x0B
#define EFI_LIGHTRED                         0x0C
#define EFI_LIGHTMAGENTA                     0x0D
#define EFI_YELLOW                           0x0E
#define EFI_WHITE                            0x0F
#define EFI_BACKGROUND_BLACK                 0x00
#define EFI_BACKGROUND_BLUE                  0x10
#define EFI_BACKGROUND_GREEN                 0x20
#define EFI_BACKGROUND_CYAN                  0x30
#define EFI_BACKGROUND_RED                   0x40
#define EFI_BACKGROUND_MAGENTA               0x50
#define EFI_BACKGROUND_BROWN                 0x60
#define EFI_BACKGROUND_LIGHTGRAY             0x70

//
// Macro to accept color values in their raw form to create 
// a value that represents both a foreground and background 
// color in a single byte.
// For Foreground, and EFI_* value is valid from EFI_BLACK(0x00) 
// to EFI_WHITE (0x0F).
// For Background, only EFI_BLACK, EFI_BLUE, EFI_GREEN, 
// EFI_CYAN, EFI_RED, EFI_MAGENTA, EFI_BROWN, and EFI_LIGHTGRAY // are acceptable.
//
// Do not use EFI_BACKGROUND_xxx values with this macro.
//#define EFI_TEXT_ATTR(Foreground,Background) ((Foreground) | ((Background) << 4))
