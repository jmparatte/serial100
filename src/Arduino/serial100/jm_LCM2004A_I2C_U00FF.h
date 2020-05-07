//éèà


#pragma once


// -----------------------------------------------------------------------------


#define OK true
#define ER false

#define _OK_ "=OK="
#define _ER_ "=ER="


// -----------------------------------------------------------------------------


#include <jm_LCM2004A_I2C.h>


// -----------------------------------------------------------------------------


#define HD44780U_CUSTOM_FR_CHARS false


// -----------------------------------------------------------------------------


class jm_LCM2004A_I2C_U00FF : public jm_LCM2004A_I2C
{
public:

	jm_LCM2004A_I2C_U00FF() {}
	jm_LCM2004A_I2C_U00FF(uint8_t i2c_address) : jm_LCM2004A_I2C(i2c_address) {}

#if HD44780U_CUSTOM_FR_CHARS

	bool begin() // return OK
	{
		return (jm_LCM2004A_I2C::begin() && load_custom_fr_chars_P());
	}

	bool begin(uint8_t i2c_address) // return OK
	{
		return (jm_LCM2004A_I2C::begin(i2c_address) && load_custom_fr_chars_P());
	}

	bool wait(uint16_t us)
	{
		if (us > 100) delayMicroseconds(us - 100);

		return true;
	}

	static const PROGMEM byte HD44780U_CUSTOM_FR_CHARS_P[8][8];
	static const PROGMEM byte HD44780U_A00_U00FF_FR_CUSTOM_P[256];

	bool load_custom_fr_chars_P()
	{
		return write_cgram_P( 0, 8, HD44780U_CUSTOM_FR_CHARS_P[0] );
	}

	byte HD44780U_A00_U00FF_FR_translate(byte c)
	{
		return pgm_read_byte_near(HD44780U_A00_U00FF_FR_CUSTOM_P + c);
	}

#else

	static const PROGMEM byte HD44780U_A00_U00FF_FR_P[256];

	byte HD44780U_A00_U00FF_FR_translate(byte c)
	{
		return pgm_read_byte_near(HD44780U_A00_U00FF_FR_P + c);
	}

#endif

	virtual size_t write(byte c)
	{
		return jm_LCM2004A_I2C::write(HD44780U_A00_U00FF_FR_translate(c));
	}

	using jm_LCM2004A_I2C::write;
};


// -----------------------------------------------------------------------------


#if HD44780U_CUSTOM_FR_CHARS

const PROGMEM byte jm_LCM2004A_I2C_U00FF::HD44780U_CUSTOM_FR_CHARS_P[8][8] = {

// HD44780U
// Table 4 Correspondence between Character Codes and Character Patterns (ROM Code: A00)

	{ 0b00000,0b10000,0b01000,0b00100,0b00010,0b00001,0b00000,0b00000 }, // 0 '\'
	{ 0b01000,0b10101,0b00010,0b00000,0b00000,0b00000,0b00000,0b00000 }, // 1 ~
	{ 0b00010,0b00100,0b01110,0b10001,0b11111,0b10000,0b01110,0b00000 }, // 2 é
	{ 0b01000,0b00100,0b01110,0b10001,0b11111,0b10000,0b01110,0b00000 }, // 3 è
	{ 0b00100,0b01010,0b01110,0b10001,0b11111,0b10000,0b01110,0b00000 }, // 4 ê
	{ 0b01000,0b00100,0b01110,0b00001,0b01111,0b10001,0b01111,0b00000 }, // 5 à
	{ 0b00100,0b01010,0b01110,0b00001,0b01111,0b10001,0b01111,0b00000 }, // 6 â
	{ 0b00000,0b00000,0b01110,0b10000,0b10000,0b01111,0b00100,0b01100 }  // 7 ç
};

const PROGMEM byte jm_LCM2004A_I2C_U00FF::HD44780U_A00_U00FF_FR_CUSTOM_P[256] = {

// https://fr.wikipedia.org/wiki/Table_des_caract%C3%A8res_Unicode_(0000-0FFF)

//	0    1    2    3    4    5    6    7    	8    9    A    B    C    D    E    F

//	U+0000
//	NUL  SOH  STX  ETX  EOT  ENQ  ACK  BEL  	BS   HT   LF   VT   FF   CR   SO   SI
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//	U+0010
//	DLE  DC1  DC2  DC3  DC4  NAK  SYN  ETB  	CAN  EM   SUB  ESC  FS   GS   RS   US
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//	U+0020
	' ', '!', '"', '#', '$', '%', '&', '\'', 	'(', ')', '*', '+', ',', '-', '.', '/',
	'0', '1', '2', '3', '4', '5', '6', '7', 	'8', '9', ':', ';', '<', '=', '>', '?',
	'@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 	'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 	'X', 'Y', 'Z', '[',	 0,  ']', '^', '_',
	'`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 	'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
	'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 	'x', 'y', 'z', '{', '|', '}',  1,  0xFF,

//	0    1    2    3    4    5    6    7    	8    9    A    B    C    D    E    F

//	U+0080
//	PAD  HOP  BPH  NBH  IND  NEL  SSA  ESA  	HTS  HTJ  VTS  PLD  PLU  RI   SS2  SS3
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//	U+0090 	"
//	DCS  PU1  PU2  STS  CCH  MW   SPA  EPA  	SOS  SGCI SCI  CSI  ST   OSC  PM   APC
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//	U+00A0
//	NBSP "¡"  "¢"  "£"  "¤"  "¥"  "¦"  "§"  	"¨"  "©"  "ª"  "«"  "¬"  SHY  "®"  "¯"
	' ', '!', 0xEC,0xFF,0Xff,0x5C,0Xff,0Xff, 	'"', 'c', 'A', '<', 0xFF,'-', 'R', 0xFF,
//	U+00B0
//	"°"  "±"  "²"  "³"  "´"  "µ"  "¶"  "·"  	"¸"  "¹"  "º"  "»"  "¼"  "½"  "¾"  "¿"
	'o', 0xFF,'2', '3', '\'',0xE4,0xFF,0xA5, 	0xFF,'1', '0', '>', 0xFF,0xFF,0xFF,'?',
//	U+00C0
//	"À"  "Á"  "Â"  "Ã"  "Ä"  "Å"  "Æ"  "Ç"  	"È"  "É"  "Ê"  "Ë"  "Ì"  "Í"  "Î"  "Ï"
	'A', 'A', 'A', 'A', 'A', 'A', 'A', 7,   	'E', 'E', 'E', 'E', 'I', 'I', 'I', 'I',
//	U+00D0
//	"Ð"  "Ñ"  "Ò"  "Ó"  "Ô"  "Õ"  "Ö"  "×"  	"Ø"  "Ù"  "Ú"  "Û"  "Ü"  "Ý"  "Þ"  "ß"
	'D', 'N', 'O', 'O', 'O', 'O', 'O', 0xF8, 	'0', 'U', 'U', 'U', 'U', 'Y', 0xFF,0xE2,
// U+00E0
//	"à"  "á"  "â"  "ã"  "ä"  "å"  "æ"  "ç"  	"è"  "é"  "ê"  "ë"  "ì"  "í"  "î"  "ï"
	5,   'a', 6,   'a', 'a', 'a', 'a', 7,   	3,   2,   4,   'e', 'i', 'i', 'i', 'i',
// U+00F0
//	"ð"  "ñ"  "ò"  "ó"  "ô"  "õ"  "ö"  "÷"  	"ø"  "ù"  "ú"  "û"  "ü"  "ý"  "þ"  "ÿ"
	0xFF,'n', 'o', 'o', 'o', 'o', 'o', 0xFD, 	'0', 'u', 'u', 'u', 'u', 'y', 0xFF,'y'
};

#else

const PROGMEM byte jm_LCM2004A_I2C_U00FF::HD44780U_A00_U00FF_FR_P[256] = {

// https://fr.wikipedia.org/wiki/Table_des_caract%C3%A8res_Unicode_(0000-0FFF)

//	0    1    2    3    4    5    6    7    	8    9    A    B    C    D    E    F

//	U+0000
//	NUL  SOH  STX  ETX  EOT  ENQ  ACK  BEL  	BS   HT   LF   VT   FF   CR   SO   SI
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//	U+0010
//	DLE  DC1  DC2  DC3  DC4  NAK  SYN  ETB  	CAN  EM   SUB  ESC  FS   GS   RS   US
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//	U+0020
	' ', '!', '"', '#', '$', '%', '&', '\'', 	'(', ')', '*', '+', ',', '-', '.', '/',
	'0', '1', '2', '3', '4', '5', '6', '7', 	'8', '9', ':', ';', '<', '=', '>', '?',
	'@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 	'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 	'X', 'Y', 'Z', '[',	0xFF,']', '^', '_',
	'`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 	'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
	'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 	'x', 'y', 'z', '{', '|', '}', 0xFF,0xFF,

//	0    1    2    3    4    5    6    7    	8    9    A    B    C    D    E    F

//	U+0080
//	PAD  HOP  BPH  NBH  IND  NEL  SSA  ESA  	HTS  HTJ  VTS  PLD  PLU  RI   SS2  SS3
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//	U+0090 	"
//	DCS  PU1  PU2  STS  CCH  MW   SPA  EPA  	SOS  SGCI SCI  CSI  ST   OSC  PM   APC
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//	U+00A0
//	NBSP "¡"  "¢"  "£"  "¤"  "¥"  "¦"  "§"  	"¨"  "©"  "ª"  "«"  "¬"  SHY  "®"  "¯"
	' ', '!', 0xEC,0xFF,0Xff,0x5C,0Xff,0Xff, 	'"', 'c', 'A', '<', 0xFF,'-', 'R', 0xFF,
//	U+00B0
//	"°"  "±"  "²"  "³"  "´"  "µ"  "¶"  "·"  	"¸"  "¹"  "º"  "»"  "¼"  "½"  "¾"  "¿"
	'o', 0xFF,'2', '3', '\'',0xE4,0xFF,0xA5, 	0xFF,'1', '0', '>', 0xFF,0xFF,0xFF,'?',
//	U+00C0
//	"À"  "Á"  "Â"  "Ã"  "Ä"  "Å"  "Æ"  "Ç"  	"È"  "É"  "Ê"  "Ë"  "Ì"  "Í"  "Î"  "Ï"
	'A', 'A', 'A', 'A', 'A', 'A', 'A', 'C',  	'E', 'E', 'E', 'E', 'I', 'I', 'I', 'I',
//	U+00D0
//	"Ð"  "Ñ"  "Ò"  "Ó"  "Ô"  "Õ"  "Ö"  "×"  	"Ø"  "Ù"  "Ú"  "Û"  "Ü"  "Ý"  "Þ"  "ß"
	'D', 'N', 'O', 'O', 'O', 'O', 'O', 0xF8, 	'0', 'U', 'U', 'U', 'U', 'Y', 0xFF,0xE2,
// U+00E0
//	"à"  "á"  "â"  "ã"  "ä"  "å"  "æ"  "ç"  	"è"  "é"  "ê"  "ë"  "ì"  "í"  "î"  "ï"
	'a', 'a', 'a', 'a', 'a', 'a', 'a', 'c',   	'e', 'e', 'e', 'e', 'i', 'i', 'i', 'i',
// U+00F0
//	"ð"  "ñ"  "ò"  "ó"  "ô"  "õ"  "ö"  "÷"  	"ø"  "ù"  "ú"  "û"  "ü"  "ý"  "þ"  "ÿ"
	0xFF,'n', 'o', 'o', 'o', 'o', 'o', 0xFD, 	'0', 'u', 'u', 'u', 'u', 'y', 0xFF,'y'
};

#endif


// -----------------------------------------------------------------------------


// END.
