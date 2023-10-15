/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int gappx     = 12;        /* gaps between windows */
static const int vertpad            = 12;       /* vertical padding of bar */
static const int sidepad            = 81;       /* horizontal padding of bar */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int horizpadbar        = 2;        /* horizontal padding for statusbar */
static const int vertpadbar         = 9;        /* vertical padding for statusbar */
// static const char *fonts[]          = { "monospace:size=10" };
// static const char dmenufont[]       = "monospace:size=10";
// static const char *fonts[]          = { "Agave Nerd Font Mono:size=10" };
// static const char dmenufont[]       = "Agave Nerd Font Mono:size=10";
static const char *fonts[]          = { "Calling Code:size=9" };
static const char dmenufont[]       = "Calling Code:size=12";

static const char col_gray1[]       = "#4c4f69";
static const char col_gray2[]       = "#9ca0b0";
static const char col_gray3[]       = "#ccd0da";
static const char col_gray4[]       = "#5c5f77";
static const char col_surface0[]    = "#ccd0da";
static const char col_peach[]       = "#fe640b";
static const char *colors[][3]      = {
	/*               fg         bg            border   */
	[SchemeNorm] = { col_gray3, col_gray1,    col_surface0 },
	[SchemeSel]  = { col_gray4, col_surface0, col_peach },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

 // XXX: Rules
static const Rule rules[] = {
  /* xprop(1):
   *	WM_CLASS(STRING) = instance, class
   *	WM_NAME(STRING) = title
   */
  /* class      instance    title       tags mask     isfloating   monitor */
  // { "Gimp",     NULL,       NULL,       0,            0,           -1 },
  // { "Firefox",  NULL,       NULL,     1 << 8,       0,           -1 },
  // { "Gvim",  NULL,       NULL,       1 << 3,       0,           -1 },
  // { "Emacs",  NULL,       NULL,      1 << 4,       0,           -1 },
  // ==========
  // all floats
  // ==========
  { "Thunar",  NULL,       NULL,      0,       1,           -1 },
  { "st-256color",  NULL,       NULL,      0,       1,           -1 },
  { "Wish",  NULL,       NULL,      0,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[D]",      deck },
};

/* key definitions */
// #define MODKEY Mod1Mask
#define MODKEY Mod4Mask
#define ALTMODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[]       = { "dmenu_run", "-b", "-l",  "12", "-fn", dmenufont, "-nb", col_gray3, "-nf", col_gray4, "-sb", col_gray2, "-sf", col_gray1, NULL };
static const char *termcmd[]        = { "st", NULL };
static const char *screenshotcmd[]  = { "xfce4-screenshooter", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "72x10-20-50", NULL };

/* runorraise programs */
static const char *emacs[]       = { "emacs",       NULL, NULL, NULL, "Emacs"       };
static const char *gvim[]        = { "gvim",        NULL, NULL, NULL, "Gvim"        };
static const char *browser[]     = { "firefox",     NULL, NULL, NULL, "Firefox-esr" };
static const char *qutebrowser[] = { "qutebrowser", NULL, NULL, NULL, "qutebrowser" };
static const char *alacritty[]   = { "alacritty",   NULL, NULL, NULL, "Alacritty"   };
// static const char *stterm[]      = { "st",          NULL, NULL, NULL, "st-256color" };
static const char *thunar[]      = { "thunar",      NULL, NULL, NULL, "Thunar"      };
static const char *zathura[]     = { "zathura",     NULL, NULL, NULL, "Zathura"     };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ ALTMODKEY,                    XK_Return,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
  { ALTMODKEY,                    XK_n,      togglescratch,  {.v = scratchpadcmd } },
	{ 0,                       XK_F2,     spawn,          {.v = screenshotcmd } },
	{ ALTMODKEY|ShiftMask,          XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
        // XXX: jump to layouts
	{ ALTMODKEY,                    XK_t,      setlayout,      {.v = &layouts[0]} },
	{ ALTMODKEY,                    XK_f,      setlayout,      {.v = &layouts[1]} },
	{ ALTMODKEY,                    XK_m,      setlayout,      {.v = &layouts[2]} },
	{ ALTMODKEY,                    XK_r,      setlayout,      {.v = &layouts[3]} },
	{ ALTMODKEY,                    XK_space,  setlayout,      {0} },
	{ ALTMODKEY|ShiftMask,          XK_f,  togglefloating, {0} },

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ ALTMODKEY,                    XK_minus,  setgaps,        {.i = -1 } },
	{ ALTMODKEY,                    XK_equal,  setgaps,        {.i = +1 } },
	{ ALTMODKEY|ShiftMask,          XK_equal,  setgaps,        {.i = 0  } },
        // XXX: applications
        { MODKEY,                       XK_b,      runorraise,     {.v = browser } },
        { MODKEY,                       XK_m,      runorraise,     {.v = gvim } },
        { MODKEY,                       XK_n,      runorraise,     {.v = alacritty } },
        { MODKEY,                       XK_o,      runorraise,     {.v = emacs } },
        { MODKEY,                       XK_p,      runorraise,     {.v = zathura } },
        { ALTMODKEY,                    XK_b,      runorraise,     {.v = qutebrowser } },
        // { ALTMODKEY,                    XK_n,      runorraise,     {.v = stterm } },
        { ALTMODKEY,                    XK_p,      runorraise,     {.v = thunar } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            ALTMODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            ALTMODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         ALTMODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         ALTMODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         ALTMODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            ALTMODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            ALTMODKEY,         Button3,        toggletag,      {0} },
};

