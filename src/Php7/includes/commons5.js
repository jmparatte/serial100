//éèà

// 20140404 +is_numeric()
// 20131112
// 20120628
// 20120622
// 20120612


//==============================================================================


var _UNDEFINED_ =	'(undefined)';
var _NULL_ =		'(NULL)';
var _NAN_ =			'(NaN)';
var _EMPTY_ =		'';

//------------------------------------------------------------------------------

//define( 'BLACK',		'#000000' );
//define( 'RED',		'#ff0000' );
//define( 'GREEN',		'#008000' );
//define( 'LIME',		'#00ff00' );
//define( 'BLUE',		'#0000ff' );
//define( 'GRAY50',		'#777777' );
//define( 'GRAY',		'#808080' );
//define( 'GREY',		'#808080' );
//define( 'WHITE',		'#ffffff' );
//define( 'CYAN',		'#00ffff' );
//define( 'MAGENTA',	'#ff00ff' );
//define( 'YELLOW',		'#ffff00' );

//------------------------------------------------------------------------------

var NUL =	'\x00';		// 00	Null character
var CC =	'\x03';		// 03	Ctrl-C
var CTRC =	'\x03';		// 03	Ctrl-C
var CTRLC =	'\x03';		// 03	Ctrl-C
var BEL =	'\x07';		// 07	Bell
var BSP =	'\x08';		// 08	Back-Space character
var HT =	'\t';		// 09	Horizontal Tabulation
var LF =	'\n';		// 0A	Line-Feed
var CR =	'\r';		// 0D	Carriage-Return
var CZ =	'\x1A';		// 1A	Ctrl-Z
var CTRZ =	'\x1A';		// 1A	Ctrl-Z
var CTRLZ =	'\x1A';		// 1A	Ctrl-Z
var ESC =	'\x1B';		// 1B	Escape character
var SP =	' ';		// 20	Space character
var SPC =	' ';		// 20	Space character
var DQT =	'"';		// 22	Double-Quote character
var SQT =	"'";		// 27	Single-Quote character
var BQT =	'`';		// 60	Back-Quote character
var DEL =	'\x7F';		// 7F	Delete character
var NB =	'\xA0';		// A0	  ANSI Non-Breakable space character
var PC =	'\xB6';		// B6	¶ ANSI Pied de mouche
var MD =	'\xB7';		// B7	· ANSI Point médian
// http://www.php.net/manual/en/language.types.string.php#language.types.string.syntax.double :
// Given that PHP does not dictate a specific encoding for strings, one might wonder how string literals are encoded. For instance, is the string "á" equivalent to "\xE1" (ISO-8859-1), "\xC3\xA1" (UTF-8, C form), "\x61\xCC\x81" (UTF-8, D form) or any other possible representation? The answer is that string will be encoded in whatever fashion it is encoded in the script file. Thus, if the script is written in ISO-8859-1, the string will be encoded in ISO-8859-1 and so on. However, this does not apply if Zend Multibyte is enabled; in that case, the script may be written in an arbitrary encoding (which is explicity declared or is detected) and then converted to a certain internal encoding, which is then the encoding that will be used for the string literals. Note that there are some constraints on the encoding of the script (or on the internal encoding, should Zend Multibyte be enabled) – this almost always means that this encoding should be a compatible superset of ASCII, such as UTF-8 or ISO-8859-1. Note, however, that state-dependent encodings where the same byte values can be used in initial and non-initial shift states may be problematic.
// http://php.net/manual/en/regexp.reference.escape.php :
// After "\x", up to two hexadecimal digits are read (letters can be in upper or lower case). In UTF-8 mode, "\x{...}" is allowed, where the contents of the braces is a string of hexadecimal digits. It is interpreted as a UTF-8 character whose code number is the given hexadecimal number. The original hexadecimal escape sequence, \xhh, matches a two-byte UTF-8 character if the value is greater than 127.

var NL =	'\n';		// Unix/Linux New-Line string
var NewLine = '\n';		// Unix/Linux New-Line string

var NBSP =	'&nbsp;';	// HTML Non-Breakable space character
var PILCROW = '&para;';	// B6	¶ ANSI Pied de mouche
var MIDDOT = '&middot;';// B7	· ANSI Point médian
var BR =	'<br />';	// HTML Break line
var HR =	'<hr />';	// HTML Horizontal line

//------------------------------------------------------------------------------

var STREAM_TYPE_CONTENT = 'application/octet-stream';
var XLS_TYPE_CONTENT = 'application/vnd.ms-excel';
var XLSX_TYPE_CONTENT = 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet';

//------------------------------------------------------------------------------

var DIV = '<div>';
var _DIV = '</div>';
var P = '<p>';
var _P = '</p>';
var SPAN = '<span>';
var _SPAN = '</span>';
var B = '<b>';
var _B = '</b>';
var I = '<i>';
var _I = '</i>';
var U = '<u>';
var _U = '</u>';

var CODE = '<code>';
var _CODE = '</code>';
var KBD = '<kbd>';
var _KBD = '</kbd>';
var PRE = '<pre>';
var _PRE = '</pre>';

var H1 = '<h1>';
var _H1 = '</h1>';
var H2 = '<h2>';
var _H2 = '</h2>';
var H3 = '<h3>';
var _H3 = '</h3>';
var H4 = '<h4>';
var _H4 = '</h4>';
var H5 = '<h5>';
var _H5 = '</h5>';
var H6 = '<h6>';
var _H6 = '</h6>';

var TABLE = '<table>';
var _TABLE = '</table>';
var TR = '<tr>';
var _TR = '</tr>';
var TH = '<th>';
var _TH = '</th>';
var TD = '<td>';
var _TD = '</td>';


//==============================================================================


function ne(v,e){return v == null ? (e == null ? '' : e) : v;}
function en(v,n){return v == '' ? (n == null ? null : n) : v;}

function nz(v,z){return v == null ? (z == null ? 0 : z) : v;}
function zn(v,n){return v == 0 ? (n == null ? null : n) : v;}

function nf(v,f){return v == null ? (f == null ? false : f) : v;}
function fn(v,n){return v == false ? (n == null ? null : n) : v;}

function ez(e,z){return e == '' ? (z == null ? 0 : z) : e;}
function ze(z,e){return z == 0 ? (e == null ? '' : e) : z;}


//==============================================================================


/*	Miscellaneous functions with equivalent in PHP
	==============================================	*/

function is_numeric( v ) { // PHP bool is_numeric ( mixed $var )

	return !isNaN(v);
}

function urlencode( str ) { // PHP string urlencode ( string $str ) // RFC 1738 MIME application/x-www-form-urlencoded

//	return escape( str ).replace( /\+/g, '%2B' ).replace( /%20/g, '+' );
//	return encodeURI( str ).replace( /[;]/g, '%3B' ).replace( /[+]/g, '%2B' ).replace( /[ ]/g, '+' );
	return (
		encodeURIComponent( str )
		.replace( /!/g, '%21' )
		.replace( /'/g, '%27' )
		.replace( /\(/g, '%28' )
		.replace( /\)/g, '%29' )
		.replace( /\*/g, '%2A' )
		.replace( /%20/g, '+' )
	);
}

function urldecode( str ) { // PHP string urldecode ( string $str ) // RFC 1738 MIME application/x-www-form-urlencoded

//	return unescape( str.replace( /\+/g, '%20' ) );
//	return decodeURI( str.replace( /[+]/g, ' ' ).replace( /[%]2B]/g, '+' ).replace( /[%]3B/g, ';' ) );
	return decodeURIComponent(
		str
		.replace( /\+/g, '%20' )
		.replace( /%2A/g, '*' )
		.replace( /%29/g, ')' )
		.replace( /%28/g, '(' )
		.replace( /%27/g, '\'' )
		.replace( /%21/g, '!' )
	);
}

function microtime_us() { // PHP mixed microtime ([ bool $get_as_float = false ] ) // microtime(true)*1000000

	return (new Date()).getTime();
}


//==============================================================================


function utf8_to_char (utftext) { // PHP string utf8_to_char ( string $data )

	var string = "";
	var i=0;
	var c1=c2=c3=0;
	while (i < utftext.length)
	{
		c1 = utftext.charCodeAt(i++);
		if (c1<128)
		{
			string += String.fromCharCode(c1);
		}
		else
		if (c1<192)
		{
			string += String.fromCharCode(c1);
		}
		else
		if (c1<224)
		{
			c2 = utftext.charCodeAt(i++);
			string += String.fromCharCode(((c1&31)<<6)|(c2&63));
		}
		else
		{
			c2 = utftext.charCodeAt(i++);
			c3 = utftext.charCodeAt(i++);
			string += String.fromCharCode(((c1&15)<<12) | ((c2&63)<<6) | (c3&63));
		}
	}
	return string;
}

function char_to_utf8 (string) { // PHP string char_to_utf8 ( string $data )

//	string = string.replace(/\r\n/g,"\n");
	var utftext = "";
	for (var n=0; n<string.length; n++)
	{
		var c = string.charCodeAt(n);
		if (c<128)
		{
			utftext += String.fromCharCode(c);
		}
		else
		if (c<2048)
		{
			utftext += String.fromCharCode((c>>6)|192);
			utftext += String.fromCharCode((c&63)|128);
		}
		else
		{
			utftext += String.fromCharCode((c>>12)|224);
			utftext += String.fromCharCode(((c>>6)&63)|128);
			utftext += String.fromCharCode((c&63)|128);
		};
	}
//echo('utf8:26:'+string+','+utftext);
	return utftext;
}

//------------------------------------------------------------------------------

function cookie_escape( string ) {

	return (

		string.

		replace( /[%]/g, '%25' ).

		replace( /\t/g, '%09' ).
		replace( /\n/g, '%0a' ).
		replace( /\v/g, '%0b' ).
		replace( /\f/g, '%0c' ).
		replace( /\r/g, '%0d' ).

		replace( /[+]/g, '%2b' ).
		replace( /[,]/g, '%2c' ).
		replace( /[;]/g, '%3b' ).
		replace( /[=]/g, '%3d' ).

		replace( /[ ]/g, '+' )
	);

//	return escape( string ).replace( /[%]20/g, '+' );
}

function cookie_unescape( string ) {

	return (

		string.

		replace( /[+]/g, ' ' ).

		replace( /%3d/g, '=' ).
		replace( /%3b/g, ';' ).
		replace( /%2c/g, ',' ).
		replace( /%2b/g, '+' ).

		replace( /%0d/g, '\x0d' ).
		replace( /%0c/g, '\x0c' ).
		replace( /%0b/g, '\x0b' ).
		replace( /%0a/g, '\x0a' ).
		replace( /%09/g, '\x09' ).

		replace( /%25/g, '%' )
	);

//	return unescape( string.replace( /[+]/g, '%20' ) );
}

//------------------------------------------------------------------------------

function setrawcookie( name, value, expire, path, domain, secure ) { // PHP bool setrawcookie ( string $name [, string $value [, int $expire = 0 [, string $path [, string $domain [, bool $secure = false [, bool $httponly = false ]]]]]] )

	//alert([name,value]);
	//alert([name,value,expire.toUTCString()]);

	document.cookie = (
		( name + '=' + ( value != '' ? value : '_EMPTY_' ) ) +
		( expire ? "; expires=" + expire.toUTCString() : '' ) +
		( path ? "; path=" + path:'' ) +
		( domain ? "; domain=" + domain : '' ) +
		( secure ? "; secure" : '' )
//		( name + '=' + value + ';' ) +
//		( expire ? 'expires=' + expire.toUTCString() + ';' : '' ) +
//		( path ? 'path=' + path + ';' : '' ) +
//		( domain ? 'domain=' + domain + ';' : '' ) +
//		( secure ? 'secure' + ';' : '' )
	);
}

function getrawcookie( name ) { // PHP equivalent doesn't exist !

	var a = document.cookie.match( /[^;]+|; */g );

	if( a==null ) return;

	var cookies = {};

	for( var i=0; i<a.length; i+=2 ) {

		var j = a[i].indexOf('=');
		var n = j>=0 ? a[i].substr(0,j) : a[i];
		var v = j>=0 ? a[i].substr(j+1) : null;
		cookies[n] = v;
	}

	if( name != null ) {
		var value = cookies[name];
		if( value == '_EMPTY_' ) value = '';
		return value;
	}
	else
		return cookies;
}

function delcookie( name ) {

	setcookie( name, null, new Date(0) );
}

//------------------------------------------------------------------------------

function seturlcookie( name, value, expire, path, domain, secure ) {

//	setrawcookie( name, cookie_escape( value ), expire, path, domain, secure );
//	setrawcookie( name, cookie_escape( char_to_utf8( value ) ), expire, path, domain, secure );
	setrawcookie( name, urlencode( value ), expire, path, domain, secure );
}

function geturlcookie( name ) {

//	return cookie_unescape( getrawcookie(name) );
//	return utf8_to_char( cookie_unescape( getrawcookie(name) ) );
	return urldecode( getrawcookie(name) );
}


//==============================================================================


function htmlspecialchars( text ) // PHP string htmlspecialchars ( string $string [, int $flags = ENT_COMPAT | ENT_HTML401 [, string $encoding = 'UTF-8' [, bool $double_encode = true ]]] )
{
	return (
		text
		.toString()
		.replace( /\&/g, '&amp;' )
		.replace( /\"/g, '"' )
		.replace( /\</g, '&lt;' )
		.replace( /\>/g, '&gt;' )
	);
}

function plain( text ) // 2018-08-11
{
	return htmlspecialchars( text );
}

function _plain(...texts) // 2018-08-11
{
	plain = "";
	for (var index in texts) {
		var text = texts[index];
		plain += (/^<.*>\r?\n?$/.test(text) ? text : plain(text));
	}
	return plain;
}

//function html( $text ) { // common5.php
//	return str_replace( NL, BR.NL, htmlspecialchars($text) ); //htmlentities
//}
function html( text )
{
	return htmlspecialchars( text ).replace( /\r?\n/g, BR+NL ); //htmlentities
}

function _html(...texts) // 2018-01-16
{
	html = "";
	for (var index in texts) {
		var text = texts[index];
//		html += (preg_match('/^<.*>\r?\n?$/', text)===1 ? text : htmlspecialchars(text));
		html += (/^<.*>\r?\n?$/.test(text) ? text : htmlspecialchars(text));
	}
	return html;
}

function __h(...texts) // 2018-02-17
{
	return _html(...texts);
}

function __e(...texts) // 2018-02-17
{
	document.write( _html(...texts) );
}

//==============================================================================


function json_encode( value ) { // PHP string json_encode ( mixed $value [, int $options = 0 ] )

	if( this.JSON==null ) throw "JSON object is missing! ";
	return JSON.stringify( value );
}

function json_decode( json ) { // PHP mixed json_decode ( string $json [, bool $assoc = false [, int $depth = 512 [, int $options = 0 ]]] )

//	if( this.JSON==null ) throw "JSON object is missing! ";
	if( this.JSON==null )
	return(
		eval(
			'(function(){return ' +
			json +
			';})()'
		)
	);
	else
	return JSON.parse( json );
}


//==============================================================================


/*	XMLHttpRequest
	==============	*/

function http_new() {

	var http;

	if( window.XMLHttpRequest )
		http = new XMLHttpRequest(); // code for IE7+, Firefox, Chrome, Opera, Safari
	else
		http = new ActiveXObject( "Microsoft.XMLHTTP" ); // code for IE6, IE5, HTA, WSF

	return http;
}

function http_get_text( http, url ) {

	if (!http) return "#http object error";

	http.open( "GET", url, false );
//	http.setRequestHeader( "Content-Type", "text/plain; charset=UTF-8" );
	http.send();

	if( http.status == 200 ) // OK ?
		return http.responseText;
	else
		return '#' + http.status + ' - ' + http.statusText;
}


//==============================================================================


function isset( ...mixed ) // PHP bool isset ( mixed $var [, mixed $... ] )
{
	for (var index in mixed) if (mixed[index] == null) return false;
	return true;
}


//==============================================================================


//End.