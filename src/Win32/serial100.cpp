//éèà


// -----------------------------------------------------------------------------


#define __PROG__ "serial100.cpp"


// -----------------------------------------------------------------------------


//	https://docs.microsoft.com/en-us/previous-versions/ff802693(v=msdn.10)?redirectedfrom=MSDN


/* 	COMMTIMEOUTS
	============

	https://msdn.microsoft.com/en-us/library/windows/desktop/aa363190(v=vs.85).aspx

	typedef struct _COMMTIMEOUTS {
		DWORD ReadIntervalTimeout;
		DWORD ReadTotalTimeoutMultiplier;
		DWORD ReadTotalTimeoutConstant;
		DWORD WriteTotalTimeoutMultiplier;
		DWORD WriteTotalTimeoutConstant;
	} COMMTIMEOUTS, *LPCOMMTIMEOUTS;

	https://msdn.microsoft.com/fr-fr/library/windows/desktop/aa363428(v=vs.85).aspx

	BOOL WINAPI PurgeComm(
		_In_ HANDLE hFile,
		_In_ DWORD  dwFlags
	);

	*/


/*	DCB
	===

	https://docs.microsoft.com/en-us/windows/win32/api/winbase/ns-winbase-dcb

	typedef struct _DCB {
	  DWORD DCBlength;
	  DWORD BaudRate;
	  DWORD fBinary : 1;
	  DWORD fParity : 1;
	  DWORD fOutxCtsFlow : 1;
	  DWORD fOutxDsrFlow : 1;
	  DWORD fDtrControl : 2;
	  DWORD fDsrSensitivity : 1;
	  DWORD fTXContinueOnXoff : 1;
	  DWORD fOutX : 1;
	  DWORD fInX : 1;
	  DWORD fErrorChar : 1;
	  DWORD fNull : 1;
	  DWORD fRtsControl : 2;
	  DWORD fAbortOnError : 1;
	  DWORD fDummy2 : 17;
	  WORD  wReserved;
	  WORD  XonLim;
	  WORD  XoffLim;
	  BYTE  ByteSize;
	  BYTE  Parity;
	  BYTE  StopBits;
	  char  XonChar;
	  char  XoffChar;
	  char  ErrorChar;
	  char  EofChar;
	  char  EvtChar;
	  WORD  wReserved1;
	} DCB, *LPDCB;

	*/


// -----------------------------------------------------------------------------


/*	Commande MODE
	=============

mode com1 baud=115200 parity=n data=8 stop=1 to=off xon=off octs=off odsr=off idsr=off dtr=off rts=on

Statut du périphérique COM1:
----------------------------
    Baud :            115200
    Parité :          None
    Bits de données : 8
    Bits d’arrêt :    1
    Temporisation :   OFF
    XON/XOFF :        OFF
    Protocole CTS :   OFF
    Protocole DSR :   OFF
    Sensibilité DSR : OFF
    Circuit DTR :     OFF
    Circuit RTS :     ON

	*/


// -----------------------------------------------------------------------------


/*	Docs / Windows Server / Commandes Windows / Commandes par rôle serveur / mode
	=============================================================================

	https://docs.microsoft.com/fr-fr/windows-server/administration/windows-commands/mode
	mode com<M>[:] [baud=<B>] [parity=<P>] [data=<D>] [stop=<S>] [to={on|off}] [xon={on|off}] [odsr={on|off}] [octs={on|off}] [dtr={on|off|hs}] [rts={on|off|hs|tg}] [idsr={on|off}]

	https://docs.microsoft.com/en-us/windows/win32/devio/communications-functions

	*/


// -----------------------------------------------------------------------------


/*

typedef struct _FILETIME {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

void GetSystemTimeAsFileTime(
  LPFILETIME lpSystemTimeAsFileTime
);

BOOL GetProcessTimes(
  HANDLE     hProcess,
  LPFILETIME lpCreationTime,
  LPFILETIME lpExitTime,
  LPFILETIME lpKernelTime,
  LPFILETIME lpUserTime
);

HANDLE GetCurrentProcess();

	*/

//	https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/putc-putwc?view=vs-2019
//	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-readfile
//	https://docs.microsoft.com/en-us/windows/win32/procthread/process-and-thread-functions


// -----------------------------------------------------------------------------


#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include <winbase.h>


// -----------------------------------------------------------------------------


// Windows Data Types
// https://docs.microsoft.com/en-us/windows/win32/winprog/windows-data-types

typedef INT8 int8_t;
typedef INT16 int16_t;
typedef INT32 int32_t;
typedef INT64 int64_t;

typedef UINT8 uint8_t;
typedef UINT16 uint16_t;
typedef UINT32 uint32_t;
typedef UINT64 uint64_t;


// -----------------------------------------------------------------------------


FILETIME ftCreationTime = {0, 0};


UINT64 ft64(FILETIME & ft)
{
	return (UINT64(ft.dwHighDateTime)<<32 | ft.dwLowDateTime);
}


long micros()
{
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);

	FILETIME ft1, ft2, ft3;
	if (ft64(ftCreationTime)==0) GetProcessTimes(GetCurrentProcess(), &ftCreationTime, &ft1, &ft2, &ft3);

	return (long) UINT64(ft64(ft) - ft64(ftCreationTime))/10;
}


long millis()
{
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);

	FILETIME ft1, ft2, ft3;
	if (ft64(ftCreationTime)==0) GetProcessTimes(GetCurrentProcess(), &ftCreationTime, &ft1, &ft2, &ft3);

	return (long) UINT64(ft64(ft) - ft64(ftCreationTime))/10/1000;
}


void delay(long ms)
{
	if (ms > 0) Sleep(ms);
}


// -----------------------------------------------------------------------------


class Serial_class {

protected:

	bool _connected;

public:

	HANDLE _hComm;
	DCB _dcb;
	COMMTIMEOUTS _timeouts;
	int _peek; // RX peek char

public:

	Serial_class() :
		_connected(false),
		_hComm(0),
		_dcb{0},
		_timeouts({0, 0,1, 0,0}), // RX returns immediately if no available char
		_peek(-1)
	{}

	operator bool()
	{
		return _connected;
	}

	bool connected()
	{
		return _connected;
	}

	bool begin(const char * comm_path) // return OK
	{
		if (_connected) return true;

		// !connected, try to connect...
		_hComm = CreateFile(comm_path, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (_hComm == INVALID_HANDLE_VALUE) return false;

		// apply default timeouts...
		SetCommTimeouts(_hComm, &_timeouts);

		// set 115200,8,N,1... DTR=OFF, RTS=OFF...

		if (GetCommState(_hComm, &_dcb) == 0) return false;

		if (
			_dcb.DCBlength != sizeof(DCB) ||
			_dcb.BaudRate != 115200 || //CBR_115200 ||
			_dcb.ByteSize != 8 ||
			_dcb.Parity != NOPARITY ||
			_dcb.StopBits != ONESTOPBIT ||
		//	...
			_dcb.fDtrControl != 0 ||
			_dcb.fRtsControl != 0 )
		{
			_dcb.DCBlength = sizeof(DCB);
			_dcb.BaudRate = 115200; //CBR_115200;
			_dcb.ByteSize = 8;
			_dcb.Parity = NOPARITY;
			_dcb.StopBits = ONESTOPBIT;
		//	...
			_dcb.fDtrControl = 0;
			_dcb.fRtsControl = 0;

			if (SetCommState(_hComm, &_dcb) == 0) return false;
		}

		// set connected and return...
		_connected = true;
		return true;
	}

	bool end()
	{
		CloseHandle(_hComm);
		_connected = false;
		return true;
	}

	// implementation of Stream virtual methods...

	int available()
	{
		if (peek() >= 0) return 1; else return 0;
	}

	int read() // read char from Serial...
	{
		int c = peek();
		_peek = -1;
		return c;
	}

	int peek() // peek char from Serial...
	{
		if (!_connected) return -1;
		if (_peek >= 0 ) return _peek;
		BYTE c = 0;
		DWORD l = 0;
		if (ReadFile(_hComm, &c, 1, &l, 0)==0 || l==0) return (_peek = -1);
		_peek = c;
		return _peek;
	}

	// implementation of Stream : Print virtual methods...

	size_t write(uint8_t c) // write byte to Serial...
	{
		if (!_connected) return 0;
		DWORD l = 0;
		if (WriteFile(_hComm, &c, 1, &l, 0) == 0) return 0;
		return l;
	}

	size_t write(const uint8_t * buffer, size_t size) // write buffer to Serial...
	{
		size_t l = 0;
		for (int i=0; i<size; i++) l += write(buffer[i]);
		return l;
	}

	size_t write(const char * str) // write str to Serial...
	{
		return write((const uint8_t *) str, strlen(str));
	}

    int availableForWrite()
    {
		if (!_connected) return 0; else return 1;
	}

	void dump()
	{
		printf("[test100:%i]\n", __LINE__);
		printf("DCBlength:%i\n", (int)_dcb.DCBlength);
		printf("BaudRate:%i\n", (int)_dcb.BaudRate);
		printf("fBinary:%i\n", (int)_dcb.fBinary );
		printf("fParity:%i\n", (int)_dcb.fParity );
		printf("fOutxCtsFlow:%i\n", (int)_dcb.fOutxCtsFlow );
		printf("fOutxDsrFlow:%i\n", (int)_dcb.fOutxDsrFlow );
		printf("fDtrControl:%i\n", (int)_dcb.fDtrControl );
		printf("fDsrSensitivity:%i\n", (int)_dcb.fDsrSensitivity );
		printf("fTXContinueOnXoff:%i\n", (int)_dcb.fTXContinueOnXoff );
		printf("fOutX:%i\n", (int)_dcb.fOutX );
		printf("fInX:%i\n", (int)_dcb.fInX );
		printf("fErrorChar:%i\n", (int)_dcb.fErrorChar );
		printf("fNull:%i\n", (int)_dcb.fNull );
		printf("fRtsControl:%i\n", (int)_dcb.fRtsControl );
		printf("fAbortOnError:%i\n", (int)_dcb.fAbortOnError );
		printf("fDummy2:%i\n", (int)_dcb.fDummy2 );
		printf("wReserved:%i\n", (int)_dcb.wReserved);
		printf("XonLim:%i\n", (int)_dcb.XonLim);
		printf("XoffLim:%i\n", (int)_dcb.XoffLim);
		printf("ByteSize:%i\n", (int)_dcb.ByteSize);
		printf("Parity:%i\n", (int)_dcb.Parity);
		printf("StopBits:%i\n", (int)_dcb.StopBits);
		printf("XonChar:%i\n", (int)_dcb.XonChar);
		printf("XoffChar:%i\n", (int)_dcb.XoffChar);
		printf("ErrorChar:%i\n", (int)_dcb.ErrorChar);
		printf("EofChar:%i\n", (int)_dcb.EofChar);
		printf("EvtChar:%i\n", (int)_dcb.EvtChar);
		printf("wReserved1:%i\n", (int)_dcb.wReserved1);
	}

} Serial;


// -----------------------------------------------------------------------------


class Console_class {

protected:

	bool _connected;
	int _peek;

public:

	Console_class() :
		_connected(true),
		_peek(-1)
	{}

	operator bool()
	{
		return _connected;
	}

	bool connected()
	{
		return _connected;
	}

	// implementation of Stream virtual methods...

	int available() // available char from Serial...
	{
		if (peek() >= 0) return 1; else return 0;
	}

	int read() // read char from Serial...
	{
		int c = peek();
		_peek = -1;
		return c;
	}

	int peek() // peek char from Serial...
	{
		if (!_connected) return -1;
		if (_peek >= 0 ) return _peek;
		_peek = getwchar(); // return char ascii value or WEOF (-1) if no available char
		if (_peek == WEOF) _peek = -1;
		return _peek;
	}

	// implementation of Stream : Print virtual methods...

	size_t write(uint8_t c)	// write byte to Serial...
	{
		if (putwchar(c) != c) return 0;
		return 1;
	}

	size_t write(const uint8_t * buffer, size_t size) // write buffer to Serial...
	{
		size_t l = 0;
		for (int i=0; i<size; i++) l += write(buffer[i]);
		return l;
	}

	size_t write(const char * str) // write str to Serial...
	{
		return write((const uint8_t *) str, strlen(str));
	}

    int availableForWrite()
    {
		if (!_connected) return 0; else return 1;
	}

} Console;


// -----------------------------------------------------------------------------


#define OK true
#define ER false

#define _OK_ "=OK="
#define _ER_ "=ER="


// -----------------------------------------------------------------------------


union {
	long l;
	struct {
		bool debug: 1;
	};
} options;


// -----------------------------------------------------------------------------


// program <options> <comm_port> <rx_timeout> [<tx_argument>...]

// argv[0]	program
// argv[1]	options			0
// argv[2]	comm_port		COM1
// argv[3]	rx_timeout		100
// argv[4]	tx_argument		/millis
// argv[5]	...


int main(int argc, char *argv[]) // return errcode
{
	// errcode and error message
	int errcode = 0;					// errcode "no error"
	const char * errcstr = NULL;		// message "no error"

	// check number of arguments...
	if (argc < 4)						// argv[0]...argv[3] ?
	{
		errcode = 1;
		errcstr = (const char *) & "#too few parameters";
		goto _exit;
	}

	// retrieve program options...
	options.l = atol(argv[1]);			// debug options,...

	// retrieve communication port...
	static char comm_path[4+3+2+1] = "\\\\.\\"; // \\.\COMnn<0>
	strncat(comm_path, argv[2], 3+2);	// concat COMnn (COM1...COM99)

	// retrieve RX timeout...
	long rx_timeout;					// 0: no delay, nothing to read,
	rx_timeout = atol(argv[3]);			// >0: delay and something to read.

	// open communication port...
	if (!Serial.begin(comm_path)) // fail open COMnn ?
	{
		errcode = 2;
		errcstr = (const char *) & "#invalid comm_port";
		goto _exit;
	}

	if (options.debug) printf("<!--%s:%li millis:%li-->\n",  __PROG__, __LINE__, millis());

	// clear Serial RX...
	while (Serial.read() != -1) {}

	if (options.debug) printf("<!--%s:%li millis:%li-->\n",  __PROG__, __LINE__, millis());

	// arguments to write ?
	if (argc > 4)
	{
		// write <0> to invite Arduino to clear RX buffer...
		Serial.write('\0');

		// write arguments...
		for (int i=4; i<argc; i++)
		{
			// if more than 1 argument to write, insert a SP delimiter...
			if (i > 4)
			{
				// write SP delimiter...
				Serial.write(' ');
			}

			// write argument...
			Serial.write(argv[i]);
		}

		// write LF...
		Serial.write('\n');
	}

	if (options.debug) printf("<!--%s:%li millis:%li-->\n",  __PROG__, __LINE__, millis());

	// read answer ?
	if (rx_timeout > 0)
	{
		uint32_t cccc = 0;				// shr last 4 read chars
		int cccc_n = 0;					// count of chars in cccc (max 4)

		long rx_millis1 = millis();		// start time for() loop
		long rx_timeout1;				// calculated rest of RX timeout

		for (;;)
		{
			// calculate rest of RX timeout...
			rx_timeout1 = (rx_timeout + rx_millis1 - millis());

			// RX timeout elapsed ?
			if (rx_timeout1 < 0) // elapsed ?
			{
				// flush cccc to Console...
				// align cccc to right...
				for (int i=0; i<(cccc_n-4); i++) cccc >>= 8;
				// write cccc_n chars to Console...
				for (int i=0; i<cccc_n; i++) Console.write((uint8_t) cccc);

				errcode = 3;
				errcstr = (const char *) & "#RX timeout";
				goto _exit;
			}

			// apply rx_timeout1...
			Serial._timeouts.ReadTotalTimeoutConstant = (DWORD) rx_timeout1;

			// read next available char...
			int c = Serial.read();
			if (c == -1) continue; // loop immediately if no available char ?

			// shift cccc...
			if (cccc_n == 4) // cccc full?
				Console.write((uint8_t) cccc); // write fifo cccc char to Serial
			else
				cccc_n++; // add char to cccc
			//
			cccc = c<<24 | cccc>>8;		// shift cccc and concat last char

			// check Ok or ER signature...
			if (memcmp(&cccc,_OK_,4) == 0) // OK ?
			{
				errcode = 0;
				errcstr = NULL;
				goto _exit;				// end RX with no error.
			}
			else
			if (memcmp(&cccc,_ER_,4) == 0) // ER ?
			{
				errcode = 4;
				errcstr = (const char *) & "#RX error";
				goto _exit;				// end RX with error.
			}
		}
	}

_exit:

	// print encountered error...
	if (errcstr) printf("<!--%s-->\n", errcstr); // error message

	// close Serial...
	if (Serial) Serial.end();

	// debug millis()...
	if (options.debug) printf("<!--%s:%li millis:%li-->\n",  __PROG__, __LINE__, millis());

	// return code error...
	return errcode;
}
