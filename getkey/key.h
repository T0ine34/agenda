#ifndef __MENU_KEY_H__
#define __MENU_KEY_H__
enum Key{
    A = 1,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
    a = 31,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,
    ZERO = 61,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,
    SPACE = 71,ENTER,ESC,DEL,BACKSPACE,TAB,ESCAPE,_DELETE,
    ARROW_UP = 81,ARROW_DOWN,ARROW_LEFT,ARROW_RIGHT,
    NUMPAD_ARROW_UP = 86,NUMPAD_ARROW_DOWN,NUMPAD_ARROW_LEFT,NUMPAD_ARROW_RIGHT,
    F1 = 91,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,
    NUMPAD_ZERO = 101,NUMPAD_ONE,NUMPAD_TWO,NUMPAD_THREE,NUMPAD_FOUR,NUMPAD_FIVE,NUMPAD_SIX,NUMPAD_SEVEN,NUMPAD_EIGHT,NUMPAD_NINE,
    NUMPAD_PLUS = 111,NUMPAD_MINUS,NUMPAD_MULTIPLY,NUMPAD_DIVIDE,NUMPAD_ENTER,NUMPAD_DOT,
    PAGE_UP = 121,PAGE_DOWN,HOME,END,INSERT,
    _POINT = 131,COMMA,SEMICOLON,QUOTE,SLASH,BACKSLASH,OPEN_BRACKET,CLOSE_BRACKET,
    UNDERSCORE = 141,DASH,PLUS,ASTERISK,PERCENT,EXCLAMATION,QUESTION,AT,POUND,DOLLAR,AMPERSAND,PIPE,

    E_GRAVE = 161,E_ACUTE,E_CIRCUMFLEX,E_UMLAUT,E_TILDE,
    A_GRAVE = 166,A_ACUTE,A_CIRCUMFLEX,A_UMLAUT,A_TILDE,
    O_GRAVE = 171,O_ACUTE,O_CIRCUMFLEX,O_UMLAUT,O_TILDE,
    U_GRAVE = 176,U_ACUTE,U_CIRCUMFLEX,U_UMLAUT,U_TILDE,
    I_GRAVE = 181,I_ACUTE,I_CIRCUMFLEX,I_UMLAUT,I_TILDE,
    C_CEDILLA = 186,AE,OE,

    e_GRAVE = 191,e_ACUTE,e_CIRCUMFLEX,e_UMLAUT,e_TILDE,
    a_GRAVE = 196,a_ACUTE,a_CIRCUMFLEX,a_UMLAUT,a_TILDE,
    o_GRAVE = 201,o_ACUTE,o_CIRCUMFLEX,o_UMLAUT,o_TILDE,
    u_GRAVE = 206,u_ACUTE,u_CIRCUMFLEX,u_UMLAUT,u_TILDE,
    i_GRAVE = 211,i_ACUTE,i_CIRCUMFLEX,i_UMLAUT,i_TILDE,
    c_CEDILLA = 216,ae,oe,

    UNKNOWN = 0,
    UNDEFINED = -1
};

#endif