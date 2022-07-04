#pragma once
#define VE_SCANCODE_MASK (1<<30)
#define VE_SCANCODE_TO_KEYCODE(X)  (X | VE_SCANCODE_MASK)

namespace Vortex
{
	using KeyCode = int32_t;

	namespace Key
	{
		enum : KeyCode
		{
            UNKNOWN = 0,

            RETURN = '\r',
            ESC = '\x1B',
            BACKSPACE = '\b',
            TAB = '\t',
            SPACE = ' ',
            EXCLAIM = '!',
            QUOTEDBL = '"',
            HASH = '#',
            PERCENT = '%',
            DOLLAR = '$',
            AMPERSAND = '&',
            QUOTE = '\'',
            LEFTPAREN = '(',
            RIGHTPAREN = ')',
            ASTERISK = '*',
            PLUS = '+',
            COMMA = ',',
            MINUS = '-',
            PERIOD = '.',
            SLASH = '/',
            D0 = '0',
            D1 = '1',
            D2 = '2',
            D3 = '3',
            D4 = '4',
            D5 = '5',
            D6 = '6',
            D7 = '7',
            D8 = '8',
            D9 = '9',
            COLON = ':',
            SEMICOLON = ';',
            LESS = '<',
            EQUALS = '=',
            GREATER = '>',
            QUESTION = '?',
            AT = '@',

            LEFTBRACKET = '[',
            BACKSLASH = '\\',
            RIGHTBRACKET = ']',
            CARET = '^',
            UNDERSCORE = '_',
            BACKQUOTE = '`',
            A = 'a',
            B = 'b',
            C = 'c',
            D = 'd',
            E = 'e',
            F = 'f',
            G = 'g',
            H = 'h',
            I = 'i',
            J = 'j',
            K = 'k',
            L = 'l',
            M = 'm',
            N = 'n',
            O = 'o',
            P = 'p',
            Q = 'q',
            R = 'r',
            S = 's',
            T = 't',
            U = 'u',
            V = 'v',
            W = 'w',
            X = 'x',
            Y = 'y',
            Z = 'z',

            CAPSLOCK = VE_SCANCODE_TO_KEYCODE(57),

            F1 = VE_SCANCODE_TO_KEYCODE(58),
            F2 = VE_SCANCODE_TO_KEYCODE(59),
            F3 = VE_SCANCODE_TO_KEYCODE(60),
            F4 = VE_SCANCODE_TO_KEYCODE(61),
            F5 = VE_SCANCODE_TO_KEYCODE(62),
            F6 = VE_SCANCODE_TO_KEYCODE(63),
            F7 = VE_SCANCODE_TO_KEYCODE(64),
            F8 = VE_SCANCODE_TO_KEYCODE(65),
            F9 = VE_SCANCODE_TO_KEYCODE(66),
            F10 = VE_SCANCODE_TO_KEYCODE(67),
            F11 = VE_SCANCODE_TO_KEYCODE(68),
            F12 = VE_SCANCODE_TO_KEYCODE(69),

            PRINTSCREEN = VE_SCANCODE_TO_KEYCODE(70),
            SCROLLLOCK = VE_SCANCODE_TO_KEYCODE(71),
            PAUSE = VE_SCANCODE_TO_KEYCODE(72),
            INSERT = VE_SCANCODE_TO_KEYCODE(73),
            HOME = VE_SCANCODE_TO_KEYCODE(74),
            PAGEUP = VE_SCANCODE_TO_KEYCODE(75),
            DEL = '\x7F',
            END = VE_SCANCODE_TO_KEYCODE(77),
            PAGEDOWN = VE_SCANCODE_TO_KEYCODE(78),
            RIGHT = VE_SCANCODE_TO_KEYCODE(79),
            LEFT = VE_SCANCODE_TO_KEYCODE(80),
            DOWN = VE_SCANCODE_TO_KEYCODE(81),
            UP = VE_SCANCODE_TO_KEYCODE(82),

            NUMLOCKCLEAR = VE_SCANCODE_TO_KEYCODE(83),
            KP_DIVIDE = VE_SCANCODE_TO_KEYCODE(84),
            KP_MULTIPLY = VE_SCANCODE_TO_KEYCODE(85),
            KP_MINUS = VE_SCANCODE_TO_KEYCODE(86),
            KP_PLUS = VE_SCANCODE_TO_KEYCODE(87),
            KP_ENTER = VE_SCANCODE_TO_KEYCODE(88),
            KP_1 = VE_SCANCODE_TO_KEYCODE(89),
            KP_2 = VE_SCANCODE_TO_KEYCODE(90),
            KP_3 = VE_SCANCODE_TO_KEYCODE(91),
            KP_4 = VE_SCANCODE_TO_KEYCODE(92),
            KP_5 = VE_SCANCODE_TO_KEYCODE(93),
            KP_6 = VE_SCANCODE_TO_KEYCODE(94),
            KP_7 = VE_SCANCODE_TO_KEYCODE(95),
            KP_8 = VE_SCANCODE_TO_KEYCODE(96),
            KP_9 = VE_SCANCODE_TO_KEYCODE(97),
            KP_0 = VE_SCANCODE_TO_KEYCODE(98),
            KP_PERIOD = VE_SCANCODE_TO_KEYCODE(99),

            APPLICATION = VE_SCANCODE_TO_KEYCODE(101),
            POWER = VE_SCANCODE_TO_KEYCODE(102),
            KP_EQUALS = VE_SCANCODE_TO_KEYCODE(103),
            F13 = VE_SCANCODE_TO_KEYCODE(104),
            F14 = VE_SCANCODE_TO_KEYCODE(105),
            F15 = VE_SCANCODE_TO_KEYCODE(106),
            F16 = VE_SCANCODE_TO_KEYCODE(107),
            F17 = VE_SCANCODE_TO_KEYCODE(108),
            F18 = VE_SCANCODE_TO_KEYCODE(109),
            F19 = VE_SCANCODE_TO_KEYCODE(110),
            F20 = VE_SCANCODE_TO_KEYCODE(111),
            F21 = VE_SCANCODE_TO_KEYCODE(112),
            F22 = VE_SCANCODE_TO_KEYCODE(113),
            F23 = VE_SCANCODE_TO_KEYCODE(114),
            F24 = VE_SCANCODE_TO_KEYCODE(115),
            EXECUTE = VE_SCANCODE_TO_KEYCODE(116),
            HELP = VE_SCANCODE_TO_KEYCODE(117),
            MENU = VE_SCANCODE_TO_KEYCODE(118),
            SELECT = VE_SCANCODE_TO_KEYCODE(119),
            STOP = VE_SCANCODE_TO_KEYCODE(120),
            AGAIN = VE_SCANCODE_TO_KEYCODE(121),
            UNDO = VE_SCANCODE_TO_KEYCODE(122),
            CUT = VE_SCANCODE_TO_KEYCODE(123),
            COPY = VE_SCANCODE_TO_KEYCODE(124),
            PASTE = VE_SCANCODE_TO_KEYCODE(125),
            FIND = VE_SCANCODE_TO_KEYCODE(126),
            MUTE = VE_SCANCODE_TO_KEYCODE(127),
            VOLUMEUP = VE_SCANCODE_TO_KEYCODE(128),
            VOLUMEDOWN = VE_SCANCODE_TO_KEYCODE(129),
            KP_COMMA = VE_SCANCODE_TO_KEYCODE(133),
            KP_EQUALSAS400 = VE_SCANCODE_TO_KEYCODE(134),

            ALTERASE = VE_SCANCODE_TO_KEYCODE(153),
            SYSREQ = VE_SCANCODE_TO_KEYCODE(154),
            CANCEL = VE_SCANCODE_TO_KEYCODE(155),
            CLEAR = VE_SCANCODE_TO_KEYCODE(156),
            PRIOR = VE_SCANCODE_TO_KEYCODE(157),
            RETURN2 = VE_SCANCODE_TO_KEYCODE(158),
            SEPARATOR = VE_SCANCODE_TO_KEYCODE(159),
            KOUT = VE_SCANCODE_TO_KEYCODE(160),
            OPER = VE_SCANCODE_TO_KEYCODE(161),
            CLEARAGAIN = VE_SCANCODE_TO_KEYCODE(162),
            CRSEL = VE_SCANCODE_TO_KEYCODE(163),
            EXSEL = VE_SCANCODE_TO_KEYCODE(164),

            KP_00 = VE_SCANCODE_TO_KEYCODE(176),
            KP_000 = VE_SCANCODE_TO_KEYCODE(177),
            THOUSANDSSEPARATOR = VE_SCANCODE_TO_KEYCODE(178),
            DECIMALSEPARATOR = VE_SCANCODE_TO_KEYCODE(179),
            CURRENCYUNIT = VE_SCANCODE_TO_KEYCODE(180),
            CURRENCYSUBUNIT = VE_SCANCODE_TO_KEYCODE(181),
            KP_LEFTPAREN = VE_SCANCODE_TO_KEYCODE(182),
            KP_RIGHTPAREN = VE_SCANCODE_TO_KEYCODE(183),
            KP_LEFTBRACE = VE_SCANCODE_TO_KEYCODE(184),
            KP_RIGHTBRACE = VE_SCANCODE_TO_KEYCODE(185),
            KP_TAB = VE_SCANCODE_TO_KEYCODE(186),
            KP_BACKSPACE = VE_SCANCODE_TO_KEYCODE(187),
            KP_A = VE_SCANCODE_TO_KEYCODE(188),
            KP_B = VE_SCANCODE_TO_KEYCODE(189),
            KP_C = VE_SCANCODE_TO_KEYCODE(190),
            KP_D = VE_SCANCODE_TO_KEYCODE(191),
            KP_E = VE_SCANCODE_TO_KEYCODE(192),
            KP_F = VE_SCANCODE_TO_KEYCODE(193),
            KP_XOR = VE_SCANCODE_TO_KEYCODE(194),
            KP_POWER = VE_SCANCODE_TO_KEYCODE(195),
            KP_PERCENT = VE_SCANCODE_TO_KEYCODE(196),
            KP_LESS = VE_SCANCODE_TO_KEYCODE(197),
            KP_GREATER = VE_SCANCODE_TO_KEYCODE(198),
            KP_AMPERSAND = VE_SCANCODE_TO_KEYCODE(199),
            KP_DBLAMPERSAND = VE_SCANCODE_TO_KEYCODE(200),
            KP_VERTICALBAR = VE_SCANCODE_TO_KEYCODE(201),
            KP_DBLVERTICALBAR = VE_SCANCODE_TO_KEYCODE(202),
            KP_COLON = VE_SCANCODE_TO_KEYCODE(203),
            KP_HASH = VE_SCANCODE_TO_KEYCODE(204),
            KP_SPACE = VE_SCANCODE_TO_KEYCODE(205),
            KP_AT = VE_SCANCODE_TO_KEYCODE(206),
            KP_EXCLAM = VE_SCANCODE_TO_KEYCODE(207),
            KP_MEMSTORE = VE_SCANCODE_TO_KEYCODE(208),
            KP_MEMRECALL = VE_SCANCODE_TO_KEYCODE(209),
            KP_MEMCLEAR = VE_SCANCODE_TO_KEYCODE(210),
            KP_MEMADD = VE_SCANCODE_TO_KEYCODE(211),
            KP_MEMSUBTRACT = VE_SCANCODE_TO_KEYCODE(212),
            KP_MEMMULTIPLY = VE_SCANCODE_TO_KEYCODE(213),
            KP_MEMDIVIDE = VE_SCANCODE_TO_KEYCODE(214),
            KP_PLUSMINUS = VE_SCANCODE_TO_KEYCODE(215),
            KP_CLEAR = VE_SCANCODE_TO_KEYCODE(216),
            KP_CLEARENTRY = VE_SCANCODE_TO_KEYCODE(217),
            KP_BINARY = VE_SCANCODE_TO_KEYCODE(218),
            KP_OCTAL = VE_SCANCODE_TO_KEYCODE(219),
            KP_DECIMAL = VE_SCANCODE_TO_KEYCODE(220),
            KP_HEXADECIMAL = VE_SCANCODE_TO_KEYCODE(221),

            LCTRL = VE_SCANCODE_TO_KEYCODE(224),
            LSHIFT = VE_SCANCODE_TO_KEYCODE(225),
            LALT = VE_SCANCODE_TO_KEYCODE(226),
            LGUI = VE_SCANCODE_TO_KEYCODE(227),
            RCTRL = VE_SCANCODE_TO_KEYCODE(228),
            RSHIFT = VE_SCANCODE_TO_KEYCODE(229),
            RALT = VE_SCANCODE_TO_KEYCODE(230),
            RGUI = VE_SCANCODE_TO_KEYCODE(231),

            MODE = VE_SCANCODE_TO_KEYCODE(257),

            AUDIONEXT = VE_SCANCODE_TO_KEYCODE(258),
            AUDIOPREV = VE_SCANCODE_TO_KEYCODE(259),
            AUDIOSTOP = VE_SCANCODE_TO_KEYCODE(260),
            AUDIOPLAY = VE_SCANCODE_TO_KEYCODE(261),
            AUDIOMUTE = VE_SCANCODE_TO_KEYCODE(262),
            MEDIASELECT = VE_SCANCODE_TO_KEYCODE(263),
            WWW = VE_SCANCODE_TO_KEYCODE(264),
            MAIL = VE_SCANCODE_TO_KEYCODE(265),
            CALCULATOR = VE_SCANCODE_TO_KEYCODE(266),
            COMPUTER = VE_SCANCODE_TO_KEYCODE(267),
            AC_SEARCH = VE_SCANCODE_TO_KEYCODE(268),
            AC_HOME = VE_SCANCODE_TO_KEYCODE(269),
            AC_BACK = VE_SCANCODE_TO_KEYCODE(270),
            AC_FORWARD = VE_SCANCODE_TO_KEYCODE(271),
            AC_STOP = VE_SCANCODE_TO_KEYCODE(272),
            AC_REFRESH = VE_SCANCODE_TO_KEYCODE(273),
            AC_BOOKMARKS = VE_SCANCODE_TO_KEYCODE(274),

            BRIGHTNESSDOWN = VE_SCANCODE_TO_KEYCODE(275),
            BRIGHTNESSUP = VE_SCANCODE_TO_KEYCODE(276),
            DISPLAYSWITCH = VE_SCANCODE_TO_KEYCODE(277),
            KBDILLUMTOGGLE = VE_SCANCODE_TO_KEYCODE(278),
            KBDILLUMDOWN = VE_SCANCODE_TO_KEYCODE(279),
            KBDILLUMUP = VE_SCANCODE_TO_KEYCODE(280),
            EJECT = VE_SCANCODE_TO_KEYCODE(281),
            SLEEP = VE_SCANCODE_TO_KEYCODE(282),
            APP1 = VE_SCANCODE_TO_KEYCODE(283),
            APP2 = VE_SCANCODE_TO_KEYCODE(284),

            AUDIOREWIND = VE_SCANCODE_TO_KEYCODE(285),
            AUDIOFASTFORWARD = VE_SCANCODE_TO_KEYCODE(286)
		};
	}

    namespace Controller
    {
        enum : KeyCode
        {
            BUTTON_INVALID = -1,
            BUTTON_A,
            BUTTON_B,
            BUTTON_X,
            BUTTON_Y,
            BUTTON_BACK,
            BUTTON_GUIDE,
            BUTTON_START,
            BUTTON_LEFTSTICK,
            BUTTON_RIGHTSTICK,
            BUTTON_LEFTSHOULDER,
            BUTTON_RIGHTSHOULDER,
            BUTTON_DPAD_UP,
            BUTTON_DPAD_DOWN,
            BUTTON_DPAD_LEFT,
            BUTTON_DPAD_RIGHT,
            BUTTON_MISC1,    /* Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button, Amazon Luna microphone button */
            BUTTON_PADDLE1,  /* Xbox Elite paddle P1 */
            BUTTON_PADDLE2,  /* Xbox Elite paddle P3 */
            BUTTON_PADDLE3,  /* Xbox Elite paddle P2 */
            BUTTON_PADDLE4,  /* Xbox Elite paddle P4 */
            BUTTON_TOUCHPAD, /* PS4/PS5 touchpad button */
            BUTTON_MAX
        };
    }
}