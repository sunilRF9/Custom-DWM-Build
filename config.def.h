/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 1;        /* gaps between windows */
static const unsigned int snap      = 64;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {"xos4 Terminus: Regular:size=14", "pango monospace: size=14"};
static const char dmenufont[]       = "xos4 Terminus: Regular:size=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_cyan2[]       = "#002A35";
static const char col_green[]       = "#98971a";
static const char col_green2[]      = "#689d6a";
static const char col_red[]         = "#458588";
static const char col_red2[]        = "#ebdbb2";
static const char col_red3[]        = "#d08770";
static const char col_red4[]        = "#928374";
static const char col_red5[]        = "#eaaaef";
static const char col_red6[]        = "#b71c1c";
static const char col_yellow[]      = "#fabd2f";
static const char col_yellow2[]     = "#D79921";
static const char col_yellow1[]     = "#83a598";
static const char col_purple[]      = "#76199e";
static const char col_orange[]      = "#F22200";
static const char col_fluro[]       = "#be0";
static const char col_fluro2[]      = "#2aa198";
static const char col_fluro3[]      = "#123943";
static const char col_grey9[]       = "#2F2F2F";
static const char col_black[]       = "#000000";
static const char col_base[]       =  "#d33682";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan2,col_fluro},
	[SchemeStatus]  = { col_fluro2,col_cyan2, "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = {col_gray1,col_fluro, "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = {col_fluro2,col_fluro3,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_fluro2,col_cyan2,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_gray4,col_fluro3,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
 
};
static const char *tags[] = {"1","2","3","4","5","6","7","8","9"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           0,           -1 },
	{ NULL, NULL, "hidden", SCRATCHPAD_MASK, 0, -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) {.v = (const char*[]){ "/bin/sh", "-c", cmd, NULL }}

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_red , "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
#include <X11/XF86keysym.h>
#include "shiftview.c"
#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,           SHCMD("/usr/local/bin/dmenu_run")},
	{ 0,                       	XK_Print,  spawn,           SHCMD("/usr/bin/scrot $HOME/scrots/`date +%Y-%m-%d_%H:%M:%S`.png")},
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_t,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY, 			XK_n, 	   shiftview, 	   {.i = +1 } },
	{ MODKEY, 			XK_b, 	   shiftview, 	   {.i = -1 } },
	{ MODKEY,                       XK_q,       spawn,         SHCMD("st -e lf") }, // file manager
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("/usr/bin/xbacklight -inc 5")},
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("/usr/bin/xbacklight -dec 5")},
	{ 0, XF86XK_AudioRaiseVolume,	spawn, 		SHCMD("/usr/bin/pactl set-sink-volume 0 +5%")},
	{ 0, XF86XK_AudioLowerVolume,	spawn, 		SHCMD("/usr/bin/pactl set-sink-volume 0 -5%")},
	{ 0, XF86XK_AudioMute,		spawn, 		SHCMD("/usr/bin/pactl set-sink-mute 0 toggle")},
	{ MODKEY|ShiftMask, 		XK_x,      spawn, 		SHCMD("/home/coutinho/configs/i3lock-color/lock.sh")},
	{ MODKEY|ShiftMask, 		XK_s,      spawn, 		SHCMD("/usr/local/bin/shutdown_script.sh")},
	{ MODKEY|ShiftMask, 		XK_b,      spawn, 		SHCMD("/usr/local/bin/book.sh")},
	{ MODKEY|ShiftMask, 		XK_m,      spawn, 		SHCMD("/usr/bin/firefox https://open.spotify.com/collection/tracks")},
	{ MODKEY|ShiftMask, 		XK_h,      spawn, 	       SHCMD("/usr/local/bin/htop_scratch.sh")},
	{ MODKEY, 		    XK_grave,      spawn, 	       SHCMD("/usr/local/bin/st_scratch.sh")},
	{ MODKEY|ControlMask, 	       XK_j,     scratchpad_show, 	{0}                                          },
	//{ MODKEY|ControlMask, 	       XK_k,   scratchpad_hide,     {0}                                          },
	{ MODKEY|ShiftMask|ControlMask, XK_k,   scratchpad_remove,   {0}                               	     },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
